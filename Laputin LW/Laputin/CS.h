#pragma once
#include <string>
#include <iostream>
#include <fstream>
class CS
{
	int id;
	std::string name;
public:
	static int MaxID;
	int count_workshops;
	int count_running_workshops;
	double efficiency;
	CS();

	int GetId() const;
	std::string GetName() const;
	void edit_CS();
	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ostream& operator << (std::ostream& out, const CS& cs);
	friend std::ifstream& operator>>(std::ifstream& fin, CS& cs);
	friend std::ofstream& operator<<(std::ofstream& fout, const CS& cs);
};

