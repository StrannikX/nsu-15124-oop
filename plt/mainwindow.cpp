#include "mainwindow.h"
#include <QtCore/QDebug>
#include <Expressions.hpp>
#include <QScreen>
#include <expr_parser.hpp>
#include <plotter.h>
#include <QMessageBox>
#include <QtGui/QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QWidget * central = new QWidget(this);
    QLayout * vl = new QVBoxLayout(central);
    central->setLayout(vl);

    setCentralWidget(central);

    QWidget * hboxWidget = new QWidget(central);
    central->layout()->addWidget(hboxWidget);
    QBoxLayout * hl = new QHBoxLayout(hboxWidget);
    hboxWidget->setLayout(hl);

    expressionEditor = new QLineEdit(hboxWidget);
    expressionEditor->setText("x + 1");

    hl->addWidget(expressionEditor);

    plotButton = new QPushButton(hboxWidget);
    plotButton->setText("Plot");

    hl->addWidget(plotButton);

    hboxWidget = new QWidget(central);
    vl->addWidget(hboxWidget);
    hl = new QHBoxLayout(hboxWidget);

    hl->addStretch();

    exprLabel = new QLabel(hboxWidget);
    hl->addWidget(exprLabel);
    QPalette pal(exprLabel->palette());
    pal.setColor(QPalette::WindowText, Qt::blue);
    exprLabel->setPalette(pal);

    QLabel * ass = new QLabel(hboxWidget);
    ass->setText(" = ");
    hl->addWidget(ass);

    diffLabel = new QLabel(hboxWidget);
    hl->addWidget(diffLabel);
    pal = QPalette(diffLabel->palette());
    pal.setColor(QPalette::WindowText, Qt::darkGreen);
    diffLabel->setPalette(pal);

    hl->addStretch();

    Plotter * plotter = new Plotter(central);
    central->layout()->addWidget(plotter);

    connect(plotButton, &QPushButton::clicked, this, &MainWindow::plotButtonClicked);
    connect(this, &MainWindow::expressionChanged, plotter, &Plotter::expressionsChanged);

    plotButtonClicked();
}

MainWindow::~MainWindow()
{

}

void MainWindow::plotButtonClicked() {
    QString str = expressionEditor->text();
        try {
            Expression * expr = parse_expression(str.toStdString());
            Expression * d = expr->diff('x')->re();

            str = "(";

            QTextStream ss(&str);
            ss.setRealNumberNotation(QTextStream::SmartNotation);
            expr->print(ss);
            ss << ")'";
            exprLabel->setText(str);

            str = "";
            d->print(ss);

            diffLabel->setText(str);

            emit expressionChanged(expr, d);
        } catch (std::string e) {
            QMessageBox msg(this);
            msg.setWindowTitle("Expression parsing error!");
            msg.setText(e.c_str());
            msg.setIcon(QMessageBox::Warning);
            emit expressionChanged(nullptr, nullptr);
            exprLabel->setText("");
            diffLabel->setText("");
            msg.exec();
        }
}

void MainWindow::paintEvent(QPaintEvent * e)
{
    QMainWindow::paintEvent(e);
}
