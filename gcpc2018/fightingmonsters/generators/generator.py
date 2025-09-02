import random
random.seed(42)

def get_fib(min_num, max_num):
	# Generate fibonacci numbers between min_num and max_num
	fib = []

	# Start at 2,3; 1 has to be handled separately
	c1,c2 = 2,3
	while c2 <= max_num:
		
		if c2 >= min_num:
			fib.append(c2)
		c1, c2 = c2, c1+c2

	return fib

def make_multiple_ones(min_num, max_num, number_of_monsters, number_of_ones):

	if number_of_ones > number_of_monsters:
		return None

	# Generate fibonacci numbers in range [min, max]
	fib = get_fib(min_num, max_num)

	inp = []
	for _ in range(number_of_monsters - number_of_ones):
		# Sample random numbers between min and max
		inp.append(random.randint(min_num, max_num))

	if any(fib[ind] in inp and fib[ind+1] in inp for ind in range(0,len(fib)-1)):
		return make_multiple_ones(min_num, max_num, number_of_monsters, number_of_monsters)
	
	inp += [1] * number_of_ones

	random.shuffle(inp)
	return inp, number_of_ones > 1

def make_normal_input(min_num, max_num, number_of_monsters, has_solution):
	inp = []
	for _ in range(number_of_monsters - (has_solution * 2)):
		# Sample random numbers between min and max
		inp.append(random.randint(min_num, max_num))

	# Generate fibonacci numbers in range [min, max]
	fib = get_fib(min_num, max_num)

	solution = None

	if has_solution:		
		# Sample a random index in the sequence
		ind = random.randint(0, len(fib)-2)

		# Append 2 fib. numbers starting from sampled index
		inp.append(fib[ind])
		inp.append(fib[ind+1])

		solution = (fib[ind], fib[ind+1])
	else:
		# Make sure the sample does not contain 2 consecutive fibonacci numbers
		if inp.count(1) > 1 or any(fib[ind] in inp and fib[ind+1] in inp for ind in range(0,len(fib)-1)):
			# I'm lazy, just generate again. This should not happen very often unless min and max are very small
			return make_normal_input(min_num, max_num, number_of_monsters, has_solution)

	random.shuffle(inp)
	return inp, solution

number_of_monsters = 50
has_solution = True

max_num = 10000
min_num = 50

normal_input_params = [
("std", (10, 100, 5, True)),
("std", (10, 100, 5, False)),
("std", (100, 1000, 20, True)),
("std", (100, 1000, 20, False)),
("std", (100, 10000, 100, True)),
("std", (100, 10000, 100, False)),
("std", (100, 1000000, 1000, True)),
("std", (100, 1000000, 1000, False)),
("std", (100, 1000000, 10000, True)),
("std", (100, 1000000, 10000, False)),
("std", (100, 1000000, 100000, True)),
("std", (100, 1000000, 100000, False)),
("ones", (100, 10000, 1000, 1)),
("ones", (100, 10000, 1000, 2)),
("ones", (100, 10000, 1000, 10)),
]

current_file_num = 1

for alg, params in normal_input_params:
	
	print("generating testcase with parameters {} ...".format(params))

	input_file = open("../data/secret/{}.in".format(current_file_num),"w") 
	desc_file = open("../data/secret/{}.desc".format(current_file_num),"w") 
	ans_file = open("../data/secret/{}.ans".format(current_file_num),"w") 

	generated_input = None
	if alg == "std":
		generated_input, sol = make_normal_input(*params)

		desc_file.write("Parameters:\n")
		desc_file.write("Min: {}\nMax: {}\nSample size: {}\nHas solution: {}\n".format(*params))
		if params[-1]:
			desc_file.write("Solution: {}\n".format(sol))

			m1 = generated_input.index(sol[0])
			m2 = generated_input.index(sol[1])
			ans_file.write("{} {}\n".format(m1, m2))
		else:
			ans_file.write("impossible\n")

	elif alg == "ones":
		generated_input, sol = make_multiple_ones(*params)

		desc_file.write("Parameters:\n")
		desc_file.write("Min: {}\nMax: {}\nSample size: {}\nNumber of ones: {}\nHas solution: {}\n".format(*(params+(sol,))))
		if sol:
			desc_file.write("Solution: (1,1)\n")

			m1 = generated_input.index(1)
			m2 = generated_input[m1+1:].index(1) + m1 + 1
			ans_file.write("{} {}\n".format(m1, m2))
		else:
			ans_file.write("impossible\n")

	input_file.write(str(len(generated_input)) + "\n")
	input_file.write(" ".join(map(str, generated_input)) + "\n")

	input_file.close()
	desc_file.close()
	ans_file.close()

	current_file_num += 1
