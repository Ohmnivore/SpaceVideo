#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtAV>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVideo.h>

namespace Ui {
class MainWindow;
}

class Toolbar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    VlcInstance* m_inst;
    VlcMediaPlayer* m_player;
    VlcWidgetVideo* m_vid;
    Toolbar* m_t;

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
