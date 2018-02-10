/******************************************************************/
/* Code written by : Aniket Gade UTA ID:1001505046	          */
/* This code detects Horizontal Edges from greyscale images       */
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
	int x,y,i,j;		//Iterators for 'for loops'
	int width = size[0];	//Width of Original Image
	int height = size[1];	//Height of Original Image
	int hyp = 0;		//Magnitude of convolution

	int deriv_x_mask[3][3] = {{-1,0,1},{-1,0,1},{-1,0,1}};	//Prewitts Template
	int grad_x[size[0]][size[1]];  //Holds sum of convolution

	for(x = 0; x<height; x++)
	{
		for(y = 0; y<width; y++)
		{
			//Checks if on boundary of image
			if(x==0 || x==width-1 || y==0 || y==height-1)
			{	
				grad_x[y][x] = 0;
			}
			else
			{	
				int x_sum = 0;		 
				for(i=-1; i<2; i++){
					for(j=-1; j<2; j++){
						x_sum+=image[y+i][x+j] * deriv_x_mask[i+1][j+1] / 3; //Convolution formula (Divide by 3 to keep values in range)
					}
				}
				grad_x[y][x] = x_sum;
				
				hyp = hypot(grad_x[y][x], 0); //Calculate the magnitude
				if(hyp>255)
					proc_img[y][x] = 255; //Makes sure that values do not exceed 255
				else
					proc_img[y][x] = hyp;
			}
		}
	}


}

