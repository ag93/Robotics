#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415927
#endif

void multiply(double mat1[4][4], double mat2[4][4], double res[4][4])
{
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < 4; k++)
                res[i][j] += mat1[i][k]*mat2[k][j];
        }
    }
}

fwd_kin(theta, x)
double *theta;
double x[3];
{
    double res[4][4]={{0,0,0,0},
		      {0,0,0,0},
		      {0,0,0,0},
		      {0,0,0,0}};
   double res2[4][4]={{0,0,0,0},
		      {0,0,0,0},
		      {0,0,0,0},
		      {0,0,0,0}};
    int i, j;

    double mat1[4][4]={{1, 0, 0, 0.15},
                       {0, 1, 0, 0.05},
                       {0, 0, 1, 0.05},
                       {0, 0, 0, 1}};
 
    double mat2[4][4]={{cos(theta[3]), sin(theta[3]), 0, 0},
                       {0, 1, 0, 0},
                       {-sin(theta[3]), 0,cos(theta[3]), 0},
                       {0, 0, 0, 1}};
    multiply(mat2, mat1, res);    

    double mat3[4][4]={{1, 0, 0, 0.25},
                       {0, 1, 0, 0.05},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}};

    multiply(mat3, res, res2);
    double mat4[4][4]={{cos(theta[2]), 0, sin(theta[2]), 0},
                       {0, 1, 0, 0},
                       {-sin(theta[2]), 0, cos(theta[2]), 0},
                       {0, 0, 0, 1}};
    multiply(mat4, res2, res);
    double mat5[4][4]={{1, 0, 0, 0.25},
                       {0, 1, 0, 0},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}};
    multiply(mat5, res, res2);
    double mat6[4][4]={{cos(theta[1]), 0, sin(theta[1]), 0},
                       {0, 1, 0, 0},
                       {-sin(theta[1]), 0, cos(theta[1]), 0},
                       {0, 0, 0, 1}};
     multiply(mat6, res2, res);
    double mat7[4][4]={{cos(theta[0]), -sin(theta[0]), 0, 0},
                       {sin(theta[0]), cos(theta[0]), 0, 0},
                       {0, 0, 1, 0.25},
                       {0, 0, 0, 1}};
    multiply(mat7, res, res2);

	x[0]=res2[0][3];
	x[1]=res2[1][3];
	x[2]=res2[2][3];

}


inv_kin(x, theta)
double *x;
double theta[6];
{

}








