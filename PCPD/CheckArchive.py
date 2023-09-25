#!/usr/bin/env python

import argparse
import sys
import zipfile
import tarfile
import shutil
from pathlib import Path
from os.path import normpath
import typing
import re
import subprocess

CMAKE = "cmake"
EXECS = ["price0", "hedge"]

build = False
check = False
copy = False
extract = False
pnldir = None
structuredir = None
destdir = None
args_list = []

parser = argparse.ArgumentParser()
parser.add_argument("--check", help="Check the archives", action="store_true")
parser.add_argument("--extract", help="Extract the archives to destdir", action="store_true")
parser.add_argument("--destdir", help="Directory where to extract the archive", type=str)
parser.add_argument("--build", help="Build the projects found destdir", action="store_true")
parser.add_argument("--pnldir", help="PNL dir to pass to cmake as CMAKE_PREFIX_PATH", type=str)
parser.add_argument("--cmake", help="CMake executable", type=str)
parser.add_argument("--copy", help="Copy the executables to structuredir", action="store_true")
parser.add_argument("--structuredir", help="Structure directory", type=str)
parser.add_argument("files", nargs="*")
args = parser.parse_args()

# Get args
if args.build:
    build = True
if args.check:
    check = True
if args.extract:
    extract = True
if args.pnldir:
    pnldir = Path(args.pnldir).expanduser().resolve()
if args.destdir:
    destdir = Path(args.destdir).expanduser().resolve()
if args.files:
    args_list = args.files
if args.cmake:
    CMAKE = args.cmake
if args.copy:
    copy = True
if args.structuredir:
    structuredir = Path(args.structuredir).expanduser().resolve()

# Check args logic
if extract and destdir is None:
    print("You must specify '--destdir' along with '--extract'")
    parser.print_help()
    sys.exit(1)
if build and destdir is None:
    print("You must specify '--destdir' along with '--build'")
    parser.print_help()
    sys.exit(1)
if copy and structuredir is None:
    print("You must specify '--structuredir' along with '--copy'")
    parser.print_help()
    sys.exit(1)


class Archive(object):
    ZIP = '.zip'
    TAR = '.tar'
    TYPE = None
    file = None
    toplevelDir = None
    files = []
    filePaths = []

    def __init__(self, archiveFile: str):
        filePath = Path(archiveFile)
        if not filePath.is_file():
            print(f"\tFile {archiveFile} is not a recognized archive")
            raise ValueError
        if filePath.suffix == '.zip':
            self.TYPE = self.ZIP
            self.file = zipfile.ZipFile(archiveFile)
        elif ''.join(filePath.suffixes) in ['.tar.gz', '.tgz', '.tar.bz']:
            self.TYPE = self.TAR
            self.file = tarfile.open(archiveFile)


    def list_files(self) -> typing.List[str]:
        """
        Return the list of the files contained in the archive
        """
        if self.file is None:
            print("\tNo valid archive object found")
            raise ValueError
        if self.TYPE == self.TAR:
            return [m.path for m in self.file.getmembers()]
        if self.TYPE == self.ZIP:
            return self.file.namelist()
        return []


    def compute_toplevel_dir(self):
        if self.toplevelDir is not None:
            return
        files = self.list_files()
        # Sometimes, the first entry is ./._dirname, remove it
        if  re.match(r'\./\._', files[0]):
            files.pop(0)

        # Normalize all paths
        self.filePaths = [Path(normpath(f)) for f in files]

        # Find toplevel dir
        toplevelDirs = {f.parts[0] for f in self.filePaths}
        if len(toplevelDirs) != 1:
            print("\tNot all the files have the same toplevel directory")
            print("\t", toplevelDirs)
            toplevelDirs_no__ = [t for t in toplevelDirs if not t.startswith('__')]
            if len(toplevelDirs_no__) == 1:
                self.toplevelDir = toplevelDirs_no__.pop()
            raise ValueError
        self.toplevelDir = toplevelDirs.pop()


    def check(self) -> bool:
        """
        Return true if the archive has a valid format
        """
        try:
            self.compute_toplevel_dir()
        except ValueError:
            return False

        # Check toplevel dir name
        print(f"\tToplevel directory: {self.toplevelDir}")
        if not re.match(r'[Ee]quipe_\d+', self.toplevelDir):
            print("\tToplevel directory should be named Equipe_i")
            return False

        # No file outside toplevel
        for f in self.filePaths:
            if f.is_absolute() or f.parts[0] == '..':
                print(f"\t{f.as_posix()} refers to a file outside of the toplevel directory")
                return False

        # Check archive content
        check = True
        if Path(self.toplevelDir).joinpath('AUTHORS') not in self.filePaths:
            print("\tNo AUTHORS file found")
            check = False
        if Path(self.toplevelDir).joinpath('CMakeLists.txt') not in self.filePaths:
            print("\tNo toplevel CMakeLists.txt file found")
            check = False
        if Path(self.toplevelDir).joinpath('src') not in self.filePaths:
            print("\tNo src directory found")
            check = False
        if Path(self.toplevelDir).joinpath('/build') in self.filePaths:
            print("\tbuild directory in archive")
            check = False
        return check

    def extract(self):
        """
        Extract the archive
        """
        self.compute_toplevel_dir()
        # Create destdir
        if destdir.exists() and not destdir.is_dir():
            print(f"\t{destdir} already exists but is not a directory")
            raise ValueError
        if not destdir.exists():
            destdir.mkdir()

        # Extract
        if self.file is None:
            print("\tNo valid archive object found")
            raise ValueError
        if destdir.joinpath(self.toplevelDir).exists():
            shutil.rmtree(destdir.joinpath(self.toplevelDir).as_posix())
        self.file.extractall(path=destdir.as_posix())


