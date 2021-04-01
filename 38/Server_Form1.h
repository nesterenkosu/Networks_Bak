#pragma once

#include <windows.h>
#include <wininet.h>
//#include <winsock.h>
#include <stdio.h>

#define	WSA_NETEVENT		(WM_USER+2)
#define	WSA_NETACCEPT		(WM_USER+3)
HINTERNET hInet, hSession, hRequest;

#define CLIENT_PORT     3021
#define SERVER_PORT     3022

SOCKET         	TCPSocket, TmpSocket;
sockaddr_in	CallAddress;
sockaddr_in	OurAddress;
int		f=0;

namespace Server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button2;





	private: System::Windows::Forms::Label^  label3;

	private: System::ComponentModel::IContainer^  components;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(81, 215);
			this->textBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(242, 20);
			this->textBox1->TabIndex = 6;
			this->textBox1->Text = L"123";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(1, 0);
			this->listBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(445, 173);
			this->listBox1->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(345, 212);
			this->button2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(92, 23);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Отправить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 218);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 13);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Сообщение";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(446, 271);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->listBox1);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"Form1";
			this->Text = L"Сервер";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
			
	WSADATA	  WSAData;
	int	  rc;
	char	  Name[101], *IpAddr, Buf[1000];
	PHOSTENT  phe;
			 
	if (f==1) return;
	f = 1;
  	rc = WSAStartup(MAKEWORD(2,0), &WSAData);
	if (rc != 0) {
		listBox1->Items->Add("Ошибка инициализации WSAStartup");
		return;
	} // if

	TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (TCPSocket == INVALID_SOCKET) {
		listBox1->Items->Add("Протокол TCP установлен.");
	} // if

	memset(&OurAddress, 0, sizeof(OurAddress));
	OurAddress.sin_family = AF_INET;
	OurAddress.sin_port = htons(SERVER_PORT);

	rc =bind(TCPSocket, (LPSOCKADDR)&OurAddress, sizeof(sockaddr_in));
	if (rc == SOCKET_ERROR) {
		listBox1->Items->Add("Адресная ошибка");
		return;
	} // if
			
	rc = WSAAsyncSelect(TCPSocket, (HWND)(this->Handle.ToInt32()), WSA_NETACCEPT, FD_ACCEPT);
	if (rc != 0) {
		listBox1->Items->Add("Ошибка WSAAsyncSelect");
		return;
	} // if

	rc = listen(TCPSocket, 1);
	if (rc == SOCKET_ERROR) {
		listBox1->Items->Add("Ошибка listen");
		return;
	} // if

	gethostname(Name, 101);
	strcpy(Buf, "Имя компьютера ");
	strcat(Buf, Name);
	String ^ s= gcnew String(Buf);
	listBox1->Items->Add(s);
	phe = gethostbyname(Name);
	if (phe != NULL) {
		memcpy((void *)&(OurAddress.sin_addr), phe->h_addr, phe->h_length);
		IpAddr = inet_ntoa(OurAddress.sin_addr);
		strcpy(Buf, "IP-Адрес ");
		strcat(Buf, IpAddr);
		String ^ s2= gcnew String(Buf);
		listBox1->Items->Add(s2);
	} // if

	listBox1->Items->Add(L"Клиент запущен");
	}
	// -----------------------------------------------------------------------------------------------------------------
	
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		int      rc, l1, l3, i, Code;
		wchar_t  Buf[1001], Buf1[1001], Buf3[1001], Buf4[1001];
		char 	 *IP;
		DWORD	 Len=1000;
	

		l1 = textBox1->Text->Length;
		if (l1 <= 0) {
			listBox1->Items->Add("Не задано сообщение");
			return;
		} // if

		for (i = 0; i < l1; i++) {
			Buf1[i] = textBox1->Text->default[i];
			Buf1[i+1] = 0;
		} // for

		hInet = InternetOpen(L"MyAgent", INTERNET_OPEN_TYPE_DIRECT /* INTERNET_OPEN_TYPE_PRECONFIG*/, 
			NULL, NULL, 0);
		if (hInet == NULL) {
			listBox1->Items->Add(L"Ошибка InternetOpen");
			return;
		} // if
					
		IP = inet_ntoa(CallAddress.sin_addr);
		for (i = 0; i < strlen(IP); i++) {
			Buf3[i] = IP[i];
			Buf3[i+1] = 0;
		} // for

		hSession = InternetConnect(hInet, Buf3, CLIENT_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		if (hSession == NULL) {
			listBox1->Items->Add(L"Ошибка InternetConnect");
			return;
		} // if

		hRequest = HttpOpenRequest(hSession, L"POST", L"", L"HTTP/1.1", L"", NULL,
			INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT |
			INTERNET_FLAG_KEEP_CONNECTION, 0);
		if (hRequest == NULL) {
			Code = GetLastError();
			listBox1->Items->Add(L"Ошибка HttpOpenRequest");
			return;
		} // if		
		
		wcscpy(Buf, L"Begin=");
		wcscat(Buf, Buf1);
		wcscat(Buf, L"End");
		Code = HttpSendRequest(hRequest, NULL, 0, Buf, 2*(10+l1));
		if (!Code) {
			Code = GetLastError();
			listBox1->Items->Add(L"Ошибка HttpSendRequest");
			return;
		} 

		Code = InternetReadFile(hRequest, Buf, Len, &Len);	
		if (!Code) {
			listBox1->Items->Add(L"Ошибка при получении ответа");
			return;
		} // if

		
	}
    protected:
    virtual void WndProc (Message% m) override
	{
	 int     rc, l=sizeof(CallAddress), i;
         char	 Buf[10001];
	 wchar_t *Buf2, *Begin, *End;

		if (m.Msg == WSA_NETACCEPT) {
			if (m.LParam.ToInt32() == FD_ACCEPT) {
				TmpSocket = accept((SOCKET)m.WParam.ToInt32(), (PSOCKADDR)&CallAddress, (int *)&l);
				if (TmpSocket == INVALID_SOCKET) {
          				rc = WSAGetLastError();
          				listBox1->Items->Add(String::Format( "Ошибка accept {0}", rc ));
		          		return;
				} // if
				rc = WSAAsyncSelect(TmpSocket, (HWND)(this->Handle.ToInt32()), WSA_NETEVENT, FD_READ|FD_CLOSE);
				if (rc != 0) {
					listBox1->Items->Add("Ошибка WSAAsyncSelect");
					return;
				} // if
				listBox1->Items->Add("Канал создан");
			} // if
		} // if
		if (m.Msg == WSA_NETEVENT) {
			if (m.LParam.ToInt32() == FD_READ) {
				rc = recv((SOCKET)m.WParam.ToInt32(), (char *)Buf, sizeof(Buf)-1, 0);
				if (rc == SOCKET_ERROR) {
          				rc = WSAGetLastError();
          				listBox1->Items->Add(String::Format( "Ошибка recv {0}", rc ));
		          		return;
				} // if
				if (rc >= 1) {
					l = strlen(Buf);
					Buf2 = (wchar_t *)(Buf+l-1);
					Begin = wcsstr(Buf2, L"Begin=");
					if (Begin == NULL) {
						listBox1->Items->Add(L"Нет текста Begin=");
						return;
					} // if
					Begin = Begin + 6;
					End = NULL;
					l = wcslen(Buf2) - 2;
					for (i = l; i > 0; i--) {
						if (Buf2[i] == L'E' && Buf2[i+1] == L'n' && Buf2[i+2] == L'd') {
							End = &Buf2[i];
							break;
						} // if
					} // for 
					//End = wcsstr(Buf2, L"End");
					if (End == NULL) {
						listBox1->Items->Add(L"Нет текста End");
						return;
					} // if
					*End = '\0';
					String ^ s= gcnew String(Begin);
					listBox1->Items->Add(L"Получено " + s);
					send((SOCKET)m.WParam.ToInt32(), "OK", 6, 0); 				   
					closesocket((SOCKET)m.WParam.ToInt32());
				} // if
			} else {
				listBox1->Items->Add("Канал разорван");
			} // else
		} // if
        Form::WndProc( m );
      } // WndProc
	
};
  
}

