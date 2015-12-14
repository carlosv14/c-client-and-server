#ifndef USERS_H
#define USERS_H
#include <iostream>

using namespace std;

class Users
{
    string name, email, username, profilepic, id,bd;
    public:

        Users(string name,string username,string profilepic,string id, string bd);
        virtual ~Users();
    protected:
    private:
};

#endif // USERS_H
