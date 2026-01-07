#include <iostream>
#include <string> //para usar string
#include <clocale>
#include <limits> // Se va usar una funcion especifica para que el programa no se vaya a un bucle infinito por una entrada incorrecta.
#include <cstdlib>
#include <fstream> // para usar la funcion de oftream
#include <vector>
#include <algorithm> //para usar all-of
#include <sstream> //para validar la fecha


using namespace std;



class Pieza { // almacena informacion sobre la pieza
    private:
        string codigo;
        string nombre;
        double costo;
        int cantidad;
        string empresa;
        string factura;
        string cedula;

    public:
        //constructor con parametros
        Pieza(string cod, string nom,double cost, int cant, string emp, string fact, string ced){
        codigo = cod;
        nombre = nom;
        costo = cost;
        cantidad = cant;
        empresa = emp;
        factura = fact;
        cedula = ced;
        }
        //Constructor por defecto
        Pieza() {};

// mostrar informacion pieza
void mostrarInfo(){
    cout << "Pieza con "
         << "Código: " << codigo << ", "
         << "Nombre: " << nombre << ", "
         << "Costo: " << costo << ", "
         << "Cantidad: " << cantidad << ", "
         << "Empresa: " << empresa << ", "
         << "Factura: " << factura << ", "
         << "Cédula: " << cedula << ", " << endl;
    }

// Métodos 'get' y 'set' para cada atributo
string getCodigo() const {return codigo; }
void setCodigo(string cod) { codigo = cod; }

string getNombre()const {return nombre; }
void setNombre(string nom) { nombre = nom; }

double getCosto()const {return costo; }
void setCosto (double cost) { costo = cost; }

int getCantidad()const {return cantidad; }
void setCantidad(int cant) { cantidad = cant; }

string getEmpresa()const {return empresa; }
void setEmpresa(string emp) { empresa = emp; }

string getFactura()const {return factura; }
void setFactura(string fact) { factura = fact; }

string getCedula()const {return cedula; }
void setCedula(string ced) { cedula = ced;}
};


//*******FUNCIONES*******

// mostrar informacion pieza
void mostrarInfo(){
    cout << "Código: " << codigo << ", "
         << "Código de la pieza: " << codigoPieza << ", "
         << "Cantidad: " << cantidad << ", "
         << "Identificacion del empleado: " << identificacionEmpleado << ", "
         << "Fecha de solicitud: " << fechaSolicitud << ", "
         << "Estado: " << estado << endl;
    }
//pide y pone valores
string getCodigo() {return codigo;}
void setCodigo(string cod) {codigo = cod; }
};

//Declacion funciones globales
void mostrarMenu();
void limpiarPantalla();
bool revisaEntrada(int& opcion);
void guardarPiezaArchivo(const Pieza& pieza);
vector<Pieza> inventario;
void ingresarPieza();
void modificarPieza();
void consultarPieza();
void eliminarPieza();

void mostrarMenu (){
    cout << "1. Inventario \n";
    cout << "\t a. Ingresar pieza al inventario.\n";
    cout << "\t b. Consultar pieza del inventario.\n";
    cout << "\t c. Modificar pieza del inventario. \n";
    cout << "\t d. Eliminar pieza del inventario\n";
    cout << "2. Pedido \n";
    cout << "\t a. Ingreso de pedido\n";
    cout << "\t b. Consulta de pedido \n";
    cout << "\t Registrar entrega de pedido\n";
    cout << "3. Reporte de Inventario\n";
    cout << "4. Reporte de pedidos \n";
    cout << "6. Salir\n";
    cout << "Ingrese una opción: ";
}


void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Comando para Windows
    #else
        system("clear"); // Comando para Unix
    #endif
}

