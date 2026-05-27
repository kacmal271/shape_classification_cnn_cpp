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
    void log(T message = T {}, bool appendNewLine = true)
    {
      std::cout << message;

      if (appendNewLine)
      {
        std::cout << std::endl;
      }

      std::cout << std::flush;
    }
    
  protected:

    void clear();
};

#endif // CONSOLEINTERFACE_H
