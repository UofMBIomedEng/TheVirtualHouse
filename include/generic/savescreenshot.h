void savescreenshot(){
//this isnt done yet. it doesnt work on PS3 and seems slightly flawed on PC.
/*
	#ifdef WIN32
	char* filename = (char*)"test.bmp";
	#else
	char* filename = (char*)"/dev_hdd0/photo/2011/01/08/test.bmp";
	#endif

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

	unsigned char	*pPixels;
	FILE			*fp = NULL;

    //The length of each line must be a multiple of 4 bytes
    int bytesPerLine = (3 * (screenw + 1) / 4) * 4;
	
#ifdef WIN32
	Type = 'MB';
	OffBits = 54;
	Size = OffBits + bytesPerLine * screenh;
	Reserved1 = 0;
	Reserved2 = 0;
	StructSize = 40;
	Width = screenw;
	Height = screenh;
	Planes = 1;
	BitCount = 32;
	Compression = 0;
	SizeImage = bytesPerLine * screenh;
	XPelsPerMeter = 0;
	YPelsPerMeter = 0;
	ClrUsed = 0;   
	ClrImportant = 0; 
#else
	Type = 'BM';
	OffBits = 54;
	Size = OffBits + bytesPerLine * screenh;
	Reserved1 = 0;
	Reserved2 = 0;
	StructSize = 40;
	Width = screenw;
	Height = screenh;
	Planes = 1;
	BitCount = 32;
	Compression = 0;
	SizeImage = bytesPerLine * screenh;
	XPelsPerMeter = 0;
	YPelsPerMeter = 0;
	ClrUsed = 0;   
	ClrImportant = 0; 
#endif
	
	pPixels = new unsigned char[screenw * screenh * 4];
	glReadPixels(0, 0, screenw, screenh, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pPixels);
	unsigned int	*pIntPix = (unsigned int *)pPixels;
	for(int i = 0; i < screenw * screenh; i ++)
	{
		*pIntPix = LITTLE_INT(*pIntPix);
		pIntPix ++;
	}

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

	fwrite(pPixels, 4, screenw * screenh, fp);
	fclose(fp);
	delete []pPixels;
*/
}
