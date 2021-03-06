#include <math.h>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

#include "Pipe.h"
#include "CS.h"
#include "Network.h"
#include "utils.h"


using namespace std;


/*FILTER*/

template<class T, typename T_param>
using Filter = bool(*)(const T & obj, T_param param);

template<class T, typename T_param>
set<int> FindObjectsByFilter(const unordered_map<int, T>& m, Filter<T, T_param> f, T_param param) {
	
	set <int> result;
	for (const auto& item : m) {
		if (f(item.second, param))
			result.insert(item.first);
	}
	return result;
}


template <class T>
bool CheckByID(const T& p, unsigned int param) {
	return p.GetId() == param;
}

bool CheckByIsBroken(const Pipe& p, bool param) {
	return p.GetStatus() == param;
}

bool CheckByName(const CS& cs, string param) {
	return cs.GetName() == param;
}

bool CheckByPercentOfWorkshops(const CS& cs, double param) {
	double percentage_of_number_workshops = 1.0 - cs.count_running_workshops / (double)cs.count_workshops;
	return (abs(percentage_of_number_workshops - param / 100.0) < 0.0001);
}

void EditingPipes(unordered_map<int, Pipe>& m) {

	int answer;
	while (true) {
		
		Print_secondary_menu("By ID", "By is broken status");
		answer = GetCorrectNumber("Your choice (0-2): ", 0, 2);
		
		if (answer == 1) {
			while (true) {
				int choice_id = GetCorrectNumber("Input id (0-exit): ", 0, Pipe::MaxID);
				if (choice_id == 0) {
					break;
				}
				else {
					if (m.count(choice_id) != 0) {
						m[choice_id].change_Pipe_status();
					}
				}
			}
		}
		else if (answer == 2) {
			bool is_broken_status_to_find;
			is_broken_status_to_find = GetCorrectNumber("Is broken? [yes-1/no-0]: ", false, true);
			for (int i : FindObjectsByFilter(m, CheckByIsBroken, is_broken_status_to_find)) {
				m[i].change_Pipe_status();
			}
		}
		else {
			break;
		}
	}
}

vector<int>  CreateBatchCSs(unordered_map<int, CS>& m) {
	int mycapacity = GetCorrectNumber("How much CSs do u want to add: ", 1u, m.size());
	vector<int> result(mycapacity);
	for (auto& i : result) {
		i = GetCorrectNumber("Type CS id: ", 1u, m.size());
	}
	return result;
}

void SaveToFile(ofstream& fout, const unordered_map<int, Pipe>& Pipes, const unordered_map<int, CS>& CSs)
{
	fout << Pipes.size() << endl;
	fout << CSs.size() << endl;

	if (Pipes.size() != 0) {
		for (const auto& item : Pipes) {
			fout << item.second;
		}
	}

	if (CSs.size() != 0) {
		for (const auto& item : CSs) {
			fout << item.second;
		}
	}

	fout << Pipe::MaxID << endl;
	fout << CS::MaxID << endl;
}


void LoadFromFile(ifstream& fin, unordered_map<int, Pipe>& Pipes, unordered_map<int, CS>& CSs)
{
	int number_of_pipes;
	int number_of_CSs;
	fin >> number_of_pipes;
	fin >> number_of_CSs;
	

	if (number_of_pipes > 0 or number_of_CSs > 0) {
		
		Pipes.clear();
		CSs.clear();

		while (number_of_pipes--) {
			Pipe p;
			fin >> p;
			Pipes[p.GetId()] = p;
		}

		CSs.clear();
		while (number_of_CSs--) {
			CS cs;
			fin >> cs;
			CSs[cs.GetId()] = cs;
		}

		fin >> Pipe::MaxID;
		fin >> CS::MaxID;
	}

}


