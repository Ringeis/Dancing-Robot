#include <windows.h>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include "imageloader.h"
#include "robot.h"
#include "BG.h"

using namespace std;



Part head, neck, torso, lSholder, rSholder, lBisep, rBisep, lThigh, rThigh, lKnee, rKnee, lShin, rShin, lElbow, rElbow;
Part lForarm, rForarm, lWrist, rWrist, rClaw1, rClaw2, lClaw1, lClaw2, lEye, rEye, lSocket, rSocket;
Part mouthInt, mouthGrate, ground, wall1, wall2, wall3, wall4, balloon, balloonString;
Part box, handle, buttons, button_lines, face_plates, speaker_big, speaker_small;

float la4=1.0;
boolean lightsOff = false;
boolean eyeLights = false;
boolean rotateLight = false;
GLfloat light_diffuse[]	=	{1.0, 1.0, 1.0, 1.0};	// white diffuse light
GLfloat light_position[] =	{1.0, 1.0, 1.0, 0.0};	// infinite light position
GLfloat mat_emission[] = {1.0, 1.0, 0.0, 0.0};		// Eye/Mouth light data
GLfloat def_emmision[] = {0.0, 0.0, 0.0, 0.0};		// Default Emmisive light data
GLfloat angle1 = 0.0;
GLfloat angle2 = 0.0;
GLfloat angleH = 0.0;
GLfloat angleLA = 0.0;
GLfloat angleRA = 0.0;
GLfloat angleLH = 0.0;
GLfloat angleRH = 0.0;
GLfloat angleLElbow = 0.0;
GLfloat	angleRElbow = 0.0;
int countH = 180;
int countLA = 360;
int countRA = 360;
int countLH = 180;
int countRH = 180;
int countEL = 360;
int cameraPoint = 0;
int scale = 1;
GLuint texture[1]; 

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 image->width, image->height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image->pixels);
    return textureId;
}

GLuint textureId1;  // Non-Semless Robot Texture
GLuint textureId2;  // Balloon Texture
GLuint textureId3;  // Ground Texture
GLuint textureId4;  // Skybox Texture
GLuint textureId5;  // Eye/Mouth Texture
GLuint textureId6;  // Facial Detail Texture
GLuint textureId7;  // Boombox Texture
GLuint textureId8;  // Boombox Button Texture
GLuint textureId9;  // Boombox Panel Texture
GLuint textureId10; // BoomBox Speaker Texture
GLuint textureId11; // BoomBox Inner Speaker Texture


