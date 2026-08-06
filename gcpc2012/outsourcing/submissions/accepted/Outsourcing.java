// @EXPECTED_RESULTS@: CORRECT
import java.util.*;

public class Outsourcing {

public static void main(String[] args) {
  Scanner s = new Scanner(System.in);
  int tc = s.nextInt();
  while (tc --> 0) {
    int m1 = s.nextInt(), n1 = s.nextInt(), k1 = s.nextInt(), m2 = s.nextInt(), n2 = s.nextInt(), k2 = s.nextInt();
    Map<Integer,Map<Integer, Integer>> dfa1 = new HashMap<Integer,Map<Integer,Integer>>(), dfa2 = new HashMap<Integer,Map<Integer,Integer>>();

    while(m1 --> 0) {
      int from = s.nextInt(), to = s.nextInt(), label = s.nextInt();
      if (!dfa1.containsKey(from)) dfa1.put(from, new HashMap<Integer,Integer>());
      dfa1.get(from).put(label,to);
    }
    while(m2 --> 0) {
      int from = s.nextInt(), to = s.nextInt(), label = s.nextInt();
      if (!dfa2.containsKey(from)) dfa2.put(from, new HashMap<Integer,Integer>());
      dfa2.get(from).put(label,to);
    }

    dfa1 = minimize(dfa1,n1,Math.max(k1,k2));
    dfa2 = minimize(dfa2,n2,Math.max(k1,k2));

//		System.out.println(dfaToString(dfa1,dfa1.size(),2));
//		System.out.println(dfaToString(dfa2,dfa2.size(),2));

    if (testDfaEquivalence(Math.max(k1,k2), dfa1, dfa2, 0, 0, new int[dfa1.size()], new int[dfa2.size()], 1) > 0)
      System.out.println("eligible");
    else
      System.out.println("not eligible");
  }
}

public static Map<Integer,Map<Integer,Integer>> minimize(Map<Integer,Map<Integer,Integer>> dfa, int stateCount, int labelCount) {
  Map<Integer,List<Integer>> partitionToStates = new HashMap<Integer,List<Integer>>();
  Map<Integer,Integer> stateToPartition = new HashMap<Integer,Integer>();
  partitionToStates.put(0,new LinkedList<Integer>());
  partitionToStates.put(1,new LinkedList<Integer>());
  for (int i=0; i < stateCount-1; i++) {partitionToStates.get(0).add(i); stateToPartition.put(i,0);}
  partitionToStates.get(0).add(-1); stateToPartition.put(-1,0);
  partitionToStates.get(1).add(stateCount-1); stateToPartition.put(stateCount-1,1);
  int c=0; boolean changed = true;

  while((c!=0) || (changed)) {
    if (c==0) changed = false;
    Map<Integer,List<Integer>> newPartitionToStates = new HashMap<Integer,List<Integer>>();
    Map<Integer,Integer> newStateToPartition = new HashMap<Integer,Integer>();
    for (int pClass = 0; pClass < partitionToStates.size(); pClass++) {
      Map<Integer,Integer> reachedClasses = new HashMap<Integer,Integer>();
      for (int state: partitionToStates.get(pClass)) {
	int reachedClass = stateToPartition.get(-1);
	if (dfa.containsKey(state) && dfa.get(state).containsKey(c)) reachedClass = stateToPartition.get(dfa.get(state).get(c));
	if (!reachedClasses.containsKey(reachedClass)) {
	  reachedClasses.put(reachedClass,newPartitionToStates.size());
	  newPartitionToStates.put(newPartitionToStates.size(),new LinkedList<Integer>());
	}
	newPartitionToStates.get(reachedClasses.get(reachedClass)).add(state);
	newStateToPartition.put(state,reachedClasses.get(reachedClass));
      }
      if (reachedClasses.size() > 1) changed = true;
    }
    partitionToStates = newPartitionToStates;
    stateToPartition = newStateToPartition;
    c = (c+1) % labelCount;
  }
  Map<Integer,Map<Integer, Integer>> minDfa = new HashMap<Integer,Map<Integer,Integer>>();
  for (int pClass=0; pClass < partitionToStates.size(); pClass++) {
    int reprState = partitionToStates.get(pClass).get(0);
    Map<Integer,Integer> transitions = new HashMap<Integer,Integer>(); minDfa.put(pClass,transitions);
    for (c=0; c < labelCount; c++)
      if (dfa.containsKey(reprState) && dfa.get(reprState).containsKey(c))
	transitions.put(c,stateToPartition.get(dfa.get(reprState).get(c)));
      else
	transitions.put(c,stateToPartition.get(-1));
  }
 return minDfa;
}

public static int testDfaEquivalence(int labelCount, Map<Integer,Map<Integer,Integer>> dfa1, Map<Integer,Map<Integer,Integer>> dfa2, int curState1, int curState2, int[] labels1, int[] labels2, int nextLabel) {
  if (labels1[curState1] != labels2[curState2]) return -1;
  if (labels1[curState1] == 0) labels1[curState1]=labels2[curState2]= nextLabel++; else return nextLabel;
  if ((curState1==dfa1.size()-1) && (curState2!=dfa2.size()-1)) return -1;
  if ((curState1!=dfa1.size()-1) && (curState2==dfa2.size()-1)) return -1;

  for (int c=0; c < labelCount; c++) {
		nextLabel = testDfaEquivalence(labelCount, dfa1, dfa2, dfa1.get(curState1).get(c), dfa2.get(curState2).get(c), labels1, labels2, nextLabel);
    if (nextLabel < 0) return -1;
	}
  return nextLabel;
}

public static String dfaToString(Map<Integer,Map<Integer,Integer>> dfa, int stateCount, int labelCount) {
  String output = "";
  for(int i=0; i<stateCount; i++)
    for (int c=0; c<labelCount; c++)
      if ((dfa.containsKey(i)) && (dfa.get(i).containsKey(c))) output += i + " " + dfa.get(i).get(c) + " " + c + System.getProperty("line.separator");
      else output += i + " e " + c + System.getProperty("line.separator");
  return output;
}

} 
