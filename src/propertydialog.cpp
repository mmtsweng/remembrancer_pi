#include "propertydialog.h"

/*
    Constructor
*/
PropertyDialog::PropertyDialog( remembrancer_pi &_remembrancer_pi, wxWindow* parent)
    : PropertyDialogBase( parent ), m_remembrancer_pi(m_remembrancer_pi)
{
}


/*
    Destructor
*/
PropertyDialog::~PropertyDialog()
{
}

/*
    Cancel Button Pressed
*/
void PropertyDialog::OnCancel(wxCommandEvent &event)
{
    //m_remembrancer_pi.ResetToolbarIcon();
}

/*
    Save Button Pressed
*/
void PropertyDialog::OnSave(wxCommandEvent &event)
{
    //m_remembrancer_pi.SaveConfig();
    //m_remembrancer_pi.m_reminderDelaySeconds = this->m_txtDelay.GetValue();
    //m_remembrancer_pi.SaveConfig()
}
