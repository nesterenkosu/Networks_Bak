#pragma once

#include <windows.h>
#include <wininet.h>
//#include <stdio.h>

HINTERNET hInet, hSession, hRequest;
#define SERVER_PORT     3021

int			   State=0;

namespace Client {

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



	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Timer^  timer1;
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
			this->components = (gcnew System::ComponentModel::Container());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(108, 265);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(321, 22);
			this->textBox1->TabIndex = 6;
			this->textBox1->Text = L"123";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(1, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(592, 212);
			this->listBox1->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(460, 261);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(122, 28);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Отправить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 227);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(93, 17);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Имя сервера";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(137, 227);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(125, 22);
			this->textBox3->TabIndex = 13;
			this->textBox3->Text = L"localhost";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 268);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(84, 17);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Сообщение";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(601, 301);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->listBox1);
			this->Name = L"Form1";
			this->Text = L"Клиент";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
		//listBox1->Items->Add(L"Клиент запущен");
	}
	// -----------------------------------------------------------------------------------------------------------------
	
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		int      rc, l1, l3, i, Code;
		//char     Buf[1001], Buf1[1001]; 
		wchar_t  Buf[1001], Buf1[1001], Buf3[1001], Buf4[1001];

		l3 = textBox3->Text->Length;
		if (l3 <= 0) {
			listBox1->Items->Add("Не задано имя сервера");
			return;
		} // if

		for (i = 0; i < l3; i++) {
			Buf3[i] = textBox3->Text->default[i];
			Buf3[i+1] = 0;
		} // for

		l1 = textBox1->Text->Length;
		if (l1 <= 0) {
			listBox1->Items->Add("Нет текста сообщения");
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

		hSession = InternetConnect(hInet, Buf3, SERVER_PORT, L"Sartasov", L"123", INTERNET_SERVICE_HTTP, 0, 0);
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
		//Отправка сообщения. Сообщение находится в переменной Buf
		Code = HttpSendRequest(hRequest, NULL, 0, Buf, 2*(10+l1));
		if (!Code) {
			Code = GetLastError();
			listBox1->Items->Add(L"Ошибка HttpSendRequest");
			return;
		} 

		State = 1;
		timer1->Enabled = true;
	}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		DWORD		Len=1000;
		int			Code;
		wchar_t		Buf[1001], *Begin, *End; 

		if (State == 1) {	// Получить код ответа
			Len = 10;
			Code = HttpQueryInfo(hRequest,	HTTP_QUERY_STATUS_CODE,	Buf, &Len, NULL);			// IN OUT LPDWORD lpdwIndex,
			if (!Code) {
				listBox1->Items->Add(L"Ошибка HttpQueryInfo(HTTP_QUERY_STATUS_CODE)");
				return;
			} // if

			Code = _wtoi(Buf);
			if (Code >= 300) {
				listBox1->Items->Add(L"От сервера получен ошибочный код возврата");
				State = 0; 
				timer1->Enabled = false;
 				return;
			} // if
			State = 4;
		} // if

		if (State == 2) {	// Получить заголовок ответа
			Len = 1000;
			Code = HttpQueryInfo(hRequest,	HTTP_QUERY_RAW_HEADERS_CRLF, Buf, &Len, NULL);				
			if (!Code) {
				listBox1->Items->Add(L"Ошибка HttpQueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF)");
				return;
			} // if
			State = 4;
			Len = 1000;
		} // if

		if (State == 3) {	// Получить размер ответа
			Len = 10;
			Code = HttpQueryInfo(hRequest,	HTTP_QUERY_CONTENT_LENGTH, Buf,	&Len, NULL);	
			if (!Code) {
				listBox1->Items->Add(L"Ошибка HttpQueryInfo(HTTP_QUERY_CONTENT_LENGTH)");
				return;
			} // if
			Len = _wtoi(Buf);
			if (Len <= 0) {
				listBox1->Items->Add(L"Ошибка в размере ответа");
				State = 0; 
				timer1->Enabled = false;
 				return;
			} // if
			State = 4;
		} // if

		if (State == 4) {	// Получить ответ
			//Принятие ответа от сервера в переменную Buf
			Code = InternetReadFile(hRequest, Buf, 1000,	&Len);	
			if (!Code) {
				listBox1->Items->Add(L"Ошибка при получении ответа");
				return;
			} // if
		} // if
		State = 0;
		timer1->Enabled = false;
		Begin = wcsstr(Buf, L"Begin=")+6;
		if (Begin == NULL) {
			listBox1->Items->Add(L"Нет текста Begin=");
			return;
		} // if
		End = wcsstr(Buf, L"End");
		if (End == NULL) {
			listBox1->Items->Add(L"Нет текста End");
			return;
		} // if
		*End = '\0';
		String ^ s= gcnew String(Begin);
		listBox1->Items->Add(L"Получено " + s);
	}
};
  
}

