#include "header.hpp"

CheckerParser::CheckerParser(bool f) {
	isPrint = f;
}

CheckerParser::CheckerParser() {
}

bool CheckerParser::is_Print() {
	if (isPrint) {
		return true;
	}
	else  false;
}

/* checkparse 동시에 하는 함수.
* 오류 발생 시 tm_year값이 -1 */
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

	//여기부터 정상 결과 & 파싱
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
	//의미규칙 검사 (현재 시간보다 크다면)
	if (t == -1 || t > now_time) {
		result.tm_year = -1;
		cout << "Invalid date and time, please check the value and try again." << endl;
		return result;
	}
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int year2 = stoi(year);
	int mon2 = stoi(mon)-1;
	int day2 = stoi(day);
	int hour2 = stoi(hour);
	int min2 = stoi(min);
	if (((year2 % 4) == 0) && ((year2 % 100) != 0 || (year2%400)==0)) {
		daysInMonth[1]++;
	}
	if (mon2 == -1 || day2 == 0) {
		result.tm_year = -1;
		cout << "Invalid date and time, please check the value and try again." << endl;
		return result;
	}
	if (day2 > daysInMonth[mon2]) {
		result.tm_year = -1;
		cout << "Invalid date and time, please check the value and try again." << endl;
		return result;
	}
	if (hour2 > 23 || hour2 < 0 || min2 < 0 || min2 > 59) {
		result.tm_year = -1;
		cout << "Invalid date and time, please check the value and try again." << endl;
		return result;
	}

	return result;
}

/* 사용자로부터 입력받은 string에 숫자와 콤마로만 구성되어 있으며,
* 콤마의 위치가 적절하게 쓰였는지 검사하여 오류가 있으면 true를 반환하는 함수 */
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
			for (i = 0; i < comma_count - 1; i++) {
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

/* 길이 20자 검사, 앞뒤 공백 검사, 입력가능문자로 구성되어있는지 검사
* !!!중요!!!  사용자로부터 입력 받을 때 getline(cin, str); 함수를 사용해야함.
* cin 사용 시 개행문자나 탭문자를 지워버리고 입력받는 경우가 있어서 사용 불가 */
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
	int size = input_string.size();
	if (input_string[0] == '0') {
		cout << "Please enter a valid value." << endl;
		return true;
	}
	for (int i = 0; i < size; i++) {
		if (input_string[i] < '0' || input_string[i] > '9') {
			cout << "Please enter a valid value." << endl;
			return true;
		}
	}
	int n;
	try {
		n = stoi(input_string);
	}
	catch (exception& expn) {
		cout << "Please enter a valid value." << endl;
		return true;
	}
	if (n<0 || n>category_number) {
		cout << "Please enter a valid value." << endl;
		return true;
	}
	return false;
}

//checkMemo와 동일, 그러나 다른곳에서 사용하는 경우가 있는 것 같아 놔둡니다.
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

unsigned int CheckerParser::parseAmount(string input_string) {
	string result;
	int i;
	unsigned int return_val;
	int string_size = input_string.size();
	if (input_string[0] == '0') {
		cout << "Please enter a valid value." << endl;
		return 0;
	}
	for (i = 0; i < string_size; i++) {
		if (input_string[i] != ',') {
			result.push_back(input_string[i]);
		}
	}
	try {
		return_val = stoul(result);
	}
	catch (exception& expn) {
		cout << "Invalid amount, please make sure the amount consists of only numbers with or without comma (range : 1 ~ 4,294,967,295)." << endl;
		return 0;
	}
	return return_val;
}
