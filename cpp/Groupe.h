#ifndef GROUPE_H
#define GROUPE_H


#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>

using namespace std;

class Groupe : public list <shared_ptr<Multimedia> >{

private:
    string name;

public:
    Groupe(string _name);
    string getName() const;
    void printAllVar(ostream & s) const;
    virtual ~Groupe() {}

};
#endif // GROUPE_H

Groupe::Groupe(string _name) {
    name = _name ;
}

string Groupe::getName() const
{
    return name;
}

void Groupe::printAllVar(ostream & s) const{

    s<<"Found these elements in the group : ";
    for (auto it : *this) {
        it->printVar(s);
        s<<" // ";

    }

}


