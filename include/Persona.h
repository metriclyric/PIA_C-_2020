#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
using namespace std;


class Persona
{
    public:
        Persona();


        string Getusuario() { return usuario; }
        void Setusuario(string val) { usuario = val; }
        string Getcontrasena() { return contrasena; }
        void Setcontrasena(string val) { contrasena = val; }
        virtual void eliminar_usuarios(string);

    private:
        string usuario;
        string contrasena;
};

#endif // PERSONA_H
