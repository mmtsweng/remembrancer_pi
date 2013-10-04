#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <dialogDefinitions.h>

class remembrancer_pi;

class AlertDialog : public AlertDialogBase
{
    public:
        AlertDialog( remembrancer_pi &_remembrancer_pi, wxWindow* parent);
        virtual ~AlertDialog();
    protected:
        remembrancer_pi &m_remembrancer_pi;
        //void OnClose(wxCommandEvent &event);
    private:
};

#endif // ALERTDIALOG_H
