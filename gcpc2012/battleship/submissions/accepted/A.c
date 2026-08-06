// Problem A: Battleship
// Author: Stefan Pszczolkowski
// Expected Result: Correct
// @EXPECTED_RESULTS@: CORRECT

#include <stdio.h>
#include <stdlib.h>

int table1[30][30], table2[30][30];

void maketables(int width, int height) {
  int i, w, h;
  int *ptr2mat1, *ptr2mat2;
  
  //+3 is just to be able to store \r\n\0
  char *line = (char *) malloc((width + 3) * sizeof(char));
  
  ptr2mat1 = &table1[0][0];
  ptr2mat2 = &table2[0][0];
  
  for (i = 0; i < 900; i++) {
    *ptr2mat1 = *ptr2mat2 = 0;
    ptr2mat1++;
    ptr2mat2++;
  }
  
  for (h = 0; h < height; h++) {
    ptr2mat1 = &table1[h][0];
    scanf("%s\n",line);
    for (w = 0; w < width; w++) {
      if (line[w] == '#')
	*ptr2mat1 = 1;
      else if(line[w] == '_')
	*ptr2mat1 = 0;
      else
	fprintf(stderr,"Input error, read '%c' (%d)\n", line[w], line[w]);
      
      ptr2mat1++;
    }
  }
  
  for (h = 0; h < height; h++) {
    ptr2mat2 = &table2[h][0];
    scanf("%s\n",line);
    for (w = 0; w < width; w++) {
      if (line[w] == '#')
	*ptr2mat2 = 1;
      else if(line[w] == '_')
	*ptr2mat2 = 0;
      else
	fprintf(stderr,"Input error, read '%c' (%d)\n", line[w], line[w]);
      
      ptr2mat2++;
    }
  }
}

int hit(int x, int y, int player) {
  if (player == 1) {
    if (table2[y][x] == 1) { //player 1 hits player 2
      table2[y][x] = 0;
      return 1;
    }
  } else if (player == 2) { 
    if (table1[y][x] == 1) { //player 2 hits player 1
      table1[y][x] = 0;
      return 1;
    }
  } else {
    fprintf(stderr,"Player error\n");
  }
  
  //current player misses
  return 0;
}

int check_result() {
  int *ptr2mat1, *ptr2mat2;
  int sum1, sum2, i;
  
  ptr2mat1 = &table1[0][0];
  ptr2mat2 = &table2[0][0];
  
  sum1 = sum2 = 0;
  
  for (i = 0; i < 900; i++) {
    sum1 += *ptr2mat1;
    sum2 += *ptr2mat2;
    ptr2mat1++;
    ptr2mat2++;
  }
  
  if ((sum1 == 0) && (sum2 == 0)) //draw
    return 0;
  else if (sum1 == 0) //player 2 wins
    return 2;
  else if (sum2 == 0) //player 1 wins
    return 1;
  else //still in play
    return -1;
}

int main(int argc, char **argv) {
  int tests, shots, t, w, h, n, x, y, result, shot;
  int current_player;
  
  scanf("%d\n",&tests);
  
  for (t = 0; t < tests; t++) {
    current_player = 1;
    scanf("%d %d %d\n",&w, &h, &shots);
    maketables(w, h);
    for (n = 0; n < shots; n++) {
      scanf("%d %d\n",&x, &y);
      shot = hit(x, h - y - 1, current_player);
      result = check_result();
      
      // still in play
      if (result == -1) {
	if (shot == 0) //miss, so change current player
	  current_player = (current_player == 1 ? 2 : 1);
      // seems that player one wins, then give last chance to player 2, but only if we have shots left
      } else if (result == 1) {
	 if (n < shots - 1) {
	   do {
	     scanf("%d %d\n",&x, &y);
             shot = hit(x, h - y - 1, 2);
	     n++;
	   } while ((shot == 1) && (n < shots));
	 
	   //we have to update the results to account for this last chance
	   result = check_result();
	 }
	 break;
      //player two wins or it's a draw, so finish
      } else if ((result == 0) || (result == 2)) {
	break;
      }
    }
    
    if (result == 1) 
      printf("player one wins\n");
    else if(result == 2) 
      printf("player two wins\n");
    else 
      printf("draw\n");
    
    //Read the unnecessary shots
    while (n < shots - 1) {
      scanf("%d %d\n",&x, &y);
      n++;
    }
  }
  return 0;
}
