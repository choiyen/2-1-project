#include <windows.h>
#include<string>
#define _CRT_SECURE_NO_WARNINGS
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("������ ����");
WNDPROC OldEditProc, OldEditProc1;
HBRUSH bkBrush = CreateSolidBrush(RGB(135, 206, 235));//����� ��ü ������ �����Ѵ�.

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
//����� ũ��, ���� ũ��, ���� ����.
int sum[9][9];
int sawcheck(int b) //������ üũ �κ�.
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
int rawcheck(int b)//������
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
//�ϳ��� ���� �˻��ϰ�, 9�� �� �ϳ��� 0���� �ٲ��� ������ 1�� �����Ѵ�.
int reackcheck(int c, int k)//c= �� ��° ��, ������ Ȯ��
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
} //�ϳ��� ���� �˻��ϰ�, 9�� �� �ϳ��� 0���� �ٲ��� ������ 1�� �����Ѵ�.

int count;// ���� ������ �� ��.
TCHAR str1[256];
HWND search,submit;
enum { ID_R1 = 101, ID_R2};
CHAR h;
HWND hwndcheck;
int a0[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int a1[3][3] = { 0, 0, 1, 1, 0, 0,0,1,0};// ������ ����ϴ� ���
int a2[3][3] = { 0, 1, 0, 0, 0, 1, 1, 0, 0 }; // ������ ����ϴ� ��
int moive[9][9];//������ �����ϴ� �˰���.
int (*getmix(int (*a)[3], int (*c)[3]))[3]//2���� �迭 ���ڷ� �ѱ��.
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
	return dhsn;//2���� �迭�� ������ �����Ѵ�.
}
int(*getmix(int(*a)[3], int(*c)[3], int(*b)[3]))[3]//2���� �迭 ���ڷ� �ѱ��.
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
}//�Լ��� ���� ����

void put(int(*numPtr)[3], int c, int k)//������� ���, �� ��° ��, ������ Ȯ��
{
    for (int i = c; i < c + 3; i++)//����� ���� ��.
	{
		for (int j = k; j < k + 3; j++)//����� ������.
		{
			sum[i][j] = numPtr[i % 3][j % 3];
		}
	}
}
void change9()//�� 9x9 �迭�� �� ���̽� 3*3 �迭��  8���� �����(������ �˰��� ����)
{
	put(a0, 0, 0);//1��°
	put(getmix(a1, a0), 0, 3);//�ι�°
	put(getmix(a2, a0), 0, 6);//����°
	put(getmix(a0, a1), 3, 0);//�׹�°
	put(getmix(a1, a0, a1), 3, 3);//�ټ���°
	put(getmix(a2, a0, a1), 3, 6);//������°
	put(getmix(a0, a2), 6, 0);//7��°
	put(getmix(a1, a0,a2), 6, 3);//8����
	put(getmix(a2, a0, a2), 6, 6);//9��°.

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

void change()//3x3�� ���̽� ������ �����.
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
} //3x3�� ���̽� ���� �����.

void init(HWND hWnd) {//���� �ʱ�ȭ.
	int i, j; //������ ���� �ɶ��� ����ؼ�
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

		}//�ϳ��� ���� �˻��ϰ�, 9�� �� �ϳ��� 0���� �ٲ��� ������ 1�� �����Ѵ�.

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				icountz += reackcheck(3 * i, 3 * j);
			}
		}
		if (icountx == 0 && icounty == 0 && icountz == 0)
		{
			MessageBox(hWnd, TEXT("��� ���� �����Դϴ�. �����ϸ� ������ �޽��ϴ�."),
				TEXT("Ȯ��"), MB_OK);
		}
		else
		{
			wsprintf(buf, TEXT("���� Ʋ�� �� �����մϴ�.\n\n\n ���κ��� %d �� \n ���κ��� %d �� \n �簢���� %d ���� Ʋ�Ƚ��ϴ�. \n �׷��Ƿ� ������ ���� ���, -100���� �Ұ� �˴ϴ�."), icountx,icounty,icountz);
			MessageBox(hWnd, buf, TEXT("Ȯ��"), MB_OK);	
		}
		break;
	case WM_LBUTTONDOWN:
		PostMessage(hWnd, EM_SETSEL, 0, -1);
		break;
	}
	return CallWindowProc(OldEditProc1, hWnd, iMessage, wParam, lParam);
}//�󸶳� Ʋ�ȴ����� Ȯ��.

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

		}//�ϳ��� ���� �˻��ϰ�, 9�� �� �ϳ��� 0���� �ٲ��� ������ 1�� �����Ѵ�.

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
			MessageBox(hWnd, TEXT("������ ���߾����ϴ�. ���� ������ �Ѿ�ϴ�."),
				TEXT("����"), MB_OK);
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
			if (MessageBox(hWnd, TEXT("������ Ʋ�Ƚ��ϴ�. �ٽ� Ǯ��÷��� ��(Y), �����Ͻ÷��� �ƴϿ�(N)�� �ι� �����ּ���. ������ �����Ͻ÷��� ��Ҹ� �� �� �����ּ���"), TEXT("����"), MB_YESNOCANCEL) == IDYES)
			{

			}
			else if (MessageBox(hWnd, TEXT("������ Ʋ�Ƚ��ϴ�. �ٽ� Ǯ��÷��� ��(Y), �����Ͻ÷��� �ƴϿ�(N)�� �ι� �����ּ���. ������ �����Ͻ÷��� ��Ҹ� �� �� �����ּ���"), TEXT("����"), MB_YESNOCANCEL) == IDNO)
			{
				if (MessageBox(hWnd, TEXT("���� �ʱ�ȭ�Ͻǲ�����???."), TEXT("�ʱ�ȭ"), MB_YESNO) == IDYES)
				{
					init(hwndcheck);
				}
			}
			else if (MessageBox(hWnd, TEXT("������ Ʋ�Ƚ��ϴ�. �ٽ� Ǯ��÷��� ��(Y), �����Ͻ÷��� �ƴϿ�(N)�� �ι� �����ּ���. ������ �����Ͻ÷��� ��Ҹ� �� �� �����ּ���"), TEXT("����"), MB_YESNOCANCEL) == IDCANCEL)
			{
				if (MessageBox(hWnd, TEXT("���� �����Ͻ� ������???"), TEXT("����"), MB_YESNO) == IDYES)
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
}//�װ� ���� ���, �����̸� ������ �߰��ϰ�, Ʋ���� ���� ������ �Բ� �ٽ� Ǯ� ���� �ƴϸ� �ٽ� �� ����, �׵� �ƴϸ� ������ ������ ����.

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT  rect;
	RECT rt;
	HBRUSH hBrush;
	TCHAR *Mes = TEXT("���¾� ������ ����");
	TCHAR *Mes1 = TEXT(" ���� ��Ģ: �� ������ 9*9 ������ �����̸�, ����, ����, 3x3�� 9 ĭ�� 1-9������ ����  �Ǿ�� �����մϴ�. �׸��� ������ ���߸� 100����, Ʋ���� -100���� �����մϴ�., ������ �ٸ� ���ӵ�� �����˴ϴ�. \n �� �Ѱ����� ���� ��ư�� ������ ���� Ʋ�� ���� �հ踦 �� �� �ֽ��ϴ�. ���� ��ư�� ���� ��� ������ ���ھ ����մϴ�. \n ��, �� ���ӿ� ���̳ʽ� ���� �հ谡 �����ϴ�.");
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
		search = CreateWindow(TEXT("button"), TEXT("Ȯ��"), WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON | WS_GROUP,
			28 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
		submit = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE |
			BS_DEFPUSHBUTTON | WS_GROUP,
			34 * rect.right / 39, 35 * rect.right / 39, 50, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);//�� ��ư�� ������ �� ��ư�� �ڽ� �����쿡�� ���� ����.
		OldEditProc = (WNDPROC)SetWindowLongPtr(submit, GWLP_WNDPROC, (LONG_PTR)buttonSubProc1);//��尡 ��������� ���ÿ� ���� ��� ����.
		OldEditProc1 = (WNDPROC)SetWindowLongPtr(search, GWLP_WNDPROC, (LONG_PTR)buttonSubProc2);//��尡 ��������� ���ÿ� ���� ��� ����.
		//�˰��� ���� �־�� �� ��.
		hwndcheck = hWnd;
		change9();
		return 0;

	case WM_LBUTTONDOWN:
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		x = (LOWORD(lParam)) / (rect.right / 13);
		y = (HIWORD(lParam)) / (rect.bottom / 13);//�ϴ� Ŭ�� ��ư�� ��ġ�� ã�´�.
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
		
			if (a3[x-2][y-2] == 0)
			{
				wsprintf(str, TEXT("%d"), check);
				TextOut(hdc, 0, 0, str, lstrlen(str));
				EndPaint(hWnd, &ps);

				GetClientRect(hWnd, &rect);
				SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
				if (0 <= check && check <= 9)//�װ��� ��������? �ƴϸ� �������� �������� �Ǻ�.
				{
					sum[x - 2][y - 2] = check;
					wsprintf(str1, TEXT("%d"), sum[x - 2][y - 2]);
					TextOut(hdc, x*rect.right / 13, y*rect.right / 13, str1, lstrlen(str1));
					InvalidateRect(hWnd, NULL, TRUE);
				}
				else
				{
					wsprintf(buf, TEXT("�� ��ġ���� ���ڸ� ���ϴ�."));
					MessageBox(hWnd, buf, TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
				}
			}
			else
			{
				wsprintf(buf, TEXT("�� ��ġ�� �Էµ� ���� ������ �� �����ϴ�."));
				MessageBox(hWnd, buf, TEXT("��� �޽���"), MB_OK | MB_ICONEXCLAMATION);
			}
		}
		else
		{
			wsprintf(buf, TEXT("�� ��ġ���� ���� ���� �� �����ϴ�."));
			MessageBox(hWnd, buf, TEXT("��� �޽���"), MB_OK | MB_ICONEXCLAMATION);
		}
		return 0;

	case WM_GETMINMAXINFO://�������� ũ�⸦ ����.
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 600;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;
		return FALSE;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		
		for (int v = 0; v < 13; v++)//�������� �ۼ��Ѵ�.
		{
			hPen = CreatePen(PS_SOLID, 0, RGB(250, 248, 210));
			(HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(250, 248, 210));
			(HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, v*rect.right / 13, 0, (v + 1) * rect.right / 13, 2 * rect.bottom / 13);
			//�ٽ� �׸���.
			DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
			DeleteObject((HPEN)SelectObject(hdc, hPen));
		}
		SetMapMode(hdc, MM_TEXT);
		nPoint = 40;
		//GetDeviceCaps�� 1��ġ���� �ȼ� ���� �̾Ƴ�.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
		(HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(075, 0, 130));//���ڻ��� ����.
		SetBkColor(hdc, RGB(224, 255, 255));
		//??? �ѱ�, MS Word�� 10point ���ڸ� ����ϸ� ������ �� �ٸ� �� �ִ�.   
		// ȭ�� ���� ������ 100% ���� Ȯ������. 
		TextOut(hdc, 4 * rect.right / 39, 1 * rect.right / 39, Mes, lstrlen(Mes));
		DeleteObject((HFONT)SelectObject(hdc, font));//�������� �۱͸� �����Ѵ�.

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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
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
					//�ٽ� �׸���.
					DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
					DeleteObject((HPEN)SelectObject(hdc, hPen));
				}
			}
		}//�׸� �׸���.
		nPoint = 20;
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
		for (int i = 2; i < 11; i++)
		{
			for (int j = 2; j < 11; j++)
			{
				if (a3[i-2][j-2] == 0)
				{
					nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
					font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
					(HFONT)SelectObject(hdc, font);
					SetTextColor(hdc, RGB(0, 0, 10));//���ڻ��� ����.
					SetBkColor(hdc, RGB(173, 216, 230));
					wsprintf(str1, TEXT("%d"), sum[i - 2][j - 2]);
					TextOut(hdc, (i * 3 + 1)*rect.right / 39, (j * 3 + 1)*rect.right / 41, str1, lstrlen(str1));
					DeleteObject((HFONT)SelectObject(hdc, font));
				}
				else
				{
					nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
					font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
					(HFONT)SelectObject(hdc, font);
					SetTextColor(hdc, RGB(255, 0, 0));//���ڻ��� ����.
					SetBkColor(hdc, RGB(173, 216, 230));
					wsprintf(str1, TEXT("%d"), sum[i - 2][j - 2]);
					TextOut(hdc, (i * 3 + 1)*rect.right / 39, (j * 3 + 1)*rect.right / 41, str1, lstrlen(str1));
					DeleteObject((HFONT)SelectObject(hdc, font));
				}
			}
		}//�簢���� �ϼ��Ѵ�.

		for (int i = 0; i < 9; i++)
		{
			for (int j = 11; j < 13; j++)
			{
				hPen = CreatePen(PS_SOLID, 0, RGB(219, 112, 147));
				(HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(219, 112, 147));
				(HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, i*rect.right / 13, j*rect.bottom / 13, (i + 1) * rect.right / 13, (j + 1) * rect.bottom / 13);
				//�ٽ� �׸���.
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
				DeleteObject((HPEN)SelectObject(hdc, hPen));
			}
		}
		nPoint = 10;
		//GetDeviceCaps�� 1��ġ���� �ȼ� ���� �̾Ƴ�.
		nHeight = -((GetDeviceCaps(hdc, LOGPIXELSY)*nPoint) / 72);//10����Ʈ�� �ش�Ǵ� �ȼ��� �����.
		font = CreateFont(nHeight, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����"));
		(HFONT)SelectObject(hdc, font);
		SetTextColor(hdc, RGB(0, 0, 0));//���ڻ��� ����.
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
				//�ٽ� �׸���.
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
				DeleteObject((HPEN)SelectObject(hdc, hPen));
			}
		}
		wsprintf(str, TEXT("��ü ������ ����: %d"), count);
		TextOut(hdc, 29 * rect.right / 39, 33 * rect.right / 39, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("�����Ͻðڽ��ϱ�?(������ ����ϰ� �����մϴ�.)"), TEXT("����"), MB_YESNO) == IDNO)
		{
			// ���� ���(�������) //
			return 0;
		}
		else {
			break;
		}
	case WM_DESTROY:
		// ���� ���(�������) //
		WinExec(".\\manage.exe", SW_SHOW); // �������α׷� ����
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}