/*
 * Rev_parse.h
 *
 *  Created on: Apr 8, 2016
 *      Author: nczempin
 */

#ifndef REV_PARSE_H_
#define REV_PARSE_H_

#include <memory>
#include <string>

#include "Command.h"
#include "MyGit.h"

using namespace std;
class Rev_parse: public Command
{
public:
  Rev_parse(shared_ptr<MyGit> mygit);
  virtual ~Rev_parse();

  void execute();
  string getShortOptions();
  vector<option> getLongOptions(); //TODO dependency on getopt
  void do_long_option(bool flag, string name, string argument);
  void do_short_option(int c, string argument);
  // virtual shared_ptr<CommandParameter> createCommandParameter();
};

#endif /* REV_PARSE_H_ */
