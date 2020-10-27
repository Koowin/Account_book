#include "header.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <list>
#include <algorithm>

using namespace std::chrono;

/* note
* : i use vector for record list, list for category list
* : havent run the codes yet, need debugging afterwards
* 
* assumptions:
* assumption 1:
* all functions used to check validity return bool type : true if valid, false if invalid
* struct tm * checkDate(string date_and_time) : return pointer to a tm object if valid, nullptr if invalid
* bool checkMoney(string income_or_expense) // my assumption
* unsigned int checkAmount(string amount) //not needed when searching
* bool checkMemo(string memo) // used bool instead of string. is thr any reason to return a string?
* bool checkCategoryNumber(int category_num) // how do we use this?
* 
* assumption 2:
* no empty string
* no spaces in front, back, or in between
* no one is going to press \t, \n or other special key during input (only ascii 32~126)
* one character only for menu inputs // e.g.: possible inputs in search menu consist of only { 'q', '1', '2', '3', '4', '5' }
* 
* assumption 3:
* not using gotoxy(), thus reprint everything (menu) after getting invalid input
* # 7.5.1
* 
* assumption 4:
* recordList is already sorted by date and time
* 
* assumption 5:
* Record의 멤버 변수 category_number의 범위는 [1,category_table.size()-1]이다.
* 
* opinions:
* : struct tm의 멤버 변수를 가지고 시간 클래스를 따로 만들면 연산자 오버로딩으로 시간 선후비교 가능
* : record 클래스도 연산자 오버로딩으로 시간 순으로 정렬 가능 
* : add data, check data, etc. : 날짜 및 시간 의미검사 있는지 확인할 것 (현재보다 미래인 시간 x)
* : please refer 기획서, and refer mockup for UI
* : checkMemo, checkAmount, checkMoney, checkDate...: pls make sure to check all the details (spaces, characters, etc.)
* : check : transaction/category limit, as in 기획서
*/

