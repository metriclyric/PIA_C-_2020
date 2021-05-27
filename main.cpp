/*Librerias*/
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <functional>
#include <Persona.h>
#include <vector>
#include <Usuario_comun.h>
#include <Administrador.h>
/*Librerias*/
using namespace std;

struct creden{                 //!ESTRUTURA PARA LECTURA DE  ARCHIVO EN METODO LOGIN
    string user, pass, id;
};

struct libreria_contrasenas{     //!ESTRUCTURA PARA CONTRASEÑAS DE LIBRERIA
    string plataforma;
    string contrasena_lib;
};
int Bienvenida_USER();//!METODO DE BIENVENIDA, SOLO IMPRESION
int Bienvenida_ADMIN();
void login(int &); //!METODO DE LOGUEO Y AGREGAR USER
string encDes(string); //!Encriptacion y desencriptacion de cadenas de texto
void  Menu_usuario(int);   //!MENU DE USUARIOS
void  Menu_administrador(int); //!MENU DE ADMINISRADOR
bool Verificador_Entrada_Num(string);
int Check_Num ();
bool Verificador_Entrada_String(string );
string Check_String();

istream& operator >> (istream&, libreria_contrasenas&);   //!OPERADOR SOBRE CARGADO DE LA ESTRUCU TRA LIBRERIA_CONTRASENAS
ostream& operator << (ostream&, libreria_contrasenas&);

int main(){

    vector<libreria_contrasenas> vec_lib_pass;  //!VECTOR PRINCIPAL PARA  MANEJO DE LIBREIA DE CONTRASEÑAS
    int selector;
    int define_tipo_usuario=0;
    login(define_tipo_usuario);

    //condicionales para el manejo de el menu
    if (define_tipo_usuario==1)
    {
        selector = Bienvenida_ADMIN();
        Menu_administrador(selector);

    }else if (define_tipo_usuario==0) {
        selector = Bienvenida_USER();
        Menu_usuario(selector);
    }
}

