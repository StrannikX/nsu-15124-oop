#include "plotter.h"
#include <cstddef>
#include <QPainter>
#include <QtCore/QDebug>
#include <map>
#include <cmath>

using namespace std;

Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
{
    e = d = nullptr;
    setMinimumHeight(500);
    setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    setMinimumWidth(500);
    setAutoFillBackground(true);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
}

Plotter::~Plotter()
{
    if (e != nullptr)
        delete e;

    if (d != nullptr)
        delete d;
}

void Plotter::expressionsChanged(Expression * expr, Expression * diff)
{
    if (e != nullptr)
        delete e;

    if (d != nullptr)
        delete d;

    e = expr;
    d = diff;

    update();
}

void Plotter::paintEvent(QPaintEvent * evt) {
    QWidget::paintEvent(evt);
    QPainter p(this);

    p.setPen(Qt::black);

    double stepX = width() / 20;
    double stepY = height() / 20;

    p.drawLine(0, stepY * 10, width(), stepY * 10);
    p.drawLine(10 * stepX, 0, 10 * stepX , height());

    for (int i = 1; i < 20; ++i) {
        p.drawLine(i * stepX, stepY * 10 + 5, i * stepX , stepY * 10 - 5);
        p.drawLine(stepX * 10 - 5, i * stepY, stepX * 10 + 5, stepY * i);
    }

    if (e != nullptr && d != nullptr) {
        p.setPen(Qt::blue);
        drawPlot(e, p);
        p.setPen(Qt::darkGreen);
        drawPlot(d, p);
    }

    p.setPen(Qt::red);
    p.drawText(width() - 20, stepY * 10 + 20, 20, 20, Qt::AlignCenter || Qt::AlignHCenter, "X");
    p.drawText(stepX * 10 + 20, 20, 20, 20, Qt::AlignCenter || Qt::AlignHCenter, "Y");
    p.drawText(stepX * 11 + 5, stepY * 10 + 5, 20, 20, Qt::AlignCenter || Qt::AlignHCenter, "1");
    p.drawText(stepX * 10 + 5, stepY * 9 - 5 , 20, 20, Qt::AlignCenter || Qt::AlignHCenter, "1");
}


void Plotter::drawPlot(Expression * e, QPainter &p)
{
    map<char, double> args;

    int stepX = width() / 20;
    int stepY = height() / 20;

    double perPixelX = 1. / stepX;

    int prevX = 0;
    args['x'] = -10 + prevX * perPixelX;
    double d = e->eval(args);
    int prevY = ceil(d * stepY);

    for (int x = 1; x <= width(); ++x) {
        args['x'] = -10 + x * perPixelX;
        d = e->eval(args);
        int y = ceil(d * stepY);

        p.drawLine(prevX, height()/2 - prevY, x, height()/2 - y);
        prevX = x; prevY = y;
    }
}
