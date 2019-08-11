#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "objects.h"
#include "loadImage.h"
#include "heightmap.h"
//tga to use RGBA, create height map from alpha, use the RGB colors.

static float angle=0.0,ratio;
static float x=0.0f,y=1.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
int mode=1; //1 = triangles, 0 = wireframe
int waterLevel = 0;

char s[30];//array holds the FPS
int frame = 0;//frames since last check
int time = 0;//elapsed time in ms
int timebase = 0;//ms since last check

//GLuint loop;
GLuint heightmapDL;
//GLuint heightmap(void);
//int heightmapDL;

#define		STEP	16
#define		HEIGHT	2
int flag = 0;
int texture[17];	//array holds the textures

Image *image1[17];    // Load Texture

GLuint heightmap()
{
	GLuint MapDL;
int j,i;
int step = 16;
	if(mode==1)
	{
		glBegin(GL_TRIANGLES);
	}
	else
	{
		glBegin(GL_LINES);
	}
	MapDL = glGenLists(1);
	glNewList(MapDL, GL_COMPILE);

  for (i = sizeY; i > 1; (i=i-2))
  {//map is 2 less x and 2 less y from original (fix!)
	  for (j = sizeX; j > 1; (j=j-2))
  	{//done to neaten up edges, run to full with conditions?
//	 ______ 
//	|\_2__/|	[0][0]...[0][Y]
//	|1|__|3|	...
//	|/_4__\|	[X][0]...[X][Y]
//
	glColor3f(0.5, heightmap[i][j]*0.02, 0.5);
//	glBindTexture(GL_TEXTURE_2D, 3);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3i(i, heightmap[i][j]/HEIGHT, j); glTexCoord2f(0.0f, 0.0f);
	glVertex3i((i-1), heightmap[i-1][j+1]/HEIGHT, j+1); glTexCoord2f(-1.0f, 1.0f);
	glVertex3i(i-1, heightmap[i-1][j-1]/HEIGHT, j-1); glTexCoord2f(-1.0f, -1.0f);

	glVertex3i(i, heightmap[i][j]/HEIGHT, j); glTexCoord2f(0.0f, 0.0f);
	glVertex3i(i-1, heightmap[i-1][j+1]/HEIGHT, j+1); glTexCoord2f(-1.0f, 1.0f);
	glVertex3i(i+1, heightmap[i+1][j+1]/HEIGHT, j+1); glTexCoord2f(1.0f, 1.0f);

	glVertex3i(i, heightmap[i][j]/HEIGHT, j); glTexCoord2f(0.0f, 0.0f);
	glVertex3i(i+1, heightmap[i+1][j+1]/HEIGHT, j+1); glTexCoord2f(1.0f, -1.0f);
	glVertex3i(i+1, heightmap[i+1][j-1]/HEIGHT, j-1); glTexCoord2f(-1.0f, -1.0f);

	glVertex3i(i, heightmap[i][j]/HEIGHT, j); glTexCoord2f(0.0f, 0.0f);
	glVertex3i(i-1, heightmap[i-1][j-1]/HEIGHT, j-1); glTexCoord2f(1.0f, -1.0f);
	glVertex3i(i+1, heightmap[i+1][j-1]/HEIGHT, j-1); glTexCoord2f(1.0f, 1.0f);
	}	
  }	
	glEnd();
//water

	glPushMatrix();
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, 3);
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.8);
	glVertex3i(0, waterLevel, 0); glTexCoord2f (0, 1);
	glVertex3i(sizeX, waterLevel, 0); glTexCoord2f (0, 0);
	glVertex3i(sizeX, waterLevel, sizeY); glTexCoord2f (1, 0);
	glVertex3i(0, waterLevel, sizeY); glTexCoord2f (1, 1);
	glEnd();
	glPopMatrix();
	glEndList();

//	glutSwapBuffers();
	return(heightmapDL);
}


int textures()
{// Load Bitmaps And Convert To Textures
	//http://www.gamedev.net/reference/articles/article947.asp
	//+http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=06
	int i;
	for(i=1; i<17; i++)
	{
		image1[i] = (Image *) malloc(sizeof(Image));// allocate space for texture
		if (image1[i] == NULL)
		{
			printf("Error allocating space for image at ");
			exit(0);
		}
	}
	loadHeightMap("Map/heightmap.bmp", image1[1]);

//	loadImage("Textures/brickBuilding.bmp", image1[2]);
	loadImage("Textures/water.bmp", image1[3]);
//	loadImage("Textures/cloverfield3.bmp", image1[3]);
//	loadImage("Textures/darkMetal.bmp", image1[4]);
//	loadImage("Textures/darktiles.bmp", image1[5]);
//	loadImage("Textures/fighter.bmp", image1[6]);
//	loadImage("Textures/grass.bmp", image1[7]);
//	loadImage("Textures/metal.bmp", image1[8]);
//	loadImage("Textures/pavement.bmp", image1[9]);
//	loadImage("Textures/road1.bmp", image1[10]);
//	loadImage("Textures/road2.bmp", image1[11]);
//	loadImage("Textures/statue.bmp", image1[12]);
//	loadImage("Textures/tiles.bmp", image1[13]);
//	loadImage("Textures/tower1.bmp", image1[14]);
//	loadImage("Textures/tower3.bmp", image1[15]);
//	loadImage("Textures/wood.bmp", image1[16]);
	// Create 17 Texture, starting at 0 (indexed at 1)	

	glGenTextures(16, &texture[0]);

	for(i=1; i<17; i++)
	{//bind each image as a texture
 		glBindTexture(GL_TEXTURE_2D, texture[(i-1)]);// 2d texture (x and y size)
		//use GL_NEAREST if resizing too slow
 		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
		glTexImage2D(GL_TEXTURE_2D, // 2d texture
					 0, //level of detail 0 (normal)
					 3, //3 components (red, green, blue)
					 image1[i]->sizeX,//x size from image
					 image1[i]->sizeY,//y size from image
					 0, //border 0 (normal)
					 GL_RGB, //rgb color data
					 GL_UNSIGNED_BYTE, //how data stored
					 image1[i]->data); //images' data
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	//glBindtexture - tell what texture id working with
	//glTexParameteri ... - how to resize
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); - lighting
	//glTexImage2D -- uploads to videomemory
//	free(image1[1]);
	return(1);
}

