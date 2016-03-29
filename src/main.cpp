//  main.cpp

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
  if (argc == 1) {
    cout << "usage: " << argv[0] << " hash-object <args>" << endl;
    return 1;
  }
  if (strcmp(argv[1], "hash-object")) {
    cout << "mygit: '" << argv[1]
        << "' is not a mygit command. See 'mygit --help'." << endl;
    return 1;
  }
  if (argc == 2) {
    return 0;
  }
  string path = argv[2]; //TODO error handling
  ifstream myfile(path);
  ostringstream file_contents;
  if (myfile.is_open()) {
    string line;
    while (getline(myfile, line)) {
      file_contents << line << '\n';
    }
    myfile.close();
  } else {
    cout << "fatal: Cannot open '" << path << "': No such file or directory"
        << endl;
    return 128;
  }
  //const unsigned char str[] = "Original String";
  string file_string = file_contents.str();

  const char* str = file_string.c_str();
  char * cstr = new char[file_string.length() + 1];
  strcpy(cstr, str);
  //cout << cstr << endl;
  unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
  unsigned long int length = sizeof(cstr) - 1;
  SHA1((const unsigned char*) cstr, length, hash);
  for (auto &n : hash) {
    cout << hex << setw(2) << (unsigned int) n;
  }
  cout << endl;
  return 0;
}
