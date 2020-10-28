//나중에 신이님 결과물 합쳐서 넣을 예정
//찬종님이 기록 수정, 삭제 구현해주세요~
#include "header.hpp"

Record::Record() {

}

Record::Record(struct tm date, bool is_income, unsigned int amount, string memo, int category_number) {
	this->date = date;
	this->is_income = is_income;
	this->amount = amount;
	this->memo = memo;
	this->category_number = category_number;
}

struct tm Record::get_date() {
	
	return date;
}

bool Record::get_isIncome() {
	return is_income;
}

unsigned int Record::get_amount() {
	return amount;
}

string Record::get_memo() {
	return memo;
}

int Record::get_category_number() {
	return category_number;
}

void Record::set_date(struct tm tm) {
	
}

void Record::set_isIncome(bool) {

}

void Record::set_amount(unsigned int) {

}

void Record::set_memo(string) {

}

void Record::set_category_number(int) {

}

void RecordManage::printAllRecordList(CategoryManage& category_manager) {

}

bool RecordManage::addRecord(int category_size) {
	CheckerParser cp;
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
			flag = false;
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
		catch (const exception & expn) {
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
		record_list.push_back(Record(date, is_income, amount, memo, category_number));
		return false;
	}
}

bool RecordManage::searchRecords(CategoryManage& category_manager) {
	bool flag = true;
	string input_string;
	int menu_selected;
	Conditions cd;

	while (flag) {
		cout << "검색 조건 추가" << endl;
		cout << "1. 기간별 검색" << endl;
		cout << "2. 수입/지출별 검색" << endl;
		cout << "3. 메모 검색" << endl;
		cout << "4. 카테고리별 검색" << endl;
		cout << "5. 조건 초기화" << endl;

		cin >> input_string;
		if (input_string == "q") {
			return true;
		}

		try {
			menu_selected = stoi(input_string);
		}
		catch (const exception & expn) {
			cout << "숫자만 입력해 주세요" << endl;
		}

		switch (menu_selected) {
			switch (menu_selected) {
			case 1:
				cd.set_period();
				break;
			case 2:
				cd.set_income();
				break;
			case 3:
				cd.set_memo();
				break;
			case 4:
				cd.set_category();
				break;
			case 5:
				cd.clear_conditions();
				break;
			default:
				cout << "1부터 5 사이의 숫자만 입력해주세요" << endl;
				break;
			}
		}

		//출력 여부 물어보기
		while (1) {
			cout << "현재 조건대로 검색하시겠습니까? (1:조건 더 추가, 2:검색)" << endl;
			cin >> input_string;
			if (input_string == "q") {
				return true;
			}
			else if (input_string == "1") {
				break;
			}
			else if (input_string == "2") {
				//현재 조건으로 출력
				break;
			}
		}
	}
}

int RecordManage::getRecordSize() {
	return this->record_list.size();
}

bool RecordManage::modifyRecordList(Record r) {
	return false;
}

bool RecordManage::deleteRecordList(Record r) {
	return false;
}

Record RecordManage::getRecord() {
	Record r = record_list.front();
	record_list.pop_front();
	return r;
}