project "SDL"
	language          "C++"           
	cppdialect        "C++20"                      
	
	files 
	{
		"SDL/include/begin_code.h",
		"SDL/include/close_code.h",
		"SDL/include/SDL.h",
		"SDL/include/SDL_assert.h",
		"SDL/include/SDL_atomic.h",
		"SDL/include/SDL_audio.h",
		"SDL/include/SDL_bits.h",
		"SDL/include/SDL_blendmode.h",
		"SDL/include/SDL_clipboard.h",
		"SDL/include/SDL_config.h",
		"SDL/include/SDL_config_windows.h",
		"SDL/include/SDL_copying.h",
		"SDL/include/SDL_cpuinfo.h",
		"SDL/include/SDL_egl.h",
		"SDL/include/SDL_endian.h",
		"SDL/include/SDL_error.h",
		"SDL/include/SDL_events.h",
		"SDL/include/SDL_filesystem.h",
		"SDL/include/SDL_gamecontroller.h",
		"SDL/include/SDL_gesture.h",
		"SDL/include/SDL_guid.h",
		"SDL/include/SDL_haptic.h",
		"SDL/include/SDL_hints.h",
		"SDL/include/SDL_hidapi.h",
		"SDL/include/SDL_joystick.h",
		"SDL/include/SDL_keyboard.h",
		"SDL/include/SDL_keycode.h",
		"SDL/include/SDL_loadso.h",
		"SDL/include/SDL_locale.h",
		"SDL/include/SDL_log.h",
		"SDL/include/SDL_main.h",
		"SDL/include/SDL_messagebox.h",
		"SDL/include/SDL_metal.h",
		"SDL/include/SDL_misc.h",
		"SDL/include/SDL_mouse.h",
		"SDL/include/SDL_mutex.h",
		"SDL/include/SDL_name.h",
		"SDL/include/SDL_opengl.h",
		"SDL/include/SDL_opengl_glext.h",
		"SDL/include/SDL_opengles.h",
		"SDL/include/SDL_opengles2.h",
		"SDL/include/SDL_opengles2_gl2.h",
		"SDL/include/SDL_opengles2_gl2ext.h",
		"SDL/include/SDL_opengles2_gl2platform.h",
		"SDL/include/SDL_opengles2_khrplatform.h",
		"SDL/include/SDL_pixels.h",
		"SDL/include/SDL_platform.h",
		"SDL/include/SDL_power.h",
		"SDL/include/SDL_quit.h",
		"SDL/include/SDL_rect.h",
		"SDL/include/SDL_render.h",
		"SDL/include/SDL_revision.h",
		"SDL/include/SDL_rwops.h",
		"SDL/include/SDL_scancode.h",
		"SDL/include/SDL_sensor.h",
		"SDL/include/SDL_shape.h",
		"SDL/include/SDL_stdinc.h",
		"SDL/include/SDL_surface.h",
		"SDL/include/SDL_system.h",
		"SDL/include/SDL_syswm.h",
		"SDL/include/SDL_test.h",
		"SDL/include/SDL_test_assert.h",
		"SDL/include/SDL_test_common.h",
		"SDL/include/SDL_test_compare.h",
		"SDL/include/SDL_test_crc32.h",
		"SDL/include/SDL_test_font.h",
		"SDL/include/SDL_test_fuzzer.h",
		"SDL/include/SDL_test_harness.h",
		"SDL/include/SDL_test_images.h",
		"SDL/include/SDL_test_log.h",
		"SDL/include/SDL_test_md5.h",
		"SDL/include/SDL_test_memory.h",
		"SDL/include/SDL_test_random.h",
		"SDL/include/SDL_thread.h",
		"SDL/include/SDL_timer.h",
		"SDL/include/SDL_touch.h",
		"SDL/include/SDL_types.h",
		"SDL/include/SDL_version.h",
		"SDL/include/SDL_video.h",
		"SDL/include/SDL_vulkan.h",
		"SDL/src/audio/directsound/SDL_directsound.h",
		"SDL/src/audio/disk/SDL_diskaudio.h",
		"SDL/src/audio/dummy/SDL_dummyaudio.h",
		"SDL/src/audio/SDL_audio_c.h",
		"SDL/src/audio/SDL_audiodev_c.h",
		"SDL/src/audio/SDL_sysaudio.h",
		"SDL/src/audio/SDL_wave.h",
		"SDL/src/audio/wasapi/SDL_wasapi.h",
		"SDL/src/audio/winmm/SDL_winmm.h",
		"SDL/src/core/windows/SDL_directx.h",
		"SDL/src/core/windows/SDL_hid.h",
		"SDL/src/core/windows/SDL_immdevice.h",
		"SDL/src/core/windows/SDL_windows.h",
		"SDL/src/core/windows/SDL_xinput.h",
		"SDL/src/dynapi/SDL_dynapi.h",
		"SDL/src/dynapi/SDL_dynapi_overrides.h",
		"SDL/src/dynapi/SDL_dynapi_procs.h",
		"SDL/src/events/blank_cursor.h",
		"SDL/src/events/default_cursor.h",
		"SDL/src/events/scancodes_windows.h",
		"SDL/src/events/SDL_clipboardevents_c.h",
		"SDL/src/events/SDL_displayevents_c.h",
		"SDL/src/events/SDL_dropevents_c.h",
		"SDL/src/events/SDL_events_c.h",
		"SDL/src/events/SDL_gesture_c.h",
		"SDL/src/events/SDL_keyboard_c.h",
		"SDL/src/events/SDL_mouse_c.h",
		"SDL/src/events/SDL_touch_c.h",
		"SDL/src/events/SDL_windowevents_c.h",
		"SDL/src/haptic/SDL_haptic_c.h",
		"SDL/src/haptic/SDL_syshaptic.h",
		"SDL/src/haptic/windows/SDL_dinputhaptic_c.h",
		"SDL/src/haptic/windows/SDL_windowshaptic_c.h",
		"SDL/src/haptic/windows/SDL_xinputhaptic_c.h",
		"SDL/src/hidapi/hidapi/hidapi.h",
		"SDL/src/hidapi/SDL_hidapi_c.h",
		"SDL/src/joystick/controller_type.h",
		"SDL/src/joystick/hidapi/SDL_hidapijoystick_c.h",
		"SDL/src/joystick/hidapi/SDL_hidapi_rumble.h",
		"SDL/src/joystick/SDL_gamecontrollerdb.h",
		"SDL/src/joystick/SDL_joystick_c.h",
		"SDL/src/joystick/SDL_steam_virtual_gamepad.h",
		"SDL/src/joystick/SDL_sysjoystick.h",
		"SDL/src/joystick/usb_ids.h",
		"SDL/src/joystick/virtual/SDL_virtualjoystick_c.h",
		"SDL/src/joystick/windows/SDL_dinputjoystick_c.h",
		"SDL/src/joystick/windows/SDL_rawinputjoystick_c.h",
		"SDL/src/joystick/windows/SDL_windowsjoystick_c.h",
		"SDL/src/joystick/windows/SDL_xinputjoystick_c.h",
		"SDL/src/libm/math_libm.h",
		"SDL/src/libm/math_private.h",
		"SDL/src/locale/SDL_syslocale.h",
		"SDL/src/misc/SDL_sysurl.h",
		"SDL/src/power/SDL_syspower.h",
		"SDL/src/render/direct3d11/SDL_shaders_d3d11.h",
		"SDL/src/render/direct3d12/SDL_shaders_d3d12.h",
		"SDL/src/render/direct3d/SDL_shaders_d3d.h",
		"SDL/src/render/opengles2/SDL_gles2funcs.h",
		"SDL/src/render/opengles2/SDL_shaders_gles2.h",
		"SDL/src/render/opengl/SDL_glfuncs.h",
		"SDL/src/render/opengl/SDL_shaders_gl.h",
		"SDL/src/render/SDL_d3dmath.h",
		"SDL/src/render/SDL_sysrender.h",
		"SDL/src/render/SDL_yuv_sw_c.h",
		"SDL/src/render/software/SDL_blendfillrect.h",
		"SDL/src/render/software/SDL_blendline.h",
		"SDL/src/render/software/SDL_blendpoint.h",
		"SDL/src/render/software/SDL_draw.h",
		"SDL/src/render/software/SDL_drawline.h",
		"SDL/src/render/software/SDL_drawpoint.h",
		"SDL/src/render/software/SDL_render_sw_c.h",
		"SDL/src/render/software/SDL_rotate.h",
		"SDL/src/render/software/SDL_triangle.h",
		"SDL/src/SDL_assert_c.h",
		"SDL/src/SDL_dataqueue.h",
		"SDL/src/SDL_error_c.h",
		"SDL/src/SDL_guid.c",
		"SDL/src/SDL_hints_c.h",
		"SDL/src/SDL_internal.h",
		"SDL/src/SDL_list.h",
		"SDL/src/SDL_log_c.h",
		"SDL/src/sensor/dummy/SDL_dummysensor.h",
		"SDL/src/sensor/SDL_sensor_c.h",
		"SDL/src/sensor/SDL_syssensor.h",
		"SDL/src/sensor/windows/SDL_windowssensor.h",
		"SDL/src/thread/SDL_systhread.h",
		"SDL/src/thread/SDL_thread_c.h",
		"SDL/src/thread/generic/SDL_syscond_c.h",
		"SDL/src/thread/windows/SDL_sysmutex_c.h",
		"SDL/src/thread/windows/SDL_systhread_c.h",
		"SDL/src/timer/SDL_timer_c.h",
		"SDL/src/video/dummy/SDL_nullevents_c.h",
		"SDL/src/video/dummy/SDL_nullframebuffer_c.h",
		"SDL/src/video/dummy/SDL_nullvideo.h",
		"SDL/src/video/khronos/vulkan/vk_icd.h",
		"SDL/src/video/khronos/vulkan/vk_layer.h",
		"SDL/src/video/khronos/vulkan/vk_platform.h",
		"SDL/src/video/khronos/vulkan/vk_sdk_platform.h",
		"SDL/src/video/khronos/vulkan/vulkan.h",
		"SDL/src/video/khronos/vulkan/vulkan_android.h",
		"SDL/src/video/khronos/vulkan/vulkan_beta.h",
		"SDL/src/video/khronos/vulkan/vulkan_core.h",
		"SDL/src/video/khronos/vulkan/vulkan_directfb.h",
		"SDL/src/video/khronos/vulkan/vulkan_fuchsia.h",
		"SDL/src/video/khronos/vulkan/vulkan_ggp.h",
		"SDL/src/video/khronos/vulkan/vulkan_ios.h",
		"SDL/src/video/khronos/vulkan/vulkan_macos.h",
		"SDL/src/video/khronos/vulkan/vulkan_metal.h",
		"SDL/src/video/khronos/vulkan/vulkan_vi.h",
		"SDL/src/video/khronos/vulkan/vulkan_wayland.h",
		"SDL/src/video/khronos/vulkan/vulkan_win32.h",
		"SDL/src/video/khronos/vulkan/vulkan_xcb.h",
		"SDL/src/video/khronos/vulkan/vulkan_xlib.h",
		"SDL/src/video/khronos/vulkan/vulkan_xlib_xrandr.h",
		"SDL/src/video/SDL_blit.h",
		"SDL/src/video/SDL_blit_auto.h",
		"SDL/src/video/SDL_blit_copy.h",
		"SDL/src/video/SDL_blit_slow.h",
		"SDL/src/video/SDL_egl_c.h",
		"SDL/src/video/SDL_pixels_c.h",
		"SDL/src/video/SDL_rect_c.h",
		"SDL/src/video/SDL_RLEaccel_c.h",
		"SDL/src/video/SDL_shape_internals.h",
		"SDL/src/video/SDL_sysvideo.h",
		"SDL/src/video/SDL_vulkan_internal.h",
		"SDL/src/video/SDL_yuv_c.h",
		"SDL/src/video/windows/SDL_msctf.h",
		"SDL/src/video/windows/SDL_vkeys.h",
		"SDL/src/video/windows/SDL_windowsclipboard.h",
		"SDL/src/video/windows/SDL_windowsevents.h",
		"SDL/src/video/windows/SDL_windowsframebuffer.h",
		"SDL/src/video/windows/SDL_windowskeyboard.h",
		"SDL/src/video/windows/SDL_windowsmessagebox.h",
		"SDL/src/video/windows/SDL_windowsmodes.h",
		"SDL/src/video/windows/SDL_windowsmouse.h",
		"SDL/src/video/windows/SDL_windowsopengl.h",
		"SDL/src/video/windows/SDL_windowsopengles.h",
		"SDL/src/video/windows/SDL_windowsshape.h",
		"SDL/src/video/windows/SDL_windowsvideo.h",
		"SDL/src/video/windows/SDL_windowsvulkan.h",
		"SDL/src/video/windows/SDL_windowswindow.h",
		"SDL/src/video/windows/wmmsg.h",
		"SDL/src/video/yuv2rgb/yuv_rgb.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_common.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_internal.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_lsx.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_lsx_func.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_sse.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_sse_func.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_std.h",
		"SDL/src/video/yuv2rgb/yuv_rgb_std_func.h",

		"SDL/src/atomic/SDL_atomic.c",
		"SDL/src/atomic/SDL_spinlock.c",
		"SDL/src/audio/directsound/SDL_directsound.c",
		"SDL/src/audio/disk/SDL_diskaudio.c",
		"SDL/src/audio/dummy/SDL_dummyaudio.c",
		"SDL/src/audio/SDL_audio.c",
		"SDL/src/audio/SDL_audiocvt.c",
		"SDL/src/audio/SDL_audiodev.c",
		"SDL/src/audio/SDL_audiotypecvt.c",
		"SDL/src/audio/SDL_mixer.c",
		"SDL/src/audio/SDL_wave.c",
		"SDL/src/audio/winmm/SDL_winmm.c",
		"SDL/src/audio/wasapi/SDL_wasapi.c",
		"SDL/src/audio/wasapi/SDL_wasapi_win32.c",
		"SDL/src/core/windows/SDL_hid.c",
		"SDL/src/core/windows/SDL_immdevice.c",
		"SDL/src/core/windows/SDL_windows.c",
		"SDL/src/core/windows/SDL_xinput.c",
		"SDL/src/cpuinfo/SDL_cpuinfo.c",
		"SDL/src/dynapi/SDL_dynapi.c",
		"SDL/src/events/SDL_clipboardevents.c",
		"SDL/src/events/SDL_displayevents.c",
		"SDL/src/events/SDL_dropevents.c",
		"SDL/src/events/SDL_events.c",
		"SDL/src/events/SDL_gesture.c",
		"SDL/src/events/SDL_keyboard.c",
		"SDL/src/events/SDL_mouse.c",
		"SDL/src/events/SDL_quit.c",
		"SDL/src/events/SDL_touch.c",
		"SDL/src/events/SDL_windowevents.c",
		"SDL/src/file/SDL_rwops.c",
		"SDL/src/filesystem/windows/SDL_sysfilesystem.c",
		"SDL/src/haptic/dummy/SDL_syshaptic.c",
		"SDL/src/haptic/SDL_haptic.c",
		"SDL/src/haptic/windows/SDL_dinputhaptic.c",
		"SDL/src/haptic/windows/SDL_windowshaptic.c",
		"SDL/src/haptic/windows/SDL_xinputhaptic.c",
		"SDL/src/hidapi/SDL_hidapi.c",
		"SDL/src/joystick/controller_type.c",
		"SDL/src/joystick/dummy/SDL_sysjoystick.c",
		"SDL/src/joystick/hidapi/SDL_hidapijoystick.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_combined.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_gamecube.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_luna.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_ps3.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_ps4.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_ps5.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_rumble.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_shield.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_stadia.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_steam.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_steamdeck.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_switch.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_wii.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_xbox360.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_xbox360w.c",
		"SDL/src/joystick/hidapi/SDL_hidapi_xboxone.c",
		"SDL/src/joystick/SDL_gamecontroller.c",
		"SDL/src/joystick/SDL_joystick.c",
		"SDL/src/joystick/SDL_steam_virtual_gamepad.c",
		"SDL/src/joystick/virtual/SDL_virtualjoystick.c",
		"SDL/src/joystick/windows/SDL_dinputjoystick.c",
		"SDL/src/joystick/windows/SDL_rawinputjoystick.c",
		"SDL/src/joystick/windows/SDL_windowsjoystick.c",
		"SDL/src/joystick/windows/SDL_windows_gaming_input.c",
		"SDL/src/joystick/windows/SDL_xinputjoystick.c",
		"SDL/src/libm/e_atan2.c",
		"SDL/src/libm/e_exp.c",
		"SDL/src/libm/e_fmod.c",
		"SDL/src/libm/e_log.c",
		"SDL/src/libm/e_log10.c",
		"SDL/src/libm/e_pow.c",
		"SDL/src/libm/e_rem_pio2.c",
		"SDL/src/libm/e_sqrt.c",
		"SDL/src/libm/k_cos.c",
		"SDL/src/libm/k_rem_pio2.c",
		"SDL/src/libm/k_sin.c",
		"SDL/src/libm/k_tan.c",
		"SDL/src/libm/s_atan.c",
		"SDL/src/libm/s_copysign.c",
		"SDL/src/libm/s_cos.c",
		"SDL/src/libm/s_fabs.c",
		"SDL/src/libm/s_floor.c",
		"SDL/src/libm/s_scalbn.c",
		"SDL/src/libm/s_sin.c",
		"SDL/src/libm/s_tan.c",
		"SDL/src/loadso/windows/SDL_sysloadso.c",
		"SDL/src/locale/SDL_locale.c",
		"SDL/src/locale/windows/SDL_syslocale.c",
		"SDL/src/misc/SDL_url.c",
		"SDL/src/misc/windows/SDL_sysurl.c",
		"SDL/src/power/SDL_power.c",
		"SDL/src/power/windows/SDL_syspower.c",
		"SDL/src/render/direct3d11/SDL_shaders_d3d11.c",
		"SDL/src/render/direct3d12/SDL_render_d3d12.c",
		"SDL/src/render/direct3d12/SDL_shaders_d3d12.c",
		"SDL/src/render/direct3d/SDL_render_d3d.c",
		"SDL/src/render/direct3d11/SDL_render_d3d11.c",
		"SDL/src/render/direct3d/SDL_shaders_d3d.c",
		"SDL/src/render/opengl/SDL_render_gl.c",
		"SDL/src/render/opengl/SDL_shaders_gl.c",
		"SDL/src/render/opengles2/SDL_render_gles2.c",
		"SDL/src/render/opengles2/SDL_shaders_gles2.c",
		"SDL/src/render/SDL_d3dmath.c",
		"SDL/src/render/SDL_render.c",
		"SDL/src/render/SDL_yuv_sw.c",
		"SDL/src/render/software/SDL_blendfillrect.c",
		"SDL/src/render/software/SDL_blendline.c",
		"SDL/src/render/software/SDL_blendpoint.c",
		"SDL/src/render/software/SDL_drawline.c",
		"SDL/src/render/software/SDL_drawpoint.c",
		"SDL/src/render/software/SDL_render_sw.c",
		"SDL/src/render/software/SDL_rotate.c",
		"SDL/src/render/software/SDL_triangle.c",
		"SDL/src/SDL.c",
		"SDL/src/SDL_assert.c",
		"SDL/src/SDL_dataqueue.c",
		"SDL/src/SDL_list.c",
		"SDL/src/SDL_error.c",
		"SDL/src/SDL_hints.c",
		"SDL/src/SDL_log.c",
		"SDL/src/SDL_utils.c",
		"SDL/src/sensor/dummy/SDL_dummysensor.c",
		"SDL/src/sensor/SDL_sensor.c",
		"SDL/src/sensor/windows/SDL_windowssensor.c",
		"SDL/src/stdlib/SDL_crc16.c",
		"SDL/src/stdlib/SDL_crc32.c",
		"SDL/src/stdlib/SDL_getenv.c",
		"SDL/src/stdlib/SDL_iconv.c",
		"SDL/src/stdlib/SDL_malloc.c",
		"SDL/src/stdlib/SDL_mslibc.c",
		"SDL/src/stdlib/SDL_qsort.c",
		"SDL/src/stdlib/SDL_stdlib.c",
		"SDL/src/stdlib/SDL_string.c",
		"SDL/src/stdlib/SDL_strtokr.c",
		"SDL/src/thread/generic/SDL_syscond.c",
		"SDL/src/thread/SDL_thread.c",
		"SDL/src/thread/windows/SDL_syscond_cv.c",
		"SDL/src/thread/windows/SDL_sysmutex.c",
		"SDL/src/thread/windows/SDL_syssem.c",
		"SDL/src/thread/windows/SDL_systhread.c",
		"SDL/src/thread/windows/SDL_systls.c",
		"SDL/src/timer/SDL_timer.c",
		"SDL/src/timer/windows/SDL_systimer.c",
		"SDL/src/video/dummy/SDL_nullevents.c",
		"SDL/src/video/dummy/SDL_nullframebuffer.c",
		"SDL/src/video/dummy/SDL_nullvideo.c",
		"SDL/src/video/SDL_blit.c",
		"SDL/src/video/SDL_blit_0.c",
		"SDL/src/video/SDL_blit_1.c",
		"SDL/src/video/SDL_blit_A.c",
		"SDL/src/video/SDL_blit_auto.c",
		"SDL/src/video/SDL_blit_copy.c",
		"SDL/src/video/SDL_blit_N.c",
		"SDL/src/video/SDL_blit_slow.c",
		"SDL/src/video/SDL_bmp.c",
		"SDL/src/video/SDL_clipboard.c",
		"SDL/src/video/SDL_egl.c",
		"SDL/src/video/SDL_fillrect.c",
		"SDL/src/video/SDL_pixels.c",
		"SDL/src/video/SDL_rect.c",
		"SDL/src/video/SDL_RLEaccel.c",
		"SDL/src/video/SDL_shape.c",
		"SDL/src/video/SDL_stretch.c",
		"SDL/src/video/SDL_surface.c",
		"SDL/src/video/SDL_video.c",
		"SDL/src/video/SDL_vulkan_utils.c",
		"SDL/src/video/SDL_yuv.c",
		"SDL/src/video/windows/SDL_windowsclipboard.c",
		"SDL/src/video/windows/SDL_windowsevents.c",
		"SDL/src/video/windows/SDL_windowsframebuffer.c",
		"SDL/src/video/windows/SDL_windowskeyboard.c",
		"SDL/src/video/windows/SDL_windowsmessagebox.c",
		"SDL/src/video/windows/SDL_windowsmodes.c",
		"SDL/src/video/windows/SDL_windowsmouse.c",
		"SDL/src/video/windows/SDL_windowsopengl.c",
		"SDL/src/video/windows/SDL_windowsopengles.c",
		"SDL/src/video/windows/SDL_windowsshape.c",
		"SDL/src/video/windows/SDL_windowsvideo.c",
		"SDL/src/video/windows/SDL_windowsvulkan.c",
		"SDL/src/video/windows/SDL_windowswindow.c",
		"SDL/src/video/yuv2rgb/yuv_rgb_lsx.c",
		"SDL/src/video/yuv2rgb/yuv_rgb_sse.c",
		"SDL/src/video/yuv2rgb/yuv_rgb_std.c"
	}

	includedirs
	{
		"SDL/include"
	}

	links 
	{
		"setupapi.lib",
		"winmm.lib",
		"imm32.lib",
		"version.lib",
		"vcruntimed.lib",
		"ucrtd.lib"
	}

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} "..DynamicDir)
	}

	filter "system:windows"
		kind          "SharedLib"
		-- staticruntime "Off"
		systemversion "latest"

		defines 
		{
			"_WINDOWS","DLL_EXPORT"
		}

	filter "configurations:Debug"
		defines 
		{
			"_DEBUG"
		}
		runtime       "Debug"
		symbols       "On"

	filter "configurations:Release"
		defines 
		{
			"NDEBUG"
		}
		runtime       "Release"
		optimize      "Speed"


	filter "configurations:Dist"
		defines 
		{
			"NDEBUG"             
		}
		runtime       "Release"
		optimize      "On"


project "SDL_main"
	kind          "StaticLib"
	language      "C"
	
	systemversion "latest"

	flags 
	{
		"NoRuntimeChecks",
		"NoBufferSecurityCheck"
	}

	vectorextensions "SSE"

	location (LocationDir)
	targetdir (TargetDir)
	objdir (ObjectDir)

	files
	{
		"SDL/src/main/windows/*.c"
	}	

	includedirs
	{
		"SDL/include"
	}

	links
	{
	}

	defines {
		"_WINDOWS",
		"WIN32"
	}

	filter "configurations:Debug"
		defines 
		{
			"DEBUG"
		}
		runtime      "Debug"
		symbols      "On"

	filter "configurations:Release"
		defines 
		{
			"NDEBUG"
		}
		runtime      "Release"
		optimize     "Speed"


	filter "configurations:Dist"
		defines 
		{                           
			"NDEBUG"
		}
		runtime      "Release"
		optimize     "On"