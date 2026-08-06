// @EXPECTED_RESULTS@: TIMELIMIT

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
     
    const int MaxLength=101;
     
    int main(){ 
      int NumberOfCases;
      long long value_M, temp_value_M, value_Z;
      long long suffix_M, suffix_Z;
      int M[MaxLength], Z[MaxLength], kk[MaxLength];
      int r;
      
      long long F[MaxLength], S[MaxLength];
      int c,n,i,j,digit,max_cont;
      long long temp, solution, k, temp_k;
	
      scanf("%d", &NumberOfCases);
      for (c = 1; c <= NumberOfCases; c++) {
        scanf("%Ld%Ld%d", &value_M, &value_Z, &r);
	value_M--;
	temp_value_M=value_M;
	
	// comute decimal representaions for M and Z
	n=0;
	do {
           n++;
           digit =(int)( temp_value_M % 10);
           M[n] = digit;
           temp_value_M /= 10;
           digit =(int)( value_Z % 10);
           Z[n] = digit;
           value_Z /= 10;
        } while( temp_value_M > 0);

	solution=0;
	for (k = 0; k <= value_M; k++) {
	  temp_k=k;
	  for (j = 1; j <= n; j++) {
	    digit =(int)( temp_k % 10);
            kk[j] = digit;
            temp_k /= 10;
	  } 
          max_cont=0;
          for (j = n; j >= 1; j--) {
	    if (kk[j]==Z[j]) max_cont++;
            else {
              if (max_cont < r) max_cont=0;
            }
          }
          if (max_cont >= r) solution++;
	}
	
        printf("%Ld\n", solution);
      }
            
    return 0;
    }
     