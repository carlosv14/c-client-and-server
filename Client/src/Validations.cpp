#include "Validations.h"

bool Validations::verifyEmail(string email) {
   return regex_match(email,std::regex("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}"));
}

 bool Validations::verifyCedula(string id) {
    if( std::regex_match (id, std::regex("\\d{4}-\\d{4}-\\d{5}")))
        return true;
    printf("%s\n","Id Number not valid !!!");
    return false;
}
