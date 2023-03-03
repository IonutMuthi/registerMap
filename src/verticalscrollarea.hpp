#ifndef VERTICALSCROLLAREA_HPP
#define VERTICALSCROLLAREA_HPP

#include <qscrollarea.h>

class VerticalScrollArea: public QScrollArea
{
    Q_OBJECT
public:
   explicit VerticalScrollArea(QWidget *parent = 0);
    virtual bool eventFilter(QObject *o, QEvent *e);
};

#endif // VERTICALSCROLLAREA_HPP
