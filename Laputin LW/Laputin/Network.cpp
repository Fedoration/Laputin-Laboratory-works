#include <iostream>
#include "Network.h"


using namespace std;

int Network::MaxID = 0;

Network::Network() {
	id = ++MaxID;
	name = "Unknown";
	cout << "Type Network name: " << endl;
	cin.get();
	getline(cin, name);
}

string Network::GetName() { return name; }
void Network::SetName(const string& new_name) { name = new_name; }

int Network::GetId() { return id; }

void Network::SetId(int new_id) { id = new_id; }

void Network::Markup_pipe(
	unordered_map<int, Pipe>& m_pipe, unordered_map<int, CS>& m_cs){
	int cs_source_id = SelectById(m_cs, "Type source CS id(0-exit): ");
	int cs_destination_id = SelectById(m_cs, "Type destionation CS id(0-exit): ");
	int connection_pipe_id = SelectById(m_pipe, "Type connection pipe id(0-exit): ");

	if (cs_source_id != -1 && cs_destination_id != -1 && connection_pipe_id != -1) {
		if (m_pipe[connection_pipe_id].source == 0 &&
			m_pipe[connection_pipe_id].destination == 0) {

			m_pipe[connection_pipe_id].source = cs_source_id;
			m_pipe[connection_pipe_id].destination = cs_destination_id;
			selected_pipes.insert(connection_pipe_id);
			selected_css.insert(cs_source_id);
			selected_css.insert(cs_destination_id);
		}
		else {
			cout << "Pipe with id " << connection_pipe_id << " already connected" << endl;
		}
	}
	else {
		cout << "Objects weren`t found" << endl;
	}

}

void Network::Disconnect_pipe(
	unordered_map<int, Pipe>& m_pipe) {
	int p_id = SelectById(m_pipe, "Type Pipe id(0-exit): ");

	bool is_finded = false;
	for (auto i : selected_pipes) {
		if (p_id == i) {
			is_finded = true;
			break;
		}
	}

	if (p_id != -1 && is_finded) {
		for (int i = 0; i < adj_matr.size(); i++) {
			for (int j = 0; j < adj_matr[i].size(); j++) {
				if (cs_matr_pos[i] == m_pipe[p_id].source && cs_matr_pos[j] == m_pipe[p_id].destination) {
					adj_matr[i][j] = 0;
					selected_pipes.erase(p_id);
				}
			}
		}
	}
	else {
		cout << "There is no connected pipe with id" << endl;
	}
}

void Network::Create_adjacency_matrix(
	unordered_map<int, Pipe>& m_pipe){
	for (auto i : selected_css) {
		cs_matr_pos.push_back(i);
	}

	const int& m_size = cs_matr_pos.size();
	adj_matr.resize(m_size);
	for (int i = 0; i < m_size; i++) {
		adj_matr[i].resize(m_size);
		for (int j = 0; j < m_size; j++) {
			for (auto p_id : selected_pipes) {
				adj_matr[i][j] = (
					m_pipe[p_id].source == cs_matr_pos[i] && m_pipe[p_id].destination == cs_matr_pos[j]
					) ? m_pipe[p_id].get_weight() : 0;
				
				/*if (m_pipe[p_id].source == cs_matr_pos[i] && m_pipe[p_id].destination == cs_matr_pos[j]) {
					adj_matr[i][j] = m_pipe[p_id].get_weight();
				}
				else {
					adj_matr[i][j] = 0;
				}*/

			}
		}
	}
	cout << "created" << endl;
}

void Network::Print_network() {
	cout << "Pipes: " << endl;
	for (auto p : selected_pipes) {
		cout << p << endl;
	}
	cout << "\nCSs: " << endl;
	
	for (auto cs : selected_css) {
		cout << cs << endl;
	}
	
	cout << "-------------------" << endl;
	cout << "Adjacency matrix:" << endl;
	cout << "  ";
	for (int i = 0; i <= cs_matr_pos.size()-1; i++) {
		cout << cs_matr_pos[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < cs_matr_pos.size(); i++) {
		cout << cs_matr_pos[i] << " ";
		for (int j = 0; j < cs_matr_pos.size(); j++) {
			cout << adj_matr[i][j] << " ";
		}
		cout << endl;
	}
}