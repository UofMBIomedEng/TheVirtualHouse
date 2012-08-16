void TestApp::drawhud(){

	glViewport(0,0,(GLsizei)screenw,(GLsizei)screenh);

	char temptext[100];
	float x=-1+0.01/screenaspect;
	float y=0.99;

	if(showinfo){
		switch(lang){
			case 1:   //English
				sprintf(temptext,"%s","All rights reserved to Neuro BME, University of Manitoba");
				break;
			case 2:   //French
				sprintf(temptext,"%s","Tous droits reserves a BME Neuro de l'Universite du Manitoba");
				break;
			case 3:   //Spanish
				sprintf(temptext,"%s","Todos los derechos reservados BME Neuro, Universidad de Manitoba");
				break;
			case 4:   //German
				sprintf(temptext,"%s","Alle Rechte vorbehalten fur Neuro BME, Universitas Manitoba");
				break;
		}
			drawtext(x,y,(char*)temptext,1);y-=0.04;

		if(allocentric){
			sprintf(temptext,"%s","Allocentric mode");
			drawtext(x,y,(char*)temptext,1);y-=0.04;
		}
		//sprintf(temptext,"%s%d","joykey: ",temp);
		//drawtext(x,y,(char*)temptext,1);y-=0.03;
		sprintf(temptext,"%s%.2f","Elapsed time [sec]: ",elapsedtime);
		drawtext(x,y,(char*)temptext,1);y-=0.03;

		sprintf(temptext,"%s%.2f","Traversed distance [m]: ",elapseddist);
		drawtext(x,y,(char*)temptext,1);y-=0.03;

		sprintf(temptext,"%s%.2f","Expected distance [m]: ",expectdist);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
	
		sprintf(temptext,"%s%d","Frames per second: ",(int)fFPS);
		drawtext(x,y,(char*)temptext,1);y-=0.03;

		sprintf(temptext,"%s%d%s%.1f","Intro turn:",start_motion," Motion Time:",motion_time);
		drawtext(x,y,(char*)temptext,1);y-=0.03;

	//	sprintf(temptext,"%s%i","polygons in the game world: ",gameworldpolygons);
	//	drawtext(x,y,(char*)temptext,2);y-=0.07;
	//	sprintf(temptext,"%s%i","polygons in the player model: ",playervertexcount);
	//	drawtext(x,y,(char*)temptext,2);y-=0.07;

		sprintf(temptext,"%s%i","World tile view range: ",worldtileviewrange);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		sprintf(temptext,"%s%i","Control Latency: ", latency);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		if(freecamera) sprintf(temptext,"%s","Mouse control enabled");
		else sprintf(temptext,"%s","Mouse control disabled");
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		if(autoexit) sprintf(temptext,"%s","Auto exit enabled");
		else sprintf(temptext,"%s","Auto exit disabled");
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		if(usejoystick) sprintf(temptext,"%s","Joystick control enabled");
		else sprintf(temptext,"%s","Joystick control disabled");
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		sprintf(temptext,"%s%.1f,%.1f,%.1f","Position:",playerxpos,playerypos,playerzpos);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		sprintf(temptext,"%s%.1f,%.1f,%.1f","Target P:",target_x,target_y,target_z);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		sprintf(temptext,"%s%.1f,%.1f,%.1f","Heading:",camxang*degreesinradian,camyang*degreesinradian,camzang*degreesinradian);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		sprintf(temptext,"%s%.1f","Field of view:",screenfov);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		if(!showplayer){
			sprintf(temptext,"%s%.1f","Player height [ft]: ",playerhight);
			drawtext(x,y,(char*)temptext,1);y-=0.03;
		}
		sprintf(temptext,"%s%s","Log file: ",logfilename);
		drawtext(x,y,(char*)temptext,1);y-=0.03;
		
	}

	if(!testmode)
	{
		if(kidmode){
			switch(targetwin)
			{
				case 0:
					switch(lang){
						case 1:    //English
							sprintf(temptext,"%s%d%s","Trial number ",trial,": Go to the window with the Kitten");
							break;
						case 2:   //French
							sprintf(temptext,"%s%d%s","Numero d'essai ",trial,": Allez a la fenetre avec le Chat");
							break;
						case 3:   //Spanish
							sprintf(temptext,"%s%d%s","Prueba numero ",trial,": Vaya a la ventana con el Gato");
							break;
						case 4:   //German
							sprintf(temptext,"%s%d%s","Versuch Nummer ",trial,": Gehen Sie zu dem Fenster mit die Katze");
							break;
					}
				break;
				case 1:
					switch(lang){
						case 1:   //English
							sprintf(temptext,"%s%d%s","Trial number ",trial,": Go to the window with the Puppy");
							break;
						case 2:   //French
							sprintf(temptext,"%s%d%s","Numero d'essai ",trial,": Allez a la fenetre avec le Chein");
							break;
						case 3:   //Spanish
							sprintf(temptext,"%s%d%s","Prueba numero ",trial,": Vaya a la ventana con la Perro");
							break;
						case 4:   //German
							sprintf(temptext,"%s%d%s","Versuch Nummer ",trial,": Gehen Sie zu dem Fenster mit der Hund");
							break;
					}
				break;
				case 2:
					switch(lang){
						case 1:    //English
							sprintf(temptext,"%s%d%s","Trial number ",trial,": Go to the window with the Cow");
							break;
						case 2:   //French
							sprintf(temptext,"%s%d%s","Numero d'essai ",trial,": Allez a la fenetre avec le Vache");
							break;
						case 3:   //Spanish
							sprintf(temptext,"%s%d%s","Prueba numero ",trial,": Vaya a la ventana con el Vaca");
							break;
						case 4:   //German
							sprintf(temptext,"%s%d%s","Versuch Nummer ",trial,": Gehen Sie zu dem Fenster mit die Kuh");
							break;
					}
				break;
			}
		}
		else
		{
			switch(targetwin)
			{
				case 0:
					switch(lang){
						case 1:    //English
							sprintf(temptext,"%s%d%s","Trial number ",trial,": Go to the window with the circle");
							break;
						case 2:   //French
							sprintf(temptext,"%s%d%s","Numero d'essai ",trial,": Allez a la fenetre avec le cercle");
							break;
						case 3:   //Spanish
							sprintf(temptext,"%s%d%s","Prueba numero ",trial,": Vaya a la ventana con el circulo");
							break;
						case 4:   //German
							sprintf(temptext,"%s%d%s","Versuch Nummer ",trial,": Gehen Sie zu dem Fenster mit Kreis");
							break;
					}
				break;
				case 1:
					switch(lang){
						case 1:   //English
							sprintf(temptext,"%s%d%s","Trial number ",trial,": Go to the window with the X");
							break;
						case 2:   //French
							sprintf(temptext,"%s%d%s","Numero d'essai ",trial,": Allez a la fenetre avec le X");
							break;
						case 3:   //Spanish
							sprintf(temptext,"%s%d%s","Prueba numero ",trial,": Vaya a la ventana con la X");
							break;
						case 4:   //German
							sprintf(temptext,"%s%d%s","Versuch Nummer ",trial,": Gehen Sie zu dem Fenster mit X");
							break;
					}
				break;
				case 2:
					switch(lang){
						case 1:    //English
							sprintf(temptext,"%s%d%s","Trial number ",trial,": Go to the window with the triangle");
							break;
						case 2:   //French
							sprintf(temptext,"%s%d%s","Numero d'essai ",trial,": Allez a la fenetre avec le triangle");
							break;
						case 3:   //Spanish
							sprintf(temptext,"%s%d%s","Prueba numero ",trial,": Vaya a la ventana con el triangulo");
							break;
						case 4:   //German
							sprintf(temptext,"%s%d%s","Versuch Nummer ",trial,": Gehen Sie zu dem Fenster mit Dreieck");
							break;
					}
				break;
			}
		}
		drawtext(x,y,(char*)temptext,2);y-=0.07;
		sprintf(temptext,"%c",win_clue);
		drawtext(x,y,(char*)temptext,2);
	}

	
	if(!testmode)
	{
		if(allocentric){
			switch(targetwin){
			case 0:
				target_x=(a_win_pos[0]*worldtilesize);
				target_y=(a_win_pos[1]*worldtilesize)-4;
				target_z=(a_win_pos[2]*worldtilesize);
				break;
			case 1:
				target_x=(b_win_pos[0]*worldtilesize);
				target_y=(b_win_pos[1]*worldtilesize)-4;
				target_z=(b_win_pos[2]*worldtilesize);
				break;
			case 2:
				target_x=(c_win_pos[0]*worldtilesize);
				target_y=(c_win_pos[1]*worldtilesize)-4;
				target_z=(c_win_pos[2]*worldtilesize);
				break;
			}
		}
		else{
			target_x=(a_win_pos[0]*worldtilesize);
			target_y=(a_win_pos[1]*worldtilesize)-4;
			target_z=(a_win_pos[2]*worldtilesize);
		}
		if((target_x-target_offset<playerxpos)&&(target_x+target_offset>playerxpos)&&(target_y-target_offset<(playerypos))&&(target_y+target_offset>(playerypos))&&(target_z-target_offset<playerzpos)&&(target_z+target_offset>playerzpos)){
			switch(lang){
				case 1:   //English
					sprintf(temptext,"%s","Good Job! You reached the Goal");
					break;
				case 2:   //French
					sprintf(temptext,"%s","Bon travail! Objectif atteint");
					break;
				case 3:   //Spanish
					sprintf(temptext,"%s","Buen trabajo! Llego a la meta");
					break;
				case 4:   //German
					sprintf(temptext,"%s","Gut Gemacht! Ziel erreicht");
					break;
			}
			drawtext(x+0.08,0,(char*)temptext,5);
			if(sound){ 
				if(kidmode){
					PlaySound((LPCSTR)"media/applause.wav", NULL, SND_FILENAME | SND_SYNC); sound = 0;
				}
				else{
					switch(lang){
						case 1:   //English
							PlaySound((LPCSTR)"media/goodjob.wav", NULL, SND_FILENAME | SND_SYNC); sound = 0;
							break;
						case 2:   //French
							PlaySound((LPCSTR)"media/bontravail.wav", NULL, SND_FILENAME | SND_SYNC); sound = 0;
							break;
						case 3:   //Spanish
							PlaySound((LPCSTR)"media/buentrabajo.wav", NULL, SND_FILENAME | SND_SYNC); sound = 0;
							break;
						case 4:   //German
							PlaySound((LPCSTR)"media/gutgemacht.wav", NULL, SND_FILENAME | SND_SYNC); sound = 0;
							break;
					}
				}
			}
			if(autoexit){Sleep(3000);exit(0);}
		}
		else sound = 1;
	}
	if(kidmode&&animal_background_sound)
	{
		if(sound_delay)
			sound_delay--;
		else{
			sound_delay=200;
			switch(targetwin){
				case 0:
					PlaySound((LPCSTR)"media/cat.wav", NULL, SND_FILENAME | SND_ASYNC); sound = 0;
					break;
				case 1:
					PlaySound((LPCSTR)"media/dog.wav", NULL, SND_FILENAME | SND_ASYNC); sound = 0;
					break;
				case 2:
					PlaySound((LPCSTR)"media/cow.wav", NULL, SND_FILENAME | SND_ASYNC); sound = 0;
					break;
			}
		}
	}
//	sprintf(temptext,"%s%i","textures turned on: ",(int)usetextures);
//	drawtext(x,y,(char*)temptext,2);y-=0.07;
//	sprintf(temptext,"%s%i","ghost mode turned on: ",(int)ghostmode);
//	drawtext(x,y,(char*)temptext,2);y-=0.07;

//	sprintf(temptext,"%s%i%s","collectables found: ",collectablesfound,"/1000");
//	drawtext(x,y,(char*)temptext,2);y-=0.07;

	//ms3d info
	/*sprintf(temptext,"%s%i","num groups: ",playerms3dmodel.GetNumGroups());
	drawtext(x,y,(char*)temptext,2);y-=0.07;
	sprintf(temptext,"%s%i","num triangles: ",playerms3dmodel.GetNumTriangles());
	drawtext(x,y,(char*)temptext,2);y-=0.07;
	sprintf(temptext,"%s%i","num joints: ",playerms3dmodel.GetNumJoints());
	drawtext(x,y,(char*)temptext,2);y-=0.07;
	sprintf(temptext,"%s%s","joint 0 name: ",(char*)playerms3dmodel.GetJoint(0)->name);
	drawtext(x,y,(char*)temptext,2);y-=0.07;
	sprintf(temptext,"%s%s","joint 1 name: ",(char*)playerms3dmodel.GetJoint(1)->name);
	drawtext(x,y,(char*)temptext,2);y-=0.07;*/

	glPushMatrix();
	glTranslatef(-0.65,-0.5,0);

	//mini map texture coords
	/*
	float minimapcoord[]={
		0,0,
		minimaptexturexuse,0,
		minimaptexturexuse,minimaptexturezuse,
		0,minimaptexturezuse,};
	
	//flip
	for(int a=0;a<4;a++){
		minimapcoord[a*2+0]*=-1;//x
	}
	//shift
	for(int a=0;a<4;a++){
		minimapcoord[a*2+0]+=minimaptexturexuse*0.5;//x
		minimapcoord[a*2+1]-=minimaptexturezuse*0.5;//z
	}
	//rotate
	float tempminimapcoord[4*2];
	for(int a=0;a<4*2;a++)
		tempminimapcoord[a]=minimapcoord[a];
	float angle=-camyang+180*radiansindegree;
	for(int a=0;a<4;a++){
		minimapcoord[a*2+0]=tempminimapcoord[a*2+1]*sin(angle)+tempminimapcoord[a*2+0]*cos(angle);
		minimapcoord[a*2+1]=tempminimapcoord[a*2+1]*cos(angle)-tempminimapcoord[a*2+0]*sin(angle);
	}
	//scale
	for(int a=0;a<4*2;a++)
		minimapcoord[a]/=7;	
	//position
	float xposonmap=((((float)playerxpos-worldtilesize*0.5)/((float)worldgridsizex*worldtilesize))-0.5)*minimaptexturexuse;
	float zposonmap=((((float)playerzpos+worldtilesize*0.5)/((float)worldgridsizez*worldtilesize))-0.5)*minimaptexturezuse;
	for(int a=0;a<4;a++){
		minimapcoord[a*2+0]+=xposonmap;
		minimapcoord[a*2+1]+=zposonmap;
	}
	//shift back
	for(int a=0;a<4;a++){
		minimapcoord[a*2+0]-=minimaptexturexuse*0.555;//x
		minimapcoord[a*2+1]+=minimaptexturezuse*0.495;//z
	}
	//mini map verts
	float minimapverts[]={
		2.2/screenaspect,0.8,
		2.8/screenaspect,0.8,
		2.8/screenaspect,1.4,
		2.2/screenaspect,1.4,};
	//render
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,minimaptexture);
	glVertexPointer(2,GL_FLOAT,0,minimapverts);
	glTexCoordPointer(2,GL_FLOAT,0,minimapcoord);
	glDrawArrays(GL_QUADS,0,4);	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	
	//player verts
	float playerverts[]={
		99.5/screenaspect,44,
		100.5/screenaspect,44,
		100.5/screenaspect,45,
		99.5/screenaspect,45,};
	//scale
	for(int a=0;a<4*2;a++)
		playerverts[a]*=0.025;	
	//render
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,playerverts);
	glDrawArrays(GL_QUADS,0,4);	
	glDisableClientState(GL_VERTEX_ARRAY);
	
	glPopMatrix();
	*/
}
