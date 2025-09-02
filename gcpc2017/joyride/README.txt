Problem: Joyride
Difficulty: 50%


Idea:	01-Knapsack DP with extension


Solution:
	You are in an amusement park with your little daughter.
	Your wife will pick you up in exactly $X$ minutes and you obviously don't want to wait with your daughter, so you want to spend all $X$ minutes in the park.
	For each ride, you know how long one ride will take and how much it will cost.

	Here comes the tricky part: When going through the park, you cannot leave out one of the rides -- else your daughter would be very upset.
	Clearly you can use the same ride twice, if you pass it twice.
	You are given a map of the park and its rides (graph).
	Walking between rides is instantaneous.

	Your task is to determine the minimum amount of money you need to spend to stay $X$ minutes in the park.

	--> Use 01 knapsack DP + current position as state, memoise 

