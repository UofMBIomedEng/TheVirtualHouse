void genworldgrid(){

	//clean the world grid
	for(int x=0; x<worldgridsizex; x++)
		for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				worldgrid[x][y][z][0]=empty_tile;
				worldgrid[x][y][z][1]=empty_tile;
			}
	
	//setup the island		
	/*
	bool watergrid[worldgridsizex][worldgridsizez];
	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++){
			watergrid[x][z]=1;
	
	}
	*/

	//setup streets
	/*
	bool streetgrid[worldgridsizex][worldgridsizez];
	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			streetgrid[x][z]=1;
	*/
	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			worldgrid[x][streetlevel][z][0]=grass_tile;
	
	//set up the foundation of the house

	const int house_low_z = 18;
	const int house_high_z = 30;
	const int house_low_x = 18;
	const int house_high_x = 30;

	//sidewalks
	for(int z=house_low_z+1; z<=(house_high_z-1); z++){
		worldgrid[house_low_x][streetlevel][z][0]=sidewalk_tile;
		worldgrid[house_low_x][streetlevel][z][1]=0;
		worldgrid[house_high_x][streetlevel][z][0]=sidewalk_tile;
		worldgrid[house_high_x][streetlevel][z][1]=2;
	}
	for(int x=house_low_x+1; x<=(house_high_x-1); x++){
		worldgrid[x][streetlevel][house_low_z][0]=sidewalk_tile;
		worldgrid[x][streetlevel][house_low_z][1]=3;
		worldgrid[x][streetlevel][house_high_z][0]=sidewalk_tile;
		worldgrid[x][streetlevel][house_high_z][1]=1;
	}

	//sidewalk corners
	worldgrid[house_high_z][streetlevel][house_low_z][0]=sidewalkcorner_tile;
	worldgrid[house_high_z][streetlevel][house_low_z][1]=3;
	worldgrid[house_low_z][streetlevel][house_low_z][0]=sidewalkcorner_tile;
	worldgrid[house_low_z][streetlevel][house_low_z][1]=0;
	worldgrid[house_low_z][streetlevel][house_high_z][0]=sidewalkcorner_tile;
	worldgrid[house_low_z][streetlevel][house_high_z][1]=1;
	worldgrid[house_high_z][streetlevel][house_high_z][0]=sidewalkcorner_tile;
	worldgrid[house_high_z][streetlevel][house_high_z][1]=2;

	/*
	//building carpet
	for(int z=house_low_z+2; z<=(house_high_z-2); z++)
		for(int x=house_low_x+2; x<=(house_high_x-2); x++)
			worldgrid[x][streetlevel][z][0]=10;
	*/

	//wall
	
	for (int y=0;y<=2;y++){
		for(int z=house_low_z+2; z<=(house_high_z-2); z++){
			worldgrid[house_low_x+1][streetlevel+y][z][0]=wall_tile;
			worldgrid[house_low_x+1][streetlevel+y][z][1]=0;
			worldgrid[house_high_x-1][streetlevel+y][z][0]=wall_tile;
			worldgrid[house_high_x-1][streetlevel+y][z][1]=2;
		}
		for(int x=house_low_x+2; x<=(house_high_x-2); x++){
			worldgrid[x][streetlevel+y][house_low_z+1][0]=wall_tile;
			worldgrid[x][streetlevel+y][house_low_z+1][1]=3;
			worldgrid[x][streetlevel+y][house_high_z-1][0]=wall_tile;
			worldgrid[x][streetlevel+y][house_high_z-1][1]=1;
		}

		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][0]=wallcorner_tile;
		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][1]=2;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][0]=wallcorner_tile;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][1]=3;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][0]=wallcorner_tile;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][1]=0;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][0]=wallcorner_tile;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][1]=1;
	}
		/*This was for keeping the sidewalk on the first floor, and the walls with panels added on the second and third floors
	for (int y=1;y<=2;y++)
	{
		for(int z=house_low_z+2; z<=(house_high_z-2); z++){
			worldgrid[house_low_x+1][streetlevel+y][z][0]=82;
			worldgrid[house_low_x+1][streetlevel+y][z][1]=0;
			worldgrid[house_high_x-1][streetlevel+y][z][0]=82;
			worldgrid[house_high_x-1][streetlevel+y][z][1]=2;
		}
		for(int x=house_low_x+2; x<=(house_high_x-2); x++){
			worldgrid[x][streetlevel+y][house_low_z+1][0]=82;
			worldgrid[x][streetlevel+y][house_low_z+1][1]=3;
			worldgrid[x][streetlevel+y][house_high_z-1][0]=82;
			worldgrid[x][streetlevel+y][house_high_z-1][1]=1;
		}

		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][0]=81;
		worldgrid[house_high_z-1][streetlevel+y][house_low_z+1][1]=2;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][0]=81;
		worldgrid[house_low_z+1][streetlevel+y][house_low_z+1][1]=3;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][0]=81;
		worldgrid[house_low_z+1][streetlevel+y][house_high_z-1][1]=0;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][0]=81;
		worldgrid[house_high_z-1][streetlevel+y][house_high_z-1][1]=1;
	}
	*/
	//building windows
	for(int y=0;y<=2;y++)
	{
		for(int j=1;j<4;j++)worldgrid[house_high_x-1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][0]=window_tile;
		for(int j=1;j<4;j++)worldgrid[house_low_x+1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][0]=window_tile;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_high_z-1][0]=window_tile;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_low_z+1][0]=window_tile;
		//adding window bars
	/*	
		for(int j=1;j<4;j++)worldgrid[house_high_x-1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][0]=99;
		for(int j=1;j<4;j++)worldgrid[house_low_x+1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][0]=99;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_high_z-1][0]=99;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_low_z+1][0]=99;
		
		 for(int j=1;j<4;j++)worldgrid[house_high_x-1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][1]=0;
		for(int j=1;j<4;j++)worldgrid[house_low_x+1][streetlevel+y][house_low_z+(j*(house_high_z-house_low_z)/4)][1]=0;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_high_z-1][1]=0;
		for(int j=1;j<4;j++)worldgrid[house_low_x+(j*(house_high_x-house_low_x)/4)][streetlevel+y][house_low_z+1][1]=0;
	*/
	}
	
	expectdist=0;    //reset the expected distance value

	if(allocentric){

		//5
		a_win_pos[0]=house_low_x+(2)*(house_high_x-house_low_x)/4;
		a_win_pos[1]=streetlevel+1;
		a_win_pos[2]=house_low_z+1;
		//5

		//2
		b_win_pos[0]=house_low_x+((3)*(house_high_x-house_low_x)/4);
		b_win_pos[1]=streetlevel+2;
		b_win_pos[2]=house_high_z-1;
		//2

		//6
		c_win_pos[0]=house_high_x-1;
		c_win_pos[1]=streetlevel+2;
		c_win_pos[2]=house_low_z+(2)*(house_high_z-house_low_z)/4;
		//6

		if(kidmode){
			worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=kittenwall_tile; 	
			worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile; 
			worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;
		}
		else
		{
			worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=circle_window_tile; 	
			worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
			worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;
		}
		switch(((trial-1)%3)+1){
			case 1:
				//climb the stairs
				expectdist += 6;
				//for the clue chart resembles letter W
				win_clue=87;
			break;
			case 2:
				//climb the stairs
				expectdist += 12;
				//for the clue chart resembles letter F
				win_clue=70;
			break;
			case 3:
				//climb the stairs
				expectdist += 13;
				//for the clue chart resembles letter H
				win_clue=72;
			break;
		}	
	}
	else{
		//objective windows
		switch(trial){
			case 1:

				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=76+rand_sel;
				//1
				a_win_pos[0]=house_low_x+1;
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//1

				//to the target window
				expectdist += 1 + sqrt(((22.7-a_win_pos[0])*(22.7-a_win_pos[0]))+((26-a_win_pos[2])*(26-a_win_pos[2])));

				//4
				b_win_pos[0]=house_high_x-1;
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//4

				//3
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+1;
				//3

			break;
			case 2:
				//climb the stairs
				expectdist += (2.6*2);

				rand_sel=((int)rand()%3)+1;
				win_clue=67+rand_sel;
				//2
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_high_z-1;
				//2

				//to the target window
				expectdist += 3 + sqrt(((22.3-a_win_pos[0])*(22.3-a_win_pos[0]))+((25.5-a_win_pos[2])*(25.5-a_win_pos[2])));

				//7
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_high_z-1;
				//7

				//8
				c_win_pos[0]=house_low_x+1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//8
			break;
			case 3:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=77-rand_sel;
				//3
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+1;
				//3

				//to the target window
				expectdist += sqrt(((22.8-a_win_pos[0])*(22.8-a_win_pos[0]))+((23.6-a_win_pos[2])*(23.6-a_win_pos[2])));

				//6
				b_win_pos[0]=house_high_x-1;
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6
			
				//5
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+1;
				c_win_pos[2]=house_low_z+1;
				//5

			break;
			case 4:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=86-rand_sel;
				//4
				a_win_pos[0]=house_high_x-1;
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//4

				//to the target window
				expectdist += 2.5 + sqrt(((26.5-a_win_pos[0])*(26.5-a_win_pos[0]))+((25.7-a_win_pos[2])*(25.7-a_win_pos[2])));

				//3
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+1;
				//3

				//6
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6

			break;
			case 5:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=89-rand_sel;
				//5
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_low_z+1;
				//5

				//to the target window
				expectdist += 3.8 + sqrt(((22.1-a_win_pos[0])*(22.1-a_win_pos[0]))+((23.4-a_win_pos[2])*(23.4-a_win_pos[2])));

				//1
				b_win_pos[0]=house_low_x+1;
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//1

				//4
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+1;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//4

			break;
			case 6:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=74-rand_sel;
				//6
				a_win_pos[0]=house_high_x-1;
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//6

				//to the target window
				expectdist += 2.5 + sqrt(((26.3-a_win_pos[0])*(26.3-a_win_pos[0]))+((23-a_win_pos[2])*(23-a_win_pos[2])));

				//8
				b_win_pos[0]=house_low_x+1;
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//8

				//2
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_high_z-1;
				//2

			break;
			case 7:
				//climb the stairs
				expectdist += 2.6;

				rand_sel=((int)rand()%3)+1;
				win_clue=79+rand_sel;
				//7
				a_win_pos[0]=house_low_x+((rand_sel)*(house_high_x-house_low_x)/4);
				a_win_pos[1]=streetlevel+1;
				a_win_pos[2]=house_high_z-1;
				//7

				//to the target window
				expectdist += sqrt(((22.7-a_win_pos[0])*(22.7-a_win_pos[0]))+((26-a_win_pos[2])*(26-a_win_pos[2])));

				//5
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+1;
				b_win_pos[2]=house_low_z+1;
				//5

				//3
				c_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+1;
				//3

			break;
			case 8:
				//climb the stairs
				expectdist += (2.6*2)+(1.3);

				rand_sel=((int)rand()%3)+1;
				win_clue=64+rand_sel;
				//8
				a_win_pos[0]=house_low_x+1;
				a_win_pos[1]=streetlevel+2;
				a_win_pos[2]=house_low_z+((rand_sel)*(house_high_z-house_low_z)/4);
				//8

				//to the target window
				expectdist += sqrt(((22.8-a_win_pos[0])*(22.8-a_win_pos[0]))+((23.6-a_win_pos[2])*(23.6-a_win_pos[2])));

				//2
				b_win_pos[0]=house_low_x+((((int)rand()%3)+1)*(house_high_x-house_low_x)/4);
				b_win_pos[1]=streetlevel+2;
				b_win_pos[2]=house_high_z-1;
				//2

				//6
				c_win_pos[0]=house_high_x-1;
				c_win_pos[1]=streetlevel+2;
				c_win_pos[2]=house_low_z+((((int)rand()%3)+1)*(house_high_z-house_low_z)/4);
				//6

			break;
		}

		if(kidmode){
			switch(targetwin)
			{
			case 0:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=kittenwall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile;  
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;  
						break; 

			case 1:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=puppywall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=kittenwall_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=cowwall_tile;  
						break;

			case 2:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=cowwall_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=puppywall_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=kittenwall_tile;  
						break;
			}
		}
		else
		{
			switch(targetwin)
			{
			case 0:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=circle_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;  
						break;

			case 1:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=X_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=circle_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=triangle_window_tile;  
						break;

			case 2:	worldgrid[a_win_pos[0]][a_win_pos[1]][a_win_pos[2]][0]=triangle_window_tile; 	
				worldgrid[b_win_pos[0]][b_win_pos[1]][b_win_pos[2]][0]=X_window_tile; 
				worldgrid[c_win_pos[0]][c_win_pos[1]][c_win_pos[2]][0]=circle_window_tile;  
						break;
			}
		}
	}

	//building door
	worldgrid[house_high_x-3-(rand()%(house_high_x-house_low_x-6))][streetlevel][house_low_z+1][0]=door_tile;
	worldgrid[house_high_x-3-(rand()%(house_high_x-house_low_x-6))][streetlevel][house_high_z-1][0]=door_tile;
	int entrydoorz=house_high_z-3-(rand()%(house_high_z-house_low_z-6));
	worldgrid[house_low_x+1][streetlevel][entrydoorz][0]=door_tile;
	worldgrid[house_high_x-1][streetlevel][house_high_z-3-(rand()%(house_high_z-house_low_z-6))][0]=door_tile;

	//calculated the expected distance
	//to the entrance door
	expectdist += sqrt(((float)((worldgridsizex/2)-((worldgridsizex/3))-(house_low_x+1))*((worldgridsizex/2)-((worldgridsizex/3))-(house_low_x+1))) 
					+(((worldgridsizex/2)-(entrydoorz))*((worldgridsizex/2)-(entrydoorz))));
	//to the stairs
	expectdist += sqrt((((23.6)-(house_low_x+1))*((23.6)-(house_low_x+1)))
					+(((23.3)-(entrydoorz))*((23.3)-(entrydoorz))));
	

	//floor base
	for(int y=0;y<=2;y++)
		for(int z=house_low_z+2; z<=(house_high_z-2); z++)
			for(int x=house_low_x+2; x<=(house_high_x-2); x++)
				worldgrid[x][streetlevel+y][z][0]=hardwood_tile;

	switch(stairtype){
	case 1:

	//stairs at 180 degrees
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;

	
	//isolators
	/*
	worldgrid[24][streetlevel][26][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel][26][1]=1;
	worldgrid[25][streetlevel][23][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel][23][1]=3;

	worldgrid[25][streetlevel+1][26][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+1][26][1]=1;
	worldgrid[26][streetlevel+1][26][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+1][26][1]=1;
	worldgrid[24][streetlevel+1][23][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+1][23][1]=3;
	worldgrid[23][streetlevel+1][23][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+1][23][1]=3;
	
	worldgrid[23][streetlevel+2][26][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+2][26][1]=1;
	worldgrid[26][streetlevel+2][23][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+2][23][1]=3;
	worldgrid[27][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][24][1]=2;
	worldgrid[27][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][25][1]=2;
	worldgrid[25][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+2][24][1]=0;
	worldgrid[25][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+2][25][1]=0;

	worldgrid[24][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+2][24][1]=2;
	worldgrid[24][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+2][25][1]=2;
	worldgrid[22][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][24][1]=0;
	worldgrid[22][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][25][1]=0;
	break;
	*/
	case 2:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	//isolators
	/*
	//first floor covering stairs
	worldgrid[24][streetlevel][26][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel][26][1]=1;
	worldgrid[25][streetlevel][23][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel][23][1]=3;
	//second floor covering stairs
	worldgrid[25][streetlevel+1][26][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+1][26][1]=1;
	worldgrid[26][streetlevel+1][25][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+1][25][1]=2;
	worldgrid[26][streetlevel+1][24][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+1][24][1]=2;
	worldgrid[24][streetlevel+1][23][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+1][23][1]=3;
	worldgrid[23][streetlevel+1][24][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+1][24][1]=0;
	worldgrid[23][streetlevel+1][25][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+1][25][1]=0;
	//3rd floor covering stairs
	worldgrid[25][streetlevel+2][23][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+2][23][1]=0;
	worldgrid[26][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+2][24][1]=1;
	worldgrid[26][streetlevel+2][22][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+2][22][1]=3;
	worldgrid[27][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][24][1]=1;
	worldgrid[27][streetlevel+2][22][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][22][1]=3;

	worldgrid[24][streetlevel+2][26][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+2][26][1]=2;
	worldgrid[22][streetlevel+2][27][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][27][1]=1;
	worldgrid[22][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][25][1]=3;
	worldgrid[23][streetlevel+2][27][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+2][27][1]=1;
	worldgrid[23][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+2][25][1]=3;
	*/

	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=stairs_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=stairs_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	case 3:

	//stairs at 180 degrees
		worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+2][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)][0]=0;

	
	//isolators
	
	worldgrid[24][streetlevel][26][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel][26][1]=1;
	worldgrid[25][streetlevel][23][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel][23][1]=3;

	worldgrid[25][streetlevel+1][26][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+1][26][1]=1;
	worldgrid[26][streetlevel+1][26][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+1][26][1]=1;
	worldgrid[24][streetlevel+1][23][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+1][23][1]=3;
	worldgrid[23][streetlevel+1][23][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+1][23][1]=3;
	
	worldgrid[23][streetlevel+2][26][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+2][26][1]=1;
	worldgrid[26][streetlevel+2][23][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+2][23][1]=3;
	worldgrid[27][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][24][1]=2;
	worldgrid[27][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][25][1]=2;
	worldgrid[25][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+2][24][1]=0;
	worldgrid[25][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+2][25][1]=0;

	worldgrid[24][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+2][24][1]=2;
	worldgrid[24][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+2][25][1]=2;
	worldgrid[22][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][24][1]=0;
	worldgrid[22][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][25][1]=0;

	break;
	
	case 4:
	//stairs at 90 degrees (floor not fixed for this configuration)
	//holes in floor
	//second floor floor
	worldgrid[25][streetlevel+1][24][0]=empty_tile;//top of stairs...
	worldgrid[25][streetlevel+1][25][0]=empty_tile;
	worldgrid[24][streetlevel+1][24][0]=empty_tile;
	worldgrid[24][streetlevel+1][25][0]=empty_tile;//...
	worldgrid[26][streetlevel+1][23][0]=empty_tile;//bottom of stairs...
	worldgrid[27][streetlevel+1][23][0]=empty_tile;
	worldgrid[23][streetlevel+1][26][0]=empty_tile;
	worldgrid[22][streetlevel+1][26][0]=empty_tile;//...
	//3rd floor floor
	worldgrid[26][streetlevel+2][23][0]=empty_tile;
	worldgrid[27][streetlevel+2][23][0]=empty_tile;
	worldgrid[23][streetlevel+2][26][0]=empty_tile;
	worldgrid[22][streetlevel+2][26][0]=empty_tile;
	//isolators
	//first floor covering stairs
	worldgrid[24][streetlevel][26][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel][26][1]=1;
	worldgrid[25][streetlevel][23][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel][23][1]=3;
	//second floor covering stairs
	worldgrid[25][streetlevel+1][26][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+1][26][1]=1;
	worldgrid[26][streetlevel+1][25][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+1][25][1]=2;
	worldgrid[26][streetlevel+1][24][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+1][24][1]=2;
	worldgrid[24][streetlevel+1][23][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+1][23][1]=3;
	worldgrid[23][streetlevel+1][24][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+1][24][1]=0;
	worldgrid[23][streetlevel+1][25][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+1][25][1]=0;
	//3rd floor covering stairs
	worldgrid[25][streetlevel+2][23][0]=stairs_isolator_tile;
	worldgrid[25][streetlevel+2][23][1]=0;
	worldgrid[26][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+2][24][1]=1;
	worldgrid[26][streetlevel+2][22][0]=stairs_isolator_tile;
	worldgrid[26][streetlevel+2][22][1]=3;
	worldgrid[27][streetlevel+2][24][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][24][1]=1;
	worldgrid[27][streetlevel+2][22][0]=stairs_isolator_tile;
	worldgrid[27][streetlevel+2][22][1]=3;

	worldgrid[24][streetlevel+2][26][0]=stairs_isolator_tile;
	worldgrid[24][streetlevel+2][26][1]=2;
	worldgrid[22][streetlevel+2][27][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][27][1]=1;
	worldgrid[22][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[22][streetlevel+2][25][1]=3;
	worldgrid[23][streetlevel+2][27][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+2][27][1]=1;
	worldgrid[23][streetlevel+2][25][0]=stairs_isolator_tile;
	worldgrid[23][streetlevel+2][25][1]=3;

	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=ramp_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=ramp_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	}
	//roof
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+3][house_low_z+((house_high_z-house_low_z)/2)][0]=roof_tile;

	

	if(allocentric)
	{
		worldgrid[1+house_low_x+(2)*(house_high_x-house_low_x)/4][streetlevel+1][house_high_z-1][0]=timhortonswall_tile;
		worldgrid[house_high_x-2][streetlevel+2][house_high_z-1][0]=atmmachinewall_tile;
	}

	//block the edges of the world
	/*
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<streetlevel; y++)
	for(int z=0; z<worldgridsizez; z++)
	if(x==0 || x==worldgridsizex-1
	|| y==0 || y==worldgridsizey-1
	|| z==0 || z==worldgridsizez-1){
		worldgrid[x][y][z][0]=7;
		worldgrid[x][y][z][1]=0;

	}
	*/

	

}
