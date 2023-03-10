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

#include "Command.h"
#include "MyGit.h"

using namespace std;

class Hash_object: public Command
{
public:
  Hash_object(shared_ptr<MyGit> mygit);
  virtual ~Hash_object();

  void execute();
  string getShortOptions();
  void do_long_option(bool flag, string name, string argument);
  void do_short_option(int c, string argument);
  private:
  shared_ptr<MyGit> mygit;
};

#endif /* HASHOBJECT_H_ */
