#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(is_cave_);
    on_m_Generate_clicked();
    on_c_Generate_clicked();


    connect(timer_, &QTimer::timeout, this, &MainWindow::DoTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete field_;
    delete timer_;
}

void MainWindow::DoTimer() {
    on_Step_clicked();
}

void MainWindow::on_Time_clicked()
{
    if (!timer_->isActive())
        timer_->start(ui->c_second->value());
    else
        timer_->stop();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    is_cave_ = index;
    if (index) 
        on_c_Generate_clicked();
     else
        on_m_Generate_clicked();
    timer_->stop();
}


void  MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x_step = 0,y_step = 0;
    if (is_cave_)
        x_step = 500/settings_cave_.cols, y_step = 500/settings_cave_.rows;
    else
        x_step = 500/setting_maze_.cols, y_step = 500/setting_maze_.rows;
    int x = event->x()/x_step * x_step + x_step/4;
    int y = event->y()/y_step * y_step + y_step/4;
    if (event->button() == Qt::LeftButton) {
        if ((event->x() > 0 && event->x() < 500)
            && (event->y() > 0 && event->y() < 500)) {
            input_.x = event->x()/x_step, input_.y = event->y()/y_step;
            field_->addRect(x, y, x_step/2, y_step/2)->setBrush(QColor(0,128,0));
        }
        count_clic_mouse_++;
    } else if (event->button() == Qt::RightButton) {
        if ((event->x() > 0 && event->x() < 500)
            && (event->y() > 0 && event->y() < 500)) {
            output_.x = event->x()/x_step, output_.y = event->y()/y_step;
            field_->addRect(x, y, x_step/2, y_step/2)->setBrush(QColor(128, 0, 0));
        }
        count_clic_mouse_++;
    }
    if (count_clic_mouse_ < 2) return;
    if (is_cave_)
        PaintPathCave();
    else
        PaintPathMaze();

}


void MainWindow::PaintPathCave()
{
    PaintCave();
    int px_x = 0, px_y = 0;
    int step_x = 500/data_cave_.cols, step_y = 500/data_cave_.rows;
    auto path = controller_.Solve(data_cave_, s21::Point{input_.y,input_.x}, s21::Point{output_.y,output_.x});
    auto is_there = [path](std::size_t crow, std::size_t ccol) {
        for (auto [row, col] : path) {
            if (row == crow and col == ccol)
                return true;
        }
        return false;
    };
      for (int i = 0; i < data_cave_.rows; ++i) {
          px_x = 0;
          for (int j = 0; j < data_cave_.cols; ++j) {
              if (is_there(i, j)) {
                  field_->addEllipse(px_x+step_x/4, px_y+step_y/4, step_x/2, step_y/2)->setBrush(QColor(0, 0, 255));
              }
              px_x+=step_x;
          }
          px_y+=step_y;
  }
}

void MainWindow::on_Step_clicked()
{
        settings_cave_.born_limit = std::make_pair(ui->c_dead->value(), ui->c_dead_2->value());
        settings_cave_.live_limit = std::make_pair(ui->c_life->value(), ui->c_life_2->value());
        settings_cave_.generation_count = 1;
        data_cave_ = controller_.Generate<s21::kCave>(settings_cave_, data_cave_);
        PaintCave();
}

void MainWindow::PaintCave() {
    if (data_cave_.IsGood()) {
        field_->clear();
        ui->graph->setScene(field_);
        field_->addRect(field_->sceneRect());
        ui->graph->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graph->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        double px_x = 0;
        double px_y = 0;
        double step_x = 500/data_cave_.cols;
        double step_y = 500/data_cave_.rows;
        for (int i = 0; i != data_cave_.rows; ++i) {
            px_x = 0;
            for (int j = 0; j != data_cave_.cols; ++j) {
                if(data_cave_(i,j)) {
                      field_->addRect( px_x, px_y, step_x, step_y)->setBrush(Qt::black);
                }
                px_x += step_x ;
            }
            px_y += step_y ;
        }
    } else {
        QMessageBox::information(this, tr("Info"), "Приятель, вводи валидные даные\n\n"
                                                                   "      ╭(ರ⌓ರ)╮ \n\n\n...Нурислама не обмануть, дурень ...");
    }
}



void MainWindow::on_c_life_2_valueChanged(int arg1)
{
    ui->c_life_2->setMinimum(ui->c_life->value());
}


void MainWindow::on_c_dead_2_valueChanged(int arg1)
{
    ui->c_dead_2->setMinimum(ui->c_dead->value());
}

void MainWindow::on_c_Generate_clicked()
{
    settings_cave_.born_limit = std::make_pair(ui->c_dead->value(), ui->c_dead_2->value());
    settings_cave_.live_limit = std::make_pair(ui->c_life->value(), ui->c_life_2->value());
    settings_cave_.live_chance = ui->life_change->value();
    settings_cave_.cols = ui->c_cols->value();
    settings_cave_.rows = ui->c_rows->value();
    settings_cave_.generation_count = ui->c_popul->value();
    data_cave_ = controller_.Generate<s21::kCave>(settings_cave_);
    count_clic_mouse_ = 0;
    PaintCave();
}

