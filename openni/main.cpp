#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    VideoCapture capture(VideoCaptureAPIs::CAP_OPENNI+0); // or CAP_OPENNI
    Mat depthMap;
    Mat bgrImage;
    for(;;)
    {
        capture.grab();
        capture.retrieve( depthMap, CAP_OPENNI_POINT_CLOUD_MAP);
        capture.retrieve( bgrImage, CAP_OPENNI_BGR_IMAGE);
        imshow("dep",depthMap);
        imshow("rgb",bgrImage);
        waitKey( 3 );
    }
}
