#include "Multimedia.h"
#include <string>
using namespace std;

Multimedia::Multimedia(){
    name="unspecified";
    pathname="unspecified";
}
Multimedia::Multimedia(string _name, string _pathname){
    name=_name;
    pathname=_pathname;
}

string Multimedia::getName() const
{
    return name;
}

void Multimedia::setName(const string &value)
{
    name = value;
}

string Multimedia::getPathname() const
{
    return pathname;
}

void Multimedia::setPathname(const string &value)
{
    pathname = value;
}

void Multimedia::printVar(ostream & s) const {
    s<<  getName()<< ' '<< getPathname()<< endl;
}
