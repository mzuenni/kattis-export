// @EXPECTED_RESULTS@: CORRECT
#include <stdio.h>
#include <stdlib.h>

/* minimize a given dfa by a "brute force" method => quadratical complexity
 * principal approach: partition refinement
 * 1) create primal partition into two sets accepting state A and S/A
 * 2) while the partition changed in the last step
 * 3)   for all characters c in Sigma subpartition
 *
 * define input dfa as arrays as follows:
 * let Sigma = {0,1,...,k-1}, let states S = {0,1,...,n-1} then transition function
 * t: Sigma x S -> S is given by t(c,s) = dfa[k*s+c]
 * initial state is 0, only one accepting state n-2, and error state n-1
 * 
 * output dfa analogous but initial state is 0, accepting state is newN-1 and error state not explicit
*/

int* minimizeDfaBF(int k, int dfa[], int n, int* newN) {

	/* partitions is the linear concatenation of the partition sets
	 * the start and end positions of the sets are given by the descriptors
	 */
	int* partitions = malloc(2*n*sizeof(int));
	int* partitionDescriptorStart = malloc(2*n*sizeof(int));
	int* partitionDescriptorLength = malloc(2*n*sizeof(int));
	int* stateMap = malloc(2*n*sizeof(int));
	
	// the initial partition consists of two sets, A and S/A	
	int i,j,partitionCount[2];
	partitionCount[0]=2;
	for (i=0; i < n; i++) {
		stateMap[i]=0;
		partitions[i]=i;
	}
	partitions[n-2]=n-1;
	partitions[n-1]=n-2;
	stateMap[n-2]=1;
	partitionDescriptorStart[0]=0;
	partitionDescriptorLength[0]=n-1;
	partitionDescriptorStart[1]=n-1;
	partitionDescriptorLength[1]=1;
		
	int* countArray = malloc(n*sizeof(int));
	int* occurArray = malloc(n*sizeof(int));
	int* mapArray = malloc(n*sizeof(int));
	for (i=0; i < n; i++) countArray[i]=0;

	int partitionDescriptorPageSelect = 0, partitionChanged = 1, c = 0;
	while((c!=0) || partitionChanged) {

		int here = partitionDescriptorPageSelect*n;
		int there = (1-partitionDescriptorPageSelect)*n;
		if (c == 0) partitionChanged = 0;
		partitionCount[1-partitionDescriptorPageSelect] = 0;
		int nextStart = 0;

		//go through all classes of the partition
		for (i=0; i < partitionCount[partitionDescriptorPageSelect]; i++){
			int left = partitionDescriptorStart[here+i];
			int right = left+partitionDescriptorLength[here+i];
			int nextOccurence=0;

			//go through the states in the current class and record all destination classes via c
			for (j=left; j < right; j++) {
				int destClass = stateMap[here+dfa[k*partitions[here+j]+c]];
				if (countArray[destClass] == 0) {
					occurArray[nextOccurence]=destClass;
					mapArray[destClass]=partitionCount[1-partitionDescriptorPageSelect];
					partitionCount[1-partitionDescriptorPageSelect]++;
					nextOccurence++;
				}
				countArray[destClass]++;
			}

			if (nextOccurence > 1) partitionChanged = 1;
			
			//go through occurences and prepare new partition descriptors
			for (j=0; j < nextOccurence; j++) {
				partitionDescriptorStart[there+mapArray[occurArray[j]]]=nextStart;
				partitionDescriptorLength[there+mapArray[occurArray[j]]]=countArray[occurArray[j]];
				nextStart += countArray[occurArray[j]];
			}

			//go through the states in the current class again and put them into the correct partition subclasses
			for (j=left; j < right; j++) {
				int destClass = stateMap[here+dfa[k*partitions[here+j]+c]];
				partitions[there+partitionDescriptorStart[there+mapArray[destClass]]+partitionDescriptorLength[there+mapArray[destClass]]-countArray[destClass]] = partitions[here+j];
				stateMap[there+partitions[here+j]] = mapArray[destClass];
				countArray[destClass]--;
			}
		}

		partitionDescriptorPageSelect = 1-partitionDescriptorPageSelect;
		c = (c+1) % k;
	}

	//always: the first class contains the starting state, the last class the accepting state
	
	int* result = malloc(k*partitionCount[partitionDescriptorPageSelect]*sizeof(int));
	for (i=0; i<partitionCount[partitionDescriptorPageSelect]; i++)
		for (c=0; c<k; c++)
			result[k*i+c]=stateMap[
				n*partitionDescriptorPageSelect+dfa[c+
					k*partitions[
						n*partitionDescriptorPageSelect+partitionDescriptorStart[
							n*partitionDescriptorPageSelect+i
						]
					]
				]
			];

	*newN = partitionCount[partitionDescriptorPageSelect];

// 	for (i=0; i<*newN; i++) {
// 		for (c=0; c<k; c++)
// 			printf("%i ",result[k*i+c]);
// 		printf("\n");
// 	}
// 	printf("\n\n");

	free(partitions);
	free(partitionDescriptorStart);
	free(partitionDescriptorLength);
	free(stateMap);
	free(countArray);
	free(occurArray);
	free(mapArray);

	return result;
	
// 	for(i=0; i<partitionCount[partitionDescriptorPageSelect]; i++){
// 		printf("Class %i:\n",i);
// 		for(j=partitionDescriptorStart[partitionDescriptorPageSelect*n+i]; j<partitionDescriptorStart[partitionDescriptorPageSelect*n+i]+partitionDescriptorLength[partitionDescriptorPageSelect*n+i];j++){
// 			printf("%i ", partitions[partitionDescriptorPageSelect*n+j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("--------------------------------\n");
// 
}

