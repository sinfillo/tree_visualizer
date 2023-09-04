#ifndef GRAPHICSSCENE_CLICKABLE_H
#define GRAPHICSSCENE_CLICKABLE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include "avltree.h"
#include "rbtree.h"
#include "cartesiantree.h"

class GraphicsScene_clickable : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene_clickable();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
signals:
    void scene_clicked(QPointF);
public slots:

private:
    QPointF where_pressed;

};

#endif // GRAPHICSSCENE_CLICKABLE_H
