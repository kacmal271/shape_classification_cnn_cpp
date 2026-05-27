#include "mainwindow.h"
#include "./ui_mainwindow.h"

//*****************************************************************************

QImage MainWindow::loadImage()
{
  std::optional<QString> filePath = this->openFileDialog(this);

  // std::optional::operator!()

  if ( ! filePath)
  {
    // [todo] message box "please select an image"

    throw 1;
  }

  // std::optional::operator*()
  QString filePathAsString = *filePath;

  QImage image(filePathAsString);

  if (image.isNull())
  {
    // [todo] message box: "cannot load the image"

    throw 1;
  }

  return image;
}

//*****************************************************************************

std::optional<QString> MainWindow::openFileDialog(QWidget *parent)
{
  QString filePath = QFileDialog::getOpenFileName(
    // in which window are we opening ?
    parent,

    // dialog window title
    "Please select the image to classify",

    // start directory
    QString {},

    // filter label
    // you can define AT MOST 1 filter here
    "JPG (*.jpg)"
    );

  if (filePath.isEmpty())
  {
    // null from std::optional
    // nullopt-ional
    return std::nullopt;
  }

  return filePath;

}

//*****************************************************************************

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

//*****************************************************************************

MainWindow::~MainWindow()
{
  delete ui;
}

//*****************************************************************************

void MainWindow::on_pushButton_clicked()
{
  QImage image { loadImage() };

  // Tensor3D tensor QHelper::QTensorAdapter::convert(QImage);

  // ConvNet cnn { "./cnn_serialized.csv" };

  // cnn.classify(tensor);

  initializerDouble values { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.2 };

  ChartWindow * chartWindow
    {
      new ChartWindow(

        "Decision class scores",

        "Scores Chart",

        {
          "circle",
          "kite",
          "parallelogram",
          "rectangle",
          "rhombus",
          "square",
          "trapezoid",
          "triangle"
        },

        values,

        0,

        1)
    };

  chartWindow->show();

}
