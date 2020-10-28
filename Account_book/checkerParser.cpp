#include "header.hpp"

bool CheckerParser::checkDate(string m_date) {
	date = parseDate(m_date);
	if (date.tm_year == -1 || date.tm_mon == -1 || date.tm_mday == -1 || date.tm_hour == -1 || date.tm_min == -1) {
		cout << "Invalid time format, "
			<< "please enter the date and time using the format. "
			<< "(YYYY/MM/DD hh:mm) \n" << endl;
		return true;
	}
	else if ((date.tm_year < 1970) || (date.tm_mon < 1 || date.tm_mon>12) || (date.tm_mday < 1 || date.tm_mday>31) && (date.tm_hour < -1 || date.tm_hour>23) || (date.tm_min < -1 || date.tm_min>59)) {
		cout << "Invalid date and time, please check the value and try again.\n" << endl;
		return true;
	}
	else
		return false;
}

bool CheckerParser::checkAmount(string amount) {
	unsigned int c_amount;
	c_amount = parseAmount(amount);
	if (c_amount > 4294967295 || c_amount < 1) {
		cout << "Invalid amount, please make sure"
			<< " the amount consists of only numbers with or without comma "
			<< "(range: 1 ~ 4,294,967,295) \n" << endl;
		return true;
	}
	else {
		return false;
	}
}

bool CheckerParser::checkMemo(string memo) {
	if (memo.length() > 20 || memo.length() < 0) {
		cout << "Invalid memo, please try again.\n" << endl;
		return true;
	}
	else
		return false;
}

bool CheckerParser::checkCategoryNumber(string, int category_number) {
	if (category_number > (sizeof(recordList->category_number)/sizeof(int)) || category_number < 1) {
		cout << "Please enter a valid category number. \n" << endl;
		return true;
	}
	else
		return false;
}

bool CheckerParser::checkCategoryName(string category_name) {
	char check_category[40];
	bool check_category_name = false;
	list <Category>::iterator iter;

	strcpy_s(check_category, category_name.c_str());		// 2번째 조건을 위한 변환

	for (iter = category.begin(); iter != category.end(); iter++) {	// 3번째 조건
		if (category_name.compare(iter->get_cname()) == 0)
			check_category_name = true;
		else
			check_category_name = false;
	}

	if (category_name.length() < 0 || category_name.length() > 20) // 길이가 0미만, 20초과할 떄
		return 1;
	else if (check_category[0] == ' ' || check_category[category_name.length() - 1] == ' ') // 입력 변수의 맨앞이나 뒤에 공백이 존재할 때
		return 1;
	else if (check_category_name == false)	// 입력가능문자가 들어있지 않을 때
		return 1;
	else
		return 0;
}

struct tm CheckerParser::parseDate(string m_date) {
	string token, date_date, date_time, date_year, date_month, date_day, date_hour, date_min;
	int classify_date = 0;
	int classify_date_date = 0;
	int classify_time = 0;
	int a = 0;

	istringstream iss_divide_date(m_date);

	while (getline(iss_divide_date, token, ' ')) {	// 날짜와 시간을 공백을 기준으로 분리
		if (classify_date == 0) {
			date_date = token;
			classify_date++;
		}
		else if (classify_date == 1) {
			date_time = token;
			classify_date++;
		}
	}

	istringstream iss_date(date_date);

	while (getline(iss_date, token, '/')) { // 날짜를 '/'를 기준으로 년/월/일로 분리
		if (classify_date_date == 0) {
			date_year = token;
			classify_date_date++;
		}
		else if (classify_date_date == 1) {
			date_month = token;
			classify_date_date++;
		}
		else if (classify_date_date == 2) {
			date_day = token;
			classify_date_date++;
		}
	}

	istringstream iss_time(date_time);

	while (getline(iss_time, token, ':')) { // 시간을 ':'를 기준으로 시/분으로 분리
		if (classify_time == 0) {
			date_hour = token;
			classify_time++;
		}
		else if (classify_time == 1) {
			date_min = token;
			classify_time++;
		}
	}

	date.tm_year = stoi(date_year);
	date.tm_mon = stoi(date_month);
	date.tm_mday = stoi(date_day);
	date.tm_hour = stoi(date_hour);
	date.tm_min = stoi(date_min);

	return date;
}

unsigned int CheckerParser::parseAmount(string amount) {
	string amount_value[4];
	string token;
	int classify_amount = 0;
	int changed_amount[4];
	unsigned int total_amount = 0;

	istringstream iss(amount);

	while (getline(iss, token, ',')) {	// 입력 값을 ','를 기준으로 분할
		if (classify_amount == 0) {
			amount_value[classify_amount] = token;
			classify_amount++;
		}
		else if (classify_amount == 1) {
			amount_value[classify_amount] = token;
			classify_amount++;
		}
		else if (classify_amount == 2) {
			amount_value[classify_amount] = token;
			classify_amount++;
		}
		else if (classify_amount == 3) {
			amount_value[classify_amount] = token;
			classify_amount++;
		}
		else
			classify_amount++;
	}

	for (int i = 0; i < classify_amount; i++) { // string값을 int형으로 변환후 int 배열에 저장
		changed_amount[i] = stoi(amount_value[i]);
	}

	if (classify_amount == 1) {
		total_amount = changed_amount[0];
	}
	else if (classify_amount == 2) {
		total_amount = (changed_amount[0] * 1000) + changed_amount[1];
	}
	else if (classify_amount == 3) {
		total_amount = (changed_amount[0] * 1000000) + (changed_amount[1] * 1000) + changed_amount[2];
	}
	else if (classify_amount == 4) {
		total_amount = (changed_amount[0] * 1000000000) + (changed_amount[1] * 1000000) + (changed_amount[2] * 1000) + changed_amount[3];
	}

	return total_amount;
}