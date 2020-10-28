//���߿� ���̴� ����� ���ļ� ���� ����
//�������� ��� ����, ���� �������ּ���~
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


	//��¥ �Է¹޴� �κ�
	while (flag) {
		cout << "��¥ �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//���� �Է� ��
		if (!cp.checkDate(input_string)) {
			date = cp.parseDate(input_string);
			flag = false;
		}
		//������ �Է� �� ���� ���� ��� �� �ݺ�
	}


	//����/���� �Է¹޴� �κ�
	flag = true;
	while (flag) {
		cout << "����/����" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		//���� �Է� ��
		else if (input_string == "1" || input_string == "2") {
			if (input_string == "1") {
				is_income = true;
			}
			else {
				is_income = false;
			}
			flag = false;
		}
		//������ �Է� ��
		else {
			//to do : ���� ���� ����� �ٲٱ�
			cout << "���� ���� ���" << endl;
		}
	}

	//�ݾ� �Է� �޴� �κ�
	flag = true;
	while (flag) {
		cout << "�ݾ� �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}

		//���� �Է� ��
		if (!cp.checkAmount(input_string)) {
			amount = cp.parseAmount(input_string);
			flag = false;
		}
		//������ �Է� �� ���� ���� ����ϰ� �ݺ�
	}

	//�޸� �Է� �޴� �κ�
	flag = true;
	while (flag) {
		cout << "�޸� �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}

		//���� �Է� ��
		if (!cp.checkMemo(input_string)) {
			memo = input_string;
		}
		//������ �Է� �� ���� ���� ����ϰ� �ݺ�
	}

	//ī�װ� ��ȣ �Է� �޴� �κ�
	flag = true;
	while (flag) {
		cout << "ī�װ� ��ȣ �Է�" << endl;
		cin >> input_string;

		if (input_string == "q") {
			return true;
		}
		try {
			category_number = stoi(input_string);
		}
		catch (const exception & expn) {
			cout << "���ڸ� �Է����ּ���" << endl;
		}

		if (category_number > 0 && category_number <= category_size) {
			flag = false;
		}
		else {
			cout << "1 ���� " << category_size << " ������ ���ڸ� �Է����ּ���" << endl;
		}
	}

	//���� Ȯ�� ����� �κ�
	cout << "�����Ͻðڽ��ϱ�? (���: No)" << endl;
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
		cout << "�˻� ���� �߰�" << endl;
		cout << "1. �Ⱓ�� �˻�" << endl;
		cout << "2. ����/���⺰ �˻�" << endl;
		cout << "3. �޸� �˻�" << endl;
		cout << "4. ī�װ��� �˻�" << endl;
		cout << "5. ���� �ʱ�ȭ" << endl;

		cin >> input_string;
		if (input_string == "q") {
			return true;
		}

		try {
			menu_selected = stoi(input_string);
		}
		catch (const exception & expn) {
			cout << "���ڸ� �Է��� �ּ���" << endl;
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
				cout << "1���� 5 ������ ���ڸ� �Է����ּ���" << endl;
				break;
			}
		}

		//��� ���� �����
		while (1) {
			cout << "���� ���Ǵ�� �˻��Ͻðڽ��ϱ�? (1:���� �� �߰�, 2:�˻�)" << endl;
			cin >> input_string;
			if (input_string == "q") {
				return true;
			}
			else if (input_string == "1") {
				break;
			}
			else if (input_string == "2") {
				//���� �������� ���
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