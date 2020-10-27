#include <ConsoleView.h>

ConsoleView::ConsoleView() {



}




void ConsoleView::showUI() { // 메뉴 사이클 담당
	bool exit = false; // 프로그램 종료 여부
	while (1) {
		switch (page) {
		case 0: // 초기화면 
			page = userUI0();
			break;
		case 1: // 수입지출 내역 입력
			page = userUI1();
			break;
		case 2: // 전체 목록 보기
			page = userUI2();
			break;
		case 3: // 검색/ 수정/ 삭제 메뉴 
			page = userUI3();
			break;
		case 4: // 카테고리 관리 메뉴
			page = userUI4();
			break;
		case 5: // 종료
			exit = true;
			break;
		
		
		}
		if (exit == true) break;
	}
	cout << "System is ended.\n\n" << endl;
}


int ConsoleView::userUI0() {
	while (1) {
		console_clear();
		cout << " @ Main menu @ " << endl;
		cout << "  1. Add a transaction" << endl;
		cout << "  2. View all transaction" << endl;
		cout << "  3. Search/Edit/Delete a transaction" << endl;
		cout << "  4. Manage category" << endl;
		cout << "  5. Quit " << endl;




		inputs(); // 키보드 입력 받기

		
	}

}


int ConsoleView::userUI1() {
	while (1) {


		cout << "  @ Add a transaction@" << endl;


		inputs(); // 키보드 입력 받기



	}
}

int ConsoleView::userUI2() {
	while (1) {


		cout << "  @ View all transaction@" << endl;


		inputs(); // 키보드 입력 받기



	}
}

void ConsoleView::line_clear() {
	cout << "\33[2K";
}

void ConsoleView::console_clear() {
	system("cls");
}




void ConsoleView::inputs() {
	cin >> input;
	cin.clear();
	cin.ignore(1, '\n');
}