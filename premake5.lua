-- premake5.lua

workspace "PiByte"
	architecture "x64"
	configurations {"Debug", "Release"}
	startproject "PiByteCLI"
	--startproject "PiByte"

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
		"%{prj.name}/vendor/spdlog/include"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		runtime "Debug"
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
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PiByte/src/",
		"PiByte/vendor/spdlog/include"
	}

	links 
	{
		"PiByte"
	}

	defines
	{
		"PB_PLATFORM_WINDOWS"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		runtime "Debug"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		symbols "Off"
