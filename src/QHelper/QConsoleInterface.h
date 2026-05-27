#ifndef QCONSOLEINTERFACE_H
#define QCONSOLEINTERFACE_H

#include <QDebug>

#include "../ConsoleInterface.h"
#include "../Helper/definitions.h"

namespace QHelper { class QConsoleInterface; };

extern QHelper::QConsoleInterface console;

namespace QHelper
{

  class QConsoleInterface : public ConsoleInterface
  {
    public:

      //*****************************************************************************

      template <typename T>
      void log(T message = T {}, bool appendExtraLine = false)
      {
        qDebug().noquote() << message;

        if (appendExtraLine)
        {
          qDebug().noquote() << "";
        }
      }
  };

} // namespace QHelper

#endif // QCONSOLEINTERFACE_H
