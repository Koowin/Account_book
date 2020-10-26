#include "header.hpp"


int main() {
	list <Record> record_list;
	list <string> category_table;
	initFiles();
	/*
	ifstream in_category("Category.txt");
	if (!in_category.is_open()) {
		//cout << "Category.txt not open" << endl;
		ofstream out_category("Category.txt");

		string default_category[] = { "Bills", "Entertainment", "Food", "House Rent", "Transpoertation" };

		for (auto s : default_category) {
			out_category << s << endl;
		}

		cout << "Category.txt is created." << endl;
		//cout << endl;
	}
	else {
		// cout << "Category.txt is opened normally." << endl;
		//cout << endl;
	}
	*/

	int num = -1;
	while (true) {
		cout << "@ Main menu @" << endl;
		cout << "1. Add a transaction" << endl;
		cout << "2. View all transactions" << endl;
		cout << "3. Search/Modify/Delete a transaction" << endl;
		cout << "4. Manage category" << endl;
		cout << "5. Quit" << endl;
		cout << "Choice: ";
		/*
		// take input as string
		string str;
		getline(cin, str);
		str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) { //trim left
			return !std::isspace(ch);
			}));
		str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) { //trim right
			return !std::isspace(ch);
			}).base(), str.end());
		if (!str.empty() && find_if(str.begin(), str.end(), [](unsigned char c) { return !isdigit(c); }) == str.end()) //parse string to int
			num = stoi(str);
		if (str.find_first_not_of(' ') == str.npos) { //str.empty() // if string is empty or contains only spaces
			cout << "empty or only spaces (' ' or '\t')" << endl;
		}
		if (num == -1) {
			cout << "string can't be parsed to integer";
			cout << "trimmed string: " << '#' << str << '#' << endl;
		}
		*/

		//take input as integer, assuming only valid inputs are received
		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
		{
			cout << "Add a transaction" << endl;
			break;
		}
		case 2:
			cout << "View all transactions" << endl;
			break;
		case 3:
			cout << "Search/Modify/Delete a transaction" << endl;
			break;
		case 4:
			cout << "Manage category" << endl;
			break;
		case 5:
			cout << "Goodbye" << endl;
			return 0;
		}

		cout << endl;
	}

	return 0;
}