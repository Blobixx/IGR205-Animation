#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "body.hpp"
#include "main.hpp"
#include "operateur.hpp"
// Create the body using the BVH constructor

body::body() {
	counter = 1;

	matrix16f ident;
	ident.LoadIdentity();
	orient.push(ident);
} 

void body::setBVHFile(string bvhFile = "Take006.bvh") {
	theBvh = new bvh(bvhFile); 
}

body::~body()
{
}

// Replay the animation every time it's come to the end
void body::update()
{
	counter++; 
	if (counter >= theBvh->root->motion.size()) counter = 1;
}

// Draw the body using recursDraw
void body::draw()
{
	glPushMatrix();
	recursDraw(theBvh->root);
	glPopMatrix();
}

void body::recursDraw(bvhPart* part)
{
	// motion[0] holds the offset for every bvhPart, orient.top is the orientation of the parent
	matrix16f ident = orient.top()*part->motion[0];
	
	// Translate every part according to the counter and the position of the bvhPart
	ident.Translate( part->motion[counter].matrix[12], part->motion[counter].matrix[13], part->motion[counter].matrix[14]);
	ident.Rotate(part->motion[counter]); 	
		
	orient.push(ident);
	
	unsigned i = 0;
	for (i = 0; i < part->child.size(); i++) {
		// Give the offset of the child
		vector3f offset = part->child[i]->offset;
		
		if (part->child[i]->child.size() == 0) glColor3f(0.0f,0.0f,1.0f);
		else glColor3f(0.0f,1.0f,0.0f);

		glPushMatrix();
		glMultMatrixf(ident.matrix);	

		glBegin(GL_LINES);
		// The origin is the parent part, we draw a line from this point to the offset
		glVertex3f( 0,0,0 );
		glVertex3fv(offset.vertex);
		glEnd();
		glPopMatrix();
	
		if (part->child[i]->child.size() != 0) recursDraw(part->child[i]);
	}

	orient.pop();	
}



vector3f body::computeRotation(float a, float b, float c) {

//float xhip=45.1261,yhip= 41.6193,zhip= 0.1593;
//float xfinal=51.9961,yfinal=26.9593,zfinal=1.8599;
float xfinal=51.9961,yfinal=26.9593,zfinal=1.8599;

float xshoulder=46.1861,yshoulder=56.9493,zshoulder=1.9193;

vector3f eevector =vector3f(xfinal-xshoulder,yfinal-yshoulder,zfinal-zshoulder);
vector3f goalvector=vector3f(a-xshoulder,b-yshoulder,c-zshoulder);
vector3f axis=Cross(eevector,goalvector);

float axisX = dot(axis, vector3f(1.0f,0.0f,0.0f)) ;
float axisY = dot(axis, vector3f(0.0f,1.0f,0.0f)) ;
float axisZ = dot(axis, vector3f(0.0f,0.0f,1.0f)) ;

float eevectorX = dot(axis, vector3f(1.0f,0.0f,0.0f)) ;
float eevectorY = dot(axis, vector3f(0.0f,1.0f,0.0f)) ;
float eevectorZ = dot(axis, vector3f(0.0f,0.0f,1.0f)) ;

float goalvectorX = dot(axis, vector3f(1.0f,0.0f,0.0f)) ;
float goalvectorY = dot(axis, vector3f(0.0f,1.0f,0.0f)) ;
float goalvectorZ = dot(axis, vector3f(0.0f,0.0f,1.0f)) ;

matrix9f chgtBase ;
chgtBase.matrix[0]=axisX; 
chgtBase.matrix[1]=axisY ;
chgtBase.matrix[2]=axisZ;
chgtBase.matrix[3]= eevectorX;
chgtBase.matrix[4]= eevectorY;
chgtBase.matrix[5]= eevectorZ;
chgtBase.matrix[6]= goalvectorX;
chgtBase.matrix[7]= goalvectorY;
chgtBase.matrix[8]= goalvectorZ;

vector3f axisnorm=axis/axis.Length();

float angle= acos(dot(eevector,goalvector)/(eevector.Length()*goalvector.Length()));

vector3f vectorAngle = vector3f(angle,0,0) ;

vector3f resultat = chgtBase*vectorAngle ;

return resultat;
}

void body::compute(float a, float b, float c){
	
	float R1Y=3.16-6.35+72.8+115.95;
	float R1X=-16.76+0.14+47.99+75.35;
	float R1Z=2.33-4.03+15.84+102.01;
	vector3f angle1=vector3f(R1X,R1Y,R1Z);

	float R2X=3.9;
	float R2Y=-0.74;
	float R2Z=-15.03;
	vector3f angle2=vector3f(R2X,R2Y,R2Z);

	float R3X=-0.41;
	float R3Y=0.79;
	float R3Z=-7.44;
	vector3f angle3=vector3f(R3X,R3Y,R3Z);

	vector3f angle=computeRotation(a,b,c);

	vector3f move1=angle-angle1;
	vector3f move2=angle-angle2;
	vector3f move3=angle-angle3;
   
    	ofstream flux("Take006.bvh",ios_base::app); // Flux d'ecriture
 

            if(flux) // Si le lieu de destination existe ( j'entend par la le fichier )
            {
                flux <<"45.1261 41.6193 0.1593 -2.55 -4.82 -16.27 7.08 -4.90 1.08 -2.03 15.98 7.02 -4.72 -3.29 -0.10 -10.07 5.49 -20.86 2.47 7.37 -25.09 4.97 0.84 0.05 -2.33 16.76 -3.16 0.00 0.00 0.00 4.03 -0.14 6.35 -15.84 -47.99 -72.80"<<" "<< move1.vertex[0]<<" "<<move1.vertex[1]<<" "<<move1.vertex[2]<<" "<<move2.vertex[0]<<" "<<move2.vertex[1]<<" "<<move2.vertex[2]<<" "<<move3.vertex[0]<<" "<<move3.vertex[1]<<" "<<move3.vertex[2]<<" "<< "7.44 0.41 -0.79 -43.30 -29.41 -51.55 9.99 -65.35 38.75 -37.12 3.99 0.76 6.54 11.43 -23.87 5.11 -14.76 -22.61 "<<endl; 		// On ecrit dans le fichier de destination
            }                          // Et au passage on le créer si il n'existe pas
            else
            {
                cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
            }
   
}


//7.44 0.41 -0.79 -43.30 -29.41 -51.55 9.99 -65.35 38.75 -37.12 3.99 0.76 6.54 11.43 -23.87 5.11 -14.76 -22.61 




