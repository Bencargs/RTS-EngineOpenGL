#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "objects.h"
#include "loadImage.h"
#include "heightMap.h"
//tga to use RGBA, create height map from alpha, use the RGB colors.

static float angle=0.0,ratio;
static float x=0.0f,y=1.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
int cameraX, cameraZ;
float cameraY = 1.0;
int drawMode=1; //1 = triangles, 0 = wireframe
int waterLevel = 0;

char h[3];//string for health
char s[30];//array holds the FPS
int frame = 0;//frames since last check
int time = 0;//elapsed time in ms
int timebase = 0;//ms since last check
int unitCount = 0;

#define RENDER					1
#define SELECT					2
#define MOVE					1
#define LOOK					3
#define BUFSIZE 1024
GLuint selectBuf[BUFSIZE];
GLint hits;
int mode = RENDER;
int cursorX,cursorY;
unsigned char zoom = 50;
int selected[32];	//array holds current selected units
int selectedCount;

//GLuint loop;
GLuint heightMapDL;
//GLuint heightMap(void);
//int heightMapDL;

#define		STEP	16
#define		HEIGHT	2
int flag = 0;
int texture[17];	//array holds the textures

Image *image1[17];    // Load Texture

struct command {
	unsigned char cmd;//stop, move, attack, guard, patroll
	float x;//posX or unitID
	float y;//posY/unused/attack with certain weapon?
	struct command *next;//linking commands/patroll
};

//typedef struct command cmd;

typedef struct {
	char name[20];
	unsigned int posX;
	unsigned int posY;
	int posZ;//might be usefull for collision detec
	unsigned int destX;
	unsigned int destY;
//	unsigned int destZ;
	char rotX;
	char rotY;
//	char rotZ;
//	char rotGunX;
//	char rotGunY;
//	char rotGunZ;
//	int speed;
	unsigned char health;
//	unsigned char max health
//	char damage;
//	char reload;
//	int kills;
//	int team;
//	int losRadius;
//	int range;
	struct command *cmd;
}unit, *pUnit;

typedef struct {
	float posX;
	float posY;
	float posZ;
} CVector3D;

unit units[256];


GLuint heightMap()
{
	GLuint MapDL;
int j,i;
int step = 16;
	if(drawMode==1)
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
	return(heightMapDL);
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
	loadHeightMap("Map/heightMap.bmp", image1[1]);

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
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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
	free(image1[1]);
//	free(image1[3]);

//  glDeleteTextures(1, &texID);
	return(1);
}

CVector3D ScreenToWorld(int x, int y)
{
    //source: http://nehe.gamedev.net/data/articles/article.asp?article=13
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    // Read all pixels at given screen XY from the Depth Buffer
    glReadPixels( x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY,
&posZ);
	CVector3D temp = {(float)posX, (float)posZ, (float)posY};
	return temp;
}//ScreenToWorld()

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
//	glRotatef(ang,0,1,0);
	glLoadIdentity();
	cameraY+=-cos(ang);
	//angle += 0.01f;
	gluLookAt(0, 40+zoom, 20+cameraZ+zoom, 0, 0+zoom+cameraY, 0+cameraZ+zoom, 0.0f,1.0f,0.0f);
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
//	glTranslatef(0,0,direction);
	glLoadIdentity();
	cameraZ+=direction;
	gluLookAt(0, 40+zoom, 20+cameraZ+zoom, 0, 0+zoom, 0+cameraZ+zoom, 0.0f,1.0f,0.0f);
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

void mouseWheel(int button, int dir, int x, int y)
{//dir is either 1 or -1
	glLoadIdentity();//Reset Camera again
    if (dir > 0)
    {
	zoom-=10;//replace with a exponential scale
        // Zoom in
    }
    else
    {
	//zoom++;
	zoom+=10;
//http://www.felixgers.de/teaching/jogl/gluLookAt.html
        // Zoom out
    }
//	glutPostRedisplay();
	//CVector3D temp = ScreenToWorld(x, y);
	//gluLookAt(temp.posX, temp.posY, heightmap[(int)temp.posX][(int)temp.posY], 0, 0, 0, 0.0f,1.0f,0.0f);
	CVector3D temp = ScreenToWorld(x, y);
	printf("%i, %i\n",x, (int)temp.posX);
//	units[selectedCount].destX = temp.posX;
//	gluLookAt(0, 40+zoom, 20+cameraZ+zoom, 0, 0+zoom+cameraY, 0+cameraZ+zoom, 0.0f,1.0f,0.0f);//max zoom
	gluLookAt((int)temp.posX, 80+zoom, 60+zoom+(char)temp.posY, (int)temp.posX, 0+zoom, 0+zoom+temp.posY, 0.0f,1.0f,0.0f);//max zoom
	//eye x,y(height),z lookat x,y,z cameraupvector
    return;
}

void startPicking() {

	GLint viewport[4];
	float ratio;

	glSelectBuffer(BUFSIZE,selectBuf);

	glGetIntegerv(GL_VIEWPORT,viewport);

	glRenderMode(GL_SELECT);

	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(cursorX,viewport[3]-cursorY,5,5,viewport);//cursorY?
	ratio = (viewport[2]+0.0) / viewport[3];
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}

//void picked(GLuint name, int sw) {
//	printf("my name = %d in %d\n",name,sw);
//}

