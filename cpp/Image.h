#ifndef IMAGE_H
#define IMAGE_H
#include <cstdlib>
#include <string>
#include "Multimedia.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
class Image : public Multimedia {
private:
    string name = "unspecified";
    string pathname = "unspecified";
    int lat = 0;
    int lon = 0;

public:
    Image(string name, string pathname , int lat , int lon);
    Image();
    int getLat() const;
    void setLat(int value);
    int getLon() const;
    void setLon(int value);
    string getType() const;
    void printVar(ostream & s) const override;
    virtual void play() const;
    void serialize(ostream & s) const;
    void deserialize(string attributes);
    virtual ~Image() {}
    string getName() const;
    void setName(const string &value);
    string getPathname() const;
    void setPathname(const string &value);
};


#endif // IMAGE_H


int Image::getLat() const
{
    return lat;
}

void Image::setLat(int value)
{
    lat = value;
}

int Image::getLon() const
{
return lon;
}

void Image::setLon(int value)
{
lon = value;
}

string Image::getName() const
{
    return name;
}

void Image::setName(const string &value)
{
name = value;
}

string Image::getPathname() const
{
return pathname;
}

void Image::setPathname(const string &value)
{
pathname = value;
}
Image::Image(string _name, string _pathname , int _lat , int _lon) : Multimedia(_name, _pathname) {
    std::replace( _name.begin(), _name.end(), ' ', '_');
    std::replace( _pathname.begin(), _pathname.end(), ' ', '_');
    name = _name;
    pathname = _pathname;
    lat = _lat;
    lon = _lon;
}
Image::Image(){}

void Image::printVar(ostream & s) const {
    s<<  getName()<< ' '<< getPathname()<< ' '<< getLat()<< ' '<< getLon();
    
}

void Image::play() const {
    string command="imagej " + pathname + " &";
    system(command.c_str());
}

string Image::getType() const {
    return "Image";
}

void Image::serialize(ostream & s) const {
    if (s) {
        s<<getType()+' ';
        printVar(s);
        s<<'\n';
    }
}
void Image::deserialize(string attributes){
    vector<string> words;
    stringstream ss;
    ss.str(attributes);
    string word;
    while (getline(ss, word, ' ')) {words.push_back(word); }

    name = words[0];
    pathname = words [1];
    lat = stoi(words[2]);
    lon = stoi(words[3]);

}
