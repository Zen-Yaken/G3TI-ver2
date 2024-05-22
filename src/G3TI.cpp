// Start of wxWidgets "Hello World" Program
#include "G3TI.h"
#include "MainFrame.h"
#include "wx/stdpaths.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    
    /*
    wxString iPath = wxStandardPaths::Get().GetDataDir(); // gets path to workspaceFolder\\build
    iPath += "\\pokedexIcon256x256.png";
    wxIcon* appIcon = new wxIcon(iPath);
    frame->SetIcon(*appIcon);
    */

    MainFrame *frame = new MainFrame("Gen 3 Type Interactions", wxPoint(50, 0), wxSize(330, 450));
    frame->SetClientSize(330, 450);
    frame->Show(true);

    return true;
}



