#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

using namespace cv;
using namespace std;

int calc_media(Mat &p, int row, int col, int chan, int kernel){
    vector<int> vec;
    int media = 0;

    vec.push_back( (int) p.at<uchar>(row-1,col,chan) );
    vec.push_back( (int) p.at<uchar>(row-1,col-1, chan) );
    vec.push_back( (int) p.at<uchar>(row-1,col+1, chan) );

    vec.push_back( (int) p.at<uchar>(row+1,col-1,chan) );
    vec.push_back( (int) p.at<uchar>(row+1,col+1, chan) );
    vec.push_back( (int) p.at<uchar>(row+1,col, chan) );

    vec.push_back( (int) p.at<uchar>(row,col-1,chan) );
    vec.push_back( (int) p.at<uchar>(row,col, chan) );
    vec.push_back( (int) p.at<uchar>(row,col+1, chan) );

    
    //somma tutti gli elementi del vettore tramite Iterator
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        media += *it;
    }

    media = media/kernel;

    //Controlla se la media è > 255, mettila a 255
    if (media > 255){
        media = 255;
    }
    
    return media;
    
}

Mat padding(Mat &p, int kernel){
    int nRows = p.rows;
    int nCols = p.cols;
    int nChan = p.channels();

    int i,j,c;

     for (i = 1; i < nRows; ++i){
        for (j = 1; j < nCols; ++j){
            for (c = 0; c < nChan; c++){
                
                int media = calc_media(p, i, j , c, kernel*kernel);
                p.at<uchar>(i,j,c) = (uchar) media;
            }
           
        }
    }

}

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
