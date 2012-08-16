const float PI=3.14159265;
const float PIOVER180=0.0174532925;
const float degreesinradian=57.2957795;
const float radiansindegree=0.0174532925;

int lowint(int a,int b){
	if(a<b){return a;}else{return b;}
}

int highint(int a,int b){
	if(a>b){return a;}else{return b;}
}

float infloatrange(float num,float high,float low){
	if(num>high)num=high;
	if(num<low)num=low;
	return num;
}

void movein2dspace(float &xpos,float &ypos,float ang,float speed){
	xpos+=speed*cos(ang);
	ypos+=speed*sin(ang);
}

void movein3dspace(float &xpos,float &ypos,float &zpos,float yang,float xang,float speed){
	ypos+=speed*sin(xang);
	xpos+=speed*cos(xang)*cos(yang);
	zpos+=speed*cos(xang)*sin(yang);
}

float dist2d(float x,float y,float x2,float y2){
	x-=x2;
	y-=y2;
	return sqrt(x*x+y*y);
}

float dist3d(float x,float y,float z,float x2,float y2,float z2){
	x-=x2;
	y-=y2;
	z-=z2;
	return sqrt(x*x+y*y+z*z);
}

float mindist2d(float x,float y,float x2,float y2,float minimumdistance){
	if(x<x2+minimumdistance && y<y2+minimumdistance
	&& x>x2-minimumdistance && y>y2-minimumdistance){
		x-=x2;
		y-=y2;
		return sqrt(x*x+y*y);
	}else{
		return minimumdistance;
	}
}

float mindist3d(float x,float y,float z,float x2,float y2,float z2,float minimumdistance){
	if(x<x2+minimumdistance && y<y2+minimumdistance && z<z2+minimumdistance
	&& x>x2-minimumdistance && y>y2-minimumdistance && z>z2-minimumdistance){
		x-=x2;
		y-=y2;
		z-=z2;
		return sqrt(x*x+y*y+z*z);
	}else{
		return minimumdistance;
	}
}

float turntoangle(float startangle,float endangle,float speed){
	while(startangle<endangle-180/degreesinradian)startangle+=360/degreesinradian;
	while(startangle>endangle+180/degreesinradian)startangle-=360/degreesinradian;
	startangle+=(endangle-startangle)*speed;
	return startangle;
}

float angledifference(float startangle,float endangle){
	while(startangle<endangle-180/degreesinradian)startangle+=360/degreesinradian;
	while(startangle>endangle+180/degreesinradian)startangle-=360/degreesinradian;
	return (endangle-startangle);
}
