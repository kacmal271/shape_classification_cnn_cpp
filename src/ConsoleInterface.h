#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include <iostream>
#include <string>

#include "Interface.h"

class ConsoleInterface : Interface
{

  public:

    std::string read();

    //*****************************************************************************

    template <typename T>
    void log(T message = T {}, bool prependNewLine = true)
    {
      if (prependNewLine)
      {
        std::cout << std::endl;
      }

      std::cout << message;
    }
    
  protected:

    void clear();
};

#endif // CONSOLEINTERFACE_H