void loadModel(){
	// Begin loading model values
	head.vertices = Head_vertex;
	head.v_idx = Head_vidx;
	head.normals = Head_normal;
	head.n_idx = Head_nidx;
	head.uvs = Head_uv;
	head.num_faces = (sizeof(Head_vidx)/sizeof(long));

	neck.vertices = Neck_vertex;
	neck.v_idx = Neck_vidx;
	neck.normals = Neck_normal;
	neck.n_idx = Neck_nidx;
	neck.uvs = Neck_uv;
	neck.num_faces = (sizeof(Neck_vidx)/sizeof(long));

	torso.vertices = Torso_vertex;
	torso.v_idx = Torso_vidx;
	torso.normals = Torso_normal;
	torso.n_idx = Torso_nidx;
	torso.uvs = Torso_uv;
	torso.num_faces = (sizeof(Torso_vidx)/sizeof(long));

	lSholder.vertices = leftSholder_vertex;
	lSholder.v_idx = leftSholder_vidx;
	lSholder.normals = leftSholder_normal;
	lSholder.n_idx = leftSholder_nidx;
	lSholder.uvs = leftSholder_uv;
	lSholder.num_faces = (sizeof(leftSholder_vidx)/sizeof(long));

	rSholder.vertices = rightSholder_vertex;
	rSholder.v_idx = rightSholder_vidx;
	rSholder.normals = rightSholder_normal;
	rSholder.n_idx = rightSholder_nidx;
	rSholder.uvs = rightSholder_uv;
	rSholder.num_faces = (sizeof(rightSholder_vidx)/sizeof(long));

	lBisep.vertices = LBisep_vertex;
	lBisep.v_idx = LBisep_vidx;
	lBisep.normals = LBisep_normal;
	lBisep.n_idx = LBisep_nidx;
	lBisep.uvs = LBisep_uv;
	lBisep.num_faces = (sizeof(LBisep_vidx)/sizeof(long));

	rBisep.vertices = RBisep_vertex;
	rBisep.v_idx = RBisep_vidx;
	rBisep.normals = RBisep_normal;
	rBisep.n_idx = RBisep_nidx;
	rBisep.uvs = RBisep_uv;
	rBisep.num_faces = (sizeof(RBisep_vidx)/sizeof(long));

	lThigh.vertices = LThigh_vertex;
	lThigh.v_idx = LThigh_vidx;
	lThigh.normals = LThigh_normal;
	lThigh.n_idx = LThigh_nidx;
	lThigh.uvs = LThigh_uv;
	lThigh.num_faces = (sizeof(LThigh_vidx)/sizeof(long));

	rThigh.vertices = RThigh_vertex;
	rThigh.v_idx = RThigh_vidx;
	rThigh.normals = RThigh_normal;
	rThigh.n_idx = RThigh_nidx;
	rThigh.uvs = RThigh_uv;
	rThigh.num_faces = (sizeof(RThigh_vidx)/sizeof(long));

	lKnee.vertices = Lknee_vertex;
	lKnee.v_idx = Lknee_vidx;
	lKnee.normals = Lknee_normal;
	lKnee.n_idx = Lknee_nidx;
	lKnee.uvs = Lknee_uv;
	lKnee.num_faces = (sizeof(Lknee_vidx)/sizeof(long));

	rKnee.vertices = Rknee_vertex;
	rKnee.v_idx = Rknee_vidx;
	rKnee.normals = Rknee_normal;
	rKnee.n_idx = Rknee_nidx;
	rKnee.uvs = Rknee_uv;
	rKnee.num_faces = (sizeof(Rknee_vidx)/sizeof(long));

	lShin.vertices = Lshin_vertex;
	lShin.v_idx = Lshin_vidx;
	lShin.normals = Lshin_normal;
	lShin.n_idx = Lshin_nidx;
	lShin.uvs = Lshin_uv;
	lShin.num_faces = (sizeof(Lshin_vidx)/sizeof(long));

	rShin.vertices = Rshin_vertex;
	rShin.v_idx = Rshin_vidx;
	rShin.normals = Rshin_normal;
	rShin.n_idx = Rshin_nidx;
	rShin.uvs = Rshin_uv;
	rShin.num_faces = (sizeof(Rshin_vidx)/sizeof(long));

	lElbow.vertices = Lelbow_vertex;
	lElbow.v_idx = Lelbow_vidx;
	lElbow.normals = Lelbow_normal;
	lElbow.n_idx = Lelbow_nidx;
	lElbow.uvs = Lelbow_uv;
	lElbow.num_faces = (sizeof(Lelbow_vidx)/sizeof(long));

	rElbow.vertices = Relbow_vertex;
	rElbow.v_idx = Relbow_vidx;
	rElbow.normals = Relbow_normal;
	rElbow.n_idx = Relbow_nidx;
	rElbow.uvs = Relbow_uv;
	rElbow.num_faces = (sizeof(Relbow_vidx)/sizeof(long));

	lForarm.vertices = Lforarm_vertex;
	lForarm.v_idx = Lforarm_vidx;
	lForarm.normals = Lforarm_normal;
	lForarm.n_idx = Lforarm_nidx;
	lForarm.uvs = Lforarm_uv;
	lForarm.num_faces = (sizeof(Lforarm_vidx)/sizeof(long));

	rForarm.vertices = Rforarm_vertex;
	rForarm.v_idx = Rforarm_vidx;
	rForarm.normals = Rforarm_normal;
	rForarm.n_idx = Rforarm_nidx;
	rForarm.uvs = Rforarm_uv;
	rForarm.num_faces = (sizeof(Rforarm_vidx)/sizeof(long));

	lWrist.vertices = Lwrist_vertex;
	lWrist.v_idx = Lwrist_vidx;
	lWrist.normals = Lwrist_normal;
	lWrist.n_idx = Lwrist_nidx;
	lWrist.uvs = Lwrist_uv;
	lWrist.num_faces = (sizeof(Lwrist_vidx)/sizeof(long));

	rWrist.vertices = Rwrist_vertex;
	rWrist.v_idx = Rwrist_vidx;
	rWrist.normals = Rwrist_normal;
	rWrist.n_idx = Rwrist_nidx;
	rWrist.uvs = Rwrist_uv;
	rWrist.num_faces = (sizeof(Rwrist_vidx)/sizeof(long));

	lClaw1.vertices = Lclaw1_vertex;
	lClaw1.v_idx = Lclaw1_vidx;
	lClaw1.normals = Lclaw1_normal;
	lClaw1.n_idx = Lclaw1_nidx;
	lClaw1.uvs = Lclaw1_uv;
	lClaw1.num_faces = (sizeof(Lclaw1_vidx)/sizeof(long));

	rClaw1.vertices = Rclaw1_vertex;
	rClaw1.v_idx = Rclaw1_vidx;
	rClaw1.normals = Rclaw1_normal;
	rClaw1.n_idx = Rclaw1_nidx;
	rClaw1.uvs = Rclaw1_uv;
	rClaw1.num_faces = (sizeof(Rclaw1_vidx)/sizeof(long));

	lClaw2.vertices = Lclaw2_vertex;
	lClaw2.v_idx = Lclaw2_vidx;
	lClaw2.normals = Lclaw2_normal;
	lClaw2.n_idx = Lclaw2_nidx;
	lClaw2.uvs = Lclaw2_uv;
	lClaw2.num_faces = (sizeof(Lclaw2_vidx)/sizeof(long));

	rClaw2.vertices = Rclaw2_vertex;
	rClaw2.v_idx = Rclaw2_vidx;
	rClaw2.normals = Rclaw2_normal;
	rClaw2.n_idx = Rclaw2_nidx;
	rClaw2.uvs = Rclaw2_uv;
	rClaw2.num_faces = (sizeof(Rclaw2_vidx)/sizeof(long));

	lEye.vertices = Leye_vertex;
	lEye.v_idx = Leye_vidx;
	lEye.normals = Leye_normal;
	lEye.n_idx = Leye_nidx;
	lEye.uvs = Leye_uv;
	lEye.num_faces = (sizeof(Leye_vidx)/sizeof(long));

	rEye.vertices = Reye_vertex;
	rEye.v_idx = Reye_vidx;
	rEye.normals = Reye_normal;
	rEye.n_idx = Reye_nidx;
	rEye.uvs = Reye_uv;
	rEye.num_faces = (sizeof(Reye_vidx)/sizeof(long));

	lSocket.vertices = Lsocket_vertex;
	lSocket.v_idx = Lsocket_vidx;
	lSocket.normals = Lsocket_normal;
	lSocket.n_idx = Lsocket_nidx;
	lSocket.uvs = Lsocket_uv;
	lSocket.num_faces = (sizeof(Lsocket_vidx)/sizeof(long));

	rSocket.vertices = Rsocket_vertex;
	rSocket.v_idx = Rsocket_vidx;
	rSocket.normals = Rsocket_normal;
	rSocket.n_idx = Rsocket_nidx;
	rSocket.uvs = Rsocket_uv;
	rSocket.num_faces = (sizeof(Rsocket_vidx)/sizeof(long));

	mouthInt.vertices = mouth_interior_vertex;
	mouthInt.v_idx = mouth_interior_vidx;
	mouthInt.normals = mouth_interior_normal;
	mouthInt.n_idx = mouth_interior_nidx;
	mouthInt.uvs = mouth_interior_uv;
	mouthInt.num_faces = (sizeof(mouth_interior_vidx)/sizeof(long));

	mouthGrate.vertices = mouth_grate_vertex;
	mouthGrate.v_idx = mouth_grate_vidx;
	mouthGrate.normals = mouth_grate_normal;
	mouthGrate.n_idx = mouth_grate_nidx;
	mouthGrate.uvs = mouth_grate_uv;
	mouthGrate.num_faces = (sizeof(mouth_grate_vidx)/sizeof(long));

	mouthGrate.vertices = mouth_grate_vertex;
	mouthGrate.v_idx = mouth_grate_vidx;
	mouthGrate.normals = mouth_grate_normal;
	mouthGrate.n_idx = mouth_grate_nidx;
	mouthGrate.uvs = mouth_grate_uv;
	mouthGrate.num_faces = (sizeof(mouth_grate_vidx)/sizeof(long));
// Background Objects
	ground.vertices = ground_vertex;
	ground.v_idx = ground_vidx;
	ground.normals = ground_normal;
	ground.n_idx = ground_nidx;
	ground.uvs = ground_uv;
	ground.num_faces = (sizeof(ground_vidx)/sizeof(long));

	wall1.vertices = wall1_vertex;
	wall1.v_idx = wall1_vidx;
	wall1.normals = wall1_normal;
	wall1.n_idx = wall1_nidx;
	wall1.uvs = wall1_uv;
	wall1.num_faces = (sizeof(wall1_vidx)/sizeof(long));

	wall2.vertices = wall2_vertex;
	wall2.v_idx = wall2_vidx;
	wall2.normals = wall2_normal;
	wall2.n_idx = wall2_nidx;
	wall2.uvs = wall2_uv;
	wall2.num_faces = (sizeof(wall2_vidx)/sizeof(long));

	wall3.vertices = wall3_vertex;
	wall3.v_idx = wall3_vidx;
	wall3.normals = wall3_normal;
	wall3.n_idx = wall3_nidx;
	wall3.uvs = wall3_uv;
	wall3.num_faces = (sizeof(wall3_vidx)/sizeof(long));

	wall4.vertices = wall4_vertex;
	wall4.v_idx = wall4_vidx;
	wall4.normals = wall4_normal;
	wall4.n_idx = wall4_nidx;
	wall4.uvs = wall4_uv;
	wall4.num_faces = (sizeof(wall4_vidx)/sizeof(long));

	balloon.vertices = balloon_vertex;
	balloon.v_idx = balloon_vidx;
	balloon.normals = balloon_normal;
	balloon.n_idx = balloon_nidx;
	balloon.uvs = balloon_uv;
	balloon.num_faces = (sizeof(balloon_vidx)/sizeof(long));

	balloonString.vertices = bString_vertex;
	balloonString.v_idx = bString_vidx;
	balloonString.normals = bString_normal;
	balloonString.n_idx = bString_nidx;
	balloonString.uvs = bString_uv;
	balloonString.num_faces = (sizeof(bString_vidx)/sizeof(long));

	box.vertices = box_vertex;
	box.v_idx = box_vidx;
	box.normals = box_normal;
	box.n_idx = box_nidx;
	box.uvs = box_uv;
	box.num_faces = (sizeof(box_vidx)/sizeof(long));

	buttons.vertices = buttons_vertex;
	buttons.v_idx = buttons_vidx;
	buttons.normals = buttons_normal;
	buttons.n_idx = buttons_nidx;
	buttons.uvs = buttons_uv;
	buttons.num_faces = (sizeof(buttons_vidx)/sizeof(long));

	button_lines.vertices = button_lines_vertex;
	button_lines.v_idx = button_lines_vidx;
	button_lines.normals = button_lines_normal;
	button_lines.n_idx = button_lines_nidx;
	button_lines.uvs = button_lines_uv;
	button_lines.num_faces = (sizeof(button_lines_vidx)/sizeof(long));

	face_plates.vertices = face_plates_vertex;
	face_plates.v_idx = face_plates_vidx;
	face_plates.normals = face_plates_normal;
	face_plates.n_idx = face_plates_nidx;
	face_plates.uvs = face_plates_uv;
	face_plates.num_faces = (sizeof(face_plates_vidx)/sizeof(long));

	handle.vertices = handle_vertex;
	handle.v_idx = handle_vidx;
	handle.normals = handle_normal;
	handle.n_idx = handle_nidx;
	handle.uvs = handle_uv;
	handle.num_faces = (sizeof(handle_vidx)/sizeof(long));

	speaker_big.vertices = speaker_big_vertex;
	speaker_big.v_idx = speaker_big_vidx;
	speaker_big.normals = speaker_big_normal;
	speaker_big.n_idx = speaker_big_nidx;
	speaker_big.uvs = speaker_big_uv;
	speaker_big.num_faces = (sizeof(speaker_big_vidx)/sizeof(long));

	speaker_small.vertices = speaker_small_vertex;
	speaker_small.v_idx = speaker_small_vidx;
	speaker_small.normals = speaker_small_normal;
	speaker_small.n_idx = speaker_small_nidx;
	speaker_small.uvs = speaker_small_uv;
	speaker_small.num_faces = (sizeof(speaker_small_vidx)/sizeof(long));
// End loading model values
}

