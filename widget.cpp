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

    QHBoxLayout *h = new QHBoxLayout(this);
    QVBoxLayout *vr = new QVBoxLayout;

    colorSystemController *controller = new colorSystemController(this, {ColorSystem::RGB, ColorSystem::HSV, ColorSystem::XYZ});
    vr -> addWidget(ui -> selectModel);
    vr -> addWidget(ui -> colorShowcase);
    vr -> addWidget(ui -> chooseColorButton);
    h -> addWidget(controller);
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
