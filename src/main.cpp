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
		<< "   init       Create an empty Git repository or reinitialize an existing one"
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

void hopt(shared_ptr<Command> command, int c, int option_index,
		struct option* long_options)
{
	option long_option = long_options[option_index];
	if (c == 0) {
		command->do_long_option(long_option.flag, long_option.name, optarg);
	} else {
		string argument = "";
		if (optarg) {
			argument = string(optarg);
		}
		command->do_short_option(c, argument);
	}
}

void handle_options(shared_ptr<Command> command, int argc, char* argv[])
{
	int c;
	while (1) {
		vector<option> long_options1 = command->getLongOptions();//long_options_();
		long_options1.push_back({0, 0, 0, 0}); // for handling the options
		option* long_options = &long_options1[0];
		/* getopt_long stores the option index here. */
		int option_index = 0;
		string short_options_hash_object = command->getShortOptions();
		c = getopt_long(argc, argv, short_options_hash_object.c_str(),
				long_options,	&option_index);
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
	//  CommandParameter commandParameter = command->createCommandParameter();

	try {
		// TODO right now this will only check for "hash-object" command. 
		//It should check for a collection of commands and 
		//decide on the appropriate Command subclass (TODO)
		--argc;
		++argv;
		// skip actual command //TODO: extract actual command
		//cout << "before: " << argc << ", " << optind << endl;
		handle_options(command, argc, argv);
		//cout << "after: " << argc << ", " << optind << endl;
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

	vector<string> varargs;
	while (optind < argc) { //TODO get rid of dependency on optind
		char* file = argv[optind++];
		varargs.push_back(file);
	}
//	if (varargs.size() > 0) {
//		cout << "Files to consider: ";
//		for (const auto& file : varargs) {
//			cout << file << " ";
//		}
//		cout << endl;
//	}

	// we have our command and its parameter

	// now read the file contents
	// TODO set parameters / handle options
	for (string path : varargs) {
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
