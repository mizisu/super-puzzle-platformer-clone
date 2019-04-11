from glob import glob
import os


def get_cc_files(dir) -> list:
    files_group = [glob(e, recursive=True) for e in [dir + '/**/*.cc']]
    files = [f for group in files_group for f in group]
    return list(files)


def clear_folder(dir):
    for file in glob(dir + '/*'):
        os.remove(file)
