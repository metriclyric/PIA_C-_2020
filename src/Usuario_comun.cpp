#include "Usuario_comun.h"
#include <iostream>
using namespace std;

Usuario_comun::Usuario_comun()
{
    //ctor
}

Usuario_comun::Usuario_comun(string usu,string cons,string id)
{
    Setusuario(usu);
    Setcontrasena(cons);
    Setidentificador(id);
}
