#include "alertdialog.h"

AlertDialog::AlertDialog( remembrancer_pi &_remembrancer_pi, wxWindow* parent)
    : AlertDialogBase( parent ), m_remembrancer_pi(m_remembrancer_pi)
{
    //ctor
}

AlertDialog::~AlertDialog()
{
    //dtor
}
