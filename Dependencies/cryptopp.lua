project "cryptopp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    disablewarnings { "4996","4231"; "4251"; "4275"; "4355"; "4505" }

    pchheader "pch.h"
    pchsource "cryptopp/pch.cpp"

    files
    {
        "cryptopp/**.cpp",
        "cryptopp/**.h",
        "cryptopp/**.asm"
    }

    excludes
    {
        "cryptopp/Test**",
        "cryptopp/**test**",
        "cryptopp/**bench**",
        "cryptopp/fipsalgt.cpp",
        "cryptopp/adhoc.cpp"
    }

    includedirs
    {
        "%{DepIncludeDir.cryptopp}"
    }

    links
    {
        
    }

    defines
	{
        "USE_PRECOMPILED_HEADERS"
	}

    flags
    {
        "NoRuntimeChecks", -- Only used on Visual Studio.
		-- "NoBufferSecurityCheck"
    }

    vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions 
    { 
        "/EHsc", 
        "/Zc:preprocessor", 
        "/Zc:__cplusplus",
        "/Yu\"pch.h\"",  -- 使用预编译头文件
        "/Fp\"$(IntDir)pch.pch\"",-- 指定预编译头文件输出路径
        "/diagnostics:column"
    }

    warnings "off"

    location (LocationDir)
    targetdir (TargetDir)
    objdir (ObjectDir)

    -- inlining    "Explicit"
	-- intrinsics  "Off"

    filter{"platforms:win32"}
        excludes
        {
            "cryptopp/cpuid64.asm",
            "cryptopp/x64dll.asm",
            "cryptopp/x64masm.asm",
        }

    

    filter { "files:cryptopp/dll.cpp or cryptopp/iterhash.cpp" }
        buildoptions { "/Y-", "/Yu\"\"" }


    filter { "files:cryptopp/adhoc.cpp.proto" }
        buildcommands 
        {
            'if not exist adhoc.cpp copy "%{file.relpath}" adhoc.cpp',
            'echo: >> adhoc.cpp.copied'
        }
        buildoutputs { "adhoc.cpp.copied" }



    filter { "platforms:x64" }
        defines { 
            "_M_X64", 
            "CRYPTOPP_DISABLE_ASM=0",  -- 覆盖默认配置
            "CRYPTOPP_IMPORTS"         -- 启用DLL特性
        }
        buildoptions {
            "/Zc:__cplusplus",         -- 强制C++标准识别
            "/FI\"cryptopp/config_asm.h\""      -- 预包含配置文件
        }


        -- x64 build
    filter {'files:cryptopp/cpuid64.asm'}
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %[%{file.relpath}]'
        -- One or more commands to run (required)
        buildcommands 
        {
            'ml64.exe /c /nologo /D_M_X64 /W3 /Zi /Fo"$(IntDir)cpuid64.obj" "%(FullPath)"'
        }
        buildoutputs { "$(IntDir)/cpuid64.obj;%(Outputs)" }
        buildinputs {"cryptopp/config_asm.h"}

    filter {'files:cryptopp/rdrand.asm'}
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %[%{file.relpath}]'
        -- One or more commands to run (required)
        buildcommands 
        {
            'ml64.exe /c /nologo /D_M_X64 /W3 /Cx /Zi /Fo"$(IntDir)rdrand-x64.obj" "%(FullPath)"'
        }
        buildoutputs { "$(IntDir)/rdrand-x64.obj;%(Outputs)" }
        buildinputs {"cryptopp/config_asm.h"}

    filter {'files:cryptopp/rdseed.asm'}
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %[%{file.relpath}]'
        -- One or more commands to run (required)
        buildcommands 
        {
            'ml64.exe /c /nologo /D_M_X64 /W3 /Cx /Zi /Fo"$(IntDir)rdseed-x64.obj" "%(FullPath)"'
        }
        buildoutputs { "$(IntDir)/rdseed-x64.obj;%(Outputs)" }
        buildinputs {"cryptopp/config_asm.h"}

    filter {'files:cryptopp/x64masm.asm'}
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %[%{file.relpath}]'
        -- One or more commands to run (required)
        buildcommands 
        {
            'ml64.exe /c /nologo /D_M_X64 /W3 /Zi /Fo"$(IntDir)x64masm.obj" "%(FullPath)"'
        }
        buildoutputs { "$(IntDir)/x64masm.obj;%(Outputs)" }
        buildinputs {"cryptopp/config_asm.h"}

    
    filter {'files:cryptopp/x64dll.asm'}
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %[%{file.relpath}]'
        -- One or more commands to run (required)
        buildcommands 
        {
            'ml64.exe /c /nologo /D_M_X64 /W3 /Zi /Fo"$(IntDir)x64dll.obj" "%(FullPath)"'
        }
        buildoutputs { "$(IntDir)/x64dll.obj;%(Outputs)" }
        buildinputs {"cryptopp/config_asm.h"}


    -- 平台配置
    filter "system:windows" 
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