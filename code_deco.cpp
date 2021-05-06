#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

string dectobin(int n);

string archivoBinario(string cadena);

int cerosYunos(string frac);

string encriptar (string act, int tipo);

string metodoUno (string bin, int sem);

string encriptar2(string frac);

string decodificacionUno (string bin, int sem);

string encriptar2(string frac);

string metodoDos(string bin, int sem);

string decoDos(string frac);

string decodificacionDos(string bin, int sem);

string lectura(string name);

int dos_exp (int exp);

int bintodec(string bin);

string represetacion (string cadBin);

void escribir(string name,string escritura);

int main()
{

    int opcion_principal = 1;

    while (opcion_principal!=0){

        cout << endl;
        cout << " +-----------------------------+" << endl;
        cout << " +        Menu principal       +" << endl;
        cout << " +-----------------------------+" << endl;
        cout << " + 1. Codificar archivos       +" << endl;
        cout << " + 2. Decodificar archivos     +" << endl;
        cout << " + 0. Para salir               +" << endl;
        cout << " +-----------------------------+" << endl;
        cout << endl;
        cout << " -> Seleccione una opcion: ";

        int opc_menu;
        cin >> opc_menu;

        if(opc_menu == 1){ // codificar archivos

            cout << endl;

            string name_entrada;
            cout << " -> Nombre del archivo a codificar (no incluya .txt): ";
            cin >> name_entrada;

            string name_salida;
            cout << " -> Nombre del archivo en el que se guarda la codificacion (no incluya .txt): ";
            cin >> name_salida;

            cout << endl;
            string texto_original = lectura(name_entrada+".txt");

            cout << endl;

            string texto_binario = archivoBinario(texto_original);


            cout << " +-----------------------------+" << endl;
            cout << " +    Metodo de codificacion   +" << endl;
            cout << " +-----------------------------+" << endl;
            cout << " + 1. Primer Metodo            +" << endl;
            cout << " + 2. Segundo Metodo           +" << endl;
            cout << " +-----------------------------+" << endl;
            cout << endl;
            cout << " -> Seleccione una opcion: ";
            int opc_met;
            cin >> opc_met;

            cout << " -> Escriba la semilla de codificacion: ";
            int semilla;
            cin >> semilla;

            if (opc_met == 1){
                string texto_cod = metodoUno(texto_binario,semilla);
                escribir(name_salida+".txt",texto_cod);
                cout << "  **<< La codificacion se guardo satisfactoriamente en: " << name_salida << ".txt  >>** " << endl;
                cout << endl;
            }

            else if (opc_met == 2){
                string texto_cod = metodoDos(texto_binario,semilla);
                escribir(name_salida+".txt",texto_cod);
                cout << "  **<< La codificacion se guardo satisfactoriamente en: " << name_salida << ".txt   >>** " << endl;
                cout << endl;
            }
        }


        else if (opc_menu == 2){ // decodificar archivos


            string name_entrada;
            cout << " -> Nombre del archivo a decodificar (no incluya .txt): ";
            cin >> name_entrada;

            string bin_codificado = lectura(name_entrada+".txt");
            string name_salida;
            cout << " -> Nombre del archivo en el que se guarda la decodificacion (no incluya .txt): ";
            cin >> name_salida;

            cout << endl;
            cout << " +------------------------------------------+" << endl;
            cout << " + Metodo con el que se codifco el archivo  +" << endl;
            cout << " +------------------------------------------+" << endl;
            cout << " + 1. Primer Metodo                         +" << endl;
            cout << " + 2. Segundo Metodo                        +" << endl;
            cout << " +------------------------------------------+" << endl;
            cout << endl;

            int opc_met;
            cout << " -> Seleccione el metodo: ";
            cin >> opc_met;


            cout << " -> Escriba la semilla con la que se codifico el archivo: ";
            int semilla;
            cin >> semilla;


            if (opc_met == 1){

                string bin_deco = decodificacionUno(bin_codificado,semilla);
                string tex_deco = represetacion(bin_deco);
                escribir(name_salida+".txt",tex_deco);
                cout << " **<<La decodificacion se guardo satisfactoriamente en: " << name_salida << ".txt >>** " << endl;
                cout << endl;
            }

            else if(opc_met == 2){

                string bin_deco = decodificacionDos(bin_codificado,semilla);
                string tex_deco = represetacion(bin_deco);
                escribir(name_salida+".txt",tex_deco);
                cout << "  **<<La codificacion se guardo satisfactoriamente en: " << name_salida << ".txt  >>**" << endl;
                cout << endl;
            }
        }


        else if (opc_menu == 0){ // salir del programa
            opcion_principal = 0;
        }

        else{
            cout << " ** Ingrese una opcion valida **" << endl;
        }
    }


    return 0;
}


