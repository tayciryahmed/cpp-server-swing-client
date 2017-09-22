#ifndef COHERANTEDATA_H
#define COHERANTEDATA_H
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <list>
#include <memory>
#include "cppsocket.h"
#include <sstream>
#include "tcpserver.h"
#include <vector>
#include <typeinfo>
#include <sstream>
using namespace std;
using namespace cppu;
#include <typeinfo>


class MyBase {

private:
    map<string, shared_ptr<Groupe>> groups= {};
    map<string, shared_ptr<Multimedia>> multimediaFiles = {};

public:

    MyBase();
    shared_ptr<Image> createPhoto(string name, string path , int lat , int lon);
    shared_ptr<Video> createVideo(string name, string path);
    shared_ptr<Groupe> createGroup(string name);
    shared_ptr<Film> createFilm(string name, string path);
    string print(string name, ostream & s );
    void play (string name);
    void serialize(string storeFile) const;
    void deserialize(string storeFile);
    string deleteItem (string name);
    bool processRequest(TCPConnection& cnx, const string& request, string& response);
    virtual ~MyBase() {}
};

#endif // COHERANTEDATA_H



MyBase::MyBase() {
}

shared_ptr<Image> MyBase::createPhoto(string name, string path , int lat , int lon){
    if (find_if(name.begin(), name.end(), [](char c) { return !(isalnum(c) || c==' '); }) != name.end()){
        cout<<"error in creating the file: name contains invalid caracters: "+name<<endl;
        return NULL;
    }
    else {
        if (multimediaFiles.find(name) == multimediaFiles.end()){
            shared_ptr<Image> myImage ( new Image (name, path, lat , lon));
            multimediaFiles[name] = myImage;
            return myImage;
        }
        else {
            cout<<"Second file with name '"+name + "' not created because there is already another one having the same name."<<endl;
            return NULL;
        }
    }

}

shared_ptr<Video> MyBase::createVideo(string name, string path){
    if (find_if(name.begin(), name.end(), [](char c) { return !(isalnum(c) || c==' '); }) != name.end()){
        cout<<"error in creating the file: name contains invalid caracters: "+name<<endl;
        return NULL;
    }
    else {
        if (multimediaFiles.find(name) == multimediaFiles.end()){
            shared_ptr<Video> myVideo (new Video (name, path));
            multimediaFiles[name] = myVideo;
            return myVideo;
        }
        else {
            cout<<"Second file with name '"+name + "' not created because there is already another one having the same name."<<endl;
            return NULL;
        }
    }
}

shared_ptr<Groupe> MyBase::createGroup(string name){
    if (find_if(name.begin(), name.end(), [](char c) { return !(isalnum(c) || c==' '); }) != name.end()){
        cout<<"error in creating the group: name contains invalid caracters: "+name<<endl;
        return NULL;
    }
    else {
        if (groups.find(name) == groups.end()){
            shared_ptr<Groupe> myGroup (new Groupe (name));
            groups[name] = myGroup;
            return myGroup;
        }
        else {
            cout<<"Second file with name '"+name + "' not created because there is already another one having the same name."<<endl;
            return NULL;
        }
    }


}

shared_ptr<Film> MyBase::createFilm(string name, string path){
    if (find_if(name.begin(), name.end(), [](char c) { return !(isalnum(c) || c==' '); }) != name.end()){
        cout<<"error in creating the file: name contains invalid caracters: "+name<<endl;
        return NULL;
    }
    else {
        if (multimediaFiles.find(name) == multimediaFiles.end()){
            shared_ptr<Film> myFilm (new Film (name, path));
            multimediaFiles[name] = myFilm;
            return myFilm;
        }
        else {
            cout<<"Second file with name '"+name + "' not created because there is already another one having the same name."<<endl;
            return NULL;
        }
    }

}

string MyBase::print (string name, ostream & s){
      if (multimediaFiles.find(name) != multimediaFiles.end()){
          cout<<"multimedia file found"<<endl;
          stringstream ss;
          multimediaFiles.find(name)->second->printVar(ss);
          return ss.str();

      }
      else if (groups.find(name) != groups.end()){
              stringstream ss;
              cout<<"Group Found"<<endl;
              groups.find(name)->second->printAllVar(ss);
              return ss.str();

          }
      else if (name=="*"){
          // below statement : print all the base content
          string result = "The multimedia files in the base are the following : ";
          for(auto it=multimediaFiles.begin(); it!=multimediaFiles.end(); ++it) {
                  result = result + it->first + "//";
          }
          result+="; The groups in the base are : ";
          for(auto it=groups.begin(); it!=groups.end(); ++it) {
              result = result + it->first+ "//";
          }
          return result;

        }
      else if (name=="images"){
          // below statement to print all the images in the base
          string result = "The images in the base are the following : ";
          for(auto it=multimediaFiles.begin(); it!=multimediaFiles.end(); ++it) {
              if (it->second->getType()=="Image"){
                  result = result + it->first + "//";
              }
          }
          if (result=="The images in the base are the following : "){result="No images found in the base";}
          return result;
      }
      else if (name=="films"){
          // below statement to print all the films in the base
          string result = "The films in the base are the following : ";
          for(auto it=multimediaFiles.begin(); it!=multimediaFiles.end(); ++it) {
              if (it->second->getType()=="Film"){
                  result = result + it->first + "//";
              }
          }
          if (result=="The films in the base are the following : "){result="No films found in the base";}
          return result;
      }
      else if (name=="videos"){
          // below statement to print all the videos in the base
          string result = "The videos in the base are the following : ";
          for(auto it=multimediaFiles.begin(); it!=multimediaFiles.end(); ++it) {
              if (it->second->getType()=="Video"){
                  result = result + it->first + "//";
              }
          }
          if (result=="The videos in the base are the following : "){result="No videos found in the base";}
          return result;
      }
      else {
        cout<<"error in printing - Didn't find any file/group with the name : "+ name<<endl;
        return "Didn't find any file/group with the name : "+ name;
      }


}

