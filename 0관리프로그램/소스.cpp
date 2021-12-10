#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

TCHAR st1[5][255] = { TEXT("�̴ϰ��� õ��"), TEXT("���Ӽ���"), TEXT("����ǥ"), TEXT("������") };
TCHAR st2[5][255] = { TEXT("�ڷΰ���"), TEXT("���°���"), TEXT("������"), TEXT("Ÿ�ڿ���") };
TCHAR st3[5][255] = { TEXT("�ڷΰ���"), TEXT("�̸�          ����") };

int condition;
int loc, limit = 2;

HANDLE hFile;
DWORD nr;
TCHAR ff[1024][1];
TCHAR fstr[1024];
int j = 0, l = 0, m;
int flag = 0; // ����:0, ����:1

TCHAR ch[100][2] = {
	TEXT("a"), TEXT("b"),TEXT("c"), TEXT("d"),TEXT("e"),TEXT("f"),TEXT("g"),TEXT("h"),TEXT("i"),TEXT("j"),TEXT("k"), TEXT("l"),TEXT("m"),TEXT("n"),TEXT("o"),TEXT("p"),TEXT("q"),TEXT("r"),TEXT("s"),TEXT("t"),TEXT("u"),TEXT("v"),TEXT("w"),TEXT("x"),TEXT("y"),TEXT("z"),
	TEXT("A"), TEXT("B"),TEXT("C"), TEXT("D"),TEXT("E"),TEXT("F"),TEXT("G"),TEXT("H"),TEXT("I"),TEXT("J"),TEXT("K"), TEXT("L"),TEXT("M"),TEXT("N"),TEXT("O"),TEXT("P"),TEXT("Q"),TEXT("R"),TEXT("S"),TEXT("T"),TEXT("U"),TEXT("V"),TEXT("W"),TEXT("X"),TEXT("Y"),TEXT("Z"),
	TEXT("0"),TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5"),TEXT("6"),TEXT("7"),TEXT("8"),TEXT("9")
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hf1, hf2;
	HPEN hp;
	RECT rc;
	GetClientRect(hWnd, &rc);
	
	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;
		
	case WM_KEYDOWN:
		switch (wParam) {
			// Ű���� �Է�
		case VK_LEFT:
			if (loc > 0)
				loc--;
			break;
		case VK_RIGHT:
			if (loc < limit)
				loc++;
			break;

		case VK_RETURN: // ���͸� ������ ���� ����
			switch (condition)
			{
			case 0: // ����ȭ�鿡�� ���� �޴���
				condition = loc + 1;
				loc = 0;
				if (condition == 1) // ���Ӱ����� ���� ����
					limit = 3;
				break;
			case 1: // ���� -> ���Ӽ���
				switch (loc) // loc ���� ���� ������ �������α׷��� ���۽�Ŵ / �������� ������ ��.
				{
				case 1:
					WinExec(".\\Mouse.exe", SW_SHOW);
					PostQuitMessage(0);
					break;
				case 2:
					WinExec(".\\������ ����.exe", SW_SHOW);
					PostQuitMessage(0);
					break;
				case 3:
					WinExec(".\\Project3.exe", SW_SHOW);
					PostQuitMessage(0);
					break;
				}
				condition = loc; // ó��ȭ������ ����
				loc = 0;
				limit = 2;
				break;
			case 2: // ���� -> ����ǥ
				condition = loc; // ó��ȭ������ ����
				loc = 1;
				limit = 2;
				break;
			}
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hf1 = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
		hf2 = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
		(HFONT)SelectObject(hdc, hf1);
		TextOut(hdc, 220, 50, st1[0], lstrlen(st1[0])); // ����
		DeleteObject((HFONT)SelectObject(hdc, hf2)); // ���� �޴� ��Ʈ ����

		hp = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		(HPEN)SelectObject(hdc, hp);

		switch (condition)
		{
		case 0: // ����ȭ��
			switch (loc) // �޴� ���� Ŀ��
			{
			case 0:
				Rectangle(hdc, 145, 295, 255, 330);
				break;
			case 1:
				Rectangle(hdc, 360, 295, 445, 330);
				break;
			case 2:
				Rectangle(hdc, 545, 295, 630, 330);
				break;
			}
			TextOut(hdc, 150, 300, st1[1], lstrlen(st1[1]));
			TextOut(hdc, 365, 300, st1[2], lstrlen(st1[2]));
			TextOut(hdc, 550, 300, st1[3], lstrlen(st1[3]));
			break;

		case 1: // ���Ӽ���
			switch (loc)
			{
			case 0:
				Rectangle(hdc, 145, 295, 255, 330);
				break;
			case 1:
				Rectangle(hdc, 145, 345, 280, 380);
				break;
			case 2:
				Rectangle(hdc, 360, 345, 445, 380);
				break;
			case 3:
				Rectangle(hdc, 545, 345, 655, 380);
				break;
			}
			TextOut(hdc, 150, 300, st2[0], lstrlen(st2[0]));
			TextOut(hdc, 150, 350, st2[1], lstrlen(st2[1]));
			TextOut(hdc, 365, 350, st2[2], lstrlen(st2[2]));
			TextOut(hdc, 550, 350, st2[3], lstrlen(st2[3]));
			break;

		case 2: // ����ǥ 
			Rectangle(hdc, 145, 295, 255, 330);
			TextOut(hdc, 150, 300, st3[0], lstrlen(st3[0]));
			TextOut(hdc, 300, 150, st3[1], lstrlen(st3[1]));
			// ���� ���α׷��� �ִ� ��ġ�� ���ھ� ������ ������ ������.
			hFile = CreateFile(TEXT(".\\score.txt"), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			for (int i = 0; i < 55; i++)
			{
				SetFilePointer(hFile, sizeof(CHAR) * i, NULL, FILE_BEGIN);
				ReadFile(hFile, ff[i], sizeof(CHAR), &nr, NULL);

				// ���� -> ���� : Tab
				for (int k = 52; k < 62; k++)
				{
					if (0 == lstrcmp(ch[k], ff[i]) && flag == 0)
					{
						flag = 1;
						j++;
						break;
					}
				}

				// ���� -> ���� : �ٹٲ�
				for (int k = 0; k < 52; k++)
				{
					if (0 == lstrcmp(ch[k], ff[i]) && flag == 1)
					{
						flag = 0;
						l++;
						j = 0;
						break;
					}

				}

				m = 300 + 15 * i + 75 * j;

				TextOut(hdc, m, 200 + 50 * l, ff[i], sizeof(CHAR));
				ff[i][0] = NULL; // �̰ž��ϸ� ���ǹ� �ν��� ����. (����� ����)
			}
			CloseHandle(hFile);
			l = 0;
			j = 0;
			flag = 0;
			break;
			
		case 3: // ��������
			PostQuitMessage(0);
		}
		DeleteObject((HPEN)SelectObject(hdc, hp));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
