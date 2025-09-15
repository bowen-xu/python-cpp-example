#pragma once

#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include <memory>
#include <pybind11/pybind11.h>

#include "node/node.h"

namespace py = pybind11;

struct Link;
using pLink = std::shared_ptr<Link>;
using wpLink = std::weak_ptr<Link>;

struct Node;
using pNode = std::shared_ptr<Node>;
using wpNode = std::weak_ptr<Node>;

struct Link
{
    size_t id_tgt;
    size_t id_src;
    wpNode src;
    wpNode tgt;
    std::unordered_map<std::string, std::any> attributes;

    Link() {}
    Link(pNode source, pNode target) : src(source), tgt(target) {}

    static pLink create(pNode source, pNode target)
    {
        return pLink(new Link(source, target));
    }

    static pLink create()
    {
        return pLink(new Link());
    }
};