//funcion de bienvenida para usuario comun
int Bienvenida_USER(){
    int accion=0;
    cout << fixed << showpoint;
    cout<<setw(50)<<"SecPasswordGen"<<endl;
    cout<<setw(60)<<"Your offline password manager"<<endl;
    cout<<"==========================================================================================="<<endl;
    cout << "Que accion desea tomar?:   1: Buscar contraseña "<<endl;
    cout << setw(50)<<"2  Eliminar contraseña "<< endl;
    cout <<setw(50)<< "3: Ingresar contraseña " << endl << endl;
    accion =Check_Num();
    cin.clear();
    return accion;
}
//funcion de usuario para administrador
int Bienvenida_ADMIN(){
    int accion=0;
    cout << fixed << showpoint;
    cout<<setw(50)<<"SecPasswordGen / ADMIN"<<endl;
    cout<<setw(60)<<"Your offline password manager"<<endl;
    cout<<"==========================================================================================="<<endl;
    cout << "Que accion desea tomar?:   1: Buscar contraseña "<<endl;
    cout << setw(50)<<"2  Eliminar contraseña "<< endl;
    cout <<setw(60)<< "3: Le permitira eliminar a los usuarios " << endl;
    cout << setw(50) <<"  4: Agregar password nueva" << endl;
    accion=Check_Num();
    cin.clear();
    return accion;
}
//funcion para el manejo de el login
void login (int &tipo_usuario){

    int eleccion;
    string  ing_user;
    string  ing_contr;
    string  ing_llave;
    string  ing_idusuario;
    vector<creden> cred;

    Persona *usuario_ingresar;

    cout << "1: Ingresar como administrador."<< endl;
    cout << "2: Ingresar como user."<<endl;
    cout << "3: Agregar usuario y loguearte." <<endl;
    eleccion=Check_Num();
    cin.clear();


    switch (eleccion){
        case 1:                           //!SACA DEL ARCHIVO TXT LAS VARIABLES PARA REVISAR EL LOGIN
        {

                            ifstream* read = new ifstream("Admin_login.txt");//metodo para leer archivo de texto Admin_login.txt
                            string pass, user, llave;
                            int c=1;
                        while (!read->eof()){
                                string linea;
                                getline((*read), linea);
                                if (read->fail()){
                                        break;
                                }
                            switch (c){
                            case 1:
                                user = linea;
                                break;
                            case 2:
                                pass = linea;
                                break;
                            case 3:
                                llave = linea;
                                c=0;
                                break;
                                }
                        c++;
                    }
                        int flag=0;
                        //insercion de datos y comparativa para evaluar los stings ingresados si son los correctos permitira el acceso
                        hash<string> hash_fn;
                     do{
                        cout <<"Ingrese el usuario" << endl;
                        ing_user=Check_String();
                        cin.clear();
                        cin.ignore();
                        cout <<"Ingrese la contrase;a" << endl;
                        getline(cin,ing_contr);
                        cin.clear();
                        cin.ignore();
                        cout <<"Ingrese la llave" << endl;
                        getline(cin,ing_llave);
                        cin.clear();

                        size_t htry_npass = hash_fn(ing_contr);

                        stringstream ss;
                            ss << htry_npass;
                        string s;
                            ss >> s;
                                ss.clear();

                        if(ing_user==user&&ing_llave==llave&& pass==s){
                        flag=5;
                            cout <<"Logueo exitoso"<<endl;
                        }else{ flag++;
                        if(flag<3) cout<<"Las credenciales no son correctas, ingrese de nuevo: " << endl;}
                        if(flag==3) {
                                cout << "Excedio el numero de intentos, regresara al inicio: " << endl;
                                login(tipo_usuario);
                            }
                        }while(flag<=4);
                        tipo_usuario =1;
                            break;
        }

      case 2:
       {
                        //
                        ifstream* read = new ifstream("User_login.txt");
                        string pass, user, idusuario;
                        int c=1;
                        while (!read->eof()){
                                string linea;
                                getline((*read), linea);
                                if (read->fail()){
                                        break;
                                }
                            switch (c){
                            case 1:
                                user = linea;
                                break;
                            case 2:
                                pass = linea;
                                break;
                            case 3:
                                idusuario = linea;
                                creden credT;
                                credT.user=user;
                                credT.pass=pass;
                                credT.id=idusuario;
                                cred.push_back(credT);
                                c=0;
                                break;
                                }
                        c++;
                    }
                        int flag=0;

                        hash<string> hash_fn;
                     do{

                        cout <<"Ingrese el usuario" << endl;
                        ing_user = Check_String();
                        cin.clear();
                        cin.ignore();
                        cout <<"Ingrese la contrase;a" << endl;
                        getline(cin,ing_contr);
                        cin.clear();
                        cin.ignore();

                        size_t htry_npass = hash_fn(ing_contr);

                        stringstream ss;
                            ss << htry_npass;
                        string s;
                        ss >> s;
                        ss.clear();
                        creden tempCred;

                        for(int i =0;i<cred.size();i++)
                        {
                                if(cred[i].user==ing_user&&cred[i].pass==s)
                                {
                                    tempCred.user = cred[i].user;
                                    tempCred.pass = cred[i].pass;
                                    tempCred.id = cred[i].id;
                                }
                        }
                        if(ing_user==tempCred.user && s==tempCred.pass)
                        {
                            flag=5;
                            cout <<"Logueo exitoso"<<endl;
                        }else
                        {
                            flag++;
                            if(flag<3) cout<<"Las credenciales no son correctas, ingrese de nuevo: " << endl;
                        }
                        if(flag==3)
                        {
                            cout << "Excedio el numero de intentos, regresara al inicio: " << endl;
                            login(tipo_usuario);
                        }
                        }while(flag<=4);
                    tipo_usuario=0;
                    break;

        }
        case 3:
        {
                        ifstream* read = new ifstream("User_login.txt");
                        string pass, user, idusuario;
                        int c=1;
                        while (!read->eof()){
                                string linea;
                                getline((*read), linea);
                                if (read->fail()){
                                        break;
                                }
                            switch (c){
                            case 1:
                                user = linea;
                                break;
                            case 2:
                                pass = linea;
                                break;
                            case 3:
                                idusuario = linea;
                                creden credT;
                                credT.user=user;
                                credT.pass=pass;
                                credT.id=idusuario;
                                cred.push_back(credT);
                                c=0;
                                break;
                                }
                        c++;
                    }

                    creden tempCred;
                    cout <<"Ingrese el usuario" << endl;
                        tempCred.user= Check_String();
                        cin.clear();
                        cin.ignore();
                        cout <<"Ingrese la contrase;a" << endl;
                        getline(cin,tempCred.pass);
                        cin.clear();


                    hash<string> hash_fn;
                    size_t hashTemp = hash_fn(tempCred.pass);

                        stringstream ss;
                            ss << hashTemp;
                        string s;
                            ss >> s;
                                ss.clear();

                    cin.ignore();

                    tempCred.pass=s;
                    int tamano = cred.size() +1;
                    tempCred.id = "su"+ to_string(tamano);
                    ofstream escribir("User_login.txt", ofstream::app);
                    escribir << tempCred.user << "\n" << tempCred.pass << "\n" << tempCred.id<< "\n";
                    tipo_usuario=0;
                    break;
        }
    default:
        {
            int x =0;
            cout <<"Opccion invalida, regresara a la seleccion!" << endl<< endl << endl;
            return login(x);


        }

    }
}
ostream& operator << (ostream& os, libreria_contrasenas& CO){//Operador Sobrecargado cout
    string contrasena_desencriptada = CO.contrasena_lib;
    contrasena_desencriptada= encDes(CO.contrasena_lib);
    return (os <<"Plataforma:  " << CO.plataforma<< endl<< "Contraseña: " << contrasena_desencriptada);
}
istream& operator>>(istream& is, libreria_contrasenas& CS){//sobrecarga de cin
    string contrasena_encriptada;
    libreria_contrasenas CC;
    int contadorCarac = 0;
    int contadorCaps= 0;
    int contadorLower =0;
    int contadorNum=0;
    exception e;
    cout << "introduce una plataforma" << endl;
    is >> CC.plataforma;

    cout << "contraseña" << endl;
    is >> CC.contrasena_lib;

  try{
  for(int i = 0; i < CC.contrasena_lib.size();i++){//!RECORRE TODA LA CADENA
        if (ispunct(CC.contrasena_lib[i])){//!INDICA EL SINGNO DE PUNTUACION
                contadorCarac++;
        }else if(isupper(CC.contrasena_lib[i])){//!INDICA LA LETRA EN MAYUS
            contadorCaps++;
        }else if (islower(CC.contrasena_lib[i])){//!INDICA LA LETRA MINUS
            contadorLower++;
        }else if(isdigit(CC.contrasena_lib[i])){//!INDICA SI ES DIGITO
            contadorNum++;
        }
    }
    if (contadorCarac<3||contadorCaps<1||contadorLower<1||contadorNum<1||(CC.contrasena_lib.size()<8))
        {
           throw  e;
        }
  contrasena_encriptada=  encDes(CC.contrasena_lib);
if (is){
        CS.plataforma =  CC.plataforma;
    CS.contrasena_lib = contrasena_encriptada;
  }
  return is;
  }catch(exception e)
  {
    cout << "error"<< endl;
    cin.clear();
    cin >> CC;
  }
  }
