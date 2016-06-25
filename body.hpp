#ifndef BODY_HPP
#define BODY_HPP

#include <stack>

#include "movable.hpp"
#include "bvh.hpp"
#include "light.hpp"
#include <math.h> 
#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;

class body : public movable
{
	//Recursive function to draw the body part by part
	void recursDraw(bvhPart *part);
	
	stack<matrix16f> orient;

public:
	void setBVHFile(string bvhFile) ;
	body() ;
	~body();

	// Position in the animation
	unsigned counter;

	bvh *theBvh;
	
	void draw();
	void update();
	matrix9f rotation; 
	
	vector<light*> lights;

	void compute(float a, float b, float c);

	matrix9f R1, R2,R3 ;
};

#endif //BODY_HPP
