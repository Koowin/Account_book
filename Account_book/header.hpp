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
	Record();
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
	void printAllRecordList(class CategoryManage &);
	bool addRecord(int);
	//여기에 신이님 함수 추가
	bool searchRecords(class CategoryManage &);
	bool modifyRecordList(int);
	bool deleteRecordList(int);
};

class Category {
private:
	string c_name;

public:
	Category();
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
	void categoryMenu(class RecordManage &);
	void printCategoryList();
	bool addCategoryList(Category);
	bool modifyCategoryList(Category);
	bool deleteCategoryList(Category);
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

	struct tm parseDate(string);
	bool parseAmount(string);
};