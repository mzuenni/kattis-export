#!/usr/bin/env python3
#
# Testing tool for the Crosses and Circles problem
#
# Usage:
#
#   python3 testing_tool.py [-s <seed>] <program invocation>
#
# 
# Use the -s parameter to specify a seed for repeatable randomness.
# This seed should be a single integer.
#
# You can compile and run your solution as follows:

# C++:
#   g++ solution.cpp
#   python3 testing_tool.py -s 42 ./a.out

# Python:
#   python3 testing_tool.py -s 42 python3 ./solution.py

# Rust:
#   rustc solution.rs
#   python3 testing_tool.py -s 42 ./solution

# Java:
#   javac solution.java
#   python3 testing_tool.py -s 12345 java solution

# Haskell:
#   ghc solution.hs
#   python3 testing_tool.py -s 42 ./solution


# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it is not an exhaustive test.
# It is not guaranteed that a program that passes this testing tool will be accepted.
# In particular, this interactor implements a simple random strategy that differs from the one used to judge your submission.
# This strategy is to
# 1. Win with its turn if it can.
# 2. Otherwise, block a cell that the opponent could use to win on the next turn if such a cell exists.
# 3. Otherwise, play on a random cell adjacent to a previously played cell.


import argparse
import subprocess
import traceback
import random

parser = argparse.ArgumentParser(description="Testing tool for Crosses and Circles.")
parser.add_argument(
    "-f",
    required=False,
    help="Ignore. Necessary for internal reasons."
)
parser.add_argument(
    "-s",
    dest="seed",
    metavar="seed",
    default=None,
    type=int,
    required=False,
    help="Seed for repeatable randomness.",
)
parser.add_argument("program", nargs="+", help="Invocation of your solution")

args = parser.parse_args()
rng = random.Random(args.seed)

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
    p_in = p.stdin
    p_out = p.stdout
    terminated_early = False

    def write(line: str):
        global terminated_early
        print(f"Write: {line}", flush=True)
        if p.poll() is None:
            p_in.write(f"{line}\n")
            p_in.flush()
        elif not terminated_early:
            terminated_early = True
            print("WARNING: Your program appears to have terminated early.")
            

    def read() -> str:
        line = p_out.readline().strip()
        if line == "":
            assert p.poll() is None, "Program terminated early"
        assert line != "", "Read empty line or closed output pipe"
        print(f"Read: {line}", flush=True)
        return line

    R = 59
    C = 42
    OUTSIDE = -2
    EMPTY = 0
    TEAM = 1
    JURY = -1
    DIRECTIONS = ((1, 0), (0, 1), (1, 1), (1, -1))
    NEIGHBORS = (
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1),
    )

    board = [[EMPTY for _ in range(C)] for _ in range(R)]

    def valid(cell):
        row, col = cell
        return 1 <= row <= R and 1 <= col <= C

    def value(cell):
        row, col = cell
        if not valid(cell):
            return OUTSIDE
        return board[row - 1][col - 1]

    def set_value(cell, player):
        row, col = cell
        board[row - 1][col - 1] = player

    def threats(player):
        ans = set()
        for row in range(1, R + 1):
            for col in range(1, C + 1):
                cell = (row, col)
                if value(cell) != EMPTY:
                    continue
                for drow, dcol in DIRECTIONS:
                    for i, j in ((-2, -1), (-1, 1), (1, 2)):
                        if (
                            value((row + i * drow, col + i * dcol)) == player
                            and value((row + j * drow, col + j * dcol)) == player
                        ):
                            ans.add(cell)
        return ans

    def adjacent_empty_cells():
        ans = set()
        for row in range(1, R + 1):
            for col in range(1, C + 1):
                if value((row, col)) == EMPTY:
                    continue
                for drow, dcol in NEIGHBORS:
                    cell = (row + drow, col + dcol)
                    if value(cell) == EMPTY:
                        ans.add(cell)
        return ans

    # Simulate interaction
    try:
        turns = 0
        while True:
            turns += 1
            line = read()
            team_move = tuple(map(int, line.split()))
            assert len(team_move) == 2, f"Your move should consist of two integers, got {line} instead."
            row, col = team_move
            assert valid(team_move), f"Your solution picked cell ({row}, {col}) outside the valid range [1, {R}] x [1, {C}]."
            assert value(team_move) == EMPTY, f"Your solution picked cell ({row}, {col}) again, but it was already occupied."
            if team_move in threats(TEAM):
                write("0 0")
                print()
                print(f"Your solution won after {turns} moves.", flush=True)
                break

            set_value(team_move, TEAM)

            if threats(JURY):
                write("0 0")
                winning_move = threats(JURY).pop()
                assert False, f"Your solution allows the judge to win by picking cell ({winning_move[0]}, {winning_move[1]})."

            if threats(TEAM):
                jury_move = rng.choice(list(threats(TEAM)))
            else:
                jury_move = rng.choice(list(adjacent_empty_cells()))
            assert value(jury_move) == EMPTY, "Internal error: judge tried to pick an occupied cell."
            set_value(jury_move, JURY)
            write(f"{jury_move[0]} {jury_move[1]}")
        
        assert (line := p_out.readline()) == "", f"Your submission printed extra output: '{line[:100].strip()}{'...' if len(line) > 100 else ''}'"
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
