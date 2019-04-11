from glob import glob
import os


def get_cc_files(dir, with_header=False):
    files_group = [glob(e, recursive=True) for e in [dir + '/**/*.cc']]
    if with_header:
        files_group.extend([glob(e, recursive=True) for e in [dir + '/**/*.h']])
    files = [f for group in files_group for f in group]
    return list(files)


def clear_folder(dir):
    for file in glob(dir + '/*'):
        os.remove(file)