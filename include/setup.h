struct InterleavedVertex{
	float px,py,pz;	//Vertex
	float nx,ny,nz;	//Normal
	float tx,ty;	//Texcoord
};

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

char targ_char,pos_char;
const bool usevbo=1;
const bool usetileswhenrendering=1;

const int target_offset=3;
const int worldtilecount=max_number_tile;
const float worldtilesize=10;
const int streetlevel=2;
const int walllength=2;
int worldtileviewrange=50;
float target_x=0,target_y=0,target_z=0;
bool usejoystick=0;
bool calibjoy=1;
bool sound=1;
bool showinfo=1;
bool showsky=0;
bool testmode=0;
bool showplayer=0;
bool freecamera=0;
bool autoexit=0;
bool start_motion=0;
bool allocentric=0;
int judge_res=0;

int a_win_pos[4],b_win_pos[4],c_win_pos[4],d_win_pos[4];
int rand_sel;

float latswing=0,heightswing=0,swingtime=0;

JOYINFO joystick;

int targetwin=0;

float *worldtilevertexarray[worldtilecount][4];
float *worldtiletexturearray[worldtilecount];
float *worldtilenormalarray[worldtilecount][4];
int worldtilevertexcount[worldtilecount];
InterleavedVertex* worldtileinterleavedvertex[worldtilecount][4];
collisionmesh *worldtilecollisionmesh[worldtilecount][4];
GLuint worldtiletexture[worldtilecount];

GLuint wireframetexture;

/*
const int worldgridsizex = 50*5;
const int worldgridsizey = 25;
const int worldgridsizez = 50*5;
*/
const int worldgridsizex = 50;
const int worldgridsizey = 15;  //ceiling hight
const int worldgridsizez = 50;

char worldgrid[worldgridsizex][worldgridsizey][worldgridsizez][2];

/*float waterheight[worldgridsizex][worldgridsizez];
float waterscale=1;
bool waterdirection=0;*/

#include "gamespecific/entities.h"

float *entityvertexarray[entitytypecount];
float *entitytexturearray[entitytypecount];
float *entitynormalarray[entitytypecount];
int entityvertexcount[entitytypecount];
InterleavedVertex* entityinterleavedvertex[entitytypecount];
collisionmesh *entitycollisionmesh[entitytypecount];
GLuint entitytexture;

#include "gamespecific/genentities.h"

GLuint minimaptexture;
float minimaptexturexuse;
float minimaptexturezuse;

InterleavedVertex* visibleworldinterleavedvertex;
int visibleworldvertexcount=0;
GLuint visibleworldvbo;

float *playervertexarray;
float *playertexturearray;
float *playernormalarray;
int playervertexcount;
GLuint playertexture;

/*float *watervertexarray;
float *watertexturearray;
float *waternormalarray;
int watervertexcount;
GLuint watertexture;*/

int gameworldpolygons=0;

bool usetextures=1;
bool ghostmode=0;
float playerhight=5;

int collectablesfound=0;

float playerxpos,playerypos,playerzpos;
float playerxang,playeryang,playerzang;
float playerxposmov,playeryposmov,playerzposmov;
float playerxangmov,playeryangmov,playerzangmov;
bool playergrounded;
bool playerjumping;

int playerxgridpos,playerygridpos,playerzgridpos;

float playerframe;
float lastplayerframe;
float goalplayerframe;

//#include "gamespecific/tilenames.h"
#include "gamespecific/genworldgrid.h"
#include "gamespecific/genvisibleworld.h"
#include "gamespecific/genminimap.h"

