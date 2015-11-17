#ifndef OPTIONS_H
#define OPTIONS_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class Options;
}

class Options : public QWidget
{
    Q_OBJECT

public:
    MainWindow* win;

    explicit Options(MainWindow *parent = 0);
    ~Options();
    void updateAV();
    void updateSubtitles();

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
