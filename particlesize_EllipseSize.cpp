#include "mex.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{   
      
    #define B_OUT plhs[0]
    #define A_IN prhs[0]

    double *B;
    int m,n;
    mxChar *ICEPIC;
    

    B_OUT=mxCreateDoubleScalar(3);
    B=mxGetPr(B_OUT); 
    m=mxGetM(A_IN);
    n=mxGetN(A_IN);    
    ICEPIC=mxGetChars(A_IN);
    
    int i,j,k=0;
    Point2f center;
    vector<Point> points;
    for( i = 0; i < n; i++ )
    {
        for (j=0; j<m; j++)
        {
            //cout<< ICEPIC[i*m+j] << ", ";
            if(ICEPIC[i*m+j]==48)
            {
                Point pt;
                pt.x = j;
                pt.y = i;
                points.push_back(pt);
            }
        }
        //cout<<"\n"<<endl;
        
    }
    //cout<< k << endl;

    if (points.size()==0)
    {
        //cout << "No Illuminated Doide!\n" << endl;
        *B = 0;
        return;
    }
    
    float radius;
    minEnclosingCircle(Mat(points), center, radius);
    
    //cout << "Center: " << center << " Radius: " << radius <<endl;

    *B=radius*2;
    
    return;

   
}
