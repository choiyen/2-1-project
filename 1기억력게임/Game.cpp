#include <windows.h>
#include "resource.h"
#include <ctime>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("기억력 게임");

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//게임 난이도(속도)를 설정할 메뉴
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

//구조체 정의
typedef struct _Round {
	int line;
	int click;
} Round;

Round round[9] = { {2, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 5}, {4, 6}, {4, 7}, {5, 5}, {5, 6} }; //각 라운드의 설정
int nowRound = 0;		//현재 라운드 정보의 index
int nowLine;			//nxn 게임판의 생성에서의 n의 값
int playerClick = 1;	//플레이어가 클릭할 차례인지 아닌지 판별할 값
int clickCount = 0;		//플레이어가 클릭 한 횟수
POINT *pDex;			//각 라운드 별 클릭해야 하는 횟수의 동적배열
int speed = 250;		//게임 속도 설정 (난이도 설정)

//랜덤으로 좌표를 생성하여, 문제를 저장한다.
void getRandom() {
	srand((unsigned int)time(0));
	for (int i = 0; i < round[nowRound].click; i++) {
		int x = rand() % nowLine;
		int y = rand() % nowLine;
		pDex[i].x = x;
		pDex[i].y = y;
	}
}

//게임을 새로 시작할 때 설정 초기화
void resetGame(HWND hWnd) {
	nowRound = 0;
	nowLine = round[nowRound].line;
	clickCount = 0;
	playerClick = 1;
	InvalidateRect(hWnd, NULL, TRUE);
}

//다음 레벨로 넘어갈때의 설정 초기화
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
	case WM_COMMAND:		//게임 난이도(속도)를 설정하는 처리
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
	case WM_CREATE:		//게임 시작시 메시지박스 출력
		wsprintf(buf, TEXT("   시작하려면 SPACE key를 누르세요."));
		MessageBox(hWnd, buf, TEXT("Memory Game"), MB_OK | MB_ICONEXCLAMATION);
		nowLine = round[nowRound].line;
		return 0;
	case WM_KEYDOWN:	//스페이스바를 눌렀을 때, 문제를 출력할 수 있도록 함
		switch (wParam) {
		case VK_SPACE:
			if (playerClick == 1) {		//한 번만 클릭가능 하도록 key를 설정
				pDex = new POINT[round[nowRound].click];
				getRandom();
				playerClick = 0;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:	//마우스로 클릭 시 데이터 처리
		if (playerClick == 0) {
			GetClientRect(hWnd, &rect);
			SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
			x = (LOWORD(lParam)) / (rect.right / nowLine);
			y = (HIWORD(lParam)) / (rect.bottom / nowLine);

			if (pDex[clickCount].x == x && pDex[clickCount].y == y) {		//클릭이 옳게 된 경우 clickCount 증가
				clickCount++;
			}
			else {		//잘못된 경우 종료 메시지 출력
				wsprintf(buf, TEXT("   Died in %dLevel .\n   New Game ?"), nowRound+1);
				if (MessageBox(hWnd, buf, TEXT("Memory Game"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
					resetGame(hWnd);
					return 0;
				}
				else
					SendMessage(hWnd, WM_CLOSE, 0L, 0L);
			}

			if (clickCount == round[nowRound].click) {		//해당 라운드가 끝났는지 판단
				nowRound++;
				if (nowRound == 9) {		//모든 라운드가 종료된 경우 메시지박스
					wsprintf(buf, TEXT("   Cleared All Level.\n   New Game ?"));
					if (MessageBox(hWnd, buf, TEXT("Memory Game"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
						resetGame(hWnd);
						return 0;
					}
					else
						SendMessage(hWnd, WM_CLOSE, 0L, 0L);
				}
				else {		//각 라운드 종료 시의 메시지
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

		//게임판 작성
		for (int i = 0; i < nowLine; i++) {
			for (int j = 0; j < nowLine; j++)
				Rectangle(hdc, i*rect.right / nowLine, j*rect.bottom / nowLine, (i + 1) * rect.right / nowLine, (j + 1) * rect.bottom / nowLine);
		}

		//게임판의 출력과 클릭 위치의 출력은 깜빡임을 주기 위해 Brush와 Sleep을 사용하였음
		//게임판의 문제 출력
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

		//클릭하는 위치 출력
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
		if (MessageBox(hWnd, TEXT("종료하시겠습니까?(점수를 기록하고 저장합니다.)"), TEXT("종료"), MB_YESNO) == IDNO)
		{
			// 파일 출력(점수기록) //
			return 0;
		}
		else
			break;

	case WM_DESTROY:
		WinExec(".\\manage.exe", SW_SHOW); // 관리프로그램 실행
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}