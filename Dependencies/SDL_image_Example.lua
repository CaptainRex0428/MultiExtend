project "showimage"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   files { "SDL_image/examples/showimage.c"}

   includedirs
   {
      "%{DepIncludeDir.SDL}",
	  "SDL_image/include"
   }

   links
   {
      "SDL",
      "SDL_main",
	  "SDL_image"
   }

   location (LocationDir)
   targetdir (EXEDir)
   objdir (ObjectDir)

   filter "system:windows"
       systemversion "latest"
       defines { "_WINDOWS" }

   filter "configurations:Debug"
       defines { "_DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "_RELEASE","NDEBUG" }
       runtime "Release"
       optimize "Speed"
       symbols "On"

   filter "configurations:Dist"
       defines { "_DIST","NDEBUG" }
       runtime "Release"
       optimize "On"
       symbols "Off"

project "showanim"
	   kind "ConsoleApp"
	   language "C++"
	   cppdialect "C++20"
	   staticruntime "off"
	
	   files { "SDL_image/examples/showanim.c"}
	
	   includedirs
	   {
		  "%{DepIncludeDir.SDL}",
		  "SDL_image/include"
	   }
	
	   links
	   {
		  "SDL",
		  "SDL_main",
		  "SDL_image"
	   }
	
	   location (LocationDir)
	   targetdir (EXEDir)
	   objdir (ObjectDir)
	
	   filter "system:windows"
		   systemversion "latest"
		   defines { "_WINDOWS" }
	
	   filter "configurations:Debug"
		   defines { "_DEBUG" }
		   runtime "Debug"
		   symbols "On"
	
	   filter "configurations:Release"
		   defines { "_RELEASE","NDEBUG" }
		   runtime "Release"
		   optimize "Speed"
		   symbols "On"
	
	   filter "configurations:Dist"
		   defines { "DIST","NDEBUG" }
		   runtime "Release"
		   optimize "On"
		   symbols "Off"