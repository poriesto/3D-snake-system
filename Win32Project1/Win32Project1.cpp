// Win32Project1.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "StatModule.h"
#define FILE_NAME "../stat.txt"
#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����
#define ID_MYBUTTON 1    /* ������������� ��� �������� ������ �������� ���� */
#define ID_BT 2
#define ID_BT1 3
int RED, GREEN, BLUE;
// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Options(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Records(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������
   hWnd = CreateWindow(szWindowClass, "�����������", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 500, 500, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rec1;
	STARTUPINFO si;
	static PROCESS_INFORMATION pi;
	GetClientRect(hWnd, &rec1);
	switch (message)
	{
	case WM_CREATE:
		CreateWindow("button","Start Game",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2,100,20,hWnd,(HMENU)ID_MYBUTTON,NULL,NULL);
		CreateWindow("button","Options",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2+20,100,20,hWnd,(HMENU)ID_BT,NULL,NULL);
		CreateWindow("button","Exit",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,
			rec1.right/2-40,rec1.bottom/2+40,100,20,hWnd,(HMENU)ID_BT1,NULL,NULL);
		return 0;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		int Exit;
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_MYBUTTON)) 
			system("D:\\snake.exe");
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT)) 
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Options);
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==ID_BT1)) 
			Exit = MessageBox(hWnd, "Do u want exit from this beateful game?", "Exit from game", MB_YESNO|MB_ICONQUESTION);
			if(Exit == IDYES){
				DestroyWindow(hWnd);
			}
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_32771:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Records);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rec1);
		// TODO: �������� ����� ��� ���������...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		//�������� ��� ������ ����� ���
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND DlgAbout, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(DlgAbout, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Options(HWND DlgOptions, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(DlgOptions, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==IDC_BUTTON1))
		{ 
			int confirm;
			confirm = MessageBox(DlgOptions,"Are u sure?","Save settings",MB_YESNO|MB_ICONQUESTION);
			if(confirm == IDYES)
			{
				/*RED = (int)GetDlgItem(hDlg,IDC_EDIT1);
				GREEN = (int)GetDlgItem(hDlg, IDC_EDIT2);
				BLUE = (int)GetDlgItem(hDlg, IDC_EDIT3);
				EndDialog(hDlg, 0);*/
			}
		}
		if ((HIWORD(wParam)==0) && (LOWORD(wParam)==IDC_BUTTON2)) 
		{
			EndDialog(DlgOptions, 0);
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Records(HWND DlgStat, UINT message, WPARAM wParam, LPARAM lParam)
{
	vector<Stat> V;
	vector<Stat>::iterator iter;
	HWND hwndList;
	int i = 0;
	switch(message)
	{
	case WM_INITDIALOG:
		V = ReadFromFile(FILE_NAME);
		hwndList = GetDlgItem(DlgStat, IDC_LIST2);
		iter = V.begin();
		while(iter!=V.end())
		{
			int y = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
				(LPARAM)PrintToTextField(iter).c_str());
			SendMessage(hwndList, LB_SETITEMDATA, y, (LPARAM)i);
			iter++;
			i++;
		}
		SetFocus(hwndList);
		return (INT_PTR)TRUE;
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		if((HIWORD(wParam)==0) && (LOWORD(wParam) == IDOK))
		{
			EndDialog(DlgStat,	LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if((HIWORD(wParam)==0) && (LOWORD(wParam)==IDCANCEL))
		{
			//����� ����������
			int Reset = MessageBox(DlgStat, "Do u want reset stats?", "Reset Stat", MB_YESNO|MB_ICONQUESTION);
			if(Reset == IDYES){
				/*
				�������� ����� ����������
				���������� ������� ���������� (���������)
				*/
			}
		}
	}
	return (INT_PTR)FALSE;
}
