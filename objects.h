void drawFace(float sizeX, float sizeY)
{
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, 0.0); glTexCoord2f (1, 0);//bottom left
	glVertex3f(sizeX, 0.0, 0.0); glTexCoord2f (1, 1);//bottom right
	glVertex3f(sizeX, sizeY, 0.0); glTexCoord2f (0, 1);//top right
	glVertex3f(0.0, sizeY, 0.0); glTexCoord2f (0, 0);//top left
	glEnd();
}

void drawBox( float sizeX, float sizeY, float sizeZ)
{
	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	drawFace(sizeX, sizeY);//back
	glTranslatef(0.0, sizeY, 0.0);
	glRotatef (90, 1, 0, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	drawFace(sizeX, sizeZ);//top
	glTranslatef(0.0, sizeZ, 0.0);
	glRotatef (90, 1, 0, 0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	drawFace(sizeX, sizeY);//front
	glTranslatef(0.0, sizeY, 0.0);
	glRotatef (90, 1, 0, 0);
	glNormal3f(0.0f, -1.0f, 0.0f);
	drawFace(sizeX, sizeZ);//bottom
	glTranslatef(sizeX, 0.0, 0.0);
	glRotatef (90, 0, 1, 0);
	glRotatef (90, 0, 0, 1);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	drawFace(sizeZ, sizeY);//left
	glTranslatef(sizeZ, 0.0, -sizeX);
	glRotatef (180, 0, 1, 0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	drawFace(sizeZ, sizeY);//right
	glPopMatrix();
}

void createTriangle(float length2, float height2, float width2)
{
	//creates triangles with square base
	glBegin(GL_POLYGON);
	//bottom
	glVertex3f(width2, 0.0, length2);
	glVertex3f(0.0, 0.0, length2);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(width2, 0.0, 0.0);
	//front
	glVertex3f(width2/2, height2, 0.5);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(width2, 0.0, 0.0);
	//back
	glVertex3f(width2/2, height2, length2-0.5);
	glVertex3f(width2, 0.0, length2);
	glVertex3f(0.0, 0.0, length2);
	//left
	glVertex3f(width2/2, height2, 0.5);
	glVertex3f(width2/2, height2, length2-0.5);
	glVertex3f(0.0, 0.0, length2);
	glVertex3f(0.0, 0.0, 0.0);
	//right
	glVertex3f(width2/2, height2, length2-0.5);
	glVertex3f(width2/2, height2, 0.5);
	glVertex3f(width2, 0.0, 0.0);
	glVertex3f(width2, 0.0, length2-0.5);
	glEnd();
}

void building1()
{
		//tower with triangle roof

	glPushMatrix();
	glTranslatef(-0.2f, 0, -0.2f);
	glBindTexture(GL_TEXTURE_2D, 8);//texture1
	drawBox(2.4, 0.5, 3.4);//base
	glPopMatrix();

		glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(2.0f, 7.0f, 3.0f);//top right (top)
    glVertex3f(0.0f, 7.0f, 3.0f);//top left (top)
    glVertex3f(0.0f, 7.0f, 0.0f);//bottom left (top
    glVertex3f(2.0f, 7.0f, 0.0f);//bottom right (top)

    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);//top right (bottom)
    glVertex3f(0.0f, 0.0f, 0.0f);//top left (bottom)
    glVertex3f(0.0f, 0.0f, 3.0f);//bottom left (bottom
    glVertex3f(2.0f, 0.0f, 3.0f);//bottom right (bottom)

    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(2.0f, 7.0f, -0.0f);//top right (front)
    glVertex3f(1.0f, 9.0f, 1.5f);//triangle (top)
    glVertex3f(0.0f, 7.0f, -0.0f);//top left (front)
    glVertex3f(0.0f, 0.0f, -0.0f);//bottom left (front)
    glVertex3f(2.0f, 0.0f, -0.0f);//bottom right (front)

    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(2.0f, 0.0f, 3.0f);//bottom left (back)
    glVertex3f(1.0f, 8.0f, 1.5f);//triangle (top)
    glVertex3f(0.0f, 0.0f, 3.0f);//bottom right (back)
    glVertex3f(0.0f, 7.0f, 3.0f);//top right (back)
    glVertex3f(2.0f, 7.0f, 3.0f);//top left (back)

    glNormal3f(-1.0f, 0.0f, 0.0f);    
    glVertex3f(-0.0f, 7.0f, 3.0f);//top right (left)
    glVertex3f(1.0f, 9.0f, 1.5f);//triangle (top)
    glVertex3f(-0.0f, 7.0f, 0.0f);//top left (left)
    glVertex3f(-0.0f, 0.0f, 0.0f);//bottom left (left)
    glVertex3f(-0.0f, 0.0f, 3.0f);//bottom right (left)

    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 7.0f, 0.0f);//top right (right)
    glVertex3f(1.0f, 9.0f, 1.5f);//triangle (top)
    glVertex3f(2.0f, 7.0f, 3.0f);//top left (right)
    glVertex3f(2.0f, 0.0f, 3.0f);//bottom left (right)
    glVertex3f(2.0f, 0.0f, 0.0f);//bottom right (right)
	glEnd();

	glBegin(GL_POLYGON);//spike
	glVertex3f(0.9f, 8.5f, 1.4f);
	glVertex3f(1.1f, 8.5f, 1.4f);
	glVertex3f(1.0f, 10.5f, 1.5f);

	glVertex3f(1.1f, 8.5f, 1.6f);
	glVertex3f(0.9f, 8.5f, 1.6f);
	glVertex3f(1.0f, 10.5f, 1.5f);

	glVertex3f(0.9f, 8.5f, 1.6f);
	glVertex3f(0.9f, 8.5f, 1.4f);
	glVertex3f(1.0f, 10.5f, 1.5f);

	glVertex3f(1.1f, 8.5f, 1.4f);
	glVertex3f(1.1f, 8.5f, 1.6f);
	glVertex3f(1.0f, 10.5f, 1.5f);
	glEnd();
}

void building2()
{
	//tower with box on roof
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 14);
	drawBox(2, 7, 2);//body
	glTranslatef(1.2, 7, 0.5);
	glBindTexture(GL_TEXTURE_2D, 8);
	drawBox(0.7, 0.3, 1);//level1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2f, 0, -0.2f);
	glBindTexture(GL_TEXTURE_2D, 8);
	drawBox(2.4, 0.5, 2.4);//base
	glPopMatrix();

	glBegin(GL_POLYGON);//spike
	glVertex3f(1.5f, 7.0f, 0.9f);
	glVertex3f(1.7f, 7.0f, 0.9f);
	glVertex3f(1.6f, 8.0f, 1.0f);

	glVertex3f(1.5f, 7.0f, 1.1f);
	glVertex3f(1.7f, 7.0f, 1.1f);
	glVertex3f(1.6f, 8.0f, 1.0f);

	glVertex3f(1.5f, 7.0f, 1.1f);
	glVertex3f(1.5f, 7.0f, 0.9f);
	glVertex3f(1.6f, 8.0f, 1.0f);

	glVertex3f(1.7f, 7.0f, 0.9f);
	glVertex3f(1.7f, 7.0f, 1.1f);
	glVertex3f(1.6f, 8.0f, 1.0f);
	glEnd();
}

