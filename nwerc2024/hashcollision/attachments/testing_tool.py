#!/usr/bin/env python3
#
# Testing tool for the Hash Collision problem
#
# Usage:
#
#   python3 testing_tool.py -f inputfile <program invocation>
#
#
# Use the -f parameter to specify the input file, e.g. 1.in.
# The input file should contain two lines:
# - The first line contains the value of n.
# - The second line contains the values of f(r) for r = 1, 2, ..., n.

# You can compile and run your solution as follows:

# C++:
#   g++ solution.cpp
#   python3 testing_tool.py -f 1.in ./a.out

# Python:
#   python3 testing_tool.py -f 1.in python3 ./solution.py

# Java:
#   javac solution.java
#   python3 testing_tool.py -f 1.in java solution

# Kotlin:
#   kotlinc solution.kt
#   python3 testing_tool.py -f 1.in kotlin solutionKt


# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it is not an exhaustive test.
# It is not guaranteed that a program that passes this testing tool will be accepted.


import argparse
import subprocess
import traceback

parser = argparse.ArgumentParser(description="Testing tool for problem Hash Collision.")
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

with (
    args.inputfile as f,
    subprocess.Popen(
        " ".join(args.program),
        shell=True,
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
        universal_newlines=True,
    ) as p,
):
    assert p.stdin is not None and p.stdout is not None
    p_in = p.stdin
    p_out = p.stdout

    def write(line: str):
        assert p.poll() is None, "Program terminated early"
        print(f"Write: {line}", flush=True)
        p_in.write(f"{line}\n")
        p_in.flush()

    def read() -> str:
        assert p.poll() is None, "Program terminated early"
        line = p_out.readline().strip()
        assert line != "", "Read empty line or closed output pipe"
        print(f"Read: {line}", flush=True)
        return line

    # Parse input
    lines = f.readlines()
    n = int(lines[0])
    f = list(map(int, lines[1].split()))

    def hash(c: int, r: int):
        h = r
        for _ in range(c):
            h = f[h - 1]
        return h

    # Simulate interaction
    try:
        write(f"{n}")
        queries = 0
        while True:
            line = read().split()
            c, r = map(int, line[1:])
            assert 1 <= c <= n, "c not in bounds"
            assert 1 <= r <= n, "r not in bounds"
            if line[0] == "?":
                queries += 1
                write(hash(c, r))
            elif line[0] == "!":
                assert hash(c, r) == c, f"Your solution is not correct: Got c={c} and r={r}, but f^{c}({r}) = {hash(c, r)}, expected {c}."
                break
            else:
                assert False, "Line does not start with question or exclamation mark"

        print()
        print(f"Found a valid solution: c={c} and r={r}", flush=True)
        print(f"Queries used: {queries}", flush=True)
        assert (line := p_out.readline()) == "", f"Your submission printed extra data after finding a solution: '{line[:100].strip()}{'...' if len(line) > 100 else ''}'"
        print(f"Exit code: {p.wait()}", flush=True)
        assert p.wait() == 0, "Your submission did not exit cleanly after finishing"

    except AssertionError as e:
        print()
        print(f"Error: {e}")
        print()
        print(f"Killing your submission.", flush=True)
        p.kill()
        exit(1)

    except Exception as e:
        print()
        print("Unexpected error:")
        traceback.print_exc()
        print()
        print(f"Killing your submission.", flush=True)
        p.kill()
        exit(1)
