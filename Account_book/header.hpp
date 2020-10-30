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

	/*���� �߰��ϴ� �Լ�
	* return 1: ���� �� �߰�(�ݺ�)
	* return 0: ���
	* return -1: ���θ޴��� �̵� */
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
	CheckerParser c_parser; //���� �߰� - ���� ������ ��Ÿ ��� �Լ����� �����ϱ� ���ϰ� �׳� ����� ���� // �����ڿ��� ��ü ���� �ʼ�
public:
	/* non-search part */
	void printAllRecordList(CategoryManage&);
	void printSelectedRecordList(CategoryManage&, vector <int>);
	bool addRecord(CategoryManage&);
	bool modifyRecordList(vector <int>, CategoryManage&);
	bool modifyRecordList(vector <int>);
	bool deleteRecordList(vector <int>);
	int getRecordListSize();
	/* �߰� ���� ���� */
	void init_add(Record);
	Record getRecord();

	/* search Part */
	void searchMenu(CategoryManage&);
	vector <int> searchRecords(Conditions&, CategoryManage&);

	// record_list�� ó���� �� �ݺ��ڸ� ��ȯ�ϴ� �Լ�
	list <Record>::iterator get_first();
	list <Record>::iterator get_end();
	//0: ���� 1: �������� ŭ -1: ������ ŭ
	short compare(struct tm, struct tm);
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
	void categoryMenu(RecordManage&);
	void printCategoryList();
	bool addCategory();
	bool modifyCategory();
	bool deleteCategory(RecordManage&);
	int getCategorySize();
	string getIndexedCategory(int);
	/* �߰� ���� ���� */
	bool isDuplicate(string);
	void init_add(Category);
	Category getCategory();
	/////////////////
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