
#include "wx/wxprec.h"
#include "wx/timer.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/aui/aui.h>
#include "remembrancer_pi.h"
#include "dialogDefinitions.h"

// the class factories, used to create and destroy instances of the PlugIn
extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return (opencpn_plugin *)new remembrancer_pi(ppimgr);
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

int remembrancer_pi::Init(void)
{
    printf("REMEMBRANCER: Init");

    // Get a pointer to the opencpn display canvas, to use as a parent for windows created
    m_parent_window = GetOCPNCanvasWindow();

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

    m_alertWindow = new AlertDialog(m_parent_window, wxID_ANY);

    m_AUImgr = GetFrameAuiManager();
    m_AUImgr->AddPane(m_alertWindow);
    m_AUImgr->GetPane(m_alertWindow).Name(_T("Alert!"));
    m_AUImgr->GetPane(m_alertWindow).Float();
    m_AUImgr->GetPane(m_alertWindow).CaptionVisible(true);
    m_AUImgr->GetPane(m_alertWindow).GripperTop(true);
    m_AUImgr->GetPane(m_alertWindow).CloseButton(true);
    m_AUImgr->GetPane(m_alertWindow).Show(false);
    m_AUImgr->Update();

    m_timer.Connect(wxEVT_TIMER, wxTimerEventHandler(remembrancer_pi::OnTimer), NULL, this);
    m_timer.Start(30000);


    return (
        INSTALLS_CONTEXTMENU_ITEMS     |
        WANTS_NMEA_SENTENCES           |
        USES_AUI_MANAGER
    );
}

///
bool remembrancer_pi::DeInit(void)
{
    printf("REMEMBRANCER: DeInit");
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
    return true;
}

void remembrancer_pi::OnTimer(wxTimerEvent& event)
{
    m_AUImgr->GetPane(m_alertWindow).Show(true);
    m_AUImgr->Update();
    wxMessageDialog mdlg(m_parent_window, _("ALARM!!!!"),_("Watchman"), wxOK | wxICON_ERROR);
    mdlg.ShowModal();
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
    printf("REMEMBRANCER: OnContextMenuItemCallback");
      wxLogMessage(_T("remembrancer_pi OnContextMenuCallBack()"));
     ::wxBell();

      //  Note carefully that this is a "reference to a wxAuiPaneInfo classs instance"
      //  Copy constructor (i.e. wxAuiPaneInfo pane = m_AUImgr->GetPane(m_pdemo_window);) will not work

      wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_alertWindow);
      if(!pane.IsOk())
            return;

      if(!pane.IsShown())
      {
//            printf("show\n");
            SetCanvasContextMenuItemViz(m_hide_id, true);
            SetCanvasContextMenuItemViz(m_show_id, false);

            pane.Show(true);
            m_AUImgr->Update();

      }
      else
      {
//            printf("hide\n");
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
  /*    if(m_pGribDialog && m_pGRIBOverlayFactory)
      {
            if(m_pGRIBOverlayFactory->IsReadyToRender())
            {
                  m_pGRIBOverlayFactory->RenderGribOverlay ( dc, vp );
                  return true;
            }
            else
                  return false;
      }
      else*/
            return false;
}
void remembrancer_pi::SetCursorLatLon(double lat, double lon)
{

}
bool remembrancer_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
   /*   if(m_pGribDialog && m_pGRIBOverlayFactory)
      {
            if(m_pGRIBOverlayFactory->IsReadyToRender())
            {
                  m_pGRIBOverlayFactory->RenderGLGribOverlay ( pcontext, vp );
                  return true;
            }
            else
                  return false;
      }
      else*/
            return false;

}
int remembrancer_pi::GetToolbarToolCount(void)
{
      return 1;
}
void remembrancer_pi::ShowPreferencesDialog( wxWindow* parent )
{

}
void remembrancer_pi::OnToolbarToolCallback(int id)
{

}
void remembrancer_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{

}
void remembrancer_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{

}
