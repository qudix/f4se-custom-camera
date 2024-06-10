-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/commonlibf4")

-- set project
set_project("f4se-custom-camera")
set_version("0.5.0")
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

    -- copy build files to MODS or GAME paths (remove this if not needed)
    after_build(function(target)
        local copy = function(env, ext)
            for _, env in pairs(env:split(";")) do
                if os.exists(env) then
                    local plugins = path.join(env, ext, "F4SE/Plugins")
                    os.mkdir(plugins)
                    os.trycp(target:targetfile(), plugins)
                    os.trycp(target:symbolfile(), plugins)
                end
            end
        end
        if os.getenv("XSE_FO4_MODS_PATH") then
            copy(os.getenv("XSE_FO4_MODS_PATH"), target:name())
        elseif os.getenv("XSE_FO4_GAME_PATH") then
            copy(os.getenv("XSE_FO4_GAME_PATH"), "Data")
        end
    end)
