#include <wx/wx.h>
#include <wx/wxapp.h>

class MovieTagApp : public wxApp {
public:
    virtual bool OnInit() override {
        // Create the main window
        wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "AttackPS1", wxDefaultPosition, wxSize(800, 600));

        // Set the frame icon
        frame->SetIcon(wxIcon(".ico"));

        // Show the frame
        frame->Show(true);

        return true;
    }
};
