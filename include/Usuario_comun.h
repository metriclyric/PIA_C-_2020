#ifndef USUARIO_COMUN_H
#define USUARIO_COMUN_H
#include <Persona.h>
#include <iostream>
using namespace std;

class Usuario_comun : public Persona
{
    public:
        Usuario_comun();
        Usuario_comun(string,string,string);


        string Getidentificador() { return identificador; }
        void Setidentificador(string val) { identificador = val; }

    private:
       string identificador;
};

#endif // USUARIO_COMUN_H
