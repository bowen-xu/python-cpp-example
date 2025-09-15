"""

        GraphX module
    
"""
from __future__ import annotations
import link
import node
import typing
__all__ = ['Graph']
class Graph:
    @staticmethod
    def create() -> Graph:
        ...
    @typing.overload
    def add_link(self, arg0: link.Link) -> None:
        ...
    @typing.overload
    def add_link(self, arg0: node.Node, arg1: node.Node) -> None:
        ...
    def add_node(self, arg0: node.Node) -> None:
        ...
