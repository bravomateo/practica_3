#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>


/*
La clave del administrador es: info_cajero

la codificacion y decodificion es metodo 2-semilla 3

el archivo donde se guarda la clave es sudo.txt
el archivo donde se guardan los datos de los usuarios es datos.txt

*/


using namespace std;

string lectura(string name);

void agregar(string linea);

// funciones para consulta y retiro

int verificarId(int id_inp);

int filaId(int id_ver);

int retiro_consulta(int fila, int retirar);

void escribir(string texto);

int claveId(int fila, int retirar);

int nFilas();

string clave(int fila);


// funciones de encriptacion (metodo 2 y semilla 3)

string dectobin(int n);

string archivoBinario(string cadena);

string encriptar2(string frac);

string metodoDos(string bin, int sem);

string decoDos(string frac);

string decodificacionDos(string bin, int sem);

int dos_exp (int exp);

int bintodec(string bin);

string represetacion (string cadBin);


int main()
{


    int ciclo = 1;

    while(ciclo == 1){

        cout << endl;
        cout << " +----------------------------------+" << endl;
        cout << " +           Menu principal         +" << endl;
        cout << " +----------------------------------+" << endl;
        cout << " + 1. Ingresar como administrador   +" << endl;
        cout << " + 2. Ingresar como usuario         +" << endl;
        cout << " + 0. Para salir del programa       +" << endl;
        cout << " +----------------------------------+" << endl;

        cout << endl;
        cout << " Seleccione una opcion: ";
        int opc_menu;
        cin >> opc_menu;
        cout << endl;


        if (opc_menu == 1){ // administrador

            cout << " +-----------------------------------+" << endl;
            cout << " +       Menu de adiministrador      +" << endl;
            cout << " +-----------------------------------+" << endl;

            string claveTry;
            cout << endl;
            cout << "  -> Ingrese clave de administrador: " ;
            cin >> claveTry;

            string claveAdm = lectura("sudo.txt");

            if (claveTry == represetacion(decodificacionDos(claveAdm,3))){

                cout << endl;
                cout << " -> Clave correcta! " << endl;
                string datos = "";

                cout << endl;
                cout << " +-----------------------------------+" << endl;
                cout << " ** >>>> Registro de usuarios <<<<  **" << endl;
                cout << " +-----------------------------------+" << endl;
                int cedula;
                cout << endl;
                cout << "  -> Ingrese la cedula del usuario: ";
                cin >> cedula;

                if(verificarId(cedula) == 0){ // verificar la no existencia del usuario

                    string cedulastr = to_string(cedula);
                    datos.append(cedulastr);
                    datos.append(" ");

                    string clave;
                    cout << "  -> Ingrese la clave del usuario: " ;
                    cin >> clave;
                    datos.append(metodoDos(archivoBinario(clave),3));
                    datos.append(" ");

                    string saldo;
                    cout << "  -> Ingrese el saldo (COP) del usuario: ";
                    cin >> saldo;

                    datos.append(metodoDos(archivoBinario(saldo),3));
                    datos.append("\n");
                    agregar(datos);

                    cout << endl;

                    }

                    else{
                        cout << endl;
                        cout << ">>*** La cedula: " << cedula << " ya fue registrada ***<<" << endl;
                        cout << endl;

                    }

            }
            else{
                cout << endl;
                cout << " ** -->  Lo sentimos, clave incorrecta!  <-- **" << endl;
                cout << endl;
            }
        }


        // usuario

        else if(opc_menu == 2){ // usuario

            cout << " +-------------------------+" << endl;
            cout << " +     Menu de usuario     +" << endl;
            cout << " +-------------------------+" << endl;

            cout << "  -> Ingrese su cedula: ";
            int IdUser;
            cin >> IdUser;

            cout << "  -> Ingrese su clave: ";
            string PassUser;
            cin >> PassUser;

            string PassTrue = represetacion(decodificacionDos(clave(filaId(IdUser)),3));

            if(verificarId(IdUser) == 1) {  // verificar si el Id existe en la base de datos

                if(PassUser == PassTrue){  // verificar la clave del usuario

                    cout << " -> Clave correcta! " << endl;

                    cout << endl;
                    cout << " +--------------------------------+" << endl;
                    cout << " + 1. Consultar saldo             +" << endl;
                    cout << " + 2. Retirar dinero              +" << endl;
                    cout << " +--------------------------------+" << endl;
                    cout << endl;
                    cout << "Seleccione una opcion: ";
                    int opc_op;
                    cin >> opc_op;

                    if(opc_op == 1){ // consultar saldo

                        int fila =  filaId(IdUser);

                        int consulta = retiro_consulta(fila,1000);

                        cout << "  ** Su saldo antes de la consulta fue: " << consulta +1000 << " **"<<endl;
                        cout << "  ** Su saldo despues de la consulta es: " << consulta << " **"<< endl;
                        cout << endl;
                    }

                    else if(opc_op == 2){ // retirar dinero

                        cout << endl;
                        cout << "  -> Cantidad que desea retirar: ";
                        int ret_us;
                        cin >> ret_us;

                        int fila =  filaId(IdUser);

                        int retiro = retiro_consulta(fila,ret_us);
                        cout << endl;
                        cout << " ** Su retiro fue de : " << ret_us <<" **"<< endl;
                        cout << " ** Su saldo es: " << retiro << " **"<< endl;
                        cout << endl;
                    }
                }

                else{
                    cout << " ** -->  Lo sentimos, clave incorrecta!  <-- **" << endl;
                }
            }

            else{
                cout << ">>** Lo sentimos, la su cedula no ha sido registrada: " << IdUser << " <<**" << endl;
            }

            // cout << retiro_consulta(filID,130) << endl;
        }


        else if(opc_menu == 0){
            ciclo = 0;
        }
    }

    return 0;

}

