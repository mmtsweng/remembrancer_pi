#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include <dialogDefinitions.h>

class remembrancer_pi;

class PropertyDialog : public PropertyDialogBase
{
    public:
        PropertyDialog( remembrancer_pi &_remembrancer_pi, wxWindow* parent);
        virtual ~PropertyDialog();
    protected:
        remembrancer_pi &m_remembrancer_pi;
        void OnSave(wxCommandEvent &event);
		void OnCancel(wxCommandEvent &event);

    private:
};

#endif // PROPERTYDIALOG_H
