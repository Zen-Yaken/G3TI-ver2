#include <wx/wx.h>
#include <wx/choice.h>
#include <wx/stdpaths.h>
#include <vector>
#include <string>
#include <algorithm>
#include "MainFrame.h"
#include "types.h"

using std::vector; using std::string;

enum IDs
{
    CHOICE_TYPE1_ID = 2,
    CHOICE_TYPE2_ID = 3
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CHOICE(CHOICE_TYPE1_ID, MainFrame::on_choice_made1)
    EVT_CHOICE(CHOICE_TYPE2_ID, MainFrame::on_choice_made2)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size):wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    // main panel and sizer
    panel = new wxScrolled<wxPanel>(this); //scrollbar
    panel->SetScrollRate(0, FromDIP(10));
    this->SetMinSize(wxSize(360, 100));

    mainSizer = new wxBoxSizer(wxVERTICAL);
    wxFont dmgFont(wxFontInfo(10).Bold()); // Fonts (size and if bolded or not)
    wxFont choiceFont(wxFontInfo(10));

    // create boxsizers (for text)
    typeSizer = new wxBoxSizer(wxHORIZONTAL);
    fourXSizer = new wxBoxSizer(wxHORIZONTAL);
    twoXSizer = new wxBoxSizer(wxHORIZONTAL);
    oneXSizer = new wxBoxSizer(wxHORIZONTAL);  
    halfXSizer = new wxBoxSizer(wxHORIZONTAL);
    quarterXSizer = new wxBoxSizer(wxHORIZONTAL);
    zeroXSizer = new wxBoxSizer(wxHORIZONTAL);
    
    // create Wrap sizers (for type icons)
    fourXWrap = new wxWrapSizer(wxHORIZONTAL);
    twoXWrap = new wxWrapSizer(wxHORIZONTAL);
    oneXWrap = new wxWrapSizer(wxHORIZONTAL); 
    halfXWrap = new wxWrapSizer(wxHORIZONTAL);
    quarterXWrap = new wxWrapSizer(wxHORIZONTAL);
    zeroXWrap = new wxWrapSizer(wxHORIZONTAL);

    // set font for all boxsizers
    panel->SetFont(dmgFont);
    
    // Drop down (choice) boxes
    type1 = new wxChoice(panel,CHOICE_TYPE1_ID, wxDefaultPosition, wxSize(100, -1), types1); // create drop down (choice) boxes
    type2 = new wxChoice(panel, CHOICE_TYPE2_ID, wxDefaultPosition, wxSize(100, -1), types1);
    typeSizer->Add(type1, choiceFlags2); // add drop down (choice) boxes to appropriate boxsizer
    typeSizer->Add(type2, choiceFlags2);
    type1->Select(0); //set default selection to choice 0
    type2->Select(0);
    type1->SetFont(choiceFont);
    type2->SetFont(choiceFont);
    
    // create text
    fourXText = new wxStaticText(panel, wxID_ANY, wxString("4x Damage"));
    twoXText = new wxStaticText(panel, wxID_ANY, wxString("2x Damage"));
    oneXText = new wxStaticText(panel, wxID_ANY, wxString("1x Damage"));
    halfXText = new wxStaticText(panel, wxID_ANY, wxString("1/2x Damage"));
    quarterXText = new wxStaticText(panel, wxID_ANY, wxString("1/4x Damage"));
    zeroXText = new wxStaticText(panel, wxID_ANY, wxString("0x Damage"));

    // Add text to boxsizers
    fourXSizer->Add(fourXText);
    twoXSizer->Add(twoXText);
    oneXSizer->Add(oneXText); 
    halfXSizer->Add(halfXText);
    quarterXSizer->Add(quarterXText);
    zeroXSizer->Add(zeroXText);
    
    populate_wrapsizer_with_types(fourXWrap, fourVec);
    populate_wrapsizer_with_types(twoXWrap, twoVec);
    populate_wrapsizer_with_types(oneXWrap, oneVec);
    populate_wrapsizer_with_types(halfXWrap, halfVec);
    populate_wrapsizer_with_types(quarterXWrap, quarterVec);
    populate_wrapsizer_with_types(zeroXWrap, zeroVec);
    
    // add all other sizers to the main sizer (both boxsizers and wrapsizers)
    mainSizer->Add(typeSizer);
    mainSizer->Add(fourXSizer);
    mainSizer->Add(fourXWrap);
    mainSizer->Add(twoXSizer);
    mainSizer->Add(twoXWrap);
    mainSizer->Add(oneXSizer);  
    mainSizer->Add(oneXWrap);
    mainSizer->Add(halfXSizer); 
    mainSizer->Add(halfXWrap);
    mainSizer->Add(quarterXSizer); 
    mainSizer->Add(quarterXWrap);
    mainSizer->Add(zeroXSizer); 
    mainSizer->Add(zeroXWrap);

    // set the layout
    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
    mainSizer->Layout();

}

