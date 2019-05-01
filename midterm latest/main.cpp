
/////////////////////////////////////////////////////////
//NOTE:
//// move right and left using right and left arrow keys
//// look up and down using up and down arrow keys
//// move forward using 'w' key 
//// move backward using 's' key
/////////////////////////////////////////////////////////



////MAKE ZOOM IN AND OUT WORK --make sure I can't zoom in the up/down directions
//randomly call diff. scenes?
//change background (image is in folder under "mountains")

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;

#include "Angel.h";
#include <GL/glew.h> // for OpenGL extensions
#include <GL/glut.h> // for Glut utility kit
#include "texture.h" // for the bitmap texture loader

// Global Projection Matrices
mat4 projection, modelview, translate;  

#include "GraphicsObject.h"
#include "SkyBox.h"
#include "Brick.h"
#include "tree.h"
#include "Zebra.h"


GLfloat  zoom = 0.0;         // Translation factor
vec4 view(0.0, 0.0, -2.0, 0.0);

GLfloat  fovy = 60.0;		 // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect = 1.0;       // Viewport aspect ratio
GLfloat  zNear = 0.01, zFar = 1000.0;

GLfloat dir = 1.0;
GLfloat theta[] = {0.0,0.0,0.0};
GLint axis = 1;



// THE global SkyBox Object
SkyBox go_skybox;

// The objects
Brick go_brick_1;
Brick go_brick_2;
tree go_tree_1;
Zebra go_zebra_2;
point4  eye(0.0, 0.0, 1.0, 1.0);
point4  at(0.0, 0.0, -1.0, 1.0);
vec4    up(0.0, 1.0, 0.0, 0.0);

