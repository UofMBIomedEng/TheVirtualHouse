void TestApp::play(float gamespeed){


	//decrease view range
	if(mpKey[FWInput::Channel_Key_1]->getBoolTrue()){
		worldtileviewrange-=1;
		if(worldtileviewrange<0)worldtileviewrange=0;
		if(!usetileswhenrendering)genvisibleworld();
	}

	//increase view range
	if(mpKey[FWInput::Channel_Key_2]->getBoolTrue()){
		worldtileviewrange+=1;
		if(worldtileviewrange>100)worldtileviewrange=100;
		if(!usetileswhenrendering)genvisibleworld();
	}

	//Field of view
	if(mpKey[FWInput::Channel_Key_D]->getBoolValue())
	if(screenfov<120)
			screenfov+=.1;

	if(mpKey[FWInput::Channel_Key_F]->getBoolValue())
		if(screenfov>10)
			screenfov-=.1;

	//Control Latency
	if(mpKey[FWInput::Channel_Key_L]->getBoolValue())
		if(latency<max_latency)
			latency++;

	if(mpKey[FWInput::Channel_Key_K]->getBoolValue())
		if(latency>0)
			latency--;

//	Textures on off
	if(mpKey[FWInput::Channel_Key_3]->getBoolTrue())
		if(usetextures==1){usetextures=0;}else{usetextures=1;}

//	start the intro	
	if((mpKey[FWInput::Channel_Key_S]->getBoolTrue())||(joystick.wButtons==256))
		if(start_motion==0){start_motion=1;tmpcamyang=camyang;start_time=elapsedtime;}

//  Quit by Q
	if(mpKey[FWInput::Channel_Key_Q]->getBoolTrue()||mpKey[FWInput::Channel_Key_Escape]->getBoolTrue()) exit(0);

//  Free camera on off
	if(mpKey[FWInput::Channel_Key_M]->getBoolTrue())
		if(freecamera==1){freecamera=0;}else{freecamera=1;}

//  Show player on off
	if(mpKey[FWInput::Channel_Key_P]->getBoolTrue())
		if(showplayer==1){showplayer=0;}else{showplayer=1;}

//  Auto exit on off
	if(mpKey[FWInput::Channel_Key_E]->getBoolTrue())
		if(autoexit==1){autoexit=0;}else{autoexit=1;}

//	Show info
	if(mpKey[FWInput::Channel_Key_I]->getBoolTrue())
		if(showinfo==1){showinfo=0;}else{showinfo=1;}

//	Use Joystick
	if(mpKey[FWInput::Channel_Key_J]->getBoolTrue())
		if(usejoystick==1){usejoystick=0;calibjoy=0;}else{usejoystick=1;calibjoy=0;}

//	Run Joystick calibration
	if(mpKey[FWInput::Channel_Key_C]->getBoolTrue())
		if(!calibjoy) calibjoy=WinExec("control joy.cpl", SW_NORMAL);

//  Player hight
	if(mpKey[FWInput::Channel_Key_H]->getBoolTrue())
		if(playerhight<6){playerhight+=.1;}else{playerhight=3;}

//	for(int gameloops=0; gameloops<2; gameloops++){

	float oldx=playerxpos;
	float oldy=playerypos;
	float oldz=playerzpos;

// intro
	const int turn_duration = 40;
	if(start_motion)
	{
		motion_time=(elapsedtime-start_time);

		camxpos=(worldtilesize*worldgridsizex/2)-((worldtilesize*worldgridsizex/3))*cos(motion_time*PI/(turn_duration/2));
		camzpos=(worldtilesize*worldgridsizex/2)+((worldtilesize*worldgridsizez/3))*sin(motion_time*PI/(turn_duration/2));
		camypos=streetlevel*worldtilesize;
		camyang=-motion_time*PI/(turn_duration/2)+(radiansindegree*450);
		if(motion_time>turn_duration){ start_motion = 0; camyang=tmpcamyang; }
	}
	
	//update entities
	bool saving=0;
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++)
	for(int e=0; e<entitycount[x][y][z]; e++){
		if(entitylist[x][y][z][e]->type==entitytype_disccartridge){
			entitylist[x][y][z][e]->xang+=entitylist[x][y][z][e]->xangmov*gamespeed;
			entitylist[x][y][z][e]->yang+=entitylist[x][y][z][e]->yangmov*gamespeed;
			entitylist[x][y][z][e]->zang+=entitylist[x][y][z][e]->zangmov*gamespeed;
			if(dist3d(
				entitylist[x][y][z][e]->xpos,
				entitylist[x][y][z][e]->ypos,
				entitylist[x][y][z][e]->zpos,
				playerxpos,playerypos,playerzpos)<3.25f){
					delete entitylist[x][y][z][e];
					if(e<entitycount[x][y][z]-1)for(int b=e;b<entitycount[x][y][z];b++)entitylist[x][y][z][b]=entitylist[x][y][z][b+1];
					entitycount[x][y][z]-=1;
					e--;
					collectablesfound++;
					//save();
					saving=1;
			}
		}
		if(saving==0)
		if(entitylist[x][y][z][e]->type==entitytype_elevator){
			entitylist[x][y][z][e]->ypos+=entitylist[x][y][z][e]->yposmov*gamespeed;
			if(entitylist[x][y][z][e]->yposmov>0){
				if(entitylist[x][y][z][e]->ypos>y*worldtilesize+0.5*worldtilesize
				&& entitycount[x][y+1][z]<maxentities){
					entitylist[x][y+1][z][(int)entitycount[x][y+1][z]]=entitylist[x][y][z][e];
					entitycount[x][y+1][z]+=1;
					removeentityfromlist(x,y,z,e);
				}
				if(worldgrid[x][y][z][0]==34
				&& entitylist[x][y][z][e]->ypos>y*worldtilesize){
					entitylist[x][y][z][e]->ypos=y*worldtilesize;
					entitylist[x][y][z][e]->yposmov*=-1;
				}
			}else{
				if(entitylist[x][y][z][e]->ypos<y*worldtilesize-0.5*worldtilesize
				&& entitycount[x][y-1][z]<maxentities){
					entitylist[x][y-1][z][(int)entitycount[x][y-1][z]]=entitylist[x][y][z][e];
					entitycount[x][y-1][z]+=1;
					removeentityfromlist(x,y,z,e);
				}
				if(worldgrid[x][y][z][0]==32
				&& entitylist[x][y][z][e]->ypos<y*worldtilesize){
					entitylist[x][y][z][e]->ypos=y*worldtilesize;
					entitylist[x][y][z][e]->yposmov*=-1;
				}
			}
		}
	}

	//turn
	setmouseclientrelativefalse();
	if(freecamera){
		camxang+=mpMouseY->getFloatValue()*0.001;          //sets the camera angle movement using mouse
		camyang+=mpMouseX->getFloatValue()*0.001;
		
		//dont look too far up or down
		if(camxang>90*radiansindegree)camxang=90*radiansindegree;
		if(camxang<-90*radiansindegree)camxang=-90*radiansindegree;
		if(camyang<0)camyang+=360*radiansindegree;
		if(camyang>360*radiansindegree)camyang-=360*radiansindegree;
	}

	

	//Log file writer 
	if(!start_motion)fprintf(pFile,"%3.4f,%3.4f,%3.4f,%3.4f,%3.4f,%3.4f,%.2f,%.2f,%.2f\n",playerxpos,playerypos,playerzpos,camxang,camyang,camzang,elapseddist,expectdist,elapsedtime);
	//here, can add what was wrong and how many times it was wrong, ie floor, wall, side
	
	if(playerjumping){
		if(mpKey[FWInput::Channel_Key_Space]->getBoolValue() && playeryposmov>0.1){
			playeryposmov+=(0.005+playeryposmov*0.08)*gamespeed;
		}else{
			playerjumping=0;
		}
	}
	if(playergrounded){
		playerjumping=0;
		playeryposmov-=0.01*gamespeed;
		if(testmode&&mpKey[FWInput::Channel_Key_Space]->getBoolValue()){
			playeryposmov=0.65;
			playerjumping=1;
		}
	}else{
		playeryposmov-=0.035*gamespeed;
	}
	
	playerxpos+=playerxposmov*gamespeed;
	playerypos+=playeryposmov*gamespeed;
	playerzpos+=playerzposmov*gamespeed;

	//bump into the world
	playerypos+=1.25;
	int lowx=highint((int)((playerxpos+worldtilesize*0.5)/worldtilesize-2),0);
	int lowy=highint((int)((playerypos+worldtilesize*0.5)/worldtilesize-2),0);
	int lowz=highint((int)((playerzpos+worldtilesize*0.5)/worldtilesize-2),0);
	int highx=lowint((int)((playerxpos+worldtilesize*0.5)/worldtilesize+2+1),worldgridsizex);
	int highy=lowint((int)((playerypos+worldtilesize*0.5)/worldtilesize+2+1),worldgridsizey);
	int highz=lowint((int)((playerzpos+worldtilesize*0.5)/worldtilesize+2+1),worldgridsizez);
	for(int x=lowx; x<highx; x++)
		for(int y=lowy; y<highy; y++)
			for(int z=lowz; z<highz; z++){
				if(worldgrid[x][y][z][0])
					spherebumpmesh(playerxpos,playerypos,playerzpos,1.25,
					x*worldtilesize,y*worldtilesize,z*worldtilesize,0,
					worldtilecollisionmesh[(int)worldgrid[x][y][z][0]][(int)worldgrid[x][y][z][1]],1,0);

				for(int a=0; a<entitycount[x][y][z]; a++){
					if(entitytypesolid[entitylist[x][y][z][a]->type]==1){
						spherebumpmesh(playerxpos,playerypos,playerzpos,1.25,
						entitylist[x][y][z][a]->xpos,
						entitylist[x][y][z][a]->ypos,
						entitylist[x][y][z][a]->zpos,
						entitylist[x][y][z][a]->yang,
						entitycollisionmesh[entitylist[x][y][z][a]->type],1,0);
					}
				}
			}

	for(int x=lowx; x<highx; x++)
		for(int y=lowy; y<highy; y++)
			for(int z=lowz; z<highz; z++)
				if(worldgrid[x][y][z][0]){
					if(worldgrid[x][y][z][0])
						spherebumpmesh(playerxpos,playerypos,playerzpos,1.25,
						x*worldtilesize,y*worldtilesize,z*worldtilesize,0,
						worldtilecollisionmesh[(int)worldgrid[x][y][z][0]][(int)worldgrid[x][y][z][1]],0,1);
					for(int a=0; a<entitycount[x][y][z]; a++){
						if(entitytypesolid[entitylist[x][y][z][a]->type]==1){
							spherebumpmesh(playerxpos,playerypos,playerzpos,1.25,
							entitylist[x][y][z][a]->xpos,
							entitylist[x][y][z][a]->ypos,
							entitylist[x][y][z][a]->zpos,
							entitylist[x][y][z][a]->yang,
							entitycollisionmesh[entitylist[x][y][z][a]->type],0,1);
						}
					}
				}
	playerypos-=1.25;
	if(playerypos>(float)(oldy+playeryposmov*gamespeed)+0.001){
		playergrounded=1;
	}else	playergrounded=0;	
	
	//adjust momentum
	playerxposmov=(playerxpos-oldx)/gamespeed;
	playeryposmov=(playerypos-oldy)/gamespeed;
	playerzposmov=(playerzpos-oldz)/gamespeed;

	//adjust momentum
	playerxposmov-=playerxposmov*0.1*gamespeed;
	playeryposmov-=playeryposmov*0.04*gamespeed;
	playerzposmov-=playerzposmov*0.1*gamespeed;

	//animate player
	if(showplayer){
		float movespeed=dist2d(0,0,playerxposmov,playerzposmov)*0.25;
		if(playerframe<goalplayerframe){
			playerframe+=movespeed*gamespeed;
			if(playerframe>goalplayerframe){
				playerframe=goalplayerframe;
				if(goalplayerframe==3)goalplayerframe=4;
				else goalplayerframe=3;
			}
		}
	
		if(playerframe>goalplayerframe){
			playerframe-=movespeed*gamespeed;
			if(playerframe<goalplayerframe){
				playerframe=goalplayerframe;
				if(goalplayerframe==3)goalplayerframe=4;
				else goalplayerframe=3;
			}
		}
	}
	else
	{	
		float movespeed=dist2d(0,0,playerxposmov,playerzposmov)*0.25;
		swingtime+=movespeed*5;
		heightswing=0.02*(cos(swingtime*2));

		if((playerxpos>164)&&(playerxpos<324)&&(playerzpos>164)&&(playerzpos<324))			//wheelchair wiggling effect of the grass
			latswing=0;
		else
			latswing=0.005*sin(swingtime);
	}
	//turn player
	playeryang=turntoangle(
		playeryang,
		atan2(playerzposmov,playerxposmov),
		dist2d(0,0,playerxposmov,playerzposmov)*0.3*gamespeed);            //turning speed

	if(!(usejoystick||freecamera)){
		if(showplayer) camxang=15*radiansindegree;
		else camxang=0;
	}
	
	if(latency_write_pointer<max_latency)
		latency_write_pointer++;
	else
		latency_write_pointer=0;

	latency_read_pointer=latency_write_pointer-latency;
	if(latency_read_pointer<0)
		latency_read_pointer+=max_latency;

	control_buffer[0][latency_write_pointer]=mpKey[FWInput::Channel_Key_Up]->getBoolValue();
	control_buffer[1][latency_write_pointer]=mpKey[FWInput::Channel_Key_Down]->getBoolValue();
	control_buffer[2][latency_write_pointer]=mpKey[FWInput::Channel_Key_Left]->getBoolValue();
	control_buffer[3][latency_write_pointer]=mpKey[FWInput::Channel_Key_Right]->getBoolValue();

	//Arrow key control
	if(control_buffer[0][latency_read_pointer]){
		playerxposmov+=gamespeed*(0.04*cos(-camxang)*cos(camyang-90*radiansindegree));
		//playeryposmov+=(0.04*sin(-camxang));
		playerzposmov+=gamespeed*(0.04*cos(-camxang)*sin(camyang-90*radiansindegree));
	}
	
	if(control_buffer[1][latency_read_pointer]){
		playerxposmov-=gamespeed*(0.04*cos(-camxang)*cos(camyang-90*radiansindegree));
		//playeryposmov-=(0.04*sin(-camxang));
		playerzposmov-=gamespeed*(0.04*cos(-camxang)*sin(camyang-90*radiansindegree));
	}

	if(control_buffer[2][latency_read_pointer])
		if(!start_motion)camyang-=gamespeed*0.01;

	if(control_buffer[3][latency_read_pointer])
		if(!start_motion)camyang+=gamespeed*0.01;

	if(countdownjoystickstart) countdownjoystickstart--;
	if(countdownjoystickstart==2) usejoystick = 1; 
	if(usejoystick){											//Joystick control	

		if(joyGetPos(0,&joystick))	usejoystick=0;				//obtain joystick value and check the presence
		else{
			if(((float)joystick.wXpos-32768>1500)||((float)joystick.wXpos-32768<-1500)) camyang+=((float)joystick.wXpos-32768)*(0.01/32768)*JoyAngVel*0.96*gamespeed;	
			if((32768-(float)joystick.wYpos>1500)||(32768-(float)joystick.wYpos<-1500)){
				if(!start_motion){	
					playerxposmov+=(32768-(float)joystick.wYpos)*(gamespeed*0.58*JoyTransVel/32768)*cos(-camxang)*cos(camyang-90*radiansindegree);
					playerzposmov+=(32768-(float)joystick.wYpos)*(gamespeed*0.58*JoyTransVel/32768)*cos(-camxang)*sin(camyang-90*radiansindegree);
					
				}
				
			}
		//	playeryposmov+=(32768-(float)joystick.wYpos)*(JoyTransVel/32768)*sin(-camxang);
		
		//	camxang=((float)joystick.wZpos-32768)*(45*radiansindegree/32768);	
			camxang=0*radiansindegree;
		}
	}

	//position camera
	
	float camdist;
	if(showplayer)camdist=5;
	else camdist=1;
	if(!start_motion)camxpos=playerxpos-camdist*cos(-camxang)*cos(camyang-90*radiansindegree)+latswing;
	if(showplayer)camypos=playerypos-camdist*sin(-camxang)+5;
	else camypos=playerypos-camdist*sin(-camxang)+playerhight+heightswing;
	if(!start_motion)camzpos=playerzpos-camdist*cos(-camxang)*sin(camyang-90*radiansindegree)+latswing;
	if(!showplayer&&(dist2d(0,0,playerxposmov,playerzposmov)>0.1))
		camzang=latswing*dist2d(0,0,playerxposmov,playerzposmov);

	if(showplayer) camzang=0;
	else{
	//	if(mpKey[FWInput::Channel_Key_L]->getBoolValue()) camzang+=0.01;
	//	if(mpKey[FWInput::Channel_Key_R]->getBoolValue()) camzang-=0.01;
	}

	//get grid position
	playerxgridpos=(int)((playerxpos+worldtilesize*0.5)/worldtilesize);
	playerygridpos=(int)((playerypos+worldtilesize*0.5)/worldtilesize);
	playerzgridpos=(int)((playerzpos+worldtilesize*0.5)/worldtilesize);
	int oldxgridpos=(int)((oldx+worldtilesize*0.5)/worldtilesize);
	int oldygridpos=(int)((oldy+worldtilesize*0.5)/worldtilesize);
	int oldzgridpos=(int)((oldz+worldtilesize*0.5)/worldtilesize);
	if(!usetileswhenrendering)
	if(oldxgridpos!=playerxgridpos
	|| oldygridpos!=playerygridpos
	|| oldzgridpos!=playerzgridpos)genvisibleworld();

	//integrate the elapsed distance
	if(!start_motion){
		elapseddist+=sqrt(((oldx-playerxpos)*(oldx-playerxpos))+((oldy-playerypos)*(oldy-playerypos))+((oldz-playerzpos)*(oldz-playerzpos)))/worldtilesize;
	}


	//animate the water
	/*
	if(waterdirection==0){
		waterscale+=0.04*gamespeed;
		if(waterscale>1.25){
			waterscale=1.25;
			waterdirection=1;
		}
	}else{
		waterscale-=0.04*gamespeed;
		if(waterscale<0.25){
			waterscale=0.25;
			waterdirection=0;
		}
	}
	*/




}
