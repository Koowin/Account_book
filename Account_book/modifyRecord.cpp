#include"header.cpp"

void modifyRecord(list <Record>& record_list, int num, unsigned int data) {

	list <Record>::iterator iter;

	iter = record_list.begin();

	advance(iter, num);      //  n��° �ε����� iter ���� ��
	
	(*iter).amount = data;
	
}

void modifyRecord(list <Record>& record_list, int num, string data) {

	list <Record>::iterator iter;

	iter = record_list.begin();

	advance(iter, num);      //  n��° �ε����� iter ���� ��

	(*iter).memo = data;

}

void modifyRecord(list <Record>& record_list, int num, short data) {

	list <Record>::iterator iter;

	iter = record_list.begin();

	advance(iter, num);      //  n��° �ε����� iter ���� ��

	(*iter).category = data;

}