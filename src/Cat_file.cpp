/*
 * Hashobject.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include "Cat_file.h"

#include <dirent.h>
#include <getopt.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Cat_file::Cat_file(shared_ptr<MyGit> mg) :
    mygit(mg)
{
}

Cat_file::~Cat_file()
{
  // TODO Auto-generated destructor stub
}

string Cat_file::get_absolute_cwd()
{
  // 1. determine .git path
  //    a. determine absolute path of current directory
  long size = 255;
  char* buf;
  char* ptr;
  size = pathconf(".", _PC_PATH_MAX);
  if ((buf = (char*) (malloc((size_t) (size)))) != NULL) {
    ptr = getcwd(buf, (size_t) (size));
  }
  string cwd(ptr);
  return cwd;
}

bool Cat_file::find_dir(const char* name, const char* dirpath)
{
  DIR *dirp = opendir(dirpath);

  int len = strlen(name);
  dirent* dp;
  bool found = false;
  while ((dp = readdir(dirp)) != NULL) {
    cout << "is it " << dp->d_name << endl;
    if (!strcmp(dp->d_name, name)) {
      found = true;
      break;
    }
  }
  closedir(dirp);
  return found;
}

std::vector<std::string> &split(const std::string &s, char delim,
    std::vector<std::string> &elems)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}
void Cat_file::execute()
{
  // 1. determine .git path
  //    a. determine absolute path of current directory
  string cwd = get_absolute_cwd();
  cout << "cwd: " << cwd << endl;
  const char* name = ".git";
  const char* dirpath = cwd.c_str();
  //    b. recurse up until one directory contains a .git dir (TODO: what to do when inside .git?)
  //      i. check current directory
  bool found = find_dir(name, dirpath);
  if (!found) {
    cout << "Not ";
  }
  cout << "found!" << endl;
  //        ii. if not found, go up the tree
  //        iii. if not found at the top, we are not inside a git workdir
  if (!found) {
    cout
    << "fatal: Not a git repository (or any of the parent directories): .git"
        << endl;
    throw 128;
  }
  // 2. convert sha1 param into path relative from .git
  // 3. read that file
  // 4. uncompress it
  // 5. display it

  ifstream myfile;

  string path = mygit->getPath();
  cout << "working with: " << path << endl;
  myfile.open(path);
  ostringstream file_contents;
  if (myfile.is_open()) {
    string line;
    //TODO use proper buffering, especially for large files
    while (getline(myfile, line)) {
      file_contents << line << '\n';
    }
    myfile.close();
  } else {
    throw 128;
  }
  string file_string = file_contents.str();
  // Add the git specific text, "blob " plus size of the original blob (file)
  string blobTxt = "blob " + to_string(file_string.size());
  string combined = blobTxt + '\0' + file_string;
  const char* str = combined.c_str();
  int l = combined.length();
  // convert to sha1

}

void Cat_file::do_long_option(bool flag, string name, string argument)
{
  if (flag) {
    cout << "flag" << endl;
  }
  cout << "name: " << name << endl;
  cout << "argument: " << argument << endl;
}

string Cat_file::getShortOptions()
{
  return "tsep";
}
vector<option> Cat_file::getLongOptions()
{
  vector<option> retval =
        {
            {
              "textconv",
              no_argument, 0, 0
            }
        };
  return retval;
}
void Cat_file::do_short_option(int c, string argument)
{
  switch (c) {
  case 'w':
    cout << "option -w" << endl;
    break;
  case 't':
    cout << "option -t with value `" << argument << "'\n" << endl;
    break;
  case '?':
    /* getopt_long already printed an error message. */
    break;
  default:
    throw 129; //TODO is this specific or generic?
  }
}
