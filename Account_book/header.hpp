#include<iostream>
#include<ctime>
#include<list>
#include<conio.h>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class Record {
private:
	struct tm date;
	bool is_income;
	unsigned int amount;
	string memo;
	int category_number;

public:
	Record(struct tm, bool, unsigned int, string, int);
	/* getter */
	struct tm  get_date();
	bool get_isincome();
	unsigned int get_amount();
	string get_memo();
	int get_category_number();

	/* setter */
	void set_date(struct tm);
	void set_isIncome(bool);
	void set_amount(unsigned int);
	void set_memo(string);
	void set_category_number(int);
};

class RecordManage {
private:
	list <Record> record_list;
public:
	/* 기본 기능 */
	void printAllRecordList(CategoryManage &);
	bool addRecord(int);
	//여기에 신이님 함수 추가
	bool searchRecords(CategoryManage &);
	bool modifyRecordList(int);
	bool deleteRecordList(int);

	// record_list의 처음과 끝 반복자를 반환하는 함수
	list <Record>::iterator get_first();
	list <Record>::iterator get_end();
};

class Category {
private:
	string c_name;

public:
	Category(string);

	/* getter */
	string get_cname();

	/* setter */
	void set_cname(string);
};

class CategoryManage {
private:
	list<Category> category;

public:
	void categoryMenu(RecordManage &);
	void printCategoryList();
	bool addCategory();
	bool modifyCategory();
	bool deleteCategory(RecordManage &);
	int getCategorySize();
};

class FileManage {
private:

public:
	bool initFile();
	bool saveFile();
};

class CheckerParser {
private:

public:
	bool checkDate(string);
	bool checkAmount(string);
	bool checkMemo(string);
	bool checkCategoryNumber(string, int);
	bool checkCategoryName(string);

	struct tm parseDate(string);
	unsigned int parseAmount(string);
};