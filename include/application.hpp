//
// Created by lukla on 18.06.2022.
//

#ifndef POZAKRES_APPLICATION_HPP
#define POZAKRES_APPLICATION_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include <memory>

#include "player.hpp"

class Frame : public wxFrame
{
    wxPanel* panel;
    wxBoxSizer* hbox;
    wxFlexGridSizer* grid;

    wxStaticText* filenameLabel;
    wxStaticText* lengthLabel;
    wxStaticText* sampleRateLabel;
    wxStaticText* bitDepthLabel;
    wxStaticText* channelLabel;

    wxTextCtrl* filenameCtrl;
    wxSpinCtrl* lengthCtrl;
    wxComboBox* sampleRateCtrl;
    wxComboBox* bitDepthCtrl;
    wxComboBox* channelCtrl;

    wxButton* generateButton;

    std::unique_ptr<Player> player;
public:
    Frame(const wxString&);
    void CreateControls();
    void BindEvents();
    void OnGenerate(wxCommandEvent&);
};

class Application : public wxApp
{
public:
    bool OnInit() override;
};


#endif //POZAKRES_APPLICATION_HPP
