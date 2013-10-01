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
	m_staticNotification->Wrap( -1 );
	fgSizerPanel->Add( m_staticNotification, 0, wxALL, 5 );
	
	wxBoxSizer* bSizerButton;
	bSizerButton = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonCloseAlert = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCloseAlert->SetDefault(); 
	bSizerButton->Add( m_buttonCloseAlert, 0, wxALL, 5 );
	
	m_buttonStopAlerting = new wxButton( this, wxID_ANY, wxT("Stop Alerting"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButton->Add( m_buttonStopAlerting, 0, wxALL, 5 );
	
	
	fgSizerPanel->Add( bSizerButton, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizerPanel );
	this->Layout();
	fgSizerPanel->Fit( this );
	
	this->Centre( wxBOTH );
}

AlertDialog::~AlertDialog()
{
}

PropertyDialog::PropertyDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_ckEnabled = new wxCheckBox( this, wxID_ANY, wxT("Enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ckEnabled->SetValue(true); 
	bSizer2->Add( m_ckEnabled, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblSoundFile = new wxStaticText( this, wxID_ANY, wxT("Sound File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblSoundFile->Wrap( -1 );
	bSizer3->Add( m_lblSoundFile, 0, wxALL, 5 );
	
	m_fipSoundFile = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.wav"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer3->Add( m_fipSoundFile, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_lblNMEASentance = new wxStaticText( this, wxID_ANY, wxT("NMEA Sentance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblNMEASentance->Wrap( -1 );
	bSizer5->Add( m_lblNMEASentance, 0, wxALL, 5 );
	
	wxString m_cboNMEAChoices[] = { wxT("$ECAPB"), wxT("$ECRMB"), wxT("$ECRMC") };
	int m_cboNMEANChoices = sizeof( m_cboNMEAChoices ) / sizeof( wxString );
	m_cboNMEA = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cboNMEANChoices, m_cboNMEAChoices, 0 );
	m_cboNMEA->SetSelection( 0 );
	bSizer5->Add( m_cboNMEA, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

PropertyDialog::~PropertyDialog()
{
}
