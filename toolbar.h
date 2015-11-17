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
    QTimer* updateTimer;

    explicit Toolbar(MainWindow* parent);
    ~Toolbar();
    void appear();
    void disappear();
    void onMouseMove();

public slots:
    void onToggleBtnClicked();
    void maximize();
    void fullscreen();
    void onFullscreenBtnClicked();
    void onOpenBtnClicked();
    void onSubBtnClicked();
    void minimize();
    void onOptionsBtnClicked();
    void onMinimizeBtnClicked();
    void onMouseTimerTimeout();
    void onUpdateTimerTimeout();
    void onVSliderChanged(int);
    void onHSliderChanged();

private:
    Ui::Toolbar* ui;
};

#endif // TOOLBAR_H
