#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/filedlg.h>
#include <FFmpeg/ffmpeg.h>
#include <iostream>
#include <string>

class VideoTagEditorFrame : public wxFrame {
public:
    VideoTagEditorFrame(const wxString& title);

private:
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void ExtractMetadata(const std::string& filePath);
    void UpdateMetadata(const std::string& filePath);

    wxTextCtrl* titleTextCtrl;
    wxTextCtrl* genreTextCtrl;
    wxTextCtrl* descriptionTextCtrl;

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(VideoTagEditorFrame, wxFrame)
    EVT_MENU(wxID_OPEN, VideoTagEditorFrame::OnOpen)
    EVT_MENU(wxID_SAVE, VideoTagEditorFrame::OnSave)
wxEND_EVENT_TABLE()

class VideoTagEditorApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(VideoTagEditorApp);

bool VideoTagEditorApp::OnInit() {
    VideoTagEditorFrame* frame = new VideoTagEditorFrame("Video Tag Editor");
    frame->Show(true);
    return true;
}

VideoTagEditorFrame::VideoTagEditorFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_OPEN, "&Open\tCtrl-O");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl-S");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X");
    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    titleTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, 30));
    genreTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, 30));
    descriptionTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, 100), wxTE_MULTILINE);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Title"), 0, wxALL | wxALIGN_LEFT, 5);
    mainSizer->Add(titleTextCtrl, 0, wxALL, 5);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Genre"), 0, wxALL | wxALIGN_LEFT, 5);
    mainSizer->Add(genreTextCtrl, 0, wxALL, 5);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Description"), 0, wxALL | wxALIGN_LEFT, 5);
    mainSizer->Add(descriptionTextCtrl, 0, wxALL, 5);

    SetSizer(mainSizer);
}

void VideoTagEditorFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Open Video File", "", "", "Video Files (*.mp4;*.mkv;*.avi)|*.mp4;*.mkv;*.avi", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    std::string filePath = openFileDialog.GetPath().ToStdString();
    
    ExtractMetadata(filePath);
}

void VideoTagEditorFrame::OnSave(wxCommandEvent& event) {
    // Save the metadata
    wxString title = titleTextCtrl->GetValue();
    wxString genre = genreTextCtrl->GetValue();
    wxString description = descriptionTextCtrl->GetValue();

    std::cout << "Saving metadata:\nTitle: " << title.ToStdString() << "\nGenre: " << genre.ToStdString() << "\nDescription: " << description.ToStdString() << std::endl;
    
    // Save metadata using FFmpeg or other libraries (not implemented here)
    // UpdateMetadata(filePath);
}

void VideoTagEditorFrame::ExtractMetadata(const std::string& filePath) {
    // Initialize FFmpeg (or other library)
    // For FFmpeg, you'd use avformat_open_input, avformat_find_stream_info, and other functions to extract metadata.
    // This is a simplified example:
    
    std::cout << "Extracting metadata from " << filePath << std::endl;
    
    // Example: Using FFmpeg to extract metadata
    AVFormatContext* formatContext = nullptr;
    if (avformat_open_input(&formatContext, filePath.c_str(), nullptr, nullptr) < 0) {
        wxMessageBox("Failed to open file", "Error", wxICON_ERROR);
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        wxMessageBox("Failed to find stream info", "Error", wxICON_ERROR);
        return;
    }

    AVDictionary* metadata = formatContext->metadata;
    if (metadata) {
        // Example: Extract title from metadata
        AVDictionaryEntry* tag = av_dict_get(metadata, "title", nullptr, 0);
        if (tag) {
            titleTextCtrl->SetValue(tag->value);
        }
    }

    avformat_close_input(&formatContext);
}

void VideoTagEditorFrame::UpdateMetadata(const std::string& filePath) {
    // Use FFmpeg or other libraries to update metadata
    std::cout << "Updating metadata for file: " << filePath << std::endl;
    
    // Example: Updating metadata with FFmpeg (using av_dict_set)
    // Not implemented here.
}

