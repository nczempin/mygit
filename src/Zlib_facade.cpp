/*
 * Zlib_facade.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: nczempin
 */

#include "Zlib_facade.h"

Zlib_facade::Zlib_facade()
{
  // TODO Auto-generated constructor stub

}

Zlib_facade::~Zlib_facade()
{
  // TODO Auto-generated destructor stub
}

stringstream Zlib_facade::uncompress(const string& path)
{
  //  FILE* pFile;
  //  pFile = fopen(path.c_str(), "r");
  //  if (pFile == NULL) {
  //    cout << "error1" << endl;
  //    throw 1; //TODO
  //  } else {
  //    int zerr;
  //    if (option_type) {
  //      zerr = inf_header(pFile, stdout);
  //    } else {
  //      zerr = inf(pFile, stdout);
  //    }
  //    fclose(pFile);
  //    if (zerr != Z_OK) {
  //      cout << "error2" << endl;
  //      throw 2; //TODO
  //    }
  //  }
  stringstream temp;
  temp << "hello from facade";
  return temp;
}