void building3()
{
	//simple box tower
	float height = 4;
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 15);
	drawBox(2, height, 2);//level1
	glTranslatef(-0.2f, 0, -0.2f);
	glBindTexture(GL_TEXTURE_2D, 8);
	drawBox(2.4, 0.5, 2.4);//base
	glPopMatrix();
}

void building4()
{
	//two Leveled tower
	float height = 6;
	float width = 2;
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 2);
	drawBox((width/2), height, 1.9);//level1
	drawBox(width, (height/1.5), 2);//level2
	glTranslatef(-0.2f, 0, -0.2f);
	glBindTexture(GL_TEXTURE_2D, 8);
	drawBox(2.4, 1.0, 2.4);//base
	glPopMatrix();
}

void building5()
{
	//triangluar looking building

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 5);
	float height = 2.0;
	float length = 4.8;
	float width = 1.8;
	drawBox(2, 2, 4);//base
	//triangle (squarebase) roof
	float height2 = 1.0;
	float length2 = 4.0;
	float width2 = 2.0;
	glTranslatef(0, 2, 0);
	glBegin(GL_POLYGON);
	//bottom
	glVertex3f(width2, 0.0, length2);
	glVertex3f(0.0, 0.0, length2);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(width2, 0.0, 0.0);
	//front
	glVertex3f(width2/2, height2, 0.5);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(width2, 0.0, 0.0);
	//back
	glVertex3f(width2/2, height2, length2-0.5);
	glVertex3f(width2, 0.0, length2);
	glVertex3f(0.0, 0.0, length2);
	//left
	glVertex3f(width2/2, height2, 0.5);
	glVertex3f(width2/2, height2, length2-0.5);
	glVertex3f(0.0, 0.0, length2);
	glVertex3f(0.0, 0.0, 0.0);
	//right
	glVertex3f(width2/2, height2, length2-0.5);
	glVertex3f(width2/2, height2, 0.5);
	glVertex3f(width, 0.0, 0.0);
	glVertex3f(width, 0.0, length2-0.5);
	glEnd();
	glPopMatrix();
}

