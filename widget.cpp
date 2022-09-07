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
    color = Qt::white;

    QGridLayout *g = new QGridLayout(this);
    colorSystem *test1 = new colorSystem(this, 3);
    colorSystem *test2 = new colorSystem(this, 4);
    colorSystem *test3 = new colorSystem(this, 3);
    g -> addWidget(test1, 1, 0, 1, 3);
    g -> addWidget(test2, 3, 0, 1, 3);
    g -> addWidget(test3, 5, 0, 1, 3);
    g -> addWidget(ui -> selectModel, 0, 0, 1, 1);
    g -> addWidget(ui -> colorShowcase, 1, 4, 1, 1);
    g -> addWidget(ui -> chooseColorButton, 2, 4, 1, 1);

    //test->setGeometry(150, 150, 300, 300);
}

Widget::~Widget()
{
    delete ui;
    delete selectedColorPalette;
}

void Widget::on_chooseColorButton_clicked()
{
    QColor _color = QColorDialog::getColor(color);
    selectedColorPalette -> setColor(QPalette::Window, _color);
    ui -> colorShowcase -> setPalette(*selectedColorPalette);
}
