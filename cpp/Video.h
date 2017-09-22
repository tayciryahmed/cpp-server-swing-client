#ifndef VIDEO_H
#define VIDEO_H
#include <cstdlib>
#include <string>
#include "Multimedia.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
class Video : public Multimedia {
protected:
    string name = "unspecified";
    string pathname = "unspecified";
    int duration;

public:
    Video();
    Video(string name, string pathname);
    Video(string name, string pathname , int _duration);
    virtual int getDuration() const;
    virtual void setDuration(int value);
    void printVar(ostream & s) const override;
    virtual void play() const;
    string getType() const;
    void serialize(ostream & s) const ;
    virtual ~Video() {}
    void deserialize(string attributes);
    string getName() const;
    void setName(const string &value);
    string getPathname() const;
    void setPathname(const string &value);
};


#endif // VIDEO_H

string Video::getName() const
{
    return name;
}

void Video::setName(const string &value)
{
    name = value;
}

string Video::getPathname() const
{
return pathname;
}

void Video::setPathname(const string &value)
{
pathname = value;
}
Video::Video(){}

Video::Video(string _name, string _pathname){
    std::replace( _name.begin(), _name.end(), ' ', '_');
    std::replace( _pathname.begin(), _pathname.end(), ' ', '_');
    name = _name;
    pathname = _pathname;
}

Video::Video(string _name, string _pathname , int _duration): Multimedia(_name, _pathname){
    name = _name;
    pathname = _pathname ; 
    duration = _duration;
}

int Video::getDuration() const
{
    return duration;
}

void Video::setDuration(int value)
{
    duration = value;
}

void Video::printVar(ostream & s) const {
    s<<  getName()<< ' '<< getPathname()<< ' '<< getDuration();
    
}

void Video::play() const{
    string command="mpv " + pathname + " &";
    system(command.c_str());
}

string Video::getType() const {
    return "Video";
}
void Video::serialize(ostream & s) const {

    if (s) {
        s<<getType()+" ";
        printVar(s);
        s<<'\n';
    }
}

void Video::deserialize(string attributes){
    vector<string> words;
    stringstream ss;
    ss.str(attributes);
    string word;
    while (getline(ss, word, ' ')) {words.push_back(word); }

    name = words[0];
    pathname = words [1];
    duration = stoi(words[2]);

}
