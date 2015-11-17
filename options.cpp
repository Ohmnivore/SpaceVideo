#include "options.h"
#include "ui_options.h"

Options::Options(MainWindow* parent) :
    QWidget(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    win = parent;
}

Options::~Options()
{
    delete ui;
}

void Options::updateAV()
{

}

void Options::updateSubtitles()
{

}
