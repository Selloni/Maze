#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "../../Controller/controller.h"


#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QTimer>

////


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    s21::Controller controller_;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:

    void on_tabWidget_currentChanged(int index);

    void on_Step_clicked();

    void on_c_life_2_valueChanged(int arg1);

    void on_c_dead_2_valueChanged(int arg1);

    void on_Time_clicked();

    void on_c_Generate_clicked();

    void on_c_SaveFile_clicked();

    void on_c_OpenFile_clicked();

    void on_m_Generate_clicked();

    void on_m_SaveFile_clicked();

    void on_m_OpenFile_clicked();

    void on_SolveCave_clicked();

private:

    void PaintCave();
    void PaintMaze();
    void PaintPathMaze();
    void DoTimer();
    void PaintPathCave();

    QGraphicsScene *field_ = new QGraphicsScene(0,0,500,500);

    Ui::MainWindow *ui;
    s21::CaveGenerationSettings settings_cave_{};
    s21::MazeGenerationSettings setting_maze_{};
    s21::MazeWrapper data_maze_{};
    s21::CaveWrapper data_cave_{};
    int count_clic_mouse_ = 0;
    bool is_cave_ = 1;
    s21::Point input_{}, output_{};
    QTimer* timer_ = new QTimer;

};
#endif // MAINWINDOW_H
