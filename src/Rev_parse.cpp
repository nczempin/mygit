/*
 * Rev_parse.cpp
 *
 *  Created on: Apr 8, 2016
 *      Author: nczempin
 */
#include "Command.h"
#include "Rev_parse.h"
#include "MyGit.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

Rev_parse::Rev_parse(shared_ptr<MyGit> mg) :
    Command(mg)
{
}

Rev_parse::~Rev_parse()
{
  // TODO Auto-generated destructor stub
}

void Rev_parse::execute()
{
  vector<string> path = receiver->getPath();
  for (string argument : path) {
    if (argument == "HEAD") {

      // open file, read contents
      ifstream infile(".git/HEAD");
      string line;
      while (getline(infile, line)) {
        // assume it starts with "ref: "
        string reference(line.substr(5,line.length()));
        cout << reference << endl;
      }
    }
  }

  /*
   //cout << "Proceeding with " << path << endl;

   // 2. convert sha1 param into path relative from .git
   vector<string> varargs = mygit->getPath();
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
   cout << result.str();*/
}

void Rev_parse::do_long_option(bool flag, string name, string argument)
{
  if (flag) {
    cout << "flag" << endl;
  }
  cout << "name: " << name << endl;
  cout << "argument: " << argument << endl;
}

string Rev_parse::getShortOptions()
{
  return "t";
}
vector<option> Rev_parse::getLongOptions()
{
  vector<option> retval =
    {
      { "textconv", no_argument, 0, 0 } };
  return retval;
}

void Rev_parse::do_short_option(int c, string argument)
{
  switch (c) {
  case 'w':
    //cout << "option -w" << endl;
    break;
  case 't':
    //  cout << "option -t" << endl;
    //  set_option_type(true);
    break;
  case '?':
    /* getopt_long already printed an error message. */
    break;
  default:
    throw 129; //TODO is this specific or generic?
  }
}
