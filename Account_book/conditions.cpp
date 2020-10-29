#include "header.hpp"

Conditions::Conditions() {
	on_period = false;
	on_ie = false;
	on_memo = false;
	on_category = false;
	is_income = false;
	keyword = "";
	category_number = 0;
	category_name = "";
}

short Conditions::addPeriodCondition() {
	string input_string;
	CheckerParser cp;
	while (1) {
		cout << "\n@ Search condition : Time period @" << endl;
		cout << "Enter time period using format \"YYYY/MM/DD hh:mm~YYYY/MM/DD hh:mm\"\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return -1;
		}
		if (input_string.size() != 33 || input_string[16] != '~') {
			cout << "Invalid date and time." << endl;
		}
		else {
			int i;
			string f;
			string t;
			for (i = 0; i < 16; i++) {
				f.push_back(input_string[i]);
			}
			for (i = 17; i < 33; i++) {
				t.push_back(input_string[i]);
			}
			from = cp.checkParseDate(f);
			to = cp.checkParseDate(t);
			if (from.tm_year != -1 && to.tm_year != -1) {
				on_period = true;
				break;
			}
		}
	}
	
	return printCurrentConditions();
}
short Conditions::addIeCondition() {
	string input_string;
	while (1) {
		cout << "\n@ Search condition : Income/Expense @" << endl;
		cout << "1. Income\n2. Expense\n\n";
		cout << "Select type of transaction (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return -1;
		}
		else if (input_string == "1") {
			on_ie = true;
			is_income = true;
			break;
		}
		else if (input_string == "2") {
			on_ie = true;
			is_income = false;
			break;
		}
		else {
			cout << "Please enter a valid value" << endl;
		}
	}
	return printCurrentConditions();
}
short Conditions::addMemoCondition() {
	string input_string;
	CheckerParser cp;
	while (1) {
		cout << "\n@ Search condition : Memo @" << endl;
		cout << "Search transactions that contain the text...(q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return -1;
		}
		if (!cp.checkMemo(input_string)) {
			on_memo = true;
			keyword = input_string;
			break;
		}
	}
	return printCurrentConditions();
}
short Conditions::addCategoryCondition(CategoryManage& category_manager) {
	string input_string;
	CheckerParser cp;
	while (1) {
		cout << "\n@ Search condition : Category @" << endl;
		category_manager.printCategoryList();
		cout << "\nSelect a category (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return -1;
		}
		if (!cp.checkCategoryNumber(input_string, category_manager.getCategorySize())) {
			category_number = stoi(input_string);
			category_name = category_manager.getIndexedCategory(category_number);
			break;
		}
	}
	return printCurrentConditions();
}

short Conditions::resetConditions() {
	string input_string;
	CheckerParser cp;
	while (1) {
		cout << "\n@ Search condition : Reset field @" << endl;
		cout << "1. Date and Time" << endl;
		cout << "2. Income/Expense" << endl;
		cout << "3. Memo" << endl;
		cout << "4. Category" << endl;
		cout << "\nSelect field to reset (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return -1;
		}
		else if (input_string == "1") {
			on_period = false;
			break;
		}
		else if (input_string == "2") {
			on_ie = false;
			break;
		}
		else if (input_string == "3") {
			on_memo = false;
			break;
		}
		else if (input_string == "4") {
			on_category = false;
			break;
		}
		else {
			cout << "Please enter a valid value" << endl;
		}
	}
	return printCurrentConditions();
}

short Conditions::printCurrentConditions() {
	string input_string;
	cout << "\n@ Current condition @" << endl;
	//���� ��� part
	if (on_period) {
		cout << "Time period: ";
		printf("%04d/%02d/%02d %02d:%02d~%04d/%02d/%02d %02d:%02d\n", from.tm_year, from.tm_mon, from.tm_mday, from.tm_hour, from.tm_min, to.tm_year, to.tm_mon, to.tm_mday, to.tm_hour, to.tm_min);
	}
	if (on_ie) {
		cout << "Income/Expense: ";
		if (is_income) {
			cout << "Income" << endl;
		}
		else {
			cout << "Expense" << endl;
		}
	}
	if (on_memo) {
		cout << "Memo keyword: " << keyword << endl;
	}
	if (on_category) {
		cout << "Category: " << category_name << endl;
	}
	cout << "\n1.Add another condition" << endl;
	cout << "2.Print search result\n" << endl;
	
	while (1) {
		cout << "Select action (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return -1;
		}
		else if (input_string == "1") {
			return 1;
		}
		else if (input_string == "2") {
			return 0;
		}
		else {
			cout << "Please enter a valid value." << endl;
		}
	}
}