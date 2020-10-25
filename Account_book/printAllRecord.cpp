#include"header.cpp"

string printAllRecord(list <string> *recordList) {
	list <string>::iterator iter;
	cout << "Date       Time     Type      Amount	Memo      Category" << endl;
	for (iter = recordList->begin(); iter != recordList->end(); iter++) {
		cout << *iter << endl;
	}
}
