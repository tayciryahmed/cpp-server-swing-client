#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H
#include <string>
#include <iostream>
using namespace std;

class Multimedia
{
protected:
    string name;
    string pathname;
public:
    Multimedia();
    Multimedia(string name, string pathname);
    string getName() const;
    void setName(const string &value);
    string getPathname() const;
    void setPathname(const string &value);
    virtual void printVar(ostream & s) const;
    virtual void play() const = 0;
    virtual string getType() const = 0;
    virtual void serialize(ostream & s) const = 0;
    virtual ~Multimedia() {}

};

#endif // MULTIMEDIA_H
