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

#include "Command.h"
#include "MyGit.h"
#include "CommandParameter.h"

using namespace std;

class Cat_file: public Command
{
public:
  Cat_file(shared_ptr<MyGit> mygit);
  virtual ~Cat_file();

  void execute();
  string getShortOptions();
  vector<option> getLongOptions(); // TODO dependency on getopt
  void do_long_option(bool flag, string name, string argument);
  void do_short_option(int c, string argument);
  shared_ptr<CommandParameter> createCommandParameter();

private:
  shared_ptr<MyGit> mygit;

  string get_absolute_cwd();
};

#endif /* CAT_FILE_H_ */
