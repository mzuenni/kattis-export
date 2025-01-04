#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 2, 100'000);
    v.newline();
    v.read_integer("s", 0, 0); 
    v.space(); 
    for(int i = 1; i<n; i++) {
        int t = v.read_integer("x", -200'000, 200'000);
        if(i != n-1) v.space();
    }
    v.newline(); 
}
