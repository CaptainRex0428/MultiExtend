project "lua"
    kind "StaticLib"
    language "C"

    files
    {
        "lua/**.c",
        "lua/**.h"
    }

    includedirs
    {
        "lua"
    }

    links
    {
    }

    defines
	{
        "LUA_COMPAT_5_2",
        "LUA_COMPAT_MODULE",
        "lua_c","LUA_CORE"
	}

    flags
    {
        -- "NoRuntimeChecks", -- Only used on Visual Studio.
		-- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    warnings "off"

    location (LocationDir)
    targetdir (TargetDir)
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