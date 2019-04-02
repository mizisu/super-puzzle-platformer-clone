import os
import subprocess
from glob import glob
import builder.utils

def clear_build_folder():
    for file in glob('./build/*'):
        os.remove(file)

def main():
    clear_build_folder()
    if not os.path.isdir('./build'):
        os.mkdir('./build')
    ccfiles = builder.utils.get_cc_files()
    objfiles = []
    for file in ccfiles:
        objfile = os.path.splitext(os.path.basename(file))[0]
        objfile = f'./build/{objfile}'
        objfiles.append(objfile)
        subprocess.call([
            'clang++',
            '-std=c++17',
            '-I' + os.getcwd(),
            '-g',
            '-c',
            file,
            '-o',
            objfile
        ])
    
    subprocess.call([
        'clang++',
        '-o',
        './build/game',
        '-lSDL2',
        '-lSDL2_image'] +
        objfiles)

if __name__ == "__main__":
    main()
    