#include "header.hpp"

int main() {
	class RecordManage record_manager;
	class CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag;

	//to do: 파일 읽기 및 데이터 저장 작업
	while (1) {
		//메인메뉴 출력부
		system("cls");
		cout << "@ Main menu @" << endl;
		cout << "1. Add a transaction" << endl;
		cout << "2. View all transactions" << endl;
		cout << "3. Search/Edit/Delete a transaction" << endl;
		cout << "4. Manage category" << endl;
		cout << "5. Quit" << endl << endl;
		cout << "Select menu" << endl << "> ";

		//숫자만 입력받을 때 까지 반복
		while (1) {
			getline(cin, input_string);
			if (input_string == "1") {
				//기록 1개 추가
				if (record_manager.getRecordListSize() > 1023) {
					cout << "Your number of transactions has exceeded its maximum value (1024 transactions)." << endl;
					cout << "Please delete some of your transactions to continue." << endl;
				}
				else {
					record_manager.addRecord(category_manager);
				}
			}
			else if (input_string == "2") {
				//전체 목록 출력
				record_manager.printAllRecordList(category_manager);
			}
			else if (input_string == "3") {
				//검색,수정,삭제 메뉴
				record_manager.searchMenu(category_manager);
			}
			else if (input_string == "4") {
				//카테고리 관리 메뉴
				category_manager.categoryMenu(record_manager);
			}
			else if (input_string == "5") {
				//저장 작업
			}
			else{
				cout << "Please enter a valid value." << endl;
			}
		}
	}
}