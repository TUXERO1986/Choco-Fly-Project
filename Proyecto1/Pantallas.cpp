#include <iostream>
#include "Color.h"
#include "Windows.h"
#include "GestionPantallas.h"
#include "AdminPantallas.h"


using namespace std;
using namespace ColorUI;
string usuario, correo, password;
string registro = R"(
                                 ____            _     _             
  (Simulacion de registro)      |  _ \ ___  __ _(_)___| |_ _ __ ___  
                                | |_) / _ \/ _` | / __| __| '__/ _ \ 
                                |  _ <  __/ (_| | \__ \ |_| | | (_) |
                                |_| \_\___|\__, |_|___/\__|_|  \___/ 
                                           |___/                                )";

string login = R"(
                                 _                _       
   (Simulacion de logeo)        | |    ___   __ _(_)_ __  
                                | |   / _ \ / _` | | '_ \ 
                                | |__| (_) | (_| | | | | |
                                |_____\___/ \__, |_|_| |_|
                                            |___/         )";

string chocofly = R"(
                                +-----------------------------------------+     
                                |  ____ _                      __ _       |            __|__
           __|__                | / ___| |__   ___   ___ ___  / _| |_   _ |     --------(_)--------
    --------(_)--------         || |   | '_ \ / _ \ / __/ _ \| |_| | | | ||       O  O       O  O
       O  O       O  O          || |___| | | | (_) | (_| (_) |  _| | |_| ||
                                | \____|_| |_|\___/ \___\___/|_| |_|\__, ||
                                |                                   |___/ |
                                +-----------------------------------------+

   )";

string admin = R"(
                            _       _           _       
                           / \   __| |_ __ ___ (_)_ __  
                          / _ \ / _` | '_ ` _ \| | '_ \ 
                         / ___ \ (_| | | | | | | | | | |
                        /_/   \_\__,_|_| |_| |_|_|_| |_|
)";
string chocoadmin = R"(
                                    +-------------------------------------------+
                                    |  ____ _                     _____ _       |
            __|__                   | / ___| |__   ___   ___ ___ |  ___| |_   _ |              __|__      
     --------(_)--------            || |   | '_ \ / _ \ / __/ _ \| |_  | | | | ||       --------(_)-------- 
       O  O       O  O              || |___| | | | (_) | (_| (_) |  _| | | |_| ||         O  O       O  O  
                                    | \____|_| |_|\___/ \___\___/|_|   |_|\__, ||
                                    |       / \  |  _ \|  \/  |_ _| \ | | |___/ |
                                    |      / _ \ | | | | |\/| || ||  \| |       |
                                    |     / ___ \| |_| | |  | || || |\  |       |
                                    |    /_/   \_\____/|_|  |_|___|_| \_|       |
                                    +-------------------------------------------+
   )";

void RegisterScreen(ControladorPrincipal* principal) {
    string modo;

    ColorUI::printGradient(registro, Paletas::Register, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese el modo (Admin | Usuario)", Register, false);
    cout << "\t\t\t\t"; cin >> modo;

    if (modo == "Admin" || modo == "admin" || modo == "ADMIN") {
        Admin(principal);
    }
    else if (modo == "Usuario" || modo == "USUARIO" || modo == "usuario" || modo == "user" || modo == "User") {
        LoginScreen(principal);
    }
    else {
        system("cls");
        RegisterScreen(principal);
    }
}

void LoginScreen(ControladorPrincipal* principal) {
    system("cls");

    ColorUI::printGradient(login, Paletas::Register, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese su Nombre de usuario", Paletas::Register, false);
    cout << "\t\t\t\t"; cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\tIngrese su Contrasena", Paletas::Register, false);
    cout << "\t\t\t\t"; cin >> password;
    system("cls");

    GestionPantallas* userUI = new GestionPantallas(principal);
    userUI->Menuprincipal(userUI);
    delete userUI; 
}

void Admin(ControladorPrincipal* principal) {
    system("cls");

    ColorUI::printGradient(admin, Paletas::Tux, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese Datos ADMIN", Paletas::Tux, false);
    cout << "\t\t\t\t"; cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\tIngrese contrasena ADMIN", Paletas::Tux, false);
    cout << "\t\t\t\t"; cin >> password;
    system("cls");
    AdminPantallas* adminUI = new AdminPantallas(principal);
    adminUI->MenuAdmin();
    delete adminUI; 
}

//ZONA DE ASCII ART
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
    ColorUI::printGradient(Creditos, rosa, false);
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
    system("pause");
}

