#include"header.cpp"


void deleteRecord(list <Record>& record_��ist, int num) {


	list <Record>::iterator iter;

	iter = record_list.begin();

	advance(iter, num);      //  n��° �ε����� iter ���� �� 

	record_list.erase(iter);  // �� �ε��� ��� ���� 
	

}