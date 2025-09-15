#pragma once

#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include <pybind11/pybind11.h>

#include "link/link.h"

namespace py = pybind11;

struct Link;
using pLink = std::shared_ptr<Link>;
using wpLink = std::weak_ptr<Link>;

struct Node;
using pNode = std::shared_ptr<Node>;
using wpNode = std::weak_ptr<Node>;

struct Node : public std::enable_shared_from_this<Node>
{
    std::string name;
    size_t id = 0;
    std::unordered_map<std::string, std::any> attributes;
    std::vector<pLink> in_links;
    std::vector<pLink> out_links;

    Node() {}

    static pNode create()
    {
        return pNode(new Node());
    }

    pLink connect_to(pNode target);
};
