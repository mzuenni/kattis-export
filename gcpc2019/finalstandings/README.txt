Problem: A game of chance
Difficulty: 75% (not solving it)


Idea:	Given the GCPC scoreboard at the end of the contest (i.e. including the freeze), knowledge about which problems you solved, how difficult each problem is, how strong each team is.
		Compute the probability with which you will win GCPC

Note: This problem has already been developed at NWERC'17. If selected, the story would have to be adapted to GCPC teams advancing to NWERC.

Solution:
	You win GCPC, if no team has solved more problems than you, i.e. P(win) = \Pi_{t \in other team} 1 - P(t as solved more problems than you).
	So you have to compute for each team how probable it is that it has solved more problems than you (which is a fixed number $S$).

	We can compute this probability using DP over (#problems, #problems solved)
		more(0,x) = 0
		more(0,0) = 1
		more(i,j) = more(i-1,j-1) // if problem i was solved before the timelimit
				  = more(i-1,j) // if problem i was not attempted
				  = (1-S*D)*more(i-1,j) + S*D*more(i-1,j-1) // if problem of difficulty D was attempted by team with strength S after the freeze
