#include <iostream>
#include "Color.h"
#include "Windows.h"

using namespace std;
using namespace ColorUI;
string usuario, correo, password;
void RegisterScreen() {
   
    
    string registro = R"(
                                 ____            _     _             
  (Simulacion de registro)      |  _ \ ___  __ _(_)___| |_ _ __ ___  
                                | |_) / _ \/ _` | / __| __| '__/ _ \ 
                                |  _ <  __/ (_| | \__ \ |_| | | (_) |
                                |_| \_\___|\__, |_|___/\__|_|  \___/ 
                                           |___/                                )";
    ColorUI::printGradient(registro, Register, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Register, false);
    cout << "\t\t\t\t", cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\tIngrese su Correo", Register, false);
    cout << "\t\t\t\t", cin >> correo;
    ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Register, false);
    cout << "\t\t\t\t", cin >> password;
    system("cls");
    LoginScreen();
}
void LoginScreen() {

    string registro = R"(
                                 _                _       
   (Simulacion de logeo)        | |    ___   __ _(_)_ __  
                                | |   / _ \ / _` | | '_ \ 
                                | |__| (_) | (_| | | | | |
                                |_____\___/ \__, |_|_| |_|
                                            |___/         )";
    ColorUI::printGradient(registro, Register, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Register, false);
    cout << "\t\t\t\t", cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Register, false);
    cout << "\t\t\t\t", cin >> password;
    system("cls");

}
void Menuprincipal() {
   // RegisterScreen();
    int opcion;
    string registro = R"(
                                +-----------------------------------------+     
                                |  ____ _                      __ _       |            __|__
           __|__                | / ___| |__   ___   ___ ___  / _| |_   _ |     --------(_)--------
    --------(_)--------         || |   | '_ \ / _ \ / __/ _ \| |_| | | | ||       O  O       O  O
       O  O       O  O          || |___| | | | (_) | (_| (_) |  _| | |_| ||
                                | \____|_| |_|\___/ \___\___/|_| |_|\__, ||
                                |                                   |___/ |
                                +-----------------------------------------+

   )";
    cout << BLINK;
    ColorUI::printGradient(registro, TemaPrincipal, false);
    cout << RESET;
    ColorUI::printGradient("\n\n\t\t\t\t\t[1] Vuelos", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[2] Funcion faltante", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[3] Creditos", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[4] Salir", Exito, false);
    cin >> opcion;
    switch (opcion)
    {
    case 1: {
        cout << "aqui va la funcion vuelos" << endl;
    } break;
    case 2: {
        cout << "aqui iria la funcion faltante" << endl;
    } break;
    case 3: {
        creditos();
    } break;
    default: {
        system("cls");
        for (int i = 0; i < 4;i++) {

        ColorUI:printGradient("Saliendo en ", Alerta, false, false); cout << i << endl;
            Sleep(600);
        }
        cout << BLINK;
        ColorUI::printGradient("Muchas Gracias!", gege, false);
        system("exit");
    }        break;
    }
    
}
void creditos() {
    cout << BLINK;
    string Creditos = R"(
        >>========================================<<
        ||   _____              _ _ _             ||
        ||  / ____|            | (_) |            ||
        || | |     _ __ ___  __| |_| |_ ___  ___  ||
        || | |    | '__/ _ \/ _` | | __/ _ \/ __| ||
        || | |____| | |  __/ (_| | | || (_) \__ \ ||
        ||  \_____|_|  \___|\__,_|_|\__\___/|___/ ||
        >>========================================<<
    )";
    ColorUI::printGradient(Creditos, femboy, false);
    cout << RESET;

    string ryan = R"(
      Ryan (apellido)
    [Programador C++ Backend]

            .--.
           |o_o |
           |:_/ |
          //   \ \
         (|     | )
        /'\_   _/`\
        \___)=(___/ 
    )";

    string gengis = R"(
      Gengis cam pizarro
    [Frontend Console App]

           ,_     _
           |\_,-~/
           / _  _ |    ,--.
          (  @  @ )   / ,-'
           \  _T_/-._( (
           /         `. \
          |         _  \ |
           \ \ ,  /      |
            || |-_\__   /
           ((_/`(____,-'
    )";

    string santiago = R"(
      Santiago (Apellido)
    [Correccion de Bugs]

               __         __
              /  \.-"""-./  \
              \    -   -    /
               |   o   o   |
               \  .-'''-.  /
                '-\__Y__/-'
                   `---`
    )";

    ColorUI::printMultilinesSideBySide(
        ryan, Tux,
        gengis, gege,
        santiago, TemaPrincipal
    );
}
void PruebaColor() {
    cout << BLINK;
    ColorUI::printGradient("   === SISTEMA DE GESTION ===   ", Exito, false);
    cout << "\n";
    cout << RESET;
    cout << "1. Iniciar Sesion\n";
    cout << "2. Registrar Usuario\n";
    cout << "3. Salir\n";
    ColorUI::printGradient("Seleccione una opcion: ", gege, false);
}

void test() {
    cout << "hola";
}