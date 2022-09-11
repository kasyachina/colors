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

    colorSystem *test1 = new colorSystem(this, 3, {{0, 255}, {0, 255}, {0, 255}});
    colorSystem *test2 = new colorSystem(this, 4, {{0, 255}, {0, 255}, {0, 255}, {0, 255}});
    colorSystem *test3 = new colorSystem(this, 3, {{0, 255}, {0, 255}, {0, 255}});

    QHBoxLayout *h = new QHBoxLayout(this);
    QVBoxLayout *vl = new QVBoxLayout, *vr = new QVBoxLayout;
    vl -> addWidget(test1);
    vl -> addWidget(test2);
    vl -> addWidget(test3);
    vr -> addWidget(ui -> selectModel);
    vr -> addWidget(ui -> colorShowcase);
    vr -> addWidget(ui -> chooseColorButton);
    h -> addLayout(vl);
    h -> addLayout(vr);
    setWindowTitle("Color systems");
    resize(minimumSize());
}

Widget::~Widget()
{
    delete ui;
    delete selectedColorPalette;
}

void Widget::on_chooseColorButton_clicked()
{
    QColor _color = QColorDialog::getColor(color);
    if (_color.isValid())
    {
        selectedColorPalette -> setColor(QPalette::Window, _color);
        ui -> colorShowcase -> setPalette(*selectedColorPalette);
        color = _color;
    }
}
