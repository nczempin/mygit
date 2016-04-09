/*
 * Cat_file.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include "Cat_file.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <vector>


//TODO Factor out these C libraries
#include <dirent.h>
#include <getopt.h>
#include <unistd.h>

#include <cstring>


#include "Zlib_facade.h"

using namespace std;

Cat_file::Cat_file(shared_ptr<Command_receiver> receiver) :
    Abstract_command(receiver)
{
  option_type = false;
}

Cat_file::~Cat_file()
{
  // TODO Auto-generated destructor stub
}

stringstream Cat_file::uncompress(const string& path)
{
  stringstream buffer = Zlib_facade::uncompress(path, option_type);
  return buffer;
}

void Cat_file::execute()
{
  // 1. determine .git path
  //    a. determine absolute path of current directory
  string path = Utils::getWorkareaRoot();
  path += "/.git/";
  //cout << "Proceeding with " << path << endl;

  // 2. convert sha1 param into path relative from .git
  vector<string> varargs = receiver->getArguments();
  //TODO obviously not a path
  if (!option_type && varargs[0] != "blob") {
    throw 3; //TODO handle properly
  }

  string sha1 = option_type ? varargs[0] : varargs[1]; //TODO assumption

  //cout << "sha1: " << sha1 << endl;

  string head = sha1.substr(0, 2);
  string tail = sha1.substr(2);
  //cout << head << "/" << tail << endl;
  // 3. read that file
  path += "/" + head + "/" + tail;

  //cout << "working with: " << path << endl;
  stringstream result = uncompress(path);
  cout << result.str();
}

void Cat_file::do_long_option(bool flag, string name, string argument)
{
  if (flag) {
    cout << "flag" << endl;
  }
  cout << "name: " << name << endl;
  cout << "argument: " << argument << endl;
}

string Cat_file::get_short_options()
{
  return "t";
}
vector<option> Cat_file::get_long_options()
{
  vector<option> retval =
    {
      { "textconv",
      no_argument,
        0, 0 } };
  return retval;
}
void Cat_file::set_option_type(bool ot)
{
  option_type = ot;
}

void Cat_file::do_short_option(int c, string argument)
{
  switch (c) {
  case 'w':
    cout << "option -w" << endl;
    break;
  case 't':
    //	cout << "option -t" << endl;
    set_option_type(true);
    break;
  case '?':
    /* getopt_long already printed an error message. */
    break;
  default:
    throw 129; //TODO is this specific or generic?
  }
}
