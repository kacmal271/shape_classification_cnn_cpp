#include "ConsoleInterface.h"

//*****************************************************************************

std::string ConsoleInterface::read()
{
  std::string reading = "";
  std::string tmp;

  this->clear();

  // '\n' is read and discarded from the keyboard buffer
  std::getline(std::cin, reading);

  return reading;
}

//*****************************************************************************

void ConsoleInterface::clear()
{
  //
  // istream& ignore (streamsize n = 1, int delim = EOF);
  //
  // std::cin.ignore()
  // discard characters from a formatted istream (line std::cin itself)
  //
  // std::numeric_limits<std::streamsize>::max()
  // represents the largest possible number you can count with "streamsize"
  // in practice: +infinity
  // 
  // '\n'
  // we ignore all characters until (including!) the new line
  // then we leave the remains of the buffer
  //
  // all inside: #include <iostream>
  // which includes: #include <limits>
  //
  // int delim = -1 (or enum EOF)
  // ignore all characters until EOF character (including EOF!)
  // here there is no file, there is just keyboard buffer
  // the program will never terminate executing ¯\_(ツ)_/¯
  
  // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cin >> std::ws;
}
