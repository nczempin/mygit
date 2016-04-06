/*
 * MyGit.h
 *
 *  Created on: Mar 31, 2016
 *      Author: nczempin
 */

#ifndef MYGIT_H_
#define MYGIT_H_

#include <iostream>
#include <string>

using namespace std;
class MyGit
{
public:
  MyGit();
  virtual ~MyGit();
  void setPath(string p)
  {
    path = p;
  }
  string getPath()
  {
    return path;
  }
private:
  string path;
};

#endif /* MYGIT_H_ */
