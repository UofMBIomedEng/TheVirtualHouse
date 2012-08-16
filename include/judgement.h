int TestApp::zone(float px, float py, float pz){
	if((py>22.f)&&(py<28.f)){			//second floor
		if((px>175.f)&&(px<195.f)){			//side facing
			if((pz>267)&&(pz<293))			//left
																//00000001
				return 0x01;
			else if((pz>197)&&(pz<223))		//right
																//00000000
				return 0x00;
		}
		else if((pz>295.f)&&(pz<314.f)){	//side right
			if((px>267)&&(px<293))			//left
																//00000011
				return 0x03;
			else if((px>197)&&(px<223))		//right
																//00000010
				return 0x02;
		}
		else if((pz>175.f)&&(pz<195.f)){	//side left
			if((px>197)&&(px<223))			//left
																//00000101
				return 0x05;
			else if((px>267)&&(px<293))		//right
																//00000100
				return 0x04;
		}
		else if((px>295.f)&&(px<314.f)){	//side back
			if((pz>197)&&(pz<223))			//left
																//00000111
				return 0x07;
			else if((pz>267)&&(pz<293))		//right
																//00000110
				return 0x06;
		}
	}
	else if((py>32.f)&&(py<38.f)){      //third floor
			if((px>175.f)&&(px<195.f)){			//side facing
			if((pz>267)&&(pz<293))			//left
																//00001001
				return 0x09;
			else if((pz>197)&&(pz<223))		//right
																//00001000
				return 0x08;
		}
		else if((pz>295.f)&&(pz<314.f)){	//side right
			if((px>267)&&(px<293))			//left
																//00001011
				return 0x0B;
			else if((px>197)&&(px<223))		//right
																//00001010
				return 0x0A;
		}
		else if((pz>175.f)&&(pz<195.f)){	//side left
			if((px>197)&&(px<223))			//left
																//00001101
				return 0x0D;
			else if((px>267)&&(px<293))		//right
																//00001100
				return 0x0C;
		}
		else if((px>295.f)&&(px<314.f)){	//side back
			if((pz>197)&&(pz<223))			//left
																//00001111
				return 0x0F;
			else if((pz>267)&&(pz<293))		//right
																//00001110
				return 0x0E;
		}

	}
	return 0x10;			//this means that the the player is not in any room 
}
void TestApp::judgment(){
	
	int room_judge=0,player_judge=0;
	player_judge=zone(playerxpos,playerypos,playerzpos);
	room_judge=zone(target_x,target_y,target_z);
	if(player_judge&0x10)
		judge_res=0x08;				//player is not in any room 
	else{
		judge_res=!((player_judge&0x01)^(room_judge&0x01));
		judge_res|=((!((player_judge&0x02)^(room_judge&0x02)))&&(!((player_judge&0x04)^(room_judge&0x04))))<<1;
		judge_res|=(!((player_judge&0x08)^(room_judge&0x08)))<<2;
	}

}