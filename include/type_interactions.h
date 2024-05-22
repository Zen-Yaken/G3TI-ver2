#ifndef GUARD_type_interactions_h
#define GUARD_type_interactions_h
#include <string>
#include <vector>
#include <cstdarg>

class Type
{
private:
    std::string type1;   
    std::vector<std::string> weaknesses;
    std::vector<std::string> resistances;
    std::vector<std::string> zeroXDmg;
    void populate_weaknesses(std::vector<std::string>& typeW);
    void populate_resistances(std::vector<std::string>& typeR);
    void populate_zeroXDmg(std::vector<std::string>& typeI);

public:
    Type(std::string&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&);
    Type():type1(""), weaknesses{}, resistances{}, zeroXDmg{} {};
    void output_type();
    void output_weakness();
    void output_resistance();
    void output_zeroXDmg();
    std::string get_type();
    std::vector<std::string>& get_weaknesses();
    std::vector<std::string>& get_resistances();
    std::vector<std::string>& get_zeroXDmg();
};


class Pokemon
{
private:
    Type type1;
    Type type2;

    float weakness_multiplyer = 2.0f;
    float resistance_multiplyer = 0.5f;

public:
    void set_type1(Type& x);
    void set_type2(Type& y);
    int calc_zeroXDmg(); // always call this one first
    int calc_weaknesses();
    int calc_resistances();
    int calc_neutral();    // only use this function after using calc_weaknesses(), calc_resistances(), calc_zeroXDmg()

    void output_zeroXDmg();
    void output_weaknesses();
    void output_resitances();
    void output_neutral();

    std::vector<std::string> fourXDmg;
    std::vector<std::string> twoXDmg;
    std::vector<std::string> halfXDmg;
    std::vector<std::string> quarterXDmg;
    std::vector<std::string> zeroXDmg;
    std::vector<std::string> oneXDmg;

    Pokemon(): type1(), type2(), fourXDmg{}, twoXDmg{}, halfXDmg{}, quarterXDmg{} {};
    Pokemon(Type x, Type y):  fourXDmg{}, twoXDmg{}, halfXDmg{}, quarterXDmg{} {set_type1(x); set_type2(y);};
};

void erase_element(std::vector<std::string>&, std::string);

#endif