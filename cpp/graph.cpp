#include "graph.h"

void pybind_graph(py::module &m)
{
    using classType = py::class_<Graph, pGraph>;
    const char *className = "Graph";
    PyObject *pyObj_;
    if (!py::hasattr(m, className))
        pyObj_ = classType(m, className).ptr();
    else
        pyObj_ = m.attr(className).ptr();
    auto pyClass_ = py::reinterpret_borrow<classType>(pyObj_);

    pyClass_
        .def("create", &Graph::create)
        .def("add_node", &Graph::add_node)
        .def("add_link", py::overload_cast<pLink>(&Graph::add_link))
        .def("add_link", py::overload_cast<pNode, pNode>(&Graph::add_link));
}

PYBIND11_MODULE(graphx, m)
{
#ifdef PYMODULE
    m.doc() = R"pbdoc(
        GraphX module
    )pbdoc";

    auto pyGraph = py::class_<Graph, pGraph>(m, "Graph");

    pybind_graph(m);

#endif // PYMODULE
}