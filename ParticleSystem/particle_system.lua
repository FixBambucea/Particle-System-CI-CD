project "ParticleSystem"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "**.h",
        "**.cpp",
        "**.hpp",
        "**.vert", 
        "**.frag"
    }

    includedirs
    {
        "%{IncludeDir.glfw}",
        "%{IncludeDir.VulkanSDK}",
        "%{IncludeDir.glm}"
    }

    libdirs
    {
        "%{LibraryDir.VulkanSDK}"
    }

    links
    {
        "glfw",
        Library[os.target()]["Vulkan"]
    }

    -- TODO: only the files existing at the time of executing this script will be considered
    --       any new addition will be ignored, so you have to run again generate_project script

    -- prebuild command to automatically compile .vert and .frag files for Windows
    filter { "files:**.vert or **.frag", "system:windows" }
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %{file.name}'

        -- One or more commands to run (required)
        buildcommands 
        {
            '"%{wks.location}/vendor/VulkanSDK/glslc.exe" "%{file.relpath}" -o "%{cfg.targetdir}/shaders/%{file.name}.spv"',
            '"%{wks.location}/vendor/VulkanSDK/glslc.exe" "%{file.relpath}" -o "%{file.directory}/%{file.name}.spv"'
        }

        -- One or more outputs resulting from the build (required)
        buildoutputs
        { 
            '%{cfg.targetdir}/shaders/%{file.name}.spv',
            '%{file.directory}/%{file.name}.spv'
        }

    -- prebuild command to automatically compile .vert and .frag files for Linux
    filter { "files:**.vert or **.frag", "system:linux" }
        -- A message to display while this build step is running (optional)
        buildmessage 'Compiling %{file.name}'

        -- One or more commands to run (required)
        buildcommands 
        {
            '"%{wks.location}/vendor/VulkanSDK/glslc" "%{file.relpath}" -o "%{cfg.targetdir}/shaders/%{file.name}.spv"',
            '"%{wks.location}/vendor/VulkanSDK/glslc" "%{file.relpath}" -o "%{file.directory}/%{file.name}.spv"'
        }

        -- One or more outputs resulting from the build (required)
        buildoutputs
        { 
            '%{cfg.targetdir}/shaders/%{file.name}.spv',
            '%{file.directory}/%{file.name}.spv'
        }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

    filter "system:linux"
        prebuildcommands
        {
            '[ -d "%{cfg.targetdir}/shaders" ] || mkdir -p "%{cfg.targetdir}/shaders"'
        }

    filter "configurations:Debug"
        symbols "On"

        defines
        {
            "DEBUG"
        }

    filter "configurations:Release"
        optimize "On"

        defines
        {
            "NDEBUG"
        }
