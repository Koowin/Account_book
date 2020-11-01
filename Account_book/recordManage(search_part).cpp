#include "header.hpp"

void RecordManage::searchMenu(CategoryManage& category_manager) {
	Conditions cd;

	string input_string;
	int selected_menu = 0;
	bool search_start = false;
	while (1) {
		system("cls");
		cout << "@ Search a transaction @" << endl;
		cout << "1. Date and Time" << endl;
		cout << "2. Income/Expense" << endl;
		cout << "3. Memo" << endl;
		cout << "4. Category " << endl;
		cout << "5. Reset conditions (by field)" << endl << endl;

		cout << "Select field (q:return to main menu)\n> ";

		while (1) {
			getline(cin, input_string);
			if (input_string == "q") {
				return;
			}
			else if (input_string == "1") {
				system("cls");
				//기간 조건 추가
				short n = cd.addPeriodCondition();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
					break;
				}
			}
			else if (input_string == "2") {
				system("cls");
				//수입, 지출 조건 추가
				short n = cd.addIeCondition();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
					break;
				}
			}
			else if (input_string == "3") {
				system("cls");
				//메모 키워드 조건 추가
				short n = cd.addMemoCondition();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
					break;
				}
			}
			else if (input_string == "4") {
				system("cls");
				//카테고리 조건 추가
				short n = cd.addCategoryCondition(category_manager);
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
					break;
				}
			}
			else if (input_string == "5") {
				system("cls");
				//조건 초기화
				short n = cd.resetConditions();
				if (n == -1) {
					return;
				}
				else {
					search_start = !n;
					break;
				}
			}
			else {
				cout << "Please enter a valid value\n> ";
			}
		}
		
		if (search_start) {
			//조건 맞게 출력 시작
			vector <int> result = searchRecords(cd, category_manager);
			//신이 추가: 
			if (result.size() == 0) {
				cout << "\nNone if the records satisfies the given condition(s)." << endl;
				cout << "\nPress any key to continue...\n";
				_getch();
				return;
			}
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
					modifyRecordList(result, category_manager);
					return;
				}
				else if (input_string == "2") {
					deleteRecordList(result, category_manager);
					return;
				}
				else {
					cout << "Please enter a valid value" << endl;
				}
			}
		}
		//}
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
	system("cls");
	printf("\nNo\tDate\t\tTime\tType\tAmount\t\tMemo\t\t\tCategory\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	if (end > 0) {
		advance(iter, result[0]);
		printf("%-04d\t%04d/%02d/%02d\t%02d:%02d", 1, iter->get_date().tm_year+1900, iter->get_date().tm_mon+1, iter->get_date().tm_mday, iter->get_date().tm_hour, iter->get_date().tm_min);
		if (iter->get_isincome()) {
			printf("\tincome");
		}
		else {
			printf("\texpense");
		}
		printf("\t%-10u\t%-20s\t", iter->get_amount(), (iter->get_memo()).c_str());
		printf("%-20s\n", (category_manager.getIndexedCategory(iter->get_category_number())).c_str());
		for (i = 1; i < end; i++) {
			advance(iter, (result[i] - result[i - 1]));
			printf("%-04d\t%04d/%02d/%02d\t%02d:%02d", i + 1, iter->get_date().tm_year+1900,iter->get_date().tm_mon+1, iter->get_date().tm_mday, iter->get_date().tm_hour, iter->get_date().tm_min);
			if (iter->get_isincome()) {
				printf("\tincome");
			}
			else {
				printf("\texpense");
			}
			printf("\t%-10u\t%-20s\t", iter->get_amount(), (iter->get_memo()).c_str());
			printf("%-20s\n", (category_manager.getIndexedCategory(iter->get_category_number())).c_str());
		}
	}
	return result;
}

