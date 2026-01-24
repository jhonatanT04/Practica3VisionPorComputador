#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <cstring>
#include <chrono>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/superres/optical_flow.hpp>
#include <opencv2/dnn_superres.hpp>

#include <opencv2/features2d/features2d.hpp>

#include <opencv2/dnn.hpp>
#include "ania.h"

Ania ania;

using namespace std;
using namespace cv;
using namespace dnn;

int main(int argc, char *args[])
{
    Mat img = imread("t.PNG");
    
    cout << ania.clasificacionFigura(img)  << endl;

    // cout << "vector<vector<float>> Circulo = {"  << endl;
    // Mat imgc1 = imread("KNN_Procesamieto/ups-writing-skills/all-images/circle/c1-2.PNG");
    // ania.clasificacionFigura(imgc1);
    // cout << "," ;
    // Mat imgc2 = imread("KNN_Procesamieto/ups-writing-skills/all-images/circle/c2c-1.PNG");
    // ania.clasificacionFigura(imgc2);
    // cout << "," ;
    // Mat imgc3 = imread("KNN_Procesamieto/ups-writing-skills/all-images/circle/c16-2.PNG");
    // ania.clasificacionFigura(imgc3);
    // cout << "};"  << endl;

    // cout << "vector<vector<float>> Cuadrado = {"  << endl;
    // Mat imgq1 = imread("KNN_Procesamieto/ups-writing-skills/all-images/square/q1n-2.PNG");
    // ania.clasificacionFigura(imgq1);
    // cout << "," ;
    // Mat imgq2 = imread("KNN_Procesamieto/ups-writing-skills/all-images/square/q12ni-0.PNG");
    // ania.clasificacionFigura(imgq2);
    // cout << "," ;
    // Mat imgq3 = imread("KNN_Procesamieto/ups-writing-skills/all-images/square/q10i-2.PNG");
    // ania.clasificacionFigura(imgq3);
    // cout << "};"  << endl;

    
}