void building6()
{//u shaped triangle building
	glPushMatrix();
	//base
	glBindTexture(GL_TEXTURE_2D, 5);
	drawBox(2, 2.0, 5);
	glTranslatef(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, 13);
	createTriangle(5.0, 1.0, 2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0, 1.5);
	glRotatef(90, 0, 1.0f, 0);
	glBindTexture(GL_TEXTURE_2D, 5);
	drawBox(2, 2.0, 5.5);
	glTranslatef(0, 2.0f, 0);
	glBindTexture(GL_TEXTURE_2D, 13);
	createTriangle(5.5, 1, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 0, 0);
	glBindTexture(GL_TEXTURE_2D, 5);
	drawBox(2, 2.0, 5);
	glTranslatef(0, 2, 0);
	glBindTexture(GL_TEXTURE_2D, 13);
	createTriangle(5.0, 1.0, 2.0);
	glPopMatrix();
}

void building7()
{//park
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 7);
	drawBox(2, 0.01, 2);//grass
	glRotatef(-90, 1, 0, 0);
	glTranslatef(1, -1, 0);
	glBindTexture(GL_TEXTURE_2D, 9);
	glutSolidCylinder(0.5, 0.05, 32, 1);//round path
	glBindTexture(GL_TEXTURE_2D, 12);
	glutSolidCylinder(0.25, 0.25, 32, 1);//statue base
	glutSolidCylinder(0.12, 0.5, 32, 1);//statue
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 9);
	glPushMatrix();
	glTranslatef(0.8, 0.0, 0.0);
	drawBox(0.5, 0.05, 2.0);//vertical path
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.8);
	drawBox(2.0, 0.05, 0.5);//horizontal path
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 16);
	glPushMatrix();
	glRotatef(-45, 0, 1, 0);//back left
	glTranslatef(0.5, 0, -0.25);
	drawBox(0.05, 0.25, 0.5);//back of chair1
	drawBox(0.25, 0.15, 0.5);//base of chair1

	glRotatef(-90, 0, 1, 0);//back right
	glTranslatef(-0.8, 0, -1.25);
	drawBox(0.05, 0.25, 0.5);//back of chair1
	drawBox(0.25, 0.15, 0.5);//base of chair1

	glRotatef(-90, 0, 1, 0);//back right
	glTranslatef(-0.7, 0, -1.25);
	drawBox(0.05, 0.25, 0.5);//back of chair1
	drawBox(0.25, 0.15, 0.5);//base of chair1

	glRotatef(-90, 0, 1, 0);//back right
	glTranslatef(-0.8, 0, -1.25);
	drawBox(0.05, 0.25, 0.5);//back of chair1
	drawBox(0.25, 0.15, 0.5);//base of chair1
	glPopMatrix();
}

