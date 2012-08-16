#include "3DMath.h"

//there is a lot of work to be done here...
//it could be a LOT more efficient
//and there is something wrong with the rotation

class collisionmesh{
	public:
		int polygoncount;
		CVector3 *polygonvertex1;
		CVector3 *polygonvertex2;
		CVector3 *polygonvertex3;
		CVector3 *polygonnormal;
		collisionmesh(int vertexcount,float *vertexarray);		
};

collisionmesh::collisionmesh(int vertexcount,float *vertexarray){
	polygoncount=vertexcount/3;
	polygonvertex1=new CVector3[polygoncount];
	polygonvertex2=new CVector3[polygoncount];
	polygonvertex3=new CVector3[polygoncount];
	polygonnormal=new CVector3[polygoncount];
	CVector3 g_vTriangle[3];
	for(int a=0; a<polygoncount; a++){
		polygonvertex1[a].x=vertexarray[a*9+0];
		polygonvertex1[a].y=vertexarray[a*9+1];
		polygonvertex1[a].z=vertexarray[a*9+2];
		polygonvertex2[a].x=vertexarray[a*9+3];
		polygonvertex2[a].y=vertexarray[a*9+4];
		polygonvertex2[a].z=vertexarray[a*9+5];
		polygonvertex3[a].x=vertexarray[a*9+6];
		polygonvertex3[a].y=vertexarray[a*9+7];
		polygonvertex3[a].z=vertexarray[a*9+8];
		g_vTriangle[0]=polygonvertex1[a];
		g_vTriangle[1]=polygonvertex2[a];
		g_vTriangle[2]=polygonvertex3[a];
		polygonnormal[a]=Normal(g_vTriangle);
	}
}

void spherebumpmesh(
	float &sphereposx,float &sphereposy,float &sphereposz,float radius,
	float meshposx,float meshposy,float meshposz,float meshangy,collisionmesh* mesh,
	bool hitifinside,bool hitifonedge){

	sphereposx-=meshposx;
	sphereposy-=meshposy;
	sphereposz-=meshposz;

	float tempsphereposx,tempsphereposy,tempsphereposz;

	if(meshangy!=0){
		tempsphereposx=sphereposx;tempsphereposy=sphereposy;tempsphereposz=sphereposz;
		sphereposx = tempsphereposz*sin(-meshangy)+tempsphereposx*cos(-meshangy);
		sphereposy = tempsphereposy;
		sphereposz = tempsphereposz*cos(-meshangy)-tempsphereposx*sin(-meshangy);
	}

	CVector3 g_vPosition;
	CVector3 g_vTriangle[3];

	g_vPosition = CVector3(sphereposx,sphereposy,sphereposz);
	for(int a=0; a<mesh->polygoncount; a++){
		g_vTriangle[0]=mesh->polygonvertex1[a];
		g_vTriangle[1]=mesh->polygonvertex2[a];
		g_vTriangle[2]=mesh->polygonvertex3[a];
		CVector3 vNormal=mesh->polygonnormal[a];
		float distance = 0.0f;
		int classification = ClassifySphere(g_vPosition,vNormal,g_vTriangle[0],radius,distance);
		if(classification == INTERSECTS) {
			CVector3 vOffset = vNormal * distance;
			CVector3 vPosition = g_vPosition - vOffset;
			if(InsidePolygon(vPosition,g_vTriangle,3)){
				if(hitifinside){
					sphereposx-=vNormal.x*(radius-abs(distance));
					sphereposy-=vNormal.y*(radius-abs(distance));
					sphereposz-=vNormal.z*(radius-abs(distance));
					g_vPosition = CVector3(sphereposx,sphereposy,sphereposz);
				}
			}else{
				CVector3 vPoint;
				for(int i = 0; i < 3; i++){
					vPoint = ClosestPointOnLine(g_vTriangle[i],g_vTriangle[(i+1)%3],g_vPosition);
					distance = Distance(vPoint,g_vPosition);
					if(distance < radius){
						if(hitifonedge){
							float percentx=(g_vPosition.x-vPoint.x)/distance;
							float percenty=(g_vPosition.y-vPoint.y)/distance;
							float percentz=(g_vPosition.z-vPoint.z)/distance;
							sphereposx=vPoint.x+percentx*radius;
							sphereposy=vPoint.y+percenty*radius;
							sphereposz=vPoint.z+percentz*radius;
							g_vPosition = CVector3(sphereposx,sphereposy,sphereposz);
						}
					}
				}
			}
		}
	}

	if(meshangy!=0){
		tempsphereposx=sphereposx;tempsphereposy=sphereposy;tempsphereposz=sphereposz;
		sphereposx = tempsphereposz*sin(meshangy)+tempsphereposx*cos(meshangy);
		sphereposy = tempsphereposy;
		sphereposz = tempsphereposz*cos(meshangy)-tempsphereposx*sin(meshangy);
	}

	sphereposx+=meshposx;
	sphereposy+=meshposy;
	sphereposz+=meshposz;

}
