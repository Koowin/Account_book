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

class Conditions {
public:
	bool on_period;
	bool on_ie;
	bool on_memo;
	bool on_category;
	
	struct tm from;
	struct tm to;
	bool is_income;
	string keyword;
	int category_number;
	string category_name;

	Conditions();

	/*조건 추가하는 함수
	* return 1: 조건 더 추가(반복)
	* return 0: 출력
	* return -1: 메인메뉴로 이동 */
	short addPeriodCondition();
	short addIeCondition();
	short addMemoCondition();
	short addCategoryCondition(CategoryManage&);
	short resetConditions();
	short printCurrentConditions();

	bool compare(struct tm&, struct tm&);
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
	bool modifyRecordList(vector <int>, CategoryManage&);
	bool deleteRecordList(vector <int>);
	int getRecordListSize();
	
	void init_add(Record);
	Record getRecord();

	/* search Part */
	void searchMenu(CategoryManage&);
	vector <int> searchRecords(Conditions&, CategoryManage&);

	// record_list의 처음과 끝 반복자를 반환하는 함수
	list <Record>::iterator get_first();
	list <Record>::iterator get_end();
	//0: 같음 1: 오른쪽이 큼 -1: 왼쪽이 큼
	short compare(struct tm&, struct tm&);
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
	
	bool isDuplicate(string);
	void init_add(Category);
	Category getCategory();

	list <Category>::iterator get_first();
	list <Category>::iterator get_end();
};

class FileManage {
private:

public:
	bool initFile(RecordManage&, CategoryManage&);
	bool saveFile(RecordManage&, CategoryManage&);
};

void Tokenize(const string&, vector<string>&, const string&);
struct tm setTime(string);