// funciones

// funciones para la escritura y lectura

string lectura(string name){ // funcion que da lectura a un fichero y returna el string leido

    ifstream archivo;
    string texto;
    string linea;

    archivo.open(name,ios::in); // abrimos el archivo en modo lectura

    if(archivo.fail()){
        cout << "Error al abrir SUDO.TXT" << endl;
        exit(1);
    }

    while(!archivo.eof()){ // mientras no sea el final del archivo
        getline(archivo,linea);
        texto = texto + linea;
    }

    archivo.close(); // cerramos el archivo

    return texto;

}

void agregar(string linea){ // agrega linea al archivo que se desee

    ofstream archivo;

    archivo.open("datos.txt",ios::app);

    if(archivo.fail()){
        cout << "Error al crear usuario" << endl;
        exit(1);
    }

    archivo << linea;

    archivo.close();

}


// funciones para el consulta y retiro

int verificarId(int id_inp){

    /*
    verifica si el id está en la base de datos
    retorna 0 si no está el id
    retorna 1 si está el id
    */

    fstream archivo;

    string vacio = "";
    string texto;

    archivo.open("datos.txt",ios::in);

    if(archivo.fail()){
        cout << "Error! DATOS.TXT no existe" << endl;
        exit(1);
    }

    int cnt = 0;

    while(!archivo.eof()){

        getline(archivo,texto);
        int len = texto.length();
        string ced = "";

        for (int i=0 ; i<len; i++){

            if(texto.substr(i,1)==" "){
                break;
            }
            ced += texto.substr(i,1);
        }
        if (ced == to_string(id_inp)){
            cnt++;
        }
    }

    if(cnt!=0){
        return 1;
    }
    else{
        return 0;
    }
}

int filaId(int id_ver){

    /* retorna la fila en la que está el ID */
    fstream archivo;

    string vacio = "";
    string texto;

    archivo.open("datos.txt",ios::in);

    if(archivo.fail()){
        cout << "Error! DATOS.TXT no existe" << endl;
        exit(1);
    }

    int cnt = 0;

    while(!archivo.eof()){

        getline(archivo,texto);
        int len = texto.length();
        string ced = "";

        for (int i=0 ; i<len; i++){

            if(texto.substr(i,1)==" "){
                break;
            }
            ced += texto.substr(i,1);
        }
        cnt++;
        if (ced == to_string(id_ver)){
            break;
        }
    }
    return cnt;
}

