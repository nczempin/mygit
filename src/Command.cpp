/*
 * Command.cpp
 *
 *  Created on: Mar 31, 2016
 *      Author: nczempin
 */

#include "Command.h"

Command::Command(shared_ptr<MyGit> mg) :
    receiver(mg)
{
}

Command::~Command()
{
  // TODO Auto-generated destructor stub
}