void reshapeFunc(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(h<1) h=1;
	gluPerspective(40.0, (double)w/(double)h, 1.0, 8000.0);
	glMatrixMode(GL_MODELVIEW);
}

void moveLight(){
	if(cameraPoint == 0 && rotateLight){
		light_position[2] -= 0.01;
		if(light_position[2] <= 0.0){
			rotateLight = false;
			cameraPoint = 1;
		}
	}else if(cameraPoint == 1 && rotateLight){
		light_position[2] -= 0.01;
		if(light_position[2] <= -1.0){
			cameraPoint = 2;
			rotateLight = false;
		}
	}else if(cameraPoint == 2 && rotateLight){
		light_position[0] -= 0.01;
		if(light_position[0] <= 0.0){
			cameraPoint = 3;
			rotateLight = false;
		}
	}else if(cameraPoint == 3 && rotateLight){
		light_position[0] -= 0.01;
		if(light_position[0] <= -1.0){
			cameraPoint = 4;
			rotateLight = false;
		}
	}else if(cameraPoint == 4 && rotateLight){
		light_position[2] += 0.01;
		if(light_position[2] >= 0.0){
			cameraPoint = 5;
			rotateLight = false;
		}
	}else if(cameraPoint == 5 && rotateLight){
		light_position[2] += 0.01;
		if(light_position[2] >= 1.0){
			cameraPoint = 6;
			rotateLight = false;
		}
	}else if(cameraPoint == 6 && rotateLight){
		light_position[0] += 0.01;
		if(light_position[0] >= 0.0){
			cameraPoint = 7;
			rotateLight = false;
		}
	}else{
		light_position[0] += 0.01;
		if(light_position[0] >= 1.0){
			cameraPoint = 0;
			rotateLight = false;
		}
	}
}

