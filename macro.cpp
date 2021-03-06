#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <winuser.h>
#define ESC 27
#define clrscr() system("cls")

using namespace std;

class Number {
public:
	Number();
	Number(int finish, int total);
	void SetFinish(int finish);
	void SetTotal(int total);	
	int GetFinish();
	int GetTotal();
	~Number();
protected :
	int finish;
	int total;
private :
	
};
Number::Number() {
	finish = 0;
	total = 0;
}
Number::Number(int finish, int total) {
	this->finish = finish;
	this->total = total;
}
Number::~Number() {
	
}
void Number::SetFinish(int finish) {
	this->finish = finish;
}
void Number::SetTotal(int total) {
	this->total = total;
}
int Number::GetFinish() {
	return this->finish;
}
int Number::GetTotal() {
	return this->total;
}

class Address : public Number {
	public :
		Address();
		Address(int finish, int total);
		void SetJudge(char * judge);
		char * GetJudge();
		~Address();
	protected :
	private :
		char * judge;
};
Address::Address() {
	judge = new char;
}
Address::Address(int finish, int total) {
	this->finish = finish;
	this->total = total;
}
void Address::SetJudge(char *judge) {
	this->judge = judge;
}
char *Address::GetJudge() {
	return this->judge;
}
Address::~Address() {
	delete judge;
	judge = NULL;
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();
	while(GetTickCount() - dwStart < dwMillisecond)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int CopyTextToClipboard(const char* ap_string)
{
	int string_length = strlen(ap_string) + 1;
	HANDLE h_data = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, string_length);
	char* p_data = (char*)::GlobalLock(h_data);
	if (NULL != p_data)
	{
		memcpy(p_data, ap_string, string_length);
		::GlobalUnlock(h_data);
		if (::OpenClipboard(NULL))
		{
			::EmptyClipboard();
			::SetClipboardData(CF_TEXT, h_data);
			::CloseClipboard();
		}
	}
	return 0;
}
char *CopyClipboardToText()
{
	unsigned int priority_list = CF_TEXT;
	char *p_string = NULL;
	if(::GetPriorityClipboardFormat(&priority_list,1) == CF_TEXT)
	{
		if(OpenClipboard(NULL))
		{
			HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);
			if(h_clipboard_data != NULL)
			{
				char *p_clipboard_data = (char *)::GlobalLock(h_clipboard_data);
				int string_len = strlen(p_clipboard_data) + 1;
				p_string = new char [string_len];
				memcpy(p_string, p_clipboard_data, string_len);
				::GlobalUnlock(h_clipboard_data);
			}
			::CloseClipboard();
		}	
	}
	return p_string;
}
void CopyText() // ctrl + c
{
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x43, 0, 0, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
	Sleep(300);
}
void PasteText() // ctrl + v
{
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x56, 0, 0, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	Sleep(300);
}
void FindText() // ctrl + f
{
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(0x46, 0, 0, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(0x46, 0, KEYEVENTF_KEYUP, 0);
	Sleep(300);
}
void MouseLeftClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(300);
}
void MouseLeftDoubleClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

const std::string CurrentDateTime() // ?????????? string type???? return???? ????
{
    time_t now = time(0); //???? ?????? time_t ???????? ????
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct); // YYYYMMDD ?????? ??????

    return buf;
}
int Tmp_Pause()
{
	gotoxy(23, 9);
	cout << "   ";
	gotoxy(23, 9);
	cout << "On";
	while (TRUE)
	{
		if (_kbhit() && _getch() == VK_ESCAPE)
			break;
		Sleep(500);
	}
	gotoxy(23, 9);
	cout << "Off";
	return 0;
}

