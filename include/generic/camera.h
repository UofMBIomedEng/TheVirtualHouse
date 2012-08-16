void set3dcamera(float xpos,float ypos,float zpos,float xang,float yang,float zang,float fov,float aspect){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspectivef(fov,aspect,1.f,1000.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(zang*degreesinradian,0,0,1);
	glRotatef(xang*degreesinradian,1,0,0);
	glRotatef(yang*degreesinradian,0,1,0);
	glTranslatef(-xpos,-ypos,-zpos);
}

void set2dcamera(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void unset2dcamera(){
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}
