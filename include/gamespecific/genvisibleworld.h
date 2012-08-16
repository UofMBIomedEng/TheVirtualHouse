int visibleworldarrayvertexsize=0;

void genvisibleworld(){

	//get the size of it
	visibleworldvertexcount=0;
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++){
		int a=worldgrid[x][y][z][0];
		if(a)visibleworldvertexcount+=worldtilevertexcount[a];
	}

	//create the array
	if(visibleworldvertexcount>visibleworldarrayvertexsize){
		delete visibleworldinterleavedvertex;
		visibleworldinterleavedvertex = new InterleavedVertex[visibleworldvertexcount];
		visibleworldarrayvertexsize=visibleworldvertexcount;
	}

	//fill the array
	visibleworldvertexcount=0;
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++){
		int a=worldgrid[x][y][z][0];
		int b=worldgrid[x][y][z][1];
		if(a)for(int c=0; c<worldtilevertexcount[a]; c++){
			visibleworldinterleavedvertex[visibleworldvertexcount]=
				worldtileinterleavedvertex[a][b][c];
			visibleworldinterleavedvertex[visibleworldvertexcount].px+=x*worldtilesize;
			visibleworldinterleavedvertex[visibleworldvertexcount].py+=y*worldtilesize;
			visibleworldinterleavedvertex[visibleworldvertexcount].pz+=z*worldtilesize;
			visibleworldvertexcount+=1;
		}
	}

	//number to draw on screen...
	gameworldpolygons=visibleworldvertexcount/3;
	
	//enter it into a vertex buffer object
	if(usevbo){
		glDeleteBuffers(1,&visibleworldvbo);
		glGenBuffers(1,&visibleworldvbo);
		glBindBuffer(GL_ARRAY_BUFFER,visibleworldvbo);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(InterleavedVertex)*visibleworldvertexcount,
			visibleworldinterleavedvertex,GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}

}
