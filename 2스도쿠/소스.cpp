#include <windows.h>
#include<string>
#define _CRT_SECURE_NO_WARNINGS
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("스도쿠 게임");
WNDPROC OldEditProc, OldEditProc1;
HBRUSH bkBrush = CreateSolidBrush(RGB(135, 206, 235));//배경의 전체 색깔을 결정한다.

int a3[9][9];
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = bkBrush;
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;// | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//행렬의 크기, 선의 크기, 시작 숫자.
int sum[9][9];
int sawcheck(int b) //세로줄 체크 부분.
{
	int count[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sum[b][i] == count[j])
			{
				count[j] = 0;
				break;
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (count[i] != 0)
		{
			return 1;
		}

	}
	return 0;
}
TCHAR str[256];
int rawcheck(int b)//가로줄
{
	int count[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	for (int i=0; i < 9; i++)
	{
		for (int j=0; j < 9; j++)
		{
			if (sum[i][b] == count[j])
			{
				count[j] = 0;
				break;
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{ 
		if (count[i] != 0)
		{
			return 1;
		}

	}
	return 0;
}
//하나의 줄을 검사하고, 9개 중 하나라도 0으로 바뀌지 않으면 1을 리턴한다.
int reackcheck(int c, int k)//c= 몇 번째 줄, 행인지 확인
{
	int count[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	for (int i=c; i < c+3; i++)
	{
		for (int j = k; j < k + 3; j++)
		{
			for (int w = 0; w < 9; w++)
			{
				if (sum[j][i] == count[w])
				{
					count[w] = 0;
					break;
				}
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (count[i] != 0)
		{
			return 1;
		}
	}
	return 0;
} //하나의 줄을 검사하고, 9개 중 하나라도 0으로 바뀌지 않으면 1을 리턴한다.

int count;// 현재 점수가 들어갈 곳.
TCHAR str1[256];
HWND search,submit;
enum { ID_R1 = 101, ID_R2};
CHAR h;
HWND hwndcheck;
int a0[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int a1[3][3] = { 0, 0, 1, 1, 0, 0,0,1,0};// 연산을 담당하는 행렬
int a2[3][3] = { 0, 1, 0, 0, 0, 1, 1, 0, 0 }; // 연산을 담당하는 행
int moive[9][9];//정답을 저장하는 알고리즘.
int (*getmix(int (*a)[3], int (*c)[3]))[3]//2차원 배열 인자로 넘기기.
{
	static int dhsn[3][3];
	int  MULT= 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MULT = 0;
			for (int k = 0; k < 3; k++)
			{
				MULT += a[i][k] * c[k][j];
			}
			dhsn[i][j] = MULT;
		}
	}
	return dhsn;//2차원 배열의 곱셈을 리턴한다.
}
int(*getmix(int(*a)[3], int(*c)[3], int(*b)[3]))[3]//2차원 배열 인자로 넘기기.
{
	static int dhsn[3][3];
	static int dhsn1[3][3];
	int  MULT = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MULT = 0;
			for (int k = 0; k < 3; k++)
			{
				MULT += a[i][k] * c[k][j];
			}
			dhsn[i][j] = MULT;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MULT = 0;
			for (int k = 0; k < 3; k++)
			{
				MULT += dhsn[i][k] * b[k][j];
			}
			dhsn1[i][j] = MULT;
		}
	}
	return dhsn1;
}//함수의 이중 정의

void put(int(*numPtr)[3], int c, int k)//집어넣을 행렬, 몇 번째 줄, 행인지 확인
{
    for (int i = c; i < c + 3; i++)//몇번쨰 줄인 지.
	{
		for (int j = k; j < k + 3; j++)//몇번쨰 행인지.
		{
			sum[i][j] = numPtr[i % 3][j % 3];
		}
	}
}
void change9()//각 9x9 배열에 들어갈 베이스 3*3 배열을  8개를 만든다(스도쿠 알고리즘 참조)
{
	put(a0, 0, 0);//1번째
	put(getmix(a1, a0), 0, 3);//두번째
	put(getmix(a2, a0), 0, 6);//세번째
	put(getmix(a0, a1), 3, 0);//네번째
	put(getmix(a1, a0, a1), 3, 3);//다섯번째
	put(getmix(a2, a0, a1), 3, 6);//여섯번째
	put(getmix(a0, a2), 6, 0);//7번째
	put(getmix(a1, a0,a2), 6, 3);//8번쨰
	put(getmix(a2, a0, a2), 6, 6);//9번째.

	int random1, random2;

	for (int i = 0; i < 65; i++)
	{
		random1 = rand() % 9;
		random2 = rand() % 9;
		sum[random1][random2] = 0;
	}
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			a3[i][j] = sum[i][j];
		}
	}
	InvalidateRect(hwndcheck, NULL, TRUE);
}

void change()//3x3의 베이스 스도쿠를 만든다.
{
	for (int i = 0; i < 50; i++)
	{
		int randNum1 = rand() % 3;
		int randNum2 = rand() % 3;
		int randNum3 = rand() % 3;
		int randNum4 = rand() % 3;
		int temp;
		temp = a0[randNum1][randNum2];
		a0[randNum1][randNum2] = a0[randNum3][randNum4];
		a0[randNum3][randNum4] = temp;
	}
	change9();
} //3x3의 베이스 행을 만든다.

void init(HWND hWnd) {//게임 초기화.
	int i, j; //게임이 연속 될때를 대비해서
	for (i = 0; i<9; i++)
		for (j = 0; j<9; j++){
			sum[i][j] = 0;
			a3[i][j]=0;
		}
	count = 0;
	change();
	InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK buttonSubProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int icountx = 0;
	int icounty = 0;
	int icountz = 0;
	TCHAR buf[128];

	switch (iMessage)
	{
	case WM_LBUTTONUP:

		for (int i = 0; i < 9; i++)
		{
			icountx += rawcheck(i);
			icounty += sawcheck(i);

		}//하나의 줄을 검사하고, 9개 중 하나라도 0으로 바뀌지 않으면 1을 리턴한다.

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				icountz += reackcheck(3 * i, 3 * j);
			}
		}
		if (icountx == 0 && icounty == 0 && icountz == 0)
		{
			MessageBox(hWnd, TEXT("모든 답이 정답입니다. 제출하면 점수를 받습니다."),
				TEXT("확인"), MB_OK);
		}
		else
		{
			wsprintf(buf, TEXT("현재 틀린 게 존재합니다.\n\n\n 가로변은 %d 개 \n 세로변은 %d 개 \n 사각형은 %d 개가 틀렸습니다. \n 그러므로 점수가 있을 경우, -100점을 잃게 됩니다."), icountx,icounty,icountz);
			MessageBox(hWnd, buf, TEXT("확인"), MB_OK);	
		}
		break;
	case WM_LBUTTONDOWN:
		PostMessage(hWnd, EM_SETSEL, 0, -1);
		break;
	}
	return CallWindowProc(OldEditProc1, hWnd, iMessage, wParam, lParam);
}//얼마나 틀렸는지를 확인.

LRESULT CALLBACK buttonSubProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int icountx = 0;
	int icounty = 0;
	int icountz = 0;
	TCHAR *buf = { 0 };

	int count1 = 0;
 	switch (iMessage)
	{
	case WM_LBUTTONUP:
		for (int i = 0; i < 9; i++)
		{
			icountx += rawcheck(i);
			icounty += sawcheck(i);

		}//하나의 줄을 검사하고, 9개 중 하나라도 0으로 바뀌지 않으면 1을 리턴한다.

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				icountz += reackcheck(3*i, 3*j);
			}
		}
		if (icountx == 0 && icounty == 0 && icountz == 0)
		{
			count = count + 100;	
			init(hwndcheck);
			InvalidateRect(hwndcheck, NULL, TRUE);
			UpdateWindow(hwndcheck);
			MessageBox(hWnd, TEXT("정답을 맞추었습니다. 다음 문제로 넘어갑니다."),
				TEXT("제출"), MB_OK);
			change();
		}
		else
		{
			if (count != 0)
			{
				count = count - 100;
				InvalidateRect(hwndcheck, NULL, TRUE);
				init(hwndcheck);
				UpdateWindow(hwndcheck);
			}
			if (MessageBox(hWnd, TEXT("정답을 틀렸습니다. 다시 풀어보시려면 예(Y), 포기하시려면 아니오(N)를 두번 눌려주세요. 게임을 종료하시려면 취소를 세 번 눌려주세요"), TEXT("제출"), MB_YESNOCANCEL) == IDYES)
			{

			}
			else if (MessageBox(hWnd, TEXT("정답을 틀렸습니다. 다시 풀어보시려면 예(Y), 포기하시려면 아니오(N)를 두번 눌려주세요. 게임을 종료하시려면 취소를 세 번 눌려주세요"), TEXT("제출"), MB_YESNOCANCEL) == IDNO)
			{
				if (MessageBox(hWnd, TEXT("정말 초기화하실꺼에염???."), TEXT("초기화"), MB_YESNO) == IDYES)
				{
					init(hwndcheck);
				}
			}
			else if (MessageBox(hWnd, TEXT("정답을 틀렸습니다. 다시 풀어보시려면 예(Y), 포기하시려면 아니오(N)를 두번 눌려주세요. 게임을 종료하시려면 취소를 세 번 눌려주세요"), TEXT("제출"), MB_YESNOCANCEL) == IDCANCEL)
			{
				if (MessageBox(hWnd, TEXT("정말 종료하실 꺼에염???"), TEXT("종료"), MB_YESNO) == IDYES)
				{
					PostQuitMessage(0);
				}
			}
		}
		break;
		case WM_LBUTTONDOWN:
		{
			PostMessage(hWnd, EM_SETSEL, 0, -1);
		break;
		}
	}
	return CallWindowProc(OldEditProc, hWnd, iMessage, wParam, lParam);
}//그걸 누를 경우, 정답이면 점수를 추가하고, 틀리면 오답 문구와 함께 다시 풀어볼 건지 아니면 다시 할 껀지, 그도 아니면 종료할 건지를 결정.

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT  rect;
	RECT rt;
	HBRUSH hBrush;
	TCHAR *Mes = TEXT("나는야 스도쿠 놀이");
	TCHAR *Mes1 = TEXT(" 게임 규칙: 이 게임은 9*9 스도쿠 놀이이며, 가로, 세로, 3x3이 9 칸이 1-9사이의 수가  되어야 성립합니다. 그리고 정답을 맞추면 100점을, 틀리면 -100점을 차감합니다., 점수는 다른 게임들과 연동됩니다. \n 또 한가지는 옆의 버튼을 누르면 현재 틀린 변의 합계를 알 수 있습니다. 제출 버튼을 누를 경우 게임의 스코어를 계산합니다. \n 단, 이 게임엔 마이너스 점수 합계가 없습니다.");
	HFONT font;
	int nHeight = 0, nPoint;
	HPEN hPen;
	int len =0;
	TCHAR buf[128];
	int check = 0;
	static int x, y;
	static int oldx, oldy;
	static HWND hCtrlBlock;	

	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		search = CreateWindow(TEXT("button"), TEXT("확인"), WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON | WS_GROUP,
			28 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
		submit = CreateWindow(TEXT("button"), TEXT("제출"), WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON | WS_GROUP,
			34 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);//각 버튼의 역할은 각 버튼의 자식 윈도우에서 구현 예정.
		OldEditProc = (WNDPROC)SetWindowLongPtr(submit, GWLP_WNDPROC, (LONG_PTR)buttonSubProc1);//노드가 만들어짐과 동시에 서브 노드 생성.
		OldEditProc1 = (WNDPROC)SetWindowLongPtr(search, GWLP_WNDPROC, (LONG_PTR)buttonSubProc2);//노드가 만들어짐과 동시에 서브 노드 생성.
		//알고리즘에 값을 넣어야 할 듯.
		hwndcheck = hWnd;
		change9();
		return 0;

	case WM_LBUTTONDOWN:
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		x = (LOWORD(lParam)) / (rect.right / 13);
		y = (HIWORD(lParam)) / (rect.bottom / 13);//일단 클릭 버튼의 위치를 찾는다.
		return 0;

	case WM_CHAR:
	      h = (CHAR)wParam;//0~9까지 단 하나의 숫자만 받는다.
		  check = h - '0';//아스키 코드 사용,
		 if ((int)h == 8)
		 {
			 sum[x - 2][y - 2] = 0;
			 InvalidateRect(hWnd, NULL, TRUE);//윈도우를 재갱신 한다.(VK_back 메시지를 쓰려 했으나 충돌이 일어남.
		 }
	    else if ((2 <= x && x < 11) && (2 <= y && y < 11))//좌표수가 사각형 안에 들어야 가동.
		{
			hdc = BeginPaint(hWnd, &ps);
		
			if (a3[x-2][y-2] == 0)
			{
				wsprintf(str, TEXT("%d"), check);
				TextOut(hdc, 0, 0, str, lstrlen(str));
				EndPaint(hWnd, &ps);

				GetClientRect(hWnd, &rect);
				SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
				if (0 <= check && check <= 9)//그것이 숫자인지? 아니면 쓸때없는 문자인지 판별.
				{
					sum[x - 2][y - 2] = check;
					wsprintf(str1, TEXT("%d"), sum[x - 2][y - 2]);
					TextOut(hdc, x*rect.right / 13, y*rect.right / 13, str1, lstrlen(str1));
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else
				{
					wsprintf(buf, TEXT("그 위치에는 숫자만 들어갑니다."));
					MessageBox(hWnd, buf, TEXT("에러"), MB_OK | MB_ICONEXCLAMATION);
				}
			}
			else
			{
				wsprintf(buf, TEXT("그 위치에 입력된 값은 변경할 수 없습니다."));
				MessageBox(hWnd, buf, TEXT("경고 메시지"), MB_OK | MB_ICONEXCLAMATION);
			}
		}
		else
		{
			wsprintf(buf, TEXT("그 위치에는 값을 넣을 수 없습니다."));
			MessageBox(hWnd, buf, TEXT("경고 메시지"), MB_OK | MB_ICONEXCLAMATION);
		}
		return 0;

	case WM_GETMINMAXINFO://윈도우의 크기를 제한.
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 600;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;
		return FALSE;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		
		for (int v = 0; v < 13; v++)//헤드라인을 작성한다.
		{
			hPen = CreatePen(PS_SOLID, 0, RGB(250, 248, 210));
			(HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(250, 248, 210));
			(HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, v*rect.right / 13, 0, (v + 1) * rect.right / 13, 2 * rect.bottom / 13);
			//다시 그리기.
			DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
			DeleteObject((HPEN)SelectObject(hdc, hPen));
		}
		SetMapMode(hdc, MM_TEXT);
		nPoint = 40;
		//GetDeviceCaps는 1인치당의 픽셀 수를 뽑아냄.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서"));
		(HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(075, 0, 130));//글자색을 결정.
		SetBkColor(hdc, RGB(224, 255, 255));
		//??? 한글, MS Word의 10point 문자를 출력하면 제각각 다 다를 수 있다.   
		// 화면 보기 비율이 100% 인지 확인하자. 
		TextOut(hdc, 4 * rect.right / 39, 1 * rect.right / 39, Mes, lstrlen(Mes));
		DeleteObject((HFONT)SelectObject(hdc, font));//헤드라인의 글귀를 결정한다.

		for (int i = 2; i < 11; i++)
		{
			for (int j = 2; j < 11; j++)
			{
				if (0 <= (i-2)&& (i-2) < 3 && 0 <= (j-2) && (j-2) < 3)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 155, 0));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				else if (3 <= (i - 2) && (i - 2) < 6 && 0 <= (j - 2) && (j - 2) < 3)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 250));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				else if (3 <= (i - 2) && (i - 2) < 6 && 0 <= (j - 2) && (j - 2) < 3)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (6 <= (i - 2) && (i - 2) < 9 && 0 <= (j - 2) && (j - 2) < 3)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 88, 177));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (0 <= (i - 2) && (i - 2) < 3 && 3 <= (j - 2) && (j - 2) < 6)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(255, 88, 177));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (3 <= (i - 2) && (i - 2) < 6 && 3 <= (j - 2) && (j - 2) < 6)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(250, 255, 77));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (6 <= (i - 2) && (i - 2) < 9 && 3 <= (j - 2) && (j - 2) < 6)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 155, 77));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (0 <= (i - 2) && (i - 2) < 3 && 6 <= (j - 2) && (j - 2) < 9)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 155, 77));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (3<= (i - 2) && (i - 2) < 6 && 6 <= (j - 2) && (j - 2) < 9)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
				if (6 <= (i - 2) && (i - 2) < 9 && 6 <= (j - 2) && (j - 2) < 9)
				{
					hPen = CreatePen(PS_SOLID, 0, RGB(125, 0, 0));
					(HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(173, 216, 230));
					(HBRUSH)SelectObject(hdc, hBrush);
					Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
					//다시 그리기.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
			}
		}//그림 그리기.
		nPoint = 20;
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
		for (int i = 2; i < 11; i++)
		{
			for (int j = 2; j < 11; j++)
			{
				if (a3[i-2][j-2] == 0)
				{
					nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
					font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서"));
					(HFONT)SelectObject(hdc, font);
					SetTextColor(hdc, RGB(0, 0, 10));//글자색을 결정.
					SetBkColor(hdc, RGB(173, 216, 230));
					wsprintf(str1, TEXT("%d"), sum[i - 2][j - 2]);
					TextOut(hdc, (i * 3 + 1)*rect.right / 39, (j * 3 + 1)*rect.right / 41, str1, lstrlen(str1));
					DeleteObject((HFONT)SelectObject(hdc, font));
				}
				else
				{
					nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
					font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서"));
					(HFONT)SelectObject(hdc, font);
					SetTextColor(hdc, RGB(255, 0, 0));//글자색을 결정.
					SetBkColor(hdc, RGB(173, 216, 230));
					wsprintf(str1, TEXT("%d"), sum[i - 2][j - 2]);
					TextOut(hdc, (i * 3 + 1)*rect.right / 39, (j * 3 + 1)*rect.right / 41, str1, lstrlen(str1));
					DeleteObject((HFONT)SelectObject(hdc, font));
				}
			}
		}//사각형을 완성한다.

		for (int i = 0; i < 9; i++)
		{
			for (int j = 11; j < 13; j++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(219, 112, 147));
				(HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(219, 112, 147));
				(HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//다시 그리기.
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
				DeleteObject((HPEN)SelectObject(hdc, hPen));
			}
		}
		nPoint = 10;
		//GetDeviceCaps는 1인치당의 픽셀 수를 뽑아냄.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("바탕"));
		(HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(0, 0, 0));//글자색을 결정.
		SetBkColor(hdc, RGB(219, 112, 147));
		rt = { 0 * rect.right / 39, 32 * rect.right / 39, 27 * rect.right / 39, 39 * rect.right / 39 };
		DrawText(hdc, Mes1, -1, &rt, DT_CENTER | DT_WORDBREAK );
		DeleteObject((HFONT)SelectObject(hdc, font));

		for (int i = 9; i < 13; i++)
		{
			for (int j = 11; j < 12; j++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(238, 130, 238));
				(HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(238, 130, 238));
				(HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//다시 그리기.
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
				DeleteObject((HPEN)SelectObject(hdc, hPen));
			}
		}
		wsprintf(str, TEXT("전체 게임의 점수: %d"), count);
		TextOut(hdc, 29 * rect.right / 39, 33 * rect.right / 39, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("종료하시겠습니까?(점수를 기록하고 저장합니다.)"), TEXT("종료"), MB_YESNO) == IDNO)
		{
			// 파일 출력(점수기록) //
			return 0;
		}
		else {
			break;
		}
	case WM_DESTROY:
		// 파일 출력(점수기록) //
		WinExec(".\\manage.exe", SW_SHOW); // 관리프로그램 실행
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}