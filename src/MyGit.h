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
#include <vector>

using namespace std;
class MyGit
{
public:
  MyGit();
  virtual ~MyGit();
  void setPath(vector<string> p)
  {
    path = p;
  }
  vector<string> getPath()
  {
    return path;
  }
private:
  vector<string> path;
};

#endif /* MYGIT_H_ */
