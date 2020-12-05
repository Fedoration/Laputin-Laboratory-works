#pragma once
#include <string>
#include <iostream>
#include <fstream>
class CS
{
public:
	int id;
	static int MaxID;
	std::string name;
	int count_workshops;
	int count_running_workshops;
	double efficiency;
	CS();

	void edit_CS();
	void SaveCS(std::ofstream& fout)const;
	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ostream& operator << (std::ostream& out, const CS& cs);
};

