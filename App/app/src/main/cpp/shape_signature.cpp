//
// Created by jhonatan on 20/1/26.
//


#include "shape_signature.h"
#include <opencv2/opencv.hpp>
#include <cmath>
#include <numeric>
using namespace std;
using namespace cv;
using namespace std;
Mat preprocess(Mat input)
{
    Mat gray, blurImg, bin;

    if (input.channels() == 3)
        cvtColor(input, gray, COLOR_BGR2GRAY);
    else
        gray = input.clone();

    GaussianBlur(gray, blurImg, Size(5, 5), 0);
    threshold(blurImg, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    return bin;
}

// Extrae el contorno principal (el de mayor área)
vector<Point> extractMainContour(Mat bin)
{
    vector<vector<Point>> contours;
    vector<Point> mainContour;

    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    double maxArea = 0.0;
    for (const auto &c : contours)
    {
        double area = contourArea(c);
        if (area > maxArea)
        {
            maxArea = area;
            mainContour = c;
        }
    }

    return mainContour;
}

vector<vector<Point>> bordesPuntos(Mat bin)
{
    vector<vector<Point>> puntos;
    vector<Vec4i> jerarquia;

    findContours(bin, puntos, jerarquia, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    return puntos;
}

vector<Vec4i> bordesPuntosJerarquia(Mat bin)
{
    vector<vector<Point>> puntos;
    vector<Vec4i> jerarquia;

    findContours(bin, puntos, jerarquia, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    return jerarquia;
}



Point centroideIMG(Mat bordesCanny)
{
    Moments _moments = moments(bordesCanny, true);
    double cxO = _moments.m10 / _moments.m00;
    double cyO = _moments.m01 / _moments.m00;
    Point pointO(cxO, cyO);

    return pointO;
}
vector<float> normalizarDescriptores(Mat dftResult)
{
    vector<float> descriptoresNormalizados;

    // Calcular magnitud del primer armónico |F(1)|
    Vec2f F1 = dftResult.at<Vec2f>(0, 1);
    float magF1 = sqrt(F1[0] * F1[0] + F1[1] * F1[1]);

    if (magF1 < 1e-6)
    {
        cout << "Advertencia: |F(1)| muy pequeño, usando normalización alternativa" << endl;
        magF1 = 1.0f;
    }

    int numCoefs = min(20, dftResult.cols);
    for (int k = 0; k < numCoefs; k++)
    {
        Vec2f Fk = dftResult.at<Vec2f>(0, k);
        float magnitud = sqrt(Fk[0] * Fk[0] + Fk[1] * Fk[1]);

        // Normalizar por |F(1)| para invarianza a escala
        float magnitudNormalizada = magnitud / magF1;
        descriptoresNormalizados.push_back(magnitudNormalizada);
    }

    return descriptoresNormalizados;
}
float distaciaEuclider(vector<float> desc1, vector<float> desc2)
{
    if (desc1.size() != desc2.size())
    {
        cout << "Error: descriptores de diferente tamaño" << endl;
        return FLT_MAX;
    }

    float suma = 0.0f;
    for (size_t i = 0; i < desc1.size(); i++)
    {
        float diff = desc1[i] - desc2[i];
        suma += diff * diff;
    }

    return sqrt(suma);
};
Mat coordennadasCompleja(vector<Point> &contorno, Point2f centroide)
{
    Mat señalCompleja(contorno.size(), 1, CV_32FC2);
    for (int i = 0; i < contorno.size(); i++)
    {
        señalCompleja.at<Vec2f>(i)[0] = contorno[i].x - centroide.x; // parte real
        señalCompleja.at<Vec2f>(i)[1] = contorno[i].y - centroide.y; // parte imaginaria
    }

    return señalCompleja;
}
Mat calculoDFT(Mat coordenadasComplejas)
{

    Mat input = coordenadasComplejas.reshape(1, 1);
    input.convertTo(input, CV_32F);

    Mat complexI;
    dft(input, complexI, DFT_COMPLEX_OUTPUT);

    return complexI;
}
float distaciaFiguras(vector<vector<float>> distancias, vector<float> img)
{
    float distanciaMinima = FLT_MAX;
    // string etiquetaMasCercana = "DESCONOCIDO";

    for (const auto &descrip : distancias)
    {
        float distancia = distaciaEuclider(img,descrip);

        if (distancia < distanciaMinima)
        {
            distanciaMinima = distancia;
            // etiquetaMasCercana = etiqueta;
        }
    }
    return distanciaMinima;
}
String clasificacionFigura(Mat img)
{
    Mat bin = preprocess(img);

    Mat bordesCanny;
    Canny(bin, bordesCanny, 110, 130);

    vector<Point> contornoExterno;
    contornoExterno = extractMainContour(bordesCanny);

    Point point = centroideIMG(bordesCanny);

    Mat cordenadasComplejas = coordennadasCompleja(contornoExterno, point);

    Mat imgDFT = calculoDFT(cordenadasComplejas);
    vector<float> descriptores = normalizarDescriptores(imgDFT);

    vector<vector<float>> circulo = {
            {0.0205462, 1, 0.0211465, 0.0328911, 0.00992694, 0.015461, 0.00774666, 0.00223242, 0.00552495, 0.00181698, 0.00434189, 0.00249067, 0.0028727, 0.00153274, 0.00157819, 0.00250225, 0.000581209, 0.00196945, 0.000538991, 0.000205829},
            {0.0971133, 1, 4.54864, 0.449021, 0.0771199, 0.183677, 0.416277, 0.0408067, 0.0136755, 0.0132843, 0.0401555, 0.00744942, 0.0145521, 0.00256847, 0.0454038, 0.0250527, 0.032782, 0.00919006, 0.0253667, 0.01019},
            {0.0677713, 1, 0.0240095, 0.0163242, 0.00785576, 0.0135333, 0.0107108, 0.00580505, 0.00501137, 0.00395645, 0.00295006, 0.00180582, 0.00191655, 0.00136848, 0.00124098, 0.00161798, 0.000315928, 0.00109734, 0.000271632, 0.000353949}};
    vector<vector<float>> cuadrado = {
            {0.0301652, 1, 0.00506409, 0.118465, 0.0158983, 0.0397165, 0.00952314, 0.02017, 0.00420268, 0.0137718, 0.00632955, 0.00977542, 0.00316032, 0.00470158, 0.00248152, 0.00566405, 0.00277528, 0.00336812, 0.00152689, 0.00247969},
            {0.326798, 1, 0.133166, 0.0523882, 0.0197684, 0.0248331, 0.019746, 0.00872918, 0.00795501, 0.00541987, 0.00449632, 0.00318659, 0.00224835, 0.00480693, 0.000899125, 0.000850037, 0.00236476, 0.0017981, 0.00158415, 0.000392893},
            {0.0456656, 1, 0.0177233, 0.0877399, 0.00751182, 0.0344427, 0.00616437, 0.0214271, 0.00411719, 0.0109924, 0.00216168, 0.00856584, 0.00394203, 0.00839329, 0.00365144, 0.00388795, 0.001546, 0.00356748, 0.00246987, 0.00338314}};
    vector<vector<float>> triangulo = {
            {0.15161, 1, 0.243877, 0.00620257, 0.0605582, 0.0447164, 0.00629119, 0.0193336, 0.0178042, 0.0016387, 0.00880879, 0.00945717, 0.00287863, 0.00554471, 0.00579421, 0.000849774, 0.00408182, 0.00329532, 0.000799925, 0.00189425},
            {0.205651, 1, 0.549493, 0.366529, 0.270293, 0.131046, 0.0703751, 0.00241952, 0.0150963, 0.00706138, 0.0079069, 0.0330493, 0.026534, 0.0286881, 0.00549643, 0.0100074, 0.0117479, 0.00571672, 0.00181259, 0.0142726},
            {0.0523012, 1, 0.292394, 0.0517551, 0.0713217, 0.0372526, 0.0117374, 0.0294282, 0.00658882, 0.0092281, 0.0112839, 0.00912644, 0.00990469, 0.00766942, 0.00522604, 0.00609437, 0.00726268, 0.00386651, 0.00156552, 0.00408923}};

    vector<pair<float, string>> resultados = {
            { distaciaFiguras(circulo, descriptores), "Circulo" },
            { distaciaFiguras(cuadrado, descriptores), "Cuadrado" },
            { distaciaFiguras(triangulo, descriptores), "Triangulo" }
    };

    auto minimo = resultados[0];
    for (auto &r : resultados) {
        if (r.first < minimo.first) {
            minimo = r;
        }
    }

    return minimo.second;
}
String classifySimulador(String a){
    return  a;
}