def build_project(project) -> bool:
    """
    Build project by calling 'CMake' and 'make'

    :param project: name of the directory inside destdir
    """
    buildDir = destdir.joinpath(project, 'build')
    if buildDir.exists():
        shutil.rmtree(buildDir.as_posix())
    buildDir.mkdir()
    proc_args = [CMAKE, '-DCMAKE_PREFIX_PATH=' + pnldir.as_posix(), '-DCMAKE_BUILD_TYPE=Release', '..']
    try:
        print("\tRunning CMake...", end='', flush=True)
        subprocess.run(proc_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True, cwd=buildDir.as_posix())
        print(" OK")
        print("\tCompiling...", end='', flush=True)
        subprocess.run(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True, cwd=buildDir.as_posix())
        print(" OK")
        for e in EXECS:
            exec_exists = buildDir.joinpath(e).exists()
            print(f"\tChecking if {e} is present...", "OK" if exec_exists else "FAIL")
        return True
    except FileNotFoundError as e:
        print(" FAIL")
        print("\tCMake executable not found. ABORTING ")
        print("\t\t", e.filename)
    except subprocess.CalledProcessError as e:
        print(" FAIL")
        print('--', e)
        print('--', e.output.decode('utf-8'))
        print('--', e.stderr.decode('utf-8'))
    return False


def copy_execs(project):
    builddir = destdir.joinpath(project, 'build')

    # Create Structure dir
    if structuredir.exists() and not structuredir.is_dir():
        print(f"\t{structuredir} already exists but is not a directory")
        raise ValueError
    if not structuredir.exists():
        structuredir.mkdir()
    if not structuredir.joinpath('Executables').exists():
        structuredir.joinpath('Executables').mkdir()

    for e in EXECS:
        exec_path = builddir.joinpath(e)
        if exec_path.exists():
            dest_exec = structuredir.joinpath('Executables', e + '_' + project)
            print(f"\tCopying {exec_path.as_posix()} to {dest_exec.as_posix()}")
            shutil.copy(exec_path, dest_exec)


if __name__ == "__main__":

    for arg in args_list:
        print(f"-- {arg}")
        archive = Archive(arg)
        if check:
            archive_isvalid = archive.check()
            print(f"\tChecking archive format... {'OK' if archive_isvalid else 'FAIL'}")
        if extract:
            print(f"\tExtracting {arg} to {destdir}")
            archive.extract()

    if build:
        for d in [d.name for d in destdir.iterdir() if d.is_dir()]:
            print(f"-- {d}")
            is_built = build_project(d)
            if copy and is_built:
                copy_execs(d)
