//
// Created by lukla on 18.06.2022.
//

#include <filesystem>
#include <random>

#include "application.hpp"
#include "random.hpp"
#include "piece.hpp"
#include "wave.hpp"

Frame::Frame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
                                              wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxSYSTEM_MENU)
{
    player = std::make_unique<Player>();

    CreateControls();
    BindEvents();
}

void Frame::CreateControls()
{
    panel = new wxPanel(this, wxID_ANY);
    hbox = new wxBoxSizer(wxVERTICAL);
    grid = new wxFlexGridSizer(5, 2, 10, 70);

    panel->SetFont(GetFont().Scale(1.5));

    filenameLabel = new wxStaticText(panel, wxID_ANY, "Filename: ");
    lengthLabel = new wxStaticText(panel, wxID_ANY, "Length:");
    sampleRateLabel = new wxStaticText(panel, wxID_ANY, "Sample rate: ");
    bitDepthLabel = new wxStaticText(panel, wxID_ANY, "Bit depth: ");
    channelLabel = new wxStaticText(panel, wxID_ANY, "Channels: ");

    filenameCtrl = new wxTextCtrl(panel, wxID_ANY);
    lengthCtrl = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString);
    lengthCtrl->SetValue(60);

    sampleRateCtrl = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    sampleRateCtrl->Append({"44100 Hz", "48000 Hz", "96000 Hz", "192000 Hz"});
    sampleRateCtrl->Select(0);

    bitDepthCtrl = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    bitDepthCtrl->Append({"16-bit", "24-bit", "32-bit"});
    bitDepthCtrl->Select(1);

    channelCtrl = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
    channelCtrl->Append(std::vector<wxString>{"Mono", "Stereo"});
    channelCtrl->Select(1);

    generateButton = new wxButton(panel, wxID_ANY, "Generate", wxDefaultPosition, {300, 50});
    generateButton->SetFont(GetFont().Scale(2.0));

    grid->Add(filenameLabel);
    grid->Add(filenameCtrl, 1, wxEXPAND);
    grid->Add(lengthLabel);
    grid->Add(lengthCtrl, 1, wxEXPAND);
    grid->Add(sampleRateLabel);
    grid->Add(sampleRateCtrl, 1, wxEXPAND);
    grid->Add(bitDepthLabel);
    grid->Add(bitDepthCtrl, 1, wxEXPAND);
    grid->Add(channelLabel);
    grid->Add(channelCtrl, 1, wxEXPAND);

    hbox->Add(grid, 1, wxALL | wxEXPAND, 20);
    hbox->Add(generateButton, 0, wxALIGN_CENTER | wxALL, 30);

    panel->SetSizer(hbox);
}

void Frame::BindEvents()
{
    generateButton->Bind(wxEVT_BUTTON, [&](wxCommandEvent& e) {
        Frame::OnGenerate(e);
    });
}

void Frame::OnGenerate(wxCommandEvent& e)
{
    static constexpr std::array<int, 4> sampleRates = {44100, 48000, 96000, 192000};
    static constexpr std::array<int, 3> bitDepths = {16, 24, 32};

    int sampleRate = sampleRates.at(sampleRateCtrl->GetSelection());
    int bitDepth = bitDepths.at(bitDepthCtrl->GetSelection());
    int length = lengthCtrl->GetValue();
    int channels = channelCtrl->GetSelection() + 1;

    auto filename = static_cast<std::string>(filenameCtrl->GetValue());
    if(std::filesystem::exists(filename + ".wav"))
    {
        int i = 1;
        while(std::filesystem::exists(filename + " (" + std::to_string(i) + ").wav"))
            ++i;
        filename.append(" (" + std::to_string(i) + ")");
    }
    filename.append(".wav");

    Piece piece = randomPiece({sampleRate, bitDepth, channels}, static_cast<double>(length));

    player->fromTracks({sampleRate, bitDepth, channels}, piece.play());
    player->save(filename);
}

bool Application::OnInit()
{
    auto* frame = new Frame("Pozakres");
    frame->SetClientSize(400, 700);
    frame->Center();
    frame->SetIcon(wxICON(sample));
    frame->Show();
    return true;
}
