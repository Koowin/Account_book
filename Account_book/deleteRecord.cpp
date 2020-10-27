#include"header.cpp"


void deleteRecord(list <Record>& record_ㅣist, int num) {


	list <Record>::iterator iter;

	iter = record_list.begin();

	advance(iter, num);      //  n번째 인덱스로 iter 변경 후 

	record_list.erase(iter);  // 그 인덱스 노드 삭제 
	

}