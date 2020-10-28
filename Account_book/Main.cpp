#include "header.hpp"

int main() {
	RecordManage record_manager;
	CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag;

	//to do: 파일 읽기 및 데이터 저장 작업

	FileManage file_manager;

	if (!file_manager.initFile(record_manager, category_manager)) {
		return -1;
	}

	file_manager.saveFile(record_manager, category_manager);

	while (1) {
		//to do: 메인메뉴 출력부
		cout << "메인메뉴" << endl;

		//숫자만 입력받을 때 까지 반복
		flag = true;
		while (flag) {
			cin >> input_string;
			try {
				menu_selected = stoi(input_string);
				flag = false;
			}
			catch (const exception & expn) {
				cout << "숫자만 입력해 주세요" << endl;
			}
		}

		switch (menu_selected) {
		case 1:
			//기록 1개 추가
			record_manager.addRecord(category_manager.getCategorySize());
			break;
		case 2:
			//전체 목록 출력
			record_manager.printAllRecordList(category_manager);
			break;
		case 3:
			//검색,수정,삭제 메뉴
			record_manager.searchRecords(category_manager);
			break;
		case 4:
			//카테고리 관리 메뉴
			category_manager.categoryMenu();
			break;
		case 5:
			//저장 작업

			return 0;		//프로그램 종료
		default:
			cout << "1~5사이의 숫자만 입력해주세요." << endl;
			break;
		}
	}
}

