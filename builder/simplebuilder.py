import os
import subprocess
import builder.utils as utils


def build(root: str):
    build_dir = root + '/build/'
    utils.clear_folder(build_dir)
    if not os.path.isdir(build_dir):
        os.mkdir(build_dir)
    cc_files = utils.get_cc_files(root)
    obj_files = []
    for file in cc_files:
        obj_file = os.path.splitext(os.path.basename(file))[0]
        obj_file = build_dir + obj_file
        obj_files.append(obj_file)
        subprocess.call([
            'clang++',
            '-std=c++17',
            '-I' + root,
            '-g',
            '-c',
            file,
            '-o',
            obj_file
        ])

    subprocess.call(['clang++',
                     '-o',
                     build_dir + 'game',
                     '-lSDL2',
                     '-lSDL2_image'] +
                    obj_files)