bool revisaEntrada (int& opcion) { //int& opcion, funcion que permite pasar por referencia la variable original, es decir, cualquier cambio dentro de la función afecta la variable original y asi garantiza que se actualice correctamente.
    cin >> opcion;
    while (cin.fail() || opcion < 1 || opcion > 6){
        limpiarPantalla();
        cout << "Opción inválida, vuelve a intentarlo." << endl;
        cin.clear(); //limpia el error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Cuando introducimos datos incorrectos, esos datos quedan en el búfer, esta linea es un filtro que elimina los datos incorrectos hasta dar con la entrada limpia, marcada por el salto de línea. Asi, aseguramos que cualquier entrada errónea sea ignorada y no afecte futuras entradas.
        cout << "Presione Enter para continuar...";
        cin.get();
        mostrarMenu();
        //cout << "Ingrese una opción: ";
        cin >> opcion;
    }
    return true;
}

//Revisa que la fecha sea del tamaño adecuado
bool validarFecha(const string& fecha) {
    if (fecha.length() != 10)
        return false;
    if ((fecha[2] != '/') || (fecha[5] != '/'))
        return false;

//Uso de la clase isstringsteam para extraer la informacion de la fecha
    int cant, dia, mes, anho;
    char barra1, barra2;
    istringstream iss(fecha);
    iss >> dia >> barra1 >> mes >> barra2 >> anho;

    if ((iss.fail()) || (barra1 != '/') || (barra2 != '/'))
        return false;
    if ((dia < 1) || (dia > 31) || (mes < 1) || (mes > 12))
        return false;
//Valida dias de meses de 30 dias
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
        return false;
    return true;
    }


//Opcion a
void ingresarPieza(){
    string cod, nom, emp, fact, ced;
    double cost;
    int cant;

        cout << "Ingrese el código de la pieza (Formato: P#######): ";
        cin >> cod;
        while ((cod [0] != 'P') || (cod.length() != 9)){
        cout << "Código de pieza incorrecto. Formato correcto: P#######. Intente nuevamente: ";
        cin >> cod;
        }
        cout << "Ingrese el nombre de la pieza: ";
        cin.ignore();
        getline(cin, nom);

        cout << "Ingrese el costo de la pieza: ";
        cin >>  cost;
        while (cin.fail() || cost < 0){
        cout << "Costo incorrecto. Debe ser un número positivo. Intente nuevamente: .";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cost;
        }

        cout << "Ingrese la cantidad de piezas: ";
        cin >> cant;
        while ((cin.fail()) || (cant < 0)){
        cout << "Cantidad incorrecta. Debe ser un número positivo. Intente nuevamente: .";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cant;
        }

        cout << "Ingrese el nombre de la empresa que provee las piezas: ";
        cin.ignore();
        getline(cin, emp);

        cout << "Ingrese la factura de la empresa: ";
        getline(cin, fact);

        cout << "Ingrese su cédula (9 dígitos): ";
        cin >> ced;
        while ((ced.length() != 9) || (!all_of(ced.begin(), ced.end(), ::isdigit))){
        cout << "Cédula incorrecta. Debe tener 9 dígitos. Intente nuevamente: ";
        cin >> ced;
        }

//objeto Pieza usando constructor
    Pieza nuevaPieza(cod, nom, cost, cant, emp, fact, ced);

//Guardar la informacion
    guardarPiezaArchivo(nuevaPieza);
//    inventario.push_back(nuevaPieza); ARREGLAR ESTO DE AQUI PARA GUARDAR EN UN VECTOR
}

