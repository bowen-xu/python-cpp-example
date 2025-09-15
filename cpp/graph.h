#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <any>
#include <pybind11/pybind11.h>

#include "link/link.h"
#include "node/node.h"

namespace py = pybind11;

struct Graph;
using pGraph = std::shared_ptr<Graph>;
using wpGraph = std::weak_ptr<Graph>;

struct Graph
{
    using NodeSet = std::unordered_set<pNode>;
    using LinkSet = std::unordered_set<pLink>;

    NodeSet nodes;                                                    // Set of all nodes in the graph
    LinkSet links;                                                    // Set of all links in the graph
    std::unordered_map<size_t, NodeSet::iterator> node_id_map;        // Maps node ID to pNode for quick access
    std::unordered_map<size_t, LinkSet::iterator> link_id_map;        // Maps link ID to pLink for quick access
    std::unordered_map<std::string, NodeSet::iterator> node_name_map; // Maps node name to pNode for quick access
    std::unordered_map<std::string, LinkSet::iterator> link_name_map; // Maps link name to pLink for quick access

    Graph() {}

    static pGraph create()
    {
        return pGraph(new Graph());
    }

    void add_node(pNode node)
    {
        auto old_node = node_id_map.find(node->id);
        if (node && old_node != node_id_map.end())
        {
            if (old_node->second->get() == node.get())
            {
                // If the node is already in the set, do nothing
                return;
            }
            // If the node already exists, remove it from the set and maps
            nodes.erase(old_node->second);
            node_id_map.erase(old_node);
            node_name_map.erase(node->name);
        }
        else
        {
            // If the node is new, insert it into the set and maps
            nodes.insert(node);
            node_id_map[node->id] = nodes.find(node);
            node_name_map[node->name] = nodes.find(node);
        }
    }

    void add_link(pLink link)
    {
        auto old_link = link_id_map.find(link->id_tgt);
        if (link && old_link != link_id_map.end())
        {
            if (old_link->second->get() == link.get())
            {
                // If the link is already in the set, do nothing
                return;
            }
            // If the link already exists, remove it from the set and maps
            links.erase(old_link->second);
            link_id_map.erase(old_link);
            link_name_map[link->src.lock()->name + "->" + link->tgt.lock()->name] = links.find(link);
        }
        else
        {
            // If the link is new, insert it into the set and maps
            links.insert(link);
            link_id_map[link->id_tgt] = links.find(link);
            link_name_map[link->src.lock()->name + "->" + link->tgt.lock()->name] = links.find(link);
        }
    }

    void add_link(pNode source, pNode target)
    {
        pLink link = Link::create(source, target);
        add_link(link);
        source->out_links.push_back(link);
        target->in_links.push_back(link);
    }
};

void pybind_graph(py::module &m);
