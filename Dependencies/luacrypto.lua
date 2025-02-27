project "luacrypto"
    kind "SharedLib"
    language "C"

    files
    {
        "luacrypto/src/**.c",
        "luacrypto/src/**.h"
    }

    includedirs
    {
        "%{DepIncludeDir.openssl}",
        "%{DepIncludeDir.lua}"
    }

    libdirs
    {
        "%{LibDirectories.openssl}",
        "%{LibDirectories.lua}"
    }

    links
    {
        "libcrypto",
        "libssl",
        "lua"
    }

    linkoptions 
    {
        "/IMPLIB:" .. TargetDir .. "/luacrypto.lib"  -- 添加这一行
    }

    defines
	{   
        "OPENSSL_API_COMPAT=0x10100000L",
        "LUA_COMPAT_5_2",
        "LUACRYPTO_EXPORTS",
        "_CRT_SECURE_NO_WARNINGS",
        "_USRDLL",
        "LUACRYPTO_API=__declspec(dllexport)"
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

    inlining    "Explicit"
	-- intrinsics  "Off"

    postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} "..DynamicDir)
	}

    filter "system:windows" 
        staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS","WIN32" }
        links { "Advapi32","Crypt32","Ws2_32" } 

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