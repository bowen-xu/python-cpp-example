#include "../link/link.h"
#include "node.h"

pLink Node::connect_to(pNode target)
{
    pLink link = Link::create(shared_from_this(), target);
    return link;
}

void pybind_node(py::module &m)
{
    using classType = py::class_<Node, pNode>;
    const char *className = "Node";
    PyObject *pyObj_;
    if (!py::hasattr(m, className))
        pyObj_ = classType(m, className).ptr();
    else
        pyObj_ = m.attr(className).ptr();
    auto pyClass_ = py::reinterpret_borrow<classType>(pyObj_);

    pyClass_
        .def("create", &Node::create)
        .def("connect_to", &Node::connect_to);
}

PYBIND11_MODULE(node, m)
{
#ifdef PYMODULE
    m.doc() = R"pbdoc(
        Node module
    )pbdoc";

    auto pyNode = py::class_<Node, pNode>(m, "Node");

    pybind_node(m);

#endif // PYMODULE
}