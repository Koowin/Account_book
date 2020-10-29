#include<iostream>
#include<ctime>
#include<list>
#include<conio.h>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

class CategoryManage;
class CheckerParser {
private:

public:
	struct tm checkParseDate(string);
	bool checkAmount(string);
	bool checkMemo(string);
	bool checkCategoryNumber(string, int);
	bool checkCategoryName(string);

	//struct tm parseDate(string);
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
	CheckerParser c_parser; //신이 추가 - 많이 쓰여서 기타 멤버 함수들이 접근하기 편하게 그냥 멤버로 만듦 // 생성자에서 객체 생성 필수
public:
	/* non-search part */
	void printAllRecordList(CategoryManage &);
	void printSelectedRecordList(CategoryManage&, vector <int>);
	bool addRecord(CategoryManage &);
	bool modifyRecordList(int);
	bool deleteRecordList(int);
	int getRecordListSize();

	/* search Part */
	void searchRecord(CategoryManage&);
	vector<int> getSearchResult(struct tm*, string*, string*, int*, CategoryManage &);
	void printCurrent(struct tm*, string*, string*, int*, CategoryManage &);
	int resetFieldMenu();
	int* searchCategory(CategoryManage&);
	string* searchMemo();
	string* searchType();
	int compareTime(struct tm, struct tm);
	int searchTime(struct tm* (&));
	int searchMenu();

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
	string getIndexedCategory(int);

	list <Category>::iterator get_first();
	list <Category>::iterator get_end();
};

class FileManage {
private:

public:
	bool initFile();
	bool saveFile();
};

