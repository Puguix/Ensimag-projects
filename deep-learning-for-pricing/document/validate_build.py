#!/usr/bin/env python

import subprocess
import argparse
import sys
from pathlib import Path
from zipfile import BadZipFile, ZipFile
import os



def unzip_solution(zipped_folder_path, destination_folder_name):
    if zipped_folder_path.suffix == '.zip':
        print(f"Unzipping zipped folder at {zipped_folder_path} into {destination_folder_name}")
        try:
            with ZipFile(zipped_folder_path, 'r') as zip_obj:
                zip_obj.extractall(destination_folder_name)
                print('Done with extraction')
        except BadZipFile:
            print(f'Invalid zipped folder: {zipped_folder_path.name}')
        except subprocess.CalledProcessError:
            unzipped_folder = zipped_folder_path.stem
            print(f'Error when building solution in folder {unzipped_folder}')
        except subprocess.TimeoutExpired:
            print('Timeout')
        except SystemExit:
            print('Exiting...')
    else:
        print(f'Provided file  {zipped_folder_path} is not zipped')

def build_project(project_path: Path):
    print(f'Building project {project_path.name}')
    try:
        os.chdir(project_path)
        subprocess.run(['dotnet', 'build', '-v',  'q', f'{project_path.name}.csproj'], check=True)
        print(f"Done building project {project_path}")
    except subprocess.CalledProcessError:
        print(f'Error when building project {project_path}')
        sys.exit(1)


def build_projects_in_sol(solution_folder: Path, sol_name: str, projects: list[str]):
    sol_folder = solution_folder.joinpath(sol_name)
    if sol_folder.is_dir():
        for proj_name in projects:
            proj_path = sol_folder.joinpath(proj_name)
            if proj_path.is_dir():
                build_project(proj_path)
            else:
                print(f'Error: folder {proj_name} not found in {sol_folder}')
                sys.exit(1)
    else:
        print(f'Error: {sol_folder} is not a directory')
        sys.exit(1)
   
def validate_build():
    parser = argparse.ArgumentParser()
    parser.add_argument("--sln", help="Path to the zipped solution.", type=str)
    parser.add_argument("--name", help="The name of the folder that was zipped")
    parser.add_argument("--build", help="Absolute path to the folder where the solution will be extracted and built")
    args = parser.parse_args()
    if not args.sln:
        print('Missing "--sln" parameter')
        sys.exit(1)
    if not args.build:
        print('Missing "--build" parameter')
        sys.exit(1)
    if not args.name:
        print('Missing "--name" parameter')
        sys.exit(1)
    zipped_folder_path = Path(args.sln)
    build_folder_path = Path(args.build)
    sol_name = args.name
    unzip_solution(zipped_folder_path, build_folder_path)
    build_projects_in_sol(build_folder_path, sol_name, projects = ['PropagationComparison', 'RegressionConsole'])
    print("*** Validation is OK ***")

if __name__ == "__main__":
    validate_build()