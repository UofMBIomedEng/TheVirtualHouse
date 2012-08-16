void save(){

	char filename[256];
	sprintf(filename,"%s%s",mediadir,"saves/coresave.dat");

	FILE			*fp = NULL;

	fp = fopen(filename, "wb");

	float saveversion=0.3;
	fwrite(&saveversion,sizeof(float),1,fp);

	fwrite(&usetextures,sizeof(usetextures),1,fp);
	fwrite(&ghostmode,sizeof(ghostmode),1,fp);
	fwrite(&collectablesfound,sizeof(collectablesfound),1,fp);
	fwrite(&playerxpos,sizeof(playerxpos),1,fp);
	fwrite(&playerypos,sizeof(playerypos),1,fp);
	fwrite(&playerzpos,sizeof(playerzpos),1,fp);
	fwrite(&playerxang,sizeof(playerxang),1,fp);
	fwrite(&playeryang,sizeof(playeryang),1,fp);
	fwrite(&playerzang,sizeof(playerzang),1,fp);
	fwrite(&playerxposmov,sizeof(playerxposmov),1,fp);
	fwrite(&playeryposmov,sizeof(playeryposmov),1,fp);
	fwrite(&playerzposmov,sizeof(playerzposmov),1,fp);
	fwrite(&playerxangmov,sizeof(playerxangmov),1,fp);
	fwrite(&playeryangmov,sizeof(playeryangmov),1,fp);
	fwrite(&playerzangmov,sizeof(playerzangmov),1,fp);
	fwrite(&playergrounded,sizeof(playergrounded),1,fp);
	fwrite(&playerjumping,sizeof(playerjumping),1,fp);
	fwrite(&playerxgridpos,sizeof(playerxgridpos),1,fp);
	fwrite(&playerygridpos,sizeof(playerygridpos),1,fp);
	fwrite(&playerzgridpos,sizeof(playerzgridpos),1,fp);
	fwrite(&playerframe,sizeof(playerframe),1,fp);
	fwrite(&lastplayerframe,sizeof(lastplayerframe),1,fp);
	fwrite(&goalplayerframe,sizeof(goalplayerframe),1,fp);

	fwrite(&camxpos,sizeof(camxpos),1,fp);
	fwrite(&camypos,sizeof(camypos),1,fp);
	fwrite(&camzpos,sizeof(camzpos),1,fp);
	fwrite(&camxang,sizeof(camxang),1,fp);
	fwrite(&camyang,sizeof(camyang),1,fp);
	fwrite(&camzang,sizeof(camzang),1,fp);
	fwrite(&camxposmov,sizeof(camxposmov),1,fp);
	fwrite(&camyposmov,sizeof(camyposmov),1,fp);
	fwrite(&camzposmov,sizeof(camzposmov),1,fp);
	fwrite(&camxangmov,sizeof(camxangmov),1,fp);
	fwrite(&camyangmov,sizeof(camyangmov),1,fp);
	fwrite(&camzangmov,sizeof(camzangmov),1,fp);

	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++){
		fwrite(&entitycount[x][y][z],sizeof(char),1,fp);
		for(int a=0; a<entitycount[x][y][z]; a++){
			fwrite(&entitylist[x][y][z][a]->type,sizeof(int),1,fp);
			fwrite(&entitylist[x][y][z][a]->xpos,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->ypos,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->zpos,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->xang,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->yang,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->zang,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->xposmov,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->yposmov,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->zposmov,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->xangmov,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->yangmov,sizeof(float),1,fp);
			fwrite(&entitylist[x][y][z][a]->zangmov,sizeof(float),1,fp);
		}
	}

	fclose(fp);

}

void load(){

	char filename[256];
	sprintf(filename,"%s%s",mediadir,"saves/coresave.dat");
	
	FILE			*fp = NULL;

	fp = fopen(filename, "rb");
	if(fp!=NULL){

		float saveversion=0;
		fread(&saveversion,sizeof(float),1,fp);
		if(saveversion==(float)0.3){

			fread(&usetextures,sizeof(usetextures),1,fp);
			fread(&ghostmode,sizeof(ghostmode),1,fp);
			fread(&collectablesfound,sizeof(collectablesfound),1,fp);
			fread(&playerxpos,sizeof(playerxpos),1,fp);
			fread(&playerypos,sizeof(playerypos),1,fp);
			fread(&playerzpos,sizeof(playerzpos),1,fp);
			fread(&playerxang,sizeof(playerxang),1,fp);
			fread(&playeryang,sizeof(playeryang),1,fp);
			fread(&playerzang,sizeof(playerzang),1,fp);
			fread(&playerxposmov,sizeof(playerxposmov),1,fp);
			fread(&playeryposmov,sizeof(playeryposmov),1,fp);
			fread(&playerzposmov,sizeof(playerzposmov),1,fp);
			fread(&playerxangmov,sizeof(playerxangmov),1,fp);
			fread(&playeryangmov,sizeof(playeryangmov),1,fp);
			fread(&playerzangmov,sizeof(playerzangmov),1,fp);
			fread(&playergrounded,sizeof(playergrounded),1,fp);
			fread(&playerjumping,sizeof(playerjumping),1,fp);
			fread(&playerxgridpos,sizeof(playerxgridpos),1,fp);
			fread(&playerygridpos,sizeof(playerygridpos),1,fp);
			fread(&playerzgridpos,sizeof(playerzgridpos),1,fp);
			fread(&playerframe,sizeof(playerframe),1,fp);
			fread(&lastplayerframe,sizeof(lastplayerframe),1,fp);
			fread(&goalplayerframe,sizeof(goalplayerframe),1,fp);

			fread(&camxpos,sizeof(camxpos),1,fp);
			fread(&camypos,sizeof(camypos),1,fp);
			fread(&camzpos,sizeof(camzpos),1,fp);
			fread(&camxang,sizeof(camxang),1,fp);
			fread(&camyang,sizeof(camyang),1,fp);
			fread(&camzang,sizeof(camzang),1,fp);
			fread(&camxposmov,sizeof(camxposmov),1,fp);
			fread(&camyposmov,sizeof(camyposmov),1,fp);
			fread(&camzposmov,sizeof(camzposmov),1,fp);
			fread(&camxangmov,sizeof(camxangmov),1,fp);
			fread(&camyangmov,sizeof(camyangmov),1,fp);
			fread(&camzangmov,sizeof(camzangmov),1,fp);

			for(int x=0; x<worldgridsizex; x++)
			for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				fread(&entitycount[x][y][z],sizeof(char),1,fp);
				for(int a=0; a<entitycount[x][y][z]; a++){
					entitylist[x][y][z][a]=new entity;
					fread(&entitylist[x][y][z][a]->type,sizeof(int),1,fp);
					fread(&entitylist[x][y][z][a]->xpos,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->ypos,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->zpos,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->xang,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->yang,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->zang,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->xposmov,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->yposmov,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->zposmov,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->xangmov,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->yangmov,sizeof(float),1,fp);
					fread(&entitylist[x][y][z][a]->zangmov,sizeof(float),1,fp);
				}
			}

		}

		fclose(fp);

	}

}

void saveworldgrid(){

	char filename[256];
	sprintf(filename,"%s%s",mediadir,"saves/worldgrid.dat");

	FILE			*fp = NULL;

	fp = fopen(filename, "wb");
	
	float saveversion=0.3;
	fwrite(&saveversion,sizeof(float),1,fp);

	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++)
		fwrite(&worldgrid[x][y][z][0],sizeof(worldgrid[x][y][z][0]),1,fp);

	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++)
		fwrite(&worldgrid[x][y][z][1],sizeof(worldgrid[x][y][z][1]),1,fp);

	fclose(fp);

}

void loadworldgrid(){

	char filename[256];
	sprintf(filename,"%s%s",mediadir,"saves/worldgrid.dat");
	
	FILE			*fp = NULL;

	fp = fopen(filename, "rb");
	if(fp!=NULL){

		float saveversion=0;
		fread(&saveversion,sizeof(float),1,fp);
		if(saveversion==(float)0.3){

			for(int x=0; x<worldgridsizex; x++)
			for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				fread(&worldgrid[x][y][z][0],sizeof(worldgrid[x][y][z][0]),1,fp);
			}

			for(int x=0; x<worldgridsizex; x++)
			for(int y=0; y<worldgridsizey; y++)
			for(int z=0; z<worldgridsizez; z++){
				fread(&worldgrid[x][y][z][1],sizeof(worldgrid[x][y][z][1]),1,fp);
			}

		}

		fclose(fp);

	}

}
