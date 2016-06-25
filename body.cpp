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



float computeRotation(float a, float b, float c) {

//float xhip=45.1261,yhip= 41.6193,zhip= 0.1593;
float xfinal=51.9961,yfinal=26.9593,zfinal=1.8599;
float xshoulder=46.1861,yshoulder=56.9493,zshoulder=1.9193;

vector3f eevector =vector3f(xfinal-xshoulder,yfinal-yshoulder,zfinal-zshoulder);
vector3f goalvector=vector3f(a-xshoulder,b-yshoulder,c-zshoulder);
vector3f axis=Cross(eevector,goalvector);
vector3f axisnorm=axis/axis.Length();

float angle= acos(dot(eevector,goalvector)/(eevector.Length()*goalvector.Length()));

/*matrix9f rotation;
rotation.matrix[0]=pow(axisnorm.vertex[0],2)*(1-cos(angle))+cos(angle); 
rotation.matrix[1]=axisnorm.vertex[0]*axisnorm.vertex[1]*(1-cos(angle))+axisnorm.vertex[2]*axisnorm.vertex[2] ;
rotation.matrix[2]=axisnorm.vertex[0]*axisnorm.vertex[2]*(1-cos(angle))-axisnorm.vertex[1]*sin(angle);
rotation.matrix[3]= axisnorm.vertex[0]*axisnorm.vertex[1]*(1-cos(angle))-axisnorm.vertex[2]*sin(angle);
rotation.matrix[4]= axisnorm.vertex[1]*axisnorm.vertex[1]*(1-cos(angle))+cos(angle);
rotation.matrix[5]= axisnorm.vertex[1]*axisnorm.vertex[2]*(1-cos(angle))+axisnorm.vertex[0]*sin(angle);
rotation.matrix[6]= axisnorm.vertex[0]*axisnorm.vertex[2]*(1-cos(angle))+axisnorm.vertex[1]*sin(angle);
rotation.matrix[7]= axisnorm.vertex[1]*axisnorm.vertex[2]*(1-cos(angle))-axisnorm.vertex[0]*sin(angle);
rotation.matrix[8]= axisnorm.vertex[2]*axisnorm.vertex[2]*(1-cos(angle))+cos(angle);*/

return angle;
}

void compute(float a, float b, float c){
	/*matrix9f RotationHipsChestZ ;
	RotationHipsChestZ.LoadIdentity() ; 
	RotationHipsChestZ.RotateZ(-2.33) ;

	matrix9f RotationHipsChestX ;
	RotationHipsChestX.LoadIdentity() ; 
	 RotationHipsChestX.RotateX(16.76) ;

	matrix9f RotationHipsChestY ;
	RotationHipsChestY.LoadIdentity() ; 
	RotationHipsChestX.RotateX(-3.16) ;

	matrix9f RotationChestLCollarZ ;
	RotationChestLCollarZ.LoadIdentity() ; 
	RotationChestLCollarZ.RotateZ(4.03) ;

	matrix9f RotationChestLCollarX ;
	RotationChestLCollarX.LoadIdentity() ; 
	RotationChestLCollarX.RotateX(-0.14) ;

	matrix9f RotationChestLCollarY ;
	RotationChestLCollarY.LoadIdentity() ; 
	RotationChestLCollarY.RotateY(6.35) ;

	matrix9f RotationLCollarShoulderZ ;
	RotationLCollarShoulderZ.LoadIdentity() ; 
	RotationLCollarShoulderZ.RotateZ(-15.84) ;

	matrix9f RotationLCollarShoulderX ;
	RotationLCollarShoulderX.LoadIdentity() ; 
	RotationLCollarShoulderX.RotateX(-47.99) ;

	matrix9f RotationLCollarShoulderY ;
	RotationLCollarShoulderY.LoadIdentity() ; 
	RotationLCollarShoulderY.RotateY(-72.80) ;

	matrix9f RotationShoulderElbowZ ;
	RotationShoulderElbowZ.LoadIdentity() ; 
	RotationShoulderElbowZ.RotateZ(-102.01) ;

	matrix9f RotationShoulderElbowX ;
	RotationShoulderElbowX.LoadIdentity() ; 
	RotationShoulderElbowX.RotateX(-75.35) ;

	matrix9f RotationShoulderElbowY ;
	RotationShoulderElbowY.LoadIdentity() ; 
	RotationShoulderElbowY.RotateY(-115.95) ;

	matrix9f RotationElbowWristZ ;
	RotationElbowWristZ.LoadIdentity() ; 
	RotationElbowWristZ.RotateZ(15.03) ;

	matrix9f RotationElbowWristX ;
	RotationElbowWristX.LoadIdentity() ; 
	RotationElbowWristX.RotateX(-3.9) ;

	matrix9f RotationElbowWristY ;
	RotationElbowWristY.LoadIdentity() ; 
	RotationElbowWristY.RotateY(0.74) ;

	matrix9f RotationWristEndZ ;
	RotationWristEndZ.LoadIdentity() ; 
	RotationWristEndZ.RotateZ(7.44) ;

	matrix9f RotationWristEndX ;
	RotationWristEndX.LoadIdentity() ; 
	RotationWristEndX.RotateX(0.41) ;

	matrix9f RotationWristEndY ;
	RotationWristEndY.LoadIdentity() ; 
	RotationWristEndY.RotateY(-0.79) ;*/
	
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

	float angle=computeRotation(a,b,c);
	
vector3f angleVec = vector3f(angle,0,0) ;

	vector3f move1=angleVec-angle1;
	vector3f move2=angleVec-angle2;
	vector3f move3=angleVec-angle3;
   
    	ofstream flux("Take006.bvh",ios_base::app); // Flux d'ecriture
 

            if(flux) // Si le lieu de destination existe ( j'entend par la le dossier )
            {
                flux << move1.vertex[0]<<move1.vertex[1] <<move1.vertex[2]<<move2.vertex[0]<<move2.vertex[1]<<move2.vertex[2]<<move3.vertex[0]<<move3.vertex[1]<<move3.vertex[2]<< "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"<<endl; 						// On ecrit dans le fichier de destination
            }                          // Et au passage on le créer si il n'existe pas
            else
            {
                cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
            }
   
}







