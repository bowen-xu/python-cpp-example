"""

        Link module
    
"""
from __future__ import annotations
import node
import typing
__all__ = ['Link']
class Link:
    @staticmethod
    @typing.overload
    def create() -> Link:
        ...
    @typing.overload
    def create(self: node.Node, arg0: node.Node) -> Link:
        ...
