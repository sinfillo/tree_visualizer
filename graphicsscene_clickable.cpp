#include "graphicsscene_clickable.h"
#include <QDebug>

GraphicsScene_clickable::GraphicsScene_clickable()
{

}

void GraphicsScene_clickable::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    where_pressed = mouseEvent->scenePos();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene_clickable::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    if (static_cast<int>(mouseEvent->scenePos().x()) == static_cast<int>(where_pressed.x()) &&
            static_cast<int>(mouseEvent->scenePos().y()) == static_cast<int>(where_pressed.y())) {
        qDebug() << "YES IT IS";
        emit scene_clicked(where_pressed);
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
