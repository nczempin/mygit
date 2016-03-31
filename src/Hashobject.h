/*
 * Hashobject.h

 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */
#include "Command.h"
#include <string>

using namespace std;

#ifndef HASHOBJECT_H_
#define HASHOBJECT_H_

class Hash_object: Command
{
public:
  Hash_object(MyGit& mygit);
  virtual ~Hash_object();

  void execute();

private:
  MyGit& mygit;
};

#endif /* HASHOBJECT_H_ */
