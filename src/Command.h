/*
 * Command.h
 *
 *  Created on: Mar 31, 2016
 *      Author: nczempin
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <getopt.h>
#include <memory>
#include <vector>

#include "MyGit.h"

//class CommandParameter;

using namespace std;

class Command
{
public:
  Command(shared_ptr<MyGit> mg);
  virtual ~Command();
  virtual void execute() = 0;
  virtual string getShortOptions() = 0;
	virtual vector<option> getLongOptions() = 0; //TODO dependency on getopt
  virtual void do_long_option(bool flag, string name, string argument) = 0;
  virtual void do_short_option(int c, string argument) = 0;
 // virtual shared_ptr<CommandParameter> createCommandParameter() = 0;
protected:
  shared_ptr<MyGit> receiver;

};

#endif /* COMMAND_H_ */
