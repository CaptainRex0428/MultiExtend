project "harfbuzz"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    files
    {
        "harfbuzz/src/graph/gsubgpos-context.cc",        "harfbuzz/src/hb-aat-layout.cc",
        "harfbuzz/src/hb-aat-map.cc",                    "harfbuzz/src/hb-blob.cc",
        "harfbuzz/src/hb-buffer-serialize.cc",           "harfbuzz/src/hb-buffer-verify.cc",
        "harfbuzz/src/hb-buffer.cc",                     "harfbuzz/src/hb-cairo-utils.cc",
        "harfbuzz/src/hb-cairo.cc",                      "harfbuzz/src/hb-common.cc",
        "harfbuzz/src/hb-coretext.cc",                   "harfbuzz/src/hb-directwrite.cc",
        "harfbuzz/src/hb-draw.cc",                       "harfbuzz/src/hb-face-builder.cc",
        "harfbuzz/src/hb-face.cc",                       "harfbuzz/src/hb-fallback-shape.cc",
        "harfbuzz/src/hb-font.cc",                       "harfbuzz/src/hb-ft.cc",
        "harfbuzz/src/hb-gdi.cc",                        "harfbuzz/src/hb-glib.cc",
        "harfbuzz/src/hb-gobject-structs.cc",            "harfbuzz/src/hb-graphite2.cc",
        "harfbuzz/src/hb-icu.cc",                        "harfbuzz/src/hb-map.cc",
        "harfbuzz/src/hb-number.cc",                     "harfbuzz/src/hb-ot-cff1-table.cc",
        "harfbuzz/src/hb-ot-cff2-table.cc",              "harfbuzz/src/hb-ot-color.cc",
        "harfbuzz/src/hb-ot-face.cc",                    "harfbuzz/src/hb-ot-font.cc",
        "harfbuzz/src/hb-ot-layout.cc",                  "harfbuzz/src/hb-ot-map.cc",
        "harfbuzz/src/hb-ot-math.cc",                    "harfbuzz/src/hb-ot-meta.cc",
        "harfbuzz/src/hb-ot-metrics.cc",                 "harfbuzz/src/hb-ot-name.cc",
        "harfbuzz/src/hb-ot-shape-fallback.cc",          "harfbuzz/src/hb-ot-shape-normalize.cc",
        "harfbuzz/src/hb-ot-shape.cc",                   "harfbuzz/src/hb-ot-shaper-arabic.cc",
        "harfbuzz/src/hb-ot-shaper-default.cc",          "harfbuzz/src/hb-ot-shaper-hangul.cc",
        "harfbuzz/src/hb-ot-shaper-hebrew.cc",           "harfbuzz/src/hb-ot-shaper-indic-table.cc",
        "harfbuzz/src/hb-ot-shaper-indic.cc",            "harfbuzz/src/hb-ot-shaper-khmer.cc",
        "harfbuzz/src/hb-ot-shaper-myanmar.cc",          "harfbuzz/src/hb-ot-shaper-syllabic.cc",
        "harfbuzz/src/hb-ot-shaper-thai.cc",             "harfbuzz/src/hb-ot-shaper-use.cc",
        "harfbuzz/src/hb-ot-shaper-vowel-constraints.cc","harfbuzz/src/hb-ot-tag.cc",
        "harfbuzz/src/hb-ot-var.cc",                     "harfbuzz/src/hb-outline.cc",
        "harfbuzz/src/hb-paint-extents.cc",              "harfbuzz/src/hb-paint.cc",
        "harfbuzz/src/hb-set.cc",                        "harfbuzz/src/hb-shape-plan.cc",
        "harfbuzz/src/hb-shape.cc",                      "harfbuzz/src/hb-shaper.cc",
        "harfbuzz/src/hb-static.cc",                     "harfbuzz/src/hb-style.cc",
        "harfbuzz/src/hb-subset-cff-common.cc",          "harfbuzz/src/hb-subset-cff1.cc",
        "harfbuzz/src/hb-subset-cff2.cc",                "harfbuzz/src/hb-subset-input.cc",
        "harfbuzz/src/hb-subset-instancer-solver.cc",    "harfbuzz/src/hb-subset-plan.cc",
        "harfbuzz/src/hb-subset-repacker.cc",            "harfbuzz/src/hb-subset.cc",
        "harfbuzz/src/hb-ucd.cc",                        "harfbuzz/src/hb-unicode.cc",
        "harfbuzz/src/hb-uniscribe.cc",                  "harfbuzz/src/hb-wasm-api.cc",
        "harfbuzz/src/hb-wasm-shape.cc"
    }

    includedirs
    {
        "harfbuzz/src",
        "%{DepIncludeDir.freetype}"
    }

    links
    {
        "freetype"
    }

    defines
	{
        "_CRT_SECURE_NO_WARNINGS",
        "TTF_USE_HARFBUZZ=1",
        "FT_CONFIG_OPTION_USE_HARFBUZZ",
        "HAVE_FREETYPE"
	}

    flags
    {
        -- "NoRuntimeChecks", -- Only used on Visual Studio.
		-- "NoBufferSecurityCheck"
    }

    -- vectorextensions  "SSE"               -- Necessary to run x32.

    buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/bigobj" }

    warnings "off"

    location (LocationDir)
    targetdir (TargetDir)
    objdir (ObjectDir)

    -- inlining    "Explicit"
	-- intrinsics  "Off"

    filter "system:windows" 
        -- staticruntime "Off"
        systemversion "latest"
        defines { "_WINDOWS"}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "On"
        defines { "RELEASE","NDEBUG" }

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"
        symbols "Off"
        defines { "DIST","NDEBUG" }