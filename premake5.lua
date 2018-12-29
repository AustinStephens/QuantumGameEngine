workspace "QuantumEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "QuantumEngine/vendor/GLFW/include"

include "QuantumEngine/vendor/GLFW"

project "QuantumEngine"
	location "QuantumEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "qtpch.h"
	pchsource "QuantumEngine/src/qtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS",
			"QT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "QT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QT_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"QuantumEngine/vendor/spdlog/include",
		"QuantumEngine/src"
	}

	links
	{
		"QuantumEngine"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "QT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QT_DIST"
		optimize "On"