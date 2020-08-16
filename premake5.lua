workspace "Mario-Clone"

    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

    filter "system:windows"
        startproject "Mario-Clone"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Mario-Clone/vendor/glfw/include"
IncludeDir["Glad"] = "Mario-Clone/vendor/glad/include"
IncludeDir["glm"] = "Mario-Clone/vendor/glm"
IncludeDir["stb_image"] = "Mario-Clone/vendor/stb/include"

group "Dependencies"
    include "Mario-Clone/vendor/glfw"
    include "Mario-Clone/vendor/glad"
group ""

project "Mario-Clone"
    location "Mario-Clone"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb/include/**.h",
		"%{prj.name}/vendor/stb/include/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GE_BUILD_DLL",
            "GE_PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/Resources")
        }

        links
        {
            "GLFW",
            "Glad",
            "opengl32.lib"
        }

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        links
        {
            "GLFW",
            "Glad",
            "GL",
            "X11",
            "pthread",
            "Xrandr",
            "Xi",
            "dl"
        }
        
        postbuildcommands
        {
            ("{COPY} ./Resources  ../bin/" .. outputdir .. "/%{prj.name}/Resources")
        }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        symbols "On"
      
    filter "configurations:Release"
        defines "GE_RELEASE"
        optimize "On"
      
    filter "configurations:Dist"
        defines "GE_DIST"
        optimize "On"

