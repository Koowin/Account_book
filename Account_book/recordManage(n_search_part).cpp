#include "header.hpp"

void RecordManage::printAllRecordList(CategoryManage& category_manager) {
	list <Record>::iterator iter;
	list <Record>::iterator end = record_list.end();
	printf("Date\t\tTime\tIn\tAmount\t\tMemo\t\t\tCategory\n");
	printf("--------------------------------------------------------------------------------------------\n");

	for (iter = record_list.begin(); iter != end; iter++) {
		printf("%04d/%02d/%02d\t%02d:%02d", iter->get_date().tm_year, iter->get_date().tm_mon, iter->get_date().tm_mday, iter->get_date().tm_hour, iter->get_date().tm_min);
		printf("\t%d\t%-10u\t%-20s\t", iter->get_isincome(), iter->get_amount(), (iter->get_memo()).c_str());
		printf("%-20s\n", category_manager.getIndexedCategory(iter->get_category_number()));
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
	while (flag) {
		cout << "날짜 입력" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		
		date = cp.checkParseDate(input_string);
		//정상 입력 시
		if (date.tm_year != -1) {
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


list <Record>::iterator RecordManage::get_first(){
	return record_list.begin();
}
list <Record>::iterator RecordManage::get_end() {
	return record_list.end();
}