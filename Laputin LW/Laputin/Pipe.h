#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Pipe
{
	
public:
	int id;
	static int MaxID;
	int length;
	int diameter;
	bool is_broken;

	int source, destination;
	Pipe();

	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	void SavePipe(std::ofstream& fout)const;
	void change_Pipe_status();
	int get_weight();
};

