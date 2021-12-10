#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <mmsystem.h> // sound 기능사용

#include "resource.h"

#pragma comment(lib,"winmm")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Typing Practice (Zombie Survival.ver)");

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, /*바로 옆의 것이 화면 크기임*/CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

// 단어 리스트 : 배열 -> 파일읽기 -> 랜덤발생 & 인터넷에서 검사
TCHAR dic[30][255] = { 
	TEXT("alpha"),
	TEXT("bravo"),
	TEXT("charlie"),
	TEXT("delta"),
	TEXT("echo"),
	TEXT("foxtrot"),
	TEXT("golf"),
	TEXT("hotel"),
	TEXT("india"),
	TEXT("juliet"), // 10
	TEXT("kilo"),
	TEXT("lima"),
	TEXT("mike"),
	TEXT("november"),
	TEXT("oscar"),
	TEXT("papa"),
	TEXT("quebec"),
	TEXT("romeo"),
	TEXT("sierra"),
	TEXT("tango"), // 20
	TEXT("uniform"),
	TEXT("victor"),
	TEXT("whiskey"),
	TEXT("x-ray"),
	TEXT("yankee"),
	TEXT("zulu")
};

// 오브젝트를 그려주는 기능 함수
void DrawObject(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	(HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(hdc, hBit);
	DeleteDC(MemDC);
}

// 게임 시스템 변수
int speed_op = 100;

// 플레이어 변수
int life = 100;
TCHAR life_s[255];

int money = 1000;
TCHAR money_s[255];

int condition;

// 적 오브젝트 변수
typedef struct enemyobject
{
	float x;
	float y;
	TCHAR s[255];
	COLORREF c;
	int flag;

} eo;
eo e[100];
int c;
int e_cnt = 5; // 소환되는 적 유닛 수 (난이도 조정)
float e_speed = 1; // 적 캐릭터 움직이는 비율 (난이도 조정)
float e_hit_area = 50;

int e_total = 50;
TCHAR e_total_s[255];

// 타자기 영역
TCHAR s[20] = TEXT("단어 입력 : ");
TCHAR type_s[255];
int t_len;
int correct = -999; // 검증값 : 0 이면 일치 그 외는 불일치

int sc;

TCHAR acc_s[255];
int total, ok, ratio;

int s_flag = 0; // 0이면 중지, 1이면 시작
int p_flag = 0; // 0이면 시작, 1이면 중지
int temp_con;

float e_slow = 0.7;
int slow_cnt;
int slow_flag;

TCHAR status[10][255] = { TEXT("[ Zombie Hit! ]"), TEXT("[ Zombie Attack... ]"), TEXT("[ 일시정지 ]"), TEXT("[ 게임 클리어! ]"), TEXT("[ 생존자 사망 ]")};

// 게임설명 자식 창 생성 / 그러나 알 수 없는 이유로 BOOL방식으로 처리불가하여 임시방편으로 구성
LRESULT CALLBACK InfoDlg(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBRUSH hb;
	RECT rc;
	GetClientRect(hWnd, &rc);
	SYSTEMTIME st;

	// 게임화면과 타자부분을 구분
	int height = rc.bottom - rc.top - 5;
	RECT rc1 = { rc.left + 5, rc.top + 5, rc.right - 5, height / 6 * 5 + 2 };
	RECT rc2 = { rc.left + 5,height / 6 * 5, rc.right - 5, height };

	// 캐릭터 오브젝트
	HBITMAP bm;

	// MemDC 관련 변수
	static HBITMAP b_player, b_enemy, b_background;

	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		SetTimer(hWnd, 1, speed_op, NULL); // 타이머는 0.1초를 주기로 동작, 난이도 정할때?
		srand(time(NULL));

		b_background = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_background));
		b_player = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_player));;
		b_enemy = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_enemy));

		hdc = GetDC(hWnd);

		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_COMMAND: // 메뉴창 제어
		switch (LOWORD(wParam))
		{
			// 게임설명
		case ID_explain:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, InfoDlg);
			break;

			// 시작(스테이지 설정)
		case ID_lv1:
			for (int i = 0; i < e_cnt; i++)
				e[i].flag = 0;
			e_cnt = 5;
			e_speed = 1;
			e_total = 50;
			s_flag = 1;
			life = 100;
			break;
		case ID_lv2:
			for (int i = 0; i < e_cnt; i++)
				e[i].flag = 0;
			e_cnt = 8;
			e_speed = 1.5;
			e_total = 75;
			s_flag = 1;
			life = 100;
			break;
		case ID_lv3:
			for (int i = 0; i < e_cnt; i++)
				e[i].flag = 0;
			e_cnt = 10;
			e_speed = 2;
			e_total = 100;
			s_flag = 1;
			life = 100;
			break;
		case ID_test:
			for (int i = 0; i < e_cnt; i++)
				e[i].flag = 0;
			e_cnt = 5;
			e_speed = 1;
			e_total = 5;
			s_flag = 1;
			life = 100;
			break;

			// 일시정지
		case ID_pause:
			if (p_flag == 0 && s_flag == 1)
			{
				p_flag++;
				temp_con = condition;
				condition = 3;
			}
			else if (p_flag == 1 && s_flag == 1)
			{
				condition = temp_con;
				p_flag--;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

			// 아이템 사용
		case ID_shot:
			if (money >= 200 && s_flag == 1 && p_flag == 0) {
				PlaySound(MAKEINTRESOURCE(IDR_item_shot), g_hInst, SND_RESOURCE | SND_ASYNC);
				e[rand() % e_cnt].flag = 0;
				e_total--;
				money -= 200;
			}
			break;
		case ID_slow:
			if (money >= 500 && s_flag == 1 && p_flag == 0) {
				PlaySound(MAKEINTRESOURCE(IDR_item_slow), g_hInst, SND_RESOURCE | SND_ASYNC);
				money -= 500;
				slow_cnt = 50; // 100ms에 50번이면.. 5초?
				slow_flag = 1;
			}
			break;
		case ID_heal:
			if (money >= 700 && s_flag == 1 && life < 50 && p_flag == 0) {
				PlaySound(MAKEINTRESOURCE(IDR_item_heal), g_hInst, SND_RESOURCE | SND_ASYNC);
				money -= 700;
				life += 50;
			}
			break;
		}
		return 0;

	case WM_TIMER:
		if (p_flag == 0 && s_flag == 1)
		{
			GetLocalTime(&st);
			c = rand() % 4;

			for (int i = 0; i < e_cnt; i++)
			{
				// 적 오브젝트 생성
				if (e[i].flag == 0)
				{
					switch (c) {
					case 0:
						e[i].x = (float)rc1.left;
						e[i].y = (float)(rand() % (rc1.bottom - rc1.top));
						break;
					case 1:
						e[i].x = (float)rc1.right;
						e[i].y = (float)(rand() % (rc1.bottom - rc1.top));
						break;
					case 2:
						e[i].x = (float)(rand() % (rc1.right - rc1.left));
						e[i].y = (float)rc1.top;
						break;
					case 3:
						e[i].x = (float)(rand() % (rc1.right - rc1.left));
						e[i].y = (float)rc1.bottom;
						break;
					}
					e[i].flag = 1;
					e[i].c = RGB(255, (rand() % 100 + 100), 100);
					lstrcpy(e[i].s, dic[sc]);
					sc++;
					if (sc > 25)
						sc = 0;
				}

				// 적 오브젝트가 플레이어에게 도달했을때
				if (abs(e[i].x - (rc1.right - rc1.left) / 2) < e_hit_area && abs(e[i].y - (rc1.bottom - rc1.top) / 2) < e_hit_area)
				{
					PlaySound(MAKEINTRESOURCE(IDR_zombiesound), g_hInst, SND_RESOURCE | SND_ASYNC);
					condition = 2;
					life -= 10;
					total++;
					ratio = ok * 100 / total;
					e[i].flag = 0;
				}

				if (life == 0)
				{
					PlaySound(MAKEINTRESOURCE(IDR_die), g_hInst, SND_RESOURCE | SND_ASYNC);
					money -= 500;
					condition = 5;
					s_flag = 0;
				}

				// 적 오브젝트의 이동
				if (abs(e[i].x - (rc1.right - rc1.left) / 2) >= e_speed)
				{
					if (e[i].x > (rc1.right - rc1.left) / 2)
						e[i].x -= e_speed - e_slow * slow_flag;
					else if (e[i].x < (rc1.right - rc1.left) / 2)
						e[i].x += e_speed - e_slow * slow_flag;
				}

				if (abs(e[i].y - (rc1.bottom - rc1.top) / 2) >= e_speed)
				{
					if (e[i].y > (rc1.bottom - rc1.top) / 2)
						e[i].y -= e_speed - e_slow * slow_flag;
					else if (e[i].y < (rc1.bottom - rc1.top) / 2)
						e[i].y += e_speed - e_slow * slow_flag;
				}
			}
			slow_cnt--;
			if (slow_cnt == 0)
				slow_flag = 0;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		return 0;

	case WM_KEYDOWN:
		if (p_flag == 0 && s_flag == 1)
		{
			switch (wParam) {

				// 엔터키를 누름으로써 입력한 단어와 일치하면 적 오브젝트를 파괴
			case VK_RETURN:

				for (int i = 0; i < e_cnt; i++)
				{
					correct = lstrcmp(type_s, e[i].s);
					if (correct == 0)
					{
						PlaySound(MAKEINTRESOURCE(IDR_gunsound), g_hInst, SND_RESOURCE | SND_ASYNC);
						condition = 1;
						money += 100;
						e[i].flag = 0;
						ok++;
						e_total--;
						break;
					}
				}
				total++;
				ratio = ok * 100 / total;
				t_len = lstrlen(type_s);
				for (int i = t_len; i >= 0; i--)
					type_s[i] = NULL;
				break;

			case VK_BACK: // 입력한 값 지우기
				t_len = lstrlen(type_s);
				if (t_len > 0) // -가 되면 종료되어버리는데 이를 방지
					type_s[t_len - 1] = NULL;
				break;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_CHAR:
		if (p_flag == 0 && s_flag == 1)
		{
			if (wParam != VK_BACK && wParam != VK_RETURN) {
				t_len = lstrlen(type_s);
				type_s[t_len] = (TCHAR)wParam;
				type_s[t_len + 1] = 0;

				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// 게임배경
		DrawObject(hdc, rc.left, rc.top, b_background);

		////////////////////////// 게임화면 영역 ////////////////////////
		//(HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH)); // 캐릭터 주변영역 투명하게
		Ellipse(hdc, (rc1.right - rc1.left) / 2 - e_hit_area, (rc1.bottom - rc1.top) / 2 - e_hit_area, (rc1.right - rc1.left) / 2 + e_hit_area, (rc1.bottom - rc1.top) / 2 + e_hit_area);
		DrawObject(hdc, (rc1.right - rc1.left) / 2 - 11, (rc1.bottom - rc1.top) / 2 - 30, b_player);

		wsprintf(life_s, TEXT("%d"), life);
		TextOut(hdc, (rc1.right - rc1.left) / 2 - 12, (rc1.bottom - rc1.top) / 2 - 45, life_s, lstrlen(life_s));

		// 적 오브젝트 : 난이도에 따라 스레드를 활용하여 한번에 생성가능한 양을 조절
		for (int i = 0; i < 10; i++)
		{
			if (e[i].flag == 1)
			{
				for (int i = 0; i < e_cnt; i++)
				{
					hb = CreateSolidBrush(e[i].c);
					(HBRUSH)SelectObject(hdc, hb);
					if (p_flag == 0 && s_flag == 1)
					{
						Rectangle(hdc, (e[i].x - (float)(7.27 * lstrlen(e[i].s) / 2) - 3), e[i].y - 53, e[i].x + (4 * lstrlen(e[i].s)), e[i].y - 31);
						DeleteObject((HBRUSH)SelectObject(hdc, hb));
						TextOut(hdc, e[i].x - (float)(7.27 * lstrlen(e[i].s) / 2), e[i].y - 50, e[i].s, lstrlen(e[i].s));
					}
					DrawObject(hdc, e[i].x - 10.5, e[i].y - 20, b_enemy);
				}
			}
		}

		/////////////////////////// 타자 영역 ///////////////////////////
		// 단어 입력
		TextOut(hdc, (rc2.left + rc2.right) / 5 * 1, (rc2.top + rc2.bottom) / 2 - 10, s, lstrlen(s));
		TextOut(hdc, (rc2.left + rc2.right) / 5 * 1 + 85, (rc2.top + rc2.bottom) / 2 - 10, type_s, lstrlen(type_s));

		// 정확도
		wsprintf(acc_s, TEXT("정확도 : %d / %d (%d%%) "), ok, total, ratio);
		TextOut(hdc, rc2.right - 175, rc2.top + 15, acc_s, lstrlen(acc_s));

		// 상태 출력 영역
		if (condition == 1)
			TextOut(hdc, (rc.right - rc.left) / 2 - 50, rc.bottom - 150, status[0], lstrlen(status[0]));
		else if (condition == 2)
			TextOut(hdc, (rc.right - rc.left) / 2 - 50, rc.bottom - 150, status[1], lstrlen(status[1]));
		else if (condition == 3)
			TextOut(hdc, (rc.right - rc.left) / 2 - 50, rc.bottom - 150, status[2], lstrlen(status[2]));
		else if (condition == 4)
			TextOut(hdc, (rc.right - rc.left) / 2 - 50, rc.bottom - 150, status[3], lstrlen(status[3]));
		else if (condition == 5)
			TextOut(hdc, (rc.right - rc.left) / 2 - 50, rc.bottom - 150, status[4], lstrlen(status[4]));

		// 아이템, 재화, 적 수
		wsprintf(money_s, TEXT("Money : %d $"), money);
		TextOut(hdc, rc1.right - 150, rc1.top + 10, money_s, lstrlen(money_s));

		if (s_flag == 1 && e_total > 0)
		{
			wsprintf(e_total_s, TEXT("남은 좀비 수 : %d"), e_total);
			TextOut(hdc, 5, 5, e_total_s, lstrlen(e_total_s));
		}
		else if (s_flag == 1 && e_total <= 0) // 클리어
		{
			s_flag = 0;
			condition = 4;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_CLOSE:
		if(p_flag == 0)
			p_flag++; // 일시정지
		InvalidateRect(hWnd, NULL, TRUE); // 단어 지우기 (cheat방지)

		if (MessageBox(hWnd, TEXT("종료하시겠습니까?(점수를 기록하고 저장합니다.)"), TEXT("종료"), MB_YESNO) == IDNO)
		{
			// 파일 출력(점수기록) //
			return 0;
		}
		else
		{
			if (p_flag == 1) // 스테이지가 동작중이면
				p_flag--; // 일시정지 해제
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		//return 0;

	case WM_DESTROY:
		// 파일 출력 // (위에서 안되면)
		WinExec(".\\manage.exe", SW_SHOW); // 관리프로그램 실행
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
