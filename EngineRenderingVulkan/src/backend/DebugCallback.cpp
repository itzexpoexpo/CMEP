#include "Logging/Logging.hpp"

#include "Exception.hpp"

#define ENGINERENDERINGVULKAN_LIBRARY_IMPLEMENTATION
#include "backend/Instance.hpp"
#include "vulkan/vulkan.hpp"

namespace Engine::Rendering::Vulkan
{
	namespace
	{
		// NOLINTBEGIN(readability-identifier-naming) this function has names as specified by Vulkan
		VKAPI_ATTR vk::Bool32 VKAPI_CALL vulkanDebugCallback(
			vk::DebugUtilsMessageSeverityFlagBitsEXT	  messageSeverity,
			vk::DebugUtilsMessageTypeFlagsEXT			  messageType,
			const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void*										  pUserData
		)
		{
			(void)(messageType);

			auto locked_logger = static_cast<Logging::SupportsLogging*>(pUserData)->getLogger();
			EXCEPTION_ASSERT(locked_logger, "Failed locking logger on Lua print() call");

			// Log as error only if error bit set
			Logging::LogLevel log_level = static_cast<unsigned int>(
											  messageSeverity &
											  vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
										  ) != 0
											  ? Logging::LogLevel::Error
											  : Logging::LogLevel::Warning;

			locked_logger->logSingle<void>(
				log_level,
				"Validation layer reported:\n{}",
				pCallbackData->pMessage
			);

			return vk::False;
		}
		// NOLINTEND(readability-identifier-naming)
	} // namespace

	const vk::PFN_DebugUtilsMessengerCallbackEXT debug_callback = vulkanDebugCallback;

} // namespace Engine::Rendering::Vulkan
