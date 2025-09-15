#include "link.h"
#include "../node/node.h"

PYBIND11_MODULE(link, m)
{
#ifdef PYMODULE
    m.doc() = R"pbdoc(
        Link module
    )pbdoc";

    auto pyLink = py::class_<Link, pLink>(m, "Link");

    pyLink
        .def("create", py::overload_cast<pNode, pNode>(&Link::create))
        .def("create", py::overload_cast<>(&Link::create));
#endif // PYMODULE
}