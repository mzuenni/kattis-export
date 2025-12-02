#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<string>> lsts;
    for(int i = 0; i < n; i++) {
      vector<string> lst;
      for(int j = 0; j < 10; j++) {
	string s;
	cin >> s;
	lst.push_back(s);
      }
      lsts.push_back(lst);
    }

    map<string, int> cnt;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < 10; j++) {
	cnt[lsts[i][j]]++;
      }
    }

    int best = 0;
    set<string> artists;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < 10; j++) {
	if(cnt[lsts[i][j]] > best) {
	  best = cnt[lsts[i][j]];
	  artists.clear();
	  artists.insert(lsts[i][j]);
	} else if(cnt[lsts[i][j]] == best) {
	  artists.insert(lsts[i][j]);
	}
      }
    }

    if(artists.size() == 1) {
      cout << *artists.begin() << endl;
      return 0;
    }

    for(int j = 0; j < 10; j++) {
      set<string> artistsover;
      int best = 0;
      map<string, int> cnti;
      for(int i = 0; i < n; i++) {
	cnti[lsts[i][j]]++;
      }
      
      for(set<string>::iterator it = artists.begin(); it != artists.end(); it++) {
	if(cnti[*it] > best) {
	  best = cnti[*it];
	  artistsover.clear();
	  artistsover.insert(*it);
	} else if(cnti[*it] == best) {
	  artistsover.insert(*it);
	}
      }

      if(artistsover.size() == 1) {
	cout << *artistsover.begin() << endl;
	return 0;
      }
      artists = artistsover;
    }
    
    cout << "tie" << endl;
    return 0;
}
