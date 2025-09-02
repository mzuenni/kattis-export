Problem: Election
Difficulty: 1% (not solving it)


Idea:	Given the projected result of a FPTP (also known as winner-takes it all) election.
		How many voters do you have to bribe in order to win the overall election.

Solution:
		Bribe voters greedily starting with those in the currently closest race until you have won the election.
		The number of bribes needed for each ward can be determined via simulation (we can require "intelligent" O(#parties) by having a large number of voters).
