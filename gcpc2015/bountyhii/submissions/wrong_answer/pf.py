import sys 

# WA Solution

def get_friends(planets):
    friends = [1] * len(planets)
    for p in range(len(planets)):
        n = planets[p]
        for s in n:
            if friends[s] > 0:
                friends[s] = 0 
                break
    #print planets
    #print friends
    return friends


def read_problem(f):
    N = int(f.readline())
    planets = [None] * N 
    for p in range(N):
        connections = f.readline().split()
        planets[p] = list(map(int, connections[1:]))
    friends = get_friends(planets)

    print(sum(friends))

def main():
    if len(sys.argv) >= 2:
        read_problem(open(sys.argv[1]))
    else:
        read_problem(sys.stdin)

if __name__ == "__main__":
    main()
