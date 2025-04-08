project "glew"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

	files
	{
		"glew/src/glew.c",  -- GLEW 源代码
        "glew/include/GL/**.h"
	}

	includedirs 
	{
		"%{DepIncludeDir.glfw}",
        "glew/include"
    }

	links
	{
		"glfw",
		"opengl32"
	}

	defines
	{
		"GLEW_BUILD" 
		-- GLEW_BUILD for DLL
	}

	flags
    {
        -- "NoRuntimeChecks", -- Only used on Visual Studio.
		-- "NoBufferSecurityCheck"
    }

	buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    warnings "off"

    location (LocationDir)
    targetdir (TargetDir)
    objdir (ObjectDir)

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} "..DynamicDir)
	}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG","DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "On"
        defines { "_RELEASE","NDEBUG" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"
        symbols "Off"
        defines { "_DIST","NDEBUG" }