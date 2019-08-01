#include "opencv2/opencv.hpp"
#include "iostream"
using namespace std;
using namespace cv;

int main()
{
    VideoCapture camera1(1);
    camera1.set(CAP_PROP_FRAME_WIDTH, 480);
    camera1.set(CAP_PROP_FRAME_HEIGHT, 340);
    VideoCapture camera0(0);
    camera0.set(CAP_PROP_FRAME_WIDTH, 480);
    camera0.set(CAP_PROP_FRAME_HEIGHT, 340);

    if (!(camera1.isOpened() && camera0.isOpened())) { cout << "打开摄像头或读取失败！" << endl; return -1; }

    Mat frame1,frame0;
    vector<Mat> imgs;
    Stitcher::Mode mode = Stitcher::SCANS;
    namedWindow("Left");
    namedWindow("Right");

    while (1)
    {
        if (!(camera1.read(frame1) && camera0.read(frame0))) break;
        resize(frame0,frame0,Size(frame0.cols*1.5,frame0.rows*1.5));
        resize(frame1,frame1,Size(frame1.cols*1.5,frame1.rows*1.5));
        imgs.push_back(frame0);
        imgs.push_back(frame1);
        Mat pano;
        Ptr<Stitcher> stitcher = Stitcher::create(mode);
        Stitcher::Status status = stitcher->stitch(imgs, pano);
        if (status != Stitcher::OK)
        {
            cout << "Can't stitch images, error code=" << int(status) << endl;
            system("pause");
            return -1;
        }
        imshow("Left", frame1);
        imshow("Right", frame0);
        imshow("result",pano);
        waitKey(1);
    }

    return 0;
}
