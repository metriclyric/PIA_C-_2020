#include "Administrador.h"
#include <fstream>
#include <vector>
#include <Usuario_comun.h>
Administrador::Administrador()//contrusctor sin parametros
{
    //ctor
}

Administrador::Administrador(string usu,string cons,string llav)//constructor con parametros
{
    Setusuario(usu);
    Setcontrasena(cons);
    Setllave_administracion(llav);
}

void Administrador::eliminar_usuarios(string eliminar)//Definicion de funcion de eliminar_usuarios
{
    vector <Usuario_comun> lista_de_usuarios;
                    ifstream* read = new ifstream("User_login.txt");//creacion de archivo de entrada
                    string pass, user, idusuario;
                do{
                        int c=1;
                        while (!read->eof()){
                                string linea;
                                getline((*read), linea);
                                if (read->fail()){
                                        break;
                                }
                            switch (c){
                            case 1:
                                user=linea;
                                break;
                            case 2:
                                pass = linea;
                                break;
                            case 3:
                                idusuario = linea;

                                Usuario_comun  usuT;
                                usuT.Setusuario(user);
                                usuT.Setcontrasena(pass);
                                usuT.Setidentificador(idusuario);
                                lista_de_usuarios.push_back(usuT);
                                c=0;
                                break;
                                }
                        c++;
                    }
                }while(!read->eof());

            ofstream escribir("User_login.txt");


             int control2=0;
             for(int i =0; i < lista_de_usuarios.size();i++)
             {
                 if (eliminar == lista_de_usuarios[i].Getidentificador())
                 {
                    lista_de_usuarios.erase(lista_de_usuarios.begin()+i);
                    control2 = 1;
                 }
                 if(i+1==lista_de_usuarios.size()&&control2==0)cout << "no hay";
             }

            for(int i =0; i<lista_de_usuarios.size();i++)
     {
         escribir << lista_de_usuarios[i].Getusuario() << "\n" << lista_de_usuarios[i].Getcontrasena() << "\n" << lista_de_usuarios[i].Getidentificador() << "\n" ;
     }


}
