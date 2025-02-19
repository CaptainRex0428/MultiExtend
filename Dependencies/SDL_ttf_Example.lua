project "showfont"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "SDL_ttf/showfont.c"
    }

    includedirs
    {
        "%{DepIncludeDir.SDL_ttf}",
        "%{DepIncludeDir.SDL}"
    }

    links
    {
        "freetype",          -- 确保链接 FreeType 库
        "harfbuzz", 
        "SDL",
		"SDL_main",
        "SDL_ttf",
        "OpenGL32.lib"
    }

    libdirs
    {
        "%{LibDirectories.SDL_ttf}"
    }

    defines
	{
        "_CRT_SECURE_NO_WARNINGS"
	}

    flags
    {
        -- "NoRuntimeChecks",
		-- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    warnings "Off"

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    inlining    "Explicit"
	intrinsics  "Off"

    filter "system:windows" 
        staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

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

project "glfont"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    
    files
    {
        "SDL_ttf/glfont.c"
    }

    includedirs
    {
        "%{DepIncludeDir.SDL_ttf}",
        "%{DepIncludeDir.SDL}"
    }

    links
    {
        "freetype",          -- 确保链接 FreeType 库
        "harfbuzz", 
        "SDL",
		"SDL_main",
        "SDL_ttf",
        "OpenGL32.lib"
    }

    libdirs
    {
        "%{LibDirectories.SDL_ttf}"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "HAVE_OPENGL"
    }

    flags
    {
        -- "NoRuntimeChecks",
        -- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    warnings "Off"

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    inlining    "Explicit"
    intrinsics  "Off"

    filter "system:windows" 
        staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

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