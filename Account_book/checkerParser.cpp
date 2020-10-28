#include "header.hpp"

bool CheckerParser::checkDate(string input_string) {
	
}

bool CheckerParser::checkAmount(string input_string) {
	bool error = false;
	int i;
	vector <int> comma_location;
	int string_size = input_string.size();

	for (i = 0; i < string_size; i++) {
		if (input_string[i] == ',') {
			comma_location.push_back(i);
		}
	}

	//콤마가 없을 경우
	if (comma_location.empty()) {
		for (i = 0; i < string_size; i++) {
			if (input_string[i] < 48 || input_string[i] > 57) {
				error = true;
				break;
			}
		}
	}
	//콤마가 있을 경우
	else {
		if (comma_location[0] == 0 || comma_location[0] > 3) {
			error = true;
		}
		else {
			int comma_count = comma_location.size();
			for (i = 0; i < comma_count-1; i++) {
				if (comma_location[i + 1] - comma_location[i] != 4) {
					error = true;
					break;
				}
			}
			if (string_size - comma_location.back() != 4) {
				error = true;
			}
			for (i = 0; i < string_size; i++) {
				if (!(input_string[i] == ',' || (input_string[i] > 47 && input_string[i] < 58))) {
					error = true;
					break;
				}
			}
		}
	}
	if (error) {
		cout << "금액 문법형식에 위배됩니다." << endl;
	}
	return error;
}

bool CheckerParser::checkMemo(string input_string) {
	int i;
	int string_size = input_string.size();
	bool error = false;
	if (string_size > 20 || string_size == 0) {
		error = true;
	}
	for (i = 0; i < string_size; i++) {
		if (input_string[i] < 32 || input_string[i] > 126) {
			error = true;
			break;
		}
	}
	if (input_string[0] == 32 || input_string.back() == 32) {
		error = true;
	}

	if (error) {
		cout << "Please enter valid category name." << endl;
	}
	return error;
}

bool CheckerParser::checkCategoryNumber(string input_string, int category_number) {
	int n;
	try {
		n = stoi(input_string);
	}
	catch (exception& expn) {
		cout << "Please enter a valid value." << endl;
		return true;
	}
	if (n > category_number) {
		cout << "Please enter the number blow "<< category_number+1 << endl;
		return true;
	}
	return false;
}

bool CheckerParser::checkCategoryName(string input_string) {
	int i;
	int string_size = input_string.size();
	bool error = false;
	if (string_size > 20 || string_size == 0) {
		error = true;
	}
	for (i = 0; i < string_size; i++) {
		if (input_string[i] < 32 || input_string[i] > 126) {
			error = true;
			break;
		}
	}
	if (input_string[0] == 32 || input_string.back() == 32) {
		error = true;
	}

	if (error) {
		cout << "Please enter valid category name." << endl;
	}
	return error;
}

struct tm CheckerParser::parseDate(string m_date) {
	struct tm result;
	stringstream ss(m_date);
	string sub;
	vector <string> tokens;
	while (getline(ss, sub, ' ')) {
		tokens.push_back(sub);
	}
	ss = stringstream(tokens[0]); // tokens[0] = "yyyy/mm/dd"
	vector<int>date;
	while (getline(ss, sub, '/')) date.push_back(stoi(sub));
	ss = stringstream(tokens[1]); // tokens[1] = "hh:mm"
	vector<int>time;
	while (getline(ss, sub, ':')) time.push_back(stoi(sub));
	result.tm_year = date[0];
	result.tm_mon = date[1];
	result.tm_mday = date[2];
	result.tm_hour = time[0];
	result.tm_min = time[1];
	return result;
}

unsigned int CheckerParser::parseAmount(string input_string) {
	string result;
	int i;
	int string_size = input_string.size();
	for (i = 0; i < string_size; i++) {
		if (input_string[i] != ',') {
			result.push_back(input_string[i]);
		}
	}
	return stoul(result);
}