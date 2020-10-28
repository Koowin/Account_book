#include<iostream>
#include<ctime>
#include<list>
#include<conio.h>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

class Conditions {
private:
	bool on_period;
	bool on_income;
	bool on_memo;
	bool on_category;

	struct tm from_date;
	struct tm to_date;
	bool is_income;
	string memo_keyword;
	int category_number;

public:
	Conditions();			//초기값: on~~ 모두 false로

	struct tm get_from_date();
	struct tm get_to_date();
	bool get_is_income();
	string get_memo_keyword();
	int get_category_number();

	void set_period();
	void set_income();
	void set_memo();
	void set_category();
	void clear_conditions();
};

class CheckerParser {
private:

public:
	bool checkDate(string);
	bool checkAmount(string);
	bool checkMemo(string);
	bool checkCategoryNumber(string, int);
	struct tm parseDate(string);
	unsigned int parseAmount(string);
};

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
	bool get_isIncome();
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
	void categoryMenu();
	void printCategoryList();
	bool addCategoryList(Category);
	bool modifyCategoryList(Category);
	bool deleteCategoryList(Category);
	int getCategorySize();
	void init_add(Category);
	int listSize();
	bool isDuplicate(string);
	Category getCategory();
};

class RecordManage {
private:
	list<Record> record_list;
public:
	/* 기본 기능 */
	void printAllRecordList(CategoryManage&);
	bool addRecord(int);
	bool searchRecords(CategoryManage&);
	bool modifyRecordList(Record);
	bool deleteRecordList(Record);
	void init_add(Record);
	int getRecordSize();
	Record getRecord();
};





class FileManage {
private:

public:
	bool initFile(RecordManage&, CategoryManage&);
	bool saveFile(RecordManage&, CategoryManage&);
};

void Tokenize(const string&, vector<string>&, const string&);
struct tm setTime(string);