void TestApp::setupmedia(){
	
	//generic reusable char array for filenames
	char filename[256];
	
	//load world tile meshes
	for(int a=0; a<worldtilecount; a++){
		//get the file name
		sprintf(filename,"%s%s%i%s",mediadir,"worldtiles/",a,".obj");
		//load the file
		
		loadobj((char*)filename,
			worldtilevertexarray[a][0],
			worldtiletexturearray[a],
			worldtilenormalarray[a][0],
			worldtilevertexcount[a],1.0);
		//set vertex positions for the alternate rotation
		for(int b=1; b<4; b++){
			worldtilevertexarray[a][b] = new float[worldtilevertexcount[a]*3];
			for(int c=0; c<worldtilevertexcount[a]; c++){
				float angle = b*90*radiansindegree;
				float tempposx=worldtilevertexarray[a][0][c*3+0];
				float tempposy=worldtilevertexarray[a][0][c*3+1];
				float tempposz=worldtilevertexarray[a][0][c*3+2];
				worldtilevertexarray[a][b][c*3+0] = tempposz*sin(angle)+tempposx*cos(angle);
				worldtilevertexarray[a][b][c*3+1] = tempposy;
				worldtilevertexarray[a][b][c*3+2] = tempposz*cos(angle)-tempposx*sin(angle);
			}
	
		}
		//set normals for the alternate rotation
		for(int b=1; b<4; b++){
			worldtilenormalarray[a][b] = new float[worldtilevertexcount[a]*3];
			for(int c=0; c<worldtilevertexcount[a]; c++){
				worldtilenormalarray[a][b][c*3+0]=worldtilenormalarray[a][0][c*3+0];
				worldtilenormalarray[a][b][c*3+1]=worldtilenormalarray[a][0][c*3+1];
				worldtilenormalarray[a][b][c*3+2]=worldtilenormalarray[a][0][c*3+2];
			}
		}
		//rig the texture coordinates
		if(usetileswhenrendering==0)for(int b=0; b<worldtilevertexcount[a]/3; b++){
			worldtiletexturearray[a][b*3*2+0]=0;
			worldtiletexturearray[a][b*3*2+1]=0;
			worldtiletexturearray[a][b*3*2+2]=1;
			worldtiletexturearray[a][b*3*2+3]=0;
			worldtiletexturearray[a][b*3*2+4]=0;
			worldtiletexturearray[a][b*3*2+5]=1;
		}
		//rig the normals
		for(int b=0; b<4; b++)for(int c=0; c<worldtilevertexcount[a]/3; c++){
			CVector3 g_vTriangle[3];
			g_vTriangle[0]=CVector3(
				worldtilevertexarray[a][b][c*9+0],
				worldtilevertexarray[a][b][c*9+1],
				worldtilevertexarray[a][b][c*9+2]);
			g_vTriangle[1]=CVector3(
				worldtilevertexarray[a][b][c*9+3],
				worldtilevertexarray[a][b][c*9+4],
				worldtilevertexarray[a][b][c*9+5]);
			g_vTriangle[2]=CVector3(
				worldtilevertexarray[a][b][c*9+6],
				worldtilevertexarray[a][b][c*9+7],
				worldtilevertexarray[a][b][c*9+8]);
			CVector3 vNormal = Normal(g_vTriangle);
			worldtilenormalarray[a][b][c*9+0]=-vNormal.x;//vert1
			worldtilenormalarray[a][b][c*9+1]=-vNormal.y;
			worldtilenormalarray[a][b][c*9+2]=-vNormal.z;
			worldtilenormalarray[a][b][c*9+3]=-vNormal.x;//vert2
			worldtilenormalarray[a][b][c*9+4]=-vNormal.y;
			worldtilenormalarray[a][b][c*9+5]=-vNormal.z;
			worldtilenormalarray[a][b][c*9+6]=-vNormal.x;//vert3
			worldtilenormalarray[a][b][c*9+7]=-vNormal.y;
			worldtilenormalarray[a][b][c*9+8]=-vNormal.z;
		}
		//create the interleaved vertex data
		for(int b=0; b<4; b++){
			worldtileinterleavedvertex[a][b] = new InterleavedVertex[worldtilevertexcount[a]];
			for(int c=0; c<worldtilevertexcount[a]; c++){
				worldtileinterleavedvertex[a][b][c].px=worldtilevertexarray[a][b][c*3+0];
				worldtileinterleavedvertex[a][b][c].py=worldtilevertexarray[a][b][c*3+1];
				worldtileinterleavedvertex[a][b][c].pz=worldtilevertexarray[a][b][c*3+2];
				worldtileinterleavedvertex[a][b][c].nx=worldtilenormalarray[a][b][c*3+0];
				worldtileinterleavedvertex[a][b][c].ny=worldtilenormalarray[a][b][c*3+1];
				worldtileinterleavedvertex[a][b][c].nz=worldtilenormalarray[a][b][c*3+2];
				worldtileinterleavedvertex[a][b][c].tx=worldtiletexturearray[a][c*2+0];
				worldtileinterleavedvertex[a][b][c].ty=worldtiletexturearray[a][c*2+1];
			}
		}
		//create the collission mesh
		for(int b=0; b<4; b++)worldtilecollisionmesh[a][b] = new collisionmesh(
			worldtilevertexcount[a],worldtilevertexarray[a][b]);
	}
	//load the textures
	if(usetileswhenrendering){
		for(int a=1; a<worldtilecount; a++){
			sprintf(filename,"%s%s%i%s",mediadir,"worldtiles/",a,".bmp");
			
			worldtiletexture[a]=loadbmp((char*)filename,1);
		}
		
	}

	//load world tile texture
	//sprintf(filename,"%s%s",mediadir,"worldtile.bmp");
	//wireframetexture=loadbmp((char*)filename,1);
	sprintf(filename,"%s%s",mediadir,"worldtile.tga");
	wireframetexture=loadtga((char*)filename,1);

	//load entity meshes
	for(int a=0; a<entitytypecount; a++){
		//get the file name
		sprintf(filename,"%s%s%i%s",mediadir,"entities/",a,".obj");
		//load the file
		loadobj((char*)filename,
			entityvertexarray[a],
			entitytexturearray[a],
			entitynormalarray[a],
			entityvertexcount[a],1.0);
		//rig the texture coordinates
		for(int b=0; b<entityvertexcount[a]/3; b++){
			entitytexturearray[a][b*3*2+0]=0;
			entitytexturearray[a][b*3*2+1]=0;
			entitytexturearray[a][b*3*2+2]=1;
			entitytexturearray[a][b*3*2+3]=0;
			entitytexturearray[a][b*3*2+4]=0;
			entitytexturearray[a][b*3*2+5]=1;
		}
		//rig the normals
		for(int b=0; b<entityvertexcount[a]/3; b++){
			CVector3 g_vTriangle[3];
			g_vTriangle[0]=CVector3(
				entityvertexarray[a][b*9+0],
				entityvertexarray[a][b*9+1],
				entityvertexarray[a][b*9+2]);
			g_vTriangle[1]=CVector3(
				entityvertexarray[a][b*9+3],
				entityvertexarray[a][b*9+4],
				entityvertexarray[a][b*9+5]);
			g_vTriangle[2]=CVector3(
				entityvertexarray[a][b*9+6],
				entityvertexarray[a][b*9+7],
				entityvertexarray[a][b*9+8]);
			CVector3 vNormal = Normal(g_vTriangle);
			entitynormalarray[a][b*9+0]=-vNormal.x;//vert1
			entitynormalarray[a][b*9+1]=-vNormal.y;
			entitynormalarray[a][b*9+2]=-vNormal.z;
			entitynormalarray[a][b*9+3]=-vNormal.x;//vert2
			entitynormalarray[a][b*9+4]=-vNormal.y;
			entitynormalarray[a][b*9+5]=-vNormal.z;
			entitynormalarray[a][b*9+6]=-vNormal.x;//vert3
			entitynormalarray[a][b*9+7]=-vNormal.y;
			entitynormalarray[a][b*9+8]=-vNormal.z;
		}
		//create the interleaved vertex data
		entityinterleavedvertex[a] = new InterleavedVertex[entityvertexcount[a]];
		for(int b=0; b<entityvertexcount[a]; b++){
			entityinterleavedvertex[a][b].px=entityvertexarray[a][b*3+0];
			entityinterleavedvertex[a][b].py=entityvertexarray[a][b*3+1];
			entityinterleavedvertex[a][b].pz=entityvertexarray[a][b*3+2];
			entityinterleavedvertex[a][b].nx=entitynormalarray[a][b*3+0];
			entityinterleavedvertex[a][b].ny=entitynormalarray[a][b*3+1];
			entityinterleavedvertex[a][b].nz=entitynormalarray[a][b*3+2];
			entityinterleavedvertex[a][b].tx=entitytexturearray[a][b*2+0];
			entityinterleavedvertex[a][b].ty=entitytexturearray[a][b*2+1];
		}
		//create the collission mesh
		entitycollisionmesh[a] = new collisionmesh(
			entityvertexcount[a],entityvertexarray[a]);
	}

	//load player mesh
	sprintf(filename,"%s%s",mediadir,"player.ms3d");
	loadms3d(filename,
		playerms3dmodel,
		playervertexarray,
		playertexturearray,
		playernormalarray,
		playervertexcount,1.0);

	//rig the texture coordinates
	for(int b=0; b<playervertexcount/3; b++){
		playertexturearray[b*3*2+0]=0;
		playertexturearray[b*3*2+1]=0;
		playertexturearray[b*3*2+2]=1;
		playertexturearray[b*3*2+3]=0;
		playertexturearray[b*3*2+4]=0;
		playertexturearray[b*3*2+5]=1;
	}

	//load water mesh
	/*sprintf(filename,"%s%s",mediadir,"water.obj");
	loadobj((char*)filename,
		watervertexarray,
		watertexturearray,
		waternormalarray,
		watervertexcount,1);
	//rig the texture coordinates
	for(int b=0; b<watervertexcount/3; b++){
		watertexturearray[b*3*2+0]=0;
		watertexturearray[b*3*2+1]=0;
		watertexturearray[b*3*2+2]=1;
		watertexturearray[b*3*2+3]=0;
		watertexturearray[b*3*2+4]=0;
		watertexturearray[b*3*2+5]=1;
	}
	//rig the normals
	for(int c=0; c<watervertexcount/3; c++){
		CVector3 g_vTriangle[3];
		g_vTriangle[0]=CVector3(
			watervertexarray[c*9+0],
			watervertexarray[c*9+1],
			watervertexarray[c*9+2]);
		g_vTriangle[1]=CVector3(
			watervertexarray[c*9+3],
			watervertexarray[c*9+4],
			watervertexarray[c*9+5]);
		g_vTriangle[2]=CVector3(
			watervertexarray[c*9+6],
			watervertexarray[c*9+7],
			watervertexarray[c*9+8]);
		CVector3 vNormal = Normal(g_vTriangle);
		waternormalarray[c*9+0]=-vNormal.x;//vert1
		waternormalarray[c*9+1]=-vNormal.y;
		waternormalarray[c*9+2]=-vNormal.z;
		waternormalarray[c*9+3]=-vNormal.x;//vert2
		waternormalarray[c*9+4]=-vNormal.y;
		waternormalarray[c*9+5]=-vNormal.z;
		waternormalarray[c*9+6]=-vNormal.x;//vert3
		waternormalarray[c*9+7]=-vNormal.y;
		waternormalarray[c*9+8]=-vNormal.z;
	}*/

}

