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

public slots:
    void updateVideo();
    void updateAudio();
    void updateSubtitles();
    void videoSet(int);
    void audioSet(int);
    void subtitleSet(int);

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H
