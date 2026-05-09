#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "conio.h"
#include "GestionPantallas.h"
#include "AsciiArt.h"
using namespace std;
using namespace ColorUI;

int main() {
	srand(time(0));
	RegisterScreen(new ControladorPrincipal());
    return 0;

}