string encDes(string aEncriptar){//Funcion que se encarga de encriptar y desencriptar
    char key = 'J';
    string output = aEncriptar;

    for(int i = 0; i<aEncriptar.size(); i++){
        output[i] = (aEncriptar[i])^key;
    }
        return output;

}
void  Menu_usuario(int elector){//Menu para usuario comun
    string busqueda;
    vector<libreria_contrasenas> vec_lib_pass;
    ifstream* read = new ifstream("lib_pass.txt");

    string tplat, tpass;
    int c=1;
    while (!read->eof()){
        string linea;
        getline((*read), linea);
        if (read->fail()){
        break;
        }
        switch (c){
            case 1:
            tplat = linea;
            break;
            case 2:
            tpass = linea;
            libreria_contrasenas tvec;
            tvec.plataforma=tplat;
            tvec.contrasena_lib=tpass;
            vec_lib_pass.push_back(tvec);
            c=0;
            break;
        }
        c++;
    }
    cout << vec_lib_pass.size() << endl;
    int op = 0;
    switch (elector)
    {
        case 1:
        {
             cout << "Que contrasena desea buscar?" << endl;
             busqueda=Check_String();
             cin.clear();
             int control =0;
             for(int i =0; i < vec_lib_pass.size();i++)
             {
                 if (busqueda==vec_lib_pass[i].plataforma)
                 {
                    cout  << vec_lib_pass[i];
                     control = 1;
                 }
                  if(i+1==vec_lib_pass.size()&&control==0)cout << "no hay";
             }
             break;

        }
        case 2:
            {
            cout << "Que contrasena desea eliminar?" << endl;
              busqueda= Check_String();
             cin.clear();
             int control2=0;
             for(int i =0; i < vec_lib_pass.size();i++)
             {
                 if (busqueda==vec_lib_pass[i].plataforma)
                 {
                    vec_lib_pass.erase(vec_lib_pass.begin()+i);
                    control2 = 1;
                 }
                 if(i+1==vec_lib_pass.size()&&control2==0)cout << "no hay";
             }
            break;
            }
    case 3:{
			do{
        libreria_contrasenas vect_temp;                      //!ESTRUCURA TEMPORAL PARA SOBRECARGA DEL OPERADOR;
            cin >> vect_temp;

            vec_lib_pass.push_back(vect_temp);
            cout << "Desea  otra?" << endl;
            op=Check_Num();
                }while(op ==0);
            break;
            }

    default :
        {
            cout <<"Opccion invalida, regresara a menu principal" << endl<< endl << endl;
            int x =Bienvenida_USER();
            Menu_usuario(x);
        }
    }
     ofstream escribir("lib_pass.txt");
     for(int i =0; i<vec_lib_pass.size();i++)
     {
         escribir << vec_lib_pass[i].plataforma << "\n" << vec_lib_pass[i].contrasena_lib << "\n";
     }
}
void Menu_administrador (int elector){//Menu para el administrador
    string busqueda;
    vector<libreria_contrasenas> vec_lib_pass;
    ifstream* read = new ifstream("lib_pass.txt");

    string tplat, tpass;
    int c=1;
    while (!read->eof()){
        string linea;
        getline((*read), linea);
        if (read->fail()){
        break;
        }
        switch (c){
            case 1:
            tplat = linea;
            break;
            case 2:
            tpass = linea;
            libreria_contrasenas tvec;
            tvec.plataforma=tplat;
            tvec.contrasena_lib=tpass;
            vec_lib_pass.push_back(tvec);
            c=0;
            break;
        }
        c++;
    }
    int op = 0;
    switch (elector)
    {
        case 1:
        {
             cout << "Que contrasena desea buscar?" << endl;
             busqueda =Check_String();
             cin.clear();
             int control =0;
             cout << busqueda <<endl;
             for(int i =0; i < vec_lib_pass.size();i++)
             {
                 if (busqueda==vec_lib_pass[i].plataforma)
                 {
                    cout  << vec_lib_pass[i];
                     control = 1;
                 }
                  if(i+1==vec_lib_pass.size()&&control==0)cout << "no hay";
             }
             break;

        }
        case 2:
            {
            cout << "Que contrasena desea eliminar?" << endl;
            busqueda= Check_String();
             cin.clear();
             int control2=0;
             for(int i =0; i < vec_lib_pass.size();i++)
             {
                 if (busqueda==vec_lib_pass[i].plataforma)
                 {
                    vec_lib_pass.erase(vec_lib_pass.begin()+i);
                    control2 = 1;
                 }
                 if(i+1==vec_lib_pass.size()&&control2==0)cout << "no hay";
             }
            break;
            }
        case 3:
            {

                Administrador* admin =  new Administrador ();
                cout <<"Seleccione el identificador del usuario a borrar? " << endl;
                busqueda=Check_String();
                cin.clear();
                admin->eliminar_usuarios(busqueda);
                break;
            }
    case 4:{
			do{
        libreria_contrasenas vect_temp;                      //!ESTRUCURA TEMPORAL PARA SOBRECARGA DEL OPERADOR;
            cin >> vect_temp;

            vec_lib_pass.push_back(vect_temp);
            cout << "Desea  otra?" << endl;
            op=Check_Num();
                }while(op ==0);
            break;
            }
    default:
        {
            cout <<"Opccion invalida, regresara a menu principal" << endl<< endl << endl;
            int x =Bienvenida_ADMIN();
            Menu_administrador(x);

        }
    }
    ofstream escribir("lib_pass.txt");
     for(int i =0; i<vec_lib_pass.size();i++)
     {
         escribir << vec_lib_pass[i].plataforma << "\n" << vec_lib_pass[i].contrasena_lib << "\n";
     }
}
int Check_Num () //!METODO PARA VALIDAR ENTRADA DE NUMEROS
	{
    	string eleccion;
    	bool Verify = false;

    	while (! Verify)
    	{
        	try
        	{
            	cin >> eleccion;
            	cin.clear();
            	Verify = Verificador_Entrada_Num(eleccion);

            	if (! Verify)
                	throw eleccion;
        	}
        	catch (string& e)
        	{
                	cout << "Opcion invalida: El caracter debe ser un numero." << e <<endl;

        	}
        	catch (...)
        	{
            	cout << "Error Desconocido " << endl;
        	}
    	}
    	return atoi(eleccion.c_str());
}

