#include "remembrancer_pi.h"
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
    this->Close();
}

/*
    Save Button Pressed
*/
void PropertyDialog::OnSave(wxCommandEvent &event)
{
}
