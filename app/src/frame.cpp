

#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <opencv2/opencv.hpp>

#include "frame.h"

using namespace cv;

enum
{
    ID_Open = 1
};
 
AppFrame::AppFrame()
    : wxFrame(nullptr, wxID_ANY, "DICOM Image Processing Tool", wxDefaultPosition, wxDefaultSize)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Open, "&Open\tCtrl-O",
                     "Help string shown in status bar for this menu item");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
   //Create Panel
    panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_top->SetBackgroundColour(wxColor(100, 100, 200));

    wxPanel *panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_bottom->SetBackgroundColour(wxColor(100, 200, 100));

    wxPanel *panel_bottom_right = new wxPanel(panel_bottom, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_bottom_right->SetBackgroundColour(wxColor(200, 200, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel_top, 2, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 0);
  

    wxBoxSizer *sizer_bottom = new wxBoxSizer(wxHORIZONTAL);
    sizer_bottom->Add(panel_bottom, 1, wxEXPAND | wxRIGHT, 10);

    sizer->Add(sizer_bottom, 1, wxEXPAND | wxALL, 10);

    this->SetSizerAndFit(sizer);


    CreateStatusBar();
   // SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &AppFrame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &AppFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AppFrame::OnExit, this, wxID_EXIT);
}
 
void AppFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void AppFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void AppFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
                       "DICOM files (*.dcm)|*.dcm|PNG files (*.png)|*.png|JPEG files (*.jpeg)|*.png|TIF files (*.tif)|*.tif", 
                       wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...
    
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(openFileDialog.GetPath());

    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    wxString fileName = openFileDialog.GetPath();
    const char* fileNameChar = fileName.mb_str();

    Mat image = imread(fileNameChar);
    if ( !image.data )
    {
        printf("No image data \n");
    }

    imshow("Display Image", image);
    
   // wxLogMessage("Hello world from wxWidgets!");
}