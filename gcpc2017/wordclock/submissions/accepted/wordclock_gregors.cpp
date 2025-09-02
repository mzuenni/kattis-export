#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

const int MAX_N = 21;

struct DP_Entry
{
	int row;
	int col;
	int prev;
	DP_Entry(int r = MAX_N, int c = MAX_N, int p = -1) : row(r), col(c), prev(p) {}
};

DP_Entry dp[1 << MAX_N][MAX_N];

int main()
{
	int h, w, n;
	cin >> h >> w >> n;
	vector<string> allWords(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> allWords[i];
		// word is too long
		if (allWords[i].size() > w)
		{
			cout << "impossible" << endl;
			return 0;
		}
	}

	// filter out infix words
	vector<string> words;
	for (int i = 0; i < n; ++i)
	{
		words.push_back(allWords[i]);
		for (int j = 0; j < n; ++j)
		{
			if (i == j) continue;
			if (allWords[j].find(allWords[i]) != string::npos)
			{
				words.pop_back();
				break;
			}
		}		
	}
	n = words.size();

	// compute distances between words
	int dist[words.size()][n];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int overlap = min(words[i].size(), words[j].size());
			for (; overlap > 0; overlap--)
				if (words[i].substr(words[i].size()-overlap) == words[j].substr(0,overlap))
					break;
			dist[i][j] = words[j].size() - overlap;
		}
	}

	// initialize DP
	for (int i = 0; i < n; ++i)
		dp[1 << i][i] = DP_Entry(0, words[i].size()-1, -1);
	
	// iterate over all subsets of words encoded in mask
	for (int m = 0; m < (1 << n); ++m)
	{
		// iterate over all words in mask
		for (int w1 = 0; w1 < n; ++w1)
		{
			if ((m & (1 << w1)) == 0)
				continue;
			
			// iterate over all words NOT in mask
			for (int w2 = 0; w2 < n; ++w2)
			{
				if ((m & (1 << w2)) != 0)
					continue;

				// compute end position of w2 if it is added behind w2
				int r = dp[m][w1].row;
				int c = dp[m][w1].col;
				if (c + dist[w1][w2] < w)
					c += dist[w1][w2];
				else if (r+1 < h)
				{
					c = words[w2].size()-1;
					r++;
				}
				else
					continue;

				// update if it is an improvement
				DP_Entry &cur = dp[m | (1 << w2)][w2];
				if (tie(r,c) < tie(cur.row, cur.col))
				{
					cur.row = r;
					cur.col = c;
					cur.prev = w1;
				}
			}
		}
	}

	// check if word clock can be constructed
	int last_word = -1;
	int last_mask = (1 << n) - 1;
	for (int i = 0; i < n; ++i)
	{
		if (dp[last_mask][i].col != MAX_N)
		{
			last_word = i; 
			break;
		}
	}

	if (last_word == -1)
	{
		cout << "impossible" << endl;
		return 0;
	}

	char clock[h][w];
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < w; ++j)
			clock[i][j] = 'Q';

	while (last_word != -1)
	{
		DP_Entry &last = dp[last_mask][last_word];
		int wlen = words[last_word].size();
		for (int i = 0; i < wlen; ++i)
			clock[last.row][last.col-wlen+1+i] = words[last_word][i];
		int prev_word = dp[last_mask][last_word].prev;
		last_mask ^= (1 << last_word);
		last_word = prev_word;
	}

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
			cout << clock[i][j];
		cout << endl;
	}
}


