bool RecordManage::modifyRecordList(vector <int> result, CategoryManage& category_manager) {
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
		CheckerParser cp;
		if (!cp.checkCategoryNumber(input_string, record_list.size())) {
			selected = stoi(input_string);

			//선택된 index로 수정 작업
			list <Record>::iterator iter = record_list.begin();
			advance(iter, result[selected - 1]);
			struct tm before_date = iter->get_date();
			struct tm after_date = before_date;
			bool before_is_income = iter->get_isincome();
			bool after_is_income = before_is_income;
			unsigned int before_amount = iter->get_amount();
			unsigned int after_amount = before_amount;
			string before_memo = iter->get_memo();
			string after_memo = before_memo;
			int before_category_number = iter->get_category_number();
			int after_category_number = before_category_number;
			CheckerParser cp;

			while (1) {
				cout << "\n@ Edit a transaction @" << endl;
				cout << "1. Date and Time" << endl;
				cout << "2. Income/Expense" << endl;
				cout << "3. Amount" << endl;
				cout << "4. Memo" << endl;
				cout << "5. Category\n" << endl;
				cout << "Select field to edit (q: return to main menu)\n> ";
				getline(cin, input_string);

				if (input_string == "q") {
					return true;
				}
				else if (input_string == "1") {
					while (1) {
						cout << "\n@ Edit Date and Time @" << endl;
						cout << "Before modification: ";
						printf("%04d/%02d/%02d %02d:%02d\n", before_date.tm_year+1900, before_date.tm_mon+1, before_date.tm_mday, before_date.tm_hour, before_date.tm_min);
						cout << "Enter date and time after modification (q:return to main menu)\n> ";
						getline(cin, input_string);
						if (input_string == "q") {
							return true;
						}
						after_date = cp.checkParseDate(input_string);
						if (after_date.tm_year != -1) {
							break;
						}
					}
					break;
				}
				else if (input_string == "2") {
					after_is_income = !before_is_income;
					break;
				}
				else if (input_string == "3") {
					while (1) {
						cout << "\n@ Edit Amount @" << endl;
						cout << "Before modification: " << before_amount << endl;
						cout << "Enter amount after modification (q:return to main menu)\n> ";
						getline(cin, input_string);
						if (input_string == "q") {
							return true;
						}
						if (!cp.checkAmount(input_string)) {
							after_amount = cp.parseAmount(input_string);
							break;
						}
					}
					break;
				}
				else if (input_string == "4") {
					while (1) {
						cout << "\n@ Edit Memo @" << endl;
						cout << "Before modification: " << before_memo << endl;
						cout << "Enter memo after modification (q:return to main menu)\n> ";
						getline(cin, input_string);
						if (input_string == "q") {
							return true;
						}
						if (!cp.checkMemo(input_string)) {
							after_memo = input_string;
							break;
						}
					}
					break;
				}
				else if (input_string == "5") {
					while (1) {
						cout << "\n@ Edit Category @" << endl;
						cout << "Before modification: " << category_manager.getIndexedCategory(before_category_number) << endl;
						cout << "\nAll categories:" << endl;
						category_manager.printCategoryList();
						cout << "\nSelect category after modification (q:return to main menu)\n> ";
						getline(cin, input_string);
						if (input_string == "q") {
							return true;
						}
						if (!cp.checkCategoryNumber(input_string, category_manager.getCategorySize())) {
							after_category_number = stoi(input_string);
							break;
						}
					}
					break;
				}
				else {
					cout << "Please enter a valid value." << endl;
				}
			}
			//수정 확인
			system("cls");
			cout << "@ Before modification @" << endl;
			cout << "- Date and Time: ";
			printf("%04d/%02d/%02d %02d:%02d\n", before_date.tm_year+1900, before_date.tm_mon+1, before_date.tm_mday, before_date.tm_hour, before_date.tm_min);
			cout << "- Income/Expense: ";
			if (before_is_income) {
				cout << "Income" << endl;
			}
			else {
				cout << "Expense" << endl;
			}
			cout << "- Amount: " << before_amount << endl;
			cout << "- Memo: " << before_memo << endl;
			cout << "- Category: " << category_manager.getIndexedCategory(before_category_number) << endl << endl;

			cout << "@ After modification @" << endl;
			cout << "- Date and Time: ";
			printf("%04d/%02d/%02d %02d:%02d\n", after_date.tm_year+1900, after_date.tm_mon+1, after_date.tm_mday, after_date.tm_hour, after_date.tm_min);
			cout << "- Income/Expense: ";
			if (after_is_income) {
				cout << "Income" << endl;
			}
			else {
				cout << "Expense" << endl;
			}
			cout << "- Amount: " << after_amount << endl;
			cout << "- Memo: " << after_memo << endl;
			cout << "- Category: " << category_manager.getIndexedCategory(after_category_number) << endl << endl;
			cout << "Confirm modification? (type 'No' to cancle)\n> ";
			getline(cin, input_string);
			if (input_string == "No") {
				return true;
			}
			else {
				//최종 수정 작업
				record_list.erase(iter);

				list <Record>::iterator iter2 = record_list.begin();
				list <Record>::iterator end_of_list = record_list.end();

				for (; iter2 != end_of_list; iter2++) {
					struct tm d = iter2->get_date();
					if (compare(after_date, d) == 1) {
						break;
					}
				}

				if (iter2 == end_of_list) {
					record_list.push_back(Record(after_date, after_is_income, after_amount, after_memo, after_category_number));
				}
				else {
					record_list.insert(iter2, Record(after_date, after_is_income, after_amount, after_memo, after_category_number));
				}
				FileManage file_manager;
				file_manager.saveFile(*this, category_manager);
				return false;
			}
		}
	}
}

bool RecordManage::deleteRecordList(vector <int> result, CategoryManage &category_manager) {
	string input_string;
	int selected;
	while (1) {
		cout << "\n@ Delete a transaction @" << endl;
		cout << "Enter transaction number (q: return to main menu)\n> ";
		getline(cin, input_string);
		if (input_string == "q") {
			return true;
		}
		
		CheckerParser cp;
		if (!cp.checkCategoryNumber(input_string, record_list.size())) {
			selected = stoi(input_string);

			//선택된 index로 삭제 작업
			cout << "\n@ Delete a transaction @" << endl;
			cout << "Confirm deletion? (type 'No' to cancel)\n> ";
			getline(cin, input_string);
			if (input_string == "No") {
				return true;
			}
			else {
				list <Record>::iterator iter = record_list.begin();
				advance(iter, result[selected - 1]);
				record_list.erase(iter);
				FileManage file_manager;
				file_manager.saveFile(*this, category_manager);
				return false;
			}
		}
	}
}

short RecordManage::compare(struct tm left, struct tm right) {
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
