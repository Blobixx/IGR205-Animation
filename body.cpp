#ifdef WIN32
#include <windows.h>
#endif


#include <GL/gl.h>
#include <GL/glu.h>

#include "body.hpp"
#include "main.hpp"


body::body(string bvhFile = "bvh/Take 006.bvh")
{
	counter = 1;
	theBvh = new bvh(bvhFile); 

	matrix16f ident;
	ident.LoadIdentity();
	orient.push(ident);	
}

body::~body()
{
}

void body::update()
{
	counter++; 
	if (counter >= theBvh->root->motion.size()) counter = 1;
}

void body::update(int counterOffset)
{
	counter += counterOffset; 

	if (counter >= theBvh->root->motion.size()) counter %= theBvh->root->motion.size();
	else if (counter < 0) 
		counter = 0 ;
}

void body::draw()
{
	glPushMatrix();

	glColor3f(0.5f,0.0f,0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1000.0f,0.0f,0.0f);
	glColor3f(0.0f,0.5f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,1000.0f,0.0f);
	glColor3f(0.0f,0.0f,0.5f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,1000.0f);
	glEnd();
	
	glColor3f(1.0f,0.0f,0.5f);
	
	recursDraw(theBvh->root);

	glPopMatrix();
}


void body::recursDraw(bvhPart* part)
{
	GLUquadricObj *q = gluNewQuadric();
	
	// motion[0] holds the offset, so it is also needed
	matrix16f ident = orient.top() * part->motion[0];
	
	ident.Translate(
		part->motion[counter].matrix[12],
		part->motion[counter].matrix[13],
		part->motion[counter].matrix[14]);
	ident.Rotate(part->motion[counter]); 	
		
	orient.push(ident);
	
	vector3f up,right,out;
	matrix16f face;
	face.LoadIdentity();
	
	unsigned i = 0;
	for (i = 0; i < part->child.size(); i++) {
		vector3f offset = part->child[i]->offset;
		
		if (part->child[i]->child.size() == 0) glColor3f(0.9f,0.5f,0.0f);
		else glColor3f(1.0f,0.1f,0.1f);
		glPushMatrix();
		glMultMatrixf(ident.matrix);	
		glBegin(GL_LINES);
		glVertex3f( 0,0,0 );
		glVertex3fv( offset.vertex );
		glEnd();
		glPopMatrix();
	
		if (part->child[i]->child.size() != 0) recursDraw(part->child[i]);
	}
	gluDeleteQuadric(q);
	orient.pop();	
}
