/*
 * Zlib_facade.h
 *
 *  Created on: Apr 6, 2016
 *      Author: nczempin
 */

#ifndef ZLIB_FACADE_H_
#define ZLIB_FACADE_H_

#include <string>
#include <sstream>

using namespace std;

class Zlib_facade
{
public:
  Zlib_facade();
  virtual ~Zlib_facade();

  static stringstream uncompress(const string& path);
};

#endif /* ZLIB_FACADE_H_ */
