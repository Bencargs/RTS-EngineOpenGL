#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "3DSFile.h"

#define MAIN3DS				0x4D4D
 #define MAIN_VERS			0x0002
 #define EDIT3DS			0x3D3D
  #define MESH_VERS			0x3D3E
  #define OBJECT			0x4000
   #define TRIG_MESH		0x4100
    #define VERT_LIST		0x4110
    #define FACE_DESC		0x4120
     #define FACE_MAT		0x4130
    #define TEX_VERTS		0x4140
     #define SMOOTH_GROUP	0x4150
    #define LOCAL_COORDS	0x4160
  #define MATERIAL			0xAFFF
   #define MAT_NAME			0xA000
   #define MAT_AMBIENT		0xA010
   #define MAT_DIFFUSE		0xA020
   #define MAT_SPECULAR		0xA030
   #define SHINY_PERC		0xA040
   #define SHINY_STR_PERC	0xA041
   #define TRANS_PERC		0xA050
   #define TRANS_FOFF_PERC	0xA052
   #define REF_BLUR_PERC	0xA053
   #define RENDER_TYPE		0xA100
   #define SELF_ILLUM		0xA084
   #define MAT_SELF_ILPCT	0xA08A
   #define WIRE_THICKNESS	0xA087
   #define MAT_TEXMAP		0xA200
    #define MAT_MAPNAME		0xA300
  #define ONE_UNIT			0x0100
 #define KEYF3DS			0xB000
  #define FRAMES			0xB008
  #define MESH_INFO			0xB002
   #define HIER_POS			0xB030
   #define HIER_FATHER		0xB010
   #define PIVOT_PT			0xB013
   #define TRACK00			0xB020
   #define TRACK01			0xB021
   #define TRACK02			0xB022
#define	COLOR_RGB			0x0010
#define COLOR_TRU			0x0011
#define COLOR_TRUG			0x0012
#define COLOR_RGBG			0x0013
#define PERC_INT			0x0030
#define PERC_FLOAT			0x0031

void model3DS()
{
	// Initialization

	// Don't show the normals by default
//	shownormals = false;

	// The model is lit by default
//	lit = true;

	// The model is visible by default
//	visible = true;

	// Set up the default position
//	pos.x = 0.0f;
//	pos.y = 0.0f;
//	pos.z = 0.0f;
	// Set up the default rotation
//	rot.x = 0.0f;
//	rot.y = 0.0f;
//	rot.z = 0.0f;

	// Set up the path
//	path = new char[80];
	sprintf(path, "");

	// Zero out our counters for MFC
	numObjects = 0;
	numMaterials = 0;

	// Set the scale to one
	scale = 1.0f;
}
