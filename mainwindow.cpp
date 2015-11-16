#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolbar.h"

#include <QMessageBox>
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

    m_vo = new QtAV::VideoOutput(this);
    if (!m_vo->widget()) {
        QMessageBox::warning(0, "QtAV error", "Can't create video renderer");
        return;
    }
    setCentralWidget(m_vo->widget());

    m_player = new QtAV::AVPlayer(this);
    m_player->setRenderer(m_vo);

    m_sub = new QtAV::SubtitleFilter(this);
    m_sub->setPlayer(m_player);
    m_sub->setEnabled(true);
    m_sub->setAutoLoad(false);
    m_sub->setFontFile(":/fonts/assets/fonts/AlteHaasGroteskRegular.ttf");
    m_sub->installTo(m_player);

    m_t = new Toolbar(this);
    //QVBoxLayout* l = new QVBoxLayout();
    //m_vo->widget()->setLayout(l);
    //m_vo->widget()->layout()->addWidget(m_t);
    //m_vo->widget()->layout()->setAlignment(m_t, Qt::AlignHCenter | Qt::AlignBottom);

    qApp->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
      m_t->onMouseMove();
  return false;
}

MainWindow::~MainWindow()
{
    delete m_player;
    delete m_vo;
    delete m_sub;
}
