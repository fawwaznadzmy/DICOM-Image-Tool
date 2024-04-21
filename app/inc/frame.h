
#pragma once

#include <wx/wx.h>

class AppFrame : public wxFrame
{
public:
    AppFrame();

protected:
  wxPanel *panel_top;
 
private:
    void OnOpen(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};