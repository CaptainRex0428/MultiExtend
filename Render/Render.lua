project "Render"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "include/**.h",
        "src/**.cpp"
    }
    
    includedirs
    {
        "include",
        "%{ProjIncludeDir.MultiExtend}",
        "%{DepIncludeDir.SDL}",
        "%{DepIncludeDir.SDL_image}",
        "%{DepIncludeDir.glad}",
        "%{DepIncludeDir.glfw}",
        "%{DepIncludeDir.glew}",
        "%{DepIncludeDir.spdlog}",
        "%{DepIncludeDir.cryptopp}",
		"%{DepIncludeDir.libpng}",
        "%{DepIncludeDir.linmath}",
        "%{DepIncludeDir.spdlog}"
    }

	links
	{

        "spdlog",
        "cryptopp",
        "SDL_image",
		"SDL",
		"SDL_main",
		"libpng",
        "glfw",
        "glad",
        "glew",
        "MultiExtend",
        "OpenGL32.lib",
        "User32.lib",
        "Gdi32.lib",
        "Shell32.lib"
	}

    libdirs
    {

    }

	defines
	{

	}

    flags
    {
        -- "NoRuntimeChecks", -- Only used on Visual Studio.
		-- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    -- warnings "off"

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    -- inlining    "Explicit"
	-- intrinsics  "Off"

    filter "system:windows" 
        -- staticruntime "Off"
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