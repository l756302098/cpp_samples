/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

void DrawPolygon(Mat img)
{
    
}

int main(int argc, char *argv[])
{
    std::cout << "start ...!" << std::endl;
    // cv::Mat image = cv::imread("/home/indemind/test.png",cv::IMREAD_UNCHANGED);
    // cv::Mat logo = cv::imread("/home/indemind/home.png",cv::IMREAD_UNCHANGED);
    // cv::Mat mask = cv::imread("/home/indemind/home.png", cv::IMREAD_GRAYSCALE);
    
    // // rotate
    // cv::Point center = cv::Point(logo.cols/2,logo.rows/2);
    // double scale = 1.0;
    // double angle = 90.0;
    // cv::Mat rotMat = cv::getRotationMatrix2D(center,angle,scale);
    // cv::warpAffine(logo,logo,rotMat,logo.size());
    // cv::warpAffine(mask, mask, rotMat, mask.size());
    // // cv::namedWindow("result");
    // // cv::imshow("result", logo);
    // // cv::waitKey(5 * 1000);
    // // add logo
    // cv::Mat imageROI;
    // imageROI = image(cv::Rect(10,10,logo.cols,logo.rows));
    // logo.copyTo(imageROI, mask);
    // cv::namedWindow("result");
    // cv::imshow("result",image);
    // cv::waitKey(5 * 1000);
    // resize
    // cv::Mat desMat;
    // cv::resize(image,desMat,cv::Size(image.cols * 0.5,image.rows * 0.5));
    // cv::imwrite("/home/indemind/thumbnail.png",desMat);

    // cv::line(image, Point(10, 10), Point(100, 100),Scalar(0,0,0));

    //cv::rectangle(image, Point(10, 100), Point(100, 500), Scalar(0, 0, 255), 1, LINE_AA);

    Mat image = Mat::zeros(800, 480, CV_8UC3);
    cv::Mat poly1 = image.clone();
    cv::Mat poly2 = image.clone();
    // std::vector<cv::Point> point1,point2;
    // point1.push_back(cv::Point(image.cols / 4, image.rows / 4));
    // point1.push_back(cv::Point(image.cols / 4, image.rows / 8));
    // point1.push_back(cv::Point(image.cols / 2, image.rows / 6));
    // point1.push_back(cv::Point(image.cols / 3, image.rows / 2));
    // point1.push_back(cv::Point(image.cols / 2, image.rows / 8));

    // point2.push_back(cv::Point(image.cols / 4, image.rows / 4));
    // point2.push_back(cv::Point(image.cols / 4, image.rows / 8));
    // point2.push_back(cv::Point(image.cols / 2, image.rows / 6));
    // point2.push_back(cv::Point(image.cols / 3, image.rows / 2));
    // point2.push_back(cv::Point(image.cols / 2, image.rows / 8));

    // std::vector<std::vector<cv::Point>> pic;
    // pic.push_back(point1);
    // pic.push_back(point2);
    // cv::fillPoly(poly1, pic, Scalar(0, 0, 255), 16, 0);

    std::vector<Point> pts;
    pts.push_back(Point(210, 135));
    pts.push_back(Point(480, 270));
    pts.push_back(Point(450, 424));
    pts.push_back(Point(287, 420));
    pts.push_back(Point(162, 361));
    cv::fillConvexPoly(poly2, pts, Scalar(0, 0, 255), 16, 0);

    cv::namedWindow("result");
    // cv::imshow("result", poly1);
    // cv::waitKey(5 * 1000);

    cv::imshow("result", poly2);
    cv::waitKey(10 * 1000);

    return 0;
}

