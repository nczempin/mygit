/*
 * Utils.h
 *
 *  Created on: Apr 8, 2016
 *      Author: nczempin
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stddef.h>
#include <string>
#include <iostream>
//TODO Factor out these C libraries
#include <dirent.h>
#include <getopt.h>
#include <unistd.h>

#include <cstring>

using namespace std;

class Utils
{
public:
  Utils();
  virtual ~Utils();
  static string getWorkareaRoot()
  {
    // 1. determine .git path
    //    a. determine absolute path of current directory
    string name(".git");
    bool found = false;
    bool done = false;
    string path = Utils::get_absolute_path(".");
    while (!found && !done) {
      //cout << "cwd: " << path << endl;
      //    b. recurse up until one directory contains a .git dir
      //(TODO: what to do when inside .git?)
      //      i. check current directory
      found = find_dir(name, path);
      if (found) {
        break;
      }
      //        ii. if not found at the top, we are not inside a git workdir
      size_t pos = path.find_last_of("/"); //TODO platform-specific
      if (pos == string::npos) {
        done = true;
      }
      path = path.substr(0, pos);
    }
    //        iii. if not found, go up the tree
    if (done) {
      cout
          << "fatal: Not a git repository (or any of the parent directories): .git"
          << endl;
      throw 128;
    }
    return path;
  }
  static string get_absolute_path(string path)
  {
    // 1. determine .git path
    //    a. determine absolute path of current directory
    long size = 255;
    char* buf;
    char* ptr;
    size = pathconf(path.c_str(), _PC_PATH_MAX);
    if ((buf = (char*) (malloc((size_t) (size)))) != NULL) {
      ptr = getcwd(buf, (size_t) (size));
    }
    string cwd(ptr);
    return cwd;
  }

  static bool find_dir(string name, string dirpath)
  {
    DIR *dirp = opendir(dirpath.c_str());

    dirent* dp;
    bool found = false;
    while ((dp = readdir(dirp)) != NULL) {
      if (!strcmp(dp->d_name, name.c_str())) { //TODO strcmp is C, not C++
        found = true;
        break;
      }
    }
    closedir(dirp);
    return found;
  }
};

#endif /* UTILS_H_ */