void searchRecord(vector <Record> & records, list <string> & category_table) { // main menu 3

	struct tm* period = nullptr; // to store array for start and end time 
	// default : from earliest date to latest date
	//period = new struct tm[2];
	//period[0] = records[0].date;
	//period[1] = records[records.size() - 1].date; 

	string* transaction_type = nullptr; // default : all types
	string* memo = nullptr; // default: all memo 
	int* category = nullptr; // default: all categories

	int menu_choice;
	do {
		menu_choice = searchMenu();
		switch (menu_choice) {
		case 1: // search by period
		{
			menu_choice = searchTime(period); // -1 to main menu
			break;
		}
		case 2: // search by type of transaction (Income, Expense)
		{
			transaction_type = searchType();
			if (*transaction_type == "q") menu_choice = -1;
			break;
		}
		case 3: // search by memo
		{
			memo = searchMemo(); // return string * if valid, return pointer to "q" to main menu
			if (*memo == "q") menu_choice = -1;
			break;
		}
		case 4: // search by category
		{
			category = searchCategory(category_table); // return int * if valid, return pointer to -1 to main menu
			if (*category == -1) menu_choice = -1;
			break;
		} 
		case 5: // reset field
		{
			int field = resetFieldMenu();
			if (field == -1) menu_choice = -1;
			else {
				switch (field) {
				case 1:
					period = nullptr;
					break;
				case 2:
					transaction_type = nullptr;
					break;
				case 3:
					memo = nullptr;
					break;
				case 4:
					category = nullptr;
					break;
				}
			}
			break;
		}
		}
		//current state - choose action
		if (menu_choice != -1) {
			while (true) {
				printCurrent(period, transaction_type, memo, category, category_table);
				cout << "1. Add another condition" << endl;
				cout << "2. Print search result" << endl;
				cout << endl;
				cout << "Select action (q:return to main menu)" << endl;
				cout << "> "; 
				string action_input;
				getline(cin, action_input);
				cout << endl;
				if (action_input.length() == 1) {
					if (action_input == "q") {
						menu_choice = -1;
						break;
					}
					try {
						int action = stoi(action_input);
						if (action == 1) break; // break from this infinity loop and continue with the outer loop 
						else if (action == 2){ // get search result
							vector<int> result = getSearchResult(records, period, transaction_type, memo, category, category_table);
							if (result.size() == 0) {
								cout << "- None of the records satisfies the conditions given. -" << endl;
								cout << endl;
							} else {
								//printSearchResult
							}
						}
					}
					catch (const invalid_argument& excp) { // cant parse to int
					}
				}
				cout << "Please enter a valid value." << endl; //error message
			}
		}

	} while (menu_choice != -1);
	return; // return to main menu if menu_choice == -1
}
vector<int> getSearchResult(vector <Record>& records, struct tm* period, string* transaction_type, string* memo, int* category, list<string>& category_table) {
	vector<int>vec;
	vector<Record>::iterator record_it;
	int idx;
	for (record_it = records.begin(), idx = 0; record_it != records.end(); record_it++, idx++) {
		//1check time range
		struct tm start = (period == nullptr) ? records.begin()->date : period[0]; //if null, earliest date
		struct tm end = (period == nullptr) ? records.end()->date : period[1]; // if null, latest date
		if (compareTime(start, record_it->date) >= 0 && compareTime(record_it->date, end) >= 0) {
			//2. check type of transaction
			bool isFindingIncome = (*transaction_type == "Income") ? true : false;
			if (transaction_type == nullptr || isFindingIncome == record_it->is_income) {
				//3. check memo - 5.3
				/*검색어와 메모 모두 내부의 공백들을 전부 없앤 상태로
				* 알파벳 대/소문자를 구분하지 않으면서
				* 검색어가 메모의 부분 문자열이면 매치된 것이다*/
				string find_memo; 
				string original_memo;
				if (memo != nullptr) {
					//keyword 
					find_memo = *memo;
					find_memo.erase(remove_if(find_memo.begin(), find_memo.end(), isspace), find_memo.end()); // remove all space from the string
					for_each(find_memo.begin(), find_memo.end(), [](char& c) { c = tolower(c); }); // to lower case 
					//original memo
					original_memo = record_it->memo;
					original_memo.erase(remove(original_memo.begin(), original_memo.end(), isspace), original_memo.end()); // remove all space
					for_each(original_memo.begin(), original_memo.end(), [](char& c) {c = tolower(c); }); // to lower case 
				}
				if (memo == nullptr || original_memo.find(find_memo) != original_memo.npos) { // memo default || find_memo is a substring of original_memo
					//4. check category
					if (category == nullptr || *category == record_it->category_number) { // default category || record with the same category is found
						vec.push_back(idx);
					}
				}
				
			}
		}
	}
	return vec;
}
void printCurrent(struct tm* period, string* transaction_type, string* memo, int* category, list<string> & category_table) {
	cout << "@ Current condition @" << endl;
	if (period != nullptr) {
		cout << "Time period : ";
		char start_c[20] = "";
		char end_c[20] = "";
		strftime(start_c, 20, "%Y/%m/%d %R", &period[0]);
		strftime(end_c, 20, "%Y/%m/%d %R", &period[1]);
		cout << start_c << " ~ " << end_c << endl;
	}
	if (transaction_type != nullptr)
		cout << "Income/Expense : " << *transaction_type << endl;
	if (memo != nullptr)
		cout << "Memo : " << *memo << endl;;
	if (category != nullptr) {
		list<string>::iterator category_it = find(category_table.begin(), category_table.end(), *category);
		if (category_it != category_table.end())
			cout << "Category : " << *category_it << endl;
	}
	if (period == nullptr && transaction_type == nullptr && memo == nullptr && category == nullptr)
		cout << "- None -" << endl;
	cout << endl;
}
int resetFieldMenu() {
	while (true) {
		cout << "@ Reset Field @" << endl;
		cout << "1. Date and Time" << endl;
		cout << "2. Income/Expense" << endl;
		cout << "3. Memo" << endl;
		cout << "4. Category" << endl;
		cout << endl;
		cout << "Select field to reset (q:return to main menu)" << endl;
		cout << "> ";
		string field_input;
		getline(cin, field_input);
		cout << endl;
		if (field_input.length() == 1) { 
			if (field_input == "q") {
				return -1;
			}
			try {
				int field = stoi(field_input);
				if (field > 4 || field < 1) {} // out of range
				else return field;// valid 
			}
			catch (const invalid_argument& excp) { // cant parse to int
			}
		}
		cout << "Please enter a valid value." << endl; //error message
	}
}
int* searchCategory(list<string>&category_table) {
	while (true) { // take input until valid input or 'q' is received
		int i = 1;
		list <string>::iterator iter;

		cout << "@ Category @" << endl;
		for (iter = category_table.begin(); iter != category_table.end(); iter++) {
			cout << i << ". " << *iter << endl;
			i++;
		}
		cout << endl;
		cout << "Select a category (q: return to main menu)" << endl;
		cout << "> ";
		string category_input;
		getline(cin, category_input);
		if (category_input.length() == 1 && category_input == "q") {
			int a = -1;
			return &a; // back to main menu
		}
		//7.4.4 - '인자가 없거나' 문법 형식에 위배되면, ‘Please enter a valid value’라는 오류 메시지를 출력하고 사용자에게 재입력을 요구합니다.
		if (category_input.find_first_not_of(' ') == category_input.npos) { //str.empty() // if string is empty or contains only spaces
			cout << "Please enter a valid value." << endl;
			continue;
		}
		try {
			int category = stoi(category_input);
			if (category < 1 || category > category_table.size()) { // out of range [1,tablesize]
				cout << "Please enter a valid value." << endl;
				continue;
			}
			return &category;
		}
		catch (const invalid_argument& excp) { // can't parse string
			cout << "Please enter a valid value." << endl;
			continue;
		}
	}
}

