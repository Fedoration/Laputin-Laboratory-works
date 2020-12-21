#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Pipe
{
	int id;
	int length;
	int diameter;
	bool is_broken;
public:
	static int MaxID;
	int source, destination;
	Pipe();

	int GetId() const;
	bool GetStatus() const;
	int GetWeight() const;
	int GetCapacity() const;
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::ifstream& operator>>(std::ifstream& fin, Pipe& p);
	friend std::ofstream& operator<<(std::ofstream& fout, const Pipe& p);
	void change_Pipe_status();
	
};

