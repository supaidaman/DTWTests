/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "simple_dtw.h"
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<double> x = { 1, 1, 2, 3, 2, 0 };
    QVector<double> y = { 0, 1, 1, 2, 3, 2, 1 };
    std::unique_ptr <simple_dtw> dtw(new simple_dtw(x, y));


    QLineSeries *series = new QLineSeries();

    series->append(0, 1);
    series->append(1, 1);
    series->append(2, 2);
    series->append(3, 3);
    series->append(4, 2);
    series->append(5, 0);

    QLineSeries *series2 = new QLineSeries();

    series2->append(0, 0);
    series2->append(1, 1);
    series2->append(2, 1);
    series2->append(3, 2);
    series2->append(4, 3);
    series2->append(5, 2);
    series2->append(6, 1);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series2);


    auto cost = dtw->path_cost();

    for (int i = 0; i < dtw->path.length(); i++)
    {
        auto pathAtual = dtw->path[i];
        qDebug() << "---path-----";
        qDebug() << pathAtual[0];
        qDebug() << pathAtual[1];
        qDebug() << "----path----";

        qDebug() << "---indiceXY-----";
        qDebug() << x[pathAtual[0]];
        qDebug() << y[pathAtual[1]];
        qDebug() << "----indiceXY----";
        //plt.plot([map_x, map_y], [x[map_x], y[map_y]], 'r')
        QLineSeries *seriesPath = new QLineSeries();
        seriesPath->append(pathAtual[0],x[pathAtual[0]]);
        seriesPath->append(pathAtual[1],y[pathAtual[1]]);
        seriesPath->setColor(QColorConstants::Red);
        chart->addSeries(seriesPath);
    }


    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
