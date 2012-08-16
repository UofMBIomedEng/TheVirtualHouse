void drawcuboid(
	float x,float y,float z,
	float w,float h,float d,
	float r,float g,float b){
	float verts[]={
		x+0,y+0,z+0,//side1
		x+0,y+h,z+0,
		x+w,y+h,z+0,
		x+w,y+0,z+0,	
		x+0,y+0,z+d,//side2
		x+w,y+0,z+d,
		x+w,y+h,z+d,
		x+0,y+h,z+d,	
		x+0,y+h,z+0,//side3
		x+0,y+h,z+d,
		x+w,y+h,z+d,
		x+w,y+h,z+0,
		x+0,y+0,z+0,//side4
		x+w,y+0,z+0,
		x+w,y+0,z+d,
		x+0,y+0,z+d,
		x+0,y+0,z+0,//side5
		x+0,y+0,z+d,
		x+0,y+h,z+d,
		x+0,y+h,z+0,
		x+w,y+0,z+0,//side6
		x+w,y+h,z+0,
		x+w,y+h,z+d,
		x+w,y+0,z+d,
	};
	float color[]={
		r-0.1,g-0.1,b-0.1,//side1
		r-0.1,g-0.1,b-0.1,
		r-0.1,g-0.1,b-0.1,
		r-0.1,g-0.1,b-0.1,
		r-0.3,g-0.3,b-0.3,//side2
		r-0.3,g-0.3,b-0.3,
		r-0.3,g-0.3,b-0.3,
		r-0.3,g-0.3,b-0.3,
		r-0.4,g-0.4,b-0.4,//side3
		r-0.4,g-0.4,b-0.4,
		r-0.4,g-0.4,b-0.4,
		r-0.4,g-0.4,b-0.4,
		r-0.5,g-0.5,b-0.5,//side4
		r-0.5,g-0.5,b-0.5,
		r-0.5,g-0.5,b-0.5,
		r-0.5,g-0.5,b-0.5,
		r-0.2,g-0.2,b-0.2,//side5
		r-0.2,g-0.2,b-0.2,
		r-0.2,g-0.2,b-0.2,
		r-0.2,g-0.2,b-0.2,
		r-0.0,g-0.0,b-0.0,//side6
		r-0.0,g-0.0,b-0.0,
		r-0.0,g-0.0,b-0.0,
		r-0.0,g-0.0,b-0.0,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verts);
	glColorPointer(3,GL_FLOAT,0,color);
	glDrawArrays(GL_QUADS,0,24);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void drawquad(
	float x,float y,float z,
	float w,float h,float d,
	float r,float g,float b){
	float verts[]={
		x-w,y-h,d+z,
		x+w,y-h,d+z,
		x+w,y+h,d+z,
		x-w,y+h,d+z,};
	float color[]={
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,};
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verts);
	glColorPointer(3,GL_FLOAT,0,color);
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void drawcircle(
	float x,float y,float z,
	float radius,
	float r,float g,float b){
	float verts[200];
	verts[0]=x;
	verts[1]=y;
	verts[2]=z;
	int i=3;
	for(float angle=0; angle<2*3.14159265; angle+=0.630){
		verts[i]=x+radius*cos(angle);i++;
		verts[i]=y+radius*sin(angle);i++;
		verts[i]=z;i++;
	}
	verts[33]=verts[3];
	verts[34]=verts[4]; 
	verts[35]=verts[5]; 
	float color[]={
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,
		r,g,b,};
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verts);
	glColorPointer(3,GL_FLOAT,0,color);
	glDrawArrays(GL_TRIANGLE_FAN,0,12);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void draw2Dquad(
	float x,float y,float w,float h){
	float verts[]={
		x,y,
		x+w,y,
		x+w,y+h,
		x,y+h,};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,verts);
	glDrawArrays(GL_QUADS,0,4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void draw2Dcircle(
	float x,float y,float radius,float xscale,int sides){
	float verts[200];
	verts[0]=x;
	verts[1]=y;
	int i=2;
	for(float angle=0; angle<2*3.14159265; angle+=2*3.14159265/sides){
		verts[i]=x+radius*cos(angle)*xscale;i++;
		verts[i]=y+radius*sin(angle);i++;
	}
	verts[i]=verts[2];i++;
	verts[i]=verts[3];i++;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,verts);
	glDrawArrays(GL_TRIANGLE_FAN,0,i/2);
	glDisableClientState(GL_VERTEX_ARRAY);
}
