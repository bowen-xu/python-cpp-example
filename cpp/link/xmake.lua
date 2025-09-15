add_rules("mode.debug", "mode.release", "mode.releasedbg")
set_languages("cxx20")

local module_dir = path.join(project_root, "graphx")
local py_root = project_root

add_requires("pybind11")
add_requires("fmt")

link_includes = {
    path.join(os.scriptdir(), "."),
    project_dir
}

link_srcs = table.join(
    os.files("./*.cpp")
)

target("link")
    add_defines("PYMODULE")
    add_rules("python.library", {soabi = true})
    add_packages("pybind11")

    add_files(link_srcs)
    add_includedirs(link_includes)

    set_targetdir(module_dir)

    after_build(function (target)
        cprint("${blue}Generate stub for " .. target:name() .. "...")
        local py = os.getenv("CONDA_PREFIX") and (os.getenv("CONDA_PREFIX") .. "/bin/python") or "python"
        cprint("${yellow}Using python: " .. py)
        os.exec(py .. " " .. py_root .. "/_generate_stub.py " .. " --root " .. module_dir .. " -p " .. target:name() .. " --single True" .. " --eval \"import node\"")
    end)

