#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include "./Helper/declarations_q.h"
#include "./Helper/declarations.h"

namespace Ui
{
  class ChartWindow;
}

class ChartWindow : public QWidget
{
    Q_OBJECT

  private:

    Ui::ChartWindow *ui;

  public:

    explicit ChartWindow(QString seriesTitle,
                         QString chartTitle,
                         initializerQString categoryTitles,
                         initializerDouble values,
                         double min,
                         double max,
                         QWidget *parent = nullptr);

    ~ChartWindow();

    void displayChart(QString seriesTitle,
                      QString chartTitle,
                      initializerQString categoryTitles,
                      initializerDouble values,
                      double min,
                      double max) const;
};

#endif // CHARTWINDOW_H
