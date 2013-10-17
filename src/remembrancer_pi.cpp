
#include "wx/wxprec.h"
#include "wx/timer.h"
#include "wx/fileconf.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/aui/aui.h>
#include "time.h"
#include "remembrancer_pi.h"
#include "dialogDefinitions.h"
#include "icons.h"

// the class factories, used to create and destroy instances of the PlugIn
extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new remembrancer_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//UI Elements
AlertDialog     *m_alertWindow;
PropertyDialog  *m_propertiesWindow;
wxWindow        *m_parent_window;
wxAuiManager    *m_AUImgr;
wxString         m_alertFileWav;
bool             m_alertPlaySound;

/*
    Constructor
        Initialize Images
*/
remembrancer_pi::remembrancer_pi(void *ppimgr)
    : opencpn_plugin_18(ppimgr)
{
    try
    {
        initialize_images();
    }
    catch(...)
    {
    }
}


/*
    Initialization
*/
int remembrancer_pi::Init(void)
{
    // Get a pointer to the opencpn display canvas, to use as a parent for windows created
    m_parent_window = GetOCPNCanvasWindow();

    // Get a reference to the OCPN Configuration object
    m_pconfig = GetOCPNConfigObject();

    // Create the Context Menu Items

    //    In order to avoid an ASSERT on msw debug builds,
    //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
    //    The Items will be re-parented when added to the real context meenu
    wxMenu dummy_menu;

    wxMenuItem *pmi = new wxMenuItem(&dummy_menu, -1, _("Show PlugIn DemoWindow"));
    m_show_id = AddCanvasContextMenuItem(pmi, this );
    SetCanvasContextMenuItemViz(m_show_id, true);

    wxMenuItem *pmih = new wxMenuItem(&dummy_menu, -1, _("Hide PlugIn DemoWindow"));
    m_hide_id = AddCanvasContextMenuItem(pmih, this );
    SetCanvasContextMenuItemViz(m_hide_id, false);

    //Set Default values - not configuration values
    m_alertWindow = NULL;
    m_propertiesWindow = NULL;
    m_activeRoute = false;

    LoadConfig();
    InitReminder();

    // This PlugIn needs a toolbar icon
    m_toolbar_item_id  = InsertPlugInTool(_T(""), _img_remembrancer_inactive, _img_remembrancer_inactive, wxITEM_CHECK,
        _("Remembrancer"), _T(""), NULL, REMEMBRANCER_TOOL_POSITION, 0, this);

    return (
        INSTALLS_CONTEXTMENU_ITEMS     |
        WANTS_PLUGIN_MESSAGING         |
        WANTS_PREFERENCES              |
        WANTS_CONFIG                   |
        WANTS_TOOLBAR_CALLBACK         |
        WANTS_OPENGL_OVERLAY_CALLBACK  |
        INSTALLS_TOOLBAR_TOOL          |
        INSTALLS_CONTEXTMENU_ITEMS
    );
}


/*
    DeInitialize the plugin
        Disconnect timer
*/
bool remembrancer_pi::DeInit(void)
{
    wxLogMessage(_T("REMEMBRANCER: DeInit"));
    m_AUImgr->DetachPane(m_alertWindow);
    m_AUImgr->DetachPane(m_propertiesWindow);
    if(m_alertWindow)
    {
        m_alertWindow->Close();
    }

    if (m_propertiesWindow)
    {
        m_propertiesWindow->Close();
    }

    m_timer.Stop();
    m_timer.Disconnect(wxEVT_TIMER, wxTimerEventHandler(remembrancer_pi::OnTimer), NULL, this);

    if (_img_remembrancer_active)
    {
        delete _img_remembrancer_active;
    }
    if (_img_remembrancer_inactive)
    {
        delete _img_remembrancer_inactive;
    }

    return true;
}