void display() {
	if(rotateLight)
		moveLight();
	glDisable   (GL_LIGHT0);
	glLightfv	(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv	(GL_LIGHT0, GL_POSITION, light_position);
	glEnable	(GL_LIGHT0);
	if(lightsOff){
		glDisable   (GL_LIGHT0);
	}

/*
	Piece Indicies
	Head 0-6
	Torso 7-10
	Left Arm 11-14
	Left Hand 15-16
	Right Arm 17-20
	Right Hand 21-22
	Left leg 23-25
	Right leg 26-28
	Balloon 29-30
	Boombox 31-37
*/
	Part pieces[] = {head, lEye, rEye, lSocket, rSocket, mouthInt, mouthGrate, torso, neck, lSholder, rSholder, lBisep, lElbow, lForarm, lWrist, 
					lClaw1, lClaw2, rBisep, rElbow, rForarm,  rWrist, rClaw1, rClaw2, lThigh, lKnee, lShin, rThigh, rKnee, rShin, balloon, balloonString, 
					box, handle, buttons, button_lines, face_plates, speaker_big, speaker_small};
	Part bg[] = {ground, wall1, wall2, wall3, wall4, };

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if(countH < 180){
		countH++;
		angleH += 2.0*scale;
	}
	if(countLA < 360){
		countLA++;
		angleLA -= scale;
	}
	if(countRA < 360){
		countRA++;
		angleRA -= scale;
	}
	if(countLH < 180){
		countLH++;
		angleLH -= 4.0*scale;
	}
	if(countRH < 180){
		countRH++;
		angleRH -= 4.0*scale;
	}
	if(countEL < 360){
		countEL++;
		if(eyeLights && countEL%13==0)
			eyeLights = false;
		else if(countEL%13==0)
			eyeLights = true;
	}
	glLoadIdentity();
	glTranslatef( 0.0, -75.0+angle2, -300.0 - angle2);

	glRotatef( angle2,       1.0, 0.0, 0.0 );
	glRotatef( angle1,       0.0, 1.0, 0.0 );

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId1);
    
    //Use blurry texture mapping (replace GL_LINEAR with GL_NEAREST for blocky)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
//Draw Head
	for(int j=0; j<7; j++){
		glPushMatrix();
			if(j==1 || j==2 || j==5){
				glDisable(GL_TEXTURE_2D);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureId5);
				if(eyeLights)
					glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}else if(j==3 || j==4 || j==6){
				glDisable(GL_TEXTURE_2D);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureId6);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			glRotatef(angleH, 0, 1.0, 0);
			glBegin( GL_TRIANGLES );
			for(int i=0; i<pieces[j].num_faces; i++){
				glNormal3f( pieces[j].normals[pieces[j].n_idx[i]].x,
							pieces[j].normals[pieces[j].n_idx[i]].y,
							pieces[j].normals[pieces[j].n_idx[i]].z );
				glTexCoord2f( pieces[j].uvs[pieces[j].v_idx[i]].x, pieces[j].uvs[pieces[j].v_idx[i]].y );
				glVertex3f(	pieces[j].vertices[pieces[j].v_idx[i]].x,
							pieces[j].vertices[pieces[j].v_idx[i]].y,
							pieces[j].vertices[pieces[j].v_idx[i]].z );					
			}
			glMaterialfv(GL_FRONT, GL_EMISSION, def_emmision);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId1);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPopMatrix();			
	}
   // glDisable(GL_TEXTURE_2D);

