#ifndef VIDEO_H
#define VIDEO_H
#include <string>
#include "Multimedia.h"

class Video:public Multimedia {
private:
    int duration;
    string pathname=Video::getPathname();

public:
    int getDuration() const;
    void setDuration(int value);
    Video(int _duration);
    virtual void play(string _pathname) const;

};


#endif // VIDEO_H

int Video::getDuration() const
{
    return duration;
}

void Video::setDuration(int value)
{
    duration = value;
}
Video::Video(int _duration){
    duration=_duration;
}
void Video::play(string _pathname) const{
    system("mpv "+_pathname+" &".c_str());
}
