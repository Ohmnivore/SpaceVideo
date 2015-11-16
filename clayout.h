#ifndef CLAYOUT_H
#define CLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QWidgetItem>

class CLayout : public QLayout
{
public:
    CLayout(QWidget* parent);
    CLayout();
    ~CLayout();
    void addItem(QLayoutItem*);
    void addWidget(QWidget*);
    QLayoutItem* itemAt(int) const;
    int count() const;
    QSize minimumSize() const;
    QSize sizeHint() const;
    QLayoutItem* takeAt(int);
private:
    QList<QLayoutItem*> list;
};

#endif
