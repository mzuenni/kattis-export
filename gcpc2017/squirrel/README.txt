
Proposal 1:
Difficulty estimate: 		medium
Implementation estimate: 	medium

Ratatöskr is a squirrel that lives in a giant (but finite) mythical tree called Yggdrasil. He likes to gossip, which sets the other inhabitants of the tree against each other. Ratatöskr is thus hunted by the two ravens of Odin, which are called Hugin and Munin, to bring him to justice.

The location where two or more branches meet in the tree is called a node. Initially, all three sit on a different node. [Alternatively: the ravens are in the air in the beginning?]
On a signal of Odin, one raven flies into the air and lands on a node of the tree again, while the other stays where it is. [Alternatively: both can move?] During this maneuver, Ratatöskr can travel along the branches to reach another node, but may not pass over a node where a raven sits. He is much quicker than the ravens and will reach his destination before a raven lands.

We may safely assume that he will not pick a destination where a raven chooses to land, if this is possible. However, if Ratatöskr cannot move at all due to a sitting raven, he gets caught if the other raven chooses to fly to his position.

Help Odin determine an optimal strategy for capture, i.e. the minimum number of signals he has to give until Ratatöskr is guaranteed to be captured by a raven. Output '-1' if Ratatöskr can escape them indefinitely. The two ravens can be assumed to never share a node, as this is never beneficial, and there are at least three nodes (so it is possible).

[One could generalize to k ravens to make it more difficult.]


Solution:
The two ravens can always capture Ratatöskr. This is intuitively clear, as one raven can sit to keep Ratatöskr in some part of the tree while the other moves to reduce the remaining part of the graph. (In fact, the necessary and sufficient number of ravens is the treewidth of the graph plus one. Trees are graphs with treewidth 1, so 2 ravens are necessary and sufficient.)

To find the optimal strategy, one can use dynamic programming / memoization. If Ratatöskr is in a 'leaf' and one raven in the neighboring node, then one signal suffices, no matter where the other raven is. These are the base cases. For the given starting configuration, we generate all possible ways the raven(s) can fly and Ratatöskr can move, and we use the algorithm recursively. Then, we return 1+ the MINIMUM (raven's choice) of the MAXIMUM (Ratatöskr's choice). To speed up, we use memoization.

Maybe there is a more efficient algorithm (greedily 'halving' the remaining part or something), but this one should be accepted.
