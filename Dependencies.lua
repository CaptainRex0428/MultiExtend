DepIncludeDir={}
DepIncludeDir["SDL"] = "%{wks.location}/Dependencies/SDL/include"
DepIncludeDir["SDL_image"] = "%{wks.location}/Dependencies/SDL_image/include"

DepIncludeDir["glad"] = "%{wks.location}/Dependencies/glad/include"
DepIncludeDir["glfw"] = "%{wks.location}/Dependencies/glfw/include"
DepIncludeDir["glew"] = "%{wks.location}/Dependencies/glew/include/GL"
DepIncludeDir["imgui"] = "%{wks.location}/Dependencies/imgui"

DepIncludeDir["zlib"] = "%{wks.location}/Dependencies/zlib"
DepIncludeDir["libpng"] = "%{wks.location}/Dependencies/libpng"

DepIncludeDir["dlg"] = "%{wks.location}/Dependencies/dlg/include"
DepIncludeDir["freetype"] = "%{wks.location}/Dependencies/freetype/include"
DepIncludeDir["harfbuzz"] = "%{wks.location}/Dependencies/harfbuzz/src"
DepIncludeDir["SDL_ttf"] = "%{wks.location}/Dependencies/SDL_ttf"

DepIncludeDir["spdlog"] = "%{wks.location}/Dependencies/spdlog/include"

DepIncludeDir["linmath"] = "%{wks.location}/Dependencies/linmath"

ProjIncludeDir={}

ProjIncludeDir["ScrewExtend"] = "%{wks.location}/Extend/ScrewExtend/include"

LibDirectories = {}
LibDirectories["SDL_ttf"] =  LibDir.."/SDL_ttf"
LibDirectories["glfw"] =  LibDir.."/glfw"
LibDirectories["glad"] =  LibDir.."/glad"
LibDirectories["glew"] =  LibDir.."/glew"

Library = {}