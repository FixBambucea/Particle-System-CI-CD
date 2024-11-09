#pragma once

// TODO: sau Forward Declarations
#include "Window.h"

#include <vector>
#include <optional>

namespace VulkanCore {

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        inline bool IsComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class GPUDevice
    {
    public:
        // Constructor
        GPUDevice(Window& window);

        // Destructor
        ~GPUDevice();

        // Not copyable
        GPUDevice(const GPUDevice&) = delete;
        GPUDevice& operator = (const GPUDevice&) = delete;

        // Not moveable
        GPUDevice(GPUDevice&&) = delete;
        GPUDevice& operator = (GPUDevice&&) = delete;

        // Getters
        inline VkSurfaceKHR GetSurface() const { return surface; }  // TODO: return const &
        inline VkDevice GetDevice() const { return device; }        // TODO: return const &
        inline SwapChainSupportDetails GetSwapChainSupport() const { return QuerySwapChainSupport(physicalDevice); }    // TODO: return const &
        inline QueueFamilyIndices GetPhysicalQueueFamilies() const { return FindQueueFamilies(physicalDevice); }        // TODO: return const &

    private:
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

#ifdef DEBUG
        const bool bEnableValidationLayers = true;
#else
        const bool bEnableValidationLayers = false;
#endif

        static const std::vector<const char*> validationLayers;
        static const std::vector<const char*> deviceExtensions;

        void CreateInstance();
        void SetupDebugMessenger();
        void CreateSurface(Window& window);
        void PickPhysicalDevice();
        void CreateLogicalDevice();

        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        std::vector<const char*> GetRequiredExtensionNames();
        bool CheckValidationLayerSupport();
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
        bool IsDeviceSuitable(VkPhysicalDevice device);

        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device) const;

        // DEBUG
        void ListAvailableExtensions() const;
        void ListRequiredGLFWExtensions() const;
        void ListAvailableValidationLayers() const;
        void ListAvailablePhysicalDevices() const;
    };

} // namespace VulkanCore
