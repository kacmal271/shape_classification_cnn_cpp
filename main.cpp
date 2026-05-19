#include "./src/mainwindow.h"

#include "./src/Helper/test.h"
#include "./src/Testing/TensorTest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  test(new Testing::TensorTest {});

  QApplication a(argc, argv);

  MainWindow w;

  w.show();

  return a.exec();
}