/*
    Timer Event
        Fires every X ms
        Check to see if we are actively following a route, and alert if so
*/
void remembrancer_pi::OnTimer(wxTimerEvent& event)
{
    //wxString msg;
    //msg.Printf(wxT("REMEMBRANCER: %.0f Seconds since Autopilot:"), secondsPassed);
    //wxLogMessage(msg);

    if (m_activeRoute && m_alertingEnabled)
    {
        wxLogMessage(_T("REMEMBRANCER: Alert fired"));

        if (!m_alertWindow)
        {
            m_alertWindow = new AlertDialog(*this, m_parent_window);
        }
        m_alertWindow->Show(true);
    }
}


/*
    JSON Message received handler
        - Listens for route activation and deactivation
*/
void remembrancer_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{
    //wxLogMessage(_T("REMEMBRANCER: JSON Message Received...\n") + message_body);
    if (message_id == _T("OCPN_RTE_ACTIVATED"))
    {
        wxLogMessage(_T("REMEMBRANCER: ACTIVATED"));
        m_activeRoute = true;
        SetToolbarToolBitmaps(m_toolbar_item_id, _img_remembrancer_active, _img_remembrancer_active);
    }

    if (message_id == _T("OCPN_RTE_DEACTIVATED"))
    {
        wxLogMessage(_T("REMEMBRANCER: DEACTIVATED"));
        m_activeRoute = false;
        SetToolbarToolBitmaps(m_toolbar_item_id, _img_remembrancer_inactive, _img_remembrancer_inactive);
    }
}


/*
    InitAutopilotStatus
        Make sure alerts don't show up until autopilot NMEA messages are parsed
        Start reminder-check timer
*/
void remembrancer_pi::InitReminder()
{

    if (m_timer.IsRunning())
    {
        m_timer.Stop();
        m_timer.Disconnect(wxEVT_TIMER, wxTimerEventHandler(remembrancer_pi::OnTimer), NULL, this);
    }

    //Start Timer
    wxString message;
    message.Printf(wxT("REMEMBRANCER: Starting Timer at %d seconds per alarm"), m_reminderDelaySeconds);
    wxLogMessage(message);

    m_timer.Connect(wxEVT_TIMER, wxTimerEventHandler(remembrancer_pi::OnTimer), NULL, this);
    m_timer.Start(m_reminderDelaySeconds * 1000);
}


/*
    Method to return the bitmap for the toolbar
*/
wxBitmap *remembrancer_pi::GetPlugInBitmap()
{
      return _img_remembrancer_inactive;
}


/*
    Show Preferences
*/
void remembrancer_pi::OnToolbarToolCallback(int id)
{
    wxLogMessage(_T("REMEMBRANCER: ToolbarCallback"));
    if (!m_propertiesWindow)
    {
        wxLogMessage(_T("REMEMBRANCER: Create Properties Window"));
        m_propertiesWindow = new PropertyDialog(*this, m_parent_window);
        m_propertiesWindow->m_txtDelay->SetValue(wxString::Format(_T("%d"), m_reminderDelaySeconds));
        m_propertiesWindow->m_fipSoundFile->SetPath(m_alertFileWav);
        m_propertiesWindow->m_ckEnabled->SetValue(m_alertingEnabled);
    }

    wxLogMessage(_T("REMEMBRANCER: Show Properties Window"));
    if (m_propertiesWindow->ShowModal() == wxID_OK)
    {
        wxLogMessage(_T("REMEMBRANCER: Get Properties Window Values"));
        m_alertFileWav = m_propertiesWindow->m_fipSoundFile->GetPath();
        m_alertingEnabled = m_propertiesWindow->m_ckEnabled->GetValue();
        m_reminderDelaySeconds = wxAtoi(m_propertiesWindow->m_txtDelay->GetValue());
        SaveConfig();
        m_propertiesWindow->Close();

        //Restart Timer with new settings
        InitReminder();
    }

    SetToolbarItemState(m_toolbar_item_id, false);
}