void TestApp::setupgame(){

	//setup the world grid
	worldgrid[0][0][0][0]=99;
//	loadworldgrid();
	bool newworld=0;
	if(worldgrid[0][0][0][0]==99){
		genworldgrid();
		//saveworldgrid();
		newworld=1;
	}

	//setup the player, entities and other info
	playerypos=-9001;
//	load();
	if(playerypos==-9001 || newworld==1){
		genentities();
		usetextures=1;
		ghostmode=0;
		collectablesfound=0;

		/*
		playerxpos=worldgridsizex*worldtilesize/4;     //Player startpoint
		playerypos=streetlevel*worldtilesize;
		playerzpos=worldgridsizez*worldtilesize/2;
		*/

		/*
		switch(rand()%3){
			case 0:
				playerxpos=worldtilesize*1;     //Central door entrance
				playerypos=worldtilesize*2;
				playerzpos=worldtilesize*15;
				playeryang=0;
				break;
			case 1:
				playerxpos=worldtilesize*5;    //Western door entrance
				playerypos=worldtilesize*2;
				playerzpos=worldtilesize*1;
				playeryang=90*radiansindegree;
				break;
			case 2:
				playerxpos=worldtilesize*5;     //Eastern door entrance
				playerypos=worldtilesize*2;
				playerzpos=worldtilesize*28;
				playeryang=270*radiansindegree;
				break;
		}*/

		playerxpos=(worldtilesize*worldgridsizex/2)-((worldtilesize*worldgridsizex/3));     //Player startpoint
		playerypos=(streetlevel-0.45)*worldtilesize;
		playerzpos=(worldtilesize*worldgridsizex/2);

		playerxang=0;
		playeryang=0;
		playerzang=0;

		playerxposmov=0;
		playeryposmov=0;
		playerzposmov=0;
		playerxangmov=0;
		playeryangmov=0;
		playerzangmov=0;
		playergrounded=0;
		playerjumping=0;
		playerxgridpos=(int)((playerxpos+worldtilesize*0.5)/worldtilesize);
		playerygridpos=(int)((playerypos+worldtilesize*0.5)/worldtilesize);
		playerzgridpos=(int)((playerzpos+worldtilesize*0.5)/worldtilesize);
		playerframe=3;
		lastplayerframe=3;
		goalplayerframe=4;
		camxpos=worldgridsizex*worldtilesize/2;
		camypos=streetlevel*worldtilesize;
		camzpos=worldgridsizez*worldtilesize/2;
		camxang=0;
		camyang=playeryang+(90*radiansindegree);
		camzang=0;
		camxposmov=0;
		camyposmov=0;
		camzposmov=0;
		camxangmov=0;
		camyangmov=0;
		camzangmov=0;
		//save();
	}

	//setup water
	/*for(int x=0;x<worldgridsizex;x++)
	for(int z=0;z<worldgridsizez;z++)
	waterheight[x][z]=(float)streetlevel*(float)worldtilesize;*/

	//generate the visible world
	if(!usetileswhenrendering)genvisibleworld();

	//generate the mini map
	minimaptexture=genminimap();

}
