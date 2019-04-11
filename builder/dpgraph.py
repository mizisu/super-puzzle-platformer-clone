import builder.utils
import os
import re


class Graph:
    def __init__(self):
        self.include_rex = re.compile(r"#include\s*\"(.+)\"")

    @staticmethod
    def convert_relative_path(files):
        return [file[2:] for file in files]

    def find_includes(self, file):
        with open(file, 'r') as f:
            content = f.read()
            all_includes = self.include_rex.findall(content)
            return all_includes

    def make_graph(self, root: str):
        files = builder.utils.get_cc_files(root, with_header=True)
        rel_files = self.convert_relative_path(files)
        print(rel_files)
        print(self.find_includes(rel_files[3]))


if __name__ == '__main__':
    os.chdir('../')

    g = Graph()
    g.make_graph('.')
