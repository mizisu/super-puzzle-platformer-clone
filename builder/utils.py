import glob

def get_cc_files() -> list:
    files_group = [glob.glob(e, recursive=True) for e in ['./**/*.cc']]
    files = [f for group in files_group for f in group]
    return list(files)