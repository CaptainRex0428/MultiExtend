project "glew"
	kind "StaticLib"
	language "C"
	targetname "glew"

	files
	{
		"glew/src/glew.c",  -- GLEW 源代码
        "glew/include/GL/**.h"
	}

	includedirs 
	{
        "glew/include"
    }

	defines
	{
		"WIN32","_LIB","WIN32_LEAN_AND_MEAN","GLEW_STATIC" -- GLEW_BUILD for DLL
	}

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines{"DEBUG"}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines{"NDEBUG"}

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		defines{"NDEBUG"}