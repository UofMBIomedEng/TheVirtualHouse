GLuint genminimap(){

	int powoftwo;

	int xsize=worldgridsizex;
	powoftwo=2;
	while(powoftwo<xsize)powoftwo*=2;
	xsize=powoftwo;

	int zsize=worldgridsizez;
	powoftwo=2;
	while(powoftwo<zsize)powoftwo*=2;
	zsize=powoftwo;

	GLubyte* texturedata = new GLubyte[xsize*zsize*3];

	for(int z=0; z<zsize; z++)for(int x=0; x<xsize; x++){
		//default to blackness
		texturedata[z*xsize*3+x*3+0] = (GLubyte) 0;
		texturedata[z*xsize*3+x*3+1] = (GLubyte) 0;
		texturedata[z*xsize*3+x*3+2] = (GLubyte) 0;
	}

	for(int z=0; z<worldgridsizez; z++)for(int x=0; x<worldgridsizex; x++){
		int xoffset=x*3;
		int zoffset=z*xsize*3;
		//default to water
		texturedata[zoffset+xoffset+0] = (GLubyte) 55;
		texturedata[zoffset+xoffset+1] = (GLubyte) 55;
		texturedata[zoffset+xoffset+2] = (GLubyte) 130;
		//sidewalk
		if(worldgrid[x][streetlevel][z][0]==8
		|| worldgrid[x][streetlevel][z][0]==9){
			texturedata[zoffset+xoffset+0] = (GLubyte) 50;
			texturedata[zoffset+xoffset+1] = (GLubyte) 50;
			texturedata[zoffset+xoffset+2] = (GLubyte) 50;
		}
		//metro/sidewalk
		if((worldgrid[x][streetlevel-1][z-1][0]==5 && worldgrid[x][streetlevel-1][z-1][1]==0)
		|| (worldgrid[x][streetlevel-1][z+1][0]==5 && worldgrid[x][streetlevel-1][z+1][1]==2)
		|| (worldgrid[x+1][streetlevel-1][z][0]==5 && worldgrid[x+1][streetlevel-1][z][1]==3)
		|| (worldgrid[x-1][streetlevel-1][z][0]==5 && worldgrid[x-1][streetlevel-1][z][1]==1)){
			texturedata[zoffset+xoffset+0] = (GLubyte) 50;
			texturedata[zoffset+xoffset+1] = (GLubyte) 50;
			texturedata[zoffset+xoffset+2] = (GLubyte) 50;
		}
		//street
		if(worldgrid[x][streetlevel][z][0]==10
		|| worldgrid[x][streetlevel][z][0]==11){
			texturedata[zoffset+xoffset+0] = (GLubyte) 15;
			texturedata[zoffset+xoffset+1] = (GLubyte) 15;
			texturedata[zoffset+xoffset+2] = (GLubyte) 15;
		}
		//building walls
		if(worldgrid[x][streetlevel][z][0]==23
		|| worldgrid[x][streetlevel][z][0]==24
		|| worldgrid[x][streetlevel][z][0]==25
		|| worldgrid[x][streetlevel][z][0]==26
		|| worldgrid[x][streetlevel][z][0]==27		
		|| worldgrid[x][streetlevel][z][0]==32
		|| worldgrid[x][streetlevel][z][0]==33
		|| worldgrid[x][streetlevel][z][0]==34){
			texturedata[zoffset+xoffset+0] = (GLubyte) 110;
			texturedata[zoffset+xoffset+1] = (GLubyte) 110;
			texturedata[zoffset+xoffset+2] = (GLubyte) 110;
		}
		//the borders of the world
		if(worldgrid[x][streetlevel][z][0]==7){
			texturedata[zoffset+xoffset+0] = (GLubyte) 0;
			texturedata[zoffset+xoffset+1] = (GLubyte) 0;
			texturedata[zoffset+xoffset+2] = (GLubyte) 0;
		}
	}

	GLuint texturename;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	glGenTextures(1,&texturename);
	glBindTexture(GL_TEXTURE_2D,texturename);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,xsize,zsize, 
		0,GL_RGB,GL_UNSIGNED_BYTE,texturedata);

	///////////////////////////////////////////////////////////////////////////save mipmap
	/*char* filename = (char*)"test.bmp";

	unsigned short Type;          // signature - 'BM'
	unsigned long  Size;          // file size in bytes
	unsigned short Reserved1;     // 0
	unsigned short Reserved2;     // 0
	unsigned long  OffBits;       // offset to bitmap
	unsigned long  StructSize;    // size of this struct (40)
	unsigned long  Width;         // bmap width in pixels
	unsigned long  Height;        // bmap height in pixels
	unsigned short Planes;        // num planes - always 1
	unsigned short BitCount;      // bits per pixel
	unsigned long  Compression;   // compression flag
	unsigned long  SizeImage;     // image size in bytes
	long           XPelsPerMeter; // horz resolution
	long           YPelsPerMeter; // vert resolution
	unsigned long  ClrUsed;       // 0 -> color table size
	unsigned long  ClrImportant;  // important color count

	FILE			*fp = NULL;

    //The length of each line must be a multiple of 4 bytes
    int bytesPerLine = (3 * (xsize + 1) / 4) * 4;
	
	Type = 'MB';
	OffBits = 54;
	Size = OffBits + bytesPerLine * zsize;
	Reserved1 = 0;
	Reserved2 = 0;
	StructSize = 40;
	Width = xsize;
	Height = zsize;
	Planes = 1;
	BitCount = 24;
	Compression = 0;
	SizeImage = bytesPerLine * zsize;
	XPelsPerMeter = 0;
	YPelsPerMeter = 0;
	ClrUsed = 0;   
	ClrImportant = 0; 
	
	fp = fopen(filename, "wb");

	fwrite(&Type,sizeof(unsigned short),1,fp);
	fwrite(&Size,sizeof(unsigned long),1,fp);
	fwrite(&Reserved1,sizeof(unsigned short),1,fp);
	fwrite(&Reserved2,sizeof(unsigned short),1,fp);
	fwrite(&OffBits,sizeof(unsigned long),1,fp);
	fwrite(&StructSize,sizeof(unsigned long),1,fp);
	fwrite(&Width,sizeof(unsigned long),1,fp);
	fwrite(&Height,sizeof(unsigned long),1,fp);
	fwrite(&Planes,sizeof(unsigned short),1,fp);
	fwrite(&BitCount,sizeof(unsigned short),1,fp);
	fwrite(&Compression,sizeof(unsigned long),1,fp);
	fwrite(&SizeImage,sizeof(unsigned long),1,fp);
	fwrite(&XPelsPerMeter,sizeof(long),1,fp);
	fwrite(&YPelsPerMeter,sizeof(long),1,fp);
	fwrite(&ClrUsed,sizeof(unsigned long),1,fp);
	fwrite(&ClrImportant,sizeof(unsigned long),1,fp);

	fwrite(texturedata, 3, xsize * zsize, fp);
	fclose(fp);*/
	///////////////////////////////////////////////////////////////////////////save mipmap

	delete texturedata;

	minimaptexturexuse=(float)worldgridsizex/(float)xsize;
	minimaptexturezuse=(float)worldgridsizez/(float)zsize;

	return texturename;

}
