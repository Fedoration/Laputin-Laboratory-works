#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "CS.h"

void PrintMenu();
void Print_secondary_menu(std::string clause1, std::string clause2);
void Print_network_main_menu();

template <typename T>
T GetCorrectNumber(std::string text, T min, T max)
{
	T parameter;
	std::cout << text;
	while (!(std::cin >> parameter) || parameter < min || parameter > max) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << text;
	}
	return parameter;
}

template <typename T>
int SelectById(std::unordered_map<int, T> m, std::string text) {
	while (true) {
		unsigned int id_to_find = GetCorrectNumber(text, 0u, 10000u);

		if (id_to_find == 0) {
			break;
		}

		if (m.count(id_to_find) != 0) {
			return id_to_find;
		}
	}
	return -1;
}