void processHits2 (GLint hits, GLuint buffer[], int sw)
{
   GLint i, j, numberOfNames;
   GLuint names, *ptr, minZ,*ptrNames;

   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {	
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }
	  
	  ptr += names+2;
	}
   if (numberOfNames > 0) 
        {
	  ptr = ptrNames;
	  for (j = 0; j < numberOfNames; j++,ptr++) 
	  {
//		selectedCount++;
		printf ("unit %i, %s selected\n", *ptr, units[*ptr].name);
//		selected[selectedCount] = *ptr;
	  }
	}}

void stopPicking() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if (hits != 0){
		processHits2(hits,selectBuf,0);
	}
	mode = RENDER;
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
		case 119://w - toggle wireframe
			if(drawMode == 1)
				drawMode = 2;
			else
				drawMode = 1;
			break;
		case 56://8 move unit up
			units[0].posY--;
			break;
		case 53://5 move unit down
			units[0].posY++;
			break;
		case 52://4  move unit left
			units[0].posX--;
			break;
		case 54://6  move unit right
			units[0].posX++;
			break;
		case 48://0  add new unit
			unitCount++;
			unit new = {
				"M1A1-Abrams",
				5,
				5,
				5,
				0,
				0,
				0,
				0,
				100,
				};
			units[unitCount]=new;
			printf("New unit: %s\n", units[unitCount].name);
			break;
		case 127://reset
			glLoadIdentity();
		gluLookAt(x, y, z, 
		      x = 0,y = 12,z = -6,
			  0.0f,1.0f,0.0f);
	}
}

void mouseStuff(int button, int state, int x, int y)
{
//	specialKey = glutGetModifiers();
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			cursorX = x;
			cursorY = y;
			mode = SELECT;
		}
		if (button == GLUT_RIGHT_BUTTON)
		{
			cursorX = x;// dont know why- donest reset with out this (?)
			cursorY = y;
			/*units[selectedCount].destX = cursorX;
			units[selectedCount].destY = cursorY;*/
			CVector3D temp = ScreenToWorld(cursorX, cursorY);
			units[selectedCount].destX = temp.posX;
			units[selectedCount].destY = temp.posY;
//			units[selectedCount].destZ = temp.posZ;
			//printf("%i %i\n", units[selectedCount].destX, units[selectedCount].destY);
			mode = MOVE;
		}
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
	heightMapDL = heightMap();
//	heightMapDL = glGenLists(1);
	glEnable(GL_COLOR_MATERIAL);//enables colors
	glEnable(GL_LIGHTING);//turns lighting on
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
	glClearColor(0.7f, 0.9f, 1.0f, 1.0f);//changes background to sky color
	unit tank = {
		"M1A1-Abrams",
		5,
		5,
		8,
		7,
		0,
		0,
		0,
		100,
	};
	units[0] = tank;
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

void drawSelect() // draws circle under units - replace with texture?
{//replace with bresenhams algorythm, drawlist this
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(2);
	glTranslatef(0, -0.5, 0);
	glBegin(GL_LINES);
	int j;
	int radius = 1;
	glBegin(GL_LINES);
		x = (float)radius * cos(359 * 3.14/180.0f);
		z = (float)radius * sin(359 * 3.14/180.0f);
		for(j = 0; j < 360; j++)
		{
			glVertex3f(x,0,z);
			x = (float)radius * cos(j * 3.14/180.0f);
			z = (float)radius * sin(j * 3.14/180.0f);
			glVertex3f(x,0,z);
		}
	glEnd();
	glPopMatrix();
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


//	glCallList(heightMapDL);
	heightMap();

			glBegin(GL_LINES);
			glVertex3f(units[selectedCount].posX, 50, units[selectedCount].posY);
			glVertex3f(units[selectedCount].destX, 50, units[selectedCount].destY);
			glEnd();

	if (mode == SELECT)
	{
		startPicking();
	}
//	unit
	int i;//move thos to top of program?
	for(i=0;i<unitCount+1; i++)
	{
	glPushMatrix();
		glColor3f(0.90f, 0.00f, 0.00f);
		if((units[i].posX != units[i].destX) && (units[i].posY != units[i].destY))
		{
			//printf("%i %i\n", units[i].destX, units[i].destY);
			if(units[i].posX < units[i].destX)
			{
				units[i].posX = units[i].posX + 1;
			}
			else
			{
				units[i].posX = units[i].posX - 1;
			}

			if(units[i].posY < units[i].destY)
			{
				units[i].posY = units[i].posY + 1;
			}
			else
			{
				units[i].posY = units[i].posY - 1;
			}
		}
		glTranslatef(units[i].posX, heightmap[units[i].posX][units[i].posY]/HEIGHT + 0.5, units[i].posY);
//		replace with a loop, 0 to count		the +0.5 is becuase glut cubes start at -0.5- keeps it on surface
//		glRotatef((tempRotX), 1, 0, 0);
		glPushName(i);
		glutSolidCube(1);
		glColor3f(0.00f, 0.00f, 0.90f);
		sprintf(h,"%i", units[i].health);
		renderBitmapString(-0.5, 1, GLUT_BITMAP_TIMES_ROMAN_10,h);
//		-0.5 again because glutcube starts ar -0.5, remove when including 3d model
		glPopName();
		drawSelect();
	glPopMatrix();
	}

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

	if (mode == SELECT)
		stopPicking();
	else
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
	glutMouseFunc(mouseStuff);
	glutMouseWheelFunc(mouseWheel); // free g;ut
//	glutPassiveMotionFunc(processMousePassiveMotion);
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);//render if not doing anything, animate
	glutReshapeFunc(resize);
	initRendering(); //Initialize rendering
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn&apos;t return.
	return 0; //This line is never reached
}

