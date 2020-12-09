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
	Network();
	static int MaxID;
	std::string GetName();
	void SetName(const std::string& new_name);
	int GetId();
	void SetId(int new_id);
	void Markup_pipe(
		std::unordered_map<int, Pipe>& m_pipe, std::unordered_map<int, CS>& m_cs);
	void Disconnect_pipe(std::unordered_map<int, Pipe>& m_pipe);
	void Create_adjacency_matrix(
		std::unordered_map<int, Pipe>& m_pipe);
	void Print_network();
private:
	std::string name;
	int id;
	std::set<int> selected_pipes;
	std::set<int> selected_css;
	std::vector<int> cs_matr_pos;
	std::vector<std::vector<int>> adj_matr;
};

