/******************************************************************/
/* Code written by : Aniket Gade UTA ID:1001505046	          */
/* This code performs blob coloring for segemtation	          */
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
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];

unsigned char proc_img[DIM][DIM];
{
	int i;
	int j;
	int p;
	int k;
	int flag = 0;
	int a = 1;
	int intense[15]; // Holds intensity of the new segments
	int label[DIM][DIM]; // Label matrix of image
	int lbl = 1;//Initial Label
	int temp = 0;

	label[0][0] = 1; // set 1st label as 1
	intense[0] = image[0][0];// start form the 1st pixel
	for(i = 0; i<DIM; i++)//Iterate one on the entire image
	{
		for(j = 0; j<DIM-1; j++)
		{	
			if(image[i][j] - image[i][j+1]<10 || image[i][j] - image[i][j+1]<-10)//Check x-neighbours intensity
			{
				label[i][j+1] = lbl;//set label value
			}
			else
			{	
				for(k = 0; k<a; k++)//If intensity of neighbour changes, 
				{
					if(image[i][j+1] - intense[k]<10 || image[i][j+1] - intense[k]<-10){//compare the intensity of previous segments
						label[i][j+1] = k+1;//if match, set label as the same one of the segment with whome, the intensity matched
						flag = 1;
					}
				}
			if(flag == 0){//If no intensities match
				lbl++;
				label[i][j+1] = lbl;//Set new label
				intense[a] = image[i][j+1];// Add it to intensities list
				a++;
				}
			flag = 0;
			}
		}
		if(i!=DIM)
		{
			if(image[i][0] - image[i+1][0]<10 || image[i][0] - image[i+1][0]<-10) //Check y-neighbour intensity
			{
				label[i+1][0] = label[i][0];//set label value
			}
			else //If intensity of neighbour changes, 
			{
				for(k = 0; k<a; k++)
				{
					if(image[i+1][0] - intense[k]<10 || image[i+1][0] - intense[k]<-10){//compare the intensity of previous segments
						label[i+1][0] = k+1;//if match, set label as the same one of the segment with whome, the intensity matched
						flag = 1;
						break;
					}
				}
			if(flag == 0){//If no intensities match
				lbl++;
				label[i+1][j] = lbl;//Set new label
				intense[a] = image[i+1][0];// Add it to intensities list
				a++;
				}
			flag = 0;			
			}
		}
	}

//Print the intensities.
	for(i = 0; i<DIM; i++)
	{
		for(j = 0; j<DIM; j++)
		{	
			if(label[i][j] == 1)
				proc_img[i][j] = intense[0];
			else if(label[i][j] == 2)
				proc_img[i][j] = intense[1];
			else if(label[i][j] == 3)
				proc_img[i][j] = intense[2];
			else if(label[i][j] == 4)
				proc_img[i][j] = intense[3];
			else if(label[i][j] == 5)
				proc_img[i][j] = intense[4];
			else if(label[i][j] == 6)
				proc_img[i][j] = intense[5];
			else if(label[i][j] == 7)
				proc_img[i][j] = intense[6];
			else if(label[i][j] == 8)
				proc_img[i][j] = intense[7];
			else if(label[i][j] == 9)
				proc_img[i][j] = intense[8];
			else if(label[i][j] == 10)
				proc_img[i][j] = intense[9];
		}
	}	


printf("\n Total Number of Regions :: %d", a);
for(i = 0; i<a; i++)
	{

		printf("\nIntensity if region %d is %d",i+1,intense[i]);
	}
}


