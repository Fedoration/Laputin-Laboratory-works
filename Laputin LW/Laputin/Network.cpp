#include <iostream>
#include "Network.h"


using namespace std;

Network::Network() {
	name = "Unknown";
	cout << "Type Network name: " << endl;
	cin.get();
	getline(cin, name);
}

string Network::GetName() { return name; }
void Network::SetName(const string& new_name) { name = new_name; }

void Network::Markup_pipes(unordered_map<int, Pipe>& m_pipe, unordered_map<int, CS>& m_cs) {
	cout << "Type source (cs ID): ";

}