#include <windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("������ ����");
WNDPROC OldEditProc;
HBRUSH bkBrush = CreateSolidBrush(RGB(135, 206, 235));//����� ��ü ������ �����Ѵ�.

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
}//����� ũ��, ���� ũ��, ���� ����.
int sum[9][9];
int rawcheck(int acount, int b)//���� �ϼ� �ȵ� ������ üũ �κ�.
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
int sawcheck(int acount, int b)//������
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
int reackcheck(int c,  int b)//�簢��
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
void init(HWND hWnd) {//���� �ʱ�ȭ.
	int i, j; //������ ���� �ɶ��� ����ؼ�
	for (i = 0; i<9; i++)
		for (j = 0; j<9; j++){
			sum[i][j] = 0;
		}
	InvalidateRect(hWnd, NULL, TRUE);
}
int count = 0;// ���� ������ �� ��.
int countx; //�´� ���κ���.
int county; //�´� ���κ���.
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
	TCHAR *Mes = TEXT("���¾� ������ ����");
	TCHAR *Mes1 = TEXT(" ���� ��Ģ: �� ������ 9*9 ������ �����̸�, ����, ����, 3x3�� 9 ĭ�� 0-9������ ����  �Ǿ�� �����մϴ�. �׸��� ���� ���߸� +100���� ���ϰ� Ʋ���� ������ -100�� �����ϸ�, ������ �ٸ� ���ӵ�� �����˴ϴ�. �� �Ѱ����� ���� ��ư�� ������ ���� ���� ���� �հ踦 �� �� �ֽ��ϴ�. �׸��� ���� ��ư�� ���� ��� ������ ���ھ ����մϴ�.");
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
		search = CreateWindow(TEXT("button"), TEXT("Ȯ��"), WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON | WS_GROUP,
			28 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
		submit = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON | WS_GROUP,
			34 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);//�� ��ư�� ������ �� ��ư�� �ڽ� �����쿡�� ���� ����. ��ư�� ������.
		return 0;
	case WM_LBUTTONDOWN:
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		x = (LOWORD(lParam)) / (rect.right / 13);
		y = (HIWORD(lParam)) / (rect.bottom / 13);//�ϴ� Ŭ�� ��ư�� ��ġ�� ã�´�. / ��ư�� ��ġ�� ��´�. 
		return 0;

	case WM_CHAR:
	      h = (CHAR)wParam;//0~9���� �� �ϳ��� ���ڸ� �޴´�.
		  check = h - '0';//�ƽ�Ű �ڵ� ���,
		 if ((int)h == 8)
		 {
			 sum[x - 2][y - 2] = 0;
			 InvalidateRect(hWnd, NULL, TRUE);//�����츦 �簻�� �Ѵ�.(VK_back �޽����� ���� ������ �浹�� �Ͼ.
		 }
	    else if ((2 <= x && x < 11) && (2 <= y && y < 11))//��ǥ���� �簢�� �ȿ� ���� ����.
		{
			hdc = BeginPaint(hWnd, &ps);
		
			wsprintf(str, TEXT("%d"), check);
			TextOut(hdc, 0, 0, str, lstrlen(str));
			EndPaint(hWnd, &ps);

			GetClientRect(hWnd, &rect);
			SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
			if (0 <= check && check <= 9)//�װ��� ��������? �ƴϸ� �������� �������� �Ǻ�.
			{
				sum[x - 2][y - 2] = check;
				wsprintf(str1, TEXT("%d"), sum[x - 2][y - 2]);
				TextOut(hdc, x*rect.right / 13, y*rect.right / 13, str1, lstrlen(str1)); // �߰��� ���ڷ� ���� �簻���Ѵ�. 

				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				wsprintf(buf, TEXT("�� ��ġ���� ���ڸ� ���ϴ�.")); // ���ڿ� ���� �����ڵ带 �����Ѵ�. 
				MessageBox(hWnd, buf, TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
			}
		}
		
		else
		{
			wsprintf(buf, TEXT("�� ��ġ���� ���� ���� �� �����ϴ�.")); // ������ ��ġ�� �ƴ� ���� ���� �Ҵ��ϸ� ����. 
			MessageBox(hWnd, buf, TEXT("TicTacToe"), MB_OK | MB_ICONEXCLAMATION);
			
		}
		return 0;

	case WM_GETMINMAXINFO://�������� ũ�⸦ ����.
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 600;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 600;// ������ ���� Ư�� ũ�⸦ ���� �� ������ ����.
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;
		return FALSE;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		
		for (int v = 0; v < 13; v++)//�������� �ۼ��Ѵ�.
		{

			hPen = CreatePen(PS_SOLID, 0, RGB(250, 248, 210));
			oPen = (HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(250, 248, 210));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, v*rect.right / 13, 0, (v + 1) * rect.right / 13, 2 * rect.bottom / 13);
			//�ٽ� �׸���.
			DeleteObject(SelectObject(hdc, oldBrush));
			SelectObject(hdc, oPen);
			DeleteObject(hPen);
		}

		SetMapMode(hdc, MM_TEXT);
		nPoint = 40;
		//GetDeviceCaps�� 1��ġ���� �ȼ� ���� �̾Ƴ�.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
		oldfont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(075, 0, 130));//���ڻ��� ����.
		SetBkColor(hdc, RGB(224, 255, 255));
		//??? �ѱ�, MS Word�� 10point ���ڸ� ����ϸ� ������ �� �ٸ� �� �ִ�.   
		// ȭ�� ���� ������ 100% ���� Ȯ������. 
		TextOut(hdc, 4 * rect.right / 39, 1 * rect.right / 39, Mes, lstrlen(Mes));
		DeleteObject(font);//�������� �۱͸� �����Ѵ�.

		for (int i = 2; i < 11; i++)//���� �ߴ� �ڵ��Դϴ�.
		{


			for (int j = 2; j < 11; j++)
			{
				hBrush = CreateSolidBrush(RGB(173, 216, 230));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//�ٽ� �׸���.
				DeleteObject(SelectObject(hdc, oldBrush));
			}
		}//�׸� �׸���.
		nPoint = 20;
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
		for (int i = 2; i < 11; i++)
		{


			for (int j = 2; j < 11; j++)
			{
				nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
				font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
				oldfont = (HFONT)SelectObject(hdc, font);
				SetTextColor(hdc, RGB(70, 130, 180));//���ڻ��� ����.
				SetBkColor(hdc, RGB(173, 216, 230));
				wsprintf(str1, TEXT("%d"), sum[i - 2][j - 2]);
				TextOut(hdc, (i * 3 + 1)*rect.right / 39, (j * 3 + 1)*rect.right / 41, str1, lstrlen(str1));

			}
		}//�簢���� �ϼ��Ѵ�. �� �ȿ� ���ڸ� ����. �簢���� ������� ��û���� �����. 

		for (int i = 0; i < 9; i++)
		{


			for (int j = 11; j < 13; j++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(219, 112, 147));
				oPen = (HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(219, 112, 147));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//�ٽ� �׸���.
				DeleteObject(SelectObject(hdc, oldBrush));
				SelectObject(hdc, oPen);
				DeleteObject(hPen);
			}
		}//���� ������ �����Ѵ�. 

		nPoint = 10;
		//GetDeviceCaps�� 1��ġ���� �ȼ� ���� �̾Ƴ�.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
		oldfont = (HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(0, 0, 0));//���ڻ��� ����.
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
				//�ٽ� �׸���.
				DeleteObject(SelectObject(hdc, oldBrush));
				SelectObject(hdc, oPen);
				DeleteObject(hPen);
			}
		}
		wsprintf(str, TEXT("��ü ������ ����: %d"), count);
		TextOut(hdc, 29 * rect.right / 39, 33 * rect.right / 39, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



//���� ���� �������� �Ҵ��ϴ� ����� ������ ���ߴ�. 
//���б��� ����, �ι�°�� ������� ������Ʈ���µ�, ������ ����� ���� �־���.
//�׳� ������ �Ҵ��� ������ �������� ���ڸ� 0���� �ٲپ� �������ϴ� ����� �����غôµ�, �� ����� ���ν� �ʹ� ����� �����̾��� �� ����.
//�׸��� �׸��� �������� ����� �� ������ ��Ÿ�̾�...
