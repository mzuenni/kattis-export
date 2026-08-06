#include <cstdio>
#include <cstdlib>
#include <cstring>

bool ac = true;
int tc, p;
char buffer[100];

bool scanCoords(char *s){
  char b[10];
  for(int i=0; i<2; ++i){
    int c, t;
    c = sscanf(buffer + p, "%2s%n", b, &t);
    p += t;
    if(c != 1){
      printf("tc %d: cannot parse coordinate: %s\n", tc, buffer);
      return ac = false;
    }
    if(strlen(b) != 1){
      printf("tc %d: cannot parse coordinate: %s\n", tc, buffer);
      return ac = false;
    }
    s[i] = b[0];
  }
  return true;
}

int main(int argc, char **argv){
  if(argc != 4){
    fprintf(stderr, "wrong number of arguments %d\n", argc);
    return -1;
  }
  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[2], "r");
  FILE *ref = fopen(argv[3], "r");
  if(input == NULL || output == NULL || ref == NULL){
    printf("could not open file (in: %d out: %d ref: %d)\n", input != NULL, output != NULL, ref != NULL);
    return -1;
  }
  int n;
  if (fscanf(input, "%d", &n)==EOF) {
    printf("could not parse input\n");
    return -1;
  }
  for(tc=1; tc<=n; ++tc){
    char b[100];
    char rp[5];
    if (fscanf(input, "%2s %2s %2s %2s", &rp[0], &rp[1], &rp[2], &rp[3])==EOF) {
      printf("could not parse input\n");
      return -1;
    }
    if (not fgets(buffer, sizeof(buffer), output)) {
      printf("No answer for testcase %d\n", tc);
      ac=false;
      break;
    }
    if (not fgets(b, sizeof(b), ref)) {
      printf("could not parse judge answer\n");
      return -1;
    }
    if(strcmp(b, "Impossible\n") == 0){
      if(strcmp(buffer, "Impossible\n") != 0){
        printf("tc %d: Impossible (%s)\n", tc, buffer);
      }
      continue;
    }
    
    int m, c, t;
    p = 0;
    c = sscanf(buffer + p, "%d%n", &m, &t);
    p += t;
    if(c != 1){
      printf("tc %d: number of moves not given: %s\n", tc, buffer);
      ac = false;
      continue;
    }
    if(m > 4){
      printf("tc %d: too many moves: %d (%s)\n", tc, m, buffer);
      ac = false;
      continue;
    }
    
    char p[2];
    if (not scanCoords(p)) continue;
    if(p[0] != rp[0] || p[1] != rp[1]){
      printf("tc %d: start position not matching (%c %c) vs (%c %c)\n", tc, rp[0], rp[1], p[0], p[1]);
      ac = false;
      continue;
    }
    for(int i=0; i<m; ++i){
      char q[2];
      if (not scanCoords(q)) break;
      if(q[0] < 'A' || q[0] > 'H' || q[1] < '1' || q[1] > '8'){
        printf("tc %d: coordinate not valid (%c %c) (%s)\n", tc, q[0], q[1], buffer);
        ac = false;
        break;
      }
      if(q[0] == p[0] && q[1] == p[1]){
        printf("tc %d: non-move move not allowed (%s)\n", tc, buffer);
        ac = false;
        break;
      }
      if(q[0] + q[1] != p[0] + p[1] && q[0] - q[1] != p[0] - p[1]){
        printf("tc %d: move (%c %c) - (%c %c) not valid (%s)\n", tc, p[0], p[1], q[0], q[1], buffer);
        ac = false;
        break;
      }
      p[0] = q[0];
      p[1] = q[1];
    }
    if(p[0] != rp[2] || p[1] != rp[3]){
      printf("tc %d: end position not matching (%c %c) vs (%c %c)\n", tc, rp[0], rp[1], p[0], p[1]);
      ac = false;
      break;
    }
  }
  if(!ac){
    printf("output is wrong\n");
  }
}
