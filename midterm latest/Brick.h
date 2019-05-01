#ifndef BRICK_BOX_H
#define BRICK_BOX_H
#include "GraphicsObject.h"



// Data vertex for the brick
point4  brick_vertices[8] = {
	point4(-0.5,-0.5,0.5, 1.0),
	point4(0.5,-0.5,0.5, 1.0), 
	point4(0.5,0.5,0.5, 1.0), 
	point4(-0.5,0.5,0.5, 1.0),  
	point4(-0.5,-0.5,-0.5, 1.0),
	point4(0.5,-0.5,-0.5, 1.0),
	point4(0.5,0.5,-0.5, 1.0), 
	point4(-0.5,0.5,-0.5, 1.0)
};

class Brick : public graphics_object
{
public:
	vec3 p;
	GLfloat scale = 3.0; // scale of brick 


	Brick() : graphics_object("SkyCube") {}
	
	void triangle( unsigned int a, unsigned int b, unsigned int c )
	{	 // For this texture map, the normal are set to
		 // normalized versions of the vertice itself
		 normal.push_back( normalize(vec4to3(brick_vertices[a])) );
		 vertex.push_back( brick_vertices[a] );

		 normal.push_back( normalize(vec4to3(brick_vertices[b])) );
		 vertex.push_back( brick_vertices[b] );

		 normal.push_back( normalize(vec4to3(brick_vertices[c])) );
		 vertex.push_back( brick_vertices[c] );
	}

	void quad(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
	{	 triangle( a, b, c );
		 triangle( a, c, d );
	}

	void init_data()
	{  quad(1,5,6,2);
	   quad(4,0,3,7);
	   quad(3,2,6,7);
	   quad(4,5,1,0);
	   quad(0,1,2,3);
	   quad(5,4,7,6);
	}

	// Call first at setup
	void init_VAO()
	{
		// Init the VAO for this object on the graphics card
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GL_CHECK_ERRORS
	}

	// Call second at setup
	void init_VBO()
	{
		// Generate 2 buffers, one for the vertex, one for the normal
		glGenBuffers(2, buffers);

		// Initialize a buffer data object of all the vertex
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * vertex.size(), &(vertex[0]), GL_STATIC_DRAW);

		// Initialize a buffer data object of all the normals
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * normal.size(), &(normal[0]), GL_STATIC_DRAW);
		GL_CHECK_ERRORS

	}

	// Call third at setup
	void init_shader() 
	{
		program  = InitShader("vshader72.glsl", "fshader72.glsl");
		glUseProgram(program);
		uniforms[0] = glGetAttribLocation(program, "vPosition");
		GL_CHECK_ERRORS
		uniforms[1] = glGetAttribLocation(program, "Normal");
		GL_CHECK_ERRORS
		uniforms[2] = glGetUniformLocation( program, "ModelView" );
		GL_CHECK_ERRORS
		uniforms[3] = glGetUniformLocation( program, "Projection" );	
		GL_CHECK_ERRORS

		glEnableVertexAttribArray(uniforms[0]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glVertexAttribPointer(uniforms[0], 4, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 4, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

		glEnableVertexAttribArray(uniforms[1]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glVertexAttribPointer(uniforms[1], 4, GL_FLOAT, GL_TRUE, sizeof(GLfloat) * 4, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS
	}

	// Called forth at setup to go forth and conquer textures
	void init_texture_map()
	{
		glGenTextures(1, &tex);
		glActiveTexture(this_texture);

		glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		int TexRight = MyLoadCubeMapBitmap("Brick\\brick.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		int TexLeft = MyLoadCubeMapBitmap("Brick\\brick.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		int TexTop = MyLoadCubeMapBitmap("Brick\\brick.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		int TexBottom = MyLoadCubeMapBitmap("Brick\\brick.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		int TexFront = MyLoadCubeMapBitmap("Brick\\brick.bmp", GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		int TexBack = MyLoadCubeMapBitmap("Brick\\brick.bmp", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

		texMapLocation = glGetUniformLocation(program, "texMap");
		glUniform1i(texMapLocation, tex);

		GL_CHECK_ERRORS
	}

	// Called from draw to attach to VAO and draw the object
	void start_shader( )
	{
		glBindVertexArray(vao);
		glUseProgram(program);

		glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(this_texture);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GL_CHECK_ERRORS
	}

	// Called from draw to stop drawing the object
	void stop_shader()
	{	glUseProgram(0);
		glBindVertexArray( 0 );
		GL_CHECK_ERRORS
	}

	void draw ( GLfloat theta[], vec3 translate ) 
	{
		start_shader();
			
			// ship down the new the projection and viewing matrices
	        glUniformMatrix4fv(uniforms[2], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5,0.5,0.5) * RotateZ(theta[0]) * RotateX(theta[1]) * RotateY(theta[1]) );
			GL_CHECK_ERRORS
	        
			glUniformMatrix4fv( uniforms[3], 1, GL_TRUE, projection );
			GL_CHECK_ERRORS
			
			glDrawArrays( GL_TRIANGLES, 0,  vertex.size() ); 
			GL_CHECK_ERRORS

		stop_shader();
	}

	//	// XXX NEW XXX
	void draw1(GLfloat theta[], vec3 translate)
	{
		start_shader();

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[2], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[0]) * RotateX(theta[1]) * RotateY(theta[1]));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[3], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, vertex.size());
		GL_CHECK_ERRORS

			stop_shader();
	}
	void draw2(GLfloat theta[], vec3 translate)
	{
		start_shader();

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[2], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[0]) * RotateX(theta[1]) * RotateY(theta[1]));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[3], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, vertex.size());
		GL_CHECK_ERRORS

			stop_shader();
	}

	void draw3(GLfloat theta[], vec3 translate)
	{
		start_shader();

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[2], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[0]) * RotateX(theta[1]) * RotateY(theta[1]));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[3], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, vertex.size());
		GL_CHECK_ERRORS

			stop_shader();
	}

	vec3 getPosition()
	{
		return p;
	}


	bool CheckCollision(point4 eye1)
	{
		//  update user location by finding the radius of cube and subtrafcting it with current location. 
		//  if negative it has collided 
		//	if positive good
		// so basically just make sure Pcurrent-Pradius is alwasy positive ! 

		vec3 position = getPosition();
		vec3 eye2 = vec4to3(eye1);

		
		GLfloat dist = sqrtf(pow(p.x - eye2.x, 2) + //(positionAtX-EyeatX)^2
							pow(p.y - eye2.y, 2) +// (positionAtY-EyeatY)^2 
							pow(p.z - eye2.z, 2)); //(positionAtZ-EyeatZ)^2 


		if (dist <= 1)
		{
			return true;
		}
		return false;
	}

	
	void cleanup() 
	{ 
		glDeleteProgram(program);
		glDeleteTextures(1, &tex );
		glDeleteBuffers(3, buffers);
		glDeleteVertexArrays(1, &vao);
	}

	// whenever user moves to update position uyou use the thing he gave us 


};
#endif