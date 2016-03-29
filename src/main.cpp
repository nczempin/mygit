//  main.cpp

#include <cstring>
#include <iostream>
#include <string>

#include "Hashobject.h"

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

  // we have our command and its parameter

  // now read the file contents
  string path = argv[2]; //TODO error handling

  try {
    Hash_object hash_object;
    hash_object.set_parameter(path);
    hash_object.execute_command();
  } catch (int n) {
    cout << "fatal: Cannot open '" << path << "': No such file or directory"
        << endl;
    return n; //TODO more sophisticated exception handling
  }
  return 0;
}
