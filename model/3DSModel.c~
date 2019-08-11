#include <stdio.h>
#include <stdlib.h>#include <math.h>#include <GL/glut.h>
#include "loadImage.h"
#include <string.h>
#include <sys/stat.h>

//3dS Max loader by Damiano Vitulli
// The chunk's id numbers

#define MAIN_CHUNK			0x4D4D
#define EDITOR_CHUNK			0x3D3D
#define OBJECT_BLOCK			0x4000
#define TRIANGULAR_MESH			0x4100
#define VERTICES_LIST			0x4110
#define FACES_DESCRIPTION		0x4120
//FACES MATERIAL			0x4130
#define MAPPING_COORDINATES_LIST	0x4140
//SMOOTHING GROUP LIST		0x4150
//LOCAL COORDINATES SYSTEM	0x4160
//LIGHT				0x4600
//SPOTLIGHT			0x4610
//CAMERA				0x4700
//MATERIAL BLOCK			0xAFFF
//MATERIAL NAME			0xA000
//AMBIENT COLOR			0xA010
//DIFFUSE COLOR			0xA020
//SPECULAR COLOR			0xA030
//TEXTURE MAP 1			0xA200
//BUMP MAP			0xA230
//REFLECTION MAP			0xA220
//MAPPING FILENAME		0xA300
//MAPPING PARAMETERS		0xA351
//KEYFRAMER CHUNK			0xB000
//MESH INFORMATION BLOCK		0xB002
//SPOT LIGHT INFORMATION BLOCK	0xB007
//FRAMES (START AND END)		0xB008
//OBJECT NAME			0xB010
//OBJECT PIVOT POINT		0xB013
//POSITION TRACK			0xB020
//ROTATION TRACK			0xB021
//SCALE TRACK			0xB022
//HIERARCHY POSITION		0xB030

int num_texture=-1;

typedef struct                       /**** BMP file info structure ****/
    {
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
    char *data;
    } BITMAPINFOHEADER;

int texture[17];	//array holds the textures
Image *image1[17];    // Load Texture

#define MAX_POLYGONS 8000
polygon_type polygon[MAX_POLYGONS];

#define MAX_VERTICES 8000
vertex_type vertex[MAX_VERTICES];

typedef struct{
   float x,y,z;
}vertex_type;
//line in 3d space

typedef struct{
   int a,b,c;
}polygon_type;

typedef struct{
   float u,v;
}mapcoord_type;
//x and y coordinates for textures

typedef struct {
	char name[20];
    
	int vertices_qty;
    int polygons_qty;

    vertex_type vertex[MAX_VERTICES]; 
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture;
} obj_type, *obj_type_ptr;

/*
typedef struct{
   vertex_type vertex[MAX_VERTICES];
   polygon_type polygon[MAX_POLYGONS];
   mapcoord_type mapcoord[MAX_VERTICES];
   int id_texture;
}obj_type,*obj_type_ptr;
*/

obj_type object;

obj_type cube = 
{
	"john",
	7,
	12,
    {
        -10,-10, 10, //vertex v0
         10,-10, 10, //vertex v1
         10,-10,-10, //vertex v2
        -10,-10,-10, //vertex v3
        -10, 10, 10, //vertex v4
         10, 10, 10, //vertex v5
         10, 10,-10, //vertex v6 
        -10, 10,-10  //vertex v7
    },  
    {
        0, 1, 4, //polygon v0,v1,v4
        1, 5, 4, //polygon v1,v5,v4
        1, 2, 5, //polygon v1,v2,v5
        2, 6, 5, //polygon v2,v6,v5
        2, 3, 6, //polygon v2,v3,v6
        3, 7, 6, //polygon v3,v7,v6
        3, 0, 7, //polygon v3,v0,v7
        0, 4, 7, //polygon v0,v4,v7
        4, 5, 7, //polygon v4,v5,v7
        5, 6, 7, //polygon v5,v6,v7
        3, 2, 0, //polygon v3,v2,v0
        2, 1, 0, //polygon v2,v1,v0
    },
    {
        0.0, 0.0, // mapping coordinates for vertex v0
        1.0, 0.0, // mapping coordinates for vertex v1
        1.0, 0.0, // mapping coordinates for vertex v2
        0.0, 0.0, // mapping coordinates for vertex v3
        0.0, 1.0, // mapping coordinates for vertex v4
        1.0, 1.0, // mapping coordinates for vertex v5
        1.0, 1.0, // mapping coordinates for vertex v6 
        0.0, 1.0 // mapping coordinates for vertex v7
   },
   0, // identifier for the texture 
};


long filelength(int f)
{
    struct stat buf;

    fstat(f, &buf);

    return(buf.st_size);
}

char Load3DS (obj_type_ptr p_object, char *p_filename)
{//pointer to object, name of file
   int i;
   FILE *l_file;
   unsigned short l_chunk_id;
   unsigned int l_chunk_length;
   unsigned char l_char;
   unsigned short l_qty;
   unsigned short l_face_flags;

   if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file
 while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
   {//ftel current pointer possition
      fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header id
		printf("ChunkID: %x\n",l_chunk_id); 
      fread (&l_chunk_length, 4, 1, l_file); //Read the length of the chunk
		printf("ChunkLenght: %x\n",l_chunk_length);

      switch (l_chunk_id)
      {//scan thu to read only important chunks
         case MAIN_CHUNK: //main chunk, do nothing
         break;
         case EDITOR_CHUNK://3d editor chunk, discard
         break;
         case OBJECT_BLOCK://object name, store in name field
            i=0;
            do
            {
               fread (&l_char, 1, 1, l_file);
             p_object->name[i]=l_char;
             i++;
            }while(l_char != '\0' && i<20);
         break;
         case TRIANGULAR_MESH://empty node, ignore
         break;
         case VERTICES_LIST://model vertices
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
          p_object->vertices_qty = l_qty;//number of vertices
            printf("Number of vertices: %d\n",l_qty);
            for (i=0; i<l_qty; i++)//loop thru all vertex, and add each to object
            {
               fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
		printf("Vertices list x: %f\n",p_object->vertex[i].x);
               fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
		printf("Vertices list y: %f\n",p_object->vertex[i].y);
               fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
		printf("Vertices list z: %f\n",p_object->vertex[i].z);
            }
         break;
         case FACES_DESCRIPTION://model poly's
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
          p_object->polygons_qty = l_qty;//total faces
            printf("Number of polygons: %d\n",l_qty); 
            for (i=0; i<l_qty; i++)
            {//loop thru total faces and add each
               fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
		printf("Polygon point a: %d\n",p_object->polygon[i].a);
               fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
		printf("Polygon point b: %d\n",p_object->polygon[i].b);
               fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
		printf("Polygon point c: %d\n",p_object->polygon[i].c);
               fread (&l_face_flags, sizeof (unsigned short), 1, l_file);//if face is visible-ignored
		printf("Face flags: %x\n",l_face_flags);
            }
         break;
         case MAPPING_COORDINATES_LIST://mapping coordinates, each point has 2 values, u and v
            fread (&l_qty, sizeof (unsigned short), 1, l_file);
            for (i=0; i<l_qty; i++)
            {
             fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
		printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
             fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
		printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
            }
         break;
         default://useless function, just move pointer to next chunk
            fseek(l_file, l_chunk_length-6, SEEK_CUR);
      } 
   }
   fclose (l_file); // Closes the file stream
   return (1); // Returns ok
}

int loadTexture(char *filename)
{
    FILE * file;
    char temp;
    long i;

    BITMAPINFOHEADER infoheader;

    num_texture++; // The counter of the current texture is increased

    if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
    fread(&infoheader.biWidth, sizeof(int), 1, file);

    fread(&infoheader.biHeight, sizeof(int), 1, file);

    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    if (infoheader.biPlanes != 1) {
	    printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
	    return 0;
    }

    // read the bpp
    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
      printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
      return 0;
    }

    fseek(file, 24, SEEK_CUR);

    // read the data.
    infoheader.data = (char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
    if (infoheader.data == NULL) {
	    printf("Error allocating memory for color-corrected image data\n");
	    return 0;
    }

    if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
	    printf("Error reading image data from %s.\n", filename);
	    return 0;
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
	    temp = infoheader.data[i];
	    infoheader.data[i] = infoheader.data[i+2];
	    infoheader.data[i+2] = temp;
    }


    fclose(file); // Closes the file stream


    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);
    
    free(infoheader.data); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}

//////////////
void display(void)
{
    int l_index;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
  glMatrixMode(GL_MODELVIEW); // Modeling transformation
//  glLoadIdentity(); // Initialize the model matrix as identity
    
//    glTranslatef(0.0,0.0,-300); // We move the object forward (the model matrix is multiplied by the translation matrix)

//    glBindTexture(GL_TEXTURE_2D, cube.id_texture); 
      glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 


    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<object.polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
                      object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
                    object.vertex[ object.polygon[l_index].a ].y,
                    object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
                      object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
                    object.vertex[ object.polygon[l_index].b ].y,
                    object.vertex[ object.polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
                      object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
                    object.vertex[ object.polygon[l_index].c ].y,
                    object.vertex[ object.polygon[l_index].c ].z);
    }
    glEnd();


    glBegin(GL_TRIANGLES); // GlBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<12;l_index++)
    {
//        glColor3f(1.0,0.0,0.0); // Color for the vertex
	glTexCoord2f( cube.mapcoord[ cube.polygon[l_index].a ].u,
		cube.mapcoord[ cube.polygon[l_index].a ].v);
        glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x,
		cube.vertex[ cube.polygon[l_index].a ].y,
		cube.vertex[ cube.polygon[l_index].a ].z);//Vertex definition

//        glColor3f(0.0,1.0,0.0);
	glTexCoord2f( cube.mapcoord[ cube.polygon[l_index].b ].u,
                 cube.mapcoord[ cube.polygon[l_index].b ].v);
        glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x,
		cube.vertex[ cube.polygon[l_index].b ].y,
		cube.vertex[ cube.polygon[l_index].b ].z);

//        glColor3f(0.0,0.0,1.0);
	glTexCoord2f( cube.mapcoord[ cube.polygon[l_index].c ].u,
		cube.mapcoord[ cube.polygon[l_index].c ].v);
        glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x,
		cube.vertex[ cube.polygon[l_index].c ].y,
		cube.vertex[ cube.polygon[l_index].c ].z);
    }
    glEnd();
//    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // This clear the background color to black
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
   	
    // Viewport transformation
    glViewport(0,0,800,400);  

    // Projection transformation
  glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
  glLoadIdentity(); // We initialize the projection matrix as identity
  gluPerspective(45.0f,800/400,10.0f,10000.0f); // We define the "viewing volume"
   
    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
    
    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

    Load3DS (&object,"block.3ds");
    object.id_texture=loadTexture("Textures/water.bmp");
//    cube.id_texture=loadTexture("Textures/water.bmp");


    
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture==-1)
    {
    	printf("texture not found\n");
        //MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }
}

void rotateX(float ang)
{
	glRotatef(ang,1,0,0);
}

void rotateY(float ang)
{
	glRotatef(ang,0,1,0);
}

void moveMeFlat(float direction) 
{
	glTranslatef(0,0,direction);
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
	}
}

void resize (int width, int height)
{
//  screen_width=width; // We obtain the new screen width values and store it
//  screen_height=height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,800,400); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,800/400,10.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,400);
    glutInitWindowPosition(0,0);
    glutCreateWindow("www.spacesimulator.net - 3d engine tutorials: Tutorial 4");  
    glutKeyboardFunc(keyPress);  
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
//  glutKeyboardFunc (keyboard);
//  glutSpecialFunc (keyboard_s);
  init();
    glutMainLoop();

    return(0);    
}

