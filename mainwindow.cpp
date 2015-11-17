#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolbar.h"
#include "options.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Poor man's SASS
    QFile f(":/styles/assets/styles/style.css");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QString s = QString(f.readAll());
    f.close();
    s.replace("@cgreylight", "#3f3f3f");
    s.replace("@cgrey", "#2d2d2d");
    s.replace("@cyellow", "#ecb447");
    s.replace("@corange", "#cc583f");
    s.replace("@cpurple", "#7d6aad");
    s.replace("@cblue", "#5991aa");
    s.replace("@cgreen", "#75c095");
    setStyleSheet(s);

    qApp->installEventFilter(this);

    m_inst = new VlcInstance(VlcCommon::args(), this);
    m_player = new VlcMediaPlayer(m_inst);

    m_vid = new VlcWidgetVideo(this);
    setCentralWidget(m_vid);
    m_player->setVideoWidget(m_vid);
    m_vid->setMediaPlayer(m_player);
    m_vid->setMinimumSize(640, 480);

    m_t = new Toolbar(this);
    m_opt = new Options(this);
    m_opt->hide();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest)
    {
        m_t->move(
            m_vid->width() / 2.0 - m_t->width() / 2.0,
            m_vid->height() - m_t->height());
        m_opt->move(
            m_vid->width() / 2.0 - m_opt->width() / 2.0,
            0);
    }

    if (event->type() == QEvent::MouseMove)
        m_t->onMouseMove();
    return false;
}

MainWindow::~MainWindow()
{
    delete m_player;
    delete m_inst;
    delete m_vid;
    delete m_t;
    delete m_opt;
}
