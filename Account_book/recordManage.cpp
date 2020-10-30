#include "header.hpp"

void RecordManage::searchMenu(CategoryManage& category_manager) {
	Conditions cd;

	string input_string;
	int selected_menu;
	bool search_start = false;
	while (1) {
		cout << "\n@ Search a transaction @" << endl;
		cout << "1. Date and Time" << endl;
		cout << "2. Income/Expense" << endl;
		cout << "3. Memo" << endl;
		cout << "4. Category " << endl;
		cout << "5. Reset conditions (by field)" << endl << endl;

		cout << "Select field (q:return to main menu)\n> ";
	
		bool flag = true;
		while (flag) {
			getline(cin, input_string);
			try {
				selected_menu = stoi(input_string);
				flag = false;
			}
			catch (const exception& expn) {
				cout << "Please enter a valid value." << endl;
			}
		}

		if (input_string == "q") {
			break;
		}
		if (selected_menu > 5 || selected_menu < 1) {
			cout << "Please enter a valid value" << endl;
		}
		else {
			short n;
			switch (selected_menu) {
			case 1:
				//기간 조건 추가
				n = cd.addPeriodCondition();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
				}
				break;
			case 2:
				//수입, 지출 조건 추가
				n = cd.addIeCondition();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
				}
				break;
			case 3:
				//메모 키워드 조건 추가
				n = cd.addMemoCondition();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
				}
				break;
			case 4:
				//카테고리 조건 추가
				n = cd.addCategoryCondition(category_manager);
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
				}
				break;
			case 5:
				//조건 초기화
				n = cd.resetConditions();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
				}
				break;
			}
			if (search_start) {
				//조건 맞게 출력 시작
				cout << "조건에 맞는 목록 출력" << endl;
				vector <int> result = searchRecords(cd, category_manager);

				while (1) {
					//수정 삭제 입력받기
					cout << "\n@ Manage transaction @" << endl;
					cout << "1. Edit" << endl;
					cout << "2. Remove\n" << endl;
					cout << "Select action (q:return to main menu)\n> ";
					getline(cin, input_string);
					if (input_string == "q") {
						return;
					}
					else if (input_string == "1") {
						modifyRecordList(result);
						return;
					}
					else if (input_string == "2") {
						deleteRecordList(result);
						return;
					}
					else {
						cout << "Please enter a valid value" << endl;
					}
				}
			}
		}
	}
}

vector <int> RecordManage::searchRecords(Conditions& cd, CategoryManage& category_manager) {
	vector <int> result;
	// vector result 채우는 part
	list <Record>::iterator iter = record_list.begin();
	list <Record>::iterator end_of_list = record_list.end();
	bool check;
	int i = 0;
	for (; iter != end_of_list; iter++) {
		check = true;
		
		if (cd.on_period) {
			//기간범위 밖이면
			struct tm d = iter->get_date();
			if (compare(d, cd.from) == 1 || compare(cd.to, d) == 1) {
				check = false;
			}
		}
		if (cd.on_ie) {
			if (iter->get_isincome() != cd.is_income) {
				check = false;
			}
		}
		if (cd.on_memo) {
			if ((iter->get_memo()).find(cd.keyword) == string::npos) {
				check = false;
			}
		}
		if (cd.on_category) {
			if (iter->get_category_number() != cd.category_number) {
				check = false;
			}
		}
		
		if (check) {
			result.push_back(i);
		}
		i++;
	}

	//출력 part
	int end;
	end = result.size();
	iter = record_list.begin();
	
	printf("\nNo\tDate\t\tTime\tIn\tAmount\t\tMemo\t\t\tCategory\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	if (end > 0) {
		advance(iter, result[0]);
		printf("%-04d\t%04d/%02d/%02d\t%02d:%02d", 1, iter->get_date().tm_year, iter->get_date().tm_mon, iter->get_date().tm_mday, iter->get_date().tm_hour, iter->get_date().tm_min);
		printf("\t%d\t%-10u\t%-20s\t", iter->get_isincome(), iter->get_amount(), (iter->get_memo()).c_str());
		printf("%-20s\n", (category_manager.getIndexedCategory(iter->get_category_number())).c_str());
		for (i = 1; i < end; i++) {
			advance(iter, (result[i] - result[i - 1]));
			printf("%-04d\t%04d/%02d/%02d\t%02d:%02d", i + 1, iter->get_date().tm_year, iter->get_date().tm_mon, iter->get_date().tm_mday, iter->get_date().tm_hour, iter->get_date().tm_min);
			printf("\t%d\t%-10u\t%-20s\t", iter->get_isincome(), iter->get_amount(), (iter->get_memo()).c_str());
			printf("%-20s\n", (category_manager.getIndexedCategory(iter->get_category_number())).c_str());
		}
	}
	return result;
}

bool RecordManage::modifyRecordList(vector <int> result) {
	string input_string;
	int selected;
	while (1) {
		cout << "\n@ Edit a transaction @" << endl;
		cout << "Enter transaction number (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return true;
		}
		selected = -1;
		try {
			selected = stoi(input_string);
		}
		catch (exception& expn) {
			cout << "Please enter a valid value." << endl;
		}
		if (selected < 1 || selected > result.size()) {
			cout << "Please enter a valid value." << endl;
		}
		else {
			//선택된 index로 수정 작업
			return true;
		}
	}
}

bool RecordManage::deleteRecordList(vector <int> result) {
	string input_string;
	int selected;
	while (1) {
		cout << "\n@ Delete a transaction @" << endl;
		cout << "Enter transaction number (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return true;
		}
		selected = -1;
		try {
			selected = stoi(input_string);
		}
		catch (exception& expn) {
			cout << "Please enter a valid value." << endl;
		}
		if (selected < 1 || selected > result.size()) {
			cout << "Please enter a valid value." << endl;
		}
		else {
			//선택된 index로 삭제 작업
			cout << "\n@ Delete a transaction @" << endl;
			cout << "Confirm deletion? (type 'No' to cancel)\n> ";
			getline(cin, input_string);
			if (input_string == "No") {
				return true;
			}
			else {
				list <Record>::iterator iter = record_list.begin();
				advance(iter, result[selected-1]);
				record_list.erase(iter);
				return false;
			}
		}
	}
}

short RecordManage::compare(struct tm& left, struct tm& right) {
	if (left.tm_year != right.tm_year) {
		if (left.tm_year < right.tm_year) {
			return 1;
		}
		else {
			return -1;
		}
	}
	if (left.tm_mon != right.tm_mon) {
		if (left.tm_mon < right.tm_mon) {
			return 1;
		}
		else {
			return -1;
		}
	}
	if (left.tm_mday != right.tm_mday) {
		if (left.tm_mday < right.tm_mday) {
			return 1;
		}
		else {
			return -1;
		}
	}
	if (left.tm_hour != right.tm_hour) {
		if (left.tm_hour < right.tm_hour) {
			return 1;
		}
		else {
			return -1;
		}
	}
	
	if (left.tm_min < right.tm_min) {
		return 1;
	}
	else if (left.tm_min == right.tm_min) {
		return 0;
	}
	else {
		return -1;
	}
}