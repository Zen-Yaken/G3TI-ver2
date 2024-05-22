#include "type_interactions.h"
#include <iostream>
#include <iterator>
#include <algorithm>
using std::vector;
using std::string;
using std::cout; using std::endl;
using std::iterator;
using std::find;

std::vector<std::string> type_names = {"", "Bug", "Dark", "Dragon", "Electric", "Fighting", "Fire", "Flying", "Ghost", "Grass", "Ground", "Ice", "Normal",
                                       "Poison", "Psychic", "Rock", "Steel", "Water"};

// erases element type in 4xweakness, 2xweakness, halfXDmg, quarterXDmg, 1xdamage, and / or zeroXDmg vectors
void erase_element(vector<string>& v, string K)
{
    auto it = find(v.begin(), v.end(), K);

    //if element was found
    if(it != v.end())
    {
        int index = it - v.begin();
        v.erase(v.begin() + index);
        return;
    }
    else
    {
        return;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Type::Type(string& typeA, vector<string>& weak, vector<string>& resist, vector<string>& zeroXDmg)
{
    this->type1 = typeA;
    populate_weaknesses(weak);
    populate_resistances(resist);
    populate_zeroXDmg(zeroXDmg);
}

void Type::populate_weaknesses(vector<string>& typeW)
{
    copy(typeW.begin(), typeW.end(), back_inserter(this->weaknesses));
    return;
}

void Type::populate_resistances(vector<string>& typeR)
{
    copy(typeR.begin(), typeR.end(), back_inserter(this->resistances));
    return;
}

void Type::populate_zeroXDmg(vector<string>& typeI)
{
    copy(typeI.begin(), typeI.end(), back_inserter(this->zeroXDmg));
    return;
}

void Type::output_type()
{
    cout << "Type: " << type1 << endl;
}

void Type::output_weakness()
{
    std::cout << ("Weaknesses: ");
    if (this->weaknesses.size() == 0)
    {
        cout << "None" << endl;
        return;
    }

    for(vector<string>::iterator it = this->weaknesses.begin(); it != this->weaknesses.end(); it++)
    {
        cout << *it + " ";
    }

    cout << endl;
    return;
}

void Type::output_resistance()
{
    cout << "Resistances: ";

    if(this->resistances.size() == 0)
    {
        cout << "None " << endl;
        return;
    }

    for(vector<string>::iterator it=this->resistances.begin(); it != this->resistances.end(); it++)
    {
        cout << *it + " ";
    }

    cout << endl;
    return;
}

void Type::output_zeroXDmg()
{
    cout << "zeroXDmg: ";

    if(this->zeroXDmg.size() == 0)
    {
        cout << "None " << endl;
        return;
    }

    for(vector<string>::iterator it=this->zeroXDmg.begin(); it != this->zeroXDmg.end(); it++)
    {
        cout << *it + " ";
    }

    cout << endl;
    return;
}

string Type::get_type()
{
    return this->type1;
}

vector<string>& Type::get_weaknesses()
{
    return this->weaknesses;
}

vector<string>& Type::get_resistances()
{
    return this->resistances;
}

vector<string>& Type::get_zeroXDmg()
{
    return this->zeroXDmg;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                 

// Pokemon class
void Pokemon::set_type1(Type& x)
{
    this->type1 = x;
}

void Pokemon::set_type2(Type& y)
{
    this->type2 = y;
}

int Pokemon::calc_zeroXDmg()
{
    this->zeroXDmg.clear();

    bool single_type = false;
    if(type2.get_type() == "")
    {
        zeroXDmg = type1.get_zeroXDmg();
        single_type = true;
    }

    if(! single_type)
    {
        for(vector<string>::iterator it = type1.get_zeroXDmg().begin(); it != type1.get_zeroXDmg().end(); it++)
        {
            zeroXDmg.push_back(*it);
        }

        if (!type2.get_zeroXDmg().empty())
        {
            for(vector<string>::iterator it = type2.get_zeroXDmg().begin(); it!=type2.get_zeroXDmg().end(); it++)
            {
                vector<string>::iterator temp = find(zeroXDmg.begin(), zeroXDmg.end(), *it);
                if(temp == zeroXDmg.end())
                {
                    zeroXDmg.push_back(*it);
                }
            }
        }
    }
    return 0;
}

int Pokemon::calc_weaknesses()
{
    this->fourXDmg.clear();
    this->twoXDmg.clear();

    bool single_type = false;
    // if only 1 type only output 
    if(type2.get_type() == "")
    {
        twoXDmg = type1.get_weaknesses();
        single_type = true;
    }

    //dual type
    if(!single_type)
    {
        // get 4xWeakness
        for (vector<string>::iterator it = type1.get_weaknesses().begin(); it != type1.get_weaknesses().end(); it++)
        {
            //vector<string>::iterator zeroXDmg_temp = find(type)
            vector<string>::iterator temp = find(type2.get_weaknesses().begin(), type2.get_weaknesses().end(), *it);
            if(temp != type2.get_weaknesses().end())
            {
                fourXDmg.push_back(*it);
                continue;
            }
            twoXDmg.push_back(*it); // add 2xweakness from type1
        }

        // add 2xweakness from type2
        for (vector<string>::iterator it = type2.get_weaknesses().begin(); it != type2.get_weaknesses().end(); it++)
        {
            vector<string>::iterator temp = find(fourXDmg.begin(), fourXDmg.end(), *it);
            if(temp == fourXDmg.end())
            {
                twoXDmg.push_back(*it);
            }
        }
    }

    // get rid of any zeroXDmg the pokemon has that are in any of the weakness vectors
    for(vector<string>::iterator it = zeroXDmg.begin(); it != zeroXDmg.end(); it++)
    {
        erase_element(fourXDmg, *it);
        erase_element(twoXDmg, *it);
    }

    return 0;
}

int Pokemon::calc_resistances()
{
    this->halfXDmg.clear();
    this->quarterXDmg.clear();

    bool single_type = false;
    // if only 1 type only output 
    if(type2.get_type() == "")
    {
        halfXDmg = type1.get_resistances();
        single_type = true;
    }

    //dual type
    if(!single_type)
    {
        // get 1/4 resistances
        for (vector<string>::iterator it = type1.get_resistances().begin(); it != type1.get_resistances().end(); it++)
        {
            vector<string>::iterator temp = find(type2.get_resistances().begin(), type2.get_resistances().end(), *it);
            if(temp != type2.get_resistances().end())
            {
                quarterXDmg.push_back(*it);
                continue;
            }
            halfXDmg.push_back(*it); // add 2xweakness from type1
        }

        // add 2xweakness from type2
        for (vector<string>::iterator it = type2.get_resistances().begin(); it != type2.get_resistances().end(); it++)
        {
            vector<string>::iterator temp = find(quarterXDmg.begin(), quarterXDmg.end(), *it);
            if(temp == quarterXDmg.end())
            {
                halfXDmg.push_back(*it);
            }
        }
    }

    // get rid of any zeroXDmg the pokemon has that are in any of the weakness vectors
    for(vector<string>::iterator it = zeroXDmg.begin(); it != zeroXDmg.end(); it++)
    {
        erase_element(quarterXDmg, *it);
        erase_element(halfXDmg, *it);
    }
    return 0;
}

int Pokemon::calc_neutral() // always call this function after calc_zeroXDmg(), calc_weaknesses(), calc_resistances()
{
    this->oneXDmg.clear();

    bool in4xWeak = false;
    bool in2xWeak = false;
    bool inquarterXDmg = false;
    bool inhalfXDmg = false;
    bool inzeroXDmg = false;

    for(vector<string>::iterator it = type_names.begin(); it != type_names.end(); it++)
    {
        if(find(fourXDmg.begin(), fourXDmg.end(), *it) != fourXDmg.end())
        {   // if we enter any for loop than it was found in the resepctive vector and we do NOT have a neutral type
            in4xWeak = true;
            continue;
        }
            
        if(find(twoXDmg.begin(), twoXDmg.end(), *it) != twoXDmg.end())
        {
            in2xWeak = true;
            continue;
        }
            
        if(find(quarterXDmg.begin(), quarterXDmg.end(), *it) != quarterXDmg.end())
        {
            inquarterXDmg = true;
            continue;
        }
            
        if(find(halfXDmg.begin(), halfXDmg.end(), *it) != halfXDmg.end())
        {
            inhalfXDmg = true;
            continue;
        }
            
        if(find(zeroXDmg.begin(), zeroXDmg.end(), *it) != zeroXDmg.end())
        {
            inzeroXDmg = true;
            continue;
        }
            
        oneXDmg.push_back(*it);

    }

    vector<string>::size_type weak_len = twoXDmg.size();
    vector<string>::size_type count = 0;
    // go through twoXDmg and halfXDmg vectors and remove any elements that are in both and place those elements in oneXDmg vec
    for(vector<string>::size_type i = 0; i != weak_len; i++)
    {
        vector<string>::iterator temp = find(halfXDmg.begin(), halfXDmg.end(), twoXDmg[count]);
        if(temp != halfXDmg.end()) // found the same type in both weakness and resist vectors
        {
            //oneXDmg.push_back(*it);
            oneXDmg.push_back(twoXDmg[count]);
            erase_element(halfXDmg, twoXDmg[count]);
            erase_element(twoXDmg, twoXDmg[count]);
            count--;
        }
        count++;
    }

    return 0;
}

void Pokemon::output_zeroXDmg()
{
    cout << "0x Damage:\n";
    for(vector<string>::iterator it = zeroXDmg.begin(); it != zeroXDmg.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void Pokemon::output_weaknesses()
{
    cout << "4x Damage:\n";
    for(vector<string>::iterator it = fourXDmg.begin(); it != fourXDmg.end(); it++)
        cout << *it << " ";
    cout << endl;

    cout << "2x Damage:\n";
    for(vector<string>::iterator it = twoXDmg.begin(); it != twoXDmg.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void Pokemon::output_resitances()
{
    cout << "1/2x Damage\n";
    for(vector<string>::iterator it = halfXDmg.begin(); it != halfXDmg.end(); it++)
        cout << *it << " ";
    cout << endl;

    cout << "1/4x Damage:\n";
    for(vector<string>::iterator it = quarterXDmg.begin(); it != quarterXDmg.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void Pokemon::output_neutral()
{
    cout << "1x Damage:\n";
    for(vector<string>::iterator it = oneXDmg.begin(); it != oneXDmg.end(); it++)
        cout << *it << " ";
    cout << endl;
}


