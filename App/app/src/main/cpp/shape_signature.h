#pragma once
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;
//cv::Mat preprocess(const cv::Mat& img);
//std::vector<cv::Point> getMainContour(const cv::Mat& bin);
//std::vector<float> computeFFTDescriptor(const std::vector<cv::Point>& contour);
//std::string classifyShape(const cv::Mat& img);
//std::string classifySimulador() ;

Mat preprocess(Mat input);
vector<Point> extractMainContour(Mat bin);

float distaciaEuclider(vector<float> vector1, vector<float> vector2);
vector<vector<Point>> bordesPuntos(Mat bin);
vector<Vec4i>  bordesPuntosJerarquia(Mat bin);
Point centroideIMG(Mat bordesCanny);
Mat coordennadasCompleja(vector<Point>& contorno, Point2f centroide);
Mat calculoDFT(Mat coordenadasComplejas);
vector<float> normalizarDescriptores(Mat dftResult);

String clasificacionFigura(Mat img);
float distaciaFiguras(vector<vector<float>> distancias,vector<float> img);