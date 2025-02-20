project "OpenSSL"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    systemversion "latest"

    location (LocationDir)
    targetdir (TargetDir)
    objdir (ObjectDir)

    files
    {
        "openssl/include/openssl/**.h",
        "openssl/crypto/**.c", 
        "openssl/crypto/**.h",
        "openssl/ssl/**.c",    
        "openssl/ssl/**.h",
        "openssl/providers/**.c", 
        "openssl/providers/**.h", 

        "!openssl/crypto/LPdir_*.c"

        
    }

    includedirs
    {
        "openssl/include",
        "openssl/crypto/include",  -- 3.x新增头文件目录
        "openssl/ssl",
        "openssl/providers/common/include",
        "openssl/build/generated"
    }

    links
    {
    }

    defines
	{
        --"OPENSSL_OPENSSLCONF_H",
        "OPENSSL_API_COMPAT=30200",  -- API兼容性
        "OPENSSL_NO_DEPRECATED",      -- 禁用废弃API
        "OPENSSL_NO_SSL3_METHOD"      -- 禁用SSLv3
	}

    flags
    {
        -- "NoRuntimeChecks", -- Only used on Visual Studio.
		-- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    warnings "off"

    -- inlining    "Explicit"
	-- intrinsics  "Off"

    filter "system:windows" 
        -- staticruntime "Off"
        systemversion "latest"
        defines 
        { 
            "_WINDOWS",
            "WIN32_LEAN_AND_MEAN",
            "OPENSSL_SYS_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
            "OPENSSL_NO_ASM",  -- Windows禁用汇编
            "OPENSSL_NO_ASYNC",
            "OPENSSL_NO_KTLS"
        }

        files
        {
            "!openssl/**/test_*",     -- 排除测试
            "!openssl/**/example_*",  -- 排除示例
            "!openssl/**/fuzz_*"      -- 新增排除模糊测试    
        }

    filter {"system:macosx","system:linux"}
        defines 
        {
            "OPENSSL_THREADS",
            "OPENSSL_PIC"  -- 显式启用位置无关代码
        }

        files
        {
            "!openssl/**/asm/**",     -- 排除汇编代码
            "!openssl/**/modules/**"  -- 排除动态模块     
        }

        buildoptions { "-fPIC" }


    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "DEBUG","_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "Full"
        symbols "On"
        defines { "_RELEASE","NDEBUG" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"
        symbols "Off"
        defines { "_DIST","NDEBUG" }