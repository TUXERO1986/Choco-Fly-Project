#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "conio.h"
#include "GestionPantallas.h"
using namespace std;
using namespace ColorUI;

int main() {
    ControladorPrincipal* principal = new ControladorPrincipal();
    principal->GenerarDatos(5, 5, 5);

    GestionPantallas* ui = new GestionPantallas(principal);

    RegisterScreen(principal);

    delete principal;
    return 0;

}