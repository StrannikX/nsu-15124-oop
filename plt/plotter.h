#ifndef PLOTTER_H
#define PLOTTER_H

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <Expressions.hpp>

namespace Ui {
class Plotter;
}

class Plotter : public QWidget
{
    Q_OBJECT

    Expression * e, * d;

    void drawPlot(Expression *, QPainter&);

public:
    explicit Plotter(QWidget *parent = 0);
    ~Plotter();

public slots:
    void expressionsChanged(Expression *, Expression *);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};

#endif // PLOTTER_H
