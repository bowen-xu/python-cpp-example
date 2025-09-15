"""

        Node module
    
"""
from __future__ import annotations
import link
__all__ = ['Node']
class Node:
    @staticmethod
    def create() -> Node:
        ...
    def connect_to(self, arg0: Node) -> link.Link:
        ...
