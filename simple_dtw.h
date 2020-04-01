#pragma once
#include <QList>
#include<QVector>

/**
CLasse responsável por calculo do dtw.
Baseado em código disponível em https://nipunbatra.github.io/blog/2014/dtw.html (usar wayback machine caso não funcione)
**/
class simple_dtw {

public:
    //Inicia classe com duas curvas
    simple_dtw(QVector<double> x, QVector<double> y);
    ~simple_dtw();
    //Custo acumulado
    QVector<QVector<double>> accumulated_cost;
    //Tabela de distâncias
    QVector<QVector<double>> distances;
    //Contem caminho de resultado do dtw
    QVector<QVector<double>> path;
    double path_cost();


private:
    QVector<double> firstCurve;
    QVector<double> secondCurve;
};
