#include "window.hpp"
#include "search.hpp"
#include <iostream>
#include <string>
#include <vector>

wxBEGIN_EVENT_TABLE(Window, wxFrame)
EVT_BUTTON(20001, Window::pressedSearchBtn)
EVT_BUTTON(20002, Window::pressedExitBtn)
EVT_TEXT_ENTER(20003, Window::pressedSearchBtn)
wxEND_EVENT_TABLE()

Window::Window(const wxString& title) : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600))
{
    // Create Panel
    wxPanel *panel = new wxPanel(this, -1);

    // Create Virtical Box Sizer
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    // Create Horizontal Box Sizer
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

    // Create Title Text
    wxStaticText *st1 = new wxStaticText(panel, wxID_ANY, wxT("Search Keyword"));

    // Add Title Text to the Horizontal Box Sizer
    hbox1->Add(st1, 0, wxRIGHT, 8);

    // Create Text Box
    tc = new wxTextCtrl(panel, 20003, wxT(""), wxPoint(-1, -1), wxSize(-1, -1), wxTE_PROCESS_ENTER);

    // Add Text Box to the Horizontal Box Sizer
    hbox1->Add(tc, 1);

    // Add the Horizontal Sizer to the Vertical Sizer
    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    // NOT SURE ABOUT THIS ONE
    vbox->Add(-1, 10);

    // Create another Horizontal Box Sizer
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

    // Create Text Object
    wxStaticText *st2 = new wxStaticText(panel, wxID_ANY, wxT("Search Results"));

    // Add Text Object to Horizontal Box Sizer
    hbox2->Add(st2, 0);

    // Add Horizontal Box Sizer
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

    // NOT SURE ABOUT THIS ONE
    vbox->Add(-1, 10);

    // Make new Horizontal Box Sizer
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);

    // Create Text Box
    tc2 = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);

    // Add Text Box to Horizontal Box Sizer
    hbox3->Add(tc2, 1, wxEXPAND);

    // Add Horizontal Box Sizer to Vertical Sizer
    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);

    // NOT SURE ABOUT THIS ONE, I think this has something to do with spacing
    vbox->Add(-1, 25);

    // Create new Horizontal Box Sizer
    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);

    // Add Search Button
    btn1 = new wxButton(panel, 20001, wxT("Search"));

    // Add Search Button to Horizontal Box Sizer
    hbox4->Add(btn1, 0);

    // Add Exit Button
    btn2 = new wxButton(panel, 20002, wxT("Exit"));

    // Add Exit Button to Horizontal Box Sizer
    hbox4->Add(btn2, 0, wxLEFT, 10);

    // Add Horizontal Box Sizer to Vertical Box Sizer
    vbox->Add(hbox4, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    // Add spacing to bottom
    vbox->Add(-1, 10);

    // Set Panel Sizer
    panel->SetSizer(vbox);

    // Centre
    Centre();
}

void Window::pressedSearchBtn(wxCommandEvent& evt)
{
    // User pressed Search button
    std::cout << "Pressed Search Button" << std::endl;

    // Clear the big text box
    tc2->Clear();

    // Get search term
    std::string tbSearchTerm = tc->GetValue().ToStdString();
    std::cout << "Search Term from Textbox: " << tbSearchTerm << std::endl;

    searchSQLDB(tbSearchTerm);
    std::vector<std::string> vRetName = retName();
    std::vector<std::string> vRetLineA = retTLEA();
    std::vector<std::string> vRetLineB = retTLEB();
    std::vector<std::string> vRetTable = retTLETable();

    // DEBUG: See length of returned vector
    std::cout << "length: " << vRetName.size() << std::endl;

    // Put the names of the satellites found on the big textbox
    for (int a = 0; a < vRetName.size(); a++)
    {
        *tc2 << "(";
        *tc2 << a;
        *tc2 << " - ";
        *tc2 << vRetTable[a];
        *tc2 << ") ";
        *tc2 << vRetName[a];
        *tc2 << "\n";
    }
}

void Window::pressedExitBtn(wxCommandEvent& evt)
{
    // User pressed Exit button
    std::cout << "Pressed Exit Button" << std::endl;

    // Exit with EXIT_SUCCESS
    exit(EXIT_SUCCESS);
}
