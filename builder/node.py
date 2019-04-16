class Node:
    def __init__(self, name):
        self.children = []
        self.parent = []
        self.name = name

    @property
    def isroot(self):
        return self.parent.count() == 0

    def add_child(self, node):
        node.__add_parent(self)
        self.children.append(node)

    def __add_parent(self, node):
        self.parent.append(node)

    def __str__(self):
        return self.name
