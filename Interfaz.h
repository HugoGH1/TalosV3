#pragma once

namespace TalosV3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Interfaz
	/// </summary>
	public ref class Interfaz : public System::Windows::Forms::Form
	{
	public:
		static Interfaz^ fmg;

	private:
		void Analiza(TalosV3::Interfaz^ form);

	public:
		void AnalizadorSintactico(TalosV3::Interfaz^ form);
	public:
		Interfaz(void)
		{
			InitializeComponent();
			fmg = this;
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Interfaz()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tlpGral;
	private: System::Windows::Forms::TableLayoutPanel^ tplCodigo;
	private: System::Windows::Forms::TableLayoutPanel^ tlpBotones;
	protected:



	private: System::Windows::Forms::TableLayoutPanel^ tlpLateral;
	public: System::Windows::Forms::RichTextBox^ CodeSpace;
	private:
	public: System::Windows::Forms::Button^ btnAbrir;
	public: System::Windows::Forms::Button^ btnLimpiar;
	public: System::Windows::Forms::Button^ btnGuardar;
	public: System::Windows::Forms::Button^ btnAnalizar;
	public: System::Windows::Forms::Button^ btnSalir;

	public: System::Windows::Forms::RichTextBox^ SintaxisSpace;

	private: System::Windows::Forms::TableLayoutPanel^ tplToken;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::RichTextBox^ TokenSpace;
	private: System::Windows::Forms::Label^ lblLexemas;
	private: System::Windows::Forms::Label^ lblToken;
	private: System::Windows::Forms::TableLayoutPanel^ tplError;
	private: System::Windows::Forms::RichTextBox^ ErrorsSpaces;

	private: System::Windows::Forms::Label^ label1;


	public:

	public:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tlpGral = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tplCodigo = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tlpBotones = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->btnAbrir = (gcnew System::Windows::Forms::Button());
			this->btnLimpiar = (gcnew System::Windows::Forms::Button());
			this->btnGuardar = (gcnew System::Windows::Forms::Button());
			this->btnAnalizar = (gcnew System::Windows::Forms::Button());
			this->btnSalir = (gcnew System::Windows::Forms::Button());
			this->CodeSpace = (gcnew System::Windows::Forms::RichTextBox());
			this->tlpLateral = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SintaxisSpace = (gcnew System::Windows::Forms::RichTextBox());
			this->tplToken = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->TokenSpace = (gcnew System::Windows::Forms::RichTextBox());
			this->lblLexemas = (gcnew System::Windows::Forms::Label());
			this->lblToken = (gcnew System::Windows::Forms::Label());
			this->tplError = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->ErrorsSpaces = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tlpGral->SuspendLayout();
			this->tplCodigo->SuspendLayout();
			this->tlpBotones->SuspendLayout();
			this->tlpLateral->SuspendLayout();
			this->tplToken->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tplError->SuspendLayout();
			this->SuspendLayout();
			// 
			// tlpGral
			// 
			this->tlpGral->ColumnCount = 5;
			this->tlpGral->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 15)));
			this->tlpGral->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tlpGral->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 19)));
			this->tlpGral->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 601)));
			this->tlpGral->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 15)));
			this->tlpGral->Controls->Add(this->tplCodigo, 1, 1);
			this->tlpGral->Controls->Add(this->tlpLateral, 3, 1);
			this->tlpGral->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tlpGral->Location = System::Drawing::Point(0, 0);
			this->tlpGral->Name = L"tlpGral";
			this->tlpGral->RowCount = 3;
			this->tlpGral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 11)));
			this->tlpGral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tlpGral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 10)));
			this->tlpGral->Size = System::Drawing::Size(1692, 933);
			this->tlpGral->TabIndex = 0;
			// 
			// tplCodigo
			// 
			this->tplCodigo->ColumnCount = 1;
			this->tplCodigo->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tplCodigo->Controls->Add(this->tlpBotones, 0, 1);
			this->tplCodigo->Controls->Add(this->CodeSpace, 0, 0);
			this->tplCodigo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tplCodigo->Location = System::Drawing::Point(18, 14);
			this->tplCodigo->Name = L"tplCodigo";
			this->tplCodigo->RowCount = 2;
			this->tplCodigo->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 94.45676F)));
			this->tplCodigo->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 5.543238F)));
			this->tplCodigo->Size = System::Drawing::Size(1036, 906);
			this->tplCodigo->TabIndex = 0;
			// 
			// tlpBotones
			// 
			this->tlpBotones->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(46)));
			this->tlpBotones->ColumnCount = 12;
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 7.272727F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 13.63636F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 0.9090909F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 13.63636F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 0.9090909F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 18.18182F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 0.9090909F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 22.72727F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 0.9090909F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 13.63636F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 3.636364F)));
			this->tlpBotones->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 3.636364F)));
			this->tlpBotones->Controls->Add(this->btnAbrir, 1, 1);
			this->tlpBotones->Controls->Add(this->btnLimpiar, 3, 1);
			this->tlpBotones->Controls->Add(this->btnGuardar, 5, 1);
			this->tlpBotones->Controls->Add(this->btnAnalizar, 7, 1);
			this->tlpBotones->Controls->Add(this->btnSalir, 9, 1);
			this->tlpBotones->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tlpBotones->Location = System::Drawing::Point(3, 858);
			this->tlpBotones->Name = L"tlpBotones";
			this->tlpBotones->RowCount = 2;
			this->tlpBotones->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 10)));
			this->tlpBotones->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tlpBotones->Size = System::Drawing::Size(1030, 45);
			this->tlpBotones->TabIndex = 0;
			// 
			// btnAbrir
			// 
			this->btnAbrir->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->btnAbrir->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnAbrir->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnAbrir->Font = (gcnew System::Drawing::Font(L"Quicksand", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAbrir->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->btnAbrir->Location = System::Drawing::Point(77, 13);
			this->btnAbrir->Name = L"btnAbrir";
			this->btnAbrir->Size = System::Drawing::Size(134, 29);
			this->btnAbrir->TabIndex = 0;
			this->btnAbrir->TabStop = false;
			this->btnAbrir->Text = L"ABRIR";
			this->btnAbrir->UseVisualStyleBackColor = false;
			this->btnAbrir->Click += gcnew System::EventHandler(this, &Interfaz::btnAbrir_Click);
			// 
			// btnLimpiar
			// 
			this->btnLimpiar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->btnLimpiar->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnLimpiar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnLimpiar->Font = (gcnew System::Drawing::Font(L"Quicksand", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLimpiar->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->btnLimpiar->Location = System::Drawing::Point(226, 13);
			this->btnLimpiar->Name = L"btnLimpiar";
			this->btnLimpiar->Size = System::Drawing::Size(134, 29);
			this->btnLimpiar->TabIndex = 1;
			this->btnLimpiar->TabStop = false;
			this->btnLimpiar->Text = L"LIMPIAR";
			this->btnLimpiar->UseVisualStyleBackColor = false;
			this->btnLimpiar->Click += gcnew System::EventHandler(this, &Interfaz::btnLimpiar_Click);
			// 
			// btnGuardar
			// 
			this->btnGuardar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->btnGuardar->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnGuardar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnGuardar->Font = (gcnew System::Drawing::Font(L"Quicksand", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnGuardar->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->btnGuardar->Location = System::Drawing::Point(375, 13);
			this->btnGuardar->Name = L"btnGuardar";
			this->btnGuardar->Size = System::Drawing::Size(181, 29);
			this->btnGuardar->TabIndex = 2;
			this->btnGuardar->TabStop = false;
			this->btnGuardar->Text = L"GUARDAR";
			this->btnGuardar->UseVisualStyleBackColor = false;
			this->btnGuardar->Click += gcnew System::EventHandler(this, &Interfaz::btnGuardar_Click);
			// 
			// btnAnalizar
			// 
			this->btnAnalizar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->btnAnalizar->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnAnalizar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnAnalizar->Font = (gcnew System::Drawing::Font(L"Quicksand", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAnalizar->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->btnAnalizar->Location = System::Drawing::Point(571, 13);
			this->btnAnalizar->Name = L"btnAnalizar";
			this->btnAnalizar->Size = System::Drawing::Size(228, 29);
			this->btnAnalizar->TabIndex = 3;
			this->btnAnalizar->TabStop = false;
			this->btnAnalizar->Text = L"ANALIZAR";
			this->btnAnalizar->UseVisualStyleBackColor = false;
			this->btnAnalizar->Click += gcnew System::EventHandler(this, &Interfaz::btnAnalizar_Click);
			// 
			// btnSalir
			// 
			this->btnSalir->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(43)));
			this->btnSalir->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnSalir->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSalir->Font = (gcnew System::Drawing::Font(L"Quicksand", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSalir->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->btnSalir->Location = System::Drawing::Point(814, 13);
			this->btnSalir->Name = L"btnSalir";
			this->btnSalir->Size = System::Drawing::Size(134, 29);
			this->btnSalir->TabIndex = 4;
			this->btnSalir->TabStop = false;
			this->btnSalir->Text = L"SALIR";
			this->btnSalir->UseVisualStyleBackColor = false;
			this->btnSalir->Click += gcnew System::EventHandler(this, &Interfaz::btnSalir_Click);
			// 
			// CodeSpace
			// 
			this->CodeSpace->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(39)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->CodeSpace->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->CodeSpace->Dock = System::Windows::Forms::DockStyle::Fill;
			this->CodeSpace->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CodeSpace->ForeColor = System::Drawing::Color::Yellow;
			this->CodeSpace->Location = System::Drawing::Point(3, 3);
			this->CodeSpace->Name = L"CodeSpace";
			this->CodeSpace->Size = System::Drawing::Size(1030, 849);
			this->CodeSpace->TabIndex = 1;
			this->CodeSpace->Text = L"";
			// 
			// tlpLateral
			// 
			this->tlpLateral->ColumnCount = 1;
			this->tlpLateral->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tlpLateral->Controls->Add(this->SintaxisSpace, 0, 2);
			this->tlpLateral->Controls->Add(this->tplToken, 0, 0);
			this->tlpLateral->Controls->Add(this->tplError, 0, 4);
			this->tlpLateral->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tlpLateral->Location = System::Drawing::Point(1079, 14);
			this->tlpLateral->Name = L"tlpLateral";
			this->tlpLateral->RowCount = 5;
			this->tlpLateral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 32.63708F)));
			this->tlpLateral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 1.044386F)));
			this->tlpLateral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 32.63708F)));
			this->tlpLateral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 1.044386F)));
			this->tlpLateral->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 32.63708F)));
			this->tlpLateral->Size = System::Drawing::Size(595, 906);
			this->tlpLateral->TabIndex = 1;
			// 
			// SintaxisSpace
			// 
			this->SintaxisSpace->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(39)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->SintaxisSpace->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->SintaxisSpace->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SintaxisSpace->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SintaxisSpace->ForeColor = System::Drawing::Color::OrangeRed;
			this->SintaxisSpace->Location = System::Drawing::Point(3, 307);
			this->SintaxisSpace->Name = L"SintaxisSpace";
			this->SintaxisSpace->ReadOnly = true;
			this->SintaxisSpace->Size = System::Drawing::Size(589, 289);
			this->SintaxisSpace->TabIndex = 1;
			this->SintaxisSpace->TabStop = false;
			this->SintaxisSpace->Text = L"";
			// 
			// tplToken
			// 
			this->tplToken->ColumnCount = 1;
			this->tplToken->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tplToken->Controls->Add(this->tableLayoutPanel1, 0, 0);
			this->tplToken->Controls->Add(this->TokenSpace, 0, 1);
			this->tplToken->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tplToken->Location = System::Drawing::Point(3, 3);
			this->tplToken->Name = L"tplToken";
			this->tplToken->RowCount = 2;
			this->tplToken->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tplToken->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 90)));
			this->tplToken->Size = System::Drawing::Size(589, 289);
			this->tplToken->TabIndex = 3;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->lblLexemas, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblToken, 1, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(583, 22);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// TokenSpace
			// 
			this->TokenSpace->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(39)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->TokenSpace->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TokenSpace->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TokenSpace->Font = (gcnew System::Drawing::Font(L"Consolas", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TokenSpace->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(125)),
				static_cast<System::Int32>(static_cast<System::Byte>(218)));
			this->TokenSpace->Location = System::Drawing::Point(0, 28);
			this->TokenSpace->Margin = System::Windows::Forms::Padding(0);
			this->TokenSpace->Name = L"TokenSpace";
			this->TokenSpace->ReadOnly = true;
			this->TokenSpace->Size = System::Drawing::Size(589, 261);
			this->TokenSpace->TabIndex = 1;
			this->TokenSpace->TabStop = false;
			this->TokenSpace->Text = L"";
			// 
			// lblLexemas
			// 
			this->lblLexemas->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(46)));
			this->lblLexemas->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblLexemas->Font = (gcnew System::Drawing::Font(L"Quicksand", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLexemas->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->lblLexemas->Location = System::Drawing::Point(3, 0);
			this->lblLexemas->Name = L"lblLexemas";
			this->lblLexemas->Size = System::Drawing::Size(285, 22);
			this->lblLexemas->TabIndex = 0;
			this->lblLexemas->Text = L"Lexema";
			this->lblLexemas->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblToken
			// 
			this->lblToken->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(46)));
			this->lblToken->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblToken->Font = (gcnew System::Drawing::Font(L"Quicksand", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblToken->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->lblToken->Location = System::Drawing::Point(294, 0);
			this->lblToken->Name = L"lblToken";
			this->lblToken->Size = System::Drawing::Size(286, 22);
			this->lblToken->TabIndex = 1;
			this->lblToken->Text = L"Token";
			this->lblToken->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tplError
			// 
			this->tplError->ColumnCount = 1;
			this->tplError->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tplError->Controls->Add(this->ErrorsSpaces, 0, 1);
			this->tplError->Controls->Add(this->label1, 0, 0);
			this->tplError->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tplError->Location = System::Drawing::Point(3, 611);
			this->tplError->Name = L"tplError";
			this->tplError->RowCount = 2;
			this->tplError->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 10)));
			this->tplError->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 90)));
			this->tplError->Size = System::Drawing::Size(589, 292);
			this->tplError->TabIndex = 4;
			// 
			// ErrorsSpaces
			// 
			this->ErrorsSpaces->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(39)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->ErrorsSpaces->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->ErrorsSpaces->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ErrorsSpaces->Font = (gcnew System::Drawing::Font(L"Consolas", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ErrorsSpaces->ForeColor = System::Drawing::Color::Red;
			this->ErrorsSpaces->Location = System::Drawing::Point(3, 32);
			this->ErrorsSpaces->Name = L"ErrorsSpaces";
			this->ErrorsSpaces->ReadOnly = true;
			this->ErrorsSpaces->Size = System::Drawing::Size(583, 257);
			this->ErrorsSpaces->TabIndex = 0;
			this->ErrorsSpaces->TabStop = false;
			this->ErrorsSpaces->Text = L"";
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(46)));
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Font = (gcnew System::Drawing::Font(L"Quicksand", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(175)), static_cast<System::Int32>(static_cast<System::Byte>(179)),
				static_cast<System::Int32>(static_cast<System::Byte>(183)));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(583, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Errores";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// Interfaz
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(46)));
			this->ClientSize = System::Drawing::Size(1692, 933);
			this->Controls->Add(this->tlpGral);
			this->MinimumSize = System::Drawing::Size(855, 488);
			this->Name = L"Interfaz";
			this->Text = L"Analizador Léxico";
			this->tlpGral->ResumeLayout(false);
			this->tplCodigo->ResumeLayout(false);
			this->tlpBotones->ResumeLayout(false);
			this->tlpLateral->ResumeLayout(false);
			this->tplToken->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tplError->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnAbrir_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Text files(*.tls)|*.tls|All files(*.*)|*.*";
		openFileDialog->Title = "Select a file";
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				String^ rutaArchivo = openFileDialog->FileName;
				CodeSpace->Text = System::IO::File::ReadAllText(rutaArchivo);
			}
			catch (System::Exception^ ex) {
				MessageBox::Show("Error al leer el archivo:\n" + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	private: System::Void btnGuardar_Click(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "Text files(*.tls)|*.tls|All files(*.*)|*.*";
		saveFileDialog->Title = "Guardar archivo";

		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ rutaArchivo = saveFileDialog->FileName;
			System::IO::File::WriteAllText(rutaArchivo, CodeSpace->Text);
		}
	}
	private: System::Void btnAnalizar_Click(System::Object^ sender, System::EventArgs^ e) {

		try {
			//Analiza(this);
			AnalizadorSintactico(this);
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Interfaz trabada: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	};
	private: System::Void btnLimpiar_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult respuesta = System::Windows::Forms::MessageBox::Show("¿Estás seguro de que deseas limpiar el código?", "Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

		if (respuesta == System::Windows::Forms::DialogResult::Yes) {
			CodeSpace->Clear();
			TokenSpace->Clear();
			SintaxisSpace->Clear();
			ErrorsSpaces->Clear();
		}
		else {
			MessageBox::Show("Acción cancelada", "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	private: System::Void btnSalir_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult respuesta = System::Windows::Forms::MessageBox::Show("¿Estás seguro de que deseas salir?", "Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (respuesta == System::Windows::Forms::DialogResult::Yes) {
			Application::Exit();
		}
		else {
			MessageBox::Show("Acción cancelada", "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	};
}