//Opcion c
void modificarPieza(){
    string codigoPieza;
    cout << "Ingrese el código de la pieza a modificar: ";
    cin >> codigoPieza;

    //vector<Pieza> inventario = subirInventario();
    bool encontrado = false;

    //Busqueda en el inventario la pieza usando el codigo
    for (auto& pieza : inventario){
        if (pieza.getCodigo() == codigoPieza){
            encontrado = true;

//Mostrar informacion actual de la pieza
            cout << "Informacíon actual de la pieza \n";
            pieza.mostrarInfo();

//Pedir nuevos datos y actualizar
            string nuevoNombre, nuevaEmpresa, nuevaFactura, nuevaCedula;
            double nuevoCosto;
            int nuevaCantidad;

            cout << "Ingrese el nuevo nombre de la pieza: ";
            cin.ignore();
            getline(cin, nuevoNombre);

            cout << "Ingrese el nuevo costo de la pieza: ";
            cin >> nuevoCosto;
            cin.ignore();
            while ((cin.fail ()) || (nuevoCosto < 0)){
                    cout << "Costo incorrecto. Deber ser un número positivo. Intente de nuevo: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> nuevoCosto;
            }

            cout << "Ingrese la nueva cantidad de piezas: ";
            cin >> nuevaCantidad;
            cin.ignore();
            while ((cin.fail()) || (nuevaCantidad < 0)){
                    cout << "Cantidad incorrecta. Deber ser un número positivo. Intente de nuevo: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> nuevaCantidad;
            }

            cout << "Ingrese el nuevo nombre de la empresa: ";
            cin.ignore();
            getline(cin, nuevaEmpresa);

            cout << "Ingrese la nueva factura de la empresa: ";
            getline(cin, nuevaFactura);

            cout << "Ingrese la nueva cédula (9 dígitos): ";
            cin >> nuevaCedula;
            while ((nuevaCedula.length() != 9) || (!all_of(nuevaCedula.begin(), nuevaCedula.end(), ::isdigit))){
                cout << "Cédula incorrecta. Debe tener 9 dígitos. Intente nuevamente: ";
                cin >> nuevaCedula;
            }

            //Actualizando la pieza
            pieza.setNombre(nuevoNombre);
            pieza.setCosto(nuevoCosto);
            pieza.setCantidad(nuevaCantidad);
            pieza.setEmpresa(nuevaEmpresa);
            pieza.setFactura(nuevaFactura);
            pieza.setCedula(nuevaCedula);

            cout << "Pieza modificada correctamente." << endl;
            break;
        }
}

if (!encontrado){
    cout << "Pieza no encontrada." << endl;
} else {
    ofstream archivo("Inventario.txt", ios::trunc);
    if (archivo.is_open()){
        for (const auto& pieza : inventario){
            archivo << pieza.getCodigo() << " ";
            archivo << pieza.getNombre() << " ";
            archivo << pieza.getCosto() << " ";
            archivo << pieza.getCantidad() << " ";
            archivo << pieza.getEmpresa() << " ";
            archivo << pieza.getFactura() << " ";
            archivo        << pieza.getCedula() << endl;
        }
        archivo.close();
        cout << "Pieza modificada correctamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo para guardar los cambios" << endl;
    }
    }
}

//Guardar pieza en archivo
void guardarPiezaArchivo(const Pieza& pieza){ //const Pieza& significa pasan objeto Pieza por referencia, y const asegura que la función no modifique ese objeto
    ofstream archivo("Inventario.txt", ios::app);//tipo de datos  para crear objetos que puedan escribir datos en archivos //todo lo que escribas en el archivo se añadirá al final del mismo, sin borrar el contenido existente.
    if (archivo.is_open()){
        archivo << pieza.getCodigo() << " "
                << pieza.getNombre() << " "
                << pieza.getCosto() << " "
                << pieza.getCantidad() << " "
                << pieza.getEmpresa() << " "
                << pieza.getFactura() << " "
                << pieza.getCedula() << endl;
        archivo.close ();
    } else {
        cout << "No se pudo abrir el archivo para guardar la pieza" << endl;
    }
    }

//subir archivo de inventario
vector <Pieza> subirInventario(){
    vector<Pieza> inventario;
    ifstream archivo("Inventario.txt");
    if (archivo.is_open()){
                string codigo, nombre, empresa, factura, cedula;
                double costo;
                int cantidad;
            while (archivo >> codigo >> nombre >> costo >> cantidad >> empresa >> factura >> cedula){
                Pieza pieza;
                pieza.setCodigo(codigo);
                pieza.setNombre (nombre);
                pieza.setCosto(costo);
                pieza.setCantidad(cantidad);
                pieza.setEmpresa(empresa);
                pieza.setFactura(factura);
                pieza.setCedula(cedula);

                inventario.push_back(pieza);
            }
            archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para cargar el inventario." << endl;
        }
        return inventario;
}

