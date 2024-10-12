-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/commonlibf4")

-- set project
set_project("f4se-custom-camera")
set_version("0.5.2")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")
set_defaultmode("releasedbg")

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- set policies
set_policy("package.requires_lock", true)

-- require packages
add_requires("simpleini")

-- targets
target("f4se-custom-camera")
    -- add dependencies to target
    add_deps("commonlibf4")

    -- add packages to target
    add_packages("simpleini")

    -- add commonlibsse plugin
    add_rules("commonlibf4.plugin", {
        name = "custom-camera",
        author = "qudix",
        description = "F4SE plugin template using CommonLibF4"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")

    -- add install files
    add_installfiles("res/(**)")
