void TestApp::drawworld(){

	float background_color[4]={0.4, 0.56, 0.75, 1};      // bakgournd sky color
	glClearColor(background_color[0],background_color[1],background_color[2],background_color[3]);							//background color  
    glClearDepth(1000.0);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.0f);
	

	if(!showsky){
		float fog_color[4]={0.3, 0.46, 0.65, 0.5};			  // fog color	
		//turn on fog
		GLfloat fogColor[4]= {fog_color[0],fog_color[1],fog_color[2],fog_color[3]};             //fog color
		glFogi(GL_FOG_MODE,GL_LINEAR);
		glFogfv(GL_FOG_COLOR,fogColor);
		glFogf(GL_FOG_DENSITY,0.25f);
		glHint(GL_FOG_HINT,GL_DONT_CARE);
		glFogf(GL_FOG_START,0.1f);
		glFogf(GL_FOG_END,worldtilesize*(worldtileviewrange+20));
		glEnable(GL_FOG);
	}
	

	skybox = new SKYBOX();
	if(showsky)
		skybox->Initialize();

	//skybox->Render();

	//prep for drawing
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat light_position0[] = {camxpos,camypos,camzpos,1.0};
	//GLfloat light_position0[] = {30,10,30,1.0};
	GLfloat light_ambient0[] = {1.0,1.0,1.0,1.0};
	GLfloat light_diffuse0[] = {1.0,1.0,1.0,1.0};
	GLfloat light_specular0[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular0);
	//glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.5f/((float)worldtileviewrange+1.f));
	//glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.01f);

	/*
	glEnable(GL_LIGHT1);
	GLfloat light_position1[] = {camxpos+500,camypos+250,camzpos+300,1.0};
	GLfloat light_ambient1[] = {0.0,0.0,0.0,1.0};
	GLfloat light_diffuse1[] = {1.0,1.0,1.0,1.0};
	GLfloat light_specular1[] = {1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT1,GL_POSITION,light_position1);
	glLightfv(GL_LIGHT1,GL_AMBIENT,light_ambient1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse1);
	glLightfv(GL_LIGHT1,GL_SPECULAR,light_specular1);
	glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.005f);
	*/
	

	/*int viewport[4];
	double mvmatrix[16],projmatrix[16];
	double winx,winy,winz;
	float bufferz;
	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);*/

	if(usetextures)glEnable(GL_TEXTURE_2D);								
	if(usetextures)glBindTexture(GL_TEXTURE_2D,wireframetexture);		


	glEnableClientState(GL_VERTEX_ARRAY);
	if(usetextures)glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if(showsky)	
		skybox->Render(camyang*degreesinradian,camxang*degreesinradian);
