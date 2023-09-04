#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avltree.h"
#include <QGraphicsScene>
#include <QDebug>
#include "Graphics_view_zoom.h"
#include "graphicsscene_clickable.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    view_zoom = new Graphics_view_zoom(ui->graphicsView);
    view_zoom->set_modifiers(Qt::NoModifier);
    /*avl_tree._insert(1000000);
    rb_tree._insert(1000000);
    cart_tree._insert(1000000);*/
    QObject::connect(scene, &GraphicsScene_clickable::scene_clicked, this, &MainWindow::deleting_vertex);
    redraw_cur_tree();
    ui->getAVLtreeButton->setStyleSheet("background-color: pink");
    ui->getCortesiantreeButton->setStyleSheet("background-color : lightGray");
    ui->getRBtreeButton->setStyleSheet("background-color : lightGray");
    ui->getSplaytreeButton->setStyleSheet("background-color : lightGray");
    ui->getIputVertexButton->setStyleSheet("background-color : lightGray");
    ui->clearButton->setStyleSheet("background-color : lightGray");
}

MainWindow::~MainWindow()
{
    delete ui;
}

RBtree::Node vertex = {0, 'B', &vertex, &vertex, nullptr};

void MainWindow::deleting_vertex(QPointF delete_point) {
    qDebug() << "LOOOL";
    std::pair<bool, int> deletable_number;
    if (cur_tree == TreeState::AVLtree) {
        qDebug() << delete_point;
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                                   int(3 * NODE_RAD * countSize_AVLtree(avl_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_AVLtree(avl_tree.root) + 1);
        deletable_number = find_by_coord_AVLtree(avl_tree.root, (int)delete_point.x(), (int)delete_point.y(), 0,
                                                 std::max(ui->graphicsView->width(),
                                                          int(3 * NODE_RAD  * countSize_AVLtree(avl_tree.root))), Y_SHIFT);
    } else if (cur_tree == TreeState::CartesianTree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                                   int(3 * NODE_RAD * countSize_Cartesiantree(cart_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_Cartesiantree(cart_tree.root) + 1);
        deletable_number = find_by_coord_Cartesiantree(cart_tree.root, (int)delete_point.x(), (int)delete_point.y(), 0,
                                                 std::max(ui->graphicsView->width(),
                                                          int(3 * NODE_RAD  * countSize_Cartesiantree(cart_tree.root))), Y_SHIFT);
    } else if (cur_tree == TreeState::RBtree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                                   int(3 * NODE_RAD * countSize_RBtree(rb_tree.root, rb_tree.vertex) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_RBtree(rb_tree.root, rb_tree.vertex) + 1);
        deletable_number = find_by_coord_RBtree(rb_tree.root, rb_tree.vertex, (int)delete_point.x(), (int)delete_point.y(), 0,
                                                 std::max(ui->graphicsView->width(),
                                                          int(3 * NODE_RAD  * countSize_RBtree(rb_tree.root, rb_tree.vertex))), Y_SHIFT);
    } else if (cur_tree == TreeState::SplayTree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                                   int(3 * NODE_RAD * countSize_Splaytree(splay_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_Splaytree(splay_tree.root) + 1);
        deletable_number = find_by_coord_Splaytree(splay_tree.root, (int)delete_point.x(), (int)delete_point.y(), 0,
                                                 std::max(ui->graphicsView->width(),
                                                          int(3 * NODE_RAD  * countSize_Splaytree(splay_tree.root))), Y_SHIFT);
    }

    if (deletable_number.first) {
        avl_tree._erase(deletable_number.second);
        rb_tree._erase(deletable_number.second);
        cart_tree._erase(deletable_number.second);
        splay_tree._erase(deletable_number.second);
        all_elem.erase(deletable_number.second);
        redraw_cur_tree();
    }
}

void MainWindow::redraw_cur_tree() {

    qDebug() << "lol";
    scene->clear();
    //qDebug() << (tree.root == nullptr);
    if (cur_tree == TreeState::AVLtree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                           int(3 * NODE_RAD * countSize_AVLtree(avl_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_AVLtree(avl_tree.root) + 1);
        qDebug() << ui->graphicsView->width();
        drawProportional_AVLtree(avl_tree.root, scene, 0, std::max(ui->graphicsView->width(),
                                                               int(3 * NODE_RAD  * countSize_AVLtree(avl_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)),
                                 Y_SHIFT);
        QRectF rect = scene->itemsBoundingRect();
        scene->setSceneRect(rect);
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
        qDebug() << scene->sceneRect() << ui->graphicsView->mapToScene(ui->graphicsView->rect()).boundingRect();
    } else if (cur_tree == TreeState::CartesianTree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                           int(3 * NODE_RAD * countSize_Cartesiantree(cart_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_Cartesiantree(cart_tree.root) + 1);
        qDebug() << ui->graphicsView->width();
        drawProportional_Cartesiantree(cart_tree.root, scene, 0, std::max(ui->graphicsView->width(),
                                                               int(3 * NODE_RAD  * countSize_Cartesiantree(cart_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)),
                                 Y_SHIFT);
        QRectF rect = scene->itemsBoundingRect();
        scene->setSceneRect(rect);
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
        qDebug() << scene->sceneRect() << ui->graphicsView->mapToScene(ui->graphicsView->rect()).boundingRect();
    } else if (cur_tree == TreeState::RBtree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                           int(3 * NODE_RAD * countSize_RBtree(rb_tree.root, rb_tree.vertex) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_RBtree(rb_tree.root, rb_tree.vertex) + 1);
        qDebug() << ui->graphicsView->width();
        drawProportional_RBtree(rb_tree.root, rb_tree.vertex, scene, 0, std::max(ui->graphicsView->width(),
                                                               int(3 * NODE_RAD  * countSize_RBtree(rb_tree.root, rb_tree.vertex) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)),
                                 Y_SHIFT);
        QRectF rect = scene->itemsBoundingRect();
        scene->setSceneRect(rect);
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
        qDebug() << scene->sceneRect() << ui->graphicsView->mapToScene(ui->graphicsView->rect()).boundingRect();
    } else if (cur_tree == TreeState::SplayTree) {
        Y_SHIFT = std::max(2 * ui->graphicsView->width(),
                           int(3 * NODE_RAD * countSize_Splaytree(splay_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)) / 2 / (2 * countHeight_Splaytree(splay_tree.root) + 1);
        qDebug() << ui->graphicsView->width();
        drawProportional_Splaytree(splay_tree.root, scene, 0, std::max(ui->graphicsView->width(),
                                                               int(3 * NODE_RAD  * countSize_Splaytree(splay_tree.root) /* / sqrt(log(countSize_AVLtree(tree.root)))*/)),
                                 Y_SHIFT);
        QRectF rect = scene->itemsBoundingRect();
        scene->setSceneRect(rect);
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
        qDebug() << scene->sceneRect() << ui->graphicsView->mapToScene(ui->graphicsView->rect()).boundingRect();
    }
}


void fit_scene_in_view(QGraphicsView *view) {
    view->scale(std::min((qreal)(view->width()) / (view->scene()->width()), (qreal)(view->height()) / (view->scene()->height())),
                std::min((qreal)(view->width()) / (view->scene()->width()), (qreal)(view->height()) / (view->scene()->height())));
}

int NODE_RAD = 20, Y_SHIFT = 70;

int countSize_AVLtree(AVLtree::Node *ver) {
    if (!ver)
        return 0;
    return countSize_AVLtree(ver->left) + 1 + countSize_AVLtree(ver->right);
}

int countHeight_AVLtree(AVLtree::Node *ver) {
    if (!ver)
        return 0;
    return std::max(countHeight_AVLtree(ver->left), countHeight_AVLtree(ver->right)) + 1;
}

int countSize_Cartesiantree(Cartesiantree::Node *ver) {
    if (!ver)
        return 0;
    return countSize_Cartesiantree(ver->left) + 1 + countSize_Cartesiantree(ver->right);
}

int countHeight_Cartesiantree(Cartesiantree::Node *ver) {
    if (!ver)
        return 0;
    return std::max(countHeight_Cartesiantree(ver->left), countHeight_Cartesiantree(ver->right)) + 1;
}

int countSize_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex) {
    if (ver == &nilvertex)
        return 0;
    return countSize_RBtree(ver->left, nilvertex) + 1 + countSize_RBtree(ver->right, nilvertex);
}

int countHeight_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex) {
    if (ver == &nilvertex)
        return 0;
    return std::max(countHeight_RBtree(ver->left, nilvertex), countHeight_RBtree(ver->right, nilvertex)) + 1;
}

int countSize_Splaytree(Splaytree::Node *ver) {
    if (!ver) {
        return 0;
    }

    return countSize_Splaytree(ver->left) + 1 + countSize_Splaytree(ver->right);
}

int countHeight_Splaytree(Splaytree::Node *ver) {
    if (!ver) {
        return 0;
    }

    return std::max(countHeight_Splaytree(ver->left), countHeight_Splaytree(ver->right)) + 1;
}

void drawProportional_Splaytree(Splaytree::Node *ver, QGraphicsScene *scene, int x_left, int x_right, int y_cur) {
    if (!ver) {
        return;
    }
    int leftsz = countSize_Splaytree(ver->left), rightsz = countSize_Splaytree(ver->right);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    if (ver->left) {
        auto son = ver->left;
        int son_leftsz = countSize_Splaytree(son->left), son_rightsz = countSize_Splaytree(son->right);
        int x_left_son = x_left, x_right_son = x_cur;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) *(son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    if (ver->right) {
        auto son = ver->right;
        int son_leftsz = countSize_Splaytree(son->left), son_rightsz = countSize_Splaytree(son->right);
        int x_left_son = x_cur, x_right_son = x_right;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    QGraphicsRectItem *white_cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    white_cur_ver_rect->setBrush(QBrush(Qt::white));
    scene->addItem(white_cur_ver_rect);
    QGraphicsRectItem *cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    //cur_ver_rect->setBrush(QBrush(Qt::black));
    scene->addItem(cur_ver_rect);
    QGraphicsTextItem *cur_ver_text = scene->addText(QString::number(ver->value));
    cur_ver_text->setPos(x_cur - NODE_RAD, y_cur - NODE_RAD);

    QString font_family = "Arial";
    cur_ver_text->setFont(QFont(font_family));
    int font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                              2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                     cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                                  2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                         cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    /*
     * Drawing children
     */
    if (ver->left) {
        drawProportional_Splaytree(ver->left, scene, x_left, x_cur, y_cur + Y_SHIFT);
    }
    if (ver->right) {
        drawProportional_Splaytree(ver->right, scene, x_cur, x_right, y_cur + Y_SHIFT);
    }
}

void drawProportional_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex, QGraphicsScene *scene, int x_left, int x_right, int y_cur) {
    if (ver == &nilvertex) {
        return;
    }
    int leftsz = countSize_RBtree(ver->left, nilvertex), rightsz = countSize_RBtree(ver->right, nilvertex);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    if (ver->left != &nilvertex) {
        auto son = ver->left;
        int son_leftsz = countSize_RBtree(son->left, nilvertex), son_rightsz = countSize_RBtree(son->right, nilvertex);
        int x_left_son = x_left, x_right_son = x_cur;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    if (ver->right != &nilvertex) {
        auto son = ver->right;
        int son_leftsz = countSize_RBtree(son->left, nilvertex), son_rightsz = countSize_RBtree(son->right, nilvertex);
        int x_left_son = x_cur, x_right_son = x_right;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    QGraphicsRectItem *white_cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    if (ver->color == 'R') {
        white_cur_ver_rect->setBrush(QBrush(Qt::red));
    } else {
        white_cur_ver_rect->setBrush(QBrush(Qt::black));
    }
    scene->addItem(white_cur_ver_rect);
    QGraphicsRectItem *cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    //cur_ver_rect->setBrush(QBrush(Qt::black));
    scene->addItem(cur_ver_rect);
    QGraphicsTextItem *cur_ver_text = scene->addText(QString::number(ver->value));
    cur_ver_text->setPos(x_cur - NODE_RAD, y_cur - NODE_RAD);
    cur_ver_text->setDefaultTextColor(QColor(Qt::white));
    QString font_family = "Arial";
    cur_ver_text->setFont(QFont(font_family));
    int font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                              2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                     cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                                  2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                         cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    /*
     * Drawing children
     */
    if (ver->left != &nilvertex) {
        drawProportional_RBtree(ver->left, nilvertex, scene, x_left, x_cur, y_cur + Y_SHIFT);
    }
    if (ver->right != &nilvertex) {
        drawProportional_RBtree(ver->right, nilvertex, scene, x_cur, x_right, y_cur + Y_SHIFT);
    }
}

void drawProportional_Cartesiantree(Cartesiantree::Node *ver, QGraphicsScene *scene, int x_left, int x_right, int y_cur) {
    if (!ver) {
        return;
    }
    int leftsz = countSize_Cartesiantree(ver->left), rightsz = countSize_Cartesiantree(ver->right);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    if (ver->left) {
        auto son = ver->left;
        int son_leftsz = countSize_Cartesiantree(son->left), son_rightsz = countSize_Cartesiantree(son->right);
        int x_left_son = x_left, x_right_son = x_cur;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    if (ver->right) {
        auto son = ver->right;
        int son_leftsz = countSize_Cartesiantree(son->left), son_rightsz = countSize_Cartesiantree(son->right);
        int x_left_son = x_cur, x_right_son = x_right;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    QGraphicsRectItem *white_cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    white_cur_ver_rect->setBrush(QBrush(Qt::white));
    scene->addItem(white_cur_ver_rect);
    QGraphicsRectItem *cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    //cur_ver_rect->setBrush(QBrush(Qt::black));
    scene->addItem(cur_ver_rect);
    QGraphicsTextItem *cur_ver_text = scene->addText(QString::number(ver->value));
    cur_ver_text->setPos(x_cur - NODE_RAD, y_cur - NODE_RAD);

    QString font_family = "Arial";
    cur_ver_text->setFont(QFont(font_family));
    int font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                              2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                     cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                                  2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                         cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    /*
     * Drawing children
     */
    if (ver->left) {
        drawProportional_Cartesiantree(ver->left, scene, x_left, x_cur, y_cur + Y_SHIFT);
    }
    if (ver->right) {
        drawProportional_Cartesiantree(ver->right, scene, x_cur, x_right, y_cur + Y_SHIFT);
    }
}

void drawProportional_AVLtree(AVLtree::Node *ver, QGraphicsScene *scene, int x_left, int x_right, int y_cur) {
    if (!ver)
        return;
    int leftsz = countSize_AVLtree(ver->left), rightsz = countSize_AVLtree(ver->right);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    qDebug() << "Drawn x_cur" << x_cur << x_left << x_right;
    /*
     * Drawing segments to children
     */
    if (ver->left) {
        auto son = ver->left;
        int son_leftsz = countSize_AVLtree(son->left), son_rightsz = countSize_AVLtree(son->right);
        int x_left_son = x_left, x_right_son = x_cur;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    if (ver->right) {
        auto son = ver->right;
        int son_leftsz = countSize_AVLtree(son->left), son_rightsz = countSize_AVLtree(son->right);
        int x_left_son = x_cur, x_right_son = x_right;
        int x_son_cur = x_left_son + (x_right_son - x_left_son) * (son_leftsz + 1) / (son_leftsz + 1 + son_rightsz + 1);
        int y_son_cur = y_cur + Y_SHIFT;
        scene->addLine(x_cur, y_cur, x_son_cur, y_son_cur);
    }
    /*
     * Drawing current node
     */
    QGraphicsRectItem *white_cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    white_cur_ver_rect->setBrush(QBrush(Qt::white));
    scene->addItem(white_cur_ver_rect);
    QGraphicsRectItem *cur_ver_rect = new QGraphicsRectItem(x_cur - NODE_RAD, y_cur - NODE_RAD, 2 * NODE_RAD, 2 * NODE_RAD);
    //cur_ver_rect->setBrush(QBrush(Qt::black));
    scene->addItem(cur_ver_rect);
    QGraphicsTextItem *cur_ver_text = scene->addText(QString::number(ver->value));
    cur_ver_text->setPos(x_cur - NODE_RAD, y_cur - NODE_RAD);

    QString font_family = "Arial";
    cur_ver_text->setFont(QFont(font_family));
    int font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                              2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                     cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    font_size = static_cast<int>(std::min(2.0 * NODE_RAD / cur_ver_text->boundingRect().width(),
                                                  2.0 * NODE_RAD / cur_ver_text->boundingRect().height()) *
                                         cur_ver_text->font().pointSize());
    cur_ver_text->setFont(QFont(font_family, font_size));
    /*
     * Drawing children
     */
    if (ver->left) {
        drawProportional_AVLtree(ver->left, scene, x_left, x_cur, y_cur + Y_SHIFT);
    }
    if (ver->right) {
        drawProportional_AVLtree(ver->right, scene, x_cur, x_right, y_cur + Y_SHIFT);
    }
}

std::pair<bool, int> find_by_coord_Splaytree(Splaytree::Node *ver, int x_click, int y_click, int x_left, int x_right, int y_cur) {
    if (!ver) {
        return {false, 0};
    }
    int leftsz = countSize_Splaytree(ver->left), rightsz = countSize_Splaytree(ver->right);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    if (std::max(abs(x_cur - x_click), abs(y_cur - y_click)) <= NODE_RAD) {
        return {true, ver->value};
    }
    if (ver->left) {
        auto get_from_son = find_by_coord_Splaytree(ver->left, x_click, y_click, x_left, x_cur, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }
    if (ver->right) {
        auto get_from_son = find_by_coord_Splaytree(ver->right, x_click, y_click, x_cur, x_right, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }

    return {false, 0};
}

std::pair<bool, int> find_by_coord_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex, int x_click, int y_click, int x_left, int x_right, int y_cur) {
    if (ver == &nilvertex) {
        return {false, 0};
    }
    int leftsz = countSize_RBtree(ver->left, nilvertex), rightsz = countSize_RBtree(ver->right, nilvertex);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    if (std::max(abs(x_cur - x_click), abs(y_cur - y_click)) <= NODE_RAD) {
        return {true, ver->value};
    }
    if (ver->left != &nilvertex) {
        auto get_from_son = find_by_coord_RBtree(ver->left, nilvertex, x_click, y_click, x_left, x_cur, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }
    if (ver->right != &nilvertex) {
        auto get_from_son = find_by_coord_RBtree(ver->right, nilvertex, x_click, y_click, x_cur, x_right, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }

    return {false, 0};
}

std::pair<bool, int> find_by_coord_Cartesiantree(Cartesiantree::Node *ver, int x_click, int y_click, int x_left, int x_right, int y_cur) {
    if (!ver) {
        return {false, 0};
    }
    int leftsz = countSize_Cartesiantree(ver->left), rightsz = countSize_Cartesiantree(ver->right);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    if (std::max(abs(x_cur - x_click), abs(y_cur - y_click)) <= NODE_RAD) {
        return {true, ver->value};
    }
    if (ver->left) {
        auto get_from_son = find_by_coord_Cartesiantree(ver->left, x_click, y_click, x_left, x_cur, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }
    if (ver->right) {
        auto get_from_son = find_by_coord_Cartesiantree(ver->right, x_click, y_click, x_cur, x_right, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }

    return {false, 0};
}

std::pair<bool, int> find_by_coord_AVLtree(AVLtree::Node *ver, int x_click, int y_click, int x_left, int x_right, int y_cur) {
    if (!ver)
        return {false, 0};
    int leftsz = countSize_AVLtree(ver->left), rightsz = countSize_AVLtree(ver->right);
    int x_cur = x_left + (x_right - x_left) * (leftsz + 1) / (leftsz + 1 + rightsz + 1);
    qDebug() << "Vertex coords are" << x_cur << y_cur;
    if (std::max(abs(x_cur - x_click), abs(y_cur - y_click)) <= NODE_RAD) {
        return {true, ver->value};
    }
    if (ver->left) {
        auto get_from_son = find_by_coord_AVLtree(ver->left, x_click, y_click, x_left, x_cur, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }
    if (ver->right) {
        auto get_from_son = find_by_coord_AVLtree(ver->right, x_click, y_click, x_cur, x_right, y_cur + Y_SHIFT);
        if (get_from_son.first)
            return get_from_son;
    }
    return {false, 0};
}

std::vector<int> from_str_to_numbers(QString str) {
    QString cur_str = "";
    str += ' ';
    std::vector<int> ans;
    for (int ind = 0; ind < static_cast<int>(str.size()); ++ind) {
        if (str[ind] == ' ') {
            ans.push_back(cur_str.toInt());
            cur_str = "";
        } else {
            cur_str += str[ind];
        }
    }

    return ans;
}

bool MainWindow::correct_input(QString str) {
    QString new_str = str;
    new_str = new_str.simplified();
    new_str.replace( " ", "");
    for (int ind = 0; ind < static_cast<int>(new_str.size()); ++ind) {
        if (!(new_str[ind] >= '0' && new_str[ind] <= '9')) {
            QMessageBox msgBox;
            msgBox.setText("Введите числа");
            msgBox.exec();
            ui->valueVertexInput->setText("");

            return false;
        }
    }

    std::vector<int> values_array = from_str_to_numbers(str);
    for (int ind = 0; ind < static_cast<int>(values_array.size()); ++ind) {
        if (avl_tree._is_exists(values_array[ind])) {
            QString number;
            number.setNum(values_array[ind]);
            QMessageBox msgBox;
            msgBox.setText("Число " + number + " уже есть в дереве");
            msgBox.exec();
            ui->valueVertexInput->setText("");

            return false;
        }
    }

    return true;
}

void MainWindow::on_getIputVertexButton_clicked() {
    QString values_str = ui->valueVertexInput->text();
    if (!correct_input(values_str)) {
        return;
    }
    std::vector<int> values_array = from_str_to_numbers(values_str);
    ui->valueVertexInput->setText("");
//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
//    view_zoom = new Graphics_view_zoom(ui->graphicsView);
//    view_zoom->set_modifiers(Qt::NoModifier);
    for (int ind = 0; ind < static_cast<int>(values_array.size()); ++ind) {
        avl_tree._insert(values_array[ind]);
        rb_tree._insert(values_array[ind]);
        cart_tree._insert(values_array[ind]);
        splay_tree._insert(values_array[ind]);
        all_elem.insert(values_array[ind]);
    }
//    QObject::connect(scene, &GraphicsScene_clickable::scene_clicked, this, &MainWindow::deleting_vertex);
    redraw_cur_tree();
    ui->graphicsView->repaint();
    ui->valueVertexInput->repaint();
}

void MainWindow::on_getCortesiantreeButton_clicked() {
    cur_tree = TreeState::CartesianTree;
    ui->getCortesiantreeButton->setStyleSheet("background-color: pink");
    ui->getAVLtreeButton->setStyleSheet("background-color : lightGray");
    ui->getRBtreeButton->setStyleSheet("background-color : lightGray");
    ui->getSplaytreeButton->setStyleSheet("background-color : lightGray");
    redraw_cur_tree();
}

void MainWindow::on_getAVLtreeButton_clicked() {
    cur_tree = TreeState::AVLtree;
    ui->getAVLtreeButton->setStyleSheet("background-color: pink");
    ui->getCortesiantreeButton->setStyleSheet("background-color : lightGray");
    ui->getRBtreeButton->setStyleSheet("background-color : lightGray");
    ui->getSplaytreeButton->setStyleSheet("background-color : lightGray");
    redraw_cur_tree();
}

void MainWindow::on_getRBtreeButton_clicked() {
    cur_tree = TreeState::RBtree;
    ui->getRBtreeButton->setStyleSheet("background-color: pink");
    ui->getCortesiantreeButton->setStyleSheet("background-color : lightGray");
    ui->getAVLtreeButton->setStyleSheet("background-color : lightGray");
    ui->getSplaytreeButton->setStyleSheet("background-color : lightGray");
    redraw_cur_tree();
}

void MainWindow::on_getSplaytreeButton_clicked() {
    cur_tree = TreeState::SplayTree;
    ui->getSplaytreeButton->setStyleSheet("background-color: pink");
    ui->getCortesiantreeButton->setStyleSheet("background-color : lightGray");
    ui->getAVLtreeButton->setStyleSheet("background-color : lightGray");
    ui->getRBtreeButton->setStyleSheet("background-color : lightGray");
    redraw_cur_tree();
}

void MainWindow::on_clearButton_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();
    for (auto elem : all_elem) {
        //qDebug() << all_elem[ind];
        avl_tree._erase(elem);
        qDebug() << "ok1";
        rb_tree._erase(elem);
        qDebug() << "ok2";
        cart_tree._erase(elem);
        qDebug() << "ok3";
        splay_tree._erase(elem);
    }

    all_elem.clear();
}

