Problem: Pants on fire 
Difficulty: 10%


Idea:	Transitive hull	


Solution:
	You are given a list of facts (all of them orderings on things) like
		Mexicans are worse than Americans
		Iranians are worse than Mexicans
		North Koreans are worse than Mexicans.
	You think that these facts are correct.
	
	Now someone (@RealDonaldTrump) tells you some new facts.
	You have to determine the truth-state of these statements
		a) "Fact" -> if it logically follows from the facts you are initially given
		b) "Pants on fire" -> if neither the new fact nor its negation follow
		c) "Alternative Fact" -> if the negation follows (i.e. you know A is better than B, but DJT tells you it is the other way around)

	To make things a bit harder, there is also a second kind of facts:
		X are the worst
	stating that X must be a minimal (not the minimum) element in the order. You can simly keep a list of all these statements and check all each time (the input is rather small).