void display( void )
{
	static float angle = 0.0;

	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  /*clear the window */

	projection = Perspective(fovy, aspect, zNear, zFar);
	modelview = Translate(0.0, 0.0, 1.0)*LookAt(eye, at, up);

	// tell the skybox to draw its vertex
	go_skybox.draw( theta );
	go_skybox.draw1(theta); 
	go_skybox.draw2(theta);



								
	// tell the bricks to draw themselves and rotate too!
	go_brick_1.draw( theta, vec3(0.0,0.0,0.0) );
   	go_brick_2.draw( theta, vec3(1.0,0.0,0.0) );
	go_zebra_2.draw( theta, vec3(1.0,0.0,0.0) );

	go_brick_1.draw1(theta, vec3(0, 0, 0));
	go_brick_2.draw1(theta, vec3(1.5, 0.0, 1));
	go_zebra_2.draw1(theta, vec3(2.0, 0.0, 0.0));

	go_brick_1.draw2(theta, vec3(0, 0, 0));
	go_brick_2.draw2(theta, vec3(2.5, 0.0, 1));
	go_zebra_2.draw2(theta, vec3(3.0, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1.75, 0, 1));
	go_zebra_2.draw3(theta, vec3(2.5, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(3.2, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.5, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(2.48, 0, 1));
	go_zebra_2.draw3(theta, vec3(2.5, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.5, 1, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(0, 0, 1));
	go_zebra_2.draw3(theta, vec3(3, 1, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(2.75, 0, 1));
	go_zebra_2.draw3(theta, vec3(1, 2, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1.75, 0, 1));
	go_zebra_2.draw3(theta, vec3(1.75, 2, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(2.75, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.3, 2, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1, 0, 1));
	go_zebra_2.draw3(theta, vec3(1, 2, 0.0));


	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1.5, 0, 1));
	go_zebra_2.draw3(theta, vec3(2, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1.5, 0, 1));
	go_zebra_2.draw3(theta, vec3(1, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(3, 0, 1));
	go_zebra_2.draw3(theta, vec3(0, 1, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(0, 0, 1));
	go_zebra_2.draw3(theta, vec3(2.5, 1, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(2.75, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.5, 2, 0.0));

	go_brick_1.draw1(theta, vec3(0, 0, 0));
	go_brick_2.draw1(theta, vec3(3, 0.0, 1));
	go_zebra_2.draw1(theta, vec3(2.0, 0.0, 0.0));

	go_brick_1.draw2(theta, vec3(0, 0, 0));
	go_brick_2.draw2(theta, vec3(3.2, 0.0, 1));
	go_zebra_2.draw2(theta, vec3(2.75, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(0.5, 0, 1));
	go_zebra_2.draw3(theta, vec3(2, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.5, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(5, 0, 1));
	go_zebra_2.draw3(theta, vec3(4, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(5, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.5, 0.5, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(3, 0, 3));
	go_zebra_2.draw3(theta, vec3(3, 3, 0.0));


	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(0.5, 0, 2));
	go_zebra_2.draw3(theta, vec3(2, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1, 0, 1));
	go_zebra_2.draw3(theta, vec3(0.5, 0.0, 0.0));


	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(5, 0, 1.5));
	go_zebra_2.draw3(theta, vec3(4, 0.0, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(5, 0, 0.5));
	go_zebra_2.draw3(theta, vec3(0.5, 0.5, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1.75, 0, 0));
	go_zebra_2.draw3(theta, vec3(1.75, 2, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(2.75, 0, 0.75));
	go_zebra_2.draw3(theta, vec3(0.3, 2, 0.0));

	go_brick_1.draw3(theta, vec3(0, 0, 0));
	go_brick_2.draw3(theta, vec3(1, 0, 1.2));
	go_zebra_2.draw3(theta, vec3(1, 2, 0.0));

	go_brick_1.draw(theta, vec3(0.0, 0.0, 0.0));
	go_brick_2.draw(theta, vec3(1.0, 0.0, 0.0));
	go_zebra_2.draw(theta, vec3(2.0, 0.0, 0.0));

	// XXX NEW XXX
	go_brick_1.draw1(theta, vec3(0, 0, 0));
	go_brick_2.draw1(theta, vec3(1.5, 0.0, 2));
	go_zebra_2.draw1(theta, vec3(2.0, 0.0, 0.0));





	angle += 0.5;
	if( angle > 360.0 ) angle -= 360.0;

	go_tree_1.draw( vec3(0.0,angle,0.0), vec3(-1.0,0.0,0.0) );
	go_tree_1.draw1(vec3(0.0, angle, 0.0), vec3(-1.0, 0.0, 0.0));
	go_tree_1.draw2(vec3(0.0, angle, 0.0), vec3(-1.0, 0.0, 0.0));
	go_tree_1.draw3(vec3(0.0, angle, 0.0), vec3(-1.0, 0.0, 0.0));

	// swap the buffers
	glutSwapBuffers();

	glutPostRedisplay();
}

bool CheckCollision(point4 eye1)
{
	if (go_brick_1.CheckCollision(eye1) == true)
	{
		return true;
	}
	else { return false; }
}

void arrowKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) //look up--doesn't allow you to look past straight up/down (no sommersaults)
	{
		at.y += .5;
	}
	if (key == GLUT_KEY_DOWN) //look down
	{
		at.y -= .5;
	}
	if (key == GLUT_KEY_RIGHT) //turn right
	{
		view = RotateY(-5) * view;//rotate eye -5 degrees
		at = eye + view;
	}
	if (key == GLUT_KEY_LEFT) //turn left
	{
		view = RotateY(5) * view;//rotate eye 5 degrees
		at = eye + view;
	}
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{	
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)	axis = 1;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	glutPostRedisplay();
}

void mouse_move( int x, int y )
{
	double dx = 0.01*(250 - x);
	double dy = 0.01*(250 - y);

	//rotate eye dx degrees
	view = RotateY(dx) * view;
	at = eye + view;
	// rotate eye dy direction
	at.y -= dy; 
	
	//glutWarpPointer(250, 250); // goes back to center 


}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
	aspect =  GLfloat (w) / h;
}

void key(unsigned char key, int x, int y) //MAKE ZOOM IN AND OUT WORK
{
	if (key == 'w')//move forward (zoom)
	{
		eye = eye + 0.25*view;
		at = at + 0.25*view;
	}

	if (key == 's')//move backward (zoom)
	{
		eye = eye - 0.25*view;
		at = at - 0.25*view;
	}

    if(key == 'q') exit(0);
	glutPostRedisplay();
}

void init_gl()
{
	glEnable(GL_DEPTH_TEST);
}

void init()
{   
	init_gl();			    // Setup general OpenGL stuff of the object //could do all of this by creating  skybox.init function that does all 5 things

	go_skybox.init_data();	        // Setup the data for the this object
	go_skybox.init_VAO();           // Initialize the vertex array object for this object
	go_skybox.init_VBO();			// Initialize the data buffers for this object
	go_skybox.init_shader();		// Initialize the shader objects and textures for skybox
	go_skybox.init_texture_map();	// Initialize the texture map for this object
	
	go_brick_1.init_data();	        // Setup the data for the skybox object
	go_brick_1.init_VAO();          // Initialize the vertex array object for this object
	go_brick_1.init_VBO();			// Initialize the data buffers for this object
	go_brick_1.init_shader();		// Initialize the shader objects and textures for skybox
	go_brick_1.init_texture_map();	// Initialize the texture map for this object

	go_brick_2.init_data();	        // Setup the data for the skybox object
	go_brick_2.init_VAO();          // Initialize the vertex array object for this object
	go_brick_2.init_VBO();			// Initialize the data buffers for this object
	go_brick_2.init_shader();		// Initialize the shader objects and textures for skybox
	go_brick_2.init_texture_map();	// Initialize the texture map for this object
	
	go_tree_1.init_data();	    // Setup the data for the skybox object
	go_tree_1.init_VAO();        // Initialize the vertex array object for this object
	go_tree_1.init_VBO();		// Initialize the data buffers for this object
	go_tree_1.init_shader();		// Initialize the shader objects and textures for skybox
	go_tree_1.init_texture_map();// Initialize the texture map for this object

	go_zebra_2.init_data();	        // Setup the data for the skybox object
	go_zebra_2.init_VAO();          // Initialize the vertex array object for this object
	go_zebra_2.init_VBO();			// Initialize the data buffers for this object
	go_zebra_2.init_shader();		// Initialize the shader objects and textures for skybox
	go_zebra_2.init_texture_map();	// Initialize the texture map for this object


	view = RotateY(15) * view;//rotate eye 30 degrees
	at = eye + view;

	GL_CHECK_ERRORS
}

void OnShutdown()
{
	go_skybox.cleanup(); // release the textures on the graphics card
}

void checkGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		cerr<<"Error: " << glewGetErrorString(err)<<endl;
	} else {
		if (GLEW_VERSION_3_3)
		{
			cout<<"Driver supports OpenGL 3.3\nDetails:"<<endl;
		}
	}
	cout<<"Using GLEW "<<glewGetString(GLEW_VERSION)<<endl;
	cout<<"Vendor: "<<glGetString (GL_VENDOR)<<endl;
	cout<<"Renderer: "<<glGetString (GL_RENDERER)<<endl;
	cout<<"Version: "<<glGetString (GL_VERSION)<<endl;
	cout<<"GLSL: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<endl;
}

int main(int argc, char **argv)
{
	atexit(OnShutdown);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow( "SkyBox" );


	checkGlew();
    init();
    glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutSpecialFunc(arrowKey);
	//glutIdleFunc(arrowKey);       // set in key press
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouse_move);   // Called when mouse moves with a mouse button pressed
    glutKeyboardFunc(key);


	cout << "*****************************************************" << endl;
	cout << "*   a moves forward" << endl;
	cout << "*   s moves backward" << endl;
	cout << "*   left arrow key rotates view left" << endl;
	cout << "*   right arrow key rotates view right" << endl;
	cout << "*****************************************************" << endl;

    glutMainLoop();

    return 0;
}



// TO DO: COLLITION --- update user location by finding the radius of cube and subtrafcting it with current location. 
//                  ---if negative it has collided 
//					---if positive good
//					---so basically just make sure Pcurrent-Pradius is alwasy positive ! 

//					---- have bricks in an array so that you can loop through them to implement the collision function\
//q					