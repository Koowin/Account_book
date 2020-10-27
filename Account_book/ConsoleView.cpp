#include <ConsoleView.h>

ConsoleView::ConsoleView() {



}




void ConsoleView::showUI() { // �޴� ����Ŭ ���
	bool exit = false; // ���α׷� ���� ����
	while (1) {
		switch (page) {
		case 0: // �ʱ�ȭ�� 
			page = userUI0();
			break;
		case 1: // �������� ���� �Է�
			page = userUI1();
			break;
		case 2: // ��ü ��� ����
			page = userUI2();
			break;
		case 3: // �˻�/ ����/ ���� �޴� 
			page = userUI3();
			break;
		case 4: // ī�װ� ���� �޴�
			page = userUI4();
			break;
		case 5: // ����
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




		inputs(); // Ű���� �Է� �ޱ�

		
	}

}


int ConsoleView::userUI1() {
	while (1) {


		cout << "  @ Add a transaction@" << endl;


		inputs(); // Ű���� �Է� �ޱ�



	}
}

int ConsoleView::userUI2() {
	while (1) {


		cout << "  @ View all transaction@" << endl;


		inputs(); // Ű���� �Է� �ޱ�



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