GLuint fonttexture;
float fonttexturecoords[96][8];

void setuptext(){
	char filename[256];
	sprintf(filename,"%s%s",mediadir,"font.tga");
	fonttexture=loadtga((char*)filename,0);
	for(int y=0; y<6; y++)for(int x=0; x<16; x++){//setup the pixel positions
		fonttexturecoords[16*y+x][0]=x*32+1;
		fonttexturecoords[16*y+x][1]=y*42+42-1;
		fonttexturecoords[16*y+x][2]=x*32+32-1;
		fonttexturecoords[16*y+x][3]=y*42+42-1;
		fonttexturecoords[16*y+x][4]=x*32+32-1;
		fonttexturecoords[16*y+x][5]=y*42+1;
		fonttexturecoords[16*y+x][6]=x*32+1;
		fonttexturecoords[16*y+x][7]=y*42+1;
	}
	for(int a=0; a<96; a++){//scale it for the texture and flip it
		fonttexturecoords[a][0]/=512;
		fonttexturecoords[a][1]/=-256;
		fonttexturecoords[a][2]/=512;
		fonttexturecoords[a][3]/=-256;
		fonttexturecoords[a][4]/=512;
		fonttexturecoords[a][5]/=-256;
		fonttexturecoords[a][6]/=512;
		fonttexturecoords[a][7]/=-256;
	}
}

void drawtext(float posx,float posy,char* text,float size){

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,fonttexture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	float xsize=0.032*size/screenaspect;
	float ysize=0.042*size;
	posy-=ysize;
	posy-=0.0025*size;
	int length=strlen(text);
	for(int a=0;a<length;a++){
		float verts[]={
			posx,		posy,
			posx+xsize,	posy,
			posx+xsize,	posy+ysize,
			posx,		posy+ysize,};
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,fonttexturecoords[text[a]-' ']);
		glDrawArrays(GL_QUADS,0,4);
		posx+=xsize*0.625;
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

}

void drawtextcentered(float posx,float posy,char* text,float size){
	float xsize=0.032*size/screenaspect;
	float ysize=0.042*size;
	float length=strlen(text);
	if(length>1){
		length-=1;
		length*=0.625;
		length+=1;
	}
	posx-=xsize*0.5*length;
	posy+=ysize*0.5;
	drawtext(posx,posy,text,size);
}
