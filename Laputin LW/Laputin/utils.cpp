#include "utils.h"

using namespace std;

void PrintMenu() {
	cout << "-------------------\n"
		<< "1. Input new Pipe/CS" << "\n"
		<< "2. View all objects" << "\n"
		<< "3. Edit Pipe/CS" << "\n"
		<< "4. Delete Pipe/CS" << "\n"
		<< "5. Pipe Filter" << "\n"
		<< "6. CS Filter" << "\n"
		<< "7. Batch editing of pipes" << "\n"
		<< "8. Save to file" << "\n"
		<< "9. Load from file" << "\n"
		<< "10. Gaz Transport Network" << "\n"
		<< "0. Exit" << "\n"
		<< "-------------------" << endl;;
}

void Print_secondary_menu(string clause1, string clause2) {
	cout << "-------------------\n"
		<< "0. Back" << "\n"
		<< "1. " << clause1 << "\n"
		<< "2. " << clause2 << "\n"
		<< "-------------------" << endl;
}

void Print_network_main_menu() {
	cout << "-------------------\n"
		<< "0. Back" << "\n"
		<< "1. Edit Gaz Transport Network" << "\n"
		<< "2. Topological Sort" << "\n"
		<< "3. Reset Network" << "\n"
		<< "4. _____________" << "\n"
		<< "5. Print Gaz Transport Network" << "\n"
		<< "-------------------" << endl;
}

int FindIndexByValue(vector<int>& v, int val) {
	int n = 0;
	for (auto i : v) {
		if (i == val) {
			return n;
		}
		n++;
	}
	return -1;
}