//Draw Torso
	for(int j=7; j<11; j++){
		int count = 0;
		glBegin( GL_TRIANGLES );
		for(int i=0; i<pieces[j].num_faces; i++){
			glNormal3f( pieces[j].normals[pieces[j].n_idx[i]].x,
						pieces[j].normals[pieces[j].n_idx[i]].y,
						pieces[j].normals[pieces[j].n_idx[i]].z );
			glTexCoord2f( pieces[j].uvs[pieces[j].v_idx[i]].x, pieces[j].uvs[pieces[j].v_idx[i]].y );
			glVertex3f(	pieces[j].vertices[pieces[j].v_idx[i]].x,
						pieces[j].vertices[pieces[j].v_idx[i]].y,
						pieces[j].vertices[pieces[j].v_idx[i]].z );					
		}
		glEnd();
		
	}

//Draw Left Arm 
	for(int j=11; j<17; j++){
		glPushMatrix();
			glTranslatef(0.0, 110.0, 0.0);
			glRotatef(angleLA, 1.0, 0, 0);
			glTranslatef(0.0 ,-110.0, 0.0);
//Transform Forarm
			if(j>12){
				glTranslatef(0.0, 87.0, 0.0);
				glRotatef(angleLElbow, -1.0, 0, 0.0);
				glTranslatef(0.0 ,-87.0, 0.0);
//Transform Hand
				if(j>14){
					glTranslatef(32.0, 0.0, 0.0);
					glRotatef(angleLH, 0.0, 1.0, 0.0);
					glTranslatef(-32.0, 0.0, 0.0);
				}
			}
			glBegin( GL_TRIANGLES );
			for(int i=0; i<pieces[j].num_faces; i++){
				glNormal3f( pieces[j].normals[pieces[j].n_idx[i]].x,
							pieces[j].normals[pieces[j].n_idx[i]].y,
							pieces[j].normals[pieces[j].n_idx[i]].z );
				glTexCoord2f( pieces[j].uvs[pieces[j].v_idx[i]].x, pieces[j].uvs[pieces[j].v_idx[i]].y );
				glVertex3f(	pieces[j].vertices[pieces[j].v_idx[i]].x,
							pieces[j].vertices[pieces[j].v_idx[i]].y,
							pieces[j].vertices[pieces[j].v_idx[i]].z );					
			}
			glEnd();
		glPopMatrix();			
	}
