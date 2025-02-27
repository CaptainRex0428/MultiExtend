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
        "USE_PRECOMPILED_HEADERS",

        -- 禁用自动ASM优化[^3]
        "CRYPTOPP_DISABLE_ASM=0",
        "CRYPTOPP_ARM_ASIMD_AVAILABLE=0",
        "CRYPTOPP_ARM_CRC32_AVAILABLE=0" 
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

    filter { "files:cryptopp/dll.cpp" }
        buildoptions { "/Y-", "/Yu\"\"" }

    filter { "files:cryptopp/iterhash.cpp" }
        buildoptions { "/Y-", "/Yu\"\"" }

    filter { "files:cryptopp/adhoc.cpp.proto" }
        buildcommands 
        {
            'if not exist adhoc.cpp copy "%{file.relpath}" adhoc.cpp',
            'echo: >> adhoc.cpp.copied'
        }
        buildoutputs { "adhoc.cpp.copied" }

    filter { "files:**.asm" }
        buildaction "CustomBuild"

    -- x64平台
    filter { "platforms:x64", "files:cryptopp/cpuid64.asm" }
        prebuildcommands 
        {
            'ml64.exe /c /nologo /D_M_X64 /W3 /Zi /Fo"$(IntDir)cpuid64.obj" "%{file.relpath}"'
        }
        buildoutputs { "$(IntDir)cpuid64.obj" }

    filter { "platforms:x64", "files:cryptopp/x64dll.asm" }
        prebuildcommands 
        {
            'ml64.exe /c /nologo /Fo"$(IntDir)x64dll.obj" "%{file.relpath}"'
        }
        buildoutputs { "$(IntDir)x64dll.obj" }

    filter { "platforms:x64", "files:cryptopp/x64masm.asm" }
        prebuildcommands 
        {
            'ml64.exe /c /nologo /Fo"$(IntDir)x64masm.obj" "%{file.relpath}"'
        }
        buildoutputs { "$(IntDir)x64masm.obj" }

    
    -- 强制启用MSVC特性[^4]
    filter { "toolset:msc*" }
        buildoptions { "/Zc:__cplusplus" }

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