void fighter()
{
	glBindTexture(GL_TEXTURE_2D, 1);
	glRotatef(180, 0, 0, 1);
	glRotatef(90, 1, 0 ,0);
	glRotatef(180,0,0,1);
	//top
	glPushMatrix();
	glBegin(GL_POLYGON);//body
	glVertex3f(0.02f, 2.0f, -5.1f);//change nose to cone
	glVertex3f(0.15f, 1.5f, -5.0f);
	glVertex3f(0.15f, 1.4f, -5.0f);
	glVertex3f(0.18f, 0.9f, -5.0f);
	glVertex3f(0.1f, -0.5f, -5.0f);
	glVertex3f(0.05f, -0.6f, -5.0f);
	glVertex3f(-0.05f, -0.6f, -5.0f);
	glVertex3f(-0.1f, -0.5f, -5.0f);
	glVertex3f(-0.18f, 0.9f, -5.0f);
	glVertex3f(-0.15f, 1.4f, -5.0f);
	glVertex3f(-0.15f, 1.5f, -5.0f);
	glVertex3f(-0.02f, 2.0f, -5.1f);
	glEnd();
	glBegin(GL_POLYGON);//airIntake+sides
	glVertex3f(0.15, 1.4f, -5.0f);
	glVertex3f(0.18, 1.5f, -5.0f);
	glVertex3f(0.23, 1.5f, -5.0f);
	glVertex3f(0.3f, 1.4f, -5.0f);
	glVertex3f(0.4f, 0.9f, -5.0f);
	glVertex3f(0.4f, -0.2f, -5.0f);
	glVertex3f(0.1f, -0.5f, -5.0f);
	glVertex3f(0, -0.5f, -5.0f);
	glVertex3f(-0.1f, -0.5f, -5.0f);
	glVertex3f(-0.4f, -0.2f, -5.0f);
	glVertex3f(-0.4f, 0.9f, -5.0f);
	glVertex3f(-0.3f, 1.4f, -5.0f);
	glVertex3f(-0.23f, 1.5f, -5.0f);
	glVertex3f(-0.18f, 1.5f, -5.0f);
	glEnd();
	glBegin(GL_POLYGON);//rightWing
	glVertex3f(0.1f, 0.9f, -5.0f);
	glVertex3f(0.4f, 0.9f, -5.0f);
	glVertex3f(1.2f, 0.3f, -5.1f);
	glVertex3f(1.2f, -0.0f, -5.1f);
	glVertex3f(0.4f, -0.2f, -5.0f);
	glVertex3f(0.1f, -0.2f, -5.0f);
	glEnd();
	glBegin(GL_POLYGON);//rightTail
	glVertex3f(0.4f, -0.2f, -5.0f);
	glVertex3f(0.7f, -0.5f, -5.0f);
	glVertex3f(0.7f, -0.7f, -5.0f);
	glVertex3f(0.2f, -0.8f, -5.0f);
	glVertex3f(0.1f, -0.5f, -5.0f);
	glVertex3f(0.1f, -0.2f, -5.0f);
	glEnd();
	glBegin(GL_POLYGON);//leftWing
	glVertex3f(-0.1f, 0.9f, -5.0f);
	glVertex3f(-0.4f, 0.9f, -5.0f);
	glVertex3f(-1.2f, 0.3f, -5.1f);
	glVertex3f(-1.2f, -0.0f, -5.1f);
	glVertex3f(-0.4f, -0.2f, -5.0f);
	glVertex3f(-0.1f, -0.2f, -5.0f);
	glEnd();
	glBegin(GL_POLYGON);//leftTail
	glVertex3f(-0.4f, -0.2f, -5.0f);
	glVertex3f(-0.7f, -0.5f, -5.0f);
	glVertex3f(-0.7f, -0.7f, -5.0f);
	glVertex3f(-0.2f, -0.8f, -5.0f);
	glVertex3f(-0.1f, -0.5f, -5.0f);
	glVertex3f(-0.1f, -0.2f, -5.0f);
	glEnd();
	glPopMatrix();
	//back
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0, -5,0);
	glBegin(GL_POLYGON);//body
	glVertex3f(-0.4f, 0.0f, 0.2f);
	glVertex3f(-0.1f, -0.2f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.2f);
	glVertex3f(0.4f, 0.0f, 0.2f);
	glEnd();
	glBegin(GL_POLYGON);//underwings
	glVertex3f(-0.7f, 0.0f, -0.2f);
	glVertex3f(-0.1f, -0.2f, -0.2f);
	glVertex3f(0.1f, -0.2f, -0.2f);
	glVertex3f(0.7f, 0.0f, -0.2f);
	glEnd();
	glBegin(GL_POLYGON);//exhaustStart
	glVertex3f(-0.1f, 0.0f, 0.5f);
	glVertex3f(-0.1f, -0.1f, 0.5f);
	glVertex3f(0.0f, -0.12f, 0.5f);
	glVertex3f(0.1f, -0.1f, 0.5f);
	glVertex3f(0.1f, 0.0f, 0.5f);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);//red for exhaust - texture2
	glBegin(GL_POLYGON);//exhaustEnd
	glVertex3f(-0.05f, 0.0f, 0.6f);
	glVertex3f(-0.05f, -0.05f, 0.6f);
	glVertex3f(0.0f, -0.06f, 0.6f);
	glVertex3f(0.05f, -0.05f, 0.6f);
	glVertex3f(0.05f, 0.0f, 0.6f);
	glColor3f(0.60f,0.60f, 0.60f);
	glEnd();
	glTranslatef(0, 0, -1.3);
	glScalef(1, 1.2, 2);
	glColor4f(1.0f,1.0f,1.0f,0.5f);//transperant cockpit
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);//texture3
	glEnable(GL_BLEND);
	glutSolidSphere(0.08, 8, 8);
	glDisable(GL_BLEND);
	glPopMatrix();

	//bottom
	glRotatef(90, 1, 0, 0);
	glPushMatrix();
	glRotatef(180,0,0,1);
	glTranslatef(0,0,10.2);
	glBindTexture(GL_TEXTURE_2D, 8);
	glBegin(GL_POLYGON);//body
	glVertex3f(0.15, 1.4f, -5.0f);
	glVertex3f(0.18, 1.5f, -5.0f);
	glVertex3f(0.23, 1.5f, -5.0f);
	glVertex3f(0.3f, 1.4f, -5.2f);
	glVertex3f(0.4f, 0.9f, -5.2f);
	glVertex3f(0.2, -0.2f, -5.0f);
	glVertex3f(0.1f, -0.2f, -5.0f);
	glVertex3f(0, -0.2f, -5.0f);
	glVertex3f(-0.1f, -0.2f, -5.0f);
	glVertex3f(-0.2, -0.2f, -5.0f);
	glVertex3f(-0.4f, 0.9f, -5.2f);
	glVertex3f(-0.3f, 1.4f, -5.2f);
	glVertex3f(-0.23f, 1.5f, -5.0f);
	glVertex3f(-0.18f, 1.5f, -5.0f);
	glVertex3f(-0.15f, 1.5f, -5.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 7);
	glBegin(GL_POLYGON);//leftFin
	glVertex3f(0.2f, -0.0f, -5.2f);
	glVertex3f(0.2f, -0.3f, -5.5f);
	glVertex3f(0.2f, -0.6f, -5.5f);
	glVertex3f(0.2f, -0.5f, -5.2f);
	glVertex3f(0.2f, -0.3f, -5.2f);
	glVertex3f(0.2f, -0.0f, -5.2f);
	glEnd();
	glBegin(GL_POLYGON);//rightFin
	glVertex3f(-0.2f, -0.0f, -5.2f);
	glVertex3f(-0.2f, -0.3f, -5.5f);
	glVertex3f(-0.2f, -0.6f, -5.5f);
	glVertex3f(-0.2f, -0.5f, -5.2f);
	glVertex3f(-0.2f, -0.3f, -5.2f);
	glVertex3f(-0.2f, -0.0f, -5.2f);
	glBindTexture(GL_TEXTURE_2D, 8);
	glEnd();

	glPopMatrix();

	//bottom
	//front
	//right
	//left
}
/*
void road(float l, float w, float h)
{
	float length = l;
	float width = w;
	float height = h;
	glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, length);//top right (top)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, height, length);//top left (top)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, height, 0.0);//bottom left (top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, height, 0.0);//bottom right (top)

    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, 0.0f, 0.0f);//top right (bottom)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);//top left (bottom)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, length);//bottom left (bottom
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0.0f, length);//bottom right (bottom)

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, -0.0f);//top right (front)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, height, -0.0f);//top left (front)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.0f);//bottom left (front)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0.0f, -0.0f);//bottom right (front)

    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0.0f, length);//bottom left (back)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, length);//bottom right (back)
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, height, length);//top right (back)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, length);//top left (back)

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.0f, height, length);//top right (left)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.0f, height, 0.0f);//top left (left)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.0f, 0.0f, 0.0f);//bottom left (left)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.0f, 0.0f, length);//bottom right (left)

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width, height, 0.0f);//top right (right)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, length);//top left (right)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0.0f, length);//bottom left (right)
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width, 0.0f, 0.0f);//bottom right (right)
	glEnd();
}//obsolete
*/
void lights()
{//streetlights
	float i;
	//glPushMatrix();
	for (i = 1; i < 9; i++)
	{
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);//rotate so lights are vertical
		glTranslatef(1, -1, 0);
		glutSolidCylinder(0.05, 1.0, 32, 1);//light post
		glRotatef(-45, 0, 1, 0);
		glTranslatef(0.70, 0, 0.70);
		glutSolidCylinder(0.05, 0.2, 32, 1);//light post angle
		glRotatef(45, 0, 1, 0);
		glutSolidSphere(0.055, 8, 8);//light hood
		glTranslatef(-0.15, 0, 0.15);
		glutSolidSphere(0.055, 8, 8);//rounded hinge bit
		glTranslatef(-0.15, 0, 0.04); // x, z, y
		glScalef(2.5, 1.0, 1.0);
		glutSolidSphere(0.055, 8, 8);//rounded bit
		glTranslatef(-0.0, 0, -0.05);
		glScalef(0.7, 0.7, 1.0);
		glutSolidSphere(0.055, 8, 8);//light bulb
		glPopMatrix();

		glTranslatef(0.0f, 0.0f, 2.0f);//space lights appart
	}
}
/*
void water(int x, int y, float float_x, float float_y, float float_xb, float float_yb, int points, int wiggle_count)//passing array to function
{
	    glBegin(GL_QUADS);
    for (x=0; x<44; x++) {
	for (y=0; y<44; y++) {
	    float_x  = (float) (x)/44;
	    float_y  = (float) (y)/44;
	    float_xb = (float) (x+1)/44;
	    float_yb = (float) (y+1)/44;

	    glTexCoord2f( float_x, float_y);
	    glVertex3f( points[x][y][0], points[x][y][1], points[x][y][2] );
			
	    glTexCoord2f( float_x, float_yb );
	    glVertex3f( points[x][y+1][0], points[x][y+1][1], points[x][y+1][2] );
			
	    glTexCoord2f( float_xb, float_yb );
	    glVertex3f( points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2] );
			
	    glTexCoord2f( float_xb, float_y );
	    glVertex3f( points[x+1][y][0], points[x+1][y][1], points[x+1][y][2] );
	}
    }
	glEnd();
	glPopMatrix();

    if (wiggle_count == 2) { // cycle the sine values
	for (y = 0; y <45; y++) {
	    points[44][y][2] = points[0][y][2];
	}

	for( x = 0; x < 44; x++ ) {
	    for( y = 0; y < 45; y++) {
		points[x][y][2] = points[x+1][y][2];
	    }		
	}		
	wiggle_count = 0;
    }    
    wiggle_count++;

}*/

