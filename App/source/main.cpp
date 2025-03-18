#include "AppConfig.h"

#include <SDL3/SDL.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <chrono>
#include <thread>

using Clock = std::chrono::steady_clock;

bool
bitflagAnd(const unsigned int flags, const unsigned int bitflag);

int
main(int argc, char* argv[]) {
  std::cout << "Executing " << APP_NAME << " from path: " << argv[0] << std::endl;
  
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;

		return -1;
	}
	
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE;
	window = SDL_CreateWindow(APP_NAME, 1280, 720, windowFlags);
	if (window == nullptr) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;

		return -2;
	}

  renderer = SDL_CreateRenderer(window, nullptr);
  if (renderer == nullptr) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;

    SDL_DestroyWindow(window);
    SDL_Quit();

    return -3;
  }

  VkStructureType sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

  VkApplicationInfo appInfo = {
    VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO,
    nullptr,
    APP_NAME,
    VK_MAKE_VERSION(1, 0, 0),
    "No Engine",
    VK_MAKE_VERSION(1, 0, 0),
    VK_API_VERSION_1_0
  };

  VkInstanceCreateInfo createInfo = {
    VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    nullptr,
    0,
    &appInfo,
    0,
    nullptr,
    0,
    nullptr
  };
  
  VkInstance vulkanInstance;
  
  VkDevice vulkanDevice;

  VkResult createInstanceResult = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);

  switch (createInstanceResult) {
    case VK_SUCCESS:
      std::cout << "Vulkan instance created successfully" << std::endl;
      break;
    case VK_ERROR_OUT_OF_HOST_MEMORY:
      std::cout << "Vulkan instance creation failed: out of host memory" << std::endl;
      break;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      std::cout << "Vulkan instance creation failed: out of device memory" << std::endl;
      break;
    case VK_ERROR_INITIALIZATION_FAILED:
      std::cout << "Vulkan instance creation failed: initialization failed" << std::endl;
      break;
    case VK_ERROR_LAYER_NOT_PRESENT:
      std::cout << "Vulkan instance creation failed: layer not present" << std::endl;
      break;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      std::cout << "Vulkan instance creation failed: extension not present" << std::endl;
      break;
    case VK_ERROR_INCOMPATIBLE_DRIVER:
      std::cout << "Vulkan instance creation failed: incompatible driver" << std::endl;
      break;
    default:
      std::cout << "Vulkan instance creation failed: unknown error" << std::endl;
      break;
  }

  if (createInstanceResult == VK_SUCCESS) {
    unsigned int physicalDeviceCount = 0;
    VkPhysicalDevice* physicalDevices = nullptr;

    VkResult enumeratePhysicalDevicesResult = vkEnumeratePhysicalDevices(vulkanInstance, &physicalDeviceCount, nullptr);

    if (enumeratePhysicalDevicesResult == VK_SUCCESS) {
      physicalDevices = new VkPhysicalDevice[physicalDeviceCount];

      enumeratePhysicalDevicesResult = vkEnumeratePhysicalDevices(vulkanInstance, &physicalDeviceCount, physicalDevices);

      if (enumeratePhysicalDevicesResult == VK_SUCCESS) {
        std::cout << "Physical devices enumerated successfully" << std::endl;
      }
      else {
        std::cout << "Failed to enumerate physical devices: " << enumeratePhysicalDevicesResult << std::endl;
      }

      for (unsigned int i = 0; i < physicalDeviceCount; i++) {
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceProperties(physicalDevices[i], &properties);
        vkGetPhysicalDeviceMemoryProperties(physicalDevices[i], &memoryProperties);

        std::cout << "Physical device " << i << " properties:" << std::endl;
        std::cout << "  API version: "          << properties.apiVersion << std::endl;
        std::cout << "  Driver version: "       << properties.driverVersion << std::endl;
        std::cout << "  Vendor ID: "            << properties.vendorID << std::endl;
        std::cout << "  Device ID: "            << properties.deviceID << std::endl;
        std::cout << "  Device type: "          << properties.deviceType << std::endl;
        std::cout << "  Device name: "          << properties.deviceName << std::endl;
        std::cout << "  Pipeline cache UUID: "  << properties.pipelineCacheUUID << std::endl;
        std::cout << std::endl;

        std::cout << "Physical device " << i << " memory properties:" << std::endl;
        std::cout << "  Memory heap count: " << memoryProperties.memoryHeapCount << std::endl;
        for (unsigned int j = 0; j < memoryProperties.memoryHeapCount; j++) {
          std::cout << "    Memory heap " << j << " size: " << memoryProperties.memoryHeaps[j].size << std::endl;
          std::cout << "    Memory heap " << j << " flags: " << memoryProperties.memoryHeaps[j].flags << std::endl;
        }
        std::cout << "  Memory type count: " << memoryProperties.memoryTypeCount << std::endl;
        for (unsigned int j = 0; j < memoryProperties.memoryTypeCount; j++) {
          std::cout << "    Memory type " << j << " heap index: " << memoryProperties.memoryTypes[j].heapIndex << std::endl;
          std::cout << "    Memory type " << j << " property flags: " << memoryProperties.memoryTypes[j].propertyFlags << std::endl;
        }
        std::cout << std::endl;

        unsigned int queueFamilyPropertyCount = 0;
        VkQueueFamilyProperties* queueFamilyProperties = nullptr;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[0], &queueFamilyPropertyCount, nullptr);

        queueFamilyProperties = new VkQueueFamilyProperties[queueFamilyPropertyCount];
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[0], &queueFamilyPropertyCount, queueFamilyProperties);

        for (unsigned int j = 0; j < queueFamilyPropertyCount; j++) {
          std::cout << "Queue family " << i << " properties:" << std::endl;
          std::cout << "  Queue count: " << queueFamilyProperties[j].queueCount << std::endl;
          std::cout << "  Queue supports graphics: " << (bitflagAnd(queueFamilyProperties[j].queueFlags, VK_QUEUE_GRAPHICS_BIT) ? "true" : "false") << std::endl;
          std::cout << "  Queue supports compute: " << (bitflagAnd(queueFamilyProperties[j].queueFlags, VK_QUEUE_COMPUTE_BIT) ? "true" : "false") << std::endl;
          std::cout << "  Timestamp valid bits: " << queueFamilyProperties[j].timestampValidBits << std::endl;
          std::cout << "  Min image transfer granularity: " << queueFamilyProperties[j].minImageTransferGranularity.width << "x" << queueFamilyProperties[j].minImageTransferGranularity.height << "x" << queueFamilyProperties[j].minImageTransferGranularity.depth << std::endl;
          std::cout << std::endl;
        }

        delete[] queueFamilyProperties;
      }
      
      VkPhysicalDeviceFeatures supportedFeatures;
      VkPhysicalDeviceFeatures requiredFeatures = {};

      vkGetPhysicalDeviceFeatures(physicalDevices[0], &supportedFeatures);

      requiredFeatures.multiDrawIndirect = supportedFeatures.multiDrawIndirect;
      requiredFeatures.tessellationShader = VK_TRUE;
      requiredFeatures.geometryShader = VK_TRUE;

      VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
        VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        nullptr,
        0,
        0,
        1,
        nullptr
      };

      VkDeviceCreateInfo deviceCreateInfo = {
        VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        nullptr,
        0,
        1,
        &deviceQueueCreateInfo,
        0,
        nullptr,
        0,
        nullptr,
        &requiredFeatures
      };
      
      VkResult createDeviceResult = vkCreateDevice(physicalDevices[0], &deviceCreateInfo, nullptr, &vulkanDevice);
      
      delete[] physicalDevices;
    }
    else {
      std::cout << "Failed to enumerate physical devices: " << enumeratePhysicalDevicesResult << std::endl;
    }
  }

	bool quit = createInstanceResult != VK_SUCCESS;
  
  std::chrono::time_point<Clock> lastTime = Clock::now();
  std::chrono::time_point<Clock> newTime;
  std::chrono::milliseconds deltaTime;

  int fps = 60;
  std::chrono::milliseconds msPerFrame(1000 / fps);

  while (!quit) {
		SDL_Event evt;

		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			else if (evt.type == SDL_EVENT_KEY_DOWN) {
				if (evt.key.key == SDLK_ESCAPE) {
          quit = true;
        }
			}
		}

		if (quit) {
			break;
		}

    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    newTime = Clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - lastTime);
    lastTime = newTime;

    std::chrono::milliseconds remainingTime = msPerFrame - deltaTime;
    if (remainingTime.count() > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime.count()));
    }
	}

  SDL_DestroyWindow(window);
  SDL_Quit();

  if (vulkanDevice) {
    vkDestroyDevice(vulkanDevice, nullptr);
  }

  if (vulkanInstance) {
    vkDestroyInstance(vulkanInstance, nullptr);
  }
  
  return 0;
}

bool
bitflagAnd(const unsigned int flags, const unsigned int bitflag) {
  return (flags & bitflag) == bitflag;
}