string MyBase::deleteItem (string name){

      if (multimediaFiles.find(name) != multimediaFiles.end()){
          cout<<"multimedia file found => To be deleted upon the user request"<<endl;

          // eliminate the item from all the groups containing it
          for(auto it=groups.begin(); it!=groups.end(); ++it) {
              if (find(it->second->begin(), it->second->end(), multimediaFiles.find(name)->second) != it->second->end()){
                  it->second->remove(multimediaFiles.find(name)->second);
              }
          }
          multimediaFiles.erase(name);
          // shared_ptr => no need to use delete
          return "File deleted";

      }
      else {

          if (groups.find(name) != groups.end()){
              cout<<"Group Found => To be deleted upon the user request "<<endl;
              groups.erase(name);
              // shared_ptr => no need to use delete
              return "Group deleted";

          }
          else {
              cout<<"error in deleting - Didn't find any file/group with the name : "+ name<<endl;
              return "error in deleting - Didn't find any file/group with the name : "+ name;

          }
}
}
void MyBase::play (string name){

      if (multimediaFiles.find(name) != multimediaFiles.end()){
          cout<<"multimedia file found"<<endl;
          multimediaFiles.find(name)->second->play();
      }
      else {
          cout<<"error in playing"<<endl;
          }

}

void MyBase::serialize(string storeFile)const {
    ofstream file(storeFile);
    for(auto it=multimediaFiles.begin(); it!=multimediaFiles.end(); ++it) {
            it->second->serialize(file);
    }
    file.close();
}
void MyBase::deserialize(string storeFile) {
    multimediaFiles = {};
    ifstream infile(storeFile);
    string line;
    while (getline(infile, line))
    {
        if (line.substr(0,line.find_first_of(" "))== "Image"){
            shared_ptr<Image> myImage ( new Image ());
            myImage->deserialize(line.substr(line.find_first_of(" ")+1));
            multimediaFiles[myImage->getName()] = myImage;

        }
        if (line.substr(0,line.find_first_of(" "))== "Video"){
            shared_ptr<Video> myVideo ( new Video ());
            myVideo->deserialize(line.substr(line.find_first_of(" ")+1));
            multimediaFiles[myVideo->getName()] = myVideo;

        }
        if (line.substr(0,line.find_first_of(" "))== "Film"){
            shared_ptr<Film> myFilm ( new Film ());
            myFilm->deserialize(line.substr(line.find_first_of(" ")+1));
            multimediaFiles[myFilm->getName()] = myFilm;

        }

    }
    infile.close();
}


bool MyBase::processRequest(TCPConnection& cnx, const string& request, string& response)
{
  cerr << "\nRequest: '" << request << "'" << endl;

  // 1) pour decouper la requête:
  // on peut par exemple utiliser stringstream et getline()


  // 2) faire le traitement:
  // - si le traitement modifie les donnees inclure: TCPLock lock(cnx, true);
  // - sinon juste: TCPLock lock(cnx);

  // 3) retourner la reponse au client:
  // - pour l'instant ca retourne juste OK suivi de la requête
  // - pour retourner quelque chose de plus utile on peut appeler la methode print()
  //   des objets ou des groupes en lui passant en argument un stringstream
  // - attention, la requête NE DOIT PAS contenir les caractères \n ou \r car
  //   ils servent à délimiter les messages entre le serveur et le client

  // below I split the request parameters
   vector<string> words;
   stringstream ss;
   ss.str(request);
   string word;
   while (getline(ss, word, ' '))
   {words.push_back(word); }

    // below I process the request
   if (words[0] == "print"){
      if (words.size() >1){response = print(words[1] , cout);}
      else {response = "Please enter the name of the file you want to see those parameters; You can see all the base content by typing 'print *';";
      response += "You can see all the images, videos, films in the base by typing ; 'print images' , 'print videos' and 'print films' respectively. ";
      }
   }
   else if (words[0] == "play"){
       if (words.size() >1){play(words[1]);  response = "File played on the server."; }
       else {response = "Please enter the name of the file you want to play.";}
   }
   else if (words[0] == "del"){
       if (words.size() >1){response = deleteItem(words[1]); }
       else {response = "Please enter the name of the file you want to delete.";}
   }

  else {response = words[0];}


  cerr << "response: " << response << endl;

  // renvoyer false si on veut clore la connexion avec le client
  return true;
}

