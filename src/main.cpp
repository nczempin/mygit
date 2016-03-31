//  main.cpp

#include <getopt.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Hashobject.h"
#include "MyGit.h"

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

struct option* long_options_()
{
  int stdin_flag = 0;
  int stdin_paths_flag = 0;
  int no_filters_flag = 0;
  int literally_flag = 0;
  static struct option long_options[] =
        { //              { "stdin", no_argument, &stdin_flag, 1 },
          //              { "stdin-paths", no_argument, &stdin_paths_flag, 1 },
          //              { "no-filters", no_argument, &no_filters_flag, 1 },
          //              { "literally", no_argument, &literally_flag, 1 },
        { "path", required_argument, 0, 0 },
        { 0, 0, 0, 0 } };
  return long_options;
}

void do_long_option(option long_option)
{
  // long option selected
  /* If this option set a flag, do nothing else now. */
  if (long_option.flag != 0) {
    return;
  }

  printf("option %s", long_option.name);
  if (optarg) {
    printf(" with arg %s", optarg);
  }

  printf("\n");
}

void do_short_option(int c)
{
  switch (c) {
  case 'w':
    puts("option -w\n");
    break;
  case 't':
    printf("option -t with value `%s'\n", optarg);
    break;
  case '?':
    /* getopt_long already printed an error message. */
    break;
  default:
    throw 129; //TODO is this specific or generic?
  }
}

void hopt(shared_ptr<Command> command, int c, int option_index,
    struct option* long_options)
{
  option long_option = long_options[option_index];
  if (c == 0) {
    do_long_option(long_option);

  } else {
    do_short_option(c);
  }
}

void handle_options(shared_ptr<Command> command, int argc, char* argv[])
{
  //TODO separate generic part from hash-object specific part
  int c;
  while (1) {
    struct option* long_options = long_options_();
    /* getopt_long stores the option index here. */
    int option_index = 0;
    string short_options_hash_object = command->getShortOptions();
    c = getopt_long(argc, argv, short_options_hash_object.c_str(), long_options,
        &option_index);
    /* Detect the end of the options. */
    if (c == -1) {
      break;
    }
    hopt(command, c, option_index, long_options);
  }
}

shared_ptr<Command> determine_command(shared_ptr<MyGit> mygit, int argc,
    char* argv[])
{
  if (argc == 1) {
    print_usage();
    throw 1;
  }
  // TODO obviously specific; all the allowed commands should be collected in one place
  if (strcmp(argv[1], "hash-object")) {
    cout << "mygit: '" << argv[1]
        << "' is not a mygit command. See 'mygit --help'." << endl;
    throw 1;
  }
  if (argc == 2) {
    throw 0;
  }
  Hash_object* hashObject = new Hash_object(mygit);
  shared_ptr<Command> p(hashObject);
  return p;
}

int main(int argc, char* argv[])
{
  shared_ptr<MyGit> mygit(new MyGit());
  mygit->setPath("1");

  shared_ptr<Command> command = determine_command(mygit, argc, argv);
  try {
    // TODO right now this will only check for "hash-object" command. It should check for a collection of commands and decide on the appropriate Command subclass (TODO)
    --argc;
    ++argv;
    // skip actual command //TODO: extract actual command
    cout << "before: " << argc << ", " << optind << endl;
    handle_options(command, argc, argv);
    cout << "after: " << argc << ", " << optind << endl;
  } catch (const int n) {
    if (n == 129) { //TODO give this magic number a name
      print_usage();
    }
    return n;
  }
//  if (literally_flag) puts("literally flag is set");
//  if (no_filters_flag) puts("no-filters flag is set");
//  if (stdin_flag) puts("stdin flag is set");
//  if (stdin_paths_flag) puts("stdin paths flag is set");

  vector<string> files;
  while (optind < argc) { //TODO get rid of dependency on optind
    char* file = argv[optind++];
    files.push_back(file);
  }
  if (files.size() > 0) {
    cout << "Files to consider: ";
    for (const auto& file : files) {
      cout << file << " ";
    }
    cout << endl;
  }

  // we have our command and its parameter

  // now read the file contents
  // TODO set parameters / handle options
  for (string path : files) {
    try {
      mygit->setPath(path);
      command->execute();
    } catch (int n) {
      cout << "fatal: Cannot open '" << path << "': No such file or directory"
          << endl;
      return n; //TODO more sophisticated exception handling
    }
  }
  return 0;
}
