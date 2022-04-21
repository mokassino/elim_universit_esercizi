#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

using namespace cv;
using namespace std;

//copyMakeBorder ma rifatta a mano
Mat makeBorder(Mat& M, int extra){

    CV_Assert(M.depth() == CV_8U);

    int i,j,c;

    int nRows = M.rows;
    int nCols = M.cols;
    int nChan = M.channels();
    Mat base = cv::Mat(nRows+extra, nCols+extra, CV_8U, cv::Scalar(255,255,255));


    for ( i=extra; i<nRows; i++) {
        for ( j=extra; j<nCols; j++) {
            for ( c = 0; c < nChan; c++){
                base.at<uchar>(i,j,c) = M.at<uchar>(i,j,c);
            }
        }
    }

    return base;
}
