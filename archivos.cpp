#include<iostream>
#include<functional>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

int main(){
|  ifstream* read = new ifstream("login.txt");
   string nuser, npass;
   string pass ;
   string user ;

    int c=1;

    while (!read->eof()){
            string linea;
            getline((*read), linea);
            if (read->fail())
                break;
            switch (c){
            case 1:
                 user = linea;
                break;
            case 2:
                pass = linea;
                c=0;
break;
            }
            c++;
        }

   int flag=0;

   hash<string> hash_fn;
//   size_t hgood_user = hash_fn(user);

//   size_t hgood_pass = pass;

   do{
   cout << "Ingrese el usuario" << endl;
   cin >> nuser;
   cout <<"Ingrese la contrase;a" << endl;
   cin >> npass;
   size_t htry_nuser = hash_fn(nuser);
   size_t htry_npass = hash_fn(npass);


    stringstream ss;
    ss << htry_npass;
    string s;
    ss >> s;

    ss.clear();
    ss << htry_nuser;
    string s2;
    ss >> s2;
      cout << s << " " << pass<<endl;
        cout << s2 << " " << user<<endl;


   if(user==s2 && pass==s){
        flag=5;
   }else{ flag++;
            if(flag<3) cout<<"La contrase;a no es correcta ingese de nuevo" << endl;}
    if(flag==3) {
    cout << "Excedio el numero de intentos" << endl; return 0; }
    }while(flag<=4);


//    cout <<  hgood_user;
    //!condigo a ejecutar

 //   cout << hgood_user(user)
}
