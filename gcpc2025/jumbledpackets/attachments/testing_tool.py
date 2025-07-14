#!/usr/bin/env python3
#
# Testing tool for the Jumbled Packets problem
#
# Usage:
#
#	python3 testing_tool.py -f inputfile <program invocation>
#
#
# Use the -f parameter to specify the input file, e.g. 1.in.
# The input file should contain the following:
# - The first line contains "Encode".
# - The second line contains an integer n, the length of the string.
# - The third line contains one string of length n to encrypt.
# - The fourth line contains one integer r, the amount the encoded string
#	will be rotated to the left by.

# You can compile and run your solution as follows:

# C++:
#	g++ solution.cpp
#	python3 testing_tool.py -f 1.in ./a.out

# Python:
#	python3 testing_tool.py -f 1.in python3 ./solution.py

# Java:
#	javac solution.java
#	python3 testing_tool.py -f 1.in java solution

# Kotlin:
#	kotlinc solution.kt
#	python3 testing_tool.py -f 1.in kotlin solutionKt


# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it is not an exhaustive test.
# It is not guaranteed that a program that passes this testing tool will be accepted.


import argparse
import subprocess
import traceback

parser = argparse.ArgumentParser(
	description="Testing tool for problem Jumbled Packets."
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


def single_pass(action: str, s: str) -> str:
	with (
		subprocess.Popen(
			" ".join(args.program),
			shell=True,
			stdout=subprocess.PIPE,
			stdin=subprocess.PIPE,
			universal_newlines=True,
		) as p,
	):
		assert p.stdin is not None and p.stdout is not None

		raw = "\n".join([action, str(len(s)), s])
		(stdout, stderr) = p.communicate(input=raw)
		output = [line.strip() for line in stdout.strip().split("\n") if line.strip()]

		assert len(output) == 1, f"Your submission printed {len(output)} line(s), expected 1 line."
		print(f"{action} pass exit code: {p.returncode}")
		print(f"{action} pass output:")
		print(stdout, flush=True)

		team_output = output[0]
		assert len(team_output) == len(s), f"Your printed string has {len(team_output)} characters, expected {len(s)} characters."

		if action == "Encode":
			for c in team_output:
				assert c in "012", f"Your encoded string contains the character '{c}', only '0', '1', and '2' are permitted."

		return team_output


try:
	with args.inputfile as f:
		# Parse input
		lines = [l.strip() for l in f.readlines()]
		assert len(lines) >= 4, f"Input file should contain 4 lines, double check the testing tool input file format. This is explained in the comments at the top of testing_tool.py."
		action = lines[0]
		n = int(lines[1])
		s = lines[2]
		rotation = int(lines[3])

		assert len(s) == n, f"Input string has length {len(s)}, but the given length (n) is {n}."

		for c in s:
			assert c in "01", f"Input string contains character '{c}', only '0' and '1' are permitted."

		assert 0 <= rotation < n, f"Rotation is {rotation}, but must be between 0 and n-1 inclusive."

		assert action == "Encode", f"Initial action must be 'Encode', but got {action}"

	print(f"Input binary packet:\n{s}")
	print()
	team_ternary = single_pass("Encode", s)
	rotated_ternary = team_ternary[rotation:] + team_ternary[:rotation]

	print(f"Received ternary packet on Earth:\n{rotated_ternary}")
	print()
	decoded_binary = single_pass("Decode", rotated_ternary)

	assert decoded_binary == s, f"Got decoded string '{decoded_binary}', expected '{s}'."

	print("Ok, success.")

except AssertionError as e:
	print()
	print(f"Error: {e}")
	exit(1)

except Exception as e:
	print()
	print("Unexpected error:")
	traceback.print_exc()
	exit(1)
