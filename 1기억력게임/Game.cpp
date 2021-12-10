#include <windows.h>
#include "resource.h"
#include <ctime>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("���� ����");

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//���� ���̵�(�ӵ�)�� ������ �޴�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	hWndMain = hWnd;
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

//����ü ����
typedef struct _Round {
	int line;
	int click;
} Round;

Round round[9] = { {2, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 5}, {4, 6}, {4, 7}, {5, 5}, {5, 6} }; //�� ������ ����
int nowRound = 0;		//���� ���� ������ index
int nowLine;			//nxn �������� ���������� n�� ��
int playerClick = 1;	//�÷��̾ Ŭ���� �������� �ƴ��� �Ǻ��� ��
int clickCount = 0;		//�÷��̾ Ŭ�� �� Ƚ��
POINT *pDex;			//�� ���� �� Ŭ���ؾ� �ϴ� Ƚ���� �����迭
int speed = 250;		//���� �ӵ� ���� (���̵� ����)

//�������� ��ǥ�� �����Ͽ�, ������ �����Ѵ�.
void getRandom() {
	srand((unsigned int)time(0));
	for (int i = 0; i < round[nowRound].click; i++) {
		int x = rand() % nowLine;
		int y = rand() % nowLine;
		pDex[i].x = x;
		pDex[i].y = y;
	}
}

//������ ���� ������ �� ���� �ʱ�ȭ
void resetGame(HWND hWnd) {
	nowRound = 0;
	nowLine = round[nowRound].line;
	clickCount = 0;
	playerClick = 1;
	InvalidateRect(hWnd, NULL, TRUE);
}

//���� ������ �Ѿ���� ���� �ʱ�ȭ
void nextLevel(HWND hWnd) {
	clickCount = 0;
	nowLine = round[nowRound].line;
	playerClick = 1;
	InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT  rect;
	HBRUSH hBrush, oldBrush;
	TCHAR buf[128];
	int x, y;

	switch (iMessage) {
	case WM_COMMAND:		//���� ���̵�(�ӵ�)�� �����ϴ� ó��
		switch (wParam) {
		case ID_400:
			speed = 400;
			break;
		case ID_250:
			speed = 250;
			break;
		case ID_100:
			speed = 100;
			break;
		case ID_50:
			speed = 50;
			break;
		}
		resetGame(hWnd);
		return 0;
	case WM_CREATE:		//���� ���۽� �޽����ڽ� ���
		wsprintf(buf, TEXT("   �����Ϸ��� SPACE key�� ��������."));
		MessageBox(hWnd, buf, TEXT("Memory Game"), MB_OK | MB_ICONEXCLAMATION);
		nowLine = round[nowRound].line;
		return 0;
	case WM_KEYDOWN:	//�����̽��ٸ� ������ ��, ������ ����� �� �ֵ��� ��
		switch (wParam) {
		case VK_SPACE:
			if (playerClick == 1) {		//�� ���� Ŭ������ �ϵ��� key�� ����
				pDex = new POINT[round[nowRound].click];
				getRandom();
				playerClick = 0;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:	//���콺�� Ŭ�� �� ������ ó��
		if (playerClick == 0) {
			GetClientRect(hWnd, &rect);
			SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
			x = (LOWORD(lParam)) / (rect.right / nowLine);
			y = (HIWORD(lParam)) / (rect.bottom / nowLine);

			if (pDex[clickCount].x == x && pDex[clickCount].y == y) {		//Ŭ���� �ǰ� �� ��� clickCount ����
				clickCount++;
			}
			else {		//�߸��� ��� ���� �޽��� ���
				wsprintf(buf, TEXT("   Died in %dLevel .\n   New Game ?"), nowRound+1);
				if (MessageBox(hWnd, buf, TEXT("Memory Game"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
					resetGame(hWnd);
					return 0;
				}
				else
					SendMessage(hWnd, WM_CLOSE, 0L, 0L);
			}

			if (clickCount == round[nowRound].click) {		//�ش� ���尡 �������� �Ǵ�
				nowRound++;
				if (nowRound == 9) {		//��� ���尡 ����� ��� �޽����ڽ�
					wsprintf(buf, TEXT("   Cleared All Level.\n   New Game ?"));
					if (MessageBox(hWnd, buf, TEXT("Memory Game"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
						resetGame(hWnd);
						return 0;
					}
					else
						SendMessage(hWnd, WM_CLOSE, 0L, 0L);
				}
				else {		//�� ���� ���� ���� �޽���
					wsprintf(buf, TEXT("   %dRound Clear\n   pressed 'SPACE'key"), nowRound);
					MessageBox(hWnd, buf, TEXT("Memory Game"), MB_OK | MB_ICONEXCLAMATION);
					nextLevel(hWnd);
					return 0;
				}
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);

		//������ �ۼ�
		for (int i = 0; i < nowLine; i++) {
			for (int j = 0; j < nowLine; j++)
				Rectangle(hdc, i*rect.right / nowLine, j*rect.bottom / nowLine, (i + 1) * rect.right / nowLine, (j + 1) * rect.bottom / nowLine);
		}

		//�������� ��°� Ŭ�� ��ġ�� ����� �������� �ֱ� ���� Brush�� Sleep�� ����Ͽ���
		//�������� ���� ���
		if (playerClick == 0 && clickCount == 0) {
			for (int i = 0; i < round[nowRound].click; i++) {
				hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, pDex[i].x*rect.right / nowLine, pDex[i].y*rect.bottom / nowLine, (pDex[i].x + 1)*rect.right / nowLine, (pDex[i].y + 1)*rect.bottom / nowLine);
				SelectObject(hdc, oldBrush);
				DeleteObject(hBrush);
				Sleep(speed);
				Rectangle(hdc, pDex[i].x*rect.right / nowLine, pDex[i].y*rect.bottom / nowLine, (pDex[i].x + 1)*rect.right / nowLine, (pDex[i].y + 1)*rect.bottom / nowLine);
				Sleep(speed);
			}
		}

		//Ŭ���ϴ� ��ġ ���
		if (clickCount != 0) {
			hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, pDex[clickCount - 1].x*rect.right / nowLine, pDex[clickCount - 1].y*rect.bottom / nowLine, (pDex[clickCount - 1].x + 1)*rect.right / nowLine, (pDex[clickCount - 1].y + 1)*rect.bottom / nowLine);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			Sleep(200);
			Rectangle(hdc, pDex[clickCount - 1].x*rect.right / nowLine, pDex[clickCount - 1].y*rect.bottom / nowLine, (pDex[clickCount - 1].x + 1)*rect.right / nowLine, (pDex[clickCount - 1].y + 1)*rect.bottom / nowLine);
		}

		EndPaint(hWnd, &ps);
		return 0;
		
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("�����Ͻðڽ��ϱ�?(������ ����ϰ� �����մϴ�.)"), TEXT("����"), MB_YESNO) == IDNO)
		{
			// ���� ���(�������) //
			return 0;
		}
		else
			break;

	case WM_DESTROY:
		WinExec(".\\manage.exe", SW_SHOW); // �������α׷� ����
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}