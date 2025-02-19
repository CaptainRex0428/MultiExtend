project "freetype"             
	kind          "StaticLib"
	language          "C++"             
	cppdialect        "C++20" 

	flags {
		"NoRuntimeChecks",
		"NoBufferSecurityCheck"
	}

	-- vectorextensions  "SSE"

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	includedirs
    {
		"freetype/src",
        "freetype/include",
		"%{DepIncludeDir.dlg}"
    }

	links
	{
		"dlg"
	}

	files {
		"freetype/src/autofit/autofit.c", 	"freetype/src/bdf/bdf.c", 			"freetype/src/cff/cff.c", 				"freetype/src/base/ftbase.c",
        "freetype/src/base/ftbitmap.c", 	"freetype/src/cache/ftcache.c", 	"freetype/src/base/ftfstype.c", 		"freetype/src/base/ftgasp.c",
        "freetype/src/base/ftglyph.c", 		"freetype/src/gzip/ftgzip.c", 		"freetype/src/base/ftinit.c", 			"freetype/src/lzw/ftlzw.c",
        "freetype/src/base/ftstroke.c", 	"freetype/src/base/ftsystem.c", 	"freetype/src/smooth/smooth.c", 		"freetype/src/base/ftbbox.c",
        "freetype/src/base/ftfntfmt.c", 	"freetype/src/base/ftmm.c", 		"freetype/src/base/ftpfr.c", 			"freetype/src/base/ftsynth.c",
        "freetype/src/base/fttype1.c", 		"freetype/src/base/ftwinfnt.c", 	"freetype/src/base/ftlcdfil.c", 		"freetype/src/base/ftgxval.c",
        "freetype/src/base/ftotval.c", 		"freetype/src/base/ftpatent.c", 	"freetype/src/pcf/pcf.c", 				"freetype/src/pfr/pfr.c",
        "freetype/src/psaux/psaux.c", 		"freetype/src/pshinter/pshinter.c", 										"freetype/src/psnames/psmodule.c",
        "freetype/src/raster/raster.c", 	"freetype/src/sfnt/sfnt.c", 		"freetype/src/truetype/truetype.c",
        "freetype/src/type1/type1.c", 		"freetype/src/cid/type1cid.c", 		"freetype/src/type42/type42.c", 		"freetype/src/winfonts/winfnt.c",
		"freetype/src/pshinter/pshinter.c",	"freetype/src/psnames/psnames.c",  	"freetype/src/raster/raster.c",
  		"freetype/src/sdf/sdf.c",			"freetype/src/smooth/smooth.c", 	"freetype/src/svg/*.c"
	}

	inlining    "Explicit"
	intrinsics  "Off"

	defines{
		"_CRT_SECURE_NO_WARNINGS",
		"FT2_BUILD_LIBRARY",
		"FT_PUBLIC_FUNCTION_ATTRIBUTE=",
		"FT_CONFIG_OPTION_ERROR_STRINGS"
	}

	filter "system:windows" 
        staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS" }
		files { "freetype/builds/windows/ftdebug.c"}

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