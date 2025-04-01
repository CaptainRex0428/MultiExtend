project "MultiSandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "src/**.cpp","include/**.h"
    }

    includedirs
    {
        "include",
        "%{ProjIncludeDir.MultiExtend}",
        "%{DepIncludeDir.spdlog}",
        "%{DepIncludeDir.SDL}",
        "%{DepIncludeDir.SDL_image}",
        "%{DepIncludeDir.cryptopp}"
    }

    links
    {
        "MultiExtend",
        "spdlog",
        "SDL",
        "SDL_main",
        "SDL_image",

        "cryptopp"
    }

    defines
	{
	}

    flags
    {
        "NoRuntimeChecks",
		"NoBufferSecurityCheck"
    }

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    -- inlining    "Explicit"
	-- intrinsics  "Off"

    filter "system:windows" 
        -- staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS","_WIN64" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "Speed"
        symbols "On"
        defines { "NDEBUG" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "Full"
        symbols "Off"
        defines { "NDEBUG" }