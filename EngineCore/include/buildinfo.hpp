/**
 * @file
 * @brief Generates compile-time strings containing information about the build
 */
#pragma once

#include "PlatformSemantics.hpp"

#if SEMANTICS_IS_DEBUG == 1
#	define BUILDINFO_BUILDCONFIG "DEBUG"
#else
#	define BUILDINFO_BUILDCONFIG "RELEASE"
#endif

// Stringify contents of a macro
#define MACRO_QUOTE(name) #name
#define MACRO_STR(macro)  MACRO_QUOTE(macro)

// Determines the type of compiler and it's version based on compiler-specific predefined macros
//
#if defined(_MSC_VER) // MSVC compiler
#	pragma clang diagnostic ignored "-W#pragma-messages"
#	pragma message("-- Compiler MSVC detected")
#	define BUILDINFO_COMPILED_BY "MSVC " MACRO_STR(_MSC_FULL_VER) "." MACRO_STR(_MSC_BUILD)
#elif defined(__GNUC__)	  // Any GNU-like compiler
#	if defined(__llvm__) // Compilers that use LLVM as backend
#		pragma message("-- Compiler LLVM detected")
#		if defined(__clang__) // Clang with LLVM backend
#			pragma message("-- Compiler LLVM-clang detected")
#			define BUILDINFO_COMPILED_BY                                                          \
				"LLVM-clang " MACRO_STR(__clang_major__) "." MACRO_STR(__clang_minor__             \
				) "." MACRO_STR(__clang_patchlevel__);
#		else // Some other GNU-like compiler with LLVM is likely to be LLVM-GCC
#			pragma message("-- Compiler LLVM-GCC detected")
#			define BUILDINFO_COMPILED_BY                                                          \
				"LLVM-GCC " MACRO_STR(__GNUC__) "." MACRO_STR(__GNUC_MINOR__                       \
				) "." MACRO_STR(__GNUC_PATCHLEVEL__)
#		endif
#	else // An GNU-like compiler that is not using LLVM is likely to be pure GCC
#		pragma message("-- Compiler GCC detected")
#		define BUILDINFO_COMPILED_BY                                                              \
			"GCC " MACRO_STR(__GNUC__) "." MACRO_STR(__GNUC_MINOR__                                \
			) "." MACRO_STR(__GNUC_PATCHLEVEL__);
#	endif
#else // Any other compiler will simply be "Unknown"
#	pragma warning "-- Compiler could not be identified"
#	define BUILDINFO_COMPILED_BY "Unknown"
#endif

#include <string_view>

namespace Engine
{
	/**
	 * Time, date and build configuration
	 */
	constexpr std::string_view buildinfo_build = "CMEP EngineCore " __TIME__ " " __DATE__
												 " build, configured " BUILDINFO_BUILDCONFIG;

	/**
	 * Name and version of compiler
	 */
	constexpr std::string_view buildinfo_compiledby = BUILDINFO_COMPILED_BY;
} // namespace Engine

// Undefine macros, we don't want to pollute the namespace
#undef BUILDINFO_COMPILED_BY
#undef BUILDINFO_BUILDCONFIG
#undef MACRO_QUOTE
#undef MACRO_STR

// Macros SEMANTICS_COMPILER_* should not be undefined, they can be used for ifdefs
