#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//void initialize(int n, std::vector<int>& parent, std::vector<int>& size) {
void initialize(int n, int* parent, int* size) {
	for (int i = 0; i <= n; ++i) {
		parent[i] = -1;
		size[i] = 1;
	}
}

int find(int* parent, int u) {
	return (parent[u] < 0) ? u : parent[u] = find(parent, parent[u]);
}

void uniComps(int* parent,int* s, int& numOfComps, int u, int v) {
	int root_u = find(parent, u);
	int root_v = find(parent, v);
	if (root_u != root_v) {
		if (s[root_u] > s[root_v])
			std::swap(root_u, root_v);
		s[root_v] += s[root_u];
		parent[root_u] = root_v;
		numOfComps--;
	}
}
 
int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	int n, m, q;
	fin >> n >> m >> q;
	//std::cin >> n >> m >> q;

	int numOfComps = n;
	int* parent = new int[n + 1];
	int* s = new int[n + 1];

	std::vector<std::pair<int, int>> edges(m + 1);
	for (int i = 0; i < m; ++i) {
		fin >> edges[i].first >> edges[i].second;
		//std::cin >> edges[i].first >> edges[i].second;
		edges[i].first -= 1;
		edges[i].second -= 1;
	}

	// std::vector<int>earthquakes(q + 1);
	int* earthquakes = new int[q + 1];
	std::vector<bool> isDestroyed(m, false);
	for (int i = 0; i < q; ++i) {
		fin >> earthquakes[i];
		//std::cin >> earthquakes[i];
		earthquakes[i] -= 1; 
		isDestroyed[earthquakes[i]] = true;
	}

	initialize(n, parent, s);    
	std::string result(q, '0');

	for (int i = 0; i < m; ++i) {
		if (!isDestroyed[i]) {
			uniComps(parent, s, numOfComps, edges[i].first, edges[i].second);
		}
	}

	for (int i = q - 1; i >= 0; --i) {
		int edge_index = earthquakes[i];
		if (numOfComps == 1) {
			result[i] = '1';
		}
		uniComps(parent, s, numOfComps, edges[edge_index].first, edges[edge_index].second);
	}

	fout << result << std::endl;
	//std::cout << result << std::endl;
	// std::cout << parent[edges[5].first] << parent[edges[5].second];


	delete[] parent;
	delete[] s;
	delete[] earthquakes;
	return 0;
}