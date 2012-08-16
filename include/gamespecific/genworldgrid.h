void genworldgrid(){

	//windows locations
	const int clue_win_array[9][9]={
			{000,00,0,00,00,0,00,0,0},
			{'M',18,3,21,18,3,28,27,25},			//1
			{'D',21,4,31,28,4,31,27,31},				//2
			{'J',28,4,18,21,4,18,28,33},				//3
			{'S',31,3,28,31,3,21,26,28},				//4
			{'V',28,3,18,21,3,18,26,27},				//5
			{'G',31,4,28,31,4,21,29,27},				//6
			{'P',21,3,31,28,3,31,25,25},				//7
			{'A',18,4,21,18,4,28,29,26}};				//8

			//Zeros are placed because, I got used to Matlab and that caused these problems

	//clean the world grid
	for(int x=0; x<worldgridsizex; x++)
		for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				worldgrid[x][y][z][0]=empty_tile;
				worldgrid[x][y][z][1]=empty_tile;
			}
	//Place the grass
	for(int x=0; x<worldgridsizex; x++)
		for(int z=0; z<worldgridsizez; z++)
			worldgrid[x][streetlevel][z][0]=grass_tile;
	
	//set up the foundation of the house
	const int house_low_z = 17;
	const int house_high_z = 32;
	const int house_low_x = 17;
	const int house_high_x = 32;

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



	//wall
	for (int y=0;y<1;y++){ //changed so it only covers the first floor
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

	//building first floor windows
	//wall 1
	worldgrid[21][streetlevel][18][0]=window_tile;
	worldgrid[21][streetlevel][18][1]=3;
	worldgrid[24][streetlevel][18][0]=window_tile;
	worldgrid[24][streetlevel][18][1]=3;
	worldgrid[28][streetlevel][18][0]=window_tile;
	worldgrid[28][streetlevel][18][1]=3;
	//wall 2
	worldgrid[18][streetlevel][21][0]=window_tile;
	worldgrid[18][streetlevel][21][1]=0;
	worldgrid[18][streetlevel][25][0]=window_tile;
	worldgrid[18][streetlevel][25][1]=0;
	worldgrid[18][streetlevel][28][0]=window_tile;
	worldgrid[18][streetlevel][28][1]=0;
	//wall 3
	worldgrid[21][streetlevel][31][0]=window_tile;
	worldgrid[21][streetlevel][31][1]=1;
	worldgrid[25][streetlevel][31][0]=window_tile;
	worldgrid[25][streetlevel][31][1]=1;
	worldgrid[28][streetlevel][31][0]=window_tile;
	worldgrid[28][streetlevel][31][1]=1;
	//wall 4
	worldgrid[31][streetlevel][28][0]=window_tile;
	worldgrid[31][streetlevel][28][1]=2;
	worldgrid[31][streetlevel][24][0]=window_tile;
	worldgrid[31][streetlevel][24][1]=2;
	worldgrid[31][streetlevel][21][0]=window_tile;
	worldgrid[31][streetlevel][21][1]=2;
	


	//building door
	/*
	//this builds doors in random locations
	worldgrid[house_high_x-3-(rand()%(house_high_x-house_low_x-6))][streetlevel][house_low_z+1][0]=door_tile;
	worldgrid[house_high_x-3-(rand()%(house_high_x-house_low_x-6))][streetlevel][house_high_z-1][0]=door_tile;
	int entrydoorz=house_high_z-3-(rand()%(house_high_z-house_low_z-6));
	worldgrid[house_low_x+1][streetlevel][entrydoorz][0]=door_tile;
	worldgrid[house_high_x-1][streetlevel][house_high_z-3-(rand()%(house_high_z-house_low_z-6))][0]=door_tile;
	*/
	worldgrid[25][streetlevel][18][0]=door_tile;
	worldgrid[24][streetlevel][31][0]=door_tile;
	worldgrid[18][streetlevel][24][0]=door_tile;
	worldgrid[31][streetlevel][25][0]=door_tile;

	//floor base
	for(int y=0;y<=2;y++)
		for(int z=house_low_z+2; z<=(house_high_z-2); z++)
			for(int x=house_low_x+2; x<=(house_high_x-2); x++)
				worldgrid[x][streetlevel+y][z][0]=hardwood_tile;
	//stairs

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
	break;
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

	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=stairs_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=stairs2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	break;
	case 3:

	//ramps at 180 degrees
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

	break;
	
	case 4:
	//ramps at 90 degrees (floor not fixed for this configuration)
	
	//TEST
		//holes in floor
		worldgrid[24][streetlevel+2][24][0]=empty_tile;//3rd
		worldgrid[24][streetlevel+2][23][0]=empty_tile;
		worldgrid[24][streetlevel+1][24][0]=empty_tile;//2nd
		worldgrid[24][streetlevel+1][23][0]=empty_tile;
		worldgrid[24][streetlevel][24][0]=empty_tile;//1st
		worldgrid[24][streetlevel][23][0]=empty_tile;
		
		//double stairs
		worldgrid[24][streetlevel][24][0]=98;
		worldgrid[24][streetlevel][24][1]=2;
	
	/*
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
	
	
	
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+1][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][1]=2;//first floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)][0]=ramp_tile;//first floor up
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel][house_low_z+((house_high_z-house_low_z)/2)+1][0]=0;//bottom of first floor stairs
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)+2][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)-1][1]=1;//was2;//second floor up rotation
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][0]=ramp2_tile;//second floor up//was plus 1 z
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)-1][streetlevel+1][house_low_z+((house_high_z-house_low_z)/2)+2][1]=3;//was2;//second floor up rotation
	*/
	break;
	}
	
	//roof
	worldgrid[house_low_x+((house_high_x-house_low_x)/2)][streetlevel+3][house_low_z+((house_high_z-house_low_z)/2)][0]=roof_tile2;

	
	/*
	if(allocentric)
	{
		worldgrid[1+house_low_x+(2)*(house_high_x-house_low_x)/4][streetlevel+1][house_high_z-1][0]=timhortonswall_tile;
		worldgrid[house_high_x-2][streetlevel+2][house_high_z-1][0]=atmmachinewall_tile;
	}
	*/
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

	//interior wall
	
	for(int y=streetlevel+1;y<=streetlevel+2;y++){
		/*
		for(int x=20;x<=29;x++){
			worldgrid[x][y][19][0]=wall_tile;
			worldgrid[x][y][19][1]=1;
			worldgrid[x][y][30][0]=wall_tile;
			worldgrid[x][y][30][1]=3;
		}

		for(int z=20;z<=29;z++){
			worldgrid[19][y][z][0]=wall_tile;
			worldgrid[19][y][z][1]=2;
			worldgrid[30][y][z][0]=wall_tile;
			worldgrid[30][y][z][1]=0;
		}
		*/
		//corners
		/*
		worldgrid[20][y][20][0]=wallcorner_tile;
		worldgrid[20][y][20][1]=3;
		worldgrid[20][y][29][0]=wallcorner_tile;
		worldgrid[20][y][29][1]=0;
		worldgrid[29][y][29][0]=wallcorner_tile;
		worldgrid[29][y][29][1]=1;
		worldgrid[29][y][20][0]=wallcorner_tile;
		worldgrid[29][y][20][1]=2;
		*/
		//interior room doors
		worldgrid[house_low_x+4][y][house_low_z+2][0]=interior_door_tile;
		worldgrid[house_low_x+4][y][house_low_z+2][1]=1;
		worldgrid[house_high_x-4][y][house_low_z+2][0]=interior_door_tile;
		worldgrid[house_high_x-4][y][house_low_z+2][1]=1;
		worldgrid[house_low_x+2][y][house_low_z+4][0]=interior_door_tile;
		worldgrid[house_low_x+2][y][house_low_z+4][1]=2;
		worldgrid[house_low_x+2][y][house_high_z-4][0]=interior_door_tile;
		worldgrid[house_low_x+2][y][house_high_z-4][1]=2;
		worldgrid[house_low_x+4][y][house_high_z-2][0]=interior_door_tile;
		worldgrid[house_low_x+4][y][house_high_z-2][1]=3;
		worldgrid[house_high_x-4][y][house_high_z-2][0]=interior_door_tile;
		worldgrid[house_high_x-4][y][house_high_z-2][1]=3;
		worldgrid[house_high_x-2][y][house_high_z-4][0]=interior_door_tile;
		worldgrid[house_high_x-2][y][house_high_z-4][1]=0;
		worldgrid[house_high_x-2][y][house_low_z+4][0]=interior_door_tile;
		worldgrid[house_high_x-2][y][house_low_z+4][1]=0;

		//interior double doors
		worldgrid[house_low_x+7][y][house_low_z+2][0]=double_door_tile_l;
		worldgrid[house_low_x+7][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+8][y][house_low_z+2][0]=double_door_tile_r;
		worldgrid[house_low_x+8][y][house_low_z+2][1]=0;
		worldgrid[house_low_x+2][y][house_low_z+7][0]=double_door_tile_r;
		worldgrid[house_low_x+2][y][house_low_z+7][1]=1;
		worldgrid[house_low_x+2][y][house_low_z+8][0]=double_door_tile_l;
		worldgrid[house_low_x+2][y][house_low_z+8][1]=1;
		worldgrid[house_low_x+7][y][house_high_z-2][0]=double_door_tile_r;
		worldgrid[house_low_x+7][y][house_high_z-2][1]=2;
		worldgrid[house_low_x+8][y][house_high_z-2][0]=double_door_tile_l;
		worldgrid[house_low_x+8][y][house_high_z-2][1]=2;
		worldgrid[house_high_x-2][y][house_low_z+8][0]=double_door_tile_r;
		worldgrid[house_high_x-2][y][house_low_z+8][1]=3;
		worldgrid[house_high_x-2][y][house_low_z+7][0]=double_door_tile_l;
		worldgrid[house_high_x-2][y][house_low_z+7][1]=3;
		//walls
		//1 outside
		worldgrid[18][y][18][0]=wallcorner_tile;
		worldgrid[18][y][18][1]=3;
		worldgrid[19][y][18][0]=wall_tile;
		worldgrid[19][y][18][1]=3;
		worldgrid[20][y][18][0]=inout_wallcorner_tile_l;
		worldgrid[20][y][18][1]=2;
		worldgrid[21][y][18][0]=window_tile;
		worldgrid[21][y][18][1]=3;
		worldgrid[22][y][18][0]=inout_wallcorner_tile_r;
		worldgrid[22][y][18][1]=2;
		worldgrid[23][y][18][0]=inout_wallcorner_tile_l;
		worldgrid[23][y][18][1]=2;
		worldgrid[24][y][18][0]=double_window_tile;
		worldgrid[24][y][18][1]=1;
		worldgrid[26][y][18][0]=inout_wallcorner_tile_r;
		worldgrid[26][y][18][1]=2;
		worldgrid[27][y][18][0]=inout_wallcorner_tile_l;
		worldgrid[27][y][18][1]=2;
		worldgrid[28][y][18][0]=window_tile;
		worldgrid[28][y][18][1]=3;
		worldgrid[29][y][18][0]=inout_wallcorner_tile_r;
		worldgrid[29][y][18][1]=2;
		//1 inside
		worldgrid[18][y][19][0]=wall_tile;
		worldgrid[18][y][19][1]=0;
		worldgrid[19][y][19][0]=block_tile;
		worldgrid[19][y][19][1]=0;
		worldgrid[20][y][19][0]=interior_wallcorner_tile_l;
		worldgrid[20][y][19][1]=0;
		worldgrid[22][y][19][0]=interior_wallcorner_tile_r;
		worldgrid[22][y][19][1]=0;
		worldgrid[23][y][19][0]=interior_wallcorner_tile_l;
		worldgrid[23][y][19][1]=0;
		worldgrid[26][y][19][0]=interior_wallcorner_tile_r;
		worldgrid[26][y][19][1]=0;
		worldgrid[27][y][19][0]=interior_wallcorner_tile_l;
		worldgrid[27][y][19][1]=0;
		worldgrid[29][y][19][0]=interior_wallcorner_tile_r;
		worldgrid[29][y][19][1]=0;
		//2 outside
		worldgrid[18][y][31][0]=wallcorner_tile;
		worldgrid[18][y][31][1]=0;
		worldgrid[18][y][30][0]=wall_tile;
		worldgrid[18][y][30][1]=0;
		worldgrid[18][y][29][0]=inout_wallcorner_tile_l;
		worldgrid[18][y][29][1]=3;
		worldgrid[18][y][28][0]=window_tile;
		worldgrid[18][y][28][1]=0;
		worldgrid[18][y][27][0]=inout_wallcorner_tile_r;
		worldgrid[18][y][27][1]=3;
		worldgrid[18][y][26][0]=inout_wallcorner_tile_l;
		worldgrid[18][y][26][1]=3;
		worldgrid[18][y][25][0]=double_window_tile;
		worldgrid[18][y][25][1]=2;
		worldgrid[18][y][23][0]=inout_wallcorner_tile_r;
		worldgrid[18][y][23][1]=3;
		worldgrid[18][y][22][0]=inout_wallcorner_tile_l;
		worldgrid[18][y][22][1]=3;
		worldgrid[18][y][21][0]=window_tile;
		worldgrid[18][y][21][1]=0;
		worldgrid[18][y][20][0]=inout_wallcorner_tile_r;
		worldgrid[18][y][20][1]=3;
		//2 inside
		worldgrid[19][y][29][0]=interior_wallcorner_tile_l;
		worldgrid[19][y][29][1]=1;
		worldgrid[19][y][27][0]=interior_wallcorner_tile_r;
		worldgrid[19][y][27][1]=1;
		worldgrid[19][y][26][0]=interior_wallcorner_tile_l;
		worldgrid[19][y][26][1]=1;
		worldgrid[19][y][23][0]=interior_wallcorner_tile_r;
		worldgrid[19][y][23][1]=1;
		worldgrid[19][y][22][0]=interior_wallcorner_tile_l;
		worldgrid[19][y][22][1]=1;
		worldgrid[19][y][20][0]=interior_wallcorner_tile_r;
		worldgrid[19][y][20][1]=1;
		
		//3 outside
		worldgrid[18][y][31][0]=wallcorner_tile;
		worldgrid[18][y][31][1]=0;
		worldgrid[19][y][31][0]=wall_tile;
		worldgrid[19][y][31][1]=1;
		worldgrid[20][y][31][0]=inout_wallcorner_tile_r;
		worldgrid[20][y][31][1]=0;
		worldgrid[21][y][31][0]=window_tile;
		worldgrid[21][y][31][1]=1;
		worldgrid[22][y][31][0]=inout_wallcorner_tile_l;
		worldgrid[22][y][31][1]=0;
		worldgrid[23][y][31][0]=inout_wallcorner_tile_r;
		worldgrid[23][y][31][1]=0;
		worldgrid[25][y][31][0]=double_window_tile;
		worldgrid[25][y][31][1]=3;
		worldgrid[26][y][31][0]=inout_wallcorner_tile_l;
		worldgrid[26][y][31][1]=0;
		worldgrid[27][y][31][0]=inout_wallcorner_tile_r;
		worldgrid[27][y][31][1]=0;
		worldgrid[28][y][31][0]=window_tile;
		worldgrid[28][y][31][1]=1;
		worldgrid[29][y][31][0]=inout_wallcorner_tile_l;
		worldgrid[29][y][31][1]=0;
		//3 inside
		worldgrid[18][y][30][0]=wall_tile;
		worldgrid[18][y][30][1]=0;
		worldgrid[19][y][30][0]=block_tile;
		worldgrid[19][y][30][1]=2;
		worldgrid[20][y][30][0]=interior_wallcorner_tile_r;
		worldgrid[20][y][30][1]=2;
		worldgrid[22][y][30][0]=interior_wallcorner_tile_l;
		worldgrid[22][y][30][1]=2;
		worldgrid[23][y][30][0]=interior_wallcorner_tile_r;
		worldgrid[23][y][30][1]=2;
		worldgrid[26][y][30][0]=interior_wallcorner_tile_l;
		worldgrid[26][y][30][1]=2;
		worldgrid[27][y][30][0]=interior_wallcorner_tile_r;
		worldgrid[27][y][30][1]=2;
		worldgrid[29][y][30][0]=interior_wallcorner_tile_l;
		worldgrid[29][y][30][1]=2;
		//4 outside
		worldgrid[31][y][31][0]=wallcorner_tile;
		worldgrid[31][y][31][1]=1;
		worldgrid[31][y][30][0]=wall_tile;
		worldgrid[31][y][30][1]=2;
		worldgrid[31][y][29][0]=inout_wallcorner_tile_r;
		worldgrid[31][y][29][1]=1;
		worldgrid[31][y][28][0]=window_tile;
		worldgrid[31][y][28][1]=2;
		worldgrid[31][y][27][0]=inout_wallcorner_tile_l;
		worldgrid[31][y][27][1]=1;
		worldgrid[31][y][26][0]=inout_wallcorner_tile_r;
		worldgrid[31][y][26][1]=1;
		worldgrid[31][y][24][0]=double_window_tile;
		worldgrid[31][y][24][1]=0;
		worldgrid[31][y][23][0]=inout_wallcorner_tile_l;
		worldgrid[31][y][23][1]=1;
		worldgrid[31][y][22][0]=inout_wallcorner_tile_r;
		worldgrid[31][y][22][1]=1;
		worldgrid[31][y][21][0]=window_tile;
		worldgrid[31][y][21][1]=2;
		worldgrid[31][y][20][0]=inout_wallcorner_tile_l;
		worldgrid[31][y][20][1]=1;
		worldgrid[31][y][18][0]=wallcorner_tile;
		worldgrid[31][y][18][1]=2;
		worldgrid[31][y][19][0]=wall_tile;
		worldgrid[31][y][19][1]=2;
		//4 inside
		worldgrid[30][y][31][0]=wall_tile;
		worldgrid[30][y][31][1]=1;
		worldgrid[30][y][30][0]=block_tile;
		worldgrid[30][y][30][1]=3;
		worldgrid[30][y][29][0]=interior_wallcorner_tile_r;
		worldgrid[30][y][29][1]=3;
		worldgrid[30][y][27][0]=interior_wallcorner_tile_l;
		worldgrid[30][y][27][1]=3;
		worldgrid[30][y][26][0]=interior_wallcorner_tile_r;
		worldgrid[30][y][26][1]=3;
		worldgrid[30][y][23][0]=interior_wallcorner_tile_l;
		worldgrid[30][y][23][1]=3;
		worldgrid[30][y][22][0]=interior_wallcorner_tile_r;
		worldgrid[30][y][22][1]=3;
		worldgrid[30][y][20][0]=interior_wallcorner_tile_l;
		worldgrid[30][y][20][1]=3;
		worldgrid[30][y][18][0]=wall_tile;
		worldgrid[30][y][18][1]=3;
		worldgrid[30][y][19][0]=block_tile;
		worldgrid[30][y][19][1]=1;
	}
	
	//fence
	
	for(int x=3;x<=worldgridsizex-4;x++){
		worldgrid[x][2][2][0]=97;
		worldgrid[x][2][2][1]=1;
		worldgrid[x][2][worldgridsizez-3][0]=97;
		worldgrid[x][2][worldgridsizez-3][1]=3;
	}
	for(int z=3;z<=worldgridsizez-4;z++){
		worldgrid[2][2][z][0]=97;
		worldgrid[2][2][z][1]=2;
		worldgrid[worldgridsizex-3][2][z][0]=97;
		worldgrid[worldgridsizex-3][2][z][1]=0;
	}
	
	if(allocentric){
		//Allocentric part

		//R
		a_win_pos[0]=clue_win_array[7][4];
		a_win_pos[1]=clue_win_array[7][5];
		a_win_pos[2]=clue_win_array[7][6];
		//R

		//F
		b_win_pos[0]=clue_win_array[2][4];
		b_win_pos[1]=clue_win_array[2][5];
		b_win_pos[2]=clue_win_array[2][6];
		//F

		//P
		c_win_pos[0]=clue_win_array[7][1];
		c_win_pos[1]=clue_win_array[7][2];
		c_win_pos[2]=clue_win_array[7][3];
		//P


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


		switch(targetwin+1){
			case 1:
				//climb the stairs
				expectdist = clue_win_array[7][8];                                            
				//for the clue chart resembles letter W
				win_clue=clue_win_array[7][0]+2;
			break;
			case 2:
				//climb the stairs
				expectdist = clue_win_array[2][8];
				//for the clue chart resembles letter F
				win_clue=clue_win_array[2][0]+2;
			break;
			case 3:
				//climb the stairs
				expectdist = clue_win_array[7][7];
				//for the clue chart resembles letter H
				win_clue=clue_win_array[7][0];
			break;
		}	
	}

		//end of Allocentric part
	else{
		//Egocentric part
		//objective windows

		switch(trial){
			case 1:

				//climb the stairs
				//1
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[1][1];
					a_win_pos[1]=clue_win_array[1][2];
					a_win_pos[2]=clue_win_array[1][3];
					win_clue=clue_win_array[1][0];
					expectdist = clue_win_array[1][7];
				}
				else{
					a_win_pos[0]=clue_win_array[1][4];
					a_win_pos[1]=clue_win_array[1][5];
					a_win_pos[2]=clue_win_array[1][6];
					win_clue=clue_win_array[1][0]+2;
					expectdist = clue_win_array[1][8];
				}
				//1

				//to the target window
				//4
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[4][1];
					b_win_pos[1]=clue_win_array[4][2];
					b_win_pos[2]=clue_win_array[4][3];
				}
				else{
					b_win_pos[0]=clue_win_array[4][4];
					b_win_pos[1]=clue_win_array[4][5];
					b_win_pos[2]=clue_win_array[4][6];
				}
				//4

				//3
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[3][1];
					c_win_pos[1]=clue_win_array[3][2];
					c_win_pos[2]=clue_win_array[3][3];
				}
				else{
					c_win_pos[0]=clue_win_array[3][4];
					c_win_pos[1]=clue_win_array[3][5];
					c_win_pos[2]=clue_win_array[3][6];
				}
				//3

			break;
			case 2:
				//climb the stairs
				//2
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[2][1];
					a_win_pos[1]=clue_win_array[2][2];
					a_win_pos[2]=clue_win_array[2][3];
					win_clue=clue_win_array[2][0];
					expectdist = clue_win_array[2][7];
				}
				else{
					a_win_pos[0]=clue_win_array[2][4];
					a_win_pos[1]=clue_win_array[2][5];
					a_win_pos[2]=clue_win_array[2][6];
					win_clue=clue_win_array[2][0]+2;
					expectdist = clue_win_array[2][8];
				}
				//2

				//to the target window
				//7
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[7][1];
					b_win_pos[1]=clue_win_array[7][2];
					b_win_pos[2]=clue_win_array[7][3];
				}
				else{
					b_win_pos[0]=clue_win_array[7][4];
					b_win_pos[1]=clue_win_array[7][5];
					b_win_pos[2]=clue_win_array[7][6];
				}
				//7

				//8
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[8][1];
					c_win_pos[1]=clue_win_array[8][2];
					c_win_pos[2]=clue_win_array[8][3];
				}
				else{
					c_win_pos[0]=clue_win_array[8][4];
					c_win_pos[1]=clue_win_array[8][5];
					c_win_pos[2]=clue_win_array[8][6];
				}
				//8
			break;
			case 3:
				//climb the stairs
				//3
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[3][1];
					a_win_pos[1]=clue_win_array[3][2];
					a_win_pos[2]=clue_win_array[3][3];
					win_clue=clue_win_array[3][0];
					expectdist = clue_win_array[3][7];
				}
				else{
					a_win_pos[0]=clue_win_array[3][4];
					a_win_pos[1]=clue_win_array[3][5];
					a_win_pos[2]=clue_win_array[3][6];
					win_clue=clue_win_array[3][0]+2;
					expectdist = clue_win_array[3][8];
				}
				//3

				//to the target window
				//6
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[6][1];
					b_win_pos[1]=clue_win_array[6][2];
					b_win_pos[2]=clue_win_array[6][3];
				}
				else{
					b_win_pos[0]=clue_win_array[6][4];
					b_win_pos[1]=clue_win_array[6][5];
					b_win_pos[2]=clue_win_array[6][6];
				}
				//6
			
				//5
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[5][1];
					c_win_pos[1]=clue_win_array[5][2];
					c_win_pos[2]=clue_win_array[5][3];
				}
				else{
					c_win_pos[0]=clue_win_array[5][4];
					c_win_pos[1]=clue_win_array[5][5];
					c_win_pos[2]=clue_win_array[5][6];
				}
				//5

			break;
			case 4:
				//climb the stairs
				//4
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[4][1];
					a_win_pos[1]=clue_win_array[4][2];
					a_win_pos[2]=clue_win_array[4][3];
					win_clue=clue_win_array[4][0];
					expectdist = clue_win_array[4][7];
				}
				else{
					a_win_pos[0]=clue_win_array[4][4];
					a_win_pos[1]=clue_win_array[4][5];
					a_win_pos[2]=clue_win_array[4][6];
					win_clue=clue_win_array[4][0]+2;
					expectdist = clue_win_array[4][8];
				}
				//4

				//to the target window
				//3
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[3][1];
					b_win_pos[1]=clue_win_array[3][2];
					b_win_pos[2]=clue_win_array[3][3];
				}
				else{
					b_win_pos[0]=clue_win_array[3][4];
					b_win_pos[1]=clue_win_array[3][5];
					b_win_pos[2]=clue_win_array[3][6];
				}
				//3

				//6
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[6][1];
					c_win_pos[1]=clue_win_array[6][2];
					c_win_pos[2]=clue_win_array[6][3];
				}
				else{
					c_win_pos[0]=clue_win_array[6][4];
					c_win_pos[1]=clue_win_array[6][5];
					c_win_pos[2]=clue_win_array[6][6];
				}
				//6

			break;
			case 5:
				//climb the stairs
				//5
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[5][1];
					a_win_pos[1]=clue_win_array[5][2];
					a_win_pos[2]=clue_win_array[5][3];
					win_clue=clue_win_array[5][0];
					expectdist = clue_win_array[5][7];
				}
				else{
					a_win_pos[0]=clue_win_array[5][4];
					a_win_pos[1]=clue_win_array[5][5];
					a_win_pos[2]=clue_win_array[5][6];
					win_clue=clue_win_array[5][0]+2;
					expectdist = clue_win_array[5][8];
				}
				//5

				//to the target window
				//1
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[1][1];
					b_win_pos[1]=clue_win_array[1][2];
					b_win_pos[2]=clue_win_array[1][3];
				}
				else{
					b_win_pos[0]=clue_win_array[1][4];
					b_win_pos[1]=clue_win_array[1][5];
					b_win_pos[2]=clue_win_array[1][6];
				}
				//1

				//4
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[4][1];
					c_win_pos[1]=clue_win_array[4][2];
					c_win_pos[2]=clue_win_array[4][3];
				}
				else{
					c_win_pos[0]=clue_win_array[4][4];
					c_win_pos[1]=clue_win_array[4][5];
					c_win_pos[2]=clue_win_array[4][6];
				}
				//4

			break;
			case 6:
				//climb the stairs
				//6
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[6][1];
					a_win_pos[1]=clue_win_array[6][2];
					a_win_pos[2]=clue_win_array[6][3];
					win_clue=clue_win_array[6][0];
					expectdist = clue_win_array[6][7];
				}
				else{
					a_win_pos[0]=clue_win_array[6][4];
					a_win_pos[1]=clue_win_array[6][5];
					a_win_pos[2]=clue_win_array[6][6];
					win_clue=clue_win_array[6][0]+2;
					expectdist = clue_win_array[6][8];
				}
				//6

				//to the target window
				//8
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[8][1];
					b_win_pos[1]=clue_win_array[8][2];
					b_win_pos[2]=clue_win_array[8][3];
				}
				else{
					b_win_pos[0]=clue_win_array[8][4];
					b_win_pos[1]=clue_win_array[8][5];
					b_win_pos[2]=clue_win_array[8][6];
				}
				//8

				//2
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[2][1];
					c_win_pos[1]=clue_win_array[2][2];
					c_win_pos[2]=clue_win_array[2][3];
				}
				else{
					c_win_pos[0]=clue_win_array[2][4];
					c_win_pos[1]=clue_win_array[2][5];
					c_win_pos[2]=clue_win_array[2][6];
				}
				//2

			break;
			case 7:
				//climb the stairs
				//7
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[7][1];
					a_win_pos[1]=clue_win_array[7][2];
					a_win_pos[2]=clue_win_array[7][3];
					win_clue=clue_win_array[7][0];
					expectdist = clue_win_array[7][7];
				}
				else{
					a_win_pos[0]=clue_win_array[7][4];
					a_win_pos[1]=clue_win_array[7][5];
					a_win_pos[2]=clue_win_array[7][6];
					win_clue=clue_win_array[7][0]+2;
					expectdist = clue_win_array[7][8];
				}
				//7

				//to the target window
				//5
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[5][1];
					b_win_pos[1]=clue_win_array[5][2];
					b_win_pos[2]=clue_win_array[5][3];
				}
				else{
					b_win_pos[0]=clue_win_array[5][4];
					b_win_pos[1]=clue_win_array[5][5];
					b_win_pos[2]=clue_win_array[5][6];
				}
				//5

				//3
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[3][1];
					c_win_pos[1]=clue_win_array[3][2];
					c_win_pos[2]=clue_win_array[3][3];
				}
				else{
					c_win_pos[0]=clue_win_array[3][4];
					c_win_pos[1]=clue_win_array[3][5];
					c_win_pos[2]=clue_win_array[3][6];
				}
				//3

			break;
			case 8:
				//climb the stairs
				//8
				if((int)rand()%2){
					a_win_pos[0]=clue_win_array[8][1];
					a_win_pos[1]=clue_win_array[8][2];
					a_win_pos[2]=clue_win_array[8][3];
					win_clue=clue_win_array[8][0];
					expectdist = clue_win_array[8][7];
				}
				else{
					a_win_pos[0]=clue_win_array[8][4];
					a_win_pos[1]=clue_win_array[8][5];
					a_win_pos[2]=clue_win_array[8][6];
					win_clue=clue_win_array[8][0]+2;
					expectdist = clue_win_array[8][8];
				}
				//8

				//to the target window
				//2
				if((int)rand()%2){
					b_win_pos[0]=clue_win_array[2][1];
					b_win_pos[1]=clue_win_array[2][2];
					b_win_pos[2]=clue_win_array[2][3];
				}
				else{
					b_win_pos[0]=clue_win_array[2][4];
					b_win_pos[1]=clue_win_array[2][5];
					b_win_pos[2]=clue_win_array[2][6];
				}
				//2

				//6
				if((int)rand()%2){
					c_win_pos[0]=clue_win_array[6][1];
					c_win_pos[1]=clue_win_array[6][2];
					c_win_pos[2]=clue_win_array[6][3];
				}
				else{
					c_win_pos[0]=clue_win_array[6][4];
					c_win_pos[1]=clue_win_array[6][5];
					c_win_pos[2]=clue_win_array[6][6];
				}
				//6

			break;
		}
		//end of Egocentric

		//placing windows
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
}