int retiro_consulta(int fila, int retirar){


    /*
    recibe como parametro el numero de fila del Id y el valor a para retirar retorna el saldo despues
    de hecho la consulta (resta 1000)
    */

    fstream archivo;
    archivo.open("datos.txt",ios::in);

    if(archivo.is_open()){

        string id;
        string clave;
        string saldo;
        string dato = "";
        string saldoRes;
        string datos = "";
        string saldoDeco;

        int mod_saldo=0;
        int cnt = 0;
        while(cnt != nFilas()){

            archivo >> id >> clave >> saldo;
            cnt ++;

            if( cnt != fila){
                datos += id + " " + clave + " " + saldo + "\n";
            }
            else if (cnt == fila){
                saldoDeco = represetacion(decodificacionDos(saldo,3));
                mod_saldo = atoi(saldoDeco.c_str()) - retirar;
                datos += id + " " + clave + " " + metodoDos(archivoBinario(to_string(mod_saldo)),3) + "\n";
            }
        }
        escribir(datos);
        archivo.close();
        return mod_saldo;
    }
    return 0;
}

void escribir(string texto){

    ofstream archivo;
    archivo.open("datos.txt",ios::out);

    if(archivo.fail()){
        cout << "No se puede abrir el archivo";
        exit(1);
    }

    archivo << texto;
    archivo.close();
}

int nFilas(){ // retorna el numero de filas del documento

    int numLines = 0;
    ifstream in("datos.txt");
    //while (! in.eof())
    while (in.good())
    {
        std::string line;
        std::getline(in, line);
        ++numLines;
    }
    return numLines-1;
}

string clave(int fila){

    /*
    recibe un int fila, que significa en la fila que está
    el ID, y retorna la clave del ID
    */

    fstream archivo;

    string vacio = "";
    string texto;
    string claveFila;

    int conta = 1;

    archivo.open("datos.txt",ios::in);

    if(archivo.fail()){
        cout << "Error! DATOS.TXT no existe" << endl;
        exit(1);
    }

    while(!archivo.eof()){

        int cnt = 0;
        getline(archivo,texto);
        int len = texto.length();
        string clave = "";

        for (int i=0 ; i<len; i++){

            if(texto.substr(i,1)==" "){
                cnt = 1;
            }

            if(cnt == 1){
                if (texto.substr(i+1,1) != " "){
                    clave += texto.substr(i+1,1);
                }
                else if(texto.substr(i+1,1)== " "){
                    break;
                }
            }
        }

        if(conta == fila){
            claveFila = clave;
        }
        conta++;
    }
    return claveFila;
}


// funciones de encriptacion (metodo 2 y semilla 3)


// Representacion de una cadena en binario

string dectobin(int n){ // recibe un numero decimal y lo retorna en binario en string
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

string archivoBinario(string cadena){ // recibe una cadena y la trasnforma en binario ((?))

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

// codificacion

string encriptar2(string frac){ // codifica una FRACCION o GRUPO de 1s y 0s con metodo 2

    string enc_vacio = "";

    int len = frac.length();

    enc_vacio.append(frac.substr(len-1,1));

    for (int i=0; i<(len-1) ; i++){
        enc_vacio.append(frac.substr(i,1));
    }
   return enc_vacio;

}

string metodoDos(string bin, int sem){ // recibe una cadena de 1s y 0s (la conversion de texto a binario) y una semilla para encriptar


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

// decodificacion

string decoDos(string frac){ // decodifica una FRACCION o GRUPO de 1s y 0s con metodo 2

    string enc_vacio = "";

    int len = frac.length();


    for (int i=1; i<len ; i++){
        enc_vacio.append(frac.substr(i,1));
    }

    enc_vacio.append(frac.substr(0,1));

   return enc_vacio;
}

string decodificacionDos(string bin, int sem){ // recibe un numero binario y una semilla para ecnriptar para decodificar

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

// represetacion

int dos_exp (int exp){ // 2^exp = acu
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
