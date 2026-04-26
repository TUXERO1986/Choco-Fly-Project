#include <iostream>
#include "Color.h"

using namespace std;
using namespace ColorUI;
void RegisterScreen() {
    string usuario,password,correo;
    
    string registro = R"(
                                 ____            _     _             
                                |  _ \ ___  __ _(_)___| |_ _ __ ___  
                                | |_) / _ \/ _` | / __| __| '__/ _ \ 
                                |  _ <  __/ (_| | \__ \ |_| | | (_) |
                                |_| \_\___|\__, |_|___/\__|_|  \___/ 
                                           |___/                     )";
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
    string usuario, password, correo;

    string registro = R"(
                                 _                _       
                                | |    ___   __ _(_)_ __  
                                | |   / _ \ / _` | | '_ \ 
                                | |__| (_) | (_| | | | | |
                                |_____\___/ \__, |_|_| |_|
                                            |___/         )";
    ColorUI::printGradient(registro, Register, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Register, false);
    cout << "\t\t\t\t", cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Register, false);
    cout << "\t\t\t\t", cin >> password;

}
void Menuprincipal() {

    int a;
    cout << UNDERLINE ;
    ColorUI::printGradient("\t =================== ", femboy, false);
    ColorUI::printGradient("\t | ChocoFly        |", femboy, false);
    ColorUI::printGradient("\t =================== \n", femboy, false);
    cout << RESET;
    ColorUI::printGradient("[1] Vuelos  ", gege, false, false);
    ColorUI::printGradient(" \t[2] Paquetes ", gege, false, false);
    ColorUI::printGradient(" \t[3] Hospedaje ", gege, false,false);
    cout << BLINK; 
    ColorUI::printGradient(" \t[4] Creditos ", Alerta, false, false);
    cout << RESET;
    cin >> a;
    if (a == 4) {
        system("cls");
        creditos();
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