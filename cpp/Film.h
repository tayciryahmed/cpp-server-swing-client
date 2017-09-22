#ifndef FILM_H
#define FILM_H

#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

class Film : public Video {

protected:
    string name = "unspecified";
    int nbChapters = 0;
    double *durations = nullptr;

public:
    Film();
    Film(string name, string pathname);
    void printVar(ostream & s) const final;

    const double * getDurations() const ;
    void setDurations(const double* _durations , int _nbChapters);

    int getNbChapters() const;
    void setNbChapters(int value);

    void getAll (int & _nbChapters , const double * & _durations);
    string getType() const ;
    void serialize(ostream & s) const ;
    virtual ~Film() {delete[] durations;}
    string getName() const;
    void setName(const string &value);
    void deserialize(string attributes);
};

#endif // FILM_H


Film::Film(){}
string Film::getName() const
{
    return name;
}

void Film::setName(const string &value)
{
    name = value;
}
Film::Film(string _name, string _pathname) {
    std::replace( _name.begin(), _name.end(), ' ', '_');
    std::replace( _pathname.begin(), _pathname.end(), ' ', '_');
    name = _name;
    pathname = _pathname;

}

const double * Film::getDurations() const {
    return durations;
}


void Film::getAll (int & _nbChapters , const double * & _durations){
    _nbChapters = nbChapters;
    _durations = durations ;
}

void Film::printVar(ostream & s) const{
    string result = getName()+" ";
    for (int k=0; k<nbChapters; k++){
        result.append(to_string(durations[k]));
        result.append(" ");
     }
    s<<result;
}

void Film::setDurations(const double* _durations , int _nbChapters){
    nbChapters=_nbChapters;

    delete[] durations;

    durations = new double[nbChapters];
    for (int k=0; k<nbChapters; k++){
        durations[k]=_durations[k];
     }
}


int Film::getNbChapters() const
{
    return nbChapters;
}

void Film::setNbChapters(int value)
{
    nbChapters = value;
}

string Film::getType() const {
    return "Film";
}

void Film::serialize(ostream & s) const {

    if (s) {
        s<<getType()+" ";
        printVar(s);
        s<<'\n';
    }

}

void Film::deserialize(string attributes){
    vector<string> words;
    stringstream ss;
    ss.str(attributes);
    string word;
    while (getline(ss, word, ' ')) {words.push_back(word); }

    name = words[0];

    words.erase(words.begin());

    vector<double> doubleVector(words.size());
    std::transform(words.begin(), words.end(), doubleVector.begin(), [](const std::string& val)
    {
        return std::stod(val);
    });

    double* a = &doubleVector[0];
    nbChapters = words.size();
    setDurations(a , nbChapters);
}
