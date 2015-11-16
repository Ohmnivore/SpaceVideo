#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtAV>

namespace Ui {
class MainWindow;
}

class Toolbar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QtAV::AVPlayer* m_player;
    QtAV::VideoOutput* m_vo;
    QtAV::SubtitleFilter* m_sub;
    Toolbar* m_t;

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
