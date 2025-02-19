project "dlg"             
	kind          "SharedLib"
	language          "C++"       
	cppdialect        "C++20"
                            
	flags {
		-- "NoRuntimeChecks",
		-- "NoBufferSecurityCheck"
	}

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} "..DynamicDir)
	}

	includedirs      
    {
        "dlg/include"
    }

	files {
		"dlg/src/**.c"		
	}
		
	--inlining    "Explicit"
	--intrinsics  "Off"

	filter "system:windows"
		staticruntime "Off"
		systemversion "latest"
		defines {"_WINDOWS","_WIN64","DLG_WIN_CONSOLE"}

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
