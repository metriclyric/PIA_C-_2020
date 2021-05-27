#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <Persona.h>


class Administrador : public Persona
{
    public:
        Administrador();
        Administrador(string,string,string);

        string Getllave_administracion() { return llave_administracion; };
        void Setllave_administracion(string val) { llave_administracion = val; };
        void eliminar_usuarios(string);


    private:
        string llave_administracion;
};

#endif // ADMINISTRADOR_H