string dectobin(int n){ // recibe un numero decimal y lo retorna en binario (string)
    int b;
    string vacio = "";
    string vacioinv = "";

    for (int i=0; i<8 ; i++){
        b = n%2;
        n = n/2;
        if (b==0){
            vacio.append("0");
        }
        else{
            vacio.append("1");
        }
    }
    for (int k=7; k>=0 ; k--){
        vacioinv.append(vacio.substr(k,1));
    }
    return vacioinv;
}

string archivoBinario(string cadena){ // recibe una cadena y la trasnforma en binario


    string palinbi;
    string vacio = "";
    int lon = cadena.length();
    int n;

    for (int i=0; i < lon ; i++){
        n = cadena[i];
        palinbi = dectobin(n);
        vacio.append(palinbi);
    }
    return vacio;
}

int cerosYunos(string frac){ // recibe una fraccion de un binario y devuelve 0-1-2 segun los ceros y unos

     // -> 1 = 49  0 = 48
    int len = frac.length();
    int cnt_0 = 0;
    int cnt_1 = 0;

    for (int k=0 ; k<len ; k++){

        if (frac[k] == 48){
            cnt_0++;
        }
        else if (frac[k] == 49){
            cnt_1++;
        }
    }
    if (cnt_0 > cnt_1){
        return 0;
    }
    else if(cnt_1 > cnt_0){
        return 1;
    }
    else{
        return 2;
    }
}

string encriptar (string act, int tipo){  // recibe un string para encriptar, con el tipo que se desee tipo puede ser 0, 1 o 2

    string nuevo = "";

    int len = act.length();

    if (tipo == 0){ // mas ceros que unos

        for(int k=0; k<len ; k++){
            if(( (k+1)% 2 ) == 0){
                if(act.substr(k,1) == "0"){
                    nuevo.append("1");
                }
                else{
                    nuevo.append("0");
                }
            }
            else{
                nuevo.append(act.substr(k,1));
            }
        }
    }

    else if (tipo == 1){ // mas unos que ceros
        for(int k=0; k<len ; k++){
            if(( (k+1)% 3 ) == 0){
                if(act.substr(k,1) == "0"){
                    nuevo.append("1");
                }
                else{
                    nuevo.append("0");
                }
            }
            else{
                nuevo.append(act.substr(k,1));
            }
        }
    }

    else{ // igual cantidad de cero que de unos
        for(int k=0; k < len; k++){

            if (act.substr(k,1)=="0"){
                nuevo.append("1");
            }
            else {
                nuevo.append("0");
            }
        }
    }

    return nuevo;

}

string metodoUno (string bin, int sem){ // Metodo uno, recibe un numero binario y una semilla para ecriptar

    int len = bin.length();
    int lim;

    string ant; // anterior grupo
    string act; // grupo actual
    string enc_vac = ""; // donde se va a almacenar todo el ecriptado
    string frac_enc;  // variable para guardar la encriptacion de cada grupo

    string primera = "";

    for (int k=0 ; k<sem ; k++){

        if ( bin.substr(k,1) == "0"){
            primera.append("1");
        }
        else{
            primera.append("0");
        }
    }
    enc_vac.append(primera);


    if ( len % sem == 0){
        lim = (len/sem);
    }
    else{
        lim = (len/sem)+1;
    }


    for (int i=1 ; i < lim; i++){
        ant = bin.substr((i-1)*sem,sem);
        act = bin.substr(i*sem,sem);
        frac_enc = encriptar(act,cerosYunos(ant)); // string de fraccion encriptdo
        enc_vac.append(frac_enc);
    }

    return enc_vac;
}