//	skybox->Render(0,0);
	//draw world
	if(usetileswhenrendering){
	//	glRotatef( camxang, 1.0f, 0.0f, 0.0f );
	//	glRotatef( camyang, 0.0f, 1.0f, 0.0f );	
		gameworldpolygons=0;
		for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
			for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
				for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++){
					int a=worldgrid[x][y][z][0];
					int b=worldgrid[x][y][z][1];
					//gluProject(x*worldtilesize,y*worldtilesize,z*worldtilesize,mvmatrix,projmatrix,viewport,&winx,&winy,&winz);
					//if(winz<1)
					if(a>0){
					//	if(usetextures)glBindTexture(GL_TEXTURE_2D,worldtiletexture[a]);  //original code
		//This is if statement is for textures
					
						if(usetextures){												//added
							glEnable(GL_TEXTURE_2D);
							glEnableClientState(GL_TEXTURE_COORD_ARRAY);
							glBindTexture(GL_TEXTURE_2D,worldtiletexture[a]);
							
						}																	//added
						
						glPushMatrix();
						glTranslatef(x*worldtilesize,y*worldtilesize,z*worldtilesize);
						glVertexPointer(3,GL_FLOAT,sizeof(InterleavedVertex),&worldtileinterleavedvertex[a][b]->px);
		//This next line is also for textures
						if(usetextures||a==10||a>=45)glTexCoordPointer(2,GL_FLOAT,sizeof(InterleavedVertex),&worldtileinterleavedvertex[a][b]->tx);
						glNormalPointer(GL_FLOAT,sizeof(InterleavedVertex),&worldtileinterleavedvertex[a][b]->nx);
						glDrawArrays(GL_TRIANGLES,0,worldtilevertexcount[a]);
						if(!usetextures){glDisable(GL_TEXTURE_2D);glDisableClientState(GL_TEXTURE_COORD_ARRAY);}    //added
						glPopMatrix();			
						gameworldpolygons+=worldtilevertexcount[a]/3;
					}
				}
	}else{
		gameworldpolygons=visibleworldvertexcount/3;
		glPushMatrix();
		if(usevbo){
			glBindBuffer(GL_ARRAY_BUFFER,visibleworldvbo);
			glVertexPointer(3,GL_FLOAT,sizeof(InterleavedVertex),BUFFER_OFFSET(0));
			glNormalPointer(GL_FLOAT,sizeof(InterleavedVertex),BUFFER_OFFSET(sizeof(float)*3));
			if(usetextures)glTexCoordPointer(2,GL_FLOAT,sizeof(InterleavedVertex),BUFFER_OFFSET(sizeof(float)*6));
			glDrawArrays(GL_TRIANGLES,0,visibleworldvertexcount);
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}else{
			glVertexPointer(3,GL_FLOAT,sizeof(InterleavedVertex),&visibleworldinterleavedvertex[0].px);
			glNormalPointer(GL_FLOAT,sizeof(InterleavedVertex),&visibleworldinterleavedvertex[0].nx);
			if(usetextures)glTexCoordPointer(2,GL_FLOAT,sizeof(InterleavedVertex),&visibleworldinterleavedvertex[0].tx);
			glDrawArrays(GL_TRIANGLES,0,visibleworldvertexcount);
		}
		glPopMatrix();
	}

	if(usetextures)glBindTexture(GL_TEXTURE_2D,wireframetexture);

	//draw player
	if(showplayer){
		playerms3dmodel.SetFrame(playerframe);
		int vertnum=0;
		int numGroups = playerms3dmodel.GetNumGroups();
		for (int i = 0; i < numGroups; i++){
			ms3d_group_t *group = playerms3dmodel.GetGroup(i);
			for (size_t j = 0; j < group->triangleIndices.size(); j++){
				ms3d_triangle_t *triangle = playerms3dmodel.GetTriangle(group->triangleIndices[j]);
				for (int v = 0; v < 3; v++){
					ms3d_vertex_t *playervertex = playerms3dmodel.GetVertex(triangle->vertexIndices[v]);
					float pos[3];
					playerms3dmodel.TransformVertex(playervertex,pos);
					playervertexarray[vertnum*3+0]=pos[0]*0.05;
					playervertexarray[vertnum*3+1]=pos[1]*0.05;
					playervertexarray[vertnum*3+2]=pos[2]*0.05;
					vertnum+=1;
				}
			}
		}
		glPushMatrix();
		glTranslatef(playerxpos,playerypos,playerzpos);
		glRotatef(-playeryang*degreesinradian+90,0,1,0);
		glVertexPointer(3,GL_FLOAT,0,playervertexarray);
		if(usetextures)glTexCoordPointer(2,GL_FLOAT,0,playertexturearray);
		glNormalPointer(GL_FLOAT,0,playernormalarray);
		glDrawArrays(GL_TRIANGLES,0,playervertexcount);
		glPopMatrix();
	}


	//draw entities
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++)
	for(int a=0; a<entitycount[x][y][z]; a++){
		glPushMatrix();
		glTranslatef(
			entitylist[x][y][z][a]->xpos,
			entitylist[x][y][z][a]->ypos,
			entitylist[x][y][z][a]->zpos);
		glRotatef(entitylist[x][y][z][a]->xang*degreesinradian,1,0,0);
		glRotatef(entitylist[x][y][z][a]->yang*degreesinradian,0,1,0);
		glRotatef(entitylist[x][y][z][a]->zang*degreesinradian,0,0,1);
		glVertexPointer(3,GL_FLOAT,0,entityvertexarray[entitylist[x][y][z][a]->type]);
		if(usetextures)glTexCoordPointer(2,GL_FLOAT,0,entitytexturearray[entitylist[x][y][z][a]->type]);
		glNormalPointer(GL_FLOAT,0,entitynormalarray[entitylist[x][y][z][a]->type]);
		glDrawArrays(GL_TRIANGLES,0,entityvertexcount[entitylist[x][y][z][a]->type]);
		glPopMatrix();
	}

	//draw water
	/*for(int c=0; c<watervertexcount/3; c++){
		CVector3 g_vTriangle[3];
		g_vTriangle[0]=CVector3(
			watervertexarray[c*9+0],
			watervertexarray[c*9+1]*waterscale,
			watervertexarray[c*9+2]);
		g_vTriangle[1]=CVector3(
			watervertexarray[c*9+3],
			watervertexarray[c*9+4]*waterscale,
			watervertexarray[c*9+5]);
		g_vTriangle[2]=CVector3(
			watervertexarray[c*9+6],
			watervertexarray[c*9+7]*waterscale,
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
	/*glEnable(GL_NORMALIZE);
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++)
	if(1==1){
		glPushMatrix();
		glTranslatef(x*worldtilesize,waterheight[x][z],z*worldtilesize);
		glScalef(1,waterscale,1);
		glVertexPointer(3,GL_FLOAT,0,watervertexarray);
		if(usetextures)glTexCoordPointer(2,GL_FLOAT,0,watertexturearray);
		glNormalPointer(GL_FLOAT,0,waternormalarray);
		glDrawArrays(GL_TRIANGLES,0,watervertexcount);
		glPopMatrix();
	}
	glDisable(GL_NORMALIZE);*/

	//finished drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	if(usetextures)glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	if(showsky)
		skybox->Finalize();
	if(usetextures)glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

}
