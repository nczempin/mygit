#ifndef CAT_FILE_H_
#define CAT_FILE_H_

/*

 * Cat_file.h

 *
 *  Created on: Apr 3, 2016
 *      Author: nczempin
 */

#include <memory>
#include <string>

#include "Abstract_command.h"
#include "Command_receiver.h"

using namespace std;

class Cat_file: public Abstract_command
{
public:
  Cat_file(shared_ptr<Command_receiver> mygit);
  virtual ~Cat_file();

  void execute();
  string get_short_options();
  vector<option> get_long_options(); // TODO dependency on getopt
  void do_long_option(bool flag, string name, string argument);
  void do_short_option(int c, string argument);
//  shared_ptr<CommandParameter> createCommandParameter();

private:

  stringstream uncompress(const string& path);

  void set_option_type(bool option_type);

  bool option_type;
};

#endif /* CAT_FILE_H_ */