string* searchMemo() {
	while (true) { // take input until valid input or 'q' is received
		cout << "@ Memo @" << endl;
		cout << "Search transactions that contains the text..." << endl;
		cout << "(q: return to main menu)" << endl;
		cout << "> ";
		string memo_input;
		cout << endl;
		getline(cin, memo_input);
		if (memo_input.length() == 1 && memo_input == "q") return &memo_input; // back to main menu
		if (checkMemo(memo_input)) return &memo_input; // I dont know why checkMemo return string... so i use bool instead
		else { cout << "Invalid input, please try again." << endl; }
	}
}
string* searchType() {
	while (true) { // take input until valid input or 'q' is received
		cout << "@ Income/Expense @" << endl;
		cout << "1. Income" << endl;
		cout << "2. Expense" << endl;
		cout << endl;
		cout << "Select type of transaction (q: return to main menu)" << endl;
		cout << "> ";
		string type_input;
		getline(cin, type_input);
		cout << endl;
		if (type_input.length() != 1) { cout << "Please enter a valid value." << endl; continue; } 
		if (type_input == "q") return &type_input; // back to main menu
		try {
			int type_num = stoi(type_input);
			if (type_num > 2 || type_num < 1) { cout << "Please enter a valid value." << endl; continue; } // number out of range
			else {
				string returnstr = (type_num == 1) ? "Income" : "Expense"; 
				return &returnstr; // valid
			}
		}
		catch (const invalid_argument& excp) {
			cout << "Please enter a valid value. " << endl;
			continue;
		}
	}
}
int compareTime(struct tm start, struct tm end) { // 의미 규칙, check if end is after start
	if (start.tm_year < end.tm_year || start.tm_mon < end.tm_mon || start.tm_mday < end.tm_mday || start.tm_hour < end.tm_hour || start.tm_min < end.tm_min) return 1;
	if (start.tm_year == end.tm_year || start.tm_mon == end.tm_mon || start.tm_mday == end.tm_mday || start.tm_hour == end.tm_hour || start.tm_min == end.tm_min) return 0;
	return -1;
}
int searchTime(struct tm * period) {
	while (true) { // take input until valid input or 'q' is received
		cout << "@ Time period @" << endl;
		cout << "Enter time period using format \"YYYY/MM/DD hh:mm~YYYY/MM/DD hh:mm\"" << endl;
		cout << "(q:return to main menu)" << endl;
		cout << "> ";
		string datetimeinput;
		getline(cin, datetimeinput);
		cout << endl;
		if (datetimeinput.length() == 1 && datetimeinput == "q") return -1; // return to main menu
		vector <string> tokens;
		stringstream ss(datetimeinput);
		string sub;
		while (getline(ss, sub, '~')) {
			tokens.push_back(sub);
		}
		if (tokens.size() == 2 && tokens[0].length() == 16 && tokens[1].length() == 16) {
			struct tm * start = checkDate(tokens[0]); //check validity of starting date and time
			struct tm * end = checkDate(tokens[1]); // check validity of ending date and time
			if (start != nullptr && end != nullptr) {
				if (compareTime(*start, *end) >= 0) { // end >= start
					struct tm result[2] = { *start, *end };
					period = result;
					return 1; //valid 
				}
				else { cout << "Invalid date and time." << endl; continue; }; // not following 의미규칙
			}
			else { cout << "Invalid date and time." << endl; continue; }  // invalid date and time, im not checking which of them is wrong
		}
		else { cout << "Invalid date and time." << endl; continue; } // invalid input : not following YYYY/MM/DD hh:mm~YYYY/MM/DD hh:mm format (at '~')
	}
}
int searchMenu() { 
	while (true) { 
		cout << "@ Search a transaction @" << endl;
		cout << "1. Date and Time" << endl;
		cout << "2. Income/Expense" << endl;
		cout << "3. Memo" << endl;
		cout << "4. Category" << endl;
		cout << "5. Reset conditiion (by field)" << endl;
		cout << endl;
		cout << "Select field (q:return to main menu)" << endl;
		cout << "> ";
		string choice;
		getline(cin, choice);
		cout << endl;
		if (choice.length() != 1) continue; // 7.4 - 문법적으로 올바른 키 입력 문자열은 길이가 1인 문자열입니다.
		if (choice == "q") return -1; // back to main menu
		try {
			int menu_choice = stoi(choice);
			if (menu_choice > 5 || menu_choice < 1) continue; // number out of range // 7.4 - "비정상 결과: 별도의 오류 메시지는 출력되지 않으며 다시 입력을 기다립니다."
			else return menu_choice; // valid 
		}
		catch (const invalid_argument& excp) {
			continue;
		}
	}
}