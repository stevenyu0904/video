#pragma once
#include<iostream>
#include "avi_header.h"
namespace cvsample {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog; //定義開檔
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::Timer^  timer3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		opencv_avi *avi;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(16, 15);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 29);
			this->button1->TabIndex = 0;
			this->button1->Text = L"OpenFile";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(16, 74);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(445, 359);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(16, 472);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(132, 25);
			this->textBox1->TabIndex = 2;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(157, 471);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 29);
			this->button2->TabIndex = 3;
			this->button2->Text = L"背景相減";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(469, 74);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(467, 359);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(265, 472);
			this->button3->Margin = System::Windows::Forms::Padding(4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(100, 29);
			this->button3->TabIndex = 5;
			this->button3->Text = L"相鄰相減";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// timer3
			// 
			this->timer3->Tick += gcnew System::EventHandler(this, &MyForm::timer3_Tick_1);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(373, 472);
			this->button4->Margin = System::Windows::Forms::Padding(4);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(100, 29);
			this->button4->TabIndex = 6;
			this->button4->Text = L"光流";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click_2);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(481, 472);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(96, 29);
			this->button5->TabIndex = 7;
			this->button5->Text = L"Stop";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(957, 511);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		char* char_filename;
		//CAvi *AVI; //使用AVI
		int m_select;
		bool m_IsAVI;
		long lCurrentFrameNum;//目前Frame數
		long lTotalFrameNum; //總Frame數
		void init() {
			lTotalFrameNum = NULL;
			lCurrentFrameNum = NULL;
			m_IsAVI = NULL;
			//trackBar1->Maximum = NULL;
			//label2->Text = "0/0";
	}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		//openFileDialog1->InitialDirectory = "F:\\code\\opencv\\new.txt";
		openFileDialog1->FileName = "";
		openFileDialog1->Filter = "AVI Files (*.avi; *.AVI)|*.avi; *.AVI||";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			textBox1->Text = openFileDialog1->FileName;
			avi = new opencv_avi();
			char_filename = (char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);//檔名轉換
			avi->OpenFile(char_filename);
			pictureBox1->Image = avi->Mattobmp(avi->getmatBg());//show first image
			
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		
		textBox1->Text = "背景相減";
		timer1->Start();
		
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		
		textBox1->Text = "相鄰相減";
		timer2->Start();
	 }
	private: System::Void button4_Click_2(System::Object^  sender, System::EventArgs^  e) {
		
		textBox1->Text = "光流";
		timer3->Start();
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (avi->Play()) {
			avi->background_segmentation();
			pictureBox1->Image = avi->Mattobmp(avi->getmatImg());
			pictureBox2->Image = avi->Mattobmp(avi->getResult());
			//textBox1->Text = "Timer";
		}
		
	}
	
	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (avi->Play()) {
			avi->adjacent_segmentation();
			pictureBox1->Image = avi->Mattobmp(avi->getmatImg());
			pictureBox2->Image = avi->Mattobmp(avi->getResult());
			//textBox1->Text = "Timer";
		}
	}
	private: System::Void timer3_Tick_1(System::Object^  sender, System::EventArgs^  e) {
		if (avi->Play()) {
			avi->light_flow_segmentation();
			pictureBox1->Image = avi->Mattobmp(avi->getmatImg());
			pictureBox2->Image = avi->Mattobmp(avi->getResult());
			//textBox1->Text = "Timer";
		}
	}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		
		textBox1->Text = "stop";
		timer1->Stop();
		timer2->Stop();
		timer3->Stop();
}
};
}
