#pragma once
#include <iostream>

#include <string>
#include <map>
#include <unordered_map>

#include "utils.h"
#include "CS.h"
#include "Pipe.h"

class Network
{
public:
	Network();
	std::string GetName();
	void SetName(const std::string& new_name);
	void Markup_pipes(std::unordered_map<int, Pipe>& m_pipe, std::unordered_map<int, CS>& m_cs);
private:
	std::string name;
};

