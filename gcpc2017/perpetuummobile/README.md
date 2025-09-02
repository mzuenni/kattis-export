 Problem: Perpetuum Mobile
 Difficulty: Medium 
 
 The year is 1902. Albert Einstein is working in the patent office in Bern.
 Many patent proposals contain egrogious errors - 
 some even violate the law of conservation of energy.
 To make matters worse, the majority of proposals makes use of non-standard 
 physical units that are not part of the metric system (or not even documented).
 
 - Every patent proposal contains n>=2 energy converters. 
 - Every converter has an input energy unit attached to it.
 - For some pairs (v1, v2) of energy converters, we have labelled directed edges (v1 ---- d -----> v2) where d > 0 is a double value.
   Such an edge indicates that v1 converts 1 input value (given in the unit assigned to v1) into d output values given in the input unit of v2.
   The output of v1 can be used as input of v2 if and only if a directed edge from v1 to v2 exists.
 - Einstein would like to dismiss all those proposals out of hand where the energy converters can be chained up in a way such that more is fed back into a converter
   than is given as initial input energy to the converter, thus violating the law of conservation of energy 
   (for simplicity, converters with 100% energy conversion efficiency are allowed).
 - For every patent proposal, decide whether Einstein should dismiss the proposal!
 
 Solution:
 * Replace edge weight d by log(1/d) in given directed graph.  
 * Einstein should dismiss a proposal <=> a negative cycle exists in the graph thus constructed.  
 * Use Ford-Fulkerson to detect negative cycles.
 