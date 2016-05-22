//
//  main.cpp
//  Circle_Detection_PH
//
//  Created by Ives on 5/22/16.
//  Copyright © 2016 bochengw.twbbs.org. All rights reserved.
//

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    
    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    
    dst = Scalar::all(0);
    
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

void printPixels(Mat img) {
    for(int i = 0; i < img.rows; i++) {
        for(int j = 0; j < img.cols; j++)  {
            Scalar intensity = img.at<unsigned char>(i,j);
            std::cout << intensity[0] << " ";
        }
    }
}


int main( int argc, char** argv )
{
    src = imread("coin.png");
    
    if(!src.data){
        return -1;
    }
    
    //printPixels(src);
    
    dst.create( src.size(), src.type() );
    
    cvtColor( src, src_gray, CV_BGR2GRAY );
    
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    
    CannyThreshold(100, 0);
    
    printPixels(dst);
    
    waitKey(0);
    
    return 0;
}