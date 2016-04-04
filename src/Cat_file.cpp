/*
 * Hashobject.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include "Cat_file.h"
#include "zpipe.h"

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

string Cat_file::get_absolute_path(string path)
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

bool Cat_file::find_dir(string name, string dirpath)
{
  DIR *dirp = opendir(dirpath.c_str());

  dirent* dp;
  bool found = false;
  while ((dp = readdir(dirp)) != NULL) {
    if (!strcmp(dp->d_name, name.c_str())) {
      found = true;
      break;
    }
  }
  closedir(dirp);
  return found;
}

void Cat_file::execute()
{
  // 1. determine .git path
  //    a. determine absolute path of current directory
  string name(".git");
  bool found = false;
  bool done = false;
  string path = get_absolute_path(".");
  while (!found && !done) {
    //cout << "cwd: " << path << endl;
    //    b. recurse up until one directory contains a .git dir (TODO: what to do when inside .git?)
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
  path += "/" + name + "/objects";
  //cout << "Proceeding with " << path << endl;

// 2. convert sha1 param into path relative from .git
  string sha1 = mygit->getPath();
  //cout << "sha1: " << sha1 << endl;
  string head = sha1.substr(0, 2);
  string tail = sha1.substr(2);
  //cout << head << "/" << tail << endl;
// 3. read that file
   path += "/" + head + "/" + tail;

   cout << "working with: " << path << endl;
  FILE * pFile;
  pFile = fopen (path.c_str(),"r");
  if (pFile!=NULL)
  {
  int zerr =  inf(pFile, stdout);
    fclose (pFile);
  }
// 4. uncompress it
// 5. display it

  //  
//  ostringstream file_contents;
//  if (myfile.is_open()) {
//    string line;
//    //TODO use proper buffering, especially for large files
//    while (getline(myfile, line)) {
//      file_contents << line << '\n';
//    }
//    myfile.close();
//  } else {
//    throw 128;
//  }
//  string file_string = file_contents.str();
//  // Add the git specific text, "blob " plus size of the original blob (file)
//  string blobTxt = "blob " + to_string(file_string.size());
//  string combined = blobTxt + '\0' + file_string;
//  const char* str = combined.c_str();
//  int l = combined.length();
//  // convert to sha1

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
