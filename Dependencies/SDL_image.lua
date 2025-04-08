project "SDL_image"             
	kind          "StaticLib"
	language          "C++"            
	cppdialect        "C++20"

	-- vectorextensions  "SSE"

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	includedirs
	{
		"SDL_image/include", 
		"lib/libpng/",
		"%{DepIncludeDir.SDL}",
		"%{DepIncludeDir.libpng}"
	}

	links
	{
		"SDL",
		"SDL_main",
		"libpng"
	}

	defines
	{
		"LOAD_PNG",
		"LOAD_TGA",
		-- "LOAD_GIF",
		-- "LOAD_JPG",
		-- "LOAD_BMP",
		-- "LOAD_PNM",
		-- "LOAD_WEBP",
		-- "LOAD_PIC",
		-- "LOAD_PSD",
		-- "LOAD_PIC",
		-- "LOAD_TIF",
		-- "LOAD_SVG"
	}

	files {
		"SDL_image/include/*.h",					
		"SDL_image/src/**.h",						"SDL_image/src/**.c",		
	}

	-- inlining          "Explicit"
	-- intrinsics        "Off"

	filter "system:windows"
		staticruntime "off"
		systemversion "latest"
		defines {"_WINDOWS"}
		links 
		{
			"setupapi",
			"winmm",
			"imm32",
			"version",
		}
		

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