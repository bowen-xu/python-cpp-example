#include "graph.h"

PYBIND11_MODULE(graphx, m)
{
#ifdef PYMODULE
    m.doc() = R"pbdoc(
        GraphX module
    )pbdoc";

    auto pyGraph = py::class_<Graph, pGraph>(m, "Graph");

    pyGraph
        .def("create", &Graph::create)
        .def("add_node", &Graph::add_node)
        .def("add_link", py::overload_cast<pLink>(&Graph::add_link))
        .def("add_link", py::overload_cast<pNode, pNode>(&Graph::add_link));

#endif // PYMODULE
}