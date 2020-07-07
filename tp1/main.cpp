#include <iostream>
#include <fstream>
#include <complex>
#include "vector.h"
#include "cmdline.h"
#include "imagen.h"
#include "modulo_funcion_compleja.h"

//prueba de git y github
using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);

static option_t options[] = {
    {1, "i", "input", "-", opt_input, OPT_DEFAULT},   // stdin
    {1, "o", "output", "-", opt_output, OPT_DEFAULT}, // stdout
    {1, "f", "function", "z", opt_function, OPT_DEFAULT},
    {0, "h", "help", NULL, opt_help, OPT_DEFAULT},
    {0, },
};

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
static string funcion;


//transformacion_compleja modifica el contenido de una matriz utilizando la funcion compleja en formato rpn de la variable global funcion
//debe pasarse como parametros una matriz implementada mediante vector<vector<int>>, el ancho de la matriz (cantidad columnas) y el alto (cantidad filas)
void transformacion_compleja(vector<vector<int>> &, int, int);



int main(int argc, char * const argv[])
{
    cmdline cmdl(options);
    cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

    imagen imgin;
    imagen imgout;

    if((*iss) >> imgin){}
    else{
        cerr<<"error de entrada"<<endl;
        return 1;
    }
    imgout = imgin.transformar(transformacion_compleja);

    *oss << imgout;

    return 0;
}



static void
opt_input(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la entrada
    // estándar. De lo contrario, abrimos un archivo en modo
    // de lectura.
    if (arg == "-") {
        iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
    }
    else {
        ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
                                        // sequence of characters (i.e., a C-string) representing
                                        // the current value of the string object.
        iss = &ifs;
    }

    // Verificamos que el stream este OK.
    if (!iss->good()) {
        cerr << "cannot open "
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void
opt_output(string const &arg)
{
    // Si el nombre del archivos es "-", usaremos la salida
    // estándar. De lo contrario, abrimos un archivo en modo
    // de escritura.
    if (arg == "-") {
        oss = &cout;	// Establezco la salida estandar cout como flujo de salida
    } else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }

    // Verificamos que el stream este OK.
    if (!oss->good()) {
        cerr << "cannot open "
             << arg
             << "."
             << endl;
        exit(1);		// EXIT: Terminación del programa en su totalidad
    }
}

static void
opt_function(string const &arg){

    if(esta_balanceada(arg) && funcion_valida(arg)){//valida funcion entrada
        funcion = shutting_yard(arg);
    }else{
        cerr<<"funcion de entrada no valida"<<endl;
        exit(1);
    }

}

static void
opt_help(string const &arg){
    cout << "tp0 [-i in.pgm] [-o out.pgm] -f \"funcion\""  << arg << endl;
    exit(0);
}

void transformacion_compleja(vector<vector<int>> & matriz, int ancho, int alto){

    vector<vector<int>> original = matriz;

    double anchopx, altopx;

    anchopx = 2.0/ancho;
    altopx = 2.0/alto;
    double x,y;
    complex <double>  z;
    int subx, suby;

    for(int i = 0; i < alto; i++){
        for(int j = 0; j < ancho; j++){

            x = ((2.0*j+1.0)/ancho)-1.0;
            y = ((2.0*i+1.0)/alto)-1.0;

            z.real(x);
            z.imag(y);
            z = evaluar_expresion_rpn(funcion, z);

            if(z.real() <= -1 || z.real() >= 1 || z.imag() <= -1 || z.imag() >= 1){

                matriz[i][j] = 0;

            } else {

                subx = (z.real()+1.0)/anchopx;
                suby = (z.imag()+1.0)/altopx;
                matriz[i][j] = original[suby][subx];
            }
        }
    }
}
