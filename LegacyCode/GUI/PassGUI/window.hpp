#include <wx/wx.h>
#include <wx/grid.h>

class Window : public wxFrame
{
    public:
        Window(const wxString& title);

        wxButton* btn1 = nullptr;
        wxButton* btn2 = nullptr;

        wxTextCtrl* tc = nullptr;
        //wxTextCtrl* tc2 = nullptr;

        wxGrid* tc2 = nullptr;

        // Event Functions
        void pressedExitBtn(wxCommandEvent& evt);
        void pressedSearchBtn(wxCommandEvent& evt);

        wxDECLARE_EVENT_TABLE();
};