//Draw Right Arm 
	for(int j=17; j<23; j++){
		int count = 0;
		glPushMatrix();
			glTranslatef(0.0, 110.0, 0.0);
			glRotatef(angleRA, 1.0, 0, 0);
			glTranslatef(0.0 ,-110.0, 0.0);
//Transform Forarm
			if(j>18){
				glTranslatef(0.0, 88.0, 0.0);
				glRotatef(-angleRElbow, 1.0, 0.0, 0.0);
				glTranslatef(0.0, -88.0, 0.0);
//Transform Hand
				if(j>20){
					glTranslatef(-32.0, 0.0, 0.0);
					glRotatef(angleRH, 0.0, 1.0, 0.0);
					glTranslatef(32.0, 0.0, 0.0);
				}
			}
			glBegin( GL_TRIANGLES );
			for(int i=0; i<pieces[j].num_faces; i++){
				glNormal3f( pieces[j].normals[pieces[j].n_idx[i]].x,
							pieces[j].normals[pieces[j].n_idx[i]].y,
							pieces[j].normals[pieces[j].n_idx[i]].z );
				glTexCoord2f( pieces[j].uvs[pieces[j].v_idx[i]].x, pieces[j].uvs[pieces[j].v_idx[i]].y );
				glVertex3f(	pieces[j].vertices[pieces[j].v_idx[i]].x,
							pieces[j].vertices[pieces[j].v_idx[i]].y,
							pieces[j].vertices[pieces[j].v_idx[i]].z );					
			}
			glEnd();
		glPopMatrix();			
	}
//Draw Remainder
	for(int j=23; j<38; j++){
		glPushMatrix();
		if(j==29){ // Balloon
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId2);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else if(j==30){ // Balloon String
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId5);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else if(j==31 || j==32 || j==37){ //Boombox body and handle
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId7);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}else if(j==33){ // buttons
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId8);
			if(eyeLights)
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}else if(j==34){ // button lines
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId9);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}else if(j==35){ // face_plates
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId9);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}else if(j==36){ // Big Speaker
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId10);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}else if(j==36){ // Small Speaker
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId11);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		glBegin( GL_TRIANGLES );
		for(int i=0; i<pieces[j].num_faces; i++){
			glNormal3f( pieces[j].normals[pieces[j].n_idx[i]].x,
						pieces[j].normals[pieces[j].n_idx[i]].y,
						pieces[j].normals[pieces[j].n_idx[i]].z );
			glTexCoord2f( pieces[j].uvs[pieces[j].v_idx[i]].x, pieces[j].uvs[pieces[j].v_idx[i]].y );
			glVertex3f(	pieces[j].vertices[pieces[j].v_idx[i]].x,
						pieces[j].vertices[pieces[j].v_idx[i]].y,
						pieces[j].vertices[pieces[j].v_idx[i]].z );

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId1);
		glMaterialfv(GL_FRONT, GL_EMISSION, def_emmision);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnd();
		glPopMatrix();
	}