int main()
{
	unordered_map<int, Pipe> Pipes;
	unordered_map<int, CS> CSs;
	Network Netw;

	while (true) {

		PrintMenu();
		int choice = GetCorrectNumber("Your choice (0-10): ", 0, 10);
		cout << '\n';
		switch (choice) 
		{
		case 1: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice1 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice1 == 1){
					
					int id = Pipe::MaxID + 1;
					Pipes.emplace(id, Pipe());
					cin >> Pipes[id];

				} else if(choice1 == 2){
					
					int id = CS::MaxID + 1;
					CSs.emplace(id, CS());
					cin >> CSs[id];

				} else if(choice1 == 0){
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}				
			}
			break;
		}
		case 2: {
			if (Pipes.size() != 0) {
				for (const auto& item: Pipes) {
					cout << item.second << endl;
				}
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}

			if (CSs.size() != 0) {
				for (const auto& item: CSs) {
					cout << item.second << endl;
				}
			}
			else {
				cout << "You haven't added any compressor stations yet" << endl;
			}
			break;
		}
		case 3: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice3 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice3 == 1) {
					if (Pipes.size() != 0) {
						int selected_id = GetCorrectNumber("Type Pipe id: ", 1u, 10000u);
						if (Pipes.count(selected_id) != 0) {
							Pipes[selected_id].change_Pipe_status();
						}
						else {
							cout << "There is no pipe with id: " << selected_id << endl;
						}
					}
					else {
						cout << "You haven't added any pipes yet" << endl;
					}
				}
				else if (choice3 == 2) {
					if (CSs.size() != 0) {
						int selected_id = GetCorrectNumber("Type CS id: ", 1u, 10000u);
						if (CSs.count(selected_id) != 0) {
							CSs[selected_id].edit_CS();
						}
						else {
							cout << "There is no cs with id: " << selected_id << endl;
						}
					}
					else {
						cout << "You haven't added any compressor stations yet" << endl;
					}
				}
				else if (choice3 == 0) {
					cout << '\n';
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 4: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice1 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice1 == 1) {
					if (Pipes.size() != 0) {
						DeletePipeCS(Pipes);
					}
					else {
						cout << "You haven't added any pipes yet" << endl;
					}
				}
				else if (choice1 == 2) {
					if (CSs.size() != 0) {
						unsigned int cs_id;
						DeletePipeCS(CSs, cs_id);
						for (auto& item : Pipes) {
							if (item.second.source == cs_id || item.second.destination == cs_id) {
								item.second.source = 0;
								item.second.destination = 0;
							}
						}
					}
					else {
						cout << "You haven't added any compressor stations yet" << endl;
					}
				}
				else if (choice1 == 0) {
					cout << '\n';
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 5: {
			while (true) {
				Print_secondary_menu("Find by id", "Find by status is broken");
				int choice5 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice5 == 1) {
					unsigned int id_to_find;
					id_to_find = GetCorrectNumber("Type id: ", 0u, 10000u);
					for (int i : FindObjectsByFilter(Pipes, CheckByID, id_to_find)) {
						cout << Pipes[i] << endl;
					}
				}
				else if (choice5 == 2) {
					bool is_broken_status_to_find;
					is_broken_status_to_find = GetCorrectNumber("Is broken? [yes-1/no-0]: ", false, true);
					for (int i : FindObjectsByFilter(Pipes, CheckByIsBroken, is_broken_status_to_find)) {
						cout << Pipes[i] << endl;
					}
				}
				else if (choice5 == 0) {
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 6: {
			while (true) {
				Print_secondary_menu("Find by name", "Find by percent of idle workshops");
				int choice6 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice6 == 1) {
					string name_to_find;
					cout << "Type cs name: ";
					cin.get();
					getline(cin, name_to_find);
					for (int i : FindObjectsByFilter(CSs, CheckByName, name_to_find)) {
						cout << CSs[i] << endl;
					}
				}
				else if (choice6 == 2) {
					double percentage_to_find;
					percentage_to_find = GetCorrectNumber("Type percentage(0-100%): ", 0.0, 100.0);
					for (int i : FindObjectsByFilter(CSs, CheckByPercentOfWorkshops, percentage_to_find)) {
						cout << CSs[i] << endl;
					}
				}
				else if (choice6 == 0) {
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				} 
			}
			break;
		}
		case 7: {
			if (Pipes.size() != 0) {
				EditingPipes(Pipes);
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}
			break;
		}
		case 8: {
			ofstream fout;
			fout.open("data.txt", ios::out);
			if (fout.is_open())
			{
				SaveToFile(fout, Pipes, CSs);
				fout.close();
			}
			break;
		}
		case 9: {
			ifstream fin;
			fin.open("data.txt", ios::in);
			if (fin.is_open()) {
				LoadFromFile(fin, Pipes, CSs);
				fin.close();
			}
			break;
		}
		case 10: {
			while (true) {
				Print_network_main_menu();
				int choice10 = GetCorrectNumber("Your choice (0-5): ", 0, 5);
				if (choice10 == 1) {
					Netw.AddConnection(Pipes, CSs);
					Netw.CreateAdjMatrix(Pipes, "Weigth");
				} 
				else if(choice10 == 2) {
					Netw.CreateAdjMatrix(Pipes, "Weigth");
					Netw.TopologicalSort();
				}
				else if (choice10 == 3) {
					Netw.ResetMatrix(Pipes);
					Netw.CreateAdjMatrix(Pipes, "Weigth");
				}
				else if (choice10 == 4) {
					Netw.CreateAdjMatrix(Pipes, "Capacity");
					Netw.Print_network();
					int result = Netw.MaxFlow();
					cout << "Result: " << result << endl;
				}
				else if (choice10 == 5) {
					Netw.CreateAdjMatrix(Pipes, "Weigth");
					Netw.Print_network();
					int result = Netw.FindMinPath();
					cout << "Result: " << result << endl;
				}
				else if (choice10 == 6) {
					Netw.CreateAdjMatrix(Pipes, "Weigth");
					Netw.Print_network();
				}
				else {
					break;
				}
			}

			break;
		}
		case 0: {
			cout << "Goodbye" << endl;
			return 0;
		}
		default: {
			cout << "Wrong action, please type (0-10)" << endl;
		}
		}
	}

	return 0;	
}


/*
��� ����� �������� � �������?
GTN_adjacency - ��� ������� ����������

*/