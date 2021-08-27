#include "usuario.h"

usuario::usuario()
{

}

void usuario::lectura()
{
    ifstream infile;

    string renglon;
    int i=0;

     infile.open(mArchivo);

     if (!infile.is_open())
          {
            cout << "Error abriendo el archivo" << endl;
            exit(1);
          }

          while(!infile.eof()){
               i++;
               if(i>1){
                   mBaseDatos+='\n';
               }

               getline(infile,renglon);
               mBaseDatos+=renglon;


          }


          infile.close();



}

void usuario::verificar_Usuario(string documento)
{
    string docBase="";
    int tamanioDoc=56;
    int posicion=0;
    int lim=(mBaseDatos).length();

    for(int index=posicion;index<lim;index++){
        if(mBaseDatos[index]=='\n'){
            for(int elem=1;elem<=tamanioDoc;elem++){
                docBase+=mBaseDatos[index+elem];
                posicion=index+elem;
            }

            docBase=decotwo(docBase);
            docBase=BinaryStringToText(docBase);

            if(docBase==documento){
                mIndice=posicion;
                cout<<"El usuario existe ";
                break;

            }
            else {
                docBase="";
            }
        }

        else{
            if(index==(lim-1)){
                cout<<"El usuario con doc "<<documento<<" no existe "<<endl;
                mIndice=0;
            }
        }
    }


}

bool usuario::verificar(string clave_ingresada)
{
    string clave_Decod="";

    bool correcto = false;
    int i=0;

    while(mBaseDatos[i]!='\n'){
        clave_Decod+=mBaseDatos[i];
        i++;
    }

    clave_Decod=decotwo(clave_Decod);
    clave_Decod=BinaryStringToText(clave_Decod);

    if(clave_Decod==clave_ingresada){
        correcto=true;
    }

    else{
        correcto=false;
    }

    return correcto;
}

bool usuario::verificar_Contrasena( string contrasena)
{
    bool contraBien=false;
    string contraBase="";
    mIndice+=1;

    for(int k=1;k<=32;k++){
        contraBase+=mBaseDatos[mIndice+k];
    }

    contraBase=decotwo(contraBase);
    contraBase=BinaryStringToText(contraBase);

    if (contrasena==contraBase){
        contraBien=true;
    }
    else{
        contraBien=false;
    }
    return contraBien;

}

void usuario::Registar()
{
    fstream fileAdd;
    string nuevo_Usuario="";
    string Doc;
    string Clave;
    string Saldo;

    cout<<"Ingrese nuevo usuario con el formato: "<<endl;
    cout<<"Documento(7 digitos) : ";cin>>Doc;
    cout<<"Clave(4digitos) : ";cin>>Clave;
    cout<<"Saldo : ";cin>>Saldo;

    Doc=binario(Doc);
    Doc=codtwo(Doc);

    Clave=binario(Clave);
    Clave=codtwo(Clave);

    Saldo=binario(Saldo);
    Saldo=codtwo(Saldo);

    nuevo_Usuario=Doc+","+Clave+","+Saldo;

    fileAdd.open( mArchivo.c_str(), ios::app);
    fileAdd <<nuevo_Usuario;
    fileAdd.close();
}

string usuario::decotwo(string cadena_codificada)
{

        int n=4;
        string cadena_Decod="";
        int j=(n-1);
        int tamano=cadena_codificada.length();
        int lon=(tamano)/n;
        int modulo=(tamano)%n;
        int falta=modulo-1, seguir=0;


        //Si el string en binario se puede dividir exactamente en grupos de n bits:
        if (modulo==0){

             while(seguir<lon){

                 for(int indice=(j-1);indice>=0;indice--){
                 cadena_Decod+=cadena_codificada[((seguir*n)+j)-indice];

                 }
                 cadena_Decod+=cadena_codificada[(seguir*n)];

                 seguir++;//contador que indica la cantidad de bloques procesados

                  }


              }


        //Si el string en binario se puede dividir exactamente en grupos de n bits:
        else{

            while(seguir<lon){

                for(int indice=(j-1);indice>=0;indice--){
                cadena_Decod+=cadena_codificada[((seguir*n)+j)-indice];
                }
                cadena_Decod+=cadena_codificada[(seguir*n)];

                seguir++;

                 }


            for(int i=(falta-1);i>=0;i--){
                cadena_Decod+=cadena_codificada[(tamano-1)-i];

            }

             cadena_Decod+=cadena_codificada[tamano-modulo];

        }
        return cadena_Decod;
}

string usuario::codtwo(string cadena_Binaria)
{
    string cadena_codificada="";
    int n=4;
    int j=(n-1);
    int tamano=cadena_Binaria.length();
    int lon=(tamano)/n;  //cantidad de bloques de n bits
    int modulo=(tamano)%n; //variable que indica la cantidad de elementos sobrantes en caso de que la
                           //la cadena_Binaria(string del ASCC), no se pueda dividir exactamente en bloques
                           //de n bits
    int falta=modulo-1, seguir=0;


    //Si el string en binario se puede dividir exactamente en grupos de n bits:
    if (modulo==0){

         while(seguir<lon){

             cadena_codificada+=cadena_Binaria[(seguir*n)+j];
             for(int indice=j;indice>0;indice--){
             cadena_codificada+=cadena_Binaria[((seguir*n)+j)-indice];


             }

             seguir++;//contador que indica la cantidad de bloques procesados

              }


         }


    //Si el string en binario se puede dividir exactamente en grupos de n bits:
    else{

        while(seguir<lon){

            cadena_codificada+=cadena_Binaria[(seguir*n)+j];

            for(int indice=j;indice>0;indice--){
            cadena_codificada+=cadena_Binaria[((seguir*n)+j)-indice];
            }

            seguir++;

             }
        cadena_codificada+=cadena_Binaria[tamano-1];
        for(int i=falta;i>0;i--){
            cadena_codificada+=cadena_Binaria[(tamano-1)-i];

        }


    }
    return cadena_codificada;

}