bool Verificador_Entrada_Num(string eleccion) //!METODO COMPLEMENTARIO PARA VALIDAR ENTRADA DE NUMEROS
	{
	int i;
	if (eleccion.length () == 0)
    	{
    	return 0;
    	}
	for (i = 0; i < eleccion.length(); i++)
    	{
    	if (! isdigit(eleccion[i]))

        	return 0 ;
    	}
	return 1;

}

string Check_String(){//Metodo para validar la entrada de cadenas de texto

    string cadena;
    string error="Cadena invalida, contiene caracteres no permitidos.";
    string cadena_excedida="El maximo numero de elementos de la cadena es 20.";
    int contador_de_digitos=0;
        try
        {
            cin >>cadena;
            cin.ignore(20,'\n');
            cin.clear();
            for(int i=0;i<cadena.length();i++)
            {
                if (ispunct(cadena[i]))
                {
                    contador_de_digitos ++;
                }
            }

            if (cadena.size()>20){
                throw cadena_excedida;
            }else if (contador_de_digitos > 0)
             {
                contador_de_digitos=0;
                throw error;
             }
             if (contador_de_digitos == 0 )
            {
                return cadena;
            }
        }
        catch(string& e)
        {
            cout << e <<endl;
            cin.ignore();
            cin.clear();
            return Check_String();
        }
        catch (string& e)
        {
            cout << e <<endl;
            cin.ignore();
            cin.clear();
            return Check_String();
        }
        catch (exception e)
        {
            cout << "error" << e.what() <<endl;
        }
        catch(...)
        {

        }
}


