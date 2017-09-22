#include "Video.h"
#include "Multimedia.h"
#include "Image.h"
#include "Film.h"
#include <algorithm>
#include "Groupe.h"
#include <list>
#include <memory>
#include "MyBase.h"
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
using namespace std;

int main(int argc, char *argv[])
{	
	// example code to test 
   
    shared_ptr<MyBase> base(new MyBase());

    base->deserialize("multimediaData");
    base->serialize("multimediaData");

}

/*************************************************************************************/

/* Code to test polymorphic call for diffrent types of objects 

	Multimedia ** multimediaFiles = new Multimedia * [10] {
			new Image ("tay", "yah", 25 , 25),
			new Video ("med", "ali", 25 )
		};

	for (unsigned int k = 0; k < 10; ++k) {
		    multimediaFiles[k]->printVar(cout);
	}
*/

/*************************************************************************************/

/* Code to test film.h 

	Film * myFilm = new Film ("tay", "yah");
	double newDurations[4]= {3.,2.,3.,3.};

	myFilm->setDurations(newDurations, 4);

	myFilm->printVar(cout);

	myFilm = nullptr;
	delete myFilm;

*/

/*************************************************************************************/

/* Code to test film - references

	Film * myFilm = new Film ("tay", "tay");
	double newDurations[4]= {3.,2.,3.,3.};

	myFilm->setDurations(newDurations, 4);

	int n;
	const double * durations;
	myFilm-> getAll (n , durations);
	cout<<n<<"  "<<*durations<<endl;

	myFilm = nullptr;
	delete myFilm;
*/

/*************************************************************************************/

/* Code for groups handling 
	shared_ptr<Image> im1 (new Image ("tay1", "yah", 25 , 25));
	shared_ptr<Image> im2 (new Image ("tay2", "yah", 5 , 5));
	shared_ptr<Image> im3 (new Image ("tay3", "yahhhhh", 2 , 2));

	Groupe * mygroup = new Groupe ("mymultimediaFiles");
	mygroup->push_back(im1);
	mygroup->push_back(im2);
	mygroup->push_back(im3);


	Groupe * mygroup2 = new Groupe ("mymultimediaFiles2");
	mygroup2->push_back(im1);
	mygroup2->push_back(im2);

	im1.reset();
	im2.reset();
	im3.reset();

	cout<<"groupe 1 deletion"<<endl;
	mygroup->clear();
	delete mygroup;

	cout<<"groupe 2 deletion"<<endl;
	mygroup2->clear();
	delete mygroup2;
*/

/*************************************************************************************/

/* Code to test data management and serialization
		// example code to test 
	   
	    shared_ptr<MyBase> base(new MyBase());

	    // add elements to the factory to experiment
	    shared_ptr<Image> im1 = base->createPhoto("pic1", "./tay.jpg", 25 , 25);
	    shared_ptr<Image> im2 = base->createPhoto("pic2", "./tay.jpg", 25 , 25);
	    shared_ptr<Image> im3  = base->createPhoto("pic3", "./tay.jpg", 25 , 25);

	    shared_ptr<Film> myFilm = base->createFilm("filmname", "filmpath");
	    double newDurations[4]= {3.,2.,3.,3.};
	    myFilm->setDurations(newDurations, 4);

	    shared_ptr<Video> myVid = base->createVideo("vidname", "vidpath");

	    shared_ptr<Groupe> mygroup = base->createGroup("grouptay");
	    mygroup->push_back(im1);
	    mygroup->push_back(myFilm);
	    mygroup->push_back(myVid);

	    base->serialize("multimediaData");
*/

/*************************************************************************************/