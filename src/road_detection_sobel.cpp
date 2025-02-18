#include "road_detection_sobel.h"
#include <vector>
#include <algorithm>

// define a global variable to store the fitting result of previous frame
static cv::Vec4f prevRightLine(0, 0, 0, 0);

//main function
cv::Mat detectRoadVideo0(const cv::Mat& inputImage) {

    //define all variable
    cv::Mat hsvImage, yellowMask, whiteMask, combinedMask, blurred, edges, roiMask, output;

    //convert video into hsv
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);

    //segement of yellow line
    cv::inRange(hsvImage, cv::Scalar(15, 60, 190), cv::Scalar(60, 255, 255), yellowMask);

    //segement of white line
    cv::inRange(hsvImage, cv::Scalar(0, 0, 180), cv::Scalar(180, 25, 255), whiteMask);

    //combine two lines
    cv::bitwise_or(yellowMask, whiteMask, combinedMask);

    //apply gaussianblur to denoise
    cv::GaussianBlur(combinedMask, blurred, cv::Size(9, 9), 0);

    //use canny to detect the edges
    cv::Canny(blurred, edges, 30, 100);

    //apply roi in order to remove the noise
    roiMask = cv::Mat::zeros(edges.size(), edges.type());
    cv::Point point[1][4] = {
        {cv::Point(edges.cols * 0.1, edges.rows),
         cv::Point(edges.cols * 0.95, edges.rows),
         cv::Point(edges.cols * 0.55, edges.rows * 0.6),
         cv::Point(edges.cols * 0.5, edges.rows * 0.6)}};
    const cv::Point* ppt[1] = {point[0]};
    int npt[] = {4};
    cv::fillPoly(roiMask, ppt, npt, 1, cv::Scalar(255));
    cv::bitwise_and(edges, roiMask, edges);

    //apply hough to detecte straight line
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 10, 20, 10);

    //seperate the edges to two lines
    std::vector<cv::Point> leftPoints, rightPoints;

    int midX = edges.cols / 2;

    for (const auto& line : lines) {
        int x1 = line[0];
        int x2 = line[2];

        // segement of left line
        if (x1 < midX && x2 < midX) {
            leftPoints.push_back(cv::Point(line[0], line[1]));
            leftPoints.push_back(cv::Point(line[2], line[3]));
        }
        // segement of right line
        else if (x1 > midX && x2 > midX) {
            rightPoints.push_back(cv::Point(line[0], line[1]));
            rightPoints.push_back(cv::Point(line[2], line[3]));
        }
    }

    // use line fitting to complete the right line and left line
    if (!leftPoints.empty()) {
        cv::Vec4f leftFittedLine;
        cv::fitLine(leftPoints, leftFittedLine, cv::DIST_L2, 0, 0.01, 0.01);

        // Calculate the top and bottom coordinates of the left line
        int y1 = edges.rows;  // bottom y
        int y2 = edges.rows * 0.65;  // top x

        int x1 = leftFittedLine[2] + (y1 - leftFittedLine[3]) * (leftFittedLine[0] / leftFittedLine[1]);
        int x2 = leftFittedLine[2] + (y2 - leftFittedLine[3]) * (leftFittedLine[0] / leftFittedLine[1]);

        leftPoints = {cv::Point(x1, y1), cv::Point(x2, y2)};
    }

    if (!rightPoints.empty()) {
        cv::Vec4f rightFittedLine;
        cv::fitLine(rightPoints, rightFittedLine, cv::DIST_L2, 0, 0.01, 0.01);

        // Calculate the top and bottom coordinates of the right line
        int y1 = edges.rows;  // bottm y
        int y2 = edges.rows * 0.65;  // top y

        int x1 = rightFittedLine[2] + (y1 - rightFittedLine[3]) * (rightFittedLine[0] / rightFittedLine[1]);
        int x2 = rightFittedLine[2] + (y2 - rightFittedLine[3]) * (rightFittedLine[0] / rightFittedLine[1]);

        rightPoints = {cv::Point(x1, y1), cv::Point(x2, y2)};
    }
    // print zone green
    output = inputImage.clone();
    cv::Mat overlay = output.clone();

    if (!leftPoints.empty() && !rightPoints.empty()) {
        std::vector<cv::Point> polygonPoints = {
            leftPoints[0], rightPoints[0],  // point bottom
            rightPoints[1], leftPoints[1]   // point top
        };


        // fill the green zoom
        cv::fillPoly(overlay, std::vector<std::vector<cv::Point>>{polygonPoints}, cv::Scalar(0, 255, 0));

        // transparent the green zoom
        cv::addWeighted(overlay, 0.5, output, 0.5, 0, output);
    }

    return output;
}

cv::Mat detectRoadVideo1(const cv::Mat& inputImage) {

    //define all variable
    cv::Mat hsvImage, yellowMask, whiteMask, combinedMask, blurred, edges, roiMask, output;

    //convert video into hsv
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);

    //segement of yellow line
    cv::inRange(hsvImage, cv::Scalar(94, 24, 100), cv::Scalar(179, 70, 140), yellowMask);

    //segement of white line
    cv::inRange(hsvImage, cv::Scalar(0, 0, 180), cv::Scalar(180, 25, 255), whiteMask);

    //combine two lines
    cv::bitwise_or(yellowMask, whiteMask, combinedMask);

    //apply gaussianblur to denoise
    cv::GaussianBlur(combinedMask, blurred, cv::Size(9, 9), 0);

    //use canny to detect the edges
    cv::Canny(blurred, edges, 30, 100);

    //apply roi in order to remove the noise
    roiMask = cv::Mat::zeros(edges.size(), edges.type());
    cv::Point point[1][4] = {
        {cv::Point(edges.cols * 0.25, edges.rows),
         cv::Point(edges.cols * 0.75, edges.rows),
         cv::Point(edges.cols * 0.57, edges.rows * 0.7),
         cv::Point(edges.cols * 0.4, edges.rows * 0.7)}};
    const cv::Point* ppt[1] = {point[0]};
    int npt[] = {4};
    cv::fillPoly(roiMask, ppt, npt, 1, cv::Scalar(255));
    cv::bitwise_and(edges, roiMask, edges);

    //apply hough to detecte straight line
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 10, 20, 10);

    //seperate the edges to two lines
    std::vector<cv::Point> leftPoints, rightPoints;

    int midX = edges.cols / 2;

    for (const auto& line : lines) {
        int x1 = line[0];
        int x2 = line[2];

        // segement of left line
        if (x1 < midX && x2 < midX) {
            leftPoints.push_back(cv::Point(line[0], line[1]));
            leftPoints.push_back(cv::Point(line[2], line[3]));
        }
        // segement of right line
        else if (x1 > midX && x2 > midX) {
            rightPoints.push_back(cv::Point(line[0], line[1]));
            rightPoints.push_back(cv::Point(line[2], line[3]));
        }
    }

    // use line fitting to complete the right line and left line
    if (!leftPoints.empty()) {
        cv::Vec4f leftFittedLine;
        cv::fitLine(leftPoints, leftFittedLine, cv::DIST_L2, 0, 0.01, 0.01);

        // Calculate the top and bottom coordinates of the left line
        int y1 = edges.rows;  // bottom y
        int y2 = edges.rows * 0.7;  // top x

        int x1 = leftFittedLine[2] + (y1 - leftFittedLine[3]) * (leftFittedLine[0] / leftFittedLine[1]);
        int x2 = leftFittedLine[2] + (y2 - leftFittedLine[3]) * (leftFittedLine[0] / leftFittedLine[1]);

        leftPoints = {cv::Point(x1, y1), cv::Point(x2, y2)};
    }

    if (!rightPoints.empty()) {
        cv::Vec4f rightFittedLine;
        cv::fitLine(rightPoints, rightFittedLine, cv::DIST_L2, 0, 0.01, 0.01);

        // Calculate the top and bottom coordinates of the right line
        int y1 = edges.rows;  // bottm y
        int y2 = edges.rows * 0.7;  // top y

        int x1 = rightFittedLine[2] + (y1 - rightFittedLine[3]) * (rightFittedLine[0] / rightFittedLine[1]);
        int x2 = rightFittedLine[2] + (y2 - rightFittedLine[3]) * (rightFittedLine[0] / rightFittedLine[1]);

        rightPoints = {cv::Point(x1, y1), cv::Point(x2, y2)};
    }
    // print zone green
    output = inputImage.clone();
    cv::Mat overlay = output.clone();

    if (!leftPoints.empty() && !rightPoints.empty()) {
        std::vector<cv::Point> polygonPoints = {
            leftPoints[0], rightPoints[0],  // point bottom
            rightPoints[1], leftPoints[1]   // point top
        };

        // fill the green zoom
        cv::fillPoly(overlay, std::vector<std::vector<cv::Point>>{polygonPoints}, cv::Scalar(0, 255, 0));

        // transparent the green zoom
        cv::addWeighted(overlay, 0.5, output, 0.5, 0, output);
    }

    return output;
}

