#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dp[101][201];
vector<int> adj[201];
int inf = 987654321;

void init(vector< vector<int> >edge_list)
{
	for (int i = 0; i < 201; i++)
	{
		adj[i].clear();
	}
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 201; j++)
		{
			dp[i][j] = inf;
		}
	}
	for (auto e : edge_list)
	{
		adj[e[0]].push_back(e[1]);
		adj[e[1]].push_back(e[0]);
	}
}

int solution(int n, int m, vector< vector<int> >edge_list, int k, vector<int>gps_log)
{
	int answer;
	init(edge_list);
	dp[0][gps_log[0]] = 0;
	for (int i = 1; i < k-1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			int add = (gps_log[i] == j ? 0 : 1);
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + add);
			for (int p : adj[j])
			{
				dp[i][j] = min(dp[i][j], dp[i - 1][p] + add);
			}
		}
	}
	answer = inf;
	for (int p : adj[gps_log.back()])
	{
		answer = min(answer, dp[k - 2][p]);
	}
	if (answer > (inf / 2)) answer = -1;
	return answer;
}

int main()
{
	int n, m, k;
	cin >> n >> m;
	vector< vector<int> >edge_list;
	vector<int>edge;
	int num1, num2;
	for (int i = 0; i < m; i++)
	{
		cin >> num1 >> num2;
		edge.push_back(num1);
		edge.push_back(num2);
		edge_list.push_back(edge);
		edge.clear();
	}
	cin >> k;
	vector<int>gps_log;
	for (int i = 0; i < k; i++)
	{
		cin >> num1;
		gps_log.push_back(num1);
	}
	int answer = solution(n, m, edge_list, k, gps_log);
	cout << answer;
	return 0;
}