int simultanDfs(int k, int dfa1[], int n1, int dfa2[], int n2, int node1, int node2, int labels1[], int labels2[], int nextLabel) {
	if (labels1[node1] != labels2[node2]) return -1;
	if (labels1[node1] < 0) labels1[node1]=labels2[node2]=nextLabel++; else return nextLabel;
	if ((node1==n1-1) && (node2!=n2-1)) return -1;
	if ((node1!=n1-1) && (node2==n2-1)) return -1;
	
	int c;
	for (c=0; c < k; c++) {
		nextLabel = simultanDfs(k, dfa1, n1, dfa2, n2, dfa1[k*node1+c], dfa2[k*node2+c], labels1, labels2, nextLabel);
		if (nextLabel < 0) return -1;
	}
	
	return nextLabel;
}

int minDfaEquivalence(int k, int dfa1[], int n1, int dfa2[], int n2) {
	int* labels1 = malloc(n1*sizeof(int));
	int* labels2 = malloc(n2*sizeof(int));
	
	int i;
	for (i=0; i<n1;i++) labels1[i]=-1;
	for (i=0; i<n2;i++) labels2[i]=-1;
	
	int result = simultanDfs(k, dfa1, n1, dfa2, n2, 0, 0, labels1, labels2, 0);
	
	free(labels1);
	free(labels2);
	
	if (result < 0) return 0;
	return 1;
}


int main() {

	int tc;
	scanf("%i",&tc);

	while(tc--> 0) {
		int n1,m1,k1,n2,m2,k2,i,k;
		scanf("%i %i %i %i %i %i",&m1, &n1, &k1, &m2, &n2, &k2);
		n1++;n2++;if(k1<k2) k=k2; else k=k1;
		
		int* dfa1 = malloc(n1*k*sizeof(int));
		for (i=0;i<n1*k;i++) dfa1[i]=n1-1;
		while (m1 --> 0) {
			int from, to, c;
			scanf("%i %i %i",&from, &to, &c);
			dfa1[k*from+c]=to;
		}

		int* dfa2 = malloc(n2*k*sizeof(int));
		for (i=0;i<n2*k;i++) dfa2[i]=n2-1;
		while (m2 --> 0) {
			int from, to, c;
			scanf("%i %i %i",&from, &to, &c);
			dfa2[k*from+c]=to;
		}
		
		
		int* minDfa1 = minimizeDfaBF(k, dfa1, n1, &n1);
		int* minDfa2 = minimizeDfaBF(k, dfa2, n2, &n2);
		free(dfa1);
		free(dfa2);
		
		if(minDfaEquivalence(k, minDfa1, n1, minDfa2, n2)) printf("eligible\n"); else printf("not eligible\n");
		
		free(minDfa1);
		free(minDfa2);
	}

	return 0;
}