void printMain()
{
	gotoxy(23, 3);
	cout << "|-----------------------------|";
	gotoxy(23, 4);
	cout << "|                             |";
	gotoxy(25, 4);
	cout << "?????? ?????? (ESC to exit)";
	gotoxy(23, 5);
	cout << "|-----------------------------|";
	cout << "  [ver 2.4]";
	gotoxy(70, 21);
	cout << "since 2019.10.16";
	gotoxy(60, 23);
	cout << "?????? ?????? : 2019.12.31";

	gotoxy(26, 8);
	cout << "1. ????????";
	gotoxy(26, 12);
	cout << "2. ????????";
	gotoxy(26, 16);
	cout << "3. ????";
	gotoxy(26, 20);
	cout << "0. ????";
}
void PrintImposition()
{
	gotoxy(35, 4);
	cout << "????????" << endl;
	gotoxy(12, 7);
	cout << "?????? : ";
	gotoxy(62, 7);
	cout << "(0  %)";
	gotoxy(12, 9);
	cout << "???????? : Off";
	gotoxy(12, 11);
	cout << "???????? :     ??     ??";
	gotoxy(12, 13);
	cout << "=====================================================";
	gotoxy(12, 14);
	cout << "| ???????? :                                        |";
	gotoxy(12, 15);
	cout << "|                                                   |";
	gotoxy(12, 16);
	cout << "| ???????? :                                        |";
	gotoxy(12, 17);
	cout << "|                                                   |";
	gotoxy(12, 18);
	cout << "| ?????? ???? :                                     |";
	gotoxy(12, 19);
	cout << "=====================================================";
}
void CalPrint(int total, int finish)
{
	double tmp;
	int tot;
	int block, min, sec, min_digit, sec_digit;
	tmp = ((double)finish / total) * 100;
	gotoxy(63, 7); // ??????
	cout << (int)tmp; 
	block = tmp / 5;
	gotoxy(21, 7); // ?????? ??????????
	for (int i = 0; i < block; i++)
		cout << "??";
	for (int j = 0; j < 20 - block; j++)
		cout << "??";
	tot = (total-finish) * 40;
	min = tot / 60;
	sec = tot % 60;
	
	if(min > 99) {
		min_digit = 0;
	} 
	else if(min > 9) {
		min_digit = 1;
	} 
	else {
		min_digit = 2;
	}
	
	if(sec > 9) {
		sec_digit = 0;
	}
	else {
		sec_digit  = 1;
	}
	
	gotoxy(23,11);
	cout << "   ";
	gotoxy(23+min_digit,11);
	cout << min;
	gotoxy(31,11);
	cout << "  ";
	gotoxy(31+sec_digit,11);
	cout << sec;
}
int CalPrint2(int total, int finish)
{
	double tmp;
	int block, min, sec, min_digit, sec_digit;
	tmp = ((double)finish / total) * 100;
	gotoxy(63, 7); // ??????
	cout << (int)tmp; 
	block = tmp / 5;
	gotoxy(21, 7); // ?????? ??????????
	for (int i = 0; i < block; i++)
		cout << "??";
	for (int j = 0; j < 20 - block; j++)
		cout << "??";
	min = (total-finish) / 3;
	sec = ((total-finish) % 3) * 20;
	
		if(min > 99) {
		min_digit = 0;
	} 
	else if(min > 9) {
		min_digit = 1;
	} 
	else {
		min_digit = 2;
	}
	
	if(sec > 9) {
		sec_digit = 0;
	}
	else {
		sec_digit  = 1;
	}
	
	gotoxy(23,11);
	cout << "   ";
	gotoxy(23+min_digit,11);
	cout << min;
	gotoxy(31,11);
	cout << "  ";
	gotoxy(31+sec_digit,11);
	cout << sec;
}
void CalPrint3(int total, int finish)
{
	double tmp;
	int block, min, sec;
	if(total == 0)
		tmp = 100;
	else
		tmp = ((double)finish / total) * 100;
	gotoxy(63, 7); // ??????
	cout << (int)tmp; 
	block = tmp / 5;
	gotoxy(21, 7); // ?????? ??????????
	for (int i = 0; i < block; i++)
		cout << "??";
	for (int j = 0; j < 20 - block; j++)
		cout << "??";
	gotoxy(38,9);
	cout << "back up...";
}
void RmPrint()
{
	gotoxy(26,14); // ???????????? ?????? 
	cout << "             ";
	gotoxy(26,16); // ???? ???????? ??????
	cout << "                       ";
	gotoxy(28,18); // ???? ?????????? ??????
	cout << "                                  ";
	gotoxy(13, 21); // ?????????? ?????? 
	cout << "                                                       ";
} 
void RmPrint2()
{
	gotoxy(26,14); // ???????????? ?????? 
	cout << "                       ";
	gotoxy(29,16); // ???? ?????????? ??????
	cout << "                                  ";
	gotoxy(13, 21); // ?????????? ?????? 
	cout << "                                                        ";
}
enum {NUM = 1, PRO, EXC};

int GetNum(int var)
{
	int total = 0;
	BOOL pre_enter = FALSE; // ?????????? ???????? ???? 
	switch(var)
	{
		case NUM :
			{
				ifstream fin;
				fin.open("number.txt");
				if (!fin)
				{
					clrscr();
					gotoxy(25, 10);
					cout << "cannot open file!(number.txt)" << endl;
					Sleep(2000);
					clrscr();
					return 0;
				}
				char none;
				none = fin.get();
				if(none == EOF)
				{	
					clrscr();
					gotoxy(25, 10);
					cout << "WARNING! Empty file : \"number.txt\""<< endl;
					Sleep(2000);
					clrscr();
					total = 0;
					return total;
				}
				while (TRUE) // ???? ?????? 
				{
					char c;
					c = fin.get();
					if (c == EOF && pre_enter == TRUE)
					{
						break;
					}
					else if(c == EOF && pre_enter == FALSE)
					{
						total++;
						break;
					}
					if (c == '\n')
					{
						pre_enter = TRUE;
						total++;
						continue;
					}
					pre_enter = FALSE;
				}
				fin.close();
				return total;
			}			
		case PRO :
			{
				ifstream fin;
				fin.open("processing.txt");
				if (!fin)
				{
					clrscr();
					gotoxy(25, 10);
					cout << "cannot open file!(processing.txt)" << endl;
					Sleep(2000);
					clrscr();
					return 0;
				}
				char none;
				none = fin.get();
				if(none == EOF)
				{	
					clrscr();
					gotoxy(25, 10);
					cout << "WARNING! Empty file : \"processing.txt\"" << endl;
					Sleep(2000);
					clrscr();
					total = 0;
					return total;
				}
				while (TRUE) // ???? ?????? 
				{
					char c;
					c = fin.get();
					if (c == EOF && pre_enter == TRUE)
					{
						break;
					}
					else if(c == EOF && pre_enter == FALSE)
					{
						total++;
						break;
					}
					if (c == '\n')
					{
						pre_enter = TRUE;
						total++;
						continue;
					}
					pre_enter = FALSE;
				}
				fin.close();
				return total;
			}		
		case EXC :
			{
				ifstream fin;
				fin.open("exception.txt");
				if (!fin)
				{
					clrscr();
					gotoxy(25, 10);
					cout << "cannot open file!(exception.txt)" << endl;
					Sleep(2000);
					clrscr();
					return 0;
				}
				char none;
				none = fin.get();
				if(none == EOF)
				{	
					clrscr();
					gotoxy(25, 10);
					cout << "WARNING! Empty file : \"exception.txt\""<< endl;
					Sleep(2000);
					clrscr();
					total = 0;
					return total;
				}
				while (TRUE) // ???? ?????? 
				{
					char c;
					c = fin.get();
					if (c == EOF && pre_enter == TRUE)
					{
						break;
					}
					else if(c == EOF && pre_enter == FALSE)
					{
						total++;
						break;
					}
					if (c == '\n')
					{
						pre_enter = TRUE;
						total++;
						continue;
					}
					pre_enter = FALSE;
				}
				fin.close();
				return total;
			}	
		default :
			clrscr();
			gotoxy(25, 10);
			cout << "var value error!" << endl;
			Sleep(2000);
			return 0;		
	}
}
int CancelImposition(HWND m_hwnd)
{	
	char num[10] = {0,}; // ???????? 
	clrscr();
	PrintImposition();
	
	Address num_address(0,GetNum(NUM));
	Address *Ap; 
	Ap = &num_address;
	
	FILE* fp = fopen("number.txt", "r");
	if (fp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(number.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	FILE* fp2 = fopen("processing.txt", "r+");
	if (fp2 == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(processing.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	
	fseek(fp2,-1,SEEK_END); // ?????? ?????? ???? ?????? ?? 
	char c;
	c = fgetc(fp2);
	if(c != '\n') // ?????????? ?????? ???????? ???? (?????? ???? ????) 
	{
		fseek(fp2,0L,SEEK_END); 
		fputc('\n',fp2);
	}
	else
	{
		fseek(fp2,0L,SEEK_END); 
	}
	
	while (TRUE)
	{		
		SetForegroundWindow(m_hwnd);
		CalPrint(Ap->GetTotal(),Ap->GetFinish()); 
		gotoxy(26,14); // ???????? ????
		fgets(num, 10, fp); // fgets ?? ???????????? ??????		
		if(Ap->GetFinish()+1 != Ap->GetTotal()) // ?????? ?????????? ???????? ?????????? ?????????????? ????????????
			num[strlen(num) - 1] = '\0';
		cout << num << endl;
		// ???????? ???? 30??????
		bool error = FALSE; 
		while(TRUE)
		{
			CopyTextToClipboard(num);
			SetCursorPos(1387, 415);
			MouseLeftClick();
			MouseLeftClick();
			MouseLeftClick();
			PasteText();
			PasteText();
			keybd_event(VK_F3, 0, 0, 0);  
			keybd_event(VK_F3, 0, KEYEVENTF_KEYUP, 0);
		
			Sleep(6000); // ???????? ???????? 
			SetCursorPos(1094,642);
			MouseLeftDoubleClick();
			Sleep(5000); // ?????????? ?????? ???? 
			SetCursorPos(577,662); // ???????? ????
			MouseLeftClick();
			CopyText();
			int count = 0; // ???? ?? ?????????? ?????? ???????? ???????? 
		
			while(TRUE) // ???????? ???? ???? ?????? 
			{	
				Ap->SetJudge(CopyClipboardToText());
				if(strlen(Ap->GetJudge()) >= 15) {    // ?????? ?????? ???????? 
					gotoxy(10,21);
					cout << "????????! ???? ?? ?????????????? ?????????? (ESC??) code : 1";
					Tmp_Pause();
					gotoxy(10,21);
					cout << "                                                              ";
					CopyTextToClipboard("clear"); // ???????? ???? ??????
					error = TRUE; 
					break;
				}
				else if(strlen(Ap->GetJudge()) == 8 || strlen(Ap->GetJudge()) == 9) { // ?????????? ???????? ???????? ???? ?????????? ????
					break;
				}
			
				if(count >= 8) // ???????????????? ???? 
				{
					gotoxy(10,21);
					cout << "????????! ???? ?? ?????????????? ?????????? (ESC??) code : 2";
					Tmp_Pause();
					gotoxy(10,21);
					cout << "                                                             ";
					count = 0; // count ??????
					error = TRUE; 
					break;
				}	
				Sleep(2000); // ???????? ???????? 
				SetCursorPos(1094,642);
				MouseLeftDoubleClick();
				Sleep(2000); // ?????????? ?????? ???? 
				SetCursorPos(577,662); // ???????? ????
				MouseLeftClick();
				CopyText();	
				count++;	
			}
			if(error == TRUE) {
				error = FALSE; // ?????? ?????? 
				continue; 
			}
			else {
				break;
			}
		}
		gotoxy(26,16);
		cout << CopyClipboardToText();
		fputs(CopyClipboardToText(),fp2);   
		fputc(' ',fp2);
		SetCursorPos(1118,373); // ?????????? ????
		MouseLeftClick();
		CopyText();
		gotoxy(28,18);
		cout << CopyClipboardToText();
		fputs(CopyClipboardToText(),fp2);
		if(Ap->GetFinish()+1 != Ap->GetTotal()) // ?????? ?????? ???????? ???????? ????
			fputc('\n',fp2);
		SetCursorPos(1380,517); // ?????????? ?????? 
		MouseLeftClick();
		keybd_event(VK_NEXT, 0, 0, 0);  // page down 
		keybd_event(VK_NEXT, 0, KEYEVENTF_KEYUP, 0);
		Sleep(500);
		SetCursorPos(1065,610);
		MouseLeftDoubleClick();
		CopyText();
		Ap->SetJudge(CopyClipboardToText());
		Sleep(500); 
		SetCursorPos(1420,558); // ?????????? ?????? 
		MouseLeftClick();
		keybd_event(VK_PRIOR, 0, 0, 0);  // page up
		keybd_event(VK_PRIOR, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
		if(strlen(Ap->GetJudge()) == 4) // '????'???? ???????? ???? ???? 
		{
			SetCursorPos(1108,239);
			MouseLeftClick();
			Sleep(2000); // ???????????? ?????????? 
			SetCursorPos(917,594);
			MouseLeftClick(); 
			Sleep(6000); // '??'?????? ???? 
			SetCursorPos(951,576);
			MouseLeftClick(); 
			Sleep(1000);
		}
		else // '??????????' ???? ???????? ???? ????
		{
			SetCursorPos(1133,239);
			MouseLeftClick();
			Sleep(2000); // ???????????? ?????????? 
			SetCursorPos(915,579);
			MouseLeftClick(); 
			Sleep(6000); // '??'?????? ???? 
			SetCursorPos(953,576);
			MouseLeftClick(); 
			Sleep(1000);
		} 
		
		SetCursorPos(578,783);
		MouseLeftClick();
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				if((int)CurrentDateTime()[i] - '0' == j)
				{
					keybd_event(48+j, 0, 0, 0);
					keybd_event(48+j, 0, KEYEVENTF_KEYUP, 0);
					break;
				}
			}
		}
		Sleep(1000);
		CopyTextToClipboard("?????? ???? ????");
		PasteText();
		keybd_event(VK_F7, 0, 0, 0);
		keybd_event(VK_F7, 0, KEYEVENTF_KEYUP, 0);
		Sleep(6000); // ???? ???? 
		SetCursorPos(953,578);
		MouseLeftClick();
		Sleep(4000); //???? ???? 
		SetCursorPos(1478,182);
		MouseLeftClick(); 
		
		Ap->SetFinish(Ap->GetFinish()+1); //finish++; // ???????? ???????? ?? ???? ???? 
		SetForegroundWindow(m_hwnd); // ?? ?????? ???? ???????? ????. 
		CalPrint(Ap->GetTotal(), Ap->GetFinish());
		if (Ap->GetFinish() == Ap->GetTotal())
		{
			for (int i = 5; i > 0; i--)
			{
				gotoxy(13, 21);
				cout << "???? ?????? ??????????????! " << i << "?? ???? ??????????.       ";
				Sleep(1000);
			}
			break;
		}
		for (int i = 3; i > 0; i--)
		{
			if (_kbhit() && _getch() == VK_ESCAPE)
				Tmp_Pause();
			gotoxy(13, 21);
			cout << "?????? ??????????????! " << i << "?? ???? ???? ?????? ??????????.";
			Sleep(1000);
		}	
		RmPrint();	
	}
	fclose(fp2);
	fclose(fp);
	clrscr();
	gotoxy(15, 12);
	cout << "???????? ?????? ???? ??????????????.(Press any key)";
	while (TRUE)
	{
		if (_kbhit())
		{
			char c = _getch();
			break;
		}
	}
	return 0;
}
void PrintRegistration()
{
	gotoxy(35, 4);
	cout << "????????" << endl;
	gotoxy(12, 7);
	cout << "?????? : ????????????????????????????????????????";
	gotoxy(62, 7);
	cout << "(0  %)";
	gotoxy(12, 9);
	cout << "???????? : Off";
	gotoxy(12, 11);
	cout << "???????? :     ??     ??";
	gotoxy(12, 13);
	cout << "=====================================================";
	gotoxy(12, 14);
	cout << "| ???????? :                                        |";
	gotoxy(12, 15);
	cout << "|                                                   |";
	gotoxy(12, 16);
	cout << "| ?????? ???? :                                     |";
	gotoxy(12, 17);
	cout << "=====================================================";
}

int RegisterDoc(HWND m_hwnd)
{
	char name[50] = {0,};
	char num[20] = {0,};

	clrscr();
	PrintRegistration();
	
	Number processing(0, GetNum(PRO));
	Number *Np; 
	Np = &processing;
	
	ifstream fin;
	fin.open("processing.txt");
	if (!fin)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(processing.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	
	while(TRUE)
	{
		SetForegroundWindow(m_hwnd);
		CalPrint2(Np->GetTotal(),Np->GetFinish());
		fin.getline(num, 10, ' ');
		fin.getline(name, 80, '\n');
		gotoxy(25,14);
		cout << num;
		gotoxy(28,16);
		cout << name;
		SetCursorPos(542,205);
		MouseLeftClick();
		SetCursorPos(609,230);
		MouseLeftClick();
		Sleep(1500); //  ?????????????? 
		SetCursorPos(654,361);
		MouseLeftClick();
		CopyTextToClipboard("?????? ???? ???? (");
		PasteText();
		CopyTextToClipboard(num);
		PasteText();
		keybd_event(VK_SHIFT, 0, 0, 0);
		keybd_event(0x30, 0, 0, 0);
		keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
		SetCursorPos(654,626);
		MouseLeftClick();
		CopyTextToClipboard(name);
		PasteText();
		SetCursorPos(722,676);
		MouseLeftClick();
		Sleep(100);
		SetCursorPos(659,703);
		MouseLeftClick();
		SetCursorPos(735,703);
		MouseLeftClick();
		SetCursorPos(875,703);
		MouseLeftClick();
		SetCursorPos(657,728);
		MouseLeftClick();
		CopyTextToClipboard("???????? ????");
		PasteText() ;
		SetCursorPos(1367,303);
		MouseLeftClick(); 
		Sleep(1500); // ???? 
		SetCursorPos(963,600);
		MouseLeftClick();
		CopyTextToClipboard("??????");
		Sleep(5000); // ?????????? ???????? 
		FindText();
		Sleep(500);
		PasteText();
		Sleep(500);
		SetCursorPos(1272,240);
		MouseLeftClick();
		SetCursorPos(982,465);
		MouseLeftDoubleClick();
		SetCursorPos(1227,791);
		MouseLeftClick();
		
		Np->SetFinish(Np->GetFinish()+1);//finish++; // ???????? ?? ???? ???? 
		SetForegroundWindow(m_hwnd); // ?? ?????? ???? ???????? ????. 
		CalPrint2(Np->GetTotal(), Np->GetFinish());
		Sleep(4500);
		if (Np->GetFinish() == Np->GetTotal())
		{
			for (int i = 5; i > 0; i--)
			{
				gotoxy(13, 21);
				cout << "???? ?????? ??????????????! " << i << "?? ???? ??????????.       ";
				Sleep(1000);
			}
			break;
		}
		for (int i = 3; i > 0; i--)
		{
			if (_kbhit() && _getch() == VK_ESCAPE)
				Tmp_Pause();
			gotoxy(13, 21);
			cout << "?????? ??????????????! " << i << "?? ???? ???? ?????? ??????????.";
			Sleep(1000);
		}
		RmPrint2();	
	}
	fin.close();
	clrscr();
	gotoxy(15, 12);
	cout << "???????? ?????? ???? ??????????????.(Press any key)";
	while (TRUE)
	{
		if (_kbhit())
		{
			char c = _getch();
			break;
		}
	}
	return 0;
}
int Exception(HWND m_hwnd) // ?? ?????? ?????????? cancelImposition?? ?????????? ?????? 
{
	/*
	char num[10] = {0,}; // ???????? 

	clrscr();
	PrintImposition();
	
	Number exception(0, GetNum(EXC));
	Number *Np;
	Np = &exception;
	FILE* fp = fopen("exception.txt", "r");
	if (fp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(exception.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	FILE* fp2 = fopen("processing.txt", "r+");
	if (fp2 == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(processing.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	// ???? ???? ?????? ???? 
	SetCursorPos(945,230);
	MouseLeftClick();
	keybd_event(VK_F2, 0, 0, 0); 
	keybd_event(VK_F2, 0, KEYEVENTF_KEYUP, 0);
	Sleep(500); 
	
	fseek(fp2,-1,SEEK_END); // ?????? ?????? ???? ?????? ?? 
	char c;
	c = fgetc(fp2);
	if(c != '\n') // ?????????? ?????? ???????? ???? (?????? ???? ????) 
	{
		fseek(fp2,0L,SEEK_END); 
		fputc('\n',fp2);
	}
	else
	{
		fseek(fp2,0L,SEEK_END); 
	}
	
	while (TRUE)
	{	
		SetForegroundWindow(m_hwnd);
		CalPrint(Np->GetTotal(),Np->GetFinish()); 
		gotoxy(26,14); // ???????? ????
		fgets(num, 10, fp); // fgets ?? ???????????? ??????		
		if(Np->GetFinish()+1 != Np->GetTotal()) // ?????? ?????????? ???????? ?????????? ?????????????? ????????????
			num[strlen(num) - 1] = '\0';
		cout << num << endl;
		// ???????? ???? 30?????? 
		CopyTextToClipboard(num);
		SetCursorPos(1387, 415);
		MouseLeftClick();
		PasteText();
		PasteText();
		keybd_event(VK_F3, 0, 0, 0);  
		keybd_event(VK_F3, 0, KEYEVENTF_KEYUP, 0);
		Sleep(7000); // ???????? ???????? 
		SetCursorPos(1094,642);
		MouseLeftDoubleClick();
		Sleep(7000); // ?????????? ?????? ???? 
		SetCursorPos(577,662); // ???????? ????
		MouseLeftClick();
		CopyText();
		gotoxy(26,16);
		cout << CopyClipboardToText();
		fputs(CopyClipboardToText(),fp2);
		fputc(' ',fp2);
		SetCursorPos(1118,373); // ?????????? ????
		MouseLeftClick();
		CopyText();
		gotoxy(28,18);
		cout << CopyClipboardToText();
		fputs(CopyClipboardToText(),fp2);
		if(Np->GetFinish()+1 != Np->GetTotal()) // ?????? ?????? ???????? ???????? ????   
			fputc('\n',fp2);
		SetCursorPos(1095,239);
		MouseLeftClick();
		Sleep(2000); // ???????????? ?????????? 
		SetCursorPos(915,579);
		MouseLeftClick(); 
		Sleep(5000); // '??'?????? ???? 
		SetCursorPos(953,576);
		MouseLeftClick(); 
		Sleep(1000);
		SetCursorPos(578,783);
		MouseLeftClick();
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				if((int)CurrentDateTime()[i] - '0' == j)
				{
					keybd_event(48+j, 0, 0, 0);
					keybd_event(48+j, 0, KEYEVENTF_KEYUP, 0);
					break;
				}
			}
		}
		Sleep(1000);
		CopyTextToClipboard("?????? ???? ????");
		PasteText();
		keybd_event(VK_F7, 0, 0, 0);
		keybd_event(VK_F7, 0, KEYEVENTF_KEYUP, 0);
		Sleep(3000); // ???? ???? 
		SetCursorPos(953,578);
		MouseLeftClick();
		Sleep(4000); //???? ???? 
		SetCursorPos(1478,182);
		MouseLeftClick(); 
		
		Np->SetFinish(Np->GetFinish()+1);//finish++; // ???????? ???????? ?? ???? ???? 
		SetForegroundWindow(m_hwnd); // ?? ?????? ???? ???????? ????. 
		CalPrint(Np->GetTotal(), Np->GetFinish());
		if (Np->GetFinish() == Np->GetTotal())
		{
			for (int i = 5; i > 0; i--)
			{
				gotoxy(13, 21);
				cout << "???? ?????? ??????????????! " << i << "?? ???? ??????????.       ";
				Sleep(1000);
			}
			break;
		}
		for (int i = 3; i > 0; i--)
		{
			if (_kbhit() && _getch() == VK_ESCAPE)
				Tmp_Pause();
			gotoxy(13, 21);
			cout << "?????? ??????????????! " << i << "?? ???? ???? ?????? ??????????.";
			Sleep(1000);
		}	
		RmPrint();	
	}
	fclose(fp2);
	fclose(fp);
	clrscr();
	gotoxy(15, 12);
	cout << "???????? ?????? ???? ??????????????.(Press any key)";
	while (TRUE)
	{
		if (_kbhit())
		{
			char c = _getch();
			break;
		}
	}
	*/
	clrscr();
	gotoxy(30, 3);
	cout << "???? ???????? (Press any key)";
	gotoxy(5,6);
	cout << "1. ???????? ??????, ?????? ?????? ???????? ???? ?????? ??????????????." ;
	gotoxy(5,8);
	cout << "2. number, processing ?????? ???? ?????????? ?????? ?????? ?????????? ??????????????.";
	gotoxy(5,10);
	cout << "3. ???????? ?????? ???????????? ?????? ???? ?????????? ?????? ?? ???? ??????????????.";
	gotoxy(5,12);
	cout << "4. ?????? ???????????? ???????? ?????? ?????? ?????????? ??????????????."; 
	gotoxy(5,14);
	cout << "5. ???? processing ???? ???????? ???????? ?????? ???? ?????????? ??????????????."; 
	gotoxy(5,16);
	cout << "6. ?????????? 3?????? ???????? ?? ?????? ?????????? ??????????????. "; 
	gotoxy(5,19);
	cout << "!!! ???????? ???? ?? ?????????? ?????????? ?????? ?????? ??, processing???? ?????? ?????? ???????? ?????? ?????? ???? ????????????... ?????????? ?????? 150?? ?????? ??????????";
	
	while (TRUE)
	{
		if (_kbhit())
		{
			char c = _getch();
			break;
		}
	}
	return 0;
}
int Back_Up()
{
	clrscr();
	FILE *nfp, *nbfp, *pfp, *pbfp, *efp, *ebfp; // number, number_back_up, processing, processing_back_up, exception, exception_back_up 
	Number number(0, GetNum(NUM));
	Number *Np; 
	Np = &number;
	
	Number processing(0, GetNum(PRO));
	Number *Pp;
	Pp = &processing;
	
	Number exception(0, GetNum(EXC));
	Number *Ep;
	Ep = &exception; 
	
	char num[10] = {0,}; // ????????
	char pstr[100] = {0,}; // processing str
	char estr[100] = {0,}; // exception str
	nfp = fopen("number.txt","r");
	if (nfp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(number.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	nbfp = fopen("C:\\Users\\user\\Desktop\\??????\\????\\number_back_up.txt","wt");
	if (nbfp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(number_back_up.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	pfp = fopen("processing.txt","r");
	if (pfp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(processing.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	pbfp = fopen("C:\\Users\\user\\Desktop\\??????\\????\\processing_back_up.txt","wt");
	if (pbfp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(processing_back_up.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	efp = fopen("exception.txt","r");
	if (nfp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(exception.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	ebfp = fopen("C:\\Users\\user\\Desktop\\??????\\????\\exception_back_up.txt","wt");
	if (nbfp == NULL)
	{
		clrscr();
		gotoxy(25, 10);
		cout << "cannot open file!(exception_back_up.txt)" << endl;
		Sleep(2000);
		return 0;
	}
	
	while(TRUE)
	{	
		fgets(num, 10, nfp); // fgets ?? ???????????? ??????		
		CopyTextToClipboard(num);
		fputs(CopyClipboardToText(),nbfp);
		Sleep(30);
		
		Np->SetFinish(Np->GetFinish()+1);//finish++; // ???????? ?? ???? ???? 
		CalPrint3(Np->GetTotal(), Np->GetFinish());
		if(Np->GetTotal() == 0)
		{
			gotoxy(30, 10);
			cout << "number back up complete" << endl;
			Sleep(1000);
			break;
		}
		if (Np->GetFinish() == Np->GetTotal())
		{
			gotoxy(30, 10);
			cout << "number back up complete" << endl;
			Sleep(1000);
			break;
		}		
	}
	clrscr();
	while(TRUE)
	{	
		fgets(pstr, 100, pfp); // fgets ?? ???????????? ??????	
		
		CopyTextToClipboard(pstr);
		fputs(CopyClipboardToText(),pbfp);
		Sleep(30);
		Pp->SetFinish(Pp->GetFinish()+1);//finish++; // ???????? ?? ???? ???? 
		CalPrint3(Pp->GetTotal(), Pp->GetFinish());
		if(Pp->GetTotal() == 0)
		{
			gotoxy(30, 10);
			cout << "processing back up complete" << endl;
			Sleep(1000);
			break;
		}
		if (Pp->GetFinish() == Pp->GetTotal())
		{
			gotoxy(30, 10);
			cout << "processing back up complete" << endl;
			Sleep(1000);
			break;
		} 
	}
	clrscr();
	while(TRUE)
	{
		
		fgets(estr, 100, efp); // fgets ?? ???????????? ??????		
		CopyTextToClipboard(estr);
		fputs(CopyClipboardToText(),ebfp);
		Sleep(30);
		
		Ep->SetFinish(Ep->GetFinish()+1);//finish++; // ???????? ?? ???? ???? 
		CalPrint3(Ep->GetTotal(), Ep->GetFinish());
		if(Ep->GetTotal() == 0)
		{
			gotoxy(30, 10);
			cout << "exception back up complete" << endl;
			Sleep(1000);
			break;
		}
		if (Ep->GetFinish() == Ep->GetTotal())
		{
			gotoxy(30, 10);
			cout << "exception back up complete" << endl;
			Sleep(1000);
			break;
		} 
	}
	fclose(nfp);
	fclose(nbfp);
	fclose(pfp);
	fclose(pbfp);
	fclose(efp);
	fclose(ebfp);
	clrscr();
	gotoxy(33, 8);
	cout << "back up complete!" << endl;
	gotoxy(34, 10);
	cout << "Press any key..";
	Sleep(1000);
	while (TRUE)
	{
		if (_kbhit())
		{
			char c = _getch();
			break;
		}
	}
	return 0;
}

enum { BACKUP = 0, CANCEL, REGISTER, EXCEPTION };

int main()
{
	system("title macro.exe");
	HWND m_hwnd = GetForegroundWindow();
	::SetWindowPos(m_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // ???????????? 
	SetForegroundWindow(m_hwnd); // ?????? ?????? 
	
	int select;
	bool escape;
	setcursortype(NOCURSOR);
	while (1)
	{
		clrscr();
		printMain();
		escape = FALSE;
		while (1)
		{
			if (_kbhit())
			{
				select = _getch() - '0';
				switch (select)
				{
				case CANCEL:
					CancelImposition(m_hwnd);
					escape = TRUE;
					break;
				case REGISTER:
					RegisterDoc(m_hwnd);
					escape = TRUE;
					break;
				case EXCEPTION:
					Exception(m_hwnd);
					escape = TRUE;
					break;
				case BACKUP:
					Back_Up();
					escape = TRUE;
					break;
				case ESC - '0':
					return 0;
				default:
					gotoxy(45, 12);
					cout << "!Message : Wrong number!";
					Sleep(1000);
					escape = TRUE;
					break;
				}
			}
			if (escape == TRUE) // ???? ???? ?? ?????? ???? 
				break;
		}
	}

	return 0;
}
