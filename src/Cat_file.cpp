/*
 * Hashobject.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include "Cat_file.h"

#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "HashObjectCommandParameter.h"

using namespace std;

Cat_file::Cat_file(shared_ptr<MyGit> mg) :
    mygit(mg)
{
}

Cat_file::~Cat_file()
{
  // TODO Auto-generated destructor stub
}
shared_ptr<CommandParameter> Cat_file::createCommandParameter()
{
  shared_ptr<CommandParameter> retVal(new HashObjectCommandParameter());
  return retVal;
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

void Cat_file::execute()
{
  // 1. determine .git path
  //    a. determine absolute path of current directory
  string cwd = get_absolute_cwd();
  cout << "cwd: " << cwd << endl;

  //    b. recurse up until one directory contains a .git dir (TODO: what to do when inside .git?)

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
