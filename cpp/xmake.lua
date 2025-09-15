add_rules("mode.debug", "mode.release", "mode.releasedbg")
set_languages("cxx20")

includes(
    "./node",
    "./link"
)
project_dir = path.join(os.scriptdir(), ".")
project_root = path.join(os.scriptdir(), "..")
local module_dir = path.join(project_root, "graphx")
local py_root = project_root
mind_libs = path.join(module_dir, "libs/mind")

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
        cprint("${blue}Generate stub for " .. target:name() .. "...")
        local py = os.getenv("CONDA_PREFIX") and (os.getenv("CONDA_PREFIX") .. "/bin/python") or "python"
        cprint("${yellow}Using python: " .. py)
        os.exec(py .. " " .. py_root .. "/_generate_stub.py " .. " --root " .. module_dir .. " -p " .. target:name() .. " --single True" .. " --eval \"import link\nimport node\"")
        -- the relevant modules are imported in the cpp code, so no need to `eval` to import them here
    end)
