from graphx import Graph
from graphx.node import Node

n1 = Node.create()
n2 = Node.create()
g = Graph.create()
g.add_link(n1, n2)
print("done.")