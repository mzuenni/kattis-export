#!/usr/bin/env python3
#
# Testing tool for the Hasty Haul problem
#
# Usage:
#
#   python3 testing_tool.py -f inputfile <program invocation>
#
#
# Use the -f parameter to specify the input file, e.g. 1.in.
# The input file should follow the format specified in the problem statement:
# - The first line contains the number of test cases. Then for each test case:
# - One line containing the height h, width w, and furniture count k of the grid
# - h lines, each containing a string of '.' and '#' of length w, representing the grid.
#
# This tool calls your program two times.
# In the first pass, the input file is sent to your program.
# In the second pass, the input grids with the provided moves applied are sent to your program.
# Cases where your submission output 'risky' in the first pass are skipped in the second pass.
# The input for the second pass is written to `nextpass.in`.

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
from pathlib import Path

parser = argparse.ArgumentParser(description="Testing tool for problem Hasty Haul.")
parser.add_argument(
    "-f",
    dest="inputfile",
    metavar="inputfile",
    default=None,
    required=True,
    type=Path,
    help="The input file to use.",
)
parser.add_argument("program", nargs="+", help="Invocation of your solution")

args = parser.parse_args()


def read() -> str:
    line = p.stdout.readline().strip()
    assert line != "", "Read empty line or closed output pipe"
    print(f"Read: {line}", flush=True)
    return line


# to check consistency between rounds
mapping = dict()
# to check internal consistency
rev_mapping = dict()


def read_and_apply_move(grid):
    out = read()
    if out == "risky":
        return False

    # Read moves
    from_x, from_y = map(int, out.split())
    to_x, to_y = map(int, read().split())
    assert (
        grid[from_x - 1][from_y - 1] == "#"
    ), f"Moved from an empty cell at ({from_x}, {from_y})"
    assert (
        grid[to_x - 1][to_y - 1] == "."
    ), f"Moved to a filled cell at ({to_x}, {to_y})"

    newgrid = [x for x in grid]
    newgrid[from_x - 1] = (
        newgrid[from_x - 1][: from_y - 1] + "." + newgrid[from_x - 1][from_y:]
    )
    newgrid[to_x - 1] = newgrid[to_x - 1][: to_y - 1] + "#" + newgrid[to_x - 1][to_y:]
    return newgrid


def stringify(grid):
    return "\n".join(grid)


print(f"\n---------- RUN 1 ----------\n", flush=True)

print(f"Input:\n{args.inputfile.read_text()}", flush=True)

with (
    open(args.inputfile, "r") as f,
    subprocess.Popen(
        " ".join(args.program),
        shell=True,
        stdout=subprocess.PIPE,
        stdin=f,
        universal_newlines=True,
    ) as p,
):
    assert p.stdout is not None

    # Parse input
    lines = args.inputfile.read_text().splitlines()
    cases = int(lines[0])

    try:
        idx = 1
        # Read output from first program.
        for key in range(cases):
            # Read input
            h, w, k = map(int, lines[idx].split())
            grid = lines[idx + 1 : idx + 1 + h]
            idx += 1 + h

            newgrid = read_and_apply_move(grid)
            if newgrid is not False:
                sgrid = stringify(grid)
                snewgrid = stringify(newgrid)

                if sgrid in mapping:
                    assert (
                        mapping[sgrid] == newgrid
                    ), "Your program produced different outputs for the same input."
                else:
                    if snewgrid in rev_mapping:
                        assert (
                            rev_mapping[snewgrid] == grid
                        ), "Your program produced inconsistent outputs."

                    mapping[sgrid] = newgrid
                    rev_mapping[snewgrid] = grid

        print()
        assert (
            line := p.stdout.readline()
        ) == "", f"Your submission printed extra data: '{line[:100].strip()}{'...' if len(line) > 100 else ''}'"
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

print(f"\n---------- RUN 2 ----------\n", flush=True)
# Second round: send all generated grids, and check their moves are reversed.

# Write input for second pass
nextpass = Path("nextpass.in")
f = open(nextpass, "w")
cases = len(mapping)
# Write input to file
f.write(f"{cases}\n")
for soldgrid, newgrid in mapping.items():
    h = len(newgrid)
    w = len(newgrid[0])
    k = sum(l.count("#") for l in newgrid)
    f.write(f"{h} {w} {k}\n")
    for line in newgrid:
        f.write(line.rstrip() + "\n")
f.close()

print(f"Input:\n{nextpass.read_text()}", flush=True)

with (
    open(nextpass, "r") as f,
    subprocess.Popen(
        " ".join(args.program),
        shell=True,
        stdout=subprocess.PIPE,
        stdin=f,
        universal_newlines=True,
    ) as p,
):
    assert p.stdout is not None

    try:
        # Read output from second program.
        for soldgrid, newgrid in mapping.items():
            newnewgrid = read_and_apply_move(newgrid)
            if newnewgrid is False:
                assert (
                    False
                ), "Your program first printed a move, but then printed risky in the second round."
            else:
                snewnewgrid = stringify(newnewgrid)

                assert (
                    snewnewgrid == soldgrid
                ), "Your program did not reverse the move correctly."

        print()
        assert (
            line := p.stdout.readline()
        ) == "", f"Your submission printed extra data: '{line[:100].strip()}{'...' if len(line) > 100 else ''}'"
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