/*
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Model_3DS::Model_3DS()
{
	// Initialization

	// Don't show the normals by default
	shownormals = false;

	// The model is lit by default
	lit = true;

	// The model is visible by default
	visible = true;

	// Set up the default position
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	// Set up the default rotation
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;

	// Set up the path
	path = new char[80];
	sprintf(path, "");

	// Zero out our counters for MFC
	numObjects = 0;
	numMaterials = 0;

	// Set the scale to one
	scale = 1.0f;
}

Model_3DS::~Model_3DS()
{

}

void Model_3DS::Load(char *name)
{
	// holds the main chunk header
	ChunkHeader main;

	// strip "'s
	if (strstr(name, "\""))
		name = strtok(name, "\"");

	// Find the path
	if (strstr(name, "/") || strstr(name, "\\"))
	{
		// Holds the name of the model minus the path
		char *temp;

		// Find the name without the path
		if (strstr(name, "/"))
			temp = strrchr(name, '/');
		else
			temp = strrchr(name, '\\');

		// Allocate space for the path
		path = new char[strlen(name)-strlen(temp)+1];

		// Get a pointer to the end of the path and name
		char *src = name + strlen(name) - 1;

		// Back up until a \ or the start
		while (src != path && !((*(src-1)) == '\\' || (*(src-1)) == '/'))
			src--;

		// Copy the path into path
		memcpy (path, name, src-name);
		path[src-name] = 0;
	}

	// Load the file
	bin3ds = fopen(name,"rb");

	// Make sure we are at the beginning
	fseek(bin3ds, 0, SEEK_SET);

	// Load the Main Chunk's header
	fread(&main.id,sizeof(main.id),1,bin3ds);
    fread(&main.len,sizeof(main.len),1,bin3ds);

	// Start Processing
	MainChunkProcessor(main.len, ftell(bin3ds));

	// Don't need the file anymore so close it
	fclose(bin3ds);

	// Calculate the vertex normals
	CalculateNormals();

	// For future reference
	modelname = name;

	// Find the total number of faces and vertices
	totalFaces = 0;
	totalVerts = 0;

	for (int i = 0; i < numObjects; i ++)
	{
		totalFaces += Objects[i].numFaces/3;
		totalVerts += Objects[i].numVerts;
	}

	// If the object doesn't have any texcoords generate some
	for (int k = 0; k < numObjects; k++)
	{
		if (Objects[k].numTexCoords == 0)
		{
			// Set the number of texture coords
			Objects[k].numTexCoords = Objects[k].numVerts;

			// Allocate an array to hold the texture coordinates
			Objects[k].TexCoords = new GLfloat[Objects[k].numTexCoords * 2];

			// Make some texture coords
			for (int m = 0; m < Objects[k].numTexCoords; m++)
			{
				Objects[k].TexCoords[2*m] = Objects[k].Vertexes[3*m];
				Objects[k].TexCoords[2*m+1] = Objects[k].Vertexes[3*m+1];
			}
		}
	}

	// Let's build simple colored textures for the materials w/o a texture
	for (int j = 0; j < numMaterials; j++)
	{
		if (Materials[j].textured == false)
		{
			unsigned char r = Materials[j].color.r;
			unsigned char g = Materials[j].color.g;
			unsigned char b = Materials[j].color.b;
			Materials[j].tex.BuildColorTexture(r, g, b);
			Materials[j].textured = true;
		}
	}
}

void Model_3DS::Draw()
{
	if (visible)
	{
	glPushMatrix();

		// Move the model
		glTranslatef(pos.x, pos.y, pos.z);

		// Rotate the model
		glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
		glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
		glRotatef(rot.z, 0.0f, 0.0f, 1.0f);

		glScalef(scale, scale, scale);

		// Loop through the objects
		for (int i = 0; i < numObjects; i++)
		{
			// Enable texture coordiantes, normals, and vertices arrays
			if (Objects[i].textured)
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			if (lit)
				glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);

			// Point them to the objects arrays
			if (Objects[i].textured)
				glTexCoordPointer(2, GL_FLOAT, 0, Objects[i].TexCoords);
			if (lit)
				glNormalPointer(GL_FLOAT, 0, Objects[i].Normals);
			glVertexPointer(3, GL_FLOAT, 0, Objects[i].Vertexes);

			// Loop through the faces as sorted by material and draw them
			for (int j = 0; j < Objects[i].numMatFaces; j ++)
			{
				// Use the material's texture
				Materials[Objects[i].MatFaces[j].MatIndex].tex.Use();

				glPushMatrix();

					// Move the model
					glTranslatef(Objects[i].pos.x, Objects[i].pos.y, Objects[i].pos.z);

					// Rotate the model
					//glRotatef(Objects[i].rot.x, 1.0f, 0.0f, 0.0f);
					//glRotatef(Objects[i].rot.y, 0.0f, 1.0f, 0.0f);
					//glRotatef(Objects[i].rot.z, 0.0f, 0.0f, 1.0f);

					glRotatef(Objects[i].rot.z, 0.0f, 0.0f, 1.0f);
					glRotatef(Objects[i].rot.y, 0.0f, 1.0f, 0.0f);
					glRotatef(Objects[i].rot.x, 1.0f, 0.0f, 0.0f);

					// Draw the faces using an index to the vertex array
					glDrawElements(GL_TRIANGLES, Objects[i].MatFaces[j].numSubFaces, GL_UNSIGNED_SHORT, Objects[i].MatFaces[j].subFaces);

				glPopMatrix();
			}

			// Show the normals?
			if (shownormals)
			{
				// Loop through the vertices and normals and draw the normal
				for (int k = 0; k < Objects[i].numVerts * 3; k += 3)
				{
					// Disable texturing
					glDisable(GL_TEXTURE_2D);
					// Disbale lighting if the model is lit
					if (lit)
						glDisable(GL_LIGHTING);
					// Draw the normals blue
					glColor3f(0.0f, 0.0f, 1.0f);

					// Draw a line between the vertex and the end of the normal
					glBegin(GL_LINES);
						glVertex3f(Objects[i].Vertexes[k], Objects[i].Vertexes[k+1], Objects[i].Vertexes[k+2]);
						glVertex3f(Objects[i].Vertexes[k]+Objects[i].Normals[k], Objects[i].Vertexes[k+1]+Objects[i].Normals[k+1], Objects[i].Vertexes[k+2]+Objects[i].Normals[k+2]);
					glEnd();

					// Reset the color to white
					glColor3f(1.0f, 1.0f, 1.0f);
					// If the model is lit then renable lighting
					if (lit)
						glEnable(GL_LIGHTING);
				}
			}
		}

	glPopMatrix();
	}
}

void Model_3DS::CalculateNormals()
{
	// Let's build some normals
	for (int i = 0; i < numObjects; i++)
	{
		for (int g = 0; g < Objects[i].numVerts; g++)
		{
			// Reduce each vert's normal to unit
			float length;
			Vector unit;

			unit.x = Objects[i].Normals[g*3];
			unit.y = Objects[i].Normals[g*3+1];
			unit.z = Objects[i].Normals[g*3+2];

			length = (float)sqrt((unit.x*unit.x) + (unit.y*unit.y) + (unit.z*unit.z));

			if (length == 0.0f)
				length = 1.0f;

			unit.x /= length;
			unit.y /= length;
			unit.z /= length;

			Objects[i].Normals[g*3]   = unit.x;
			Objects[i].Normals[g*3+1] = unit.y;
			Objects[i].Normals[g*3+2] = unit.z;
		}
	}
}

void Model_3DS::MainChunkProcessor(long length, long findex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			// This is the mesh information like vertices, faces, and materials
			case EDIT3DS	:
				EditChunkProcessor(h.len, ftell(bin3ds));
				break;
			// I left this in case anyone gets very ambitious
			case KEYF3DS	:
				//KeyFrameChunkProcessor(h.len, ftell(bin3ds));
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::EditChunkProcessor(long length, long findex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// First count the number of Objects and Materials
	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case OBJECT	:
				numObjects++;
				break;
			case MATERIAL	:
				numMaterials++;
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// Now load the materials
	if (numMaterials > 0)
	{
		Materials = new Material[numMaterials];

		// Material is set to untextured until we find otherwise
		for (int d = 0; d < numMaterials; d++)
			Materials[d].textured = false;

		fseek(bin3ds, findex, SEEK_SET);

		int i = 0;

		while (ftell(bin3ds) < (findex + length - 6))
		{
			fread(&h.id,sizeof(h.id),1,bin3ds);
			fread(&h.len,sizeof(h.len),1,bin3ds);

			switch (h.id)
			{
				case MATERIAL	:
					MaterialChunkProcessor(h.len, ftell(bin3ds), i);
					i++;
					break;
				default			:
					break;
			}

			fseek(bin3ds, (h.len - 6), SEEK_CUR);
		}
	}

	// Load the Objects (individual meshes in the whole model)
	if (numObjects > 0)
	{
		Objects = new Object[numObjects];

		// Set the textured variable to false until we find a texture
		for (int k = 0; k < numObjects; k++)
			Objects[k].textured = false;

		// Zero the objects position and rotation
		for (int m = 0; m < numObjects; m++)
		{
			Objects[m].pos.x = 0.0f;
			Objects[m].pos.y = 0.0f;
			Objects[m].pos.z = 0.0f;

			Objects[m].rot.x = 0.0f;
			Objects[m].rot.y = 0.0f;
			Objects[m].rot.z = 0.0f;
		}

		// Zero out the number of texture coords
		for (int n = 0; n < numObjects; n++)
			Objects[n].numTexCoords = 0;

		fseek(bin3ds, findex, SEEK_SET);

		int j = 0;

		while (ftell(bin3ds) < (findex + length - 6))
		{
			fread(&h.id,sizeof(h.id),1,bin3ds);
			fread(&h.len,sizeof(h.len),1,bin3ds);

			switch (h.id)
			{
				case OBJECT	:
					ObjectChunkProcessor(h.len, ftell(bin3ds), j);
					j++;
					break;
				default			:
					break;
			}

			fseek(bin3ds, (h.len - 6), SEEK_CUR);
		}
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::MaterialChunkProcessor(long length, long findex, int matindex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case MAT_NAME	:
				// Loads the material's names
				MaterialNameChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			case MAT_AMBIENT	:
				//ColorChunkProcessor(h.len, ftell(bin3ds));
				break;
			case MAT_DIFFUSE	:
				DiffuseColorChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			case MAT_SPECULAR	:
				//ColorChunkProcessor(h.len, ftell(bin3ds));
			case MAT_TEXMAP	:
				// Finds the names of the textures of the material and loads them
				TextureMapChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::MaterialNameChunkProcessor(long length, long findex, int matindex)
{
	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Read the material's name
	for (int i = 0; i < 80; i++)
	{
		Materials[matindex].name[i] = fgetc(bin3ds);
		if (Materials[matindex].name[i] == 0)
		{
			Materials[matindex].name[i] = NULL;
			break;
		}
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::DiffuseColorChunkProcessor(long length, long findex, int matindex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		// Determine the format of the color and load it
		switch (h.id)
		{
			case COLOR_RGB	:
				// A rgb float color chunk
				FloatColorChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			case COLOR_TRU	:
				// A rgb int color chunk
				IntColorChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			case COLOR_RGBG	:
				// A rgb gamma corrected float color chunk
				FloatColorChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			case COLOR_TRUG	:
				// A rgb gamma corrected int color chunk
				IntColorChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::FloatColorChunkProcessor(long length, long findex, int matindex)
{
	float r;
	float g;
	float b;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	fread(&r,sizeof(r),1,bin3ds);
	fread(&g,sizeof(g),1,bin3ds);
	fread(&b,sizeof(b),1,bin3ds);

	Materials[matindex].color.r = (unsigned char)(r*255.0f);
	Materials[matindex].color.g = (unsigned char)(r*255.0f);
	Materials[matindex].color.b = (unsigned char)(r*255.0f);
	Materials[matindex].color.a = 255;

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::IntColorChunkProcessor(long length, long findex, int matindex)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	fread(&r,sizeof(r),1,bin3ds);
	fread(&g,sizeof(g),1,bin3ds);
	fread(&b,sizeof(b),1,bin3ds);

	Materials[matindex].color.r = r;
	Materials[matindex].color.g = g;
	Materials[matindex].color.b = b;
	Materials[matindex].color.a = 255;

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::TextureMapChunkProcessor(long length, long findex, int matindex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case MAT_MAPNAME:
				// Read the name of texture in the Diffuse Color map
				MapNameChunkProcessor(h.len, ftell(bin3ds), matindex);
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::MapNameChunkProcessor(long length, long findex, int matindex)
{
	char name[80];

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Read the name of the texture
	for (int i = 0; i < 80; i++)
	{
		name[i] = fgetc(bin3ds);
		if (name[i] == 0)
		{
			name[i] = NULL;
			break;
		}
	}

	// Load the name and indicate that the material has a texture
	char fullname[80];
	sprintf(fullname, "%s%s", path, name);
	Materials[matindex].tex.Load(fullname);
	Materials[matindex].textured = true;

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::ObjectChunkProcessor(long length, long findex, int objindex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Load the object's name
	for (int i = 0; i < 80; i++)
	{
		Objects[objindex].name[i] = fgetc(bin3ds);
		if (Objects[objindex].name[i] == 0)
		{
			Objects[objindex].name[i] = NULL;
			break;
		}
	}

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case TRIG_MESH	:
				// Process the triangles of the object
				TriangularMeshChunkProcessor(h.len, ftell(bin3ds), objindex);
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::TriangularMeshChunkProcessor(long length, long findex, int objindex)
{
	ChunkHeader h;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case VERT_LIST	:
				// Load the vertices of the onject
				VertexListChunkProcessor(h.len, ftell(bin3ds), objindex);
				break;
			case LOCAL_COORDS	:
				//LocalCoordinatesChunkProcessor(h.len, ftell(bin3ds));
				break;
			case TEX_VERTS	:
				// Load the texture coordinates for the vertices
				TexCoordsChunkProcessor(h.len, ftell(bin3ds), objindex);
				Objects[objindex].textured = true;
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// After we have loaded the vertices we can load the faces
	fseek(bin3ds, findex, SEEK_SET);

	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case FACE_DESC	:
				// Load the faces of the object
				FacesDescriptionChunkProcessor(h.len, ftell(bin3ds), objindex);
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::VertexListChunkProcessor(long length, long findex, int objindex)
{
	unsigned short numVerts;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Read the number of vertices of the object
	fread(&numVerts,sizeof(numVerts),1,bin3ds);

	// Allocate arrays for the vertices and normals
	Objects[objindex].Vertexes = new GLfloat[numVerts * 3];
	Objects[objindex].Normals = new GLfloat[numVerts * 3];

	// Assign the number of vertices for future use
	Objects[objindex].numVerts = numVerts;

	// Zero out the normals array
	for (int j = 0; j < numVerts * 3; j++)
		Objects[objindex].Normals[j] = 0.0f;

	// Read the vertices, switching the y and z coordinates and changing the sign of the z coordinate
	for (int i = 0; i < numVerts * 3; i+=3)
	{
		fread(&Objects[objindex].Vertexes[i],sizeof(GLfloat),1,bin3ds);
		fread(&Objects[objindex].Vertexes[i+2],sizeof(GLfloat),1,bin3ds);
		fread(&Objects[objindex].Vertexes[i+1],sizeof(GLfloat),1,bin3ds);

		// Change the sign of the z coordinate
		Objects[objindex].Vertexes[i+2] = -Objects[objindex].Vertexes[i+2];
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::TexCoordsChunkProcessor(long length, long findex, int objindex)
{
	// The number of texture coordinates
	unsigned short numCoords;

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Read the number of coordinates
	fread(&numCoords,sizeof(numCoords),1,bin3ds);

	// Allocate an array to hold the texture coordinates
	Objects[objindex].TexCoords = new GLfloat[numCoords * 2];

	// Set the number of texture coords
	Objects[objindex].numTexCoords = numCoords;

	// Read teh texture coordiantes into the array
	for (int i = 0; i < numCoords * 2; i+=2)
	{
		fread(&Objects[objindex].TexCoords[i],sizeof(GLfloat),1,bin3ds);
		fread(&Objects[objindex].TexCoords[i+1],sizeof(GLfloat),1,bin3ds);
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::FacesDescriptionChunkProcessor(long length, long findex, int objindex)
{
	ChunkHeader h;
	unsigned short numFaces;	// The number of faces in the object
	unsigned short vertA;		// The first vertex of the face
	unsigned short vertB;		// The second vertex of the face
	unsigned short vertC;		// The third vertex of the face
	unsigned short flags;		// The winding order flags
	long subs;					// Holds our place in the file
	int numMatFaces = 0;		// The number of different materials

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Read the number of faces
	fread(&numFaces,sizeof(numFaces),1,bin3ds);

	// Allocate an array to hold the faces
	Objects[objindex].Faces = new GLushort[numFaces * 3];
	// Store the number of faces
	Objects[objindex].numFaces = numFaces * 3;

	// Read the faces into the array
	for (int i = 0; i < numFaces * 3; i+=3)
	{
		// Read the vertices of the face
		fread(&vertA,sizeof(vertA),1,bin3ds);
		fread(&vertB,sizeof(vertB),1,bin3ds);
		fread(&vertC,sizeof(vertC),1,bin3ds);
		fread(&flags,sizeof(flags),1,bin3ds);

		// Place them in the array
		Objects[objindex].Faces[i]   = vertA;
		Objects[objindex].Faces[i+1] = vertB;
		Objects[objindex].Faces[i+2] = vertC;

		// Calculate the face's normal
		Vector n;
		Vertex v1;
		Vertex v2;
		Vertex v3;

		v1.x = Objects[objindex].Vertexes[vertA*3];
		v1.y = Objects[objindex].Vertexes[vertA*3+1];
		v1.z = Objects[objindex].Vertexes[vertA*3+2];
		v2.x = Objects[objindex].Vertexes[vertB*3];
		v2.y = Objects[objindex].Vertexes[vertB*3+1];
		v2.z = Objects[objindex].Vertexes[vertB*3+2];
		v3.x = Objects[objindex].Vertexes[vertC*3];
		v3.y = Objects[objindex].Vertexes[vertC*3+1];
		v3.z = Objects[objindex].Vertexes[vertC*3+2];

		// calculate the normal
		float u[3], v[3];

		// V2 - V3;
		u[0] = v2.x - v3.x;
		u[1] = v2.y - v3.y;
		u[2] = v2.z - v3.z;

		// V2 - V1;
		v[0] = v2.x - v1.x;
		v[1] = v2.y - v1.y;
		v[2] = v2.z - v1.z;

		n.x = (u[1]*v[2] - u[2]*v[1]);
		n.y = (u[2]*v[0] - u[0]*v[2]);
		n.z = (u[0]*v[1] - u[1]*v[0]);

		// Add this normal to its verts' normals
		Objects[objindex].Normals[vertA*3]   += n.x;
		Objects[objindex].Normals[vertA*3+1] += n.y;
		Objects[objindex].Normals[vertA*3+2] += n.z;
		Objects[objindex].Normals[vertB*3]   += n.x;
		Objects[objindex].Normals[vertB*3+1] += n.y;
		Objects[objindex].Normals[vertB*3+2] += n.z;
		Objects[objindex].Normals[vertC*3]   += n.x;
		Objects[objindex].Normals[vertC*3+1] += n.y;
		Objects[objindex].Normals[vertC*3+2] += n.z;
	}

	// Store our current file position
	subs = ftell(bin3ds);

	// Check to see how many materials the faces are split into
	while (ftell(bin3ds) < (findex + length - 6))
	{
		fread(&h.id,sizeof(h.id),1,bin3ds);
		fread(&h.len,sizeof(h.len),1,bin3ds);

		switch (h.id)
		{
			case FACE_MAT	:
				//FacesMaterialsListChunkProcessor(h.len, ftell(bin3ds), objindex);
				numMatFaces++;
				break;
			default			:
				break;
		}

		fseek(bin3ds, (h.len - 6), SEEK_CUR);
	}

	// Split the faces up according to their materials
	if (numMatFaces > 0)
	{
		// Allocate an array to hold the lists of faces divided by material
		Objects[objindex].MatFaces = new MaterialFaces[numMatFaces];
		// Store the number of material faces
		Objects[objindex].numMatFaces = numMatFaces;

		fseek(bin3ds, subs, SEEK_SET);

		int j = 0;

		// Split the faces up
		while (ftell(bin3ds) < (findex + length - 6))
		{
			fread(&h.id,sizeof(h.id),1,bin3ds);
			fread(&h.len,sizeof(h.len),1,bin3ds);

			switch (h.id)
			{
				case FACE_MAT	:
					// Process the faces and split them up
					FacesMaterialsListChunkProcessor(h.len, ftell(bin3ds), objindex, j);
					j++;
					break;
				default			:
					break;
			}

			fseek(bin3ds, (h.len - 6), SEEK_CUR);
		}
	}

	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}

void Model_3DS::FacesMaterialsListChunkProcessor(long length, long findex, int objindex, int subfacesindex)
{
	char name[80];				// The material's name
	unsigned short numEntries;	// The number of faces associated with this material
	unsigned short Face;		// Holds the faces as they are read
	int material;				// An index to the Materials array for this material

	// move the file pointer to the beginning of the main
	// chunk's data findex + the size of the header
	fseek(bin3ds, findex, SEEK_SET);

	// Read the material's name
	for (int i = 0; i < 80; i++)
	{
		name[i] = fgetc(bin3ds);
		if (name[i] == 0)
		{
			name[i] = NULL;
			break;
		}
	}

	// Faind the material's index in the Materials array
	for (material = 0; material < numMaterials; material++)
	{
		if (strcmp(name, Materials[material].name) == 0)
			break;
	}

	// Store this value for later so that we can find the material
	Objects[objindex].MatFaces[subfacesindex].MatIndex = material;

	// Read the number of faces associated with this material
	fread(&numEntries,sizeof(numEntries),1,bin3ds);

	// Allocate an array to hold the list of faces associated with this material
	Objects[objindex].MatFaces[subfacesindex].subFaces = new GLushort[numEntries * 3];
	// Store this number for later use
	Objects[objindex].MatFaces[subfacesindex].numSubFaces = numEntries * 3;

	// Read the faces into the array
	for (i = 0; i < numEntries * 3; i+=3)
	{
		// read the face
		fread(&Face,sizeof(Face),1,bin3ds);
		// Add the face's vertices to the list
		Objects[objindex].MatFaces[subfacesindex].subFaces[i] = Objects[objindex].Faces[Face * 3];
		Objects[objindex].MatFaces[subfacesindex].subFaces[i+1] = Objects[objindex].Faces[Face * 3 + 1];
		Objects[objindex].MatFaces[subfacesindex].subFaces[i+2] = Objects[objindex].Faces[Face * 3 + 2];
	}
	
	// move the file pointer back to where we got it so
	// that the ProcessChunk() which we interrupted will read
	// from the right place
	fseek(bin3ds, findex, SEEK_SET);
}*/