//opcion b
void consultarPieza (){
	string piezaConsultar;
	cout << "Ingrese el código de la pieza a consultar: ";
	cin >> piezaConsultar;

	//Busqueda en invetanrio de la pieza
	bool encontrado = false;
	for (auto& pieza : inventario){ // para bucle for especial para vectores, hace que el compilador deduzca el tipo de  variable
		if (pieza.getCodigo() == piezaConsultar){
			encontrado = true;
			cout << "Informacion actual de la pieza \n";
			pieza.mostrarInfo();
		}
	}

if (!encontrado){
	cout << "Pieza no encontrada" << endl;
}
}

//Opcion d
void eliminarPieza(){
	string codigoPedido;
	string piezaEspecif;
	char confirma;

	cout << "Ingrese el número de pedido";
	cin >> codigoPedido;

	bool pedidoEncontrado = false;
	for (auto& pedido : inventario){
		if(pedido.getCodigo() == codigoPedido){
			pedidoEncontrado = true;
			cout << "Informacion del pedido \n";
			pedido.mostrarInfo();
		}//llave if
	}//llave for
	cout << "Ingrese el número de pieza que desea eliminar";
	cin >> piezaEspecif;
	bool piezaEncontrada = false;
	for (auto& pieza : inventario){
		if ( pieza.getCodigo() == piezaEspecif){
			piezaEncontrada = true;
			cout << "Informacion de la pieza \n";
			pieza.mostrarInfo();
		}//llave if elimina pieza
	}//llave for elimina pieza

	cout << "¿Desea eliminar la pieza encontrada? (S/N)";
	cin >>confirma;
	if ((confirma == 's') || (confirma == 'S')){
            for (auto it = inventario.begin(); it !=inventario.end(); ++it){
                if (it -> getCodigo() == piezaEspecif){
                    inventario.erase(it);
                    break;
                }
            }
    ofstream archivo ("Inventario.txt", ios::trunc);
    if (archivo.is_open()){
        for (const auto& pieza : inventario){
            archivo << pieza.getCodigo() << "";
            archivo << pieza.getNombre() << " ";
            archivo << pieza.getCosto() << " ";
            archivo << pieza.getCantidad() << " ";
            archivo << pieza.getEmpresa() << " ";
            archivo << pieza.getFactura() << " ";
            archivo << pieza.getCedula() << endl;
        }
        archivo.close();
        cout << "Pieza eliminada correctamente." << endl;
    }else{
        cout << "No se pudo abrir el archivo para guardar los cambios." << endl;
        }
}
}

//Seccion Pedido

class Pedido { //almacena informacion sobre la pedidos realizados
private:
        string codigo;
        string codigoPieza;
        int cantidad;
        string identificacionEmpleado;
        string fechaSolicitud;
        string estado;

public:
        //constructores
        Pedido(string cod, string codPieza, int cant, string idEmpleado, string fechaSoli, string estad){
            codigo = cod;
            codigoPieza = codPieza;
            cantidad = cant;
            identificacionEmpleado = idEmpleado;
            fechaSolicitud = fechaSoli;
            estado = estad;

        }
        Pedido (){};

// Métodos 'get' y 'set' para cada atributo
string getCodigo() const {return codigo; }
void setCodigo(string cod) { codigo = cod; }

string getCodigoPieza()const {return codigoPieza; }
void setCodigoPieza(string codPieza) { codigoPieza = codPieza; }

int getCantidad()const {return cantidad; }
void setCantidad(int cant) { cantidad = cant; }

string getFechaSolicitud()const {return fechaSolicitud; }
void setFechaSolicitud(string fechaSoli) { fechaSolicitud = fechaSoli; }

string getIdentificacionEmpleado()const {return identificacionEmpleado; }
void setIdentificacionEmpleado(string idEmpleado) { identificacionEmpleado = idEmpleado;}

string getEstado()const {return estado; }
void setEstado(string estad) {estado = estad; }
};


//opcion a

