#include "link.h"
#include "../node/node.h"

void pybind_link(py::module &m)
{
    using classType = py::class_<Link, pLink>;
    const char *className = "Link";
    PyObject *pyObj_;
    if (!py::hasattr(m, className))
        pyObj_ = classType(m, className).ptr();
    else
        pyObj_ = m.attr(className).ptr();
    auto pyClass_ = py::reinterpret_borrow<classType>(pyObj_);

    pyClass_
        .def("create", py::overload_cast<pNode, pNode>(&Link::create))
        .def("create", py::overload_cast<>(&Link::create));
}

PYBIND11_MODULE(link, m)
{
#ifdef PYMODULE
    m.doc() = R"pbdoc(
        Link module
    )pbdoc";

    auto pyLink = py::class_<Link, pLink>(m, "Link");

    pybind_link(m);
#endif // PYMODULE
}