# python-cpp-example
A tiny example project for mixed programming with Python and C++.

## How to use

Make sure you have had your environment prepaired for (1) compiling C++ with XMake, and (2) running Python code.

```
cd cpp
xmake
```

Python dynamic libs (with format `*.so` on MacOS, for example) and stub files (with format `*.pyi`) will be generated in `./graphx`.

Use `graphx` as a python module. For example,
```Python
from graphx import Graph
from graphx.node import Node
n1 = Node.create()
n2 = Node.create()
g = Graph()
g = Graph.create()
g.add_link(n1, n2)
```

## Features
- Modular architecture: The project is organized into submodules (e.g., node, link), each with its own build script and clear responsibilities.
- Handles circular dependencies: The example supports circular dependencies between submodules.
- Standardized bindings: All C++/Python interfaces are exposed using dedicated `pybind_xxx` functions (e.g., `pybind_graph`); classes are interfaced in a standard way.
