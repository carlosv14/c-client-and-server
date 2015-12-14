#include "Users.h"

Users::Users(string name,string username,string profilepic,string id, string bd)
{
    this->name = name;
    this->username = username;
    this->profilepic = profilepic;
    this->id   = id;
    this->bd = bd;
}

Users::~Users()
{
    //dtor
}
