//  main.cpp

#include <getopt.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Hashobject.h"

using namespace std;

void print_usage()
{
  cout << "usage: mygit <command> [<args>]" << endl;
  cout << endl << "These are common Mygit commands used in various situations:"
      << endl;
  cout << "start a working area (see also: mygit help tutorial)" << endl;
  cout
      << "   init       Create an empty Git repository or reinitizalize an existing one"
      << endl;
  cout << "[TODO]" << endl;
  cout << endl;
  cout
  << "'mygit help -a' and 'mygit help -g' list available subcommands and some"
      << endl;
  cout << "concept guides. See 'mygit help <command>' or 'mygit help <concept>'"
      << endl;
  cout << "to read about a specific subcommand or concept." << endl;
}

int main(int argc, char* argv[])
{
  --argc;
  ++argv;
  // skip actual command //TODO: extract actual command
  int c;
  int stdin_flag = 0;
  int stdin_paths_flag = 0;
  int no_filters_flag = 0;
  int literally_flag = 0;
  while (1) {
    static struct option long_options[] =
          {
              { "stdin", no_argument, &stdin_flag, 1 },
              { "stdin-paths", no_argument, &stdin_paths_flag, 1 },
              { "no-filters", no_argument, &no_filters_flag, 1 },
              { "literally", no_argument, &literally_flag, 1 },
              { "path", required_argument, 0, 0 },
              { 0, 0, 0, 0 } };
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "wt:", long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1) break;

    switch (c) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (long_options[option_index].flag != 0) break;
      printf("option %s", long_options[option_index].name);
      if (optarg) printf(" with arg %s", optarg);
      printf("\n");
      break;

    case 'w':
      puts("option -w\n");
      break;

    case 't':
      printf("option -t with value `%s'\n", optarg);
      break;

//    case '?':
//      /* getopt_long already printed an error message. */
//      cout << "hello1" << endl;
//      break;

    default:
      // TODO synchronize stdout and stderr?
      print_usage();
      return 129;
    }
  }

  if (literally_flag) puts("literally flag is set");
  if (no_filters_flag) puts("no-filters flag is set");
  if (stdin_flag) puts("stdin flag is set");
  if (stdin_paths_flag) puts("stdin paths flag is set");

  vector<string> files;
  while (optind < argc) {
    char* file = argv[optind++];
    files.push_back(file);
  }
  if (files.size()>0){
    for (const auto& file : files){
      cout << file << " ";
    }
    cout << endl;
  }
  if (argc == 0) {
    print_usage();
    return 1;
  }
  if (strcmp(argv[0], "hash-object")) {
    cout << "mygit: '" << argv[1]
        << "' is not a mygit command. See 'mygit --help'." << endl;
    return 1;
  }
  if (argc == 1) {
    return 0;
  }

  // we have our command and its parameter

  // now read the file contents
  string path = files[0]; //TODO error handling

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
