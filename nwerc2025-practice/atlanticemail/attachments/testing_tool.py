#!/usr/bin/env python3
#
# Testing tool for the Atlantic Email problem
#
# Usage:
#
#   python3 testing_tool.py -f inputfile <program invocation>
#
#
# Use the -f parameter to specify the input file, e.g. 1.in.
# The input file should follow the format specified in the problem statement:
# - The first line must contain 'send'.
# - The second line contains an integer n, the length of the email.
# - The third line contains a string s of length n, the email to send.
#
# This tool calls your program two times.
# In the first pass, the input file is sent to your program, which should output 5 binary strings.
# In the second pass, the 5 binary strings are shuffled and sent to your program.
#
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
import random
from pathlib import Path

parser = argparse.ArgumentParser(description="Testing tool for problem Atlantic Email.")
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
    input_lines = args.inputfile.read_text().splitlines()
    assert input_lines[0].strip() == "send", "First line of input file must be 'send'"
    n = int(input_lines[1].strip())
    email = input_lines[2].strip()
    assert len(email) == n, "Length of email does not match specified length n"

    try:
        # Read output from first program.
        binary_strings = [read() for _ in range(5)]
        for bs in binary_strings:
            assert (
                len(bs) <= n + 10
            ), f"Binary string '{bs}' has length {len(bs)}, which is more than {n+10}."
        for bs in binary_strings:
            assert all(
                c in "01" for c in bs
            ), f"Binary string '{bs}' contains characters other than '0' and '1'."

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
# Second round: send the binary strings back to the program


nextpass = Path("nextpass.in")

# Write input for second pass
f = open(nextpass, "w")
f.write(f"receive\n")
random.shuffle(binary_strings)
for binary_string in binary_strings:
    f.write(f"{binary_string}\n")
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

        reconstructed_email = read()

        assert (
            reconstructed_email == email
        ), f"Your program did not reconstruct the email correctly. Started with:\n{email}\nBut reconstructed:\n{reconstructed_email}"

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
