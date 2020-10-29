#include "header.hpp"


/* checkparse ���ÿ� �ϴ� �Լ�.
* ���� �߻� �� tm_year���� -1 */
struct tm CheckerParser::checkParseDate(string input_string) {
	time_t now_time;
	struct tm result;
	now_time = time(NULL);

	result.tm_year = -1;
	int i;
	int string_size = input_string.size();
	if (string_size != 16) {
		cout << "Invalid time format, please enter the date and time using the format \"YYYY/MM/DD hh:mm\"." << endl;
		return result;
	}
	for (i = 0; i < string_size; i++) {
		if (i == 4 || i == 7 || i == 10 || i == 13) {
			if (i == 10) {
				if (input_string[i] != ' ') {
					cout << "Invalid time format, please enter the date and time using the format \"YYYY/MM/DD hh:mm\"." << endl;
					return result;
				}
			}
			else if (i == 13) {
				if (input_string[i] != ':') {
					cout << "Invalid time format, please enter the date and time using the format \"YYYY/MM/DD hh:mm\"." << endl;
					return result;
				}
			}
			else {
				if (input_string[i] != '/') {
					cout << "Invalid time format, please enter the date and time using the format \"YYYY/MM/DD hh:mm\"." << endl;
					return result;
				}
			}
		}
		else {
			if (input_string[i] < 48 || input_string[i] > 57) {
				cout << "Invalid time format, please enter the date and time using the format \"YYYY/MM/DD hh:mm\"." << endl;
				return result;
			}
		}
	}

	//������� ���� ��� & �Ľ�
	string year;
	string mon;
	string day;
	string hour;
	string min;
	for (i = 0; i < 4; i++) {
		year.push_back(input_string[i]);
	}
	mon.push_back(input_string[5]);
	mon.push_back(input_string[6]);
	day.push_back(input_string[8]);
	day.push_back(input_string[9]);
	hour.push_back(input_string[11]);
	hour.push_back(input_string[12]);
	min.push_back(input_string[14]);
	min.push_back(input_string[15]);

	result.tm_year = stoi(year) - 1900;
	result.tm_mon = stoi(mon) - 1;
	result.tm_mday = stoi(day);
	result.tm_hour = stoi(hour);
	result.tm_min = stoi(min);
	result.tm_sec = 0;
	time_t t = mktime(&result);
	//�ṉ̀�Ģ �˻� (�׷����¿� ���� ���� �ð��� �����ų�, ���� �ð����� ũ�ٸ�)
	if (t == -1 || t > now_time) {
		result.tm_year = -1;
		cout << "Invalid date and time, please check the value and try again." << endl;
	}
	else {
		result.tm_year += 1900;
		result.tm_mon += 1;
	}
	return result;
}

/* ����ڷκ��� �Է¹��� string�� ���ڿ� �޸��θ� �����Ǿ� ������,
* �޸��� ��ġ�� �����ϰ� �������� �˻��Ͽ� ������ ������ true�� ��ȯ�ϴ� �Լ� */
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

	//�޸��� ���� ���
	if (comma_location.empty()) {
		for (i = 0; i < string_size; i++) {
			if (input_string[i] < 48 || input_string[i] > 57) {
				error = true;
				break;
			}
		}
	}
	//�޸��� ���� ���
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
		cout << "Invalid amount, please make sure the amount consists of only numbers with or without comma (range : 1 ~ 4,294,967,295)." << endl;
	}
	return error;
}

/* ���� 20�� �˻�, �յ� ���� �˻�, �Է°��ɹ��ڷ� �����Ǿ��ִ��� �˻�
* !!!�߿�!!!  ����ڷκ��� �Է� ���� �� getline(cin, str); �Լ��� ����ؾ���.
* cin ��� �� ���๮�ڳ� �ǹ��ڸ� ���������� �Է¹޴� ��찡 �־ ��� �Ұ� */
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
		cout << "Please enter valid memo name." << endl;
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

//checkMemo�� ����, �׷��� �ٸ������� ����ϴ� ��찡 �ִ� �� ���� ���Ӵϴ�.
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

//struct tm CheckerParser::parseDate(string m_date) {
//	struct tm result;
//	stringstream ss(m_date);
//	string sub;
//	vector <string> tokens;
//	while (getline(ss, sub, ' ')) {
//		tokens.push_back(sub);
//	}
//	ss = stringstream(tokens[0]); // tokens[0] = "yyyy/mm/dd"
//	vector<int>date;
//	while (getline(ss, sub, '/')) date.push_back(stoi(sub));
//	ss = stringstream(tokens[1]); // tokens[1] = "hh:mm"
//	vector<int>time;
//	while (getline(ss, sub, ':')) time.push_back(stoi(sub));
//	result.tm_year = date[0];
//	result.tm_mon = date[1];
//	result.tm_mday = date[2];
//	result.tm_hour = time[0];
//	result.tm_min = time[1];
//	return result;
//}

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