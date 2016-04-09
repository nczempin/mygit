#ifndef HASHOBJECT_H_
#define HASHOBJECT_H_

/*

 * Hashobject.h

 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include <memory>
#include <string>

#include "Abstract_command.h"
#include "Command_receiver.h"


using namespace std;

class Hash_object: public Abstract_command
{
public:
  Hash_object(shared_ptr<Command_receiver> mygit);
  virtual ~Hash_object();

  void execute();
  string get_short_options();
  vector<option> get_long_options(); // TODO dependency on getopt
  void do_long_option(bool flag, string name, string argument);
  void do_short_option(int c, string argument);
  //shared_ptr<CommandParameter> createCommandParameter();
};

#endif /* HASHOBJECT_H_ */
