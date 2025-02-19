project "dlg_example"             
	kind          "ConsoleApp"
	language          "C++"           
	cppdialect        "C++20"

	includedirs      
    {
        "dlg/include"
    }

	files 
	{
		"dlg/docs/examples/example.cpp"		
	}

	links
   	{
    	"dlg"
   	}

   	location (LocationDir)
	targetdir (EXEDir)
	objdir (ObjectDir)
		
	inlining    "Explicit"
	intrinsics  "Off"

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
        defines { "_RELEASE","NDBUG" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"
        symbols "Off"
        defines { "_DIST","NDEBUG" }
