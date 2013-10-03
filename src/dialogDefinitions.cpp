///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialogDefinitions.h"

///////////////////////////////////////////////////////////////////////////

AlertDialog::AlertDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizerPanel;
	fgSizerPanel = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizerPanel->AddGrowableCol( 2 );
	fgSizerPanel->SetFlexibleDirection( wxBOTH );
	fgSizerPanel->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizerPanel->SetMinSize( wxSize( 0,0 ) ); 
	m_staticNotification = new wxStaticText( this, wxID_ANY, wxT("This is an alert  to remind you to do a safety sweep and make sure the vessel is traveling as expected."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticNotification->Wrap( 200 );
	fgSizerPanel->Add( m_staticNotification, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonCloseAlert = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCloseAlert->SetDefault(); 
	bSizerButton->Add( m_buttonCloseAlert, 0, wxALL, 5 );
	
	m_btnOptions = new wxButton( this, wxID_ANY, wxT("Options"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_btnOptions, 0, wxALL, 5 );
	
	
	fgSizerPanel->Add( bSizerButton, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizerPanel );
	this->Layout();
	fgSizerPanel->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonCloseAlert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AlertDialog::OnClose ), NULL, this );
	m_btnOptions->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AlertDialog::OnProperties ), NULL, this );
}

AlertDialog::~AlertDialog()
{
	// Disconnect Events
	m_buttonCloseAlert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AlertDialog::OnClose ), NULL, this );
	m_btnOptions->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AlertDialog::OnProperties ), NULL, this );
	
}

PropertyDialog::PropertyDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblDelay = new wxStaticText( this, wxID_ANY, wxT("Delay (Seconds)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblDelay->Wrap( -1 );
	bSizer6->Add( m_lblDelay, 0, wxALL, 5 );
	
	m_txtDelay = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_txtDelay, 0, wxALL, 5 );
	
	
	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );
	
	m_ckEnabled = new wxCheckBox( this, wxID_ANY, wxT("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ckEnabled->SetValue(true); 
	bSizer5->Add( m_ckEnabled, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblSoundFile = new wxStaticText( this, wxID_ANY, wxT("Sound File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblSoundFile->Wrap( -1 );
	bSizer3->Add( m_lblSoundFile, 0, wxALL, 5 );
	
	m_fipSoundFile = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.wav"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer3->Add( m_fipSoundFile, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_btnCancel, 0, wxALL, 5 );
	
	m_btnOk = new wxButton( this, wxID_ANY, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_btnOk, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer7, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::OnCancel ), NULL, this );
	m_btnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::OnOK ), NULL, this );
}

PropertyDialog::~PropertyDialog()
{
	// Disconnect Events
	m_btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::OnCancel ), NULL, this );
	m_btnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PropertyDialog::OnOK ), NULL, this );
	
}
