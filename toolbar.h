#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "mainwindow.h"

#include <QWidget>
#include <QTimer>

namespace Ui {
class Toolbar;
}

class Toolbar : public QWidget
{
    Q_OBJECT

public:
    MainWindow* win;
    bool appearing;
    QTimer* moveTimer;

    explicit Toolbar(MainWindow* parent);
    ~Toolbar();
    void appear();
    void disappear();
    void onMouseMove();

public slots:
    void onToggleBtnClicked();
    void onFullscreenBtnClicked();
    void onOpenBtnClicked();
    void onSubBtnClicked();
    void onMinimizeBtnClicked();
    void onMouseTimerTimeout();
    void onVSliderChanged(int);

private:
    Ui::Toolbar* ui;
};

#endif // TOOLBAR_H
