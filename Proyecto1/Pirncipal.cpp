#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "conio.h"
using namespace std;
using namespace ColorUI;
void Menu() {
	cout << "======Menu======\n";
	cout << "1. Buscar ruta mas corta\n";
	cout << "2. Agregar nueva ruta\n";
	cout << "3. Salir\n";
}
int main() {
	srand(time(0));
	string origen, destino;
	ControladorPrincipal* controladorPrincipal = new ControladorPrincipal();
		controladorPrincipal->GenerarVuelos(10);
		cout << "Digite el origen: "; 
		getline(cin,origen);
		cout << "Digite el destino: ";
		getline(cin,destino);
		cin.ignore();
		//controladorPrincipal->ConsultarVuelos(origen,destino);
		delete controladorPrincipal;
	return 0;
}