//Draw Setting
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glMaterialfv(GL_FRONT, GL_EMISSION, light_diffuse);
	for(int j=0; j<5; j++){
		int count = 0;
		if(j==1){
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureId4);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		glBegin( GL_QUADS );
		for(int i=0; i<bg[j].num_faces; i++){
			glNormal3f( bg[j].normals[bg[j].n_idx[i]].x,
						bg[j].normals[bg[j].n_idx[i]].y,
						bg[j].normals[bg[j].n_idx[i]].z );

			if(count == 0){
				glTexCoord2f(0.0f, 0.0f);
				count++;
			}else if(count == 1){
				glTexCoord2f(0.0f, 1.0f);
				count++;
			}else if(count == 2){
				glTexCoord2f(1.0f, 1.0f);
				count++;
			}else{
				glTexCoord2f(1.0f, 0.0f);
				count=0;
			}
			glVertex3f(	bg[j].vertices[bg[j].v_idx[i]].x*20,
						bg[j].vertices[bg[j].v_idx[i]].y*10,
						bg[j].vertices[bg[j].v_idx[i]].z*20 );					
		}
		glEnd();
	}
	glMaterialfv(GL_FRONT, GL_EMISSION, def_emmision);
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
// Exit Program
	if (key=='Q' || key=='q' ) { 
		exit(0);
	}

//Toggle Red light Aspect
	if (key=='1' ) { 
		if(light_diffuse[0] == 1.0){
			light_diffuse[0] = 0.5;
		}else if(light_diffuse[0] == 0.5){
			light_diffuse[0] = 0.25;
		}else if(light_diffuse[0] == .25){
			light_diffuse[0] = 0.0;
		}else{
			light_diffuse[0] = 1.0;
		}
	}

//Toggle Green light Aspect
	if (key=='2' ) { 
		if(light_diffuse[1] == 1.0){
			light_diffuse[1] = 0.5;
		}else if(light_diffuse[1] == 0.5){
			light_diffuse[1] = 0.25;
		}else if(light_diffuse[1] == .25){
			light_diffuse[1] = 0.0;
		}else{
			light_diffuse[1] = 1.0;
		}
	}
//Toggle Blue light Aspect
	if (key=='3' ) { 
		if(light_diffuse[2] == 1.0){
			light_diffuse[2] = 0.5;
		}else if(light_diffuse[2] == 0.5){
			light_diffuse[2] = 0.25;
		}else if(light_diffuse[2] == .25){
			light_diffuse[2] = 0.0;
		}else{
			light_diffuse[2] = 1.0;
		}
	}

// Toggle Intensity light Aspect
	if (key=='4' ) { 
		if(lightsOff)
			lightsOff = false;
		if(la4 == 1.0){
			light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 0.5;
			la4 = 0.5;
		}else if(la4 == 0.5){
			light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 0.25;
			la4 = 0.25;
		}else if(la4 == .25){
			light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 0.0;
			la4 = 0.0;
		}else{
			light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 1.0;
			la4 = 1.0;
		}
	}

// Toggle Eye/Boombox Lights
	if (key=='5' )
		if(eyeLights)
			eyeLights = false;
		else
			eyeLights = true;

//Rotate Global light location
	if (key=='6' ) { 
		rotateLight = true;
	}

// Toggle Lights Off Mode
	if(key=='L' || key=='l'){
		if(lightsOff){
			lightsOff = false;
			eyeLights = false;
			light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 1.0;
			la4 = 1.0;
		}else{
			lightsOff = true;
			eyeLights = true;
			light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 0.0;
			la4 = 0.0;
		}
	}

// Crazy Robot Mode
	if (key=='P' || key=='p' ) { 
		countH = countLA = countRA = countLH = countRH = countEL = -5760;
		scale = 4;
	}

// Reset to default review
	if(key=='R' || key == 'r'){
		scale = 1;
		angle1=0;
		angle2=0;
		angleH=0;
		countH = 180;
		angleLA = 0;
		countLA = 360;
		angleRA = 0;
		countRA = 360;
		angleLH = 0;
		countLH = 180;
		angleRH = 0;
		countRH = 180;
		countEL = 360;
		angleLElbow = angleRElbow = 0.0;
		cameraPoint = 0;
		light_diffuse[0] = light_diffuse[1] = light_diffuse[2] = 1.0;
		light_position[0] = light_position[2] = 1.0;
		la4 = 1.0;
		lightsOff = eyeLights = rotateLight = false;
		countH = 180;
	}

// Rotate head 360 degrees
	if (key == 'w' || key == 'W') {
		if(countH == 180){
			countH = 0;
		}
	}
// Rotate left arm 360 degrees
	if (key == 's' || key == 'S') {
		if(countLA == 360){
			countLA = 0;
		}
	}
