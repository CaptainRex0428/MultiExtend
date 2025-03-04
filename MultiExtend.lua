project "MultiExtend"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    files
    {
        "src/**.cpp",
        "include/**.h"
    }

    includedirs
    {
        "include",
        
        "%{DepIncludeDir.spdlog}",
        "%{DepIncludeDir.openssl}",
        "%{DepIncludeDir.cryptopp}",
        
        "%{DepIncludeDir.SDL}",
        "%{DepIncludeDir.SDL_image}"
    }

    libdirs
    {
        "%{LibDirectories.openssl}"
    }

    links
    {
        "spdlog",
        "libcrypto",
        "libssl",
        "cryptopp",
        "SDL",
        "SDL_main",
        "SDL_image"
    }

    defines
	{
        "_CRT_SECURE_NO_WARNINGS",
        "MULTI_EXTEND_BUILD_DLL_EXPORT"
	}

    flags
    {
        "NoRuntimeChecks",
		-- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    -- buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    -- warnings "off"

    location (LocationDir)
    targetdir (TargetDir)
    objdir (ObjectDir)

    inlining    "Explicit"
	-- intrinsics  "Off"

    postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} "..DynamicDir)
	}

    filter "system:windows" 
        staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG","SPDLOG_ACTIVE_LEVEL=0","MULTIEXTEND_DEBUG_DETAIL" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "On"
        defines { "_RELEASE","NDEBUG","SPDLOG_ACTIVE_LEVEL=1" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"
        symbols "Off"
        defines { "_DIST","NDEBUG","SPDLOG_ACTIVE_LEVEL=3" }