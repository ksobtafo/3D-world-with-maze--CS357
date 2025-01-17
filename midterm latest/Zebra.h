#ifndef Zebra_BOX_H
#define Zebra_BOX_H
#include "GraphicsObject.h"

extern GLint angleID;

// Data vertex for the zebra
point4  Zebra_vertices[8] = {
	// Quad 1
	point4( -1.0,  1.0, 0.0, 1.0 ),
	point4(  1.0,  1.0, 0.0, 1.0 ),
	point4(  1.0,  -1.0, 0.0, 1.0 ),
	point4( -1.0,  -1.0, 0.0, 1.0 ),
	// Quad 2
	point4(  0.0,  1.0,  -1.0, 1.0 ),
	point4(  0.0,  1.0,   1.0, 1.0 ),
	point4(  0.0, -1.0,   1.0, 1.0 ),
	point4(  0.0, -1.0,  -1.0, 1.0 ),
};

// RGBA colors
color4 Z_vertex_colors[4] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
};

// Set up points for the quad as 8 triangles
point4 Zebra_points[12] = { 
	Zebra_vertices[0] , Zebra_vertices[2],  Zebra_vertices[1] ,  // Triangle #1
	Zebra_vertices[3] , Zebra_vertices[2],  Zebra_vertices[0] ,   // Triangle #2
	Zebra_vertices[4] , Zebra_vertices[6],  Zebra_vertices[5] ,  // Triangle #3
	Zebra_vertices[7] , Zebra_vertices[6],  Zebra_vertices[4]    // Triangle #4
};


// Set up colors for the quad as colors for both triangles vertices
color4 Z_colors[12] = {
	// Colors for Triangle #1 vertices
	Z_vertex_colors[0], Z_vertex_colors[1], Z_vertex_colors[2], 
	// Colors for Triangle #2 vertices
	Z_vertex_colors[0], Z_vertex_colors[2], Z_vertex_colors[3], 
	// Colors for Triangle #3 vertices
	Z_vertex_colors[0], Z_vertex_colors[1], Z_vertex_colors[2], 
	// Colors for Triangle #4 vertices
	Z_vertex_colors[0], Z_vertex_colors[2], Z_vertex_colors[3]
};


vec2 Z_mapcoords[12] = { 
	vec2(0.0,1.0), vec2(0.5,0.0), vec2(0.5,1.0),  // Triangle #5
	vec2(0.0,0.0), vec2(0.5,0.0), vec2(0.0,1.0),  // Triangle #6
	vec2(0.0,1.0), vec2(0.5,0.0), vec2(0.5,1.0),  // Triangle #5
	vec2(0.0,0.0), vec2(0.5,0.0), vec2(0.0,1.0)  // Triangle #6

};


class Zebra : public graphics_object
{
public:
	Zebra() : graphics_object("Zebra") {}
	
	void init_data()
	{
	}

	void init_VAO()
	{
		// Init the VAO for this object on the graphics card
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GL_CHECK_ERRORS
	}

	void init_VBO()
	{
		// Generate 6 buffers, on for modelview, one for projections,  one for the poositions, one for the color and one for map coords one for angle
		glGenBuffers(3, buffers);

	}

