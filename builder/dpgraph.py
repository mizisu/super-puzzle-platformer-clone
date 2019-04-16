import os
import re
import builder.utils as utils
import builder.node as node
import builder.compiler as compiler


class Graph:
    def __init__(self):
        self.include_rex = re.compile(r"#include\s*\"(.+)\"")
        self.nodes = {}

    @staticmethod
    def remove_current_dir_prefix(files):
        return [file[2:] for file in files]

    def find_includes(self, file):
        with open(file, 'r') as f:
            content = f.read()
            all_includes = self.include_rex.findall(content)
            return all_includes

    def make_graph(self, root: str):
        files = utils.get_cc_files(root)

        for file in files:
            new_node = node.Node(file)
            self.nodes[file] = new_node

        for file in files:
            n = node.Node(file)
            print(n)
            print(self.find_includes(file))
            print()


if __name__ == '__main__':
    os.chdir('../')

    g = Graph()
    g.make_graph('.')

    c = compiler.Compiler('.', './build/')
    c.compile('./main.cc')
