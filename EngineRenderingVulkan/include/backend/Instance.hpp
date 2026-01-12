#pragma once
// IWYU pragma: private; include Rendering/Vulkan/backend.hpp

#include "fwd.hpp"

#include "Rendering/Transform.hpp"

#include "Logging/Logging.hpp"

#include "backend/LogicalDevice.hpp"
#include "backend/MemoryAllocator.hpp"
#include "backend/PhysicalDevice.hpp"
#include "common/HandleWrapper.hpp"
#include "rendering/Window.hpp"
#include "vulkan/vulkan_raii.hpp"

#include <string>
#include <utility>
#include <vector>

namespace Engine::Rendering::Vulkan
{
#if defined(ENGINERENDERINGVULKAN_LIBRARY_IMPLEMENTATION)
	/**
	 * Vulkan callback for logging
	 */
	extern const vk::PFN_DebugUtilsMessengerCallbackEXT debug_callback;
#endif

	class Instance final : public Logging::SupportsLogging, public HandleWrapper<vk::raii::Instance>
	{
	public:
		struct WindowParams
		{
			const ScreenSize						size;
			const std::string&						title;
			const std::vector<std::pair<int, int>>& hints;
		};

		Instance(SupportsLogging::logger_t with_logger, const WindowParams&& with_window_parameters);
		~Instance();

		[[nodiscard]] Window* getWindow()
		{
			return window;
		}

		[[nodiscard]] const PhysicalDevice* getPhysicalDevice()
		{
			return physical_device;
		}

		[[nodiscard]] LogicalDevice* getLogicalDevice()
		{
			return logical_device;
		}

		[[nodiscard]] CommandPool* getCommandPool()
		{
			return command_pool;
		}

		[[nodiscard]] MemoryAllocator* getGraphicMemoryAllocator()
		{
			return memory_allocator;
		}

	private:
		vk::raii::DebugUtilsMessengerEXT debug_messenger = nullptr;

		vk::raii::Context context;

		PhysicalDevice*	 physical_device  = nullptr;
		LogicalDevice*	 logical_device	  = nullptr;
		MemoryAllocator* memory_allocator = nullptr;

		Window*		 window		  = nullptr;
		CommandPool* command_pool = nullptr;

		void initInstance();
		void initDevice();

		static bool checkVulkanValidationLayers();
	};
} // namespace Engine::Rendering::Vulkan