string usuario::BinaryStringToText(string Cadena_Cod)
{
    int tamCad= Cadena_Cod.length(),multiplicador=1;
      int decimal=0;

      string CadTxt;

      for(int cont=0;cont<tamCad/8;cont++){
          multiplicador=1;
          decimal=0;
            for(int elem=0, palBin=(cont + 1)*8-1 ; elem<8 ; elem++,palBin--){
                if (Cadena_Cod[palBin] == '1'){
                    decimal += multiplicador;
                }
                multiplicador = multiplicador*2;
            }
            CadTxt+=decimal;
      }

    return CadTxt;

}


string usuario::Consultar_Saldo()
{
    string saldo="";
    string Saldo_Final="";
    int index_saldo=mIndice+33;
    int indiaux=index_saldo+1;
    int lim=mBaseDatos.length();
    int nuevo_saldo=0;
    int saldoNumber=0;
    int lon_Saldoviejo=0;

    while(mBaseDatos[indiaux]!='\n'){
         saldo+=mBaseDatos[indiaux];
         indiaux++;

    }

    saldo=decotwo(saldo);
    saldo=BinaryStringToText(saldo);
    cout<<"Su saldo es : "<<saldo;

    saldoNumber=stoi(saldo);
    nuevo_saldo=saldoNumber-1000;

    Saldo_Final=to_string(nuevo_saldo);
    Saldo_Final=binario(Saldo_Final);
    Saldo_Final=codtwo(Saldo_Final);

    int largo_Saldo=Saldo_Final.length();
    int ubicacion=index_saldo+largo_Saldo;

    indiaux=index_saldo+1;

    while((mBaseDatos[indiaux])!='\n'){
          lon_Saldoviejo++;
          indiaux++;
    }

    lim=lim-lon_Saldoviejo+largo_Saldo;

    for(int i=0,j=0;i<lim;i++){
        if(i<=index_saldo){
            mNuevaData+=mBaseDatos[i];
        }
        else if((ubicacion>=i) && (i>index_saldo)){
            mNuevaData+=Saldo_Final[j];
            j++;

        }
        else{
            mNuevaData+=mBaseDatos[ubicacion+1];
            ubicacion++;
        }

    }

    escritura();

}

void usuario::Retirar_Dinero()
{
    string saldo="";
    string Saldo_Final="";
    int index_saldo=mIndice+33;
    int indiaux=index_saldo+1;
    int lim=mBaseDatos.length();
    int nuevo_saldo=0;
    int saldoNumber=0;
    int lon_Saldoviejo=0;
    int retiro=0;

    cout<<"Ingrese cantidad a retirar : "<<endl;cin>>retiro;


    while(mBaseDatos[indiaux]!='\n'){
         saldo+=mBaseDatos[indiaux];
         indiaux++;

    }

    saldo=decotwo(saldo);
    saldo=BinaryStringToText(saldo);


    saldoNumber=stoi(saldo);

    if((retiro+1000)<=saldoNumber){
    nuevo_saldo=saldoNumber-retiro;

    Saldo_Final=to_string(nuevo_saldo);
    Saldo_Final=binario(Saldo_Final);
    Saldo_Final=codtwo(Saldo_Final);
    }

    else{
        cout<<"Saldo insuficiente "<<endl;
    }

    int largo_Saldo=Saldo_Final.length();
    int ubicacion=index_saldo+largo_Saldo;

    indiaux=index_saldo+1;

    while((mBaseDatos[indiaux])!='\n'){
          lon_Saldoviejo++;
          indiaux++;
    }

    lim=lim-lon_Saldoviejo+largo_Saldo;

    for(int i=0,j=0;i<lim;i++){
        if(i<=index_saldo){
            mNuevaData+=mBaseDatos[i];
        }
        else if((ubicacion>=i) && (i>index_saldo)){
            mNuevaData+=Saldo_Final[j];
            j++;

        }
        else{
            mNuevaData+=mBaseDatos[ubicacion+1];
            ubicacion++;
        }

    }

    escritura();


}

string usuario::binario(string palabra)
{
    int c;
    string palbin;

    for (int i=0;palabra[i]!='\0';i++){
        c=palabra[i];
        for(int j=7;j+1>0;j--){
            if(c>=(1<<j)){
                c=c-(1<<j);
                palbin+="1";

            }
            else{
               palbin+="0";
            }
        }
    } return palbin;
}


void usuario::escritura()
{
    ofstream outfile;

    outfile.open(mArchivo);

    if (!outfile.is_open()){
        cout<<"Error abriendo el archivo de escritura"<<endl;
        exit(1);
    }

    outfile<<mNuevaData;

    outfile.close();

}

