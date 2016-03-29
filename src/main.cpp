//  main.cpp

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

void hash_object(const string& path)
{
  //TODO handle multiple files as parameter
  ifstream myfile;
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

  // we have our command and its parameter

  // now read the file contents
  string path = argv[2]; //TODO error handling

  try {
    hash_object(path);
  } catch (int n) {
    return n; //TODO more sophisticated exception handling
  }
  return 0;
}
