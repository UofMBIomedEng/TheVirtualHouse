#include "skybox.h"

#include <stdio.h>  
#include <gl\gl.h>  
#include "glaux.h"

#define GL_TEXTURE_CUBE_MAP_ARB             0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB  0x851A

bool SKYBOX::Initialize()
{
	char* extensions = (char*) glGetString(GL_EXTENSIONS); 

	if(strstr(extensions, "GL_ARB_texture_cube_map") != NULL)
	{
		GLenum cube_map_target[6] = {           
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
		};

		AUX_RGBImageRec * texture_image[6];
		texture_image[0] = LoadBMP( "Media/sky/XN.bmp" );
		texture_image[1] = LoadBMP( "Media/sky/XP.bmp" );
		texture_image[2] = LoadBMP( "Media/sky/YN.bmp" );
		texture_image[3] = LoadBMP( "Media/sky/YP.bmp" );
		texture_image[4] = LoadBMP( "Media/sky/ZN.bmp" );
		texture_image[5] = LoadBMP( "Media/sky/ZP.bmp" );

		glGenTextures(1, &cube_map_texture_ID);

		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

		for (int i = 0; i < 6; i++)
		{
			if (texture_image[i])				
			{
				glTexImage2D(cube_map_target[i], 0, 3, texture_image[i]->sizeX, texture_image[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image[i]->data);

				if (texture_image[i]->data)	
				{
					free(texture_image[i]->data);	
				}
				free(texture_image[i]);	
			}
		}

	
		
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP );
		//glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
		return true;
	} 

	return false;
}

void SKYBOX::Render( float camera_yaw, float camera_pitch )
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB); 
	glDisable(GL_LIGHTING);

	glDepthMask(GL_FALSE);

	DrawSkyBox( camera_yaw, camera_pitch );

	glDepthMask(GL_TRUE);

	glDisable(GL_TEXTURE_CUBE_MAP_ARB); 
	glEnable(GL_LIGHTING);
}

void SKYBOX::Finalize()
{
	// Suppression de la skybox
	glDeleteTextures( 1, &cube_map_texture_ID );
}

void SKYBOX::DrawSkyBox( float camera_yaw, float camera_pitch )
{
	// Cube size
	float t = 1.5f;

	//use of the cube map texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	//setting the orientation
	glPushMatrix();
	glLoadIdentity();
	glRotatef( camera_pitch, 1.0f, 0.0f, 0.0f );
	glRotatef( camera_yaw, 0.0f, 1.0f, 0.0f );	
	

	// Rendering the geometry
	glBegin(GL_TRIANGLE_STRIP);			// X Negative	
		glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t); 	
		glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
		glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
		glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// X Positive
		glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
		glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
		glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
		glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Negative	
		glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
		glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
		glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
		glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Y Positive		
		glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
		glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
		glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
		glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Negative		
		glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
		glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
		glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
		glTexCoord3f(t,t,-t); glVertex3f(t,t,-t); 
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);			// Z Positive	
		glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
		glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
		glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
		glTexCoord3f(t,t,t); glVertex3f(t,t,t); 	
	glEnd();

	// Reinitialization of the the mode view matrix
	glPopMatrix();
}


AUX_RGBImageRec * SKYBOX::LoadBMP(char *Filename)  // Loading Bitmap
{
	FILE *File=NULL;                     

	if (!Filename)   
	{
		return NULL; 
	}

	File=fopen(Filename,"r");  

	if (File)                              
	{
		fclose(File);                    
		return auxDIBImageLoad(Filename);  
	}

	return NULL;  
}
