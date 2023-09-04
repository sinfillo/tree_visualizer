#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "avltree.h"
#include "rbtree.h"
#include "cartesiantree.h"
#include "graphicsscene_clickable.h"
#include "Graphics_view_zoom.h"
#include <set>
#include "splaytree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void deleting_vertex(QPointF delete_point);
private slots:
    void on_getIputVertexButton_clicked();
    void on_getCortesiantreeButton_clicked();
    void on_getAVLtreeButton_clicked();
    void on_getRBtreeButton_clicked();
    void on_clearButton_clicked();

    void on_getSplaytreeButton_clicked();

private:
    Ui::MainWindow *ui;
    AVLtree avl_tree;
    RBtree rb_tree;
    Cartesiantree cart_tree;
    Splaytree splay_tree;
    enum class TreeState {AVLtree, RBtree, CartesianTree, SplayTree};
    TreeState cur_tree = TreeState::AVLtree;
    GraphicsScene_clickable *scene = new GraphicsScene_clickable();
    Graphics_view_zoom* view_zoom;
    void redraw_cur_tree();
    bool correct_input(QString str);
    std::set<int> all_elem;
};

extern int NODE_RAD, Y_SHIFT;
int countSize_AVLtree(AVLtree::Node *ver);
int countHeight_AVLtree(AVLtree::Node *ver);
void drawProportional_AVLtree(AVLtree::Node *ver, QGraphicsScene *scene, int x_left, int x_right, int y_cur);
std::pair<bool, int> find_by_coord_AVLtree(AVLtree::Node *ver, int x_click, int y_click, int x_left, int x_right, int y_cur);

void fit_scene_in_view(QGraphicsView *view);
std::vector<int> from_str_to_numbers(QString str);

void drawProportional_Cartesiantree(Cartesiantree::Node * ver, QGraphicsScene *scene, int x_left, int x_right, int y_cur);
int countSize_Cartesiantree(Cartesiantree::Node *ver);
int countHeight_Cartesiantree(Cartesiantree::Node *ver);
std::pair<bool, int> find_by_coord_Cartesiantree(Cartesiantree::Node* ver, int x_click, int y_click, int x_left, int x_right, int y_cur);

int countSize_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex);
int countHeight_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex);
void drawProportional_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex, QGraphicsScene *scene, int x_left, int x_right, int y_cur);
std::pair<bool, int> find_by_coord_RBtree(RBtree::Node*& ver, RBtree::Node& nilvertex, int x_click, int y_click, int x_left, int x_right, int y_cur);

int countSize_Splaytree(Splaytree::Node *ver);
int countHeight_Splaytree(Splaytree::Node *ver);
void drawProportional_Splaytree(Splaytree::Node*ver, QGraphicsScene *scene, int x_left, int x_right, int y_cur);
std::pair<bool, int> find_by_coord_Splaytree(Splaytree::Node* ver, int x_click, int y_click, int x_left, int x_right, int y_cur);

#endif // MAINWINDOW_H
