#include <iostream>
#include <string>
#include <queue>
#include "Network.h"
#include "utils.h"


using namespace std;


void Network::AddConnection(
	unordered_map<int, Pipe>& m_pipe, unordered_map<int, CS>& m_cs) {

	int number_operations = GetCorrectNumber("How much connections?: ", 1u, 10000u);

	while (number_operations--) {
		int cs_source_id = SelectById(m_cs, "Type source CS id(0-exit): ");
		int cs_destination_id = SelectById(m_cs, "Type destination CS id(0-exit): ");
		int connection_pipe_id = SelectById(m_pipe, "Type connection pipe id(0-exit): ");

		if (cs_source_id != -1 && cs_destination_id != -1 && connection_pipe_id != -1) {
			m_pipe[connection_pipe_id].source = cs_source_id;
			m_pipe[connection_pipe_id].destination = cs_destination_id;
		}
		else {
			cout << "Objects weren`t found" << endl;
		}
	}
}


void Network::CreateAdjMatrix(unordered_map<int, Pipe>& m_pipe, string mode) {
	
	cs_matr_pos.resize(0);
	selected_pipes.clear();
	selected_css.clear();
	for (const auto& item : m_pipe) {
		if (item.second.source != 0 && item.second.destination != 0) {
			selected_pipes.insert(item.first);
			selected_css.insert(item.second.source);
			selected_css.insert(item.second.destination);
		}
	}

	for (const auto& station : selected_css) {
		cs_matr_pos.push_back(station);
	}

	Adj_Matr.resize(0);
	Adj_Matr.resize(cs_matr_pos.size(), vector<int>(cs_matr_pos.size()));

	for (const auto& p_id : selected_pipes) {
		Adj_Matr[FindIndexByValue(cs_matr_pos, m_pipe[p_id].source)]
				[FindIndexByValue(cs_matr_pos, m_pipe[p_id].destination)]
				= (mode == "Capacity")? m_pipe[p_id].GetCapacity() : m_pipe[p_id].GetWeight();
	}
}


bool Network::is_cycle(int v0, vector<vector<int>> matr, vector<int>& color) {
	color[v0] = 1; // Зашли в вершину
	for (int i = 0; i < matr[v0].size(); i++) {
		if (matr[v0][i] != 0) {
			if (color[i] == 0) {
				if (is_cycle(i, matr, color))
					return true;
			}
			else if (color[i] == 1) {
				return true;
			}
		}
	}
	color[v0] = 2; // Вышли из вершины
	return false;
}


void Network::dfs(int v0, std::vector<std::vector<int>> matr, std::vector<bool>& visited, std::vector<int>& ans)
{
	visited[v0] = true;
	for (int i = 0; i < matr[v0].size(); i++) {
		if (!visited[i] && matr[v0][i] != 0) {
			dfs(i, matr, visited, ans);
		}
	}
	ans.push_back(v0);

}


void Network::TopologicalSort() {
	int n = cs_matr_pos.size();
	vector<int> color(n, 0);
	vector<int> ans;
	bool cycle_found = false;
	for(int j = 0; j < n; j++)
		if (is_cycle(j, Adj_Matr, color)) {
			cout << "Cycle" << endl;
			cycle_found = true;
			break;
		}
	if (!(cycle_found)) {
		vector<bool> visited(n, false);
		for (int v = 0; v < visited.size(); v++) {
			if(!visited[v]){
				dfs(v, Adj_Matr, visited, ans);
			}
		}
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)
		{
			cout << cs_matr_pos[ans[i]] << " ";
		}
		cout << endl;
	}
}


void Network::ResetMatrix(unordered_map<int, Pipe>& m_pipes) {
	for (auto& p : m_pipes) {
		p.second.source = 0;
		p.second.destination = 0;
	}
}


int Network::MaxFlow() {
	vector<vector<int>> FlowMatrix = Adj_Matr;
	vector<bool> visited(FlowMatrix.size(), false);
	int s = GetCorrectNumber("Input source: ", 1u, (size_t)CS::MaxID);
	int t = GetCorrectNumber("Input sink: ", 1u, (size_t)CS::MaxID);
	s = s - 1;
	t = t - 1;
	for (int flow = 0;;) {
		int df = FindPath(FlowMatrix, visited, s, t, INT_MAX);
		if (df == 0) {
			return flow;
		}
		flow += df;
	}
}


int Network::FindPath(vector<vector<int>>& matr, vector<bool> visited, int u, int t, int f) {
	if (u == t) {
		return f;
	}
	visited[u] = true;
	for (int v = 0; v < visited.size(); v++) {
		if (!visited[v] && matr[u][v] > 0) {
			int df = FindPath(matr, visited, v, t, min(f, matr[u][v]));
			if (df > 0) {
				matr[u][v] -= df;
				matr[v][u] += df;
				return df;
			}
		}
	}
	return 0;
}


int Network::FindMinPath() {
	int src = GetCorrectNumber("Input source: ", 1u, (size_t)CS::MaxID);
	int dest = GetCorrectNumber("Input destination: ", 1u, (size_t)CS::MaxID);
	vector<vector<int>> matr = Adj_Matr;
	int num_vertex = matr.size();
	vector<bool> visited(num_vertex, false);
	vector<int> dist(num_vertex, INT_MAX);
	src--;
	dest--;
	dist[src] = 0;
	visited[src] = true;

	queue<int> q;
	q.push(src);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int i = 1; i < matr[v].size(); i++) {
			if (matr[v][i] && !visited[i] && dist[i] > dist[v] + matr[v][i]) {
				dist[i] = dist[v] + matr[v][i];
				q.push(i);
			}
		}
	}
	return dist[dest];
}


void Network::Print_network() {
	cout << "Pipes: " << endl;
	for (const auto& p : selected_pipes) {
		cout << p << endl;
	}
	cout << "\nCSs: " << endl;
	for (const auto& cs : selected_css) {
		cout << cs << endl;
	}
	
	cout << "-------------------" << endl;
	cout << "Adjacency matrix:" << endl;
	cout << "  ";

	for (int i = 0; i < cs_matr_pos.size(); i++) {
		cout << cs_matr_pos[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < cs_matr_pos.size(); i++) {
		cout << cs_matr_pos[i] << " ";
		for (int j = 0; j < cs_matr_pos.size(); j++) {
			cout << Adj_Matr[i][j] << "\t";
		}
		cout << endl;
	}
}