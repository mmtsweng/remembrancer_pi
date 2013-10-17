
#ifndef _DEMOPI_H_
#define _DEMOPI_H_

#include "wx/wxprec.h"
#include "wx/timer.h"

#ifndef  WX_PRECOMP
    #include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    6

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    8

#define     REMEMBRANCER_TOOL_POSITION    -1          // Request default positioning of toolbar tool

#include "time.h"
#include "../include/opencpn/ocpn_plugin.h"
#include "../include/nmea0183/nmea0183.h"
#include "alertdialog.h"
#include "propertydialog.h"

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------
class remembrancer_pi : public opencpn_plugin_18, wxEvtHandler
{
public:
    enum Alarm
    {ALERT_TIMER=1};
    remembrancer_pi(void* ppimgr);

    //    The required PlugIn Methods
    int Init(void);
    bool DeInit(void);

    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();

    wxBitmap *GetPlugInBitmap();
    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();

    //    The optional method overrides
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
    bool LoadConfig(void);
    bool SaveConfig(void);


private:
    //Private Methods
    void InitReminder();
    void ResetToolbarIcon();

    // UI Windows
    PropertyDialog   *m_propertiesWindow;
    AlertDialog      *m_alertWindow;
    wxTimer          m_timer;
    int              m_reminderDelaySeconds;
    wxString         m_alertFileWav;
    bool             m_alertPlaySound;
    bool             m_alertingEnabled;
    bool             m_activeRoute;

    wxWindow         *m_parent_window;
    wxAuiManager     *m_AUImgr;
    wxFileConfig     *m_pconfig;
    int              m_show_id;
    int              m_hide_id;
    int              m_toolbar_item_id;

};
#endif



