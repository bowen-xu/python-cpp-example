#include "../link/link.h"
#include "node.h"

pLink Node::connect_to(pNode target)
{
    pLink link = Link::create(shared_from_this(), target);
    return link;
}

PYBIND11_MODULE(node, m)
{
#ifdef PYMODULE
    m.doc() = R"pbdoc(
        Node module
    )pbdoc";

    auto pyNode = py::class_<Node, pNode>(m, "Node");

    pyNode
        .def("create", &Node::create)
        .def("connect_to", &Node::connect_to);

#endif // PYMODULE
}