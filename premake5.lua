-- premake5.lua

workspace "PiByte"
	architecture "x64"
	configurations {"Debug", "Release"}
	startproject "PiByteCLI"

outputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"

project "PiByte"
	location "PiByte"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		-- Future includes here
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PB_PLATFORM_WINDOWS",
			"PIBYTE_EXPORTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/PiByteCLI")
		}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		symbols "Off"


project "PiByteCLI"
	location "PiByteCLI"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	targetdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PiByte/src/"
	}

	links 
	{
		"PiByte"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		symbols "Off"