string decodificacionUno (string bin, int sem){ // recibe un binario para decodificar y una semilla

    int len = bin.length();
    int lim;
    int n;

    string bin_dec = "";
    string dec_frac;

    for(int k=0; k<sem ; k++){

        if (bin.substr(k,1) == "0" ){
            bin_dec.append("1");
        }
        else{
            bin_dec.append("0");
        }

    }

    if ( len % sem == 0){
        lim = (len/sem);
    }
    else{
        lim = (len/sem)+1;
    }

    for(int i=1 ; i <lim ; i++){

        n = cerosYunos(bin_dec.substr((i-1)*sem,sem));
        dec_frac = encriptar(bin.substr(i*sem,sem),n);
        bin_dec.append(dec_frac);
    }

    return bin_dec;

}

string encriptar2(string frac){ // encripata una FRACCION o GRUPO con el metodo 2

    string enc_vacio = "";

    int len = frac.length();

    enc_vacio.append(frac.substr(len-1,1));

    for (int i=0; i<(len-1) ; i++){
        enc_vacio.append(frac.substr(i,1));
    }

   return enc_vacio;

}

string metodoDos(string bin, int sem){ // Metodo dos, recibe un numero binario y una semilla para ecnriptar


    int len = bin.length();
    int lim;

    string fracc; // fraccion
    string encDos = "";

    if ( len % sem == 0){
        lim = (len/sem);
    }
    else{
        lim = (len/sem)+1;
    }

    for (int i=0 ; i < lim; i++){
        fracc = bin.substr(i*sem,sem);
        encDos.append(encriptar2(fracc));
    }
    return encDos;

}

string decoDos(string frac){ // decodifica una FRACCION o GRUPO con el metodo 2

    string enc_vacio = "";

    int len = frac.length();


    for (int i=1; i<len ; i++){
        enc_vacio.append(frac.substr(i,1));
    }

    enc_vacio.append(frac.substr(0,1));

   return enc_vacio;
}

string decodificacionDos(string bin, int sem){ // Decofifica, recibe un numero binario y una semilla para ecnriptar


    int len = bin.length();
    int lim;

    string fracc; // fraccion
    string encDos = "";

    if ( len % sem == 0){
        lim = (len/sem);
    }
    else{
        lim = (len/sem)+1;
    }

    for (int i=0 ; i < lim; i++){
        fracc = bin.substr(i*sem,sem);
        encDos.append(decoDos(fracc));
    }
    return encDos;

}

int dos_exp (int exp){
    int acu = 1;
    for (int i=0 ; i<exp ; i++){
        acu = acu*2;
    }
    return acu;
}

int bintodec(string bin){ // recibe un binario y retorna un decimal en tipo entero
    int dec = 0;
    for(int i=0; i<8 ; i++){
        if (bin.substr(i,1)=="1"){
                dec = dec + (dos_exp(7-i));
        }
    }
    return dec;
}

string represetacion (string cadBin){  // recibe un binario y retorna su palabra o texto correpondiente

    string palabra = "";
    int len = cadBin.length();
    int let;

    for (int i=0; i < len/8 ; i++){
        let = bintodec(cadBin.substr(i*8,8));
        palabra += let;
    }

    return palabra;
}

string lectura(string name){ // funcion que da lectura a un fichero y returna el string leido

    ifstream archivo;

    string texto;
    string linea;

    archivo.open(name,ios::in); // abrimos el archivo en modo lectura

    if(archivo.fail()){
        cout << " ** Asegurese que el archivo exista ** " << endl;
        cout << endl;
        exit(1);
    }

    while(!archivo.eof()){ // mientras no sea el final del archivo
        getline(archivo,linea);
        texto = texto + linea + "\n";
    }

    archivo.close(); // cerramos el archivo

    return texto;

}

void escribir(string name, string escritura){ // Recibe el nombre del fichero, y el string lo que va a escribir en el fichero

    ofstream archivo;
    archivo.open(name.c_str(),ios::out);

    if (archivo.fail()){
        cout << " ** Error al crear el archivo! ** " << endl;
        cout << endl;
        exit(1);
    }
    archivo<<escritura;
    archivo.close();
}