	void init_shader() 
	{
		program  = InitShader("vshader32.glsl", "fshader32.glsl");
		glUseProgram( program );
		GL_CHECK_ERRORS
		uniforms[0] = glGetAttribLocation(program, "vPosition");	
		uniforms[1] = glGetAttribLocation( program, "vColor" ); 
		uniforms[2] = glGetAttribLocation( program, "vMapCoord" ); 
		uniforms[3] = glGetUniformLocation( program, "angle" );
		uniforms[4] = glGetUniformLocation( program, "ModelView" );
		uniforms[5] = glGetUniformLocation( program, "Projection" );
		GL_CHECK_ERRORS


		// Buffer for the points
		glEnableVertexAttribArray(uniforms[0]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Zebra_points), &(Zebra_points[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(uniforms[0], 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

		// Buffer for the colors
		glEnableVertexAttribArray(uniforms[1]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Z_colors), &(Z_colors[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(uniforms[1], 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

		// Buffer for the mapcoord
		glEnableVertexAttribArray(uniforms[2]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Z_mapcoords), &(Z_mapcoords[0]), GL_STATIC_DRAW);
		glVertexAttribPointer(uniforms[2], 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		GL_CHECK_ERRORS

		// Send down the initial angle
		glUniform1f(uniforms[3], 0.0f);
	}

	void init_texture_map()
	{
		glActiveTexture(this_texture);
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		int TreeTex = MyLoadBitmap("zebra.bmp", GL_TEXTURE_2D, true);
		GL_CHECK_ERRORS

		texMapLocation = glGetUniformLocation(program, "texMap");
		glUniform1i(texMapLocation, tex);

		GL_CHECK_ERRORS
	}

	void start_shader( )
	{	
		glBindVertexArray(vao);
		glUseProgram(program);

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(this_texture);
		glBindTexture(GL_TEXTURE_2D, tex);

	    glEnable(GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    // Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
	    glAlphaFunc ( GL_GREATER, 0.1 ) ;
        glEnable ( GL_ALPHA_TEST ) ;

	    // Initialize Z-Buffering
	    glEnable(GL_DEPTH_TEST);
	
	}

	void stop_shader()
	{	glUseProgram(0);
		glBindVertexArray( 0 );
		GL_CHECK_ERRORS
	}



	void draw ( GLfloat theta[], vec3 translate ) 
	{
		// Initialize Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
		glAlphaFunc ( GL_GREATER, 0.1 ) ;
		glEnable ( GL_ALPHA_TEST ) ;

		// Initialize Z-Buffering
		glEnable(GL_DEPTH_TEST);
	
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
		GL_CHECK_ERRORS
		start_shader();
			
			// ship down the new the projection and viewing matrices
	        glUniformMatrix4fv(uniforms[4], 1, GL_TRUE, modelview * Translate(translate) * Scale( 0.5, 0.5, 0.5) * RotateZ(theta[2]) * RotateY(theta[1]) * RotateX(theta[0]) );
			GL_CHECK_ERRORS
	        
			glUniformMatrix4fv( uniforms[5], 1, GL_TRUE, projection );
			GL_CHECK_ERRORS
			
			glDrawArrays( GL_TRIANGLES, 0,  sizeof(Zebra_points)/3  );    // draw the points
			GL_CHECK_ERRORS

		stop_shader();
	}

	// XXX NEW XXX
	void draw1(GLfloat theta[], vec3 translate)
	{
		// Initialize Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
		glAlphaFunc(GL_GREATER, 0.1);
		glEnable(GL_ALPHA_TEST);

		// Initialize Z-Buffering
		glEnable(GL_DEPTH_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GL_CHECK_ERRORS
			start_shader();

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[4], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[2]) * RotateY(theta[1]) * RotateX(theta[0]));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[5], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, sizeof(Zebra_points) / 3);    // draw the points
		GL_CHECK_ERRORS

			stop_shader();
	}
	
	void draw2(GLfloat theta[], vec3 translate)
	{
		// Initialize Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
		glAlphaFunc(GL_GREATER, 0.1);
		glEnable(GL_ALPHA_TEST);

		// Initialize Z-Buffering
		glEnable(GL_DEPTH_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GL_CHECK_ERRORS
			start_shader();

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[4], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[2]) * RotateY(theta[1]) * RotateX(theta[0]));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[5], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, sizeof(Zebra_points) / 3);    // draw the points
		GL_CHECK_ERRORS

			stop_shader();
	}
	void draw3(GLfloat theta[], vec3 translate)
	{
		// Initialize Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Prevent alpha values of less than 0.1 from writing out the the depth test buffer.
		glAlphaFunc(GL_GREATER, 0.1);
		glEnable(GL_ALPHA_TEST);

		// Initialize Z-Buffering
		glEnable(GL_DEPTH_TEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GL_CHECK_ERRORS
			start_shader();

		// ship down the new the projection and viewing matrices
		glUniformMatrix4fv(uniforms[4], 1, GL_TRUE, modelview * Translate(translate) * Scale(0.5, 0.5, 0.5) * RotateZ(theta[2]) * RotateY(theta[1]) * RotateX(theta[0]));
		GL_CHECK_ERRORS

			glUniformMatrix4fv(uniforms[5], 1, GL_TRUE, projection);
		GL_CHECK_ERRORS

			glDrawArrays(GL_TRIANGLES, 0, sizeof(Zebra_points) / 3);    // draw the points
		GL_CHECK_ERRORS

			stop_shader();
	}
	void cleanup() 
	{ 
		glDeleteProgram(program);
		glDeleteTextures(1, &tex );
		glDeleteBuffers(3, buffers);
		glDeleteVertexArrays(1, &vao);
	}


};
#endif