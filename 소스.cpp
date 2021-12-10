#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("스도쿠 게임");
WNDPROC OldEditProc;
HBRUSH bkBrush = CreateSolidBrush(RGB(135, 206, 235));//배경의 전체 색깔을 결정한다.

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
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
}//행렬의 크기, 선의 크기, 시작 숫자.
int sum[9][9];
int rawcheck(int acount, int b)//아직 완성 안된 가로줄 체크 부분.
{
	int count[9] = { 1, 2, 3, 4, 5, 7, 8, 9 };
	for (int i=0; i < 9; i++)
	{
		for (int j=0; j < 9; j++)
		{
			if (sum[b][i] == count[j])
			{
				count[j] = 0;
				return 1;
			}
		}
	}

}
TCHAR str[256];
int sawcheck(int acount, int b)//세로줄
{
	int count[9] = { 1, 2, 3, 4, 5, 7, 8, 9 };
	
	for (int i=0; i < 9; i++)
	{
		for (int j=0; j < 9; j++)
		{
			if (sum[i][b] == count[j])
			{
				count[j] = 0;
				return 1;
			}
		}
	}

}
int reackcheck(int c,  int b)//사각형
{

	int count[9] = { 1, 2, 3, 4, 5, 7, 8, 9 };
	
	for (int i=c; i < c+3; i++)
	{
		for (int j = c; j < c + 3; j++)
		{
			for (int k = 0; j=k < 9; j++)
			{
				if (sum[i][j] == count[k])
				{
					count[k] = 0;
					return 1;
				}
			}
		}
	}

}
TCHAR str1[256];
void init(HWND hWnd) {//게임 초기화.
	int i, j; //게임이 연속 될때를 대비해서
	for (i = 0; i<9; i++)
		for (j = 0; j<9; j++){
			sum[i][j] = 0;
		}
	InvalidateRect(hWnd, NULL, TRUE);
}
int count = 0;// 현재 점수가 들어갈 곳.
int countx; //맞는 가로변수.
int county; //맞는 가로변수.
HWND search,submit;
enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 };
CHAR h;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT  rect;
	RECT rt;
	HBRUSH hBrush, oldBrush;
	TCHAR *Mes = TEXT("나는야 스도쿠 놀이");
	TCHAR *Mes1 = TEXT(" 게임 규칙: 이 게임은 9*9 스도쿠 놀이이며, 가로, 새로, 3x3이 9 칸이 0-9사이의 수가  되어야 성립합니다. 그리고 선을 맞추면 +100점씩 더하고 틀리면 점수를 -100을 차감하며, 점수는 다른 게임들과 연동됩니다. 또 한가지는 옆의 버튼을 누르면 현재 맞은 변의 합계를 알 수 있습니다. 그리고 제출 버튼을 누를 경우 게임의 스코어를 계산합니다.");
	HFONT font, oldfont;
	int nHeight = 0, nPoint;
	HPEN hPen,oPen;
	int len =0;
	TCHAR buf[128];
	int check = 0;
	static int x, y;
	static int oldx, oldy;
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
			34 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);//각 버튼의 역할은 각 버튼의 자식 윈도우에서 구현 예정. 버튼을 생성함.
		return 0;
	case WM_LBUTTONDOWN:
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		x = (LOWORD(lParam)) / (rect.right / 13);
		y = (HIWORD(lParam)) / (rect.bottom / 13);//일단 클릭 버튼의 위치를 찾는다. / 버튼을 위치를 잡는다. 
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
		
			wsprintf(str, TEXT("%d"), check);
			TextOut(hdc, 0, 0, str, lstrlen(str));
			EndPaint(hWnd, &ps);

			GetClientRect(hWnd, &rect);
			SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
			if (0 <= check && check <= 9)//그것이 숫자인지? 아니면 쓸때없는 문자인지 판별.
			{
				sum[x - 2][y - 2] = check;
				wsprintf(str1, TEXT("%d"), sum[x - 2][y - 2]);
				TextOut(hdc, x*rect.right / 13, y*rect.right / 13, str1, lstrlen(str1)); // 추가된 숫자로 값을 재갱신한다. 

				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				wsprintf(buf, TEXT("그 위치에는 숫자만 들어갑니다.")); // 숫자에 대한 에러코드를 산출한다. 
				MessageBox(hWnd, buf, TEXT("에러"), MB_OK | MB_ICONEXCLAMATION);
			}
		}
		
		else
		{
			wsprintf(buf, TEXT("그 위치에는 값을 넣을 수 없습니다.")); // 지정된 위치가 아닌 곳에 값을 할당하면 에러. 
			MessageBox(hWnd, buf, TEXT("TicTacToe"), MB_OK | MB_ICONEXCLAMATION);
			
		}
		return 0;

	case WM_GETMINMAXINFO://윈도우의 크기를 제한.
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 600;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 600;// 윈도우 폼은 특정 크기를 넘을 수 없음을 뜻함.
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;
		return FALSE;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		
		for (int v = 0; v < 13; v++)//헤드라인을 작성한다.
		{

			hPen = CreatePen(PS_SOLID, 0, RGB(250, 248, 210));
			oPen = (HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(250, 248, 210));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, v*rect.right / 13, 0, (v + 1) * rect.right / 13, 2 * rect.bottom / 13);
			//다시 그리기.
			DeleteObject(SelectObject(hdc, oldBrush));
			SelectObject(hdc, oPen);
			DeleteObject(hPen);
		}

		SetMapMode(hdc, MM_TEXT);
		nPoint = 40;
		//GetDeviceCaps는 1인치당의 픽셀 수를 뽑아냄.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서"));
		oldfont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(075, 0, 130));//글자색을 결정.
		SetBkColor(hdc, RGB(224, 255, 255));
		//??? 한글, MS Word의 10point 문자를 출력하면 제각각 다 다를 수 있다.   
		// 화면 보기 비율이 100% 인지 확인하자. 
		TextOut(hdc, 4 * rect.right / 39, 1 * rect.right / 39, Mes, lstrlen(Mes));
		DeleteObject(font);//헤드라인의 글귀를 결정한다.

		for (int i = 2; i < 11; i++)//줄을 긋는 코드입니다.
		{


			for (int j = 2; j < 11; j++)
			{
				hBrush = CreateSolidBrush(RGB(173, 216, 230));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//다시 그리기.
				DeleteObject(SelectObject(hdc, oldBrush));
			}
		}//그림 그리기.
		nPoint = 20;
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
		for (int i = 2; i < 11; i++)
		{


			for (int j = 2; j < 11; j++)
			{
				nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
				font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("궁서"));
				oldfont = (HFONT)SelectObject(hdc, font);
				SetTextColor(hdc, RGB(70, 130, 180));//글자색을 결정.
				SetBkColor(hdc, RGB(173, 216, 230));
				wsprintf(str1, TEXT("%d"), sum[i - 2][j - 2]);
				TextOut(hdc, (i * 3 + 1)*rect.right / 39, (j * 3 + 1)*rect.right / 41, str1, lstrlen(str1));

			}
		}//사각형을 완성한다. 그 안에 숫자를 뜻함. 사각형을 맞출려고 엄청나게 노력함. 

		for (int i = 0; i < 9; i++)
		{


			for (int j = 11; j < 13; j++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(219, 112, 147));
				oPen = (HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(219, 112, 147));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//다시 그리기.
				DeleteObject(SelectObject(hdc, oldBrush));
				SelectObject(hdc, oPen);
				DeleteObject(hPen);
			}
		}//글자 형식을 갱신한다. 

		nPoint = 10;
		//GetDeviceCaps는 1인치당의 픽셀 수를 뽑아냄.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10포인트에 해당되는 픽셀을 계산함.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("바탕"));
		oldfont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(0, 0, 0));//글자색을 결정.
		SetBkColor(hdc, RGB(219, 112, 147));
		rt = { 0 * rect.right / 39, 32 * rect.right / 39, 27 * rect.right / 39, 39 * rect.right / 39 };
		DrawText(hdc, Mes1, -1, &rt, DT_CENTER | DT_WORDBREAK );
		DeleteObject(font); 

		for (int i = 9; i < 13; i++)
		{


			for (int j = 11; j < 12; j++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(238, 130, 238));
				oPen = (HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(238, 130, 238));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//다시 그리기.
				DeleteObject(SelectObject(hdc, oldBrush));
				SelectObject(hdc, oPen);
				DeleteObject(hPen);
			}
		}
		wsprintf(str, TEXT("전체 게임의 점수: %d"), count);
		TextOut(hdc, 29 * rect.right / 39, 33 * rect.right / 39, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



//렌덤 값을 무작위로 할당하는 기능을 만들지 못했다. 
//대학교에 들어와, 두번째로 만들었던 프로젝트였는데, 허탕에 가까운 면이 있었다.
//그냥 정답을 할당한 다음에 무작위로 숫자를 0으로 바꾸어 리뉴얼하는 방법도 생각해봤는데, 이 당시의 나로썬 너무 어려운 로직이었던 것 같다.
//그림을 그리고 디자인을 만드는 것 만으로 리타이어...
