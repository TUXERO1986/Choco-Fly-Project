#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "conio.h"
#include "GestionPantallas.h"
using namespace std;
using namespace ColorUI;

int main() {
	srand(time(0));
   ControladorPrincipal* principal = new ControladorPrincipal();
    principal->GenerarDatos(5, 5, 5);
	//principal->getControladorVuelos()->getVuelos()->obtenerPos(0)->MostrarAsientos();
	ControladorUsuarios* controladorUsuarios = new ControladorUsuarios();
	string nombre, correo, password;
	cout << "Digite el nombre del nuevo usuario: ";
	cin >> nombre;
	cout << "Digite el correo del nuevo usuario: ";
	cin >> correo;
	cout << "Digite la contraseña del nuevo usuario: ";
	cin >> password;
	Usuario* userActual=principal->VerificarInicioSesion(nombre, correo, password);
	
	
	//principal->ReservarPaquete(1, aux);
	//principal->ComprarTicket(0, aux);
	//principal->MostrarReservasAdmin();
    delete principal;
    delete controladorUsuarios;
    return 0;

}