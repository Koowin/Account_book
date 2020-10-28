#include "header.hpp"

int main() {
	class RecordManage record_manager;
	class CategoryManage category_manager;
	string input_string;
	int menu_selected;
	bool flag;

	//to do: 파일 읽기 및 데이터 저장 작업

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
			catch (const exception& expn) {
				cout << "숫자만 입력해 주세요" << endl;
			}
		}

		switch(menu_selected) {
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
			category_manager.categoryMenu(record_manager);
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






bool RecordManage::addRecord(int category_size) {
	class CheckerParser cp;
	string input_string;
	bool flag = true;

	struct tm date;
	bool is_income;
	unsigned int amount;
	string memo;
	int category_number;
	

	//날짜 입력받는 부분
	while(flag){
		cout << "날짜 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//정상 입력 시
		if (!cp.checkDate(input_string)) {
			date = cp.parseDate(input_string);
			flag = false;
		}
		//비정상 입력 시 오류 문구 출력 후 반복
	}


	//수입/지출 입력받는 부분
	flag = true;
	while (flag) {
		cout << "수입/지출" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//정상 입력 시
		else if (input_string == "1" || input_string == "2") {
			if (input_string == "1") {
				is_income = true;
			}
			else {
				is_income = false;
			}
			flag == false;
		}
		//비정상 입력 시
		else {
			//to do : 오류 문구 영어로 바꾸기
			cout << "오류 문구 출력" << endl;
		}
	}

	//금액 입력 받는 부분
	flag = true;
	while (flag) {
		cout << "금액 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		
		//정상 입력 시
		if (!cp.checkAmount(input_string)) {
			amount = cp.parseAmount(input_string);
			flag = false;
		}
		//비정상 입력 시 오류 문구 출력하고 반복
	}

	//메모 입력 받는 부분
	flag = true;
	while (flag) {
		cout << "메모 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}

		//정상 입력 시
		if (!cp.checkMemo(input_string)) {
			memo = input_string;
		}
		//비정상 입력 시 오류 문구 출력하고 반복
	}

	//카테고리 번호 입력 받는 부분
	flag = true;
	while (flag) {
		cout << "카테고리 번호 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		try {
			category_number = stoi(input_string);
		}
		catch (const exception& expn) {
			cout << "숫자만 입력해주세요" << endl;
		}

		if (category_number > 0 && category_number <= category_size) {
			flag = false;
		}
		else {
			cout << "1 부터 " << category_size << " 사이의 숫자만 입력해주세요" << endl;
		}
	}
	
	//저장 확인 물어보는 부분
	cout << "저장하시겠습니까? (취소: No)" << endl;
	cin >> input_string;

	if (input_string == "No") {
		return true;
	}
	else {
		//to do : index 찾아서 넣기 혹은 넣고 정렬하기
		record_list.push_back(Record(date, is_income, amount, memo, category_number));
		return false;
	}
}