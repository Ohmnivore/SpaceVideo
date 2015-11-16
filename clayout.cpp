#include "clayout.h"

CLayout::CLayout(QWidget* parent):
    QLayout(parent)
{

}

CLayout::CLayout():
    QLayout()
{

}

CLayout::~CLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void CLayout::addItem(QLayoutItem* item)
{
    list.append(item);
}

void CLayout::addWidget(QWidget* widget)
{
    list.append(new QWidgetItem(widget));
}

QLayoutItem* CLayout::itemAt(int index) const
{
    return list.value(index);
}

int CLayout::count() const
{
    return list.size();
}

QSize CLayout::minimumSize() const
{
    return QSize(320, 240);
}

QSize CLayout::sizeHint() const
{
    return QSize(320, 240);
}

QLayoutItem* CLayout::takeAt(int index)
{
    return index >= 0 && index < list.size() ? list.takeAt(index) : 0;
}
