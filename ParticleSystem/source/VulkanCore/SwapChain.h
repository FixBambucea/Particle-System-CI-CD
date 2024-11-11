#pragma once

// TODO: asta sau alt Window / GPUDevice
#include "Window.h"
#include "GPUDevice.h"

#include <vector>

namespace VulkanCore {

	class SwapChain final
	{
	public:
        // Constructor
        SwapChain(GPUDevice& device, const Window& window);

        // Destructor
        ~SwapChain();

        // Not copyable
        SwapChain(const SwapChain&) = delete;
        SwapChain& operator = (const SwapChain&) = delete;

        // Not moveable
        SwapChain(SwapChain&&) = delete;
        SwapChain& operator = (SwapChain&&) = delete;

        VkResult AcquireNextImage(uint32_t* imageIndex);
        VkResult SubmitCommandBuffer(const VkCommandBuffer* buffer, uint32_t* imageIndex);

        // Getters
        VkExtent2D GetSwapChainExtent() const { return swapChainExtent; }
        VkRenderPass GetRenderPass() const { return renderPass; }
        VkFramebuffer GetSwapChainFramebuffer(const size_t& index) const { return swapChainFramebuffers[index]; }

	private:
        GPUDevice& device; // TODO: const?
        const Window& window;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        VkRenderPass renderPass;

        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;

        void CreateSwapChain();
        void CreateImageViews();
        void CreateRenderPass();
        void CreateChainFramebuffers();
        void CreateSyncObjects();

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	};

} // namespace VulkanCore