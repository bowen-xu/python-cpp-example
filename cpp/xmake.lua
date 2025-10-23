add_rules("mode.debug", "mode.release", "mode.releasedbg")
set_languages("cxx20")

includes(
    "./node",
    "./link"
)
project_dir = path.join(os.scriptdir(), ".")
project_root = path.join(os.scriptdir(), "..")
local module_dir = path.join(project_root, "graphx/__internal__")
local link_module_dir = path.join(project_root, "graphx")
local node_module_dir = path.join(project_root, "graphx")
local py_root = project_root

add_requires("pybind11")

graphx_includes = {
    path.join(os.scriptdir(), "."),
}

graphx_srcs = table.join(
    os.files("./*.cpp")
)

target("graphx")
    add_defines("PYMODULE")
    add_rules("python.library", {soabi = true})
    add_packages("pybind11")

    add_deps("link", "node", {public = true, inherit = false}) -- add{inherit = false} to avoid automatic .so linking on Linux.

    add_files(graphx_srcs)
    add_includedirs(
        graphx_includes
    )

    set_targetdir(module_dir)

    after_build(function (target)
        local py = os.getenv("CONDA_PREFIX") and (os.getenv("CONDA_PREFIX") .. "/bin/python") or "python"

        cprint("${blue}Generate stub for " .. "node" .. "...")
        os.exec(py .. " " .. py_root .. "/_generate_stub.py " .. " --root " .. node_module_dir .. " -p " .. "node" .. " --single True" .. " --eval \"import link\"")

        cprint("${blue}Generate stub for " .. "link" .. "...")
        os.exec(py .. " " .. py_root .. "/_generate_stub.py " .. " --root " .. link_module_dir .. " -p " .. "link" .. " --single True" .. " --eval \"import node\"")

        cprint("${blue}Generate stub for " .. target:name() .. "...")
        os.exec(py .. " " .. py_root .. "/_generate_stub.py " .. " --root " .. module_dir .. " -p " .. target:name() .. " --single True" .. " --eval \"import sys; sys.path.insert(0, '" .. module_dir .. "/..'); import link; import node\"")
    end)
