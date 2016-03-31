/*
 * Hashobject.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: nczempin
 */

#include "Hashobject.h"

#include <openssl/sha.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

Hash_object::Hash_object(shared_ptr<MyGit> mg) :
    mygit(mg)
{
}

Hash_object::~Hash_object()
{
  // TODO Auto-generated destructor stub
}

void Hash_object::execute()
{
  ifstream myfile;
  //TODO handle multiple files as parameter
  string path = mygit->getPath();
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
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1((const unsigned char*) (str), l, hash);
  // convert to 2 hex nibbles per byte and output.
  for (auto& n : hash) {
    cout << hex << setfill('0') << setw(2) << (unsigned int) (n);
  }
  cout << endl;
}
