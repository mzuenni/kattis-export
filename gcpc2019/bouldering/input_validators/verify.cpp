#include <bits/stdc++.h>


using namespace std;

int main(){
	int h,w,r,s; cin >> h >> w >> r >> s;
	int field[h][w];
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			char c; cin >> c;
			if (c != '.')
				field[h-1-i][j] = c-'0';
			else
				field[h-1-i][j] = 0;
		}
	}

    bool foundmax = false;
    for (int y = h-1; y >= 0; y--) {
        for (int x = 0; x < w; x++) {
            if (field[y][x] != 0) {
                if (foundmax) {
                    cout << "No unique maximal hold.";
                    return 1;
                } else {
                    foundmax = true;
                }
            }
        }
        if (foundmax) {
            break;
        }
    }

    bool foundmin = false;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (field[y][x] != 0) {
                if (foundmin) {
                    cout << "No unique minimal hold.";
                    return 1;
                } else {
                    foundmin = true;
                }
            }
        }
        if (foundmin) {
            break;
        }
    }

    int numholds = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (field[y][x] != 0) {
                numholds++;
            }
        }
    }
    if (numholds < 2) {
    	cout << "Only " << numholds << " holds, needs at least 2.";
    	return 1;
    }

	return 42;
}
