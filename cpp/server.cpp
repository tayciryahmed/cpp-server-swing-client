//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//
#include "Video.h"
#include "Multimedia.h"
#include "Image.h"
#include "Film.h"
#include <algorithm>
#include "Groupe.h"
#include <list>
#include <memory>
#include "MyBase.h"
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
using namespace std;
using namespace cppu;

const int PORT = 3332;


int main(int argc, char* argv[])
{
  // create lthe TCPServer
  shared_ptr<TCPServer> server(new TCPServer());
  
  // cree l'objet qui gère les données
  shared_ptr<MyBase> base(new MyBase());

  // add elements to the factory to experiment
  shared_ptr<Image> im1 = base->createPhoto("pic1", "./tay.jpg", 25 , 25);
  shared_ptr<Image> im2 = base->createPhoto("pic2", "yah", 25 , 25);
  shared_ptr<Image> im3  = base->createPhoto("pic3", "yah", 25 , 25);

  shared_ptr<Film> myFilm = base->createFilm("filmname", "filmpath");
  double newDurations[4]= {3.,2.,3.,3.};
  myFilm->setDurations(newDurations, 4);

  shared_ptr<Video> myVid = base->createVideo("vidname", "vidpath");

  shared_ptr<Groupe> mygroup = base->createGroup("grouptay");
  mygroup->push_back(im1);
  mygroup->push_back(myFilm);
  mygroup->push_back(myVid);


  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &MyBase::processRequest);
  
  // lance la boucle infinie du serveur
  cout << "Starting Server on port " << PORT << endl;
  int status = server->run(PORT);
  
  // en cas d'erreur
  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }
  
  return 0;
}

