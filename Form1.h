#ifndef FORM1_H
#define FORM1_H

#pragma once
#include "Rurring.h"
#include "decompressor.h"
#include "compressor.h"
#include <fstream>
#include <msclr\marshal_cppstd.h>

using namespace std;

namespace Rurry {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
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
	private: System::Windows::Forms::PictureBox^  picRurryTitle;
	private: System::Windows::Forms::Button^  btnCompress;
	private: System::Windows::Forms::Button^  btnDecompress;
	private: System::Windows::Forms::Button^  btnAddFile;









	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteSelectedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  compressToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  compressAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  compressSelectedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  decompressToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  decompressAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  decompressSelectedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewHelpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::Button^  btnDeleteFile;

	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->picRurryTitle = (gcnew System::Windows::Forms::PictureBox());
			this->btnCompress = (gcnew System::Windows::Forms::Button());
			this->btnDecompress = (gcnew System::Windows::Forms::Button());
			this->btnAddFile = (gcnew System::Windows::Forms::Button());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteSelectedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compressToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compressAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compressSelectedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->decompressToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->decompressAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->decompressSelectedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewHelpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->btnDeleteFile = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picRurryTitle))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// picRurryTitle
			// 
			this->picRurryTitle->BackColor = System::Drawing::Color::Transparent;
			this->picRurryTitle->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picRurryTitle.BackgroundImage")));
			this->picRurryTitle->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->picRurryTitle->Location = System::Drawing::Point(-1, 21);
			this->picRurryTitle->Name = L"picRurryTitle";
			this->picRurryTitle->Size = System::Drawing::Size(255, 110);
			this->picRurryTitle->TabIndex = 0;
			this->picRurryTitle->TabStop = false;
			// 
			// btnCompress
			// 
			this->btnCompress->BackColor = System::Drawing::Color::White;
			this->btnCompress->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnCompress->Location = System::Drawing::Point(241, 65);
			this->btnCompress->Name = L"btnCompress";
			this->btnCompress->Size = System::Drawing::Size(100, 40);
			this->btnCompress->TabIndex = 1;
			this->btnCompress->Text = L"&Compress";
			this->btnCompress->UseVisualStyleBackColor = false;
			this->btnCompress->Click += gcnew System::EventHandler(this, &Form1::btnCompress_Click);
			// 
			// btnDecompress
			// 
			this->btnDecompress->BackColor = System::Drawing::Color::White;
			this->btnDecompress->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnDecompress->Location = System::Drawing::Point(345, 65);
			this->btnDecompress->Name = L"btnDecompress";
			this->btnDecompress->Size = System::Drawing::Size(120, 40);
			this->btnDecompress->TabIndex = 2;
			this->btnDecompress->Text = L"&Decompress";
			this->btnDecompress->UseVisualStyleBackColor = false;
			this->btnDecompress->Click += gcnew System::EventHandler(this, &Form1::btnDecompress_Click);
			// 
			// btnAddFile
			// 
			this->btnAddFile->BackColor = System::Drawing::Color::White;
			this->btnAddFile->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnAddFile->Location = System::Drawing::Point(471, 260);
			this->btnAddFile->Name = L"btnAddFile";
			this->btnAddFile->Size = System::Drawing::Size(100, 30);
			this->btnAddFile->TabIndex = 4;
			this->btnAddFile->Text = L"Add file";
			this->btnAddFile->UseVisualStyleBackColor = false;
			this->btnAddFile->Click += gcnew System::EventHandler(this, &Form1::btnAddFile_Click);
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->CheckBoxes = true;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->columnHeader1, this->columnHeader2, 
				this->columnHeader3, this->columnHeader4});
			this->listView1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listView1->GridLines = true;
			this->listView1->Location = System::Drawing::Point(16, 128);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(449, 195);
			this->listView1->TabIndex = 6;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"File Name";
			this->columnHeader1->Width = 141;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Path";
			this->columnHeader2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader2->Width = 130;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Size";
			this->columnHeader3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader3->Width = 87;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Rurred Size";
			this->columnHeader4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->columnHeader4->Width = 88;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Multiselect = true;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::Transparent;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->toolsToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(684, 24);
			this->menuStrip1->TabIndex = 7;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->addFileToolStripMenuItem, 
				this->deleteToolStripMenuItem, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// addFileToolStripMenuItem
			// 
			this->addFileToolStripMenuItem->Name = L"addFileToolStripMenuItem";
			this->addFileToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->addFileToolStripMenuItem->Text = L"Add File";
			this->addFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::addFileToolStripMenuItem_Click);
			// 
			// deleteToolStripMenuItem
			// 
			this->deleteToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->deleteAllToolStripMenuItem, 
				this->deleteSelectedToolStripMenuItem});
			this->deleteToolStripMenuItem->Name = L"deleteToolStripMenuItem";
			this->deleteToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->deleteToolStripMenuItem->Text = L"Delete File";
			// 
			// deleteAllToolStripMenuItem
			// 
			this->deleteAllToolStripMenuItem->Name = L"deleteAllToolStripMenuItem";
			this->deleteAllToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->deleteAllToolStripMenuItem->Text = L"Delete All";
			this->deleteAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deleteAllToolStripMenuItem_Click);
			// 
			// deleteSelectedToolStripMenuItem
			// 
			this->deleteSelectedToolStripMenuItem->Name = L"deleteSelectedToolStripMenuItem";
			this->deleteSelectedToolStripMenuItem->Size = System::Drawing::Size(154, 22);
			this->deleteSelectedToolStripMenuItem->Text = L"Delete Selected";
			this->deleteSelectedToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deleteSelectedToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// toolsToolStripMenuItem
			// 
			this->toolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->compressToolStripMenuItem, 
				this->decompressToolStripMenuItem});
			this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			this->toolsToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->toolsToolStripMenuItem->Text = L"Tools";
			// 
			// compressToolStripMenuItem
			// 
			this->compressToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->compressAllToolStripMenuItem, 
				this->compressSelectedToolStripMenuItem});
			this->compressToolStripMenuItem->Name = L"compressToolStripMenuItem";
			this->compressToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->compressToolStripMenuItem->Text = L"Compress";
			this->compressToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::compressToolStripMenuItem_Click);
			// 
			// compressAllToolStripMenuItem
			// 
			this->compressAllToolStripMenuItem->Name = L"compressAllToolStripMenuItem";
			this->compressAllToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->compressAllToolStripMenuItem->Text = L"Compress All";
			// 
			// compressSelectedToolStripMenuItem
			// 
			this->compressSelectedToolStripMenuItem->Name = L"compressSelectedToolStripMenuItem";
			this->compressSelectedToolStripMenuItem->Size = System::Drawing::Size(174, 22);
			this->compressSelectedToolStripMenuItem->Text = L"Compress Selected";
			// 
			// decompressToolStripMenuItem
			// 
			this->decompressToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->decompressAllToolStripMenuItem, 
				this->decompressSelectedToolStripMenuItem});
			this->decompressToolStripMenuItem->Name = L"decompressToolStripMenuItem";
			this->decompressToolStripMenuItem->Size = System::Drawing::Size(139, 22);
			this->decompressToolStripMenuItem->Text = L"Decompress";
			// 
			// decompressAllToolStripMenuItem
			// 
			this->decompressAllToolStripMenuItem->Name = L"decompressAllToolStripMenuItem";
			this->decompressAllToolStripMenuItem->Size = System::Drawing::Size(186, 22);
			this->decompressAllToolStripMenuItem->Text = L"Decompress All";
			// 
			// decompressSelectedToolStripMenuItem
			// 
			this->decompressSelectedToolStripMenuItem->Name = L"decompressSelectedToolStripMenuItem";
			this->decompressSelectedToolStripMenuItem->Size = System::Drawing::Size(186, 22);
			this->decompressSelectedToolStripMenuItem->Text = L"Decompress Selected";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->viewHelpToolStripMenuItem, 
				this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// viewHelpToolStripMenuItem
			// 
			this->viewHelpToolStripMenuItem->Name = L"viewHelpToolStripMenuItem";
			this->viewHelpToolStripMenuItem->Size = System::Drawing::Size(127, 22);
			this->viewHelpToolStripMenuItem->Text = L"View Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(127, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// btnDeleteFile
			// 
			this->btnDeleteFile->BackColor = System::Drawing::Color::White;
			this->btnDeleteFile->Font = (gcnew System::Drawing::Font(L"Century Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnDeleteFile->Location = System::Drawing::Point(471, 293);
			this->btnDeleteFile->Name = L"btnDeleteFile";
			this->btnDeleteFile->Size = System::Drawing::Size(100, 30);
			this->btnDeleteFile->TabIndex = 8;
			this->btnDeleteFile->Text = L"Delete File";
			this->btnDeleteFile->UseVisualStyleBackColor = false;
			this->btnDeleteFile->Click += gcnew System::EventHandler(this, &Form1::btnDeleteFile_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(684, 361);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->btnDeleteFile);
			this->Controls->Add(this->btnAddFile);
			this->Controls->Add(this->btnDecompress);
			this->Controls->Add(this->btnCompress);
			this->Controls->Add(this->picRurryTitle);
			this->Controls->Add(this->menuStrip1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(700, 400);
			this->MinimumSize = System::Drawing::Size(700, 400);
			this->Name = L"Form1";
			this->Text = L"R u r r y";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picRurryTitle))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		// VARIABLES //
		public :
			long long  _fileSize_;

#pragma endregion

	// Prosedur saat jendela terbuka - berisi keadaan awal
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			}


	/*****************************************************/
	/*					BUTTON PROCEDURE                 */
	/*****************************************************/
			 
	// Prosedur saat ADD FILE button di klik
	private: System::Void btnAddFile_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 //Menampilakan Open File Dialog
				 if (openFileDialog1->ShowDialog() ==  System::Windows::Forms::DialogResult::OK) {
					
					int iSize = listView1->Items->Count;
					int i = 0;
					
					//Memasukkan Nama file dan Path ke dalam list 
					for each (String ^ file in openFileDialog1->SafeFileNames) {

						ListViewItem ^ lItem = gcnew ListViewItem (file);
						lItem->SubItems->Add(openFileDialog1->FileNames[i]);
						
						//Menulis Nama File dan Path
						listView1->Items->Add(lItem);

						String^ t_file = openFileDialog1->FileNames[i];
						std::string _file =  msclr::interop::marshal_as<std::string>(t_file);
						int fileSize = getFileSize(_file); //Menghitung File Size
						
						_fileSize_ = fileSize;
						
						String^  _fileSize = System::Convert::ToString(fileSize);
						
						//Menulis File Size
						listView1->Items[iSize]->SubItems->Add(_fileSize + " Byte");

						i++;
						iSize++;
					}
				 }
			 }

	// Prosedur saat COMPRESS button di klik
	private: System::Void btnCompress_Click(System::Object^  sender, System::EventArgs^  e) {

				int n = listView1->Items->Count;
				
				if (n > 0) {
					
					if (n == 1){

						string fileName = msclr::interop::marshal_as<std::string>(listView1->Items[0]->SubItems[0]->Text);
						Rurring^ RurringCompress = gcnew Rurring();

						compressor RurryCompressor(fileName);
						MessageBox::Show("Rurring Complete!", "R u r r y");

						int fileSize = getFileSize(fileName + "_head_final.rur");
						String^  _fileSize = System::Convert::ToString(fileSize);
						listView1->Items[0]->SubItems->Add(_fileSize + " Byte");


					} else {
						//Array untuk menyimpan nama file
						string* tabFileName = new string[n];

						for (int i = 0; i < n; i++){
							string fileName = msclr::interop::marshal_as<std::string>(listView1->Items[i]->SubItems[0]->Text);
							tabFileName[i] = fileName;
						}

						Rurring^ RurringCompress = gcnew Rurring();		
					
						//Compressing file
						compressor RurryCompressor(n,tabFileName);

						RurringCompress->ShowDialog();
					
						int fileSize = getFileSize(tabFileName[0] + "_head_final.rur");
						String^  _fileSize = System::Convert::ToString(fileSize);
						listView1->Items[0]->SubItems->Add(_fileSize + " Byte");
					}
				} else {
					MessageBox::Show("You haven't add any file to be compressed yet.", "R u r r i n g  F a i l e d");
				}
			 }

	// Prosedur saat DECOMPRESS button di klik
	private: System::Void btnDecompress_Click(System::Object^  sender, System::EventArgs^  e) {
				 int n = listView1->Items->Count;
				
				if (n > 0) {
					
					if (n == 1){

						string fileName = msclr::interop::marshal_as<std::string>(listView1->Items[0]->SubItems[0]->Text);
						Rurring^ RurringCompress = gcnew Rurring();

						decompressor RurryDecompressor(fileName);
						MessageBox::Show("Rurring Complete!", "R u r r y");

					}
				} else {
					MessageBox::Show("You haven't add any file to be decompressed yet.", "R u r r i n g  F a i l e d");
				}
			 }


	//Prosedur saat DELETE button di klik
	private: System::Void btnDeleteFile_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Prosedur menghapus semua file yang di select (di centang)
				 deleteSelectedToolStripMenuItem_Click(sender,e);
			 }


	//Prosedur saat CLOSE button di klik
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 
				 //Menampilkan jendela pesan apakah pengguna benar-benar ingin keluar
				 if (MessageBox::Show("Do you really want to exit?", "R u r r y", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
					 Application::Exit(); //klik Yes -> keluar dari aplikasi
				 } else {
					 e->Cancel = true; // Klik No -> jendela pesan tertutup, kembali ke aplikasi
				 }
			}



	/*****************************************************/
	/*					MENU PROCEDURE                   */
	/*****************************************************/

	// Prosedur saat menu Help->About Menu di klik
	private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				MessageBox::Show("                          Rurry \n          [File Archiever Program] \n\n                 Copyright(C)2016 \n\n                    Developed by : \n             Richard - Umay - Reifi", "About Rurry");
			 }

	// Prosedur saat menu File->Add File Menu di klik
	private: System::Void addFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				btnAddFile_Click(sender,e);
			 }

	// Prosedur saat menu File->Exit Menu di klik
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Application::Exit();
			 }
	
	//Prosedur saat menu Tools -> Delete Selected di klik
	private: System::Void deleteSelectedToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Prosedur menghapus semua file yang di select (di centang)
				 for(int i = listView1->Items->Count; i>0; i--) {
					 if (listView1->Items[i-1]->Checked==true) {
						 listView1->Items->RemoveAt(i-1);
					 }
				 }
				 
			 }


	//Prosedur saat menu Tool -> Delete All di klik
	private: System::Void deleteAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Prosedur menghapus semua file pada list
				 for (int i = listView1->Items->Count; i>0; i--) {
					listView1->Items->Remove(listView1->Items[i-1]);
				 }
			 }


	private: System::Void compressToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 }




	/*****************************************************/
	/*					OTHER FUNCTION                   */
	/*****************************************************/

	//Menghitung File Size
	int getFileSize(std::string fileName){

				FILE *file = NULL;
				file = fopen(fileName.c_str(),"rb");

				fseek(file,0,SEEK_END);
				int size = ftell(file);
				 
				fclose(file);
				return size;
			}

	
	
	
};
}

#endif
