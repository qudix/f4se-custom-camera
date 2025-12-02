set_xmakever("2.8.2")

includes("lib/commonlibf4")

set_project("f4se-custom-camera")
set_version("0.5.4")
set_license("GPL-3.0")

set_languages("c++23")
set_warnings("allextra")
set_defaultmode("releasedbg")

set_policy("package.requires_lock", true)

add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

add_requires("simpleini")

target("f4se-custom-camera")
    add_deps("commonlibf4")

    add_packages("simpleini")

    add_rules("commonlibf4.plugin", {
        name = "custom-camera",
        author = "qudix",
        description = "Customize the in-game camera"
    })

    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")

    add_installfiles("res/(**)")
