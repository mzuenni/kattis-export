//code from MarkusTLE, translated to C
#include <iostream>
#include <stdio.h>
#include <list>

using namespace std;

#define byte asdf
typedef unsigned char byte;


byte N;
// each permutation is hashed (function code()) and its status can be read from the following array.
byte* status;	// holds 0 for the one and only permutation, -2 for permutations that have been enqueued, and -1 for permutations that have not been enqueued yet.
const int powersOfTen [9] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
		100000000 };

/**
 * Only use the first N-1 digits -- the last one is immediately determined since we have a permutation. This saves a lot of memory. (We need 87 MB instead of 876 MB.)
 * @param arr
 * @return
 */
int comp(byte* arr) {
	int code = 0;
	for (int i = 0; i < N-1; i++) {
		code += powersOfTen[i]*arr[i];
	}
	return code;
}
	

int minBFS(byte* ing) {
	int code = comp(ing);
	if (status[code] == 2)
		return 0;	// this should only happen when the one and only permutation is the input.

	list<byte*> permQ ;
	list<byte*> permQNext;
	list<byte*> canBeReused;	// this avoids new allocations to save memory 
	permQ.push_back(ing);
	status[code] = 1;	// enqueued.
	int currDepth = 0;
	
//		int numReused = 0;
	do {
		while (!permQ.empty()) {
			byte* perm = permQ.front();
			permQ.pop_front();
			byte* shifted;
			if (!canBeReused.empty()) {
				shifted = canBeReused.front();
				canBeReused.pop_front();
			}
			else
				shifted = new byte[N];
			for (int i = 0; i < N; i++) {	// note: i == 0 => A empty.

				for (int j = i; j < N; j++) {
					if (j == 0)	// j == 0 => i == 0. Therefore, A and B are empty and nothing changes.
						continue;
					const int nJ = N-j;
					const int iJ = i-j;

					for (int k = j; k <= N; k++) {
						if ((j == k) && ((i == j) || (k == N)))	// if this is the case, C is empty and either B or D are empty, thus nothing changes.
							continue;
						const int kJ = k-j;
						int pos;
						for (pos = j; pos < k; pos++)
							shifted[pos-j] = perm[pos];
						for (pos = 0; pos < i; pos++)
							shifted[kJ+pos] = perm[pos];
						for (pos = k; pos < N; pos++)
							shifted[pos+iJ] = perm[pos];
						for (pos = i; pos < j; pos++)
							shifted[nJ+pos] = perm[pos];
//							System.out.println("i="+i+", j="+j+", k="+k);
//							System.out.println(Arrays.toString(shifted));
						int codeShifted = comp(shifted);
						
						if (status[codeShifted] == 0) {
							permQNext.push_back(shifted);
							status[codeShifted] = 1;	// this indicates that this value is enqueued and thus we do not need to compute it again.
							// since we enqueued it, we (usually) need a new array.
							if (!canBeReused.empty()) {
								shifted = canBeReused.front();
								canBeReused.pop_front();
//									numReused++;
							}
							else
								shifted = new byte[N];
						}
						else if (status[codeShifted] == 2) {
//								System.out.println("Num reused = "+numReused);
							return currDepth+1;
						}
					}
				}
			}
			canBeReused.push_back(perm);
		}
		list<byte*> tmp = permQ;
		permQ = permQNext;
		permQNext = tmp;
		currDepth++;
	}
	while (true);
}
	

	
int main() {
 	std::cout.sync_with_stdio(false);
 	std::cin.sync_with_stdio(false);

 	int tmp;
 	cin >> tmp;
 	N = (byte) tmp;

	byte* ing = new byte[N];
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		ing[i] = (byte)(tmp-1);
	}

	status = new byte[987654322];	// ends with 2, not 1! important!
	std::fill(status, status+987654322, 0); 	// all not initialized
	byte* theOneAndOnly = new byte[N];
	for (byte i = 0; i < N; i++) {
		theOneAndOnly[i] = i;
	}
	status[comp(theOneAndOnly)] = 2;

	int min = minBFS(ing);
	cout << min << endl;
	return 0;

}
