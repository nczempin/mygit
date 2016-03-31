/*
 * Command.h
 *
 *  Created on: Mar 31, 2016
 *      Author: nczempin
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
using namespace std;

class Command
{
public:
  Command();
  virtual ~Command();
  virtual void execute() = 0;
  virtual string getShortOptions() = 0;
};

#endif /* COMMAND_H_ */
