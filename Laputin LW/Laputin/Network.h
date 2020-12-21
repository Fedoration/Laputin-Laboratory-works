#pragma once
#include <iostream>

#include <string>
#include <map>
#include <unordered_map>
#include <set>

#include "utils.h"
#include "CS.h"
#include "Pipe.h"

class Network
{
public:
	void CreateAdjMatrix(std::unordered_map<int, Pipe>& m_pipe, std::string mode);
	bool is_cycle(int v0, std::vector<std::vector<int>> matr, std::vector<int>& color);
	void dfs(int v, std::vector<std::vector<int>> matr, std::vector<bool>& visited, std::vector<int>& ans);
	void TopologicalSort();
	void ResetMatrix(std::unordered_map<int, Pipe>& m_pipes);
	int MaxFlow();
	int FindPath(std::vector<std::vector<int>>& matr, std::vector<bool> visited, int s, int t, int max_value);
	int FindMinPath();
	void AddConnection(
		std::unordered_map<int, Pipe>& m_pipe, std::unordered_map<int, CS>& m_cs);
	void Print_network();
private:
	std::set<int> selected_pipes;
	std::set<int> selected_css;
	std::vector<int> cs_matr_pos;
	std::vector<std::vector<int>> Adj_Matr;
};

