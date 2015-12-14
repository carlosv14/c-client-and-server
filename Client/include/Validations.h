#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <iostream>
#include <string>
#include <regex>

using namespace std;

class Validations
{
    public:
        Validations(){
        }
      static bool verifyEmail(string email);
      static bool verifyCedula(string id);
        virtual ~Validations();
    protected:
    private:


};

#endif // VALIDATIONS_H