void MainWindow::on_c_SaveFile_clicked()
{
    QString save_path = QFileDialog::getSaveFileName(
          this, tr("You're cute"), QDir::homePath(), tr("more_fun (*.txt)"));
    std::string path_str = save_path.toStdString();
    controller_.SaveFile<s21::kCave>(data_cave_, path_str);
}


void MainWindow::on_c_OpenFile_clicked()
{
    QString path_for_file = QFileDialog::getOpenFileName(0, "Open File", "/Users/", "*.txt");
    std::string path_str = path_for_file.toStdString();
    if (path_str.empty()) return;
    data_cave_  = controller_.ReadFile<s21::kCave>(path_str);
    PaintCave();
}



void MainWindow::on_SolveCave_clicked()
{
    PaintPathCave();
}

void MainWindow::PaintMaze()
{
    if (data_maze_.IsGood()) {
        field_->clear();
        QPen pen;
        pen.setWidth(2);
        double line_x = 500/data_maze_.cols;
        double line_y = 500/data_maze_.rows;
        double step_x = 0;
        double step_y = 0;
        field_->addLine(0,0,0,500);
        field_->addLine(0,0,500,0);
        for (int i = 0; i != data_maze_.rows; ++i) {
                for (int j = 0; j != data_maze_.cols; ++j) {
                    if (data_maze_(i, j) == 0 and data_maze_(i, j, false) == 0) {
                        step_x += line_x;
                    } else if (data_maze_(i, j) == 1 and data_maze_(i, j, false) == 1) {
                        field_->addLine(step_x+line_x, step_y, step_x+line_x, step_y+line_y)->setPen(pen);
                        field_->addLine(step_x, step_y+line_y, step_x+line_x , step_y+line_y)->setPen(pen);
                        step_x+=line_x;
                    } else if (data_maze_(i, j) == 1 and data_maze_(i, j, false) == 0) {
                        step_x+=line_x;
                        field_->addLine(step_x, step_y, step_x, step_y+line_y)->setPen(pen);
                    } else if (data_maze_(i, j) == 0 and data_maze_(i, j, false) == 1) {
                        field_->addLine(step_x, step_y+line_y, step_x+line_x , step_y+line_y)->setPen(pen);
                        step_x += line_x;
                    }
                }
                 step_y += line_y;
                 step_x = 0;
        }
    } else {
        QMessageBox::information(this, tr("Info"), "Приятель, вводи валидные даные\n\n"
                                                                   "      ╭(ರ⌓ರ)╮ \n\n\n...Нурислама не обмануть, дурень ...");
    }
}

void MainWindow::PaintPathMaze() {
    PaintMaze();
    int px_x = 0, px_y = 0;
    int step_x = 500/data_maze_.cols, step_y = 500/data_maze_.rows;
    auto path = controller_.Solve(data_maze_, s21::Point{input_.y,input_.x}, s21::Point{output_.y,output_.x});
    auto is_there = [path](std::size_t crow, std::size_t ccol) {
        for (auto [row, col] : path) {
            if (row == crow and col == ccol)
                return true;
        }
        return false;
    };
      for (int i = 0; i < data_maze_.rows; ++i) {
          px_x = 0;
          for (int j = 0; j < data_maze_.cols; ++j) {
              if (is_there(i, j)) {
                  field_->addRect(px_x+step_x/4, px_y+step_y/4, step_x/2, step_y/2)->setBrush(QColor(0, 0, 255));
              }
              px_x+=step_x;

          }
          px_y+=step_y;
  }


}


void MainWindow::on_m_Generate_clicked()
{
    setting_maze_.cols = ui->m_cols->value();
    setting_maze_.rows = ui->m_rows->value();
    data_maze_ = controller_.Generate<s21::kMaze>(setting_maze_);
    PaintMaze();
    count_clic_mouse_ = 0;
}


void MainWindow::on_m_SaveFile_clicked()
{
    QString save_path = QFileDialog::getSaveFileName(
          this, tr("You're cute"), QDir::homePath(), tr("more_fun (*.txt)"));
    std::string path_str = save_path.toStdString();
    controller_.SaveFile<s21::kMaze>(data_maze_, path_str);
}


void MainWindow::on_m_OpenFile_clicked()
{
    QString path_for_file = QFileDialog::getOpenFileName(0, "Open File", "/Users/", "*.txt");
    std::string path_str = path_for_file.toStdString();
    if (path_str.empty()) return;
    data_maze_ = controller_.ReadFile<s21::kMaze>(path_str);
    PaintMaze();
}



