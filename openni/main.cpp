#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    VideoCapture capture(VideoCaptureAPIs::CAP_OPENNI+0); // or CAP_OPENNI
    Mat depth;
    Mat bgrImage;
    viz::Viz3d window("window");
    //显示坐标系
    window.showWidget("Coordinate", viz::WCoordinateSystem());

    while (!window.wasStopped())
    {
        capture.grab();
        //capture.retrieve( depthMap, CAP_OPENNI_POINT_CLOUD_MAP);
        capture.retrieve( depth, CAP_OPENNI_DISPARITY_MAP);
        capture.retrieve( bgrImage, CAP_OPENNI_BGR_IMAGE);


        int height=depth.rows;
        int width = depth.cols;
        //创建一个储存point cloud的图片
        Mat point_cloud = Mat::zeros(height, width, CV_32FC3);
        //point cloud 赋值，其中 fx,fy,cx,cy 为Kinect2 的内参
        double fx = 368.096588, fy = 368.096588, cx = 261.696594, cy = 202.522202;
        for(int row=0; row<depth.rows;row++)
            for (int col = 0; col < depth.cols; col++)
            {
                point_cloud.at<Vec3f>(row, col)[2] = depth.at<unsigned short>(row,col);
                point_cloud.at<Vec3f>(row, col)[0] = depth.at<unsigned short>(row, col)*(col - cx) / fx;
                point_cloud.at<Vec3f>(row, col)[1] = depth.at<unsigned short>(row, col)*(row - cy) / fy;
            }
        cv::viz::WCloud cloud(point_cloud);
        window.showWidget("cloud",cloud);
        imshow("dep",depth);
        imshow("rgb",bgrImage);
        waitKey( 3 );
        window.spinOnce(1, true);
    }


}
