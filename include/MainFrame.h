#ifndef GAURD_MAINFRAME_h
#define GAURD_MAINFRAME_h
#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <vector>
#include "type_interactions.h"

class MainFrame: public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& sz); // constructor
    
    // used for drop down (choice) box
    wxArrayString types1 = {"NONE", "BUG", "DARK", "DRAGON", "ELECTRIC", "FIGHTING", "FIRE", "FLYING", "GHOST", "GRASS", "GROUND", "ICE", "NORMAL",
                           "POISON", "PSYCHIC", "ROCK", "STEEL", "WATER"};

    std::vector<std::string> fileNames = {"", "Bug.png", "Dark.png", "Dragon.png", "Electric.png", "Fighting.png", "Fire.png", "Flying.png", "Ghost.png",
                                        "Grass.png", "Ground.png", "Ice.png", "Normal.png", "Poison.png", "Psychic.png", "Rock.png", "Steel.png", "Water.png"};

    std::vector<std::string> types2 = {"Bug", "Dark", "Dragon", "Electric", "Fighting", "Fire", "Flying", "Ghost",
                                        "Grass", "Ground", "Ice", "Normal", "Poison", "Psychic", "Rock", "Steel", "Water"};


private:
    Pokemon poke;                       // Data
    int first_type_selection = 0;
    int second_type_selection = 0;
    int current_first_selection = 0;
    int current_second_selection = 0;
    Type typeA;
    Type typeB;


    int iconSizeX = 60; // type icon x-dimension
    int iconSizeY = 30; // type icon y-dimension
    wxSizerFlags choiceFlags = wxSizerFlags().CenterVertical().Top().Border(wxALL, 25); // flag for drop down (choice) boxes
    wxSizerFlags choiceFlags2 = wxSizerFlags().CenterVertical().Top().Border(wxALL, 30);
    
    // main components
    wxScrolled<wxPanel>* panel;
    wxBoxSizer* mainSizer;

    // BoxSizers types, super effective, resistances, 1x, and immunities
    wxBoxSizer* typeSizer;
    wxBoxSizer* fourXSizer;
    wxBoxSizer* twoXSizer;
    wxBoxSizer* oneXSizer;
    wxBoxSizer* halfXSizer;
    wxBoxSizer* quarterXSizer;
    wxBoxSizer* zeroXSizer;

    // WrapSizers, where to display type icons (for super effective, resistances, 1x, and immunities)
    wxWrapSizer* fourXWrap;
    wxWrapSizer* twoXWrap;
    wxWrapSizer* oneXWrap;
    wxWrapSizer* halfXWrap;
    wxWrapSizer* quarterXWrap;
    wxWrapSizer* zeroXWrap;

    // Drop down (choice) boxes
    wxChoice* type1;
    wxChoice* type2;

    // Text
    wxStaticText* fourXText;
    wxStaticText* twoXText;
    wxStaticText* oneXText;
    wxStaticText* halfXText;
    wxStaticText* quarterXText;
    wxStaticText* zeroXText;
     
    // used to hold type icons in each wrapper, need this to show and hide the correct types based on weakness, resistance, neutral, immunity
    std::vector<wxStaticBitmap*> fourVec;
    std::vector<wxStaticBitmap*> twoVec;
    std::vector<wxStaticBitmap*> oneVec;
    std::vector<wxStaticBitmap*> halfVec;
    std::vector<wxStaticBitmap*> quarterVec;
    std::vector<wxStaticBitmap*> zeroVec;
    
    // did not implement. these bools could be used to hide the text in the boxsizers (that say 4x Damage, etc)
    bool fourXNone = true;
    bool twoXNone = true;
    bool oneXNone = true;
    bool halfXNone = true;
    bool quarterXNone = true;
    bool zeroXNone = true;
    void populate_wrapsizer_with_types(wxWrapSizer*, std::vector<wxStaticBitmap*>&); // fill a given wraper with all type icons
    void display_types(const std::vector<wxStaticBitmap*>&, const std::vector<std::string>&); // display 
    void display_all_types();

    void on_choice_made1(wxCommandEvent&); // calculate weaknesses, resistances, neutral, immunities when a selection / choice is made
    void on_choice_made2(wxCommandEvent&);


    wxDECLARE_EVENT_TABLE();
};



#endif