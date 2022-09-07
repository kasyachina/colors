#include "widget.h"
#include "ui_widget.h"
#include <QPalette>
#include <QColorDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui -> colorShowcase -> setAutoFillBackground(true);
    selectedColorPalette = new QPalette;
    selectedColorPalette -> setColor(QPalette::Window, Qt::white);
    ui -> colorShowcase -> setPalette(*selectedColorPalette);

    QGridLayout g(this);
    g.addWidget(ui -> selectModel, 0, 1, 1, 1);
    g.addWidget(ui -> colorShowcase, 1, 4, 1, 1);
    g.addWidget(ui -> chooseColorButton, 2, 4, 1, 1);

    colorSystem *test = new colorSystem(this, 3);
    //g.addWidget(test, 1, 0, 2, 3);
    test->setGeometry(150, 150, 300, 300);
}

Widget::~Widget()
{
    delete ui;
    delete selectedColorPalette;
}

void Widget::on_chooseColorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    selectedColorPalette -> setColor(QPalette::Window, color);
    ui -> colorShowcase -> setPalette(*selectedColorPalette);
}
