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

#include "Abstract_command.h"
#include "Command_receiver.h"

using namespace std;
class Rev_parse: public Abstract_command
{
public:
  Rev_parse(shared_ptr<Command_receiver> mygit);
  virtual ~Rev_parse();

  void execute();
  string get_short_options();
  vector<option> get_long_options(); //TODO dependency on getopt
  void do_long_option(bool flag, string name, string argument);
  void do_short_option(int c, string argument);
  // virtual shared_ptr<CommandParameter> createCommandParameter();
};

#endif /* REV_PARSE_H_ */