void rotateX(float ang)
{
	glRotatef(ang,1,0,0);
/*
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx,y + ly, z + lz,
			0.0f, 1.0f, 0.0f);
*/
}

void rotateY(float ang)
{
	glRotatef(ang,0,1,0);
/*
	ly = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
			x + lx, y + ly, z + lz,
			0.0f, 1.0f, 0.0f);
*/
}

void moveMeFlat(float direction) 
{
	glTranslatef(0,0,direction);
/*	if (direction == 0)
		direction = 1;
	x = x + direction*(lx)*0.1;
	y = y + direction*(ly)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
*/
}

void keyPress(unsigned char key, int x, int y) 
{
	switch (key)
	{//X+Y are confused
		case 27:
			exit(0);
		case 122://z zoom in
			moveMeFlat(10.0);break;
		case 90://Z zoom out
			moveMeFlat(-10.0);break;
		case 120://x rotate about x clockwise
			//angle += 0.01f;
			rotateX(1);break;
		case 88://X rotate about x anti-clockwise
			//angle -=0.01f;
			rotateX(-1);break;
		case 121://y rotate about y clockwise
			//angle += 0.01f;
			rotateY(1);break;
		case 89://Y rotate about y anti-clockwise
			//angle -= 0.01f;
			rotateY(-1);break;
		case 112://p for flat polygons
			glDisable (GL_BLEND);
			glShadeModel (GL_SMOOTH);
			glDisable (GL_POLYGON_SMOOTH);
			break;
		case 80://P for smooth shaded polygons (anti aliasing
			glEnable (GL_POLYGON_SMOOTH);
			glShadeModel (GL_FLAT);
			glEnable (GL_BLEND);
			break;
		case 43://+ increase water level
			waterLevel++;
			break;
		case 45://- decrease water level
			waterLevel--;
			break;
		case 119://F1 - toggle wireframe
			if(mode == 1)
				mode = 2;
			else
				mode = 1;
			break;
		case 127://reset
			glLoadIdentity();
		gluLookAt(x, y, z, 
		      x = 0,y = 12,z = -6,
			  0.0f,1.0f,0.0f);
	}
}

void initRendering() 
{
	textures();// Load The Texture(s)
	glEnable(GL_TEXTURE_2D);// Enable Texture Mapping
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
	heightmapDL = heightmap();
//	heightmapDL = glGenLists(1);
	glEnable(GL_COLOR_MATERIAL);//enables colors
	glEnable(GL_LIGHTING);//turns lighting on
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
	glClearColor(0.7f, 0.9f, 1.0f, 1.0f);//changes background to sky color
}

//Called when the window is resized
void resize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);//Switch to setting camera perspective
	glLoadIdentity();//Reset Camera
	
	// Set the viewport to be the entire window
    	glViewport(0, 0, w, h);//converts from corrdinates to pixel values

	// Set the clipping volume
	gluPerspective(45,ratio,0.1,800);
	//fov,aspect,znear,zfar
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//Reset Camera again
	y=5;
	z=25;
	gluLookAt(x, y, z, 
		  	x + lx,y + ly,z + lz,
			0.0f,1.0f,0.0f);
	}

void renderBitmapString(float x, float y, void *font, char *string) 
{  
	char *c;//take in string
	glRasterPos2f(x,y);//set position for text
	for (c=string; *c != '\0'; c++) //untill no more characters;
	{
		glutBitmapCharacter(font, *c);//put text in possition
	}
}

void drawScene() 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glColor3f(0.60f,0.60f, 0.60f);

    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {30.0f, 30.0f, 10.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
//    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
  //  GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    //glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

//	glCallList(heightmapDL);
	heightmap();

	//calculate fps
	frame++;//increase frame count
	time=glutGet(GLUT_ELAPSED_TIME);//get elapsed time
	if (time - timebase > 1000)//if more than 1 second;
	{//print out time
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}
	renderBitmapString(0, 0, GLUT_BITMAP_8_BY_13,s);//print to screen

	glutSwapBuffers(); //Send the 3D scene to the screen

}

int main(int argc, char** argv) 
{
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 400); //Set the window size
	//glutInitWindowPosition(500,300);
    
	//Create the window
	glutCreateWindow("'Up It Goes' Assignment. - Ben Cargill");
	//Set handler functions for drawing, keypresses, and window resizes
	glutKeyboardFunc(keyPress);
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);//render if not doing anything, animate
	glutReshapeFunc(resize);
	initRendering(); //Initialize rendering
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn&apos;t return.
	return 0; //This line is never reached
}

