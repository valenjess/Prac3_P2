#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <fstream>

using namespace std;

class usuario
{
    private: //Atributos de la clase usuario
        string mArchivo="../Cajero_Prac3/BD/sudo.txt";
        string mBaseDatos; //Contiene toda la data de los usuarios y la contraseña del administrador
        string mNuevaData="";//String con informacion actualizada
        int mIndice=0;


    public: //Metodos de la clase usuario
        usuario();
        void lectura(); //lee el txt y guarda toda la data en un string

        void verificar_Usuario(string documento); //recibe el documento ingresado por
                                                  //el usuario,y recorre el arreglo buscando el documento

        bool verificar(string clave_ingresada);  //Recibe la clave ingresada por el administrador
                                                 //y la compara con el contenido del primer renglon
                                                 //del txt

        bool verificar_Contrasena(string contrasena); // recibe la contrasena ingresada por
                                                      //el usuario y la compara con sus datos respectivos
                                                      //en el txt

        void Registar();                        //Le permite al administrador añadir un nuevo usuario

        string decotwo(string cadena_codificada); //decodificador , 2do metodo

        string codtwo(string cadena_Binaria);     //codificador 2do metodo

        string BinaryStringToText(string Cadena_Cod); //Conversor de binario a ASCII

       string Consultar_Saldo();  //Permite consultar el saldo del usuario, y ademas devuelve
                                 //un string con toda la informacion actualizada, incluyendo el saldo
                                 //con los 1000 COP descontados por manejo

        void Retirar_Dinero();      //Permite retirar dinero, siempre y cuando el usuario cuente con
                                    //saldo mayor o igual a lo que desea retirar mas los 1000 COP de manejo

        string binario(string palabra); //Conversor de ASCII a binario

        void escritura();  //Permite escribir toda la informacion actualizada en el txt

};

#endif // USUARIO_H
