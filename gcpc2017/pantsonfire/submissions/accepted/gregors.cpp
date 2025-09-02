#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

const int MAX_C = 200;
bool isWorse[MAX_C][MAX_C];
map<string,int> id;
int id_cnt = 0;

int getID(string s)
{
	if(id.find(s) == id.end())
		id[s] = id_cnt++;
	return id[s];
}

bool readFact(int &a, int &b)
{
	string fact;
	getline(cin, fact);
	int idx = fact.find(" are worse than ");
	if (idx != -1)
	{
		a = getID(fact.substr(0, idx));
		b = getID(fact.substr(idx + 16));
		return true;
	}
	else
	{
		a = getID(fact.substr(0, fact.find(" are the worst")));
		b = -1;
		return false;
	}
}

int main()
{
	int n,m;
	cin >> n >> m;
	char c;
	scanf("%c", &c);

	int a,b;
	for (int i = 0; i < n; ++i)
	{
		if (readFact(a,b))
			isWorse[a][b] = true;
		else
		{
			for (int j = 0; j < MAX_C; ++j)
				if (j != a)
					isWorse[a][j] = true;
		}
	}

	for (int k = 0; k < MAX_C; ++k)
		for (int i = 0; i < MAX_C; ++i)
			for (int j = 0; j < MAX_C; ++j)
				if (isWorse[i][k] && isWorse[k][j])
					isWorse[i][j] = true;
	
	for (int i = 0; i < m; ++i)
	{
		if (readFact(a,b))
		{
			if (isWorse[a][b])
				cout << "Fact" << endl;
			else if (isWorse[b][a])
				cout << "Alternative Fact" << endl;
			else
				cout << "Pants on Fire" << endl;
		}
		else
		{
			bool isFact = true;
			bool isAlternativeFact = false;
			for (int j = 0; j < MAX_C; ++j)
			{
				if (j == a)
					continue;
				if (!isWorse[a][j])
					isFact = false;
				if (isWorse[j][a])
					isAlternativeFact = true;
			}
			if (isFact)
				cout << "Fact" << endl;
			else if (isAlternativeFact)
				cout << "Alternative Fact" << endl;
			else
				cout << "Pants on Fire" << endl;
		}
	}
}

