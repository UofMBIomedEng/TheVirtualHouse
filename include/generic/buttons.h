GLuint buttontexture;
GLuint buttonglowingtexture;
float buttontexturecoords[9][4*2];

void setupbuttons(){
	char filename[256];
	sprintf(filename,"%s%s",mediadir,"button.tga");
	buttontexture=loadtga((char*)filename,0);
	sprintf(filename,"%s%s",mediadir,"buttonglowing.tga");
	buttonglowingtexture=loadtga((char*)filename,0);
	//bottom left corner
	buttontexturecoords[0][0*2+0] = 0.00;
	buttontexturecoords[0][0*2+1] = 0.00;
	buttontexturecoords[0][1*2+0] = 0.25;
	buttontexturecoords[0][1*2+1] = 0.00;
	buttontexturecoords[0][2*2+0] = 0.25;
	buttontexturecoords[0][2*2+1] = 0.25;
	buttontexturecoords[0][3*2+0] = 0.00;
	buttontexturecoords[0][3*2+1] = 0.25;
	//bottom right corner
	buttontexturecoords[1][0*2+0] = 0.75;
	buttontexturecoords[1][0*2+1] = 0.00;
	buttontexturecoords[1][1*2+0] = 1.00;
	buttontexturecoords[1][1*2+1] = 0.00;
	buttontexturecoords[1][2*2+0] = 1.00;
	buttontexturecoords[1][2*2+1] = 0.25;
	buttontexturecoords[1][3*2+0] = 0.75;
	buttontexturecoords[1][3*2+1] = 0.25;
	//top left corner
	buttontexturecoords[2][0*2+0] = 0.00;
	buttontexturecoords[2][0*2+1] = 0.75;
	buttontexturecoords[2][1*2+0] = 0.25;
	buttontexturecoords[2][1*2+1] = 0.75;
	buttontexturecoords[2][2*2+0] = 0.25;
	buttontexturecoords[2][2*2+1] = 1.00;
	buttontexturecoords[2][3*2+0] = 0.00;
	buttontexturecoords[2][3*2+1] = 1.00;
	//top right corner
	buttontexturecoords[3][0*2+0] = 0.75;
	buttontexturecoords[3][0*2+1] = 0.75;
	buttontexturecoords[3][1*2+0] = 1.00;
	buttontexturecoords[3][1*2+1] = 0.75;
	buttontexturecoords[3][2*2+0] = 1.00;
	buttontexturecoords[3][2*2+1] = 1.00;
	buttontexturecoords[3][3*2+0] = 0.75;
	buttontexturecoords[3][3*2+1] = 1.00;
	//bottom side
	buttontexturecoords[4][0*2+0] = 0.25;
	buttontexturecoords[4][0*2+1] = 0.00;
	buttontexturecoords[4][1*2+0] = 0.75;
	buttontexturecoords[4][1*2+1] = 0.00;
	buttontexturecoords[4][2*2+0] = 0.75;
	buttontexturecoords[4][2*2+1] = 0.25;
	buttontexturecoords[4][3*2+0] = 0.25;
	buttontexturecoords[4][3*2+1] = 0.25;
	//left side
	buttontexturecoords[5][0*2+0] = 0.00;
	buttontexturecoords[5][0*2+1] = 0.25;
	buttontexturecoords[5][1*2+0] = 0.25;
	buttontexturecoords[5][1*2+1] = 0.25;
	buttontexturecoords[5][2*2+0] = 0.25;
	buttontexturecoords[5][2*2+1] = 0.75;
	buttontexturecoords[5][3*2+0] = 0.00;
	buttontexturecoords[5][3*2+1] = 0.75;
	//right side
	buttontexturecoords[6][0*2+0] = 0.75;
	buttontexturecoords[6][0*2+1] = 0.25;
	buttontexturecoords[6][1*2+0] = 1.00;
	buttontexturecoords[6][1*2+1] = 0.25;
	buttontexturecoords[6][2*2+0] = 1.00;
	buttontexturecoords[6][2*2+1] = 0.75;
	buttontexturecoords[6][3*2+0] = 0.75;
	buttontexturecoords[6][3*2+1] = 0.75;
	//top side
	buttontexturecoords[7][0*2+0] = 0.25;
	buttontexturecoords[7][0*2+1] = 0.75;
	buttontexturecoords[7][1*2+0] = 0.75;
	buttontexturecoords[7][1*2+1] = 0.75;
	buttontexturecoords[7][2*2+0] = 0.75;
	buttontexturecoords[7][2*2+1] = 1.00;
	buttontexturecoords[7][3*2+0] = 0.25;
	buttontexturecoords[7][3*2+1] = 1.00;
	//center
	buttontexturecoords[8][0*2+0] = 0.25;
	buttontexturecoords[8][0*2+1] = 0.25;
	buttontexturecoords[8][1*2+0] = 0.75;
	buttontexturecoords[8][1*2+1] = 0.25;
	buttontexturecoords[8][2*2+0] = 0.75;
	buttontexturecoords[8][2*2+1] = 0.75;
	buttontexturecoords[8][3*2+0] = 0.25;
	buttontexturecoords[8][3*2+1] = 0.75;
}

void drawbutton(float posx,float posy,float width,float height,bool glow){

	width/=screenaspect;
	posx-=width*0.5;
	posy-=height*0.5;

	float x,y,w,h;

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	if(glow)glBindTexture(GL_TEXTURE_2D,buttonglowingtexture);
	else glBindTexture(GL_TEXTURE_2D,buttontexture);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	w=0.1/screenaspect;	h=0.1;
	//bottom left
	x=posx-w;			y=posy-h;
	float vertsbottomleft[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertsbottomleft);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[0]);
	glDrawArrays(GL_QUADS,0,4);
	//bottom right
	x=posx+width;		y=posy-h;
	float vertsbottomright[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertsbottomright);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[1]);
	glDrawArrays(GL_QUADS,0,4);
	//top left
	x=posx-w;			y=posy+height;
	float vertstopleft[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertstopleft);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[2]);
	glDrawArrays(GL_QUADS,0,4);
	//top right
	x=posx+width;		y=posy+height;
	float vertstopright[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertstopright);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[3]);
	glDrawArrays(GL_QUADS,0,4);
	//bottom
	w=width;			h=0.1;
	x=posx;				y=posy-h;
	float vertsbottom[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertsbottom);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[4]);
	glDrawArrays(GL_QUADS,0,4);
	//left
	w=0.1/screenaspect;	h=height;
	x=posx-w;			y=posy;
	float vertsleft[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertsleft);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[5]);
	glDrawArrays(GL_QUADS,0,4);
	//right
	w=0.1/screenaspect;	h=height;
	x=posx+width;		y=posy;
	float vertsright[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertsright);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[6]);
	glDrawArrays(GL_QUADS,0,4);
	//top
	w=width;			h=0.1;
	x=posx;				y=posy+height;
	float vertstop[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertstop);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[7]);
	glDrawArrays(GL_QUADS,0,4);
	//center
	w=width;			h=height;
	x=posx;				y=posy;
	float vertscenter[]={x,y,x+w,y,x+w,y+h,x,y+h,};
	glVertexPointer(2,GL_FLOAT,0,vertscenter);
	glTexCoordPointer(2,GL_FLOAT,0,buttontexturecoords[8]);
	glDrawArrays(GL_QUADS,0,4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

}
