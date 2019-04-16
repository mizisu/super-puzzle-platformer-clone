import os
import subprocess


class Compiler:
    def __init__(self, root, output_dir):
        self.root = root
        self.output_dir = output_dir
        if not os.path.isdir(self.output_dir):
            os.mkdir(self.output_dir)

    def compile(self, *cc_files):
        for file in cc_files:
            obj_file = str(file).replace('/', '_').replace('.cc', '')
            if obj_file[0] == '.':
                obj_file = obj_file[1:]
            obj_file = os.path.join(self.output_dir, obj_file)
            subprocess.call([
                'clang++',
                '-std=c++17',
                '-I' + self.root,
                '-g',
                '-c',
                file,
                '-o',
                obj_file
            ])