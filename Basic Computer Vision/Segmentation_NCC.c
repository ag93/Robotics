/******************************************************************/
/* Code written by : Aniket Gade UTA ID:1001505046	          */
/* This code detects Segments(Template) In a given input image    */
/******************************************************************/
#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#define DIM 512

/******************************************************************/
/* This structure contains the coordinates of a box drawn with    */
/* the left mouse button on the image window.                     */
/* roi.x , roi.y  - left upper corner's coordinates               */
/* roi.width , roi.height - width and height of the box           */
/******************************************************************/
extern XRectangle roi;


/******************************************************************/
/* Main processing routine. This is called upon pressing the      */
/* Process button of the interface.                               */
/* image  - the original greyscale image                          */
/* size   - the actual size of the image			  */
/*	    0 - width and 1 = height                              */
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];

unsigned char proc_img[DIM][DIM];
{

	int x,y,i,j;		//Iterators for 'for loop'
	int width = size[0];	//Width on image
	int height = size[1];	//Height of image
	int hyp = 0;		//Holds magnitude
        int sum = 0;		//used to calculate mean
	int avg = 0;		//holds mean
	long temp1 = 0;	
	long temp = 0;
	long variance_img = 0;	//holds variance of input image
	//int sd_img = 0;	
	long variance_temp = 0;	//holds variance of template
	//int sd_temp = 0;	
	int b = 0;
	int a = 0;
	int template[roi.width][roi.height]; //Holds the template
	int grad[size[0]][size[1]];	//Holds the sum
//-------------------------------------------------------------------------------------------------------------------------

for(x = 0; x<width; x++)
	{
		for(y = 0; y<height; y++)
		{
			sum = sum+image[x][y]; //Calculate the total inorder to get mean of source image
		}
	}


avg = sum/(size[0]*size[1]);	//calculate mean


for(x = 0; x<height; x++)
	{
		for(y = 0; y<width; y++)
		{
			image[x][y] = image[x][y]-avg;	//subtract mean from the source image
			temp = temp + pow(image[x][y],2); //store the sum of squares of the difference of image and mean (for calculating variance)
		}
	}

variance_img = temp/(size[0]*size[1]);	//calculate variance
//sd_img = sqrt(variance_img);

for(x = 0; x<(roi.width); x++)
	{
		b = 0;
		for(y = 0; y<(roi.height); y++)
		{
			template[x][y] = image[roi.x+a][roi.y+b]; //store the template (Mean already subtracted)
			temp1 = temp1 + pow(template[x][y],2);	//store the sum of squares of the difference of image and mean (for calculating variance)
			b++;
		}
		a++;
	}

variance_temp = temp1/(roi.height*roi.width); //calculate variance
//sd_temp = sqrt(variance_temp);

//--------------------------------------------------------------------------------------------------------------------------
	for(x = 0; x<width-roi.width; x++) //Exclude boundary
	{
		for(y = 0; y<height-roi.height; y++)
		{
			{	
				int sum1 = 0;	 
				for(i=0; i<roi.width-1; i++){
					for(j=0; j<roi.height-1; j++){
						sum1+=image[x+i][y+j] * template[i][j]; //Convolution
					}
				}
				grad[x][y] = sum1;				
				hyp = hypot(grad[x][y], 0);
				proc_img[x][y] = hyp/sqrt((variance_img*variance_temp)); //Formula for normalized cross convolution
			}
		}
	}
}

