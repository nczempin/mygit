/*
 * Hashobject.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include "Hash_object.h"

#include <openssl/sha.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "HashObjectCommandParameter.h"

using namespace std;

Hash_object::Hash_object(shared_ptr<MyGit> mg) :
    mygit(mg)
{
}

Hash_object::~Hash_object()
{
  // TODO Auto-generated destructor stub
}
shared_ptr<CommandParameter> Hash_object::createCommandParameter()
{
  shared_ptr<CommandParameter> retVal(new HashObjectCommandParameter());
  return retVal;
}
void Hash_object::execute()
{
  ifstream myfile;
  //TODO handle multiple files as parameter
  vector<string> varargs = mygit->getPath();
	string path = varargs[0]; //TODO assumption
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
    cout << "fatal: Cannot open '" << path << "': No such file or directory"
        << endl;
    throw 128;
  }
  string file_string = file_contents.str();
  // Add the git specific text, "blob " plus size of the original blob (file)
  string blobTxt = "blob " + to_string(file_string.size());
  string combined = blobTxt + '\0' + file_string;
  const char* str = combined.c_str();
  int l = combined.length();
  // convert to sha1
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1((const unsigned char*) (str), l, hash);
  // convert to 2 hex nibbles per byte and output.
  for (auto& n : hash) {
    cout << hex << setfill('0') << setw(2) << (unsigned int) (n);
  }
  cout << endl;
}

void Hash_object::do_long_option(bool flag, string name, string argument)
{
//  if (flag) {
//    cout << "flag" << endl;
//  }
//  cout << "name: " << name << endl;
//  cout << "argument: " << argument << endl;
}

string Hash_object::getShortOptions()
{
  return "wt:";
}
vector<option> Hash_object::getLongOptions()
{
  vector<option> retval =
        {
            {
              "path",
              required_argument, 0, 0
            }
        };
  return retval;
}
void Hash_object::do_short_option(int c, string argument)
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
