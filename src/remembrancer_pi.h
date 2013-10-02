
#ifndef _DEMOPI_H_
#define _DEMOPI_H_

#include "wx/wxprec.h"
#include "wx/timer.h"

#ifndef  WX_PRECOMP
    #include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    1

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    8

#include "time.h"
#include "../include/opencpn/ocpn_plugin.h"
#include "../include/nmea0183/nmea0183.h"
#include "dialogDefinitions.h"

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------
class remembrancer_pi : public opencpn_plugin_18, wxEvtHandler
{
public:
    enum Alarm
    {ALERT_TIMER=1};

    remembrancer_pi(void *ppimgr):opencpn_plugin_18(ppimgr){}

    //    The required PlugIn Methods
    int Init(void);
    bool DeInit(void);

    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();

    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();

    //    The optional method overrides
    void SetNMEASentence(wxString &sentence);
    void OnContextMenuItemCallback(int id);
    void UpdateAuiStatus(void);
    void OnTimer(wxTimerEvent& event);

    //    The override PlugIn Methods
    bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
    void SetCursorLatLon(double lat, double lon);
    bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
    int GetToolbarToolCount(void);
    void ShowPreferencesDialog( wxWindow* parent );
    void OnToolbarToolCallback(int id);
    void SetPluginMessage(wxString &message_id, wxString &message_body);
    void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);


private:
    //Private Methods
    double SecondsSinceAutopilotUpdate();

    // UI Windows
    PropertyDialog  *m_propertiesWindow;
    AlertDialog     *m_alertWindow;
    NMEA0183         m_NMEA;
    wxTimer          m_timer;
    time_t           m_lastAutopilotFix;

    wxWindow        *m_parent_window;
    wxAuiManager    *m_AUImgr;
    int              m_show_id;
    int              m_hide_id;
};
#endif



