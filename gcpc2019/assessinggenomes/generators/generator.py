#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys
import random
import string
import subprocess
import time


def roll_string(length, char_set):
    return ''.join(random.choice(char_set) for _ in range(length))


def roll_input(nmin, nmax, lmin, lmax):
    string = []
    n = random.randint(nmin, nmax)
    string.append(str(n))
    for i in range(2 * n):
        l = 1
        while l % 2:
            l = random.randint(lmin, lmax)

        char_set = random.choice(char_sets)
        val = random.random()
        if val < 0.1:
            string.append(roll_string(l, char_set))
        else:
            divisors = list(i for i in range(2, l // 2) if l % i == 0)
            num_parts = random.choice(divisors)
            part_length = l // num_parts

            if val < 0.2:
                substring = random.choice(char_set) * (part_length - 1) + random.choice(char_set)
            else:
                substring = roll_string(part_length, char_set)
            string.append(substring * num_parts)

    return "\n".join(string)


if __name__ == "__main__":
    char_sets = [string.ascii_lowercase, string.ascii_uppercase, string.ascii_letters]
    nmin, nmax, lmin, lmax = map(int, sys.argv[1:5])

    if len(sys.argv) < 5:
        print(roll_input(nmin, nmax, lmin, lmax))

    subprocess_args = sys.argv[5:]
    longest_time = 0.0
    longest_input = ""

    try:
        while True:
            process = subprocess.Popen(subprocess_args, stdout=subprocess.PIPE,
                                       stderr=subprocess.PIPE, stdin=subprocess.PIPE)
            process_input = roll_input(nmin, nmax, lmin, lmax)
            start = time.time()
            process.stdin.write(process_input.encode("ascii"))
            process.communicate()
            duration = time.time() - start
            if duration > longest_time:
                print("New longest: {0}".format(duration))
                longest_time = duration
                longest_input = process_input
    except KeyboardInterrupt:
        print()
        print(longest_input)
