#include <iostream> //Permite entrada y salida de comandos
#include <clocale> //libreria para usar tildes
#include <cstdlib> //libreria para limpiar pantalla, consultado 2 de octubre canal youtube AlgoritmosJavaYCpp
#include <string>
#include <cstring>// incluir para evitar -> cuando se utilizan funciones de la biblioteca de manejo de cadenas provoca errores de compilación.



using namespace std;

        bool esNumero(const string& str){ //se toma la cadena de caracteres y revisa que todo sean digitos
            for (char c : str){
                if (!isdigit (c)){ //sirve para comprobar si son numero 0-9
                    return false; //si encuentra letras, devuelve falso
            }
            }
            return true; ////si encuentra numeros, devuelve verdadero, tomado de 918 - Capítulo 22 Bits, caracteres, cadenas C y estructuras
        }

        bool esletra (const string& str){ //funcion parecida a la anterior pero para verificar si hay letras.
            for (char a : str){
                if (!isalpha (a)){
                    return false;
                }
            }
            return true;
        }

int main()
{

        string nomCliente, cedula, numMEDIDOR, m3;
        int opcion, consumo, montoTOTAL, impuesto, DIFFmetros;
        char exento;
        const float IVA = 0.13;
        const int Hidrantes = 182;
        const int costoM3 = 150;
        const int RecHidr = 50;
        const int Alcantarillado =1200;
        float total = 0;
        //int i=0;


        setlocale(LC_ALL,"Spanish"); //Para tildes y eñe - sirve en linux pero no windows

 do {        // <-- INICIA EL PROGRAMA
            //Muestra el menu
            cout<<"\t\t Menú \n\n"<<endl;//la t y la n, ponen sangria y salto de linea
            cout<<"\t 1. Ingresar datos. \n"<<endl;
            cout<<"\t 2. Recibo de consumo. \n"<<endl;
            cout<<"\t 3. Salir del programa. \n"<<endl;
            cout<<"\t Opción: ";
            cin>> opcion;//Lee elección usuario
            //Ciclo si elige opcion incorrecta.
                if (cin.fail() || opcion < 1 || opcion > 3) {  //cin.fail cuando intentan ingresar numero en vez de texto da falso, entonces se puede usar para descartar.
                cin.fail();
                cin.clear(); // Limpiar el flujo, segun pag 602 del libro de texto
                cout << "Opción inválida, vuelva a intentarlo.\n";

                } else {
            // Entrando al menú con la opción correcta.
                    switch (opcion) {
                        case 1:
                        cout<<"Has seleccionado 'Ingresar datos'.\n"<<endl;
                        cout<<"\tIngrese la siguiente información.\n" <<endl;
                        //Cedula
                        do{
                        cout<<"Ingrese el número de cédula del dueño del servicio (9 dígitos, sin guiones o espacios)\n"<<endl;
                        cin>>cedula;
                        }while((cedula.length() !=9) || (!esNumero (cedula)));

                        //Nombre
                        do{
                           cout<<"Ingrese el nombre completo (nombre y dos apellidos): "<<endl;
                            cin>>nomCliente; //lee linea de texto
                        }while((!esletra (nomCliente))); //hay que escribir bien length....


                        // Medidor
                        do {
                            cout<<"Ingrese el número del medidor (6 dígitos):"<<endl;
                            cin>>numMEDIDOR;
                            }while((numMEDIDOR.length()!=6) || (!esNumero(numMEDIDOR)));

                        // Consumo agua
                        do {
                        cout<<"Ingrese el valor de metros cúbicos del medidor (valor numérico): "<<endl;
                        cin>>m3;
                        } while(!esNumero(m3));
                        m3=consumo;
                         if (consumo <= 10) {
                            total = consumo*costoM3;
                        } else if ((consumo > 10) && (consumo <= 50)) {
                                   DIFFmetros=consumo-10;
                                   total = (10*costoM3)+((DIFFmetros*costoM3)+0.10); // 10% más
                        } else if ((consumo > 50) && (consumo <= 100)) {
                                   DIFFmetros=consumo-50;
                                   total = (10*costoM3)+(40*costoM3)+((DIFFmetros*costoM3)+0.20); // 20% más
                        } else {
                            total = (consumo*costoM3)+0.30; // 30% más
                        }


                            break;


                       case 2:
                        cout <<"\tHas seleccionado 'Recibo de Consumo'.\n"<<endl;
                        cout<<"\t\tRecibo de Consumo \n"<<endl;
                        cout<<"\t\tNúmero de cédula: "<<cedula<<endl;
                        cout<<"\t\tNombre de dueño del servicio: "<<nomCliente<<endl;

                        cout<<"\t\tNúmero del medidor: "<<numMEDIDOR<<endl;

                        cout<<"\t\tMetros cúbicos consumidos: "<<consumo<<endl;

                        cout<<"\t\tRecibo\n"<<endl;

                        cout<<"\t\tConsumo de Agua "<<consumo<<endl;
                        cout<<"\t\tHidrantes   "<<Hidrantes<<endl;

                        cout<<"\t\tProtección Recurso Hídrico "<<RecHidr<<endl;

                        cout<<"\t\tAlcantarillado "<<Alcantarillado<<endl;

                        cout<<"\t\tIVA: "<<impuesto<<endl;

                        cout<<"\t\tTOTAL a Pagar en colones: "<<montoTOTAL<<endl;

                        break;
                        }

                        }
 } while (opcion != 3); // Opcion para salir, se termina el programa.

    return 0;