/*
    Load Configuration Settings
*/
bool remembrancer_pi::LoadConfig(void)
{
    wxFileConfig *pConf = m_pconfig;

    if(!pConf)
    {
        wxLogMessage(_T("REMEMBRANCER: No configuration"));
        return false;
    }

    pConf->SetPath ( _T( "/Settings/Remembrancer" ) );
    pConf->Read ( _T( "AlertingEnabled" ), &m_alertingEnabled, 1 );
    pConf->Read ( _T( "AlertingDelaySeconds" ), &m_reminderDelaySeconds, 60 );
    pConf->Read ( _T( "SoundFile" ), &m_alertFileWav, _T("") );

    return true;
}

bool remembrancer_pi::SaveConfig(void)
{
    wxFileConfig *pConf = m_pconfig;

    if(pConf)
    {
        wxLogMessage(_T("REMEMBRANCER: Writing Configuration"));
        pConf->SetPath ( _T ( "/Settings/Remembrancer" ) );
        pConf->Write ( _T ( "AlertingEnabled" ), m_alertingEnabled );
        pConf->Write ( _T ( "AlertingDelaySeconds" ), m_reminderDelaySeconds );
        pConf->Write ( _T ( "SoundFile" ), m_alertFileWav );

        //Automatically write changes
        pConf->Flush();

        return true;
    }
    else
    {
        wxLogMessage(_T("REMEMBRANCER: No configuration"));
        return false;
    }
}

void remembrancer_pi::ResetToolbarIcon()
{
    RequestRefresh(m_parent_window);
}


int remembrancer_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int remembrancer_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int remembrancer_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int remembrancer_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxString remembrancer_pi::GetCommonName()
{
      return _("Remembrancer");
}

wxString remembrancer_pi::GetShortDescription()
{
      return _("Remembrancer PlugIn for OpenCPN");
}

wxString remembrancer_pi::GetLongDescription()
{
      return _("Remembrancer PlugIn for OpenCPN\n\rPlugIn processing of NMEA messages and displaying an alert if the autopilot is engaged.");

}

void remembrancer_pi::OnContextMenuItemCallback(int id)
{
    wxLogMessage(_T("REMEMBRANCER: OnContextMenuCallBack()"));
    ::wxBell();

      //  Note carefully that this is a "reference to a wxAuiPaneInfo classs instance"
      //  Copy constructor (i.e. wxAuiPaneInfo pane = m_AUImgr->GetPane(m_pdemo_window);) will not work

    wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_alertWindow);
    if(!pane.IsOk())
        return;

    if(!pane.IsShown())
    {
        SetCanvasContextMenuItemViz(m_hide_id, true);
        SetCanvasContextMenuItemViz(m_show_id, false);

        pane.Show(true);
        m_AUImgr->Update();

    }
    else
    {
        SetCanvasContextMenuItemViz(m_hide_id, false);
        SetCanvasContextMenuItemViz(m_show_id, true);

        pane.Show(false);
        m_AUImgr->Update();
    }
}

void remembrancer_pi::UpdateAuiStatus(void)
{
      //    This method is called after the PlugIn is initialized
      //    and the frame has done its initial layout, possibly from a saved wxAuiManager "Perspective"
      //    It is a chance for the PlugIn to syncronize itself internally with the state of any Panes that
      //    were added to the frame in the PlugIn ctor.

      //    We use this callback here to keep the context menu selection in sync with the window state

    printf("REMEMBRANCER: UpdateAuiStatus");
    wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_alertWindow);
    if(!pane.IsOk())
        return;

    printf("update %d\n",pane.IsShown());

    SetCanvasContextMenuItemViz(m_hide_id, pane.IsShown());
    SetCanvasContextMenuItemViz(m_show_id, !pane.IsShown());

}

bool remembrancer_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    return false;
}

void remembrancer_pi::SetCursorLatLon(double lat, double lon)
{
}

bool remembrancer_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    return false;
}

int remembrancer_pi::GetToolbarToolCount(void)
{
    return 1;
}

void remembrancer_pi::ShowPreferencesDialog( wxWindow* parent )
{

}

void remembrancer_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
}
