#include "simple_dtw.h"
#include <algorithm>
#include <QDebug>
/**
Inicializa matrizes de distância e custo acumulado para o calculo do DTW

Referências:
https://nipunbatra.github.io/blog/2014/dtw.html //usar wayback machine, página caiu
https://stackoverflow.com/a/7616783
https://jmotif.github.io/sax-vsm_site/morea/algorithm/znorm.html
**/
simple_dtw::simple_dtw(QVector<double> x, QVector<double> y)
{
    firstCurve = x;
    secondCurve = y;

    //calculo de mean
//    double sumFirstCurve = std::accumulate(x.begin(), x.end(), 0.0);
//    double meanFirstCurve = sumFirstCurve / x.size();


//    double sumSecondCurve = std::accumulate(y.begin(), y.end(), 0.0);
//    double meanSecondCurve = sumFirstCurve / y.size();


//    //calculo de standard deviation
//    std::vector<double> diffFirstCurve(x.size());

//    std::transform(x.begin(), x.end(), diffFirstCurve.begin(),
//        std::bind2nd(std::minus<double>(), meanFirstCurve));
//    double sq_sumFirstCurve = std::inner_product(diffFirstCurve.begin(), diffFirstCurve.end(), diffFirstCurve.begin(), 0.0);
//    double stdevFirstCurve = std::sqrt(sq_sumFirstCurve / x.size());


//    std::vector<double> diffSecondCurve(x.size());

//    std::transform(x.begin(), x.end(), diffSecondCurve.begin(),
//        std::bind2nd(std::minus<double>(), meanSecondCurve));
//    double sq_sumSecondCurve = std::inner_product(diffSecondCurve.begin(), diffSecondCurve.end(), diffSecondCurve.begin(), 0.0);
//    double stdevSecondCurve = std::sqrt(sq_sumSecondCurve / x.size());


//    //aplica z normalization nos valores das curvas.
//    for (double firstCurveValue : x)
//    {
//        double new_value = (firstCurveValue - meanFirstCurve) / stdevFirstCurve;
//        firstCurve.push_back(new_value);
//    }

//    for (double secondCurveValue : y)
//    {
//        double new_value = (secondCurveValue - meanSecondCurve) / stdevSecondCurve;
//        secondCurve.push_back(new_value);
//    }


    for (int i = 0; i < secondCurve.size(); i++)
    {
        QVector<double> internalVector;
        for (int j = 0; j < firstCurve.size(); j++)
        {
            internalVector.push_back(0);
        }
        distances.push_back(internalVector);
        //distances.push_back(internalVector);
        accumulated_cost.push_back(internalVector);

    }
    for (int i = 0; i < secondCurve.size(); i++)
    {
        for (int j = 0; j < firstCurve.size(); j++)
        {
            distances[i][j] = pow(firstCurve[j] - secondCurve[i], 2);

        }
    }
    accumulated_cost[0][0] = distances[0][0];



    for (int i = 1; i < firstCurve.length(); i++)
        accumulated_cost[0][i] = distances[0][i] + accumulated_cost[0][i - 1];

    for (int i = 1; i < secondCurve.size(); i++)
        accumulated_cost[i][0] = distances[i][0] + accumulated_cost[i - 1][0];


    for (int i = 1; i < secondCurve.size(); i++) {
        for (int j = 1; j < firstCurve.length(); j++) {
            accumulated_cost[i][j] = std::min(
                std::min(accumulated_cost[i - 1][j - 1], accumulated_cost[i - 1][j]), accumulated_cost[i][j - 1]) + distances[i][j];

        }
    }
}

 simple_dtw::~simple_dtw()
{

}

 /**
    Calcula custo do caminho a partir das curvas passadas no construtor. Retorna o valor do custo como um double e salva o caminho resultado no array path
 **/
double simple_dtw::path_cost()
{
    double cost = 0;
  //  qDebug() << y.length();
  //  qDebug() << x.length();
    int i = secondCurve.length() - 1;
    int j = firstCurve.length() - 1;
    path.append({ (double)firstCurve.length() - 1, (double)secondCurve.length() - 1 });
    while (i > 0 && j > 0)
    {

        if (i == 0)
        {
            j = j - 1;
        }
        else if (j == 0)
        {
            i = i - 1;
        }
        else
        {

            if (accumulated_cost[i - 1][j] ==
                std::min(
                    std::min(accumulated_cost[i - 1][j - 1], accumulated_cost[i - 1][j]), accumulated_cost[i][j - 1]))
            {
                i = i - 1;
            }
            else if (accumulated_cost[i][j - 1] ==
                std::min(std::min(accumulated_cost[i - 1][j - 1], accumulated_cost[i - 1][j]), accumulated_cost[i][j - 1]))
            {
                j = j - 1;
            }

            else
            {
                i = i - 1;
                j = j - 1;
            }
        }
        QVector<double> pathValue = { (double)j, (double)i };
        path.append(pathValue);

    }
    path.append({ 0,0 });

    for (int x = 0; x < path.length(); x++)
    {

        auto actualPath = path[x];
        int i = actualPath[0];
        int j = actualPath[1];

        cost = cost + distances[j][i];

    }

    return cost;

}
