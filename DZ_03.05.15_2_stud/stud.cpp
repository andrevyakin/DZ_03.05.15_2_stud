#include<Windows.h>
#include<tchar.h>
#include<ctime>

#define ID_LIST1 1001
#define ID_LIST2 1002
#define ID_LIST3 1003
#define ID_BUTTON 1010

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;
RECT desktop, cr;
int count;

HWND list1, list2, list3, button;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(10, 128, 256));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;
	GetWindowRect(GetDesktopWindow(), &desktop);
	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		desktop.right / 4,
		desktop.bottom / 6,
		desktop.right / 2,
		desktop.bottom / 2,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:

	case BN_CLICKED:
		if (LOWORD(wParam) == ID_BUTTON)
		{
			wchar_t temp[20];
			for (int i = 0; i < count; i++)
			{
				SendMessage(list2, LB_GETTEXT, i, (LPARAM)temp);		//������� �� ������� ������ ������
				if (!wcscmp(temp, L"�������"))							//����� ������� ��� ���
				{
					SendMessage(list1, LB_GETTEXT, i, (LPARAM)temp);	//���� �������, ������� ����������� �� ������ ������ �� 1-�� ������
					SendMessage(list3, LB_ADDSTRING, 0, (LPARAM)temp);	//� ��������� � ������ ������
				}
			}
		}
		break;

	case WM_CREATE:

		GetClientRect(hWnd, &cr);

		list1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL,
			cr.right / 8,
			cr.bottom / 8,
			cr.right / 6,
			cr.bottom / 1.5,
			hWnd,
			(HMENU)ID_LIST1,
			hinst,
			NULL);
		list2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL,
			cr.right / 2.5,
			cr.bottom / 8,
			cr.right / 6,
			cr.bottom / 1.5,
			hWnd,
			(HMENU)ID_LIST2,
			hinst,
			NULL);
		list3 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | ES_READONLY | WS_VSCROLL,
			cr.right / 1.45,
			cr.bottom / 8,
			cr.right / 6,
			cr.bottom / 1.5,
			hWnd,
			(HMENU) ID_LIST3,
			hinst,
			NULL);

		button = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"������",
			WS_CHILD | WS_VISIBLE,
			cr.right / 2 - 90,
			cr.bottom / 1.2,
			150,
			30,
			hWnd,
			(HMENU)ID_BUTTON,
			hinst,
			NULL);

		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"�������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"��������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"���������� ����");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"���������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"�������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"���������� ����");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"���������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"�����������");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"�����");
		
		count = SendMessage(list1, LB_GETCOUNT, 0, 0);
		
		srand((unsigned)time(NULL));

		for (int i = 0; i < count; i++)
		{
			int temp = rand() % 2;
			if (temp)
				SendMessage(list2, LB_ADDSTRING, 0, (LPARAM)L"�����");
			else
				SendMessage(list2, LB_ADDSTRING, 0, (LPARAM)L"�������");
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}