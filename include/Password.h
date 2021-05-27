#ifndef PASSWORD_H
#define PASSWORD_H
#include <iostream>
using namespace std;

class Password
{
    public:
        Password();
        Password(password);

        string Getpassword() { return password; };
        void Setpassword( string val) { password = val; };
        void cifrar_password();
        void descrifrar_password();
        friend string comprobar_fortaleza( string);



    private:
      string password;
};

#endif // PASSWORD_H
