project "zlib"             
	kind          "StaticLib"
	language          "C++"
	cppdialect        "C++20"

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	includedirs      
    {
        "zlib"
    }

	files {
		"zlib/adler32.c",
        "zlib/compress.c",
        "zlib/crc32.c",
        "zlib/deflate.c",
        "zlib/infback.c",
        "zlib/inffast.c",
        "zlib/inflate.c",
        "zlib/inftrees.c",
        "zlib/trees.c",
        "zlib/uncompr.c",
        "zlib/zutil.c"
					
	}
		
	flags {
		"NoRuntimeChecks",
		"NoBufferSecurityCheck"
	}

	-- vectorextensions  "SSE"

	inlining    "Explicit"
	intrinsics  "Off"

	filter "system:windows"
		systemversion "latest"
		staticruntime "off"
		defines {"_WINDOWS"}

	filter "configurations:Debug"
		defines {"_DEBUG"}
		runtime       "Debug"
		symbols       "On"

	filter "configurations:Release"
		defines {"_RELEASE","NDEBUG"}
		runtime       "Release"
		optimize      "Speed"


	filter "configurations:Dist"
		defines {"_Dist","NDEBUG"}
		runtime       "Release"
		optimize      "On"
