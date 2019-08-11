unsigned long sizeX, sizeY;
unsigned char heightmap[1024][1024];
//unsigned char **heightmap;	//name of heightmap array

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int loadHeightMap(char *filename, Image *image)
{
	int X = 0, Y = 0;
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    unsigned char temp;                          // temporary color storage for bgr-rgb conversion.

    if ((file = fopen(filename, "rb"))==NULL)
    {    // make sure the file is there. --wont be required once working
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    fseek(file, 18, SEEK_CUR);//look through file header to width/height
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1)
    {    // read the width
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1)
    {    // read the height 
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    size = image->sizeX * image->sizeY * 3;    // calculate the size (3 bytes/pixel)
    if ((fread(&planes, 2, 1, file)) != 1)
    {    // read the planes
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1)
    {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }
    if ((i = fread(&bpp, 2, 1, file)) != 1)
    {    // read the bpp
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24)
    {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
    fseek(file, 24, SEEK_CUR);//seek past the rest of the bitmap header.
    // read the data. 
    image->data = (unsigned char *) malloc(size*3);
//    image->data = (unsigned char *) malloc(image->sizeX * image->sizeY *3);
    if (image->data == NULL)
    {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }
    if ((i = fread(image->data, size, 1, file)) != 1)
    {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }
    for (i=0;i<size;i+=3)
    { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
//heightmap start
	//rgb to greyscale
	int x, y;
  /*  allocate storage for an array of pointers */
//  heightmap = malloc(image->sizeX * (sizeof(unsigned char *)*3));
  /* for each pointer, allocate storage for an array of ints */
//  for (i = 0; i < image->sizeX; i++) {
//    heightmap[i] = malloc(image->sizeY * (sizeof(char)*3));
//  }

//	printf("%i ", image->data[1]);

	for (x = 0; x < (image->sizeY); x++) //rows (?!)
	{
	  for (y = 0; y < (image->sizeX); y++) 
	  {
		heightmap[x][y] = image->data[((x*image->sizeX)+y)*3];
/*		if(y==image->sizeY-1)
		{
			printf("!!!%x %y\n", x, y);
		}
		printf("|%i", heightmap[x][y]);
*/
	  }//allocate storage of an array of ints at each pointer (y-dimention)
	}
//	printf("x %i & y %i\n", x, y);
	sizeX = image->sizeX;
	sizeY = image->sizeY;
	free(image);
    return 1;
} 
