project "glfw"
	kind "SharedLib"
	language "C"
	cdialect "C11"  -- 使用 C11 标准

	files
	{
		"glfw/include/GLFW/glfw3.h",
    	"glfw/include/GLFW/glfw3native.h",
    	"glfw/src/internal.h",
    	"glfw/src/platform.h",
    	"glfw/src/mappings.h",
    	"glfw/src/context.c",
    	"glfw/src/init.c",
    	"glfw/src/input.c",
    	"glfw/src/monitor.c",
    	"glfw/src/platform.c",
    	"glfw/src/vulkan.c",
    	"glfw/src/window.c",
    	"glfw/src/egl_context.c",
    	"glfw/src/osmesa_context.c",
    	"glfw/src/null_platform.h",
    	"glfw/src/null_joystick.h",
    	"glfw/src/null_init.c",

    	"glfw/src/null_monitor.c",
    	"glfw/src/null_window.c",
    	"glfw/src/null_joystick.c",
	}

	defines 
	{ 
		"_GLFW_BUILD_DLL"
	}

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} "..DynamicDir)
	}

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"glfw/src/x11_init.c",
			"glfw/src/x11_monitor.c",
			"glfw/src/x11_window.c",
			"glfw/src/xkb_unicode.c",
			"glfw/src/posix_time.c",
			"glfw/src/posix_thread.c",
			"glfw/src/glx_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c",
			"glfw/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"glfw/src/win32_init.c",
	        "glfw/src/win32_module.c",
	        "glfw/src/win32_joystick.c",
	        "glfw/src/win32_monitor.c",
	        "glfw/src/win32_time.h",
	        "glfw/src/win32_time.c",
	        "glfw/src/win32_thread.h",
	        "glfw/src/win32_thread.c",
	        "glfw/src/win32_window.c",
	        "glfw/src/wgl_context.c",
	        "glfw/src/egl_context.c",
	        "glfw/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

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