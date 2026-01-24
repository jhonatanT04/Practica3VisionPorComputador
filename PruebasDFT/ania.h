#include <opencv2/opencv.hpp>
using namespace cv;
#include <string>

using namespace cv;
using namespace std;
class Ania
{
public:
    Ania();
    ~Ania();

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
};
 