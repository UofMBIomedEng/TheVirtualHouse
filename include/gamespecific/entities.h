const int entitytypecount			= 3;

const int entitytype_disccartridge	= 0;
const int entitytype_elevator		= 1;
const int entitytype_trashcan		= 2;

const bool entitytypesolid[] = {0,1,1,};

class entity{
	public:
		int type;
		float xpos,ypos,zpos;
		float xang,yang,zang;
		float xposmov,yposmov,zposmov;
		float xangmov,yangmov,zangmov;
		entity();
		~entity();
};
entity::entity(){
	type=0;
	xpos=0,ypos=0,zpos=0;
	xang=0,yang=0,zang=0;
	xposmov=0,yposmov=0,zposmov=0;
	xangmov=0,yangmov=0,zangmov=0;
}
entity::~entity(){
}

const int maxentities = 100;
entity *entitylist[worldgridsizex][worldgridsizey][worldgridsizez][maxentities];
char entitycount[worldgridsizex][worldgridsizey][worldgridsizez];

void removeentityfromlist(int x,int y,int z,int a){
	if(a<entitycount[x][y][z]-1)
		for(int b=a;b<entitycount[x][y][z];b++)
			entitylist[x][y][z][b]=entitylist[x][y][z][b+1];
	entitycount[x][y][z]-=1;
}