void guardarPedidoArchivo(const Pedido& pedido){ //const Pieza& significa pasan objeto Pieza por referencia, y const asegura que la función no modifique ese objeto
    ofstream archivo("Pedidos.txt", ios::app);//tipo de datos  para crear objetos que puedan escribir datos en archivos //todo lo que escribas en el archivo se añadirá al final del mismo, sin borrar el contenido existente.
    if (archivo.is_open()){
        archivo << pedido.getCodigo() << " "
                << pedido.getCodigoPieza() << " "
                << pedido.getCantidad() << " "
                << pedido.getidentificacionEmpleado() << " "
                << pedido.getfechaSolicitud() << " "
                << pedido.getEstado() << endl;
        archivo.close ();
    } else {
        cout << "No se pudo abrir el archivo para guardar el pedido" << endl;
    }
    }
void ingresoPedido(){
    string cod, codPieza, idEmpleado, fact, fechaSoli;
    string estad = "En proceso";
    int cant;

    cout << "Ingrese el código del pedido (Formato: PE########): ";
        cin >> cod;
        while ((cod [0] != 'P') || (cod.length() != 9)){
        cout << "Código de pedido incorrecto. Formato correcto: PE########. Intente nuevamente: ";
        cin >> cod;
        }
        cout << "Ingrese el código de pieza: ";
        cin.ignore();
        getline(cin, codPieza);

        cout << "Ingrese la cantidad de piezas a solicitar: ";
        cin >> cant;
        while ((cin.fail()) || (cant < 0)){
        cout << "Cantidad incorrecta. Debe ser un número positivo. Intente nuevamente: .";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> cant;
        }

        cout << "Ingrese su cédula (9 dígitos): ";
        cin >> idEmpleado;
        while ((idEmpleado.length() != 9) || (!all_of(idEmpleado.begin(), idEmpleado.end(), ::isdigit))){
        cout << "Cédula incorrecta. Debe tener 9 dígitos. Intente nuevamente: ";
        cin >> idEmpleado;
        }

        cout << "Ingrese la fecha de solicitud (DD/MM/YYYY): ";
        cin >> fechaSoli;
        while (!validarFecha(fechaSoli)) {
            cout << "Fecha incorrecta. Formato correcto: DD/MM/YYYY. Intente nuevamente: ";
            cin >> fechaSoli;
        }

        //Creacion objeto Pedido con la informacion suministrada
        Pedido nuevoPedido (cod, codPieza, cant, idEmpleado, fechaSoli, estad);

        //Guardar pedido en archivo
        guardarPedidoArchivo(nuevoPedido);

        // Mostrar estado del pedido
        cout << "Estado del pedido: " << nuevoPedido.getEstado() << endl;

        cout << "Pedido ingresado correctamente." << endl;
}






}//llave ingreso pedido







int main (){
    setlocale (LC_ALL, "SPANISH");

    int opcion;
    do {
        mostrarMenu();
        revisaEntrada(opcion);
        switch(opcion){
            case 1:
                char opcionInventario;
                cout << "a. Ingresar pieza al inventario.\n";
                cout << "b. Consultar pieza del inventario.\n";
                cout << "c. Modificar pieza del inventario.\n";
                cout << "d. Eliminar pieza del inventario.\n";
                cout << "Ingrese una opción: ";
                cin >> opcionInventario;
                switch (opcionInventario){
                    case 'a':
                        ingresarPieza();
                        break;
                    case 'b':
                        consultarPieza();
                        break;
                    case 'c':
                        modificarPieza();
                        break;
                    case 'd':
                        eliminarPieza();
                        break;
                    default:
                        cout << "Opción inválida, vuelda a intentarlo" << endl;
                        break;
                }
                break;
                }//llave switch segundo case
                break;
            case 2:
                //opciones
                break;
            case 3:
                //Reporte Inventario
                break;
            case 4:
                //Reporte pedidos
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida, vuelva a intentarlo." << endl;
                break;
        }//llave switch

    } while (opcion != 6);

    return 0;
}//llave del main
