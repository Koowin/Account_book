#include "header.hpp"

void RecordManage::printAllRecordList(CategoryManage& category_manager) {
	list <Record>::iterator iter;
	list <Record>::iterator end = record_list.end();
	system("cls");
	printf("Date\t\tTime\tIn\tAmount\t\tMemo\t\t\tCategory\n");
	printf("--------------------------------------------------------------------------------------------\n");

	for (iter = record_list.begin(); iter != end; iter++) {

		printf("%04d/%02d/%02d\t%02d:%02d", iter->get_date().tm_year+1900, iter->get_date().tm_mon+1, iter->get_date().tm_mday, iter->get_date().tm_hour, iter->get_date().tm_min);

		printf("\t%d\t%-10u\t%-20s\t", iter->get_isincome(), iter->get_amount(), (iter->get_memo()).c_str());
		printf("%-20s\n", (category_manager.getIndexedCategory(iter->get_category_number())).c_str());
	}
	cout << "\nEnter any string to continue...\n";
	string a;
	getline(cin, a);
}

void RecordManage::printSelectedRecordList(CategoryManage& category_manager, vector <int> selected_index) {
	int i = 0;

}

bool RecordManage::addRecord(CategoryManage& category_manager) {
	class CheckerParser cp;
	string input_string;
	bool flag = true;

	struct tm date;
	bool is_income;
	unsigned int amount;
	string memo;
	int category_number;


	//날짜 입력받는 부분
	while (1) {
		if (flag) {
			system("cls");
			cout << "@ Add a transaction @" << endl;
		}
		cout << "\nEnter the date and time  format:YYYY/MM/DD hh:mm\n(q:return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}

		date = cp.checkParseDate(input_string);
		//정상 입력 시
		if (date.tm_year != -1) {
			break;
		}
		else {
			flag = false;
		}
		//비정상 입력 시 오류 문구 출력 후 반복
	}

	//수입/지출 입력받는 부분
	flag = true;
	while (1) {
		if (flag) {
			system("cls");
			cout << "@ Add a transaction @" << endl;
			cout << "1.Income" << endl;
			cout << "2.Expense" << endl << endl;
		}
		cout << "Select type of transaction (q:return to main menu)" << endl << "> ";

		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}
		//정상 입력 시
		else if (input_string == "1" || input_string == "2") {
			if (input_string == "1") {
				is_income = true;
				break;
			}
			else {
				is_income = false;
				break;
			}
			flag = false;
		}
		//비정상 입력 시
		else {
			cout << "Please enter a valid value." << endl;
			cout << endl;
			flag = false;
		}
	}

	//금액 입력 받는 부분
	flag = true;
	while (1) {
		if (flag) {
			system("cls");
			cout << "@ Add a transaction @" << endl;
		}
		cout << "\nEnter the amount (q: return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}

		//정상 입력 시
		if (!cp.checkAmount(input_string)) {
			amount = cp.parseAmount(input_string);
			if (amount == 0) {
				flag = false;
			}
			else {
				break;
			}
		}
		//비정상 입력 시 오류 문구 출력하고 반복
		/*else {
			cout << "Please enter a valid value." << endl;
			flag = false;
		}*/
	}

	//메모 입력 받는 부분
	flag = true;
	while (1) {
		if (flag) {
			system("cls");
			cout << "@ Add a transaction @" << endl;
		}
		cout << "\nEnter the memo (q: return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}

		//정상 입력 시
		if (!cp.checkMemo(input_string)) {
			memo = input_string;
			break;
		}
		else {
			flag = false;
		}
		//비정상 입력 시 오류 문구 출력하고 반복
	}

	//카테고리 번호 입력 받는 부분
	flag = true;
	while (1) {
		if (flag) {
			system("cls");
			cout << "\n@ Add a transaction @" << endl;
			category_manager.printCategoryList();
		}
		cout << "\nSelect a category (q:return to main menu)" << endl << "> ";
		getline(cin, input_string);

		if (input_string == "q") {
			return true;
		}
		if (!cp.checkCategoryNumber(input_string, category_manager.getCategorySize())) {
			category_number = stoi(input_string);
			break;
		}
		else {
			flag = false;
		}
	}

	//저장 확인 물어보는 부분
	cout << "\n@ Add a transaction @" << endl;
	printf("- Date and Time: %04d/%02d/%02d %02d:%02d\n", date.tm_year+1900, date.tm_mon+1, date.tm_mday, date.tm_hour, date.tm_min);
	cout << "- Income/Expense: ";
	if (is_income) {
		cout << "Income" << endl;
	}
	else {
		cout << "Expense" << endl;
	}
	cout << "- Amount: " << amount << endl;
	cout << "- Memo: " << memo << endl;
	cout << "- Category: " << category_manager.getIndexedCategory(category_number) << endl;
	cout << "\nConfirm new transaction? (type 'No' to cancel)\n> ";
	getline(cin, input_string);

	if (input_string == "No") {
		return true;
	}
	else {
		//index 찾아서 넣기
		list <Record>::iterator iter = record_list.begin();
		list <Record>::iterator end_of_list = record_list.end();

		for (; iter != end_of_list; iter++) {
			struct tm d = iter->get_date();
			if (compare(date, d) == 1) {
				break;
			}
		}

		if (iter == end_of_list) {
			record_list.push_back(Record(date, is_income, amount, memo, category_number));
		}
		else {
			record_list.insert(iter, Record(date, is_income, amount, memo, category_number));
		}

		return false;
	}
}

int RecordManage::getRecordListSize() {
	return record_list.size();
}

list <Record>::iterator RecordManage::get_first() {
	return record_list.begin();
}
list <Record>::iterator RecordManage::get_end() {
	return record_list.end();
}

void RecordManage::init_add(Record r) {
	record_list.push_back(r);
}

Record RecordManage::getRecord() {
	Record r = record_list.front();
	record_list.pop_front();
	return r;
}
