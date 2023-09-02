#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
@Author       : Jamie LaPointe
@Date         : 2020-12-17 15:00:00
@LastEditors  : Jamie LaPointe
@LastEditTime : 2020-12-17 15:00:00
@Description  : Runs unit tests with code coverage on the project
this only supports Linux
'''

import argparse
import os
import pathlib
import subprocess
import sys

ROOT_DIR = pathlib.Path(__file__).parent.parent.parent.absolute()
BUILD_DIR = os.path.join(ROOT_DIR, 'build')
TEST_DIR = os.path.join(BUILD_DIR, 'test')


class Inputs:

    def __init__(self) -> None:
        self.compiler = 'clang++'
        self.ccompiler = 'clang'
        self.generator = 'Ninja'
        self.enable_ipo = 'OFF'
        self.build_type = 'Debug'
        self.sanitizers = 'OFF'
        self.coverage = 'ON'


def run_tests(inputs: Inputs) -> None:
    cmake_configure_command = (
        f'CXX=/usr/bin/{inputs.compiler} '
        f'CC=/usr/bin/{inputs.ccompiler} '
        f'cmake -S . -B ./build -G "{inputs.generator}" '
        f'-Dcpp_practice_ENABLE_IPO:BOOL={inputs.enable_ipo} '
        f'-DCMAKE_BUILD_TYPE:STRING={inputs.build_type} '
        f'-Dcpp_practice_ENABLE_COVERAGE:BOOL={inputs.coverage} '
        f'-Dcpp_practice_ENABLE_SANITIZER_ADDRESS:BOOL={inputs.sanitizers} '
        f'-Dcpp_practice_ENABLE_SANITIZER_LEAK:BOOL={inputs.sanitizers} '
        f'-Dcpp_practice_ENABLE_SANITIZER_UNDEFINED:BOOL={inputs.sanitizers}')
    print(f'Running: {cmake_configure_command}')
    subprocess.run(
        cmake_configure_command,
        shell=True,
        check=True,
        cwd=ROOT_DIR,
        text=True)

    cmake_build_command = 'cmake --build ./build --parallel 4'
    print(f'Running: {cmake_build_command}')
    subprocess.run(
        cmake_build_command, shell=True, check=True, cwd=ROOT_DIR, text=True)

    cmake_test_command = './cpp_practice_tests --gtest_output=xml'
    print(f'Running: {cmake_test_command}')
    subprocess.run(
        cmake_test_command, shell=True, check=True, cwd=TEST_DIR, text=True)

    cmake_coverage_command = (
        'llvm-profdata-16 merge -sparse default.profraw '
        '-o cpp_practice_tests.profdata ')
    print(f'Running: {cmake_coverage_command}')
    subprocess.run(
        cmake_coverage_command, shell=True, check=True, cwd=TEST_DIR, text=True)

    cmake_coverage_command = (
        'llvm-profdata-16 merge -sparse default.profraw -o '
        'cpp_practice_tests.profdata ')
    print(f'Running: {cmake_coverage_command}')
    subprocess.run(
        cmake_coverage_command, shell=True, check=True, cwd=TEST_DIR, text=True)

    cmake_coverage_command = (
        'llvm-cov-16 export ./cpp_practice_tests '
        '-instr-profile=cpp_practice_tests.profdata > coverage.json')
    print(f'Running: {cmake_coverage_command}')
    subprocess.run(
        cmake_coverage_command, shell=True, check=True, cwd=TEST_DIR, text=True)

    cmake_coverage_command = (
        'llvm-cov-16 export ./cpp_practice_tests '
        '-instr-profile=cpp_practice_tests.profdata '
        '-format=lcov > coverage.lcov')
    print(f'Running: {cmake_coverage_command}')
    subprocess.run(
        cmake_coverage_command, shell=True, check=True, cwd=TEST_DIR, text=True)

    cmake_coverage_command = (
        'llvm-cov-16 show ./cpp_practice_tests '
        '-instr-profile=cpp_practice_tests.profdata '
        '-format=html > coverage.html')
    print(f'Running: {cmake_coverage_command}')
    subprocess.run(
        cmake_coverage_command, shell=True, check=True, cwd=TEST_DIR, text=True)


def cli_arguments() -> tuple[argparse.Namespace, argparse.ArgumentParser]:
    parser = argparse.ArgumentParser(description=__doc__)
    args = parser.parse_args()
    return args, parser


def main() -> None:
    args, parser = cli_arguments()
    del args
    del parser
    inputs = Inputs()
    run_tests(inputs)


if __name__ == '__main__':
    sys.exit(main())