// Rotate right arm 360 degrees
	if (key == 'a' || key == 'A') {
		if(countRA == 360){
			countRA = 0;
		}
	}
// Rotate left forarm forward up to 90 degrees
	if (key == 'g' || key == 'G') {
		if(angleLElbow < 90.0){
			angleLElbow += 2.0;
		}
	}
// Rotate right forarm forward up to 90 degrees
	if (key == 'f' || key == 'F') {
		if(angleRElbow < 90.0){
			angleRElbow += 2.0;
		}
	}
// Rotate left forarm back down to 0 degrees
	if (key == 'b' || key == 'B') {
		if(angleLElbow > 0.0){
			angleLElbow -= 2.0;
		}
	}
// Rotate right forarm back down to 0 degrees
	if (key == 'v' || key == 'V') {
		if(angleRElbow > 0.0){
			angleRElbow -= 2.0;
		}
	}
// Rotate left hand 720 degrees
	if (key == 'x' || key == 'X') {
		if(countLH == 180){
			countLH = 0;
		}
	}
// Rotate right hand 720 degrees
	if (key == 'z' || key == 'Z') {
		if(countRH == 180){
			countRH = 0;
		}
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_LEFT : angle1-=3; break;
		case GLUT_KEY_RIGHT : angle1+=3; break;
		case GLUT_KEY_UP : if(angle2<90) angle2+=3; break;
		case GLUT_KEY_DOWN : if(angle2>0) angle2-=3; break;
	}
}

int main(int argc, char** argv){
	int width = 1024;
	int height = 720;
	loadModel();
	glutInit(&argc, argv);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Dancing Robot");
	glutReshapeFunc(reshapeFunc);
	glutDisplayFunc(display);
	glClearColor(0.2,0.5,0.5,0.0);
	glEnable(GL_DEPTH_TEST);
	glLightfv	(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv	(GL_LIGHT0, GL_POSITION, light_position);
	glEnable	(GL_LIGHT0);
	glEnable	(GL_LIGHTING);

	Image *image1 = loadBMP("metal.bmp");
	Image *image2 = loadBMP("red.bmp");
	Image *image3 = loadBMP("grassTexture.bmp");
	Image *image4 = loadBMP("skybox.bmp");
	Image *image5 = loadBMP("yellow.bmp");
	Image *image6 = loadBMP("black.bmp");
	Image *image7 = loadBMP("boombox.bmp");
	Image *image8 = loadBMP("buttons.bmp");
	Image *image9 = loadBMP("panel.bmp");
	Image *image10 = loadBMP("speaker.bmp");
	Image *image11 = loadBMP("speakerInner.bmp");
    textureId1 = loadTexture(image1);
	textureId2 = loadTexture(image2);
	textureId3 = loadTexture(image3);
	textureId4 = loadTexture(image4);
	textureId5 = loadTexture(image5);
	textureId6 = loadTexture(image6);
	textureId7 = loadTexture(image7);
	textureId8 = loadTexture(image8);
	textureId9 = loadTexture(image9);
	textureId10 = loadTexture(image10);
	textureId11 = loadTexture(image11);
    delete image1;
    delete image2;
    delete image3;
	delete image4;
	delete image5;
	delete image6;
	delete image7;
	delete image8;
	delete image9;
	delete image10;
	delete image11;
	
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	cout << "R -> Reset Model" << endl;
	cout << "W -> Head Spin" << endl;
	cout << "A -> Right Arm Spin" << endl;
	cout << "S -> Left Arm Spin" << endl;
	cout << "Z -> Right Claw Spin" << endl;
	cout << "X -> Left Claw Spin" << endl;
	cout << "F -> Rotate Right Forearm Forward" << endl;
	cout << "G -> Rotate Left Forearm Forward" << endl;
	cout << "V -> Rotate Right Forearm Backward" << endl;
	cout << "B -> Rotate Left Forearm Backward" << endl;
	cout << "L -> Toggle LightsOff Mode" << endl;
	cout << "P -> Crazy Bot Mode" << endl;
	cout << "1 -> Toggle Red Intensity" << endl;
	cout << "2 -> Toggle Green Intensity" << endl;
	cout << "3 -> Toggle Blue Intensity" << endl;
	cout << "4 -> Toggle Total Light Intensity" << endl;
	cout << "5 -> Toggle Eye Light and Boombox lights On and Off" << endl;
	cout << "6 -> Rotate light source 45 degrees counterclockwise around the robot" << endl;
	cout << "Right & Left Arrows -> Rotate Horizonally Around Model" << endl;
	cout << "Up & Down Arrows -> Rotate Vertically Around Model" << endl;
	
	glutMainLoop();

}