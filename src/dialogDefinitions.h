///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __DIALOGDEFINITIONS_H__
#define __DIALOGDEFINITIONS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_Cancel 1000

///////////////////////////////////////////////////////////////////////////////
/// Class AlertDialogBase
///////////////////////////////////////////////////////////////////////////////
class AlertDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticNotification;
		wxButton* m_buttonCloseAlert;
		wxButton* m_btnOptions;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnProperties( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AlertDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Alert"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~AlertDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PropertyDialogBase
///////////////////////////////////////////////////////////////////////////////
class PropertyDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_lblDelay;
		wxTextCtrl* m_txtDelay;
		wxCheckBox* m_ckEnabled;
		wxStaticText* m_lblSoundFile;
		wxFilePickerCtrl* m_fipSoundFile;
		wxButton* m_btnSave;
		wxButton* m_btnCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PropertyDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,220 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~PropertyDialogBase();
	
};

#endif //__DIALOGDEFINITIONS_H__
