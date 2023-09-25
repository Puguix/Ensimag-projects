import subprocess
import argparse
import sys
from pathlib import Path
from zipfile import BadZipFile, ZipFile
import os
import shutil
from subprocess import STDOUT
import time
import pandas as pd


def get_csv_json_from_folder(folder):
    '''
    Helper function for retrieving json and csv files from a folder
    '''
    csvs = []
    jsons = []
    for filename in os.listdir(folder):
        if filename.endswith('.csv'):
            csvs.append(filename)
        if filename.endswith('.json'):
            jsons.append(filename)
    return csvs, jsons

def extract_build_solution(zipped_folder_path, destination_folder_name):
    '''
    Principle: give as an input a zipped folder containing the solution to compile, along with a destination folder where the solution will be extracted. 
    The script compiles the entire unzipped solution.
    '''
    try:
        if not zipped_folder_path.exists():
            print(f'No zippped folder {zipped_folder_path.name} available on path')
            sys.exit(1)
        unzipped_folder = zipped_folder_path.stem
        if not unzipped_folder.startswith('Group'):
            print('*********************************************************************')
            print('*** WARNING: expecting a zipped file and folder of the form *Group_i*')
            print('*** still proceeding')
            print('*********************************************************************')
        print(f"Unzipping zipped folder at {zipped_folder_path} into {destination_folder_name}")
        with ZipFile(zipped_folder_path, 'r') as zip_obj:
            zip_obj.extractall(destination_folder_name)
            print('Done with extraction')
        new_folder = Path(destination_folder_name).joinpath(unzipped_folder)
        if not Path(new_folder).exists():
            print(f'Wrong extracted folder name, expected {new_folder.stem}')
            sys.exit(1)
        os.chdir(new_folder)
        print(f'Building solution in folder {unzipped_folder} (platform x64)')
        subprocess.run("dotnet build /nowarn:msb3246,msb3270 /p:Platform=x64 -v q", check=True)
        print(f"Done building solution in folder {unzipped_folder}")
        return True, new_folder
    except BadZipFile:
        print(f'Invalid zipped folder: {zipped_folder_path.name}')
        return False, None
    except subprocess.CalledProcessError as e:
        print(f'Error when building solution in folder {unzipped_folder}')
        return False, None
    except subprocess.TimeoutExpired:
        print('Timeout')
        return False, None
    except SystemExit:
        print('Exiting...')
        return False, None

def console_tests(console_folder, test_prop_folder, output_folder):
    '''
    Execution of a set of tests from an application console
    '''
    try:
        print('Running tests on console')
        Path.mkdir(output_folder, parents=True)
        for test_folder in test_prop_folder.iterdir():
            if test_folder.is_dir():
                run_single_console_test(console_folder, test_folder, output_folder)
    except SystemExit:
        print('Exiting...')

def run_single_console_test(solution_folder, test_folder, out_folder):
    '''
    Main method for running a console test on a given set of parameters and market data.
    '''
    print(f'Running test in folder {test_folder}')
    os.chdir(solution_folder)  
    csvs, jsons = get_csv_json_from_folder(test_folder)
    if len(csvs) != 1 or len(jsons) != 1:
        print(f'wrong number of csv or json files in {test_folder}, skipping.')
    else:
        csv_file = test_folder.joinpath(csvs[0])
        json_file = test_folder.joinpath(jsons[0])
        result_file = str(out_folder.joinpath(test_folder.name))
        subprocess.run(f"BacktestConsole.exe {json_file} {csv_file} {result_file}_output.json", check=True)

def grpc_console_tests(grpc_server_folder, test_prop_folder, output_folder, client_path):
    '''
    Execution of a set of tests from a grpc server
    '''
    try:
        print('Running grpc tests on console')
        os.chdir(grpc_server_folder)
        print('starting grpc folder')
        process= subprocess.Popen("GrpcBacktestServer.exe")
        time.sleep(3)
        for test_folder in test_prop_folder.iterdir():
            if test_folder.is_dir():
                run_single_grpc_test(test_folder, output_folder, client_path)
        print('killing server')
        process.kill()
    except SystemExit:
        print('killing server on exception')
        process.kill()
        print('Exiting...')
    except FileNotFoundError as e:
        print('killing server on file not found exception')
        print(e)
        process.kill()
        print('Exiting...')

def run_single_grpc_test(test_folder, out_folder, client_path):
    '''
    Main method for running a grpc test on a given set of parameters and market data.
    '''
    print(f'Running grpc test in folder {test_folder}')
    csvs, jsons = get_csv_json_from_folder(test_folder)
    if len(csvs) != 1 or len(jsons) != 1:
        print(f'wrong number of csv or json files in {test_folder}, skipping.')
    else:
        csv_file = test_folder.joinpath(csvs[0])
        json_file = test_folder.joinpath(jsons[0])
        result_file = str(out_folder.joinpath(test_folder.name))
        os.chdir(client_path)
        proc_2 = subprocess.Popen(["GrpcEvaluation.exe", json_file, csv_file, f"{result_file}_grpc_output.json"], stderr=STDOUT)
        proc_2.communicate()
        print('killing client')
        proc_2.kill()
        print('done with grpc test')

def create_grpc_client_path(grpc_folder_path):
    '''
    Helper method for building the grpc and accessing the executable path.
    '''    
    os.chdir(grpc_folder_path)
    print(f'Building client in folder {grpc_folder_path} (platform x64)')
    subprocess.run("dotnet build /nowarn:msb3246,msb3270 /p:Platform=x64 -v q", check=True)
    print(f"Done building client in folder {grpc_folder_path}")
    grpc_client_path=grpc_folder_path.joinpath('GrpcEvaluation/bin/x64/Debug/net7.0')
    return grpc_client_path  

def check_output_structure(output_folder):
    '''
    Helper method to make sure the application outputs are in the correct format.
    '''
    EXPECTED_FIELDS = ['date', 'value', 'deltas', 'deltasStdDev', 'price', 'priceStdDev']
    for result_file in output_folder.iterdir():
        print(f'  File {result_file}')
        try:
            df = pd.read_json(result_file)
            columns = df.columns
            for field in EXPECTED_FIELDS:
                if field not in columns:
                    print(f'** Warning: missing field {field}. Make sure the field names are camelcased.')
            print('  --> OK')
        except ValueError:
            print('Unable to parse json file.')

def create_output_for_project(zipped_project_path, tests_folder_path, build_folder_path, out_folder_path, grpc_client_path):
    '''
    Parameters:
    - zipped_project_path: path to the zipped project for which the output will be created
    - test_folder_path: path to the folder containing the tests to be run
    - build_folder_path: path to the folder where the project will be extracted and built
    - out_folder_path: path to the folder where the output results will be stored
    - grpc_client_path: path to the folder containing the grpc client (if it exists), None otherwise
    '''    
    build_ok, solution_folder = extract_build_solution(zipped_project_path, build_folder_path)
    path_suffix = 'bin/x64/Debug/net7.0'
    if build_ok:
        solution_folder_path = Path(solution_folder)
        solution_name = solution_folder_path.name
        console_bin_path = f'BacktestConsole/{path_suffix}'
        console_folder = solution_folder_path.joinpath(console_bin_path)
        if not Path(console_folder).exists():
            print(f'Wrong path {console_folder}')
            sys.exit(1)
        output_folder = out_folder_path.joinpath(solution_name).joinpath('output')
        console_tests(console_folder, tests_folder_path, output_folder)
        if not (grpc_client_path is None):
            grpc_path = Path(solution_folder).joinpath('GrpcBacktestServer')
            if grpc_path.exists():
                print('Grpc server exists, running tests')
                server_bin_path = f'GrpcBacktestServer/{path_suffix}'
                grpc_folder = solution_folder_path.joinpath(server_bin_path)
                grpc_console_tests(grpc_folder, tests_folder_path, output_folder, grpc_client_path)
        print('Checking output structure')
        check_output_structure(output_folder)

def run_tests():
    '''
    Main orchestrator for tests
    '''
    parser = argparse.ArgumentParser()
    parser.add_argument("--sln", help="Path to the folder containing the zipped solution.", type=str)
    parser.add_argument("--tests", help="Path to folder containing tests to run", type=str)
    parser.add_argument("--build", help="Path to folder where the solution will be extracted and built")
    parser.add_argument("--out", help="Path to folder where the results will be stored")
    parser.add_argument("--grpc", help="Optional. Path to folder where the grpc client will be stored")
    parser.add_argument("--force", action='store_true', help="Force output folder to be erased if it already exists. Default: false")
    args = parser.parse_args()
    if not args.sln:
        print('Missing "--sln" parameter')
        sys.exit(1)
    if not args.tests:
        print('Missing "--tests" parameter')
        sys.exit(1)
    if not args.build:
        print('Missing "--build" parameter')
        sys.exit(1)
    if not args.out:
        print('Missing "--out" parameter')
        sys.exit(1)
    else:
        if not args.grpc:
            grpc_client_path=None
        else:
            grpc_folder_path = Path(args.grpc)
            grpc_client_path = create_grpc_client_path(grpc_folder_path)
        zipped_folder_path = Path(args.sln)
        tests_folder_path = Path(args.tests)
        build_folder_path = Path(args.build)
        out_folder_path = Path(args.out)        
        if  Path(out_folder_path).exists():
            if args.force:
                shutil.rmtree(out_folder_path)
            else:
                print('Error: output folder already exists')
                sys.exit(1)
        Path.mkdir(out_folder_path)
        for filename in zipped_folder_path.iterdir():
            if filename.suffix == '.zip':
                create_output_for_project(zipped_folder_path.joinpath(filename), tests_folder_path, build_folder_path, out_folder_path, grpc_client_path) 

     

if __name__ == "__main__":
    run_tests()

