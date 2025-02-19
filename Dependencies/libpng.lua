project "libpng"             
	kind          "StaticLib"
	language          "C++"              -- Some files are C++ files, although they
	cppdialect        "C++20"            -- are not needed on normal Windows.
                            
	systemversion     "latest"

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	includedirs      
    {
        "libpng",
		"lib/libpng/",
        "%{DepIncludeDir.zlib}"
    }

	links
	{
		"zlib"
	}

	defines
	{
		-- "PNG_WRITE_INT_FUNCTIONS_SUPPORTED"
	}

	files 
    {
        "libpng/arm/arm_init.c",
        "libpng/arm/filter_neon_intrinsics.c",
        "libpng/arm/palette_neon_intrinsics.c"	,
        "libpng/png.c",
        "libpng/pngerror.c",
        "libpng/pngget.c",
        "libpng/pngmem.c",
        "libpng/pngpread.c",
        "libpng/pngread.c",
        "libpng/pngrio.c",
        "libpng/pngrtran.c",
        "libpng/pngrutil.c",
        "libpng/pngset.c",
        "libpng/pngtrans.c",
        "libpng/scripts/pngwin.rc",
        "libpng/pngwio.c",
        "libpng/pngwrite.c",
        "libpng/pngwtran.c",
        "libpng/pngwutil.c"
	}

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
		defines {"RELEASE","NDEBUG"}
		runtime       "Release"
		optimize      "Speed"


	filter "configurations:Dist"
		defines {"Dist","NDEBUG"}
		runtime       "Release"
		optimize      "On"

