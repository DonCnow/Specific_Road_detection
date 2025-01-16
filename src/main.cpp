#include <opencv2/opencv.hpp>
#include "road_detection_sobel.h"

int main(int argc, char** argv) {

    if(argc <2){
        std::cerr <<"Usage:./road_detection[0|1]"<<std::endl;
        return -1;
    }

    std::string videoPath;
    cv::Mat(*processFrame)(const cv::Mat&);

    if(std::string(argv[1]) =="0"){
        videoPath = "../data/test_video/challenge0.mp4";
        processFrame = detectRoadVideo0;
        }else if(std::string(argv[1]) =="1"){
            videoPath = "../data/test_video/challenge1.mp4";
            processFrame = detectRoadVideo1;
        }else{
            std::cerr<<"Invalid argument. Use 0 or 1."<<std::endl;
            return -1;
        }

    cv::VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open video stream!" << std::endl;
        return -1;
    }

    //size of window
    const int targetWidth = 640;
    const int targetHeight = 360;

    cv::Mat frame, resizedFrame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cv::Mat processedFrame = processFrame(frame);

        cv::resize(processedFrame, resizedFrame, cv::Size(targetWidth, targetHeight));

        //cv::imshow("Original Video", frame);
        cv::imshow("Processed Video", resizedFrame);

        char key = (char)cv::waitKey(30);
        if (key == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
