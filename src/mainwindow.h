#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <optional>

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>

#include "./ChartWindow.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
  class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  private:

    Ui::MainWindow *ui;

  public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    std::optional<QString> openFileDialog(QWidget *parent);

    QImage loadImage();

  private slots:

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
