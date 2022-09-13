#include "colorsystemcontroller.h"

colorSystemController::colorSystemController(QWidget *parent, const std::vector<ColorSystem>& data): QWidget(parent)
{
    vLayout = nullptr;
    for (int i = 0; i < 3; i++)
    {
        systems[i] = nullptr;
    }
    ChangeSystems(data);
}
void colorSystemController::ChangeSystems(const std::vector<ColorSystem>& data)
{
    if (vLayout)
        delete vLayout;
    vLayout = new QVBoxLayout(this);
    for (int i = 0; i < 3; i++)
    {
        if (systems[i])
            delete systems[i];
        switch (data[i])
        {
            case ColorSystem::RGB:
                systems[i] = new RGBSystem(this);
            break;
            case ColorSystem::CMYK:
                systems[i] = new CMYKSystem(this);
            break;
            case ColorSystem::HSV:
                systems[i] = new HSVSystem(this);
            break;
            case ColorSystem::HLS:
                systems[i] = new HLSSystem(this);
            break;
            case ColorSystem::XYZ:
                systems[i] = new XYZSystem(this);
            break;
            case ColorSystem::LAB:
                systems[i] = new LABSystem(this);
        }
        vLayout->addWidget(systems[i]);
    }
}
colorSystemController::~colorSystemController()
{
    delete vLayout;
    for (int i = 0; i < 3; i++)
    {
        delete systems[i];
    }
}
