#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "glaux.h"


//#pragma comment(lib,"GLaux.lib")

class SKYBOX
{
public:
	SKYBOX(){}
	~SKYBOX(){}

	bool Initialize();
	void Render( float camera_yaw, float camera_pitch );
	void Finalize();

private:
	void DrawSkyBox( float camera_yaw, float camera_pitch );

	AUX_RGBImageRec * LoadBMP( char * file );

	GLuint cube_map_texture_ID;
};

#endif