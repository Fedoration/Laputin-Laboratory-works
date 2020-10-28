#pragma once
#include <iostream>
#include <string>

class Pipe
{
	
public:
	int id;
	static int MaxID;
	double length;
	int diameter;
	bool is_broken;
	Pipe();

	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	void change_Pipe_status();
};

