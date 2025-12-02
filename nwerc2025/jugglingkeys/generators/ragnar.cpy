#!/usr/bin/env python3
import sys
import random
import numpy

MAXT = 10**9
MAXN = 100000
MAXQ = 100000

seed = int(sys.argv[1])
random.seed(seed)
numpy.random.seed(seed + 1)

# PARAMS
# #people is random from one of the ranges below.
n_ranges = [(1, 10), (10, 100), (100, 1000), (1000, 100000), (95000, 100000)]
n = random.randint(*random.choice(n_ranges))

# #trips is either a bit larger than n, random, or close to max.
q_ranges = [(n, 10 * n), (n, MAXQ), (95000, MAXQ)]
q = random.randint(*random.choice(q_ranges))
q = min(q, MAXQ)

# GENERATE TRIPS
num_trips = 0
trips = []

home = list(range(n))
away = []

# Strategy 1 (50%):
# - At each point in time, either each person at home leaves with probability p%,
# - or else a random person returns.
# Strategy 2 (50%):
# - At each point in time, if >=1 person is home, someone leaves with fixed probability p.
p_fixed = random.randint(0, 1) == 1

# p of leaving is in [0.4, 1.0], so that many times most people are away.
p_leave = random.random() * 0.6 + 0.4
p_stay = 1.0 - p_leave

t = 0
# Average time between events
dt = random.choice([1, 2, 5, 10, 1000, 4000, 4500])

while len(trips) < q:
    if p_fixed:
        all_stay = random.random() < p_stay
    else:
        p_all_stay = p_stay ** len(home)
        all_stay = random.random() < p_all_stay

    # Increment time by a geometrically distributed amount, with average dt.
    t += 1 + numpy.random.geometric(1 / dt)

    if len(away) > 0 and (num_trips == q or len(home) == 0 or all_stay):
        # a random person comes home
        idx = random.randint(0, len(away) - 1)
        pid, ltime = away[idx]
        trips.append((pid, ltime, t))
        home.append(pid)
        # swapppop
        away[idx] = away[len(away) - 1]
        away.pop()
    else:
        # a random person leaves
        idx = random.randint(0, len(home) - 1)
        pid = home[idx]
        away.append((pid, t))
        num_trips += 1
        # swappop
        home[idx] = home[len(home) - 1]
        home.pop()

# SOLVE FOR K


# copied from submissions/accepted/ragnar.py
def solve(n, q, trips):
    events = []
    for j in range(q):
        ni, l, r = trips[j]
        events.append((l, ni - 1, "l", j))
        events.append((r + 0.5, ni - 1, "r", j))
    events.sort(reverse=True)
    cnt = n
    ans = []
    keys = 0
    maxkeys = 0
    person_keys = [0] * n
    ans = ["0"] * q
    for _, i, d, j in events:
        if d == "l":
            cnt += 1
            if person_keys[i]:
                keys -= 1
                person_keys[i] = False
                # print('left', i, 'cnt', cnt, 'keys', keys)
            continue

        cnt -= 1

        if cnt == 0:
            keys += 1
            maxkeys = max(maxkeys, keys)
            ans[j] = "1"
            person_keys[i] = True
        # print('left', i, 'cnt', cnt, 'keys', keys)

    # print(ans)
    return maxkeys


solve_k = solve(n, q, trips)

# CHOOSE K
# we choose either:
# - 10%: solve_k-randint(1..10) => impossible
# - 10%: solve_k-1 => impossible
# - 40%: exactly solve_k
# - 20%: solve_k + randint(1..5)
# - 10%: solve_k + randint(5..100)
# - 10%: solve_k + randint(100..n)

k_ranges = [(-10, -1), (-1, -1), (0, 0), (1, 5), (5, 100), (100, max(n, 100))]
weights = [0.1, 0.1, 0.4, 0.2, 0.1, 0.1]
k_range = random.choices(k_ranges, weights=weights)[0]
k = solve_k + random.randint(*k_range)

if k > n:
    # randomly choose in solve_k..=n
    k = random.randint(solve_k, n)
if k < 0:
    # randomly choose in 0..=solve_k
    k = random.randint(1, max(solve_k, 1))
if k == 0:
    k = 1


# SHUFFLE?
# - 10% sort by person
# - 10% reverse sort by person
# - 10% sort by l time
# - 10% reverse sort by l time
# - 10% sort by r time
# - 10% reverse sort by r time
# - 40% random

mode = random.randint(1, 10)
if mode == 1:
    trips.sort(key=lambda x: x[0])
elif mode == 2:
    trips.sort(key=lambda x: x[0], reverse=True)
elif mode == 3:
    trips.sort(key=lambda x: x[1])
elif mode == 4:
    trips.sort(key=lambda x: x[1], reverse=True)
elif mode == 5:
    trips.sort(key=lambda x: x[2])
elif mode == 6:
    trips.sort(key=lambda x: x[2], reverse=True)
else:
    random.shuffle(trips)

# PRINT
print(n, k, q)
for p, l, r in trips:
    print(p + 1, l, r)
