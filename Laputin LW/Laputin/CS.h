#pragma once
#include <string>
class CS
{
public:
	int id;
	static int MaxID;
	std::string name;
	int count_workshops;
	int count_running_workshops;
	int efficiency;
	CS();

	void edit_CS();
	friend std::istream& operator >> (std::istream& in, CS& cs);
	friend std::ostream& operator << (std::ostream& out, const CS& cs);
};

