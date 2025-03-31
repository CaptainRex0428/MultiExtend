project "MultiExtendTemplateFile"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "Template01.cpp"
    }

    includedirs
    {
        "%{ProjIncludeDir.MultiExtend}",
        "%{DepIncludeDir.spdlog}"
    }

    links
    {
        "MultiExtend",
        "spdlog"
    }

    defines
	{
	}

    flags
    {
    }

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    filter "system:windows" 
        systemversion "latest"
        defines { "_WINDOWS","_WIN64" }

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


project "MultiExtendTemplateEntity"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "Template02.cpp"
    }

    includedirs
    {
        "%{ProjIncludeDir.MultiExtend}",
        "%{DepIncludeDir.spdlog}"
    }

    links
    {
        "MultiExtend",
        "spdlog"
    }

    defines
	{
	}

    flags
    {
    }

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    filter "system:windows" 
        systemversion "latest"
        defines { "_WINDOWS","_WIN64" }

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


project "MultiExtendTemplateObject"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "Template03.cpp", "../assets/**"
    }

    includedirs
   {
     "%{ProjIncludeDir.MultiExtend}",
     "%{DepIncludeDir.SDL}",
     "%{DepIncludeDir.SDL_image}",
     "%{DepIncludeDir.spdlog}",
     "%{DepIncludeDir.cryptopp}"
   }

   links
   {
     "MultiExtend",
     "SDL",
     "SDL_main",
     "SDL_image",

     "spdlog",
     "cryptopp"
     
   }
   
   location (LocationDir)
   targetdir (EXEDir)
   objdir (ObjectDir)

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"


project "MultiExtendTemplateSSL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "Template04.cpp",
        "test.lua"
    }

    includedirs
    {
        "%{ProjIncludeDir.MultiExtend}",
        "%{DepIncludeDir.spdlog}",
        "%{DepIncludeDir.luacrypto}",
        "%{DepIncludeDir.lua}",
        "%{DepIncludeDir.openssl}",
        "%{DepIncludeDir.cryptopp}"

    }

    libdirs
    {
        "%{LibDirectories.openssl}"
    }

    links
    {
        "MultiExtend",
        "spdlog",

        "libcrypto",
        "libssl",
        "lua",
        "luacrypto",

        "cryptopp"
        
    }

    defines
    {
        
    }

    flags
    {
    }

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus"}

    location (LocationDir)
    targetdir (EXEDir)
    objdir (ObjectDir)

    filter "system:windows" 
        systemversion "latest"
        defines { "_WINDOWS","_WIN64" }

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