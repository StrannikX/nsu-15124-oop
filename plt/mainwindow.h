#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Expressions.hpp>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void plotButtonClicked();

signals:
    void expressionChanged(Expression *, Expression *);


protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    QPushButton * plotButton;
    QLabel      * diffLabel;
    QLineEdit   * expressionEditor;
    QLabel      * exprLabel;
};

#endif // MAINWINDOW_H
