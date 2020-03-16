#pragma once
#include "stdafx.h"


namespace PADK_UART_VC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			pData = nullptr;
			pData = new unDaneType;
			if (pData != nullptr)  fDaneDSP(pData);
			znak = 47;
			flaga = false;
			buf = buf_0 = 48;
			odbLancZn = false;
			this->serialPort1->Open();
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			this->serialPort1->Close();
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		unDaneType *pData;
		char znak;
		int buf, buf_0;
		bool flaga;
		int numb;
		bool odbLancZn;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::ComponentModel::IContainer^  components;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(39, 33);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(614, 136);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(39, 194);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Wyœlij";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			this->button1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button1_MouseDown);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 115200;
			this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MyForm::serialPort1_DataReceived);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(316, 192);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(104, 45);
			this->trackBar1->TabIndex = 2;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(449, 204);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"label1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(168, 203);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Wyslij 1 bajt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::button2_MouseDown);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(39, 233);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(126, 17);
			this->checkBox1->TabIndex = 5;
			this->checkBox1->Text = L"Odbiór  ³ancucha zn.";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(696, 262);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if (pData != nullptr) { delete pData; }
}
private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
	if (odbLancZn == true) { // Odbiór ca³ego ³añcucha znaków
		array <unsigned char> ^buffer = gcnew array <unsigned char>(SIZE_TAB_ZN);
		array <unsigned char> ^buffer1 = gcnew array <unsigned char>(SIZE_TAB_ZN);
		numb = this->serialPort1->Read(buffer, 0, SIZE_TAB_ZN);
		this->serialPort1->DiscardInBuffer();
//		this->serialPort1->DiscardOutBuffer();
		int nx = this->serialPort1->BytesToRead;
		if (nx > 0) {
			int nx1 = this->serialPort1->Read(buffer1, 0, nx);
		}
		//		this->serialPort1->DiscardInBuffer();
		if (numb != SIZE_TAB_ZN) {
			String ^napis = gcnew String("B³¹d odczytu ³añcucha znaków!!!, numb = ");
			napis += numb.ToString();
			MessageBox::Show(napis); }
		else {
			for (int i = 0; i < SIZE_TAB_ZN; i++) {
				tab_zn_input[i] = buffer[i];
			}
		}
		flaga = true;
	}
	else {
		array <unsigned char> ^buffer = gcnew array <unsigned char>(1);
		buf = this->serialPort1->ReadByte();
		this->serialPort1->DiscardInBuffer();
	}
		//	this->label1->Text = "Byte = " + buf.ToString();
//		buffer[0] = buf;
//		buffer[0] = znak;
//		this->serialPort1->Write(buffer, 0, 1);
//		this->serialPort1->DiscardOutBuffer();
		//for (int i = 0; i < sizeof(StrDaneDSP); i++) {
		//	pData->Buf[i] = this->serialPort1->ReadByte();
		//}
		//this->textBox1->Text += gcnew String(pData->DxDSP.Komunikat);
		//this->label1->Text = "Gain = " + pData->DxDSP.gain.ToString();
}
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
	//pData->DxDSP.gain = this->trackBar1->Value;
	//pData->DxDSP.minGain = this->trackBar1->Minimum;
	//pData->DxDSP.maxGain = this->trackBar1->Maximum;
	//array <unsigned char> ^buffer = gcnew array <unsigned char>(sizeof(StrDaneDSP));
	//for (int i = 0; i < sizeof(StrDaneDSP); i++) {
	//	buffer[i] = pData->Buf[i];
	//}
	//this->serialPort1->Write(buffer, 0, sizeof(StrDaneDSP));
	////	this->serialPort1->DiscardOutBuffer();
	array <unsigned char> ^buffer = gcnew array <unsigned char>(1);
	buffer[0] = 49 + this->trackBar1->Value;
	this->serialPort1->Write(buffer, 0, 1);
	this->serialPort1->DiscardOutBuffer();

}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	//pData->DxDSP.Komunikat[0] = znak;
	//pData->DxDSP.Komunikat[1] = znak;
	//pData->DxDSP.Komunikat[2] = '\0';
	//pData->DxDSP.wysw7Segm = znak - 48;
	//pData->DxDSP.gain = this->trackBar1->Value;
	//pData->DxDSP.minGain = this->trackBar1->Minimum;
	//pData->DxDSP.maxGain = this->trackBar1->Maximum;
	//znak++;
	//if (znak > 58)  znak = 48;
	//array <unsigned char> ^buffer = gcnew array <unsigned char>(sizeof(StrDaneDSP));
	//for (int i = 0; i < sizeof(StrDaneDSP); i++) {
	//	buffer[i] = pData->Buf[i];
	//}
	//this->serialPort1->Write(buffer, 0, sizeof(StrDaneDSP));
}
private: System::Void button2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		znak++;
		if (znak > 57)  znak = 48;
		array <unsigned char> ^buffer = gcnew array <unsigned char>(1);
		buffer[0] = znak;
		this->serialPort1->Write(buffer, 0, 1);
		this->serialPort1->DiscardOutBuffer();
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (odbLancZn == true) { // Odbiór ca³ego ³añcucha znaków
		if (flaga == true) {
			this->textBox1->Text += gcnew String(tab_zn_input);
			flaga = false;
		}
	}
	else {
		if (buf != buf_0) {
			char tab[2];
			tab[0] = buf;
			tab[1] = '\0';
			this->label1->Text = "Byte = " + buf.ToString();
			this->textBox1->Text += " ";
			this->textBox1->Text += gcnew String(tab);
			buf_0 = buf;
		}
	}
}
private: System::Void button1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	array <unsigned char> ^buffer = gcnew array <unsigned char>(SIZE_TAB_ZN);
	for (int i = 0; i < SIZE_TAB_ZN; i++) {
		buffer[i] = tab_zn[i];
	}
	this->serialPort1->DiscardOutBuffer();
	this->serialPort1->Write(buffer, 0, SIZE_TAB_ZN);
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (this->checkBox1->Checked) { odbLancZn = true; }  
	else { odbLancZn = false; }
}
};
}
