#!/usr/bin/env python3
#
# Testing tool for the Lateral Damage problem
#
# Usage:
#
#   python3 testing_tool.py -f inputfile <program>
#
#
# Use the -f parameter to specify the input file, e.g. 1.in.
# Format of the input file:
# - One line with two integers:
#   - n, the size of the grid; and
#   - k, the number of aircraft carriers.
# - n lines with characters in [.0-9], where
#     `.` is an empty location,
#     `0` is a part of the first carrier,
#     `1` is a part of the second carrier,
#     ...
#     `k-1` is a part of the last carrier.
# E.g.:
# 5 1
# .....
# 00000
# .....
# .....
# .....
#
# If you have a C++ solution stored in a file called "sol.cpp",
# you must first compile using "g++ sol.cpp -o sol" and then
# invoke the testing tool with:
#
#   python3 testing_tool.py -f 1.in ./sol
#
# If you have a Python solution that you would run using
# "pypy3 solution.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py -f 1.in pypy3 solution.py
#
# If you have a Java solution that you would run using
# "java MyClass", you could invoke the testing tool with:
#
#   python3 testing_tool.py -f 1.in java MyClass
#
# If you have a Kotlin solution stored in a file called "Sol.kt",
# you must first compile using "kotlinc Sol.kt" and then
# invoke the testing tool with:
#
#   python3 testing_tool.py -f 1.in kotlin Sol
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it is not guaranteed
# that a program that passes the testing tool will be accepted.
# Specifically, this testing tool only uses fixed grid,
# while your program will be tested against an adaptive interactor.

import argparse
import subprocess
import traceback


def write(p, line):
    assert p.poll() is None, "Program terminated early"
    print(f"Write: {line}", flush=True)
    p.stdin.write(f"{line}\n")
    p.stdin.flush()


def read(p):
    assert p.poll() is None, "Program terminated early"
    line = p.stdout.readline().strip()
    assert (
        line != ""
    ), "Read empty line or closed output pipe. Make sure that your program started successfully."
    print(f"Read: {line}", flush=True)
    return line


parser = argparse.ArgumentParser(
    description="Testing tool for the Lateral Damage problem"
)
parser.add_argument(
    "-f",
    dest="inputfile",
    metavar="inputfile",
    default=None,
    type=argparse.FileType("r"),
    required=True,
    help="The input file to use.",
)
parser.add_argument("program", nargs="+", help="Invocation of your solution")

args = parser.parse_args()

with args.inputfile as f:
    lines = f.readlines()
    assert len(lines) > 0

    n, k = map(int, lines[0].split())

    ships = {i: set() for i in range(k)}
    for y, line in enumerate(lines[1:], start=1):
        for x, char in enumerate(line.strip(), start=1):
            if char != ".":
                ships[int(char)].add((x, y))

shots = 0
max_shots = 2500

with subprocess.Popen(
    " ".join(args.program),
    shell=True,
    stdout=subprocess.PIPE,
    stdin=subprocess.PIPE,
    universal_newlines=True,
) as p:
    try:
        write(p, f"{n} {k}")

        while True:
            x, y = map(int, read(p).split())
            shots += 1
            for ship in ships.values():
                if (x, y) in ship:
                    ship.remove((x, y))
                    write(p, "hit" if ship else "sunk")
                    break
            else:
                write(p, "miss")
            if not any(ship for ship in ships.values()):
                break

        assert (
            p.stdout.readline() == ""
        ), "Your submission printed extra data after shooting all ships."
        assert p.wait() == 0, "Your submission did not exit cleanly after finishing."

        assert (
            shots <= max_shots
        ), f"Used {shots} shots, which is more than the allowed {max_shots}."

        print(f"\nSuccess.\nShots used: {shots}\n")

    except AssertionError as e:
        print()
        print(f"Error: {e}")
        print()
        try:
            p.wait(timeout=2)
        except subprocess.TimeoutExpired:
            print("Killing your submission after 2 second timeout.")
            p.kill()

    except Exception as e:
        print()
        traceback.print_exc()
        print()
        try:
            p.wait(timeout=2)
        except subprocess.TimeoutExpired:
            print("Killing your submission after 2 second timeout.")
            p.kill()
        raise e

    finally:
        print(f"Exit code: {p.wait()}\n", flush=True)
