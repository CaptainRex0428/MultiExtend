include "Directory.lua"
include "Dependencies.lua"

workspace "MultiExtend"
	architecture "x64"
	startproject "MultiSandbox"
	configurations{
		"Debug",
		"Release",
        "Dist"
	}

    filter "system:windows"
    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus","/utf-8" }
	
group "Render"
	include "Render/Render.lua"

group ""
	include "MultiExtend.lua"

group "Sandbox"
	include "MultiSandbox/MultiSandbox.lua"
	include "MultiTemplate/Template.lua"
	
group "Dependencies"
	include "Dependencies/SDL.lua"
	include "Dependencies/SDL_image.lua"
	include "Dependencies/glad.lua"
	include "Dependencies/glfw.lua"
	include "Dependencies/glew.lua"
	include "Dependencies/imgui.lua"
	include "Dependencies/libpng.lua"
	include "Dependencies/zlib.lua"

	include "Dependencies/dlg.lua"
	include "Dependencies/freetype.lua"
	include "Dependencies/harfbuzz.lua"
	include "Dependencies/SDL_ttf.lua"

	include "Dependencies/spdlog.lua"
	
group "Dependencies/Examples"
	include "Dependencies/SDL_image_Example.lua"
	include "Dependencies/dlg_example.lua"
	include "Dependencies/SDL_ttf_Example.lua"