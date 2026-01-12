#pragma once

#include "Assets/AssetManager.hpp"

#include "EventHandling.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "SceneObject.hpp"

/** Provides functions that construct a proper table for the specified object */
namespace Engine::Scripting::API::LuaFactories
{
	template <typename class_t>
	void templatedFactory(lua_State* state, class_t* object_ptr);

	template <>
	void templatedFactory(lua_State* state, AssetManager* object_ptr);
	template <>
	void templatedFactory(lua_State* state, SceneManager* object_ptr);
	template <>
	void templatedFactory(lua_State* state, Scene* object_ptr);
	template <>
	void templatedFactory(lua_State* state, SceneObject* object_ptr);
	template <>
	void templatedFactory(lua_State* state, Engine* object_ptr);

} // namespace Engine::Scripting::API::LuaFactories
