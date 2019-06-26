workspace "QuantumEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "QuantumEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "QuantumEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "QuantumEngine/vendor/imgui"

include "QuantumEngine/vendor/GLFW"
include "QuantumEngine/vendor/GLAD"
include "QuantumEngine/vendor/imgui"

project "QuantumEngine"
	location "QuantumEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "qtpch.h"
	pchsource "QuantumEngine/src/qtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS",
			"QT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		defines "QT_RELEASE"
		buildoptions "/MT"
		optimize "on"

	filter "configurations:Dist"
		defines "QT_DIST"
		buildoptions "/MT"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

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
		"QuantumEngine/src",
		"QuantumEngine/vendor"
	}

	links
	{
		"QuantumEngine"
	}

	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QT_DIST"
		runtime "Release"
		optimize "on"