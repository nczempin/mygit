/*
 * Hashobject.h

 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include <string>

using namespace std;

#ifndef HASHOBJECT_H_
#define HASHOBJECT_H_

class Hash_object
{
public:
  Hash_object();
  virtual ~Hash_object();

  void set_parameter(string param);
  void execute_command();

private:
  string path;
};

#endif /* HASHOBJECT_H_ */
