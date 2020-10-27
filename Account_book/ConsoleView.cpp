#include <ConsoleView.h>

ConsoleView::ConsoleView() {



}


void ConsoleView::gotoxy(short x, short y) {

	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

void ConsoleView::showUI() { // �޴� ����Ŭ ���
	bool exit = false; // ���α׷� ���� ����
	while (1) {
		switch (page) {
		case 0: // �ʱ�ȭ�� & ī�װ� ���� & īƮ ���� & ����
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

		
		border_above(); // �� �׸���

		
		gotoxy(101, 9); // Ŀ�� �̵�
		cout << "��" << endl;


		inputs(); // Ű���� �Է� �ޱ�

		console_clear(); // �ܼ� ����

	
}


	int ConsoleView::userUI1() {
		while (1) {
			console_clear();
			


			border_above(); // �� �׸���


			gotoxy(101, 9); // Ŀ�� �̵�
			cout << "��" << endl;


			inputs(); // Ű���� �Է� �ޱ�

			console_clear(); // �ܼ� ����


		}

void ConsoleView::line_clear() {
	cout << "\33[2K";
}

void ConsoleView::console_clear() {
	system("cls");
}

void ConsoleView::border_above() {
	cout << "��";
	for (int i = 0; i < 100; i++)
	{
		cout << "��";
	}
	cout << "��" << endl;
}

void ConsoleView::border_bottom() {
	cout << "��";
	for (int i = 0; i < 100; i++)
	{
		cout << "��";
	}
	cout << "��" << endl;
}

void ConsoleView::inputs() {
	cin >> input;
	cin.clear();
	cin.ignore(1, '\n');
}