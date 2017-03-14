#ifndef RURRING_H
#define RURRING_H

#pragma once

using namespace std;

namespace Rurry {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Rurring
	/// </summary>
	public ref class Rurring : public System::Windows::Forms::Form
	{
	public:
		Rurring(void)
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
		~Rurring()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		long long Rate;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Rurring::typeid));
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(19, 24);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(451, 23);
			this->progressBar1->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(201, 65);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Cancel";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Rurring::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Rurring::timer1_Tick);
			// 
			// Rurring
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(484, 111);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->progressBar1);
			this->Name = L"Rurring";
			this->Text = L"R u r r i n g";
			this->Load += gcnew System::EventHandler(this, &Rurring::Rurring_Load);
			this->ResumeLayout(false);

		}


#pragma endregion
	
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				if (progressBar1->Value < 100) {
					if (MessageBox::Show("Do you really want to cancel?", "R u r r y", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
						 Rurring::Close();
						 timer1->Stop();
					 } else {
						
					 }				 
					
				} else {
					Rurring::Close();
				}
			 }

	private: System::Void Rurring_Load(System::Object^  sender, System::EventArgs^  e) {
				timer1->Start();
			 }

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				progressBar1->Increment(1);
				if (progressBar1->Value == 100) {
					timer1->Stop();
					button1->Text = "OK";
					MessageBox::Show("Rurring complete!","R u r r e d");
					
				}
			 }

	};
}
#endif