// put all the type icons in a wrap sizer, we call this for all wrap sizers
void MainFrame::populate_wrapsizer_with_types(wxWrapSizer* wrapPtr, vector<wxStaticBitmap*>& vec)
{
    // go through ALL IMAGES IN workspaceFolder\\build\\TypeIcons
    for(vector<string>::iterator it = fileNames.begin(); it !=fileNames.end(); it++)
    {
        wxString fpath = wxStandardPaths::Get().GetDataDir(); // gets path to workspaceFolder\\build
        if (*it == "")
            continue;
        fpath += "\\TypeIcons\\" + *it; // get full filename for png. Ex: ${workspaceFolder}\\build\\TypeIcons\\*.png
        
        wxImage* temp_img = new wxImage(fpath, wxBITMAP_TYPE_PNG); //make a wxImage so we can resize the type icons
        temp_img->Rescale(iconSizeX, iconSizeY, wxIMAGE_QUALITY_NORMAL); // resizes / recale the icon
        wxStaticBitmap* temp_bitmap = new wxStaticBitmap(panel, wxID_ANY, *temp_img); //create a static bitmap so we can display to screen
        temp_img->Destroy(); // destroy the wxImage so we can free this memory
        temp_img = NULL;

        vec.push_back(temp_bitmap); // add the newly created static bitmap to the appropriate vec, so we can hide or unhide this bitmap when we need to
        wrapPtr->Add(temp_bitmap);  // we hide / unhide these static bitmaps based on what the Pokemon is weak to, resistant to, neutral to, immune to
        temp_bitmap->Hide();
        temp_bitmap = NULL;
        mainSizer->Layout();   // ensure layout is set 
    }

    return;
}

void MainFrame::on_choice_made1(wxCommandEvent& evt)
{    
    first_type_selection = evt.GetSelection();
    poke.set_type1(types[first_type_selection]);

    poke.calc_zeroXDmg(); //calculate weaknesses, resistances, neutral, immunities
    poke.calc_weaknesses();
    poke.calc_resistances();
    poke.calc_neutral();

    display_all_types();
    mainSizer->Layout();
}

void MainFrame::on_choice_made2(wxCommandEvent& evt)
{

    second_type_selection = evt.GetSelection();
    poke.set_type2(types[second_type_selection]);
    
    poke.calc_zeroXDmg(); //calculate weaknesses, resistances, neutral, immunities
    poke.calc_weaknesses();
    poke.calc_resistances();
    poke.calc_neutral();

    display_all_types();
    mainSizer->Layout();
}

// hide and unhide types (based on weaknesses, resistances, neutral, immunities)
// do this my comparing the staticbitmap* vector with the poke objs vectors
void MainFrame::display_types(const vector<wxStaticBitmap*>& imgs, const vector<string>& damageTypes)
{
    for(vector<wxStaticBitmap*>::size_type i = 0; i !=imgs.size(); i++) //iterate through all type icons in given wraper
    {
        if(find(damageTypes.begin(), damageTypes.end(), types2[i]) != damageTypes.end()) // Type found in the damageTypes vec
        {
            imgs[i]->Show(true);
        }
        else // type NOT found in damageTypes vec
        {
            imgs[i]->Hide(); // hide element
        }
    }
}

// calls the above functoiin for all vectors (4x, 2x, 1x, 1/2x, 1/4x, 0x) dmg
void MainFrame::display_all_types()
{
    display_types(fourVec, poke.fourXDmg);
    display_types(twoVec, poke.twoXDmg);
    display_types(oneVec, poke.oneXDmg);
    display_types(halfVec, poke.halfXDmg);
    display_types(quarterVec, poke.quarterXDmg);
    display_types(zeroVec, poke.zeroXDmg);
}

// In the current implementation, we only hide or unhide the type icons. An alternative implementation is to dynamically allocate
// and destroy the type icons. A code snippet demonstrating this is shown below. One thing to note, this type of implementation is
// more prone to memory leaks, so make sure to destroy any unused type icons (AND the temporary variables that are dynamically allocated
// to create those type icons)

/*
void MainFrame::populate_fourX()
{   
    depopulate_vector_bitmapbutton(fourX);
    fourX.clear();

    wxString fpath = wxStandardPaths::Get().GetDataDir();
    wxLogStatus(fpath);
    for(vector<string>::iterator it = poke.FourXWeakness.begin(); it!= poke.FourXWeakness.end(); it++)
    {   
        //string name = *it;
        vector<string>::size_type index = getIndex(type_names1, *it);
        if (fileNames[index] == "")
            continue;
        //string file = "TypeIcons\\" + fileNames[index];
        wxString file = fpath + "\\TypeIcons\\" + fileNames[index];
        wxLogStatus(file);
        wxImage* temp_img = new wxImage(file, wxBITMAP_TYPE_PNG);
        (*temp_img).Rescale(button_size_x, button_size_y, wxIMAGE_QUALITY_NORMAL);
        wxBitmapButton* temp_button = new wxBitmapButton(panel, wxID_ANY, wxBitmap(*temp_img, -1));
        fourX.push_back(temp_button);
    }
    fourXWrap->Layout();
}
*/

