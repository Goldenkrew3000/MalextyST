#include "main.hpp"
#include "window.hpp"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Window *window = new Window(wxT("SQLite Search DB"));
    window->Show(true);

    return true;
}