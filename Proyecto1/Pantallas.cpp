#include <iostream>
#include "Color.h"
#include "Windows.h"
#include "GestionPantallas.h"


using namespace std;
using namespace ColorUI;
string usuario, correo, password;
void RegisterScreen() {
   
    string modo;
    string registro = R"(
                                 ____            _     _             
  (Simulacion de registro)      |  _ \ ___  __ _(_)___| |_ _ __ ___  
                                | |_) / _ \/ _` | / __| __| '__/ _ \ 
                                |  _ <  __/ (_| | \__ \ |_| | | (_) |
                                |_| \_\___|\__, |_|___/\__|_|  \___/ 
                                           |___/                                )";
    ColorUI::printGradient(registro, Register, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese el modo (Admin | Usuario)", Register, false);
    cout << "\t\t\t\t", cin >> modo;
    if (modo == "Admin" || modo == "admin" || modo == "ADMIN") {
        Admin();
    }
    else  if (modo == "Usuario" || modo == "USUARIO" || modo == "usuario" || modo == "user" || modo == "User") {
        LoginScreen();
    }
    else  system("cls"); RegisterScreen();
}
void LoginScreen() {
    system("cls");
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
    Menuprincipal();

}
void Menuprincipal() {
  
    int opcion;
    do {
        system("cls");
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
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Reservar Vuelos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Reservar Hospedaje", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] Tickets", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] Creditos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[5] Menu", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[6] Salir", Exito, false);
        cin >> opcion;
        switch (opcion)
        {
        case 1: {
            system("cls");
            VuelosRyan();
        } break;

        case 2: {
            cout << "aqui iria la funcion faltante" << endl;
        } break;

        case 3: {
            cout << "aqui iria la funcion faltante" << endl;
        } break;

        case 4: {
            system("cls");
            creditos();
        } break;
        case 5: {
            system("cls");
            RegisterScreen(); break;
        }
        
        case 6: {
            system("cls");
            for (int i = 0; i < 4;i++) {

            ColorUI:printGradient("Saliendo en ", Alerta, false, false); cout << i << endl;
                Sleep(600);
            }
            cout << BLINK;
            ColorUI::printGradient("Muchas Gracias!", gege, false);
            exit(0);
        }  break;
        default: cout << "Opcion no valida" << endl; break;
        } 
    } while (opcion != 6);
    
}

void Admin() {
    system("cls");
    string admin = R"(
                            _       _           _       
                           / \   __| |_ __ ___ (_)_ __  
                          / _ \ / _` | '_ ` _ \| | '_ \ 
                         / ___ \ (_| | | | | | | | | | |
                        /_/   \_\__,_|_| |_| |_|_|_| |_|
)";

    ColorUI::printGradient(admin, Tux, false);
    ColorUI::printGradient("\n\n\n\t\t\t\tIngrese Datos ADMIN", Tux, false);
    cout << "\t\t\t\t", cin >> usuario;
    ColorUI::printGradient("\n\t\t\t\tIngrese contrasena ADMIN", Tux, false);
    cout << "\t\t\t\t", cin >> password;
    MenuAdmin();
    system("cls");
}

void MenuAdmin() {

    int opcion;
    do {
        system("cls");
        string registro = R"(
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
        cout << BLINK;
        ColorUI::printGradient(registro, Tux, false);
        cout << RESET;
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Agregar Vuelos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Agregar Paquetes", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] Agregar hoteles", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] Eliminar Vuelos", Alerta, false);
        ColorUI::printGradient("\n\t\t\t\t\t[5] Eliminar Paquetes", Alerta, false);
        ColorUI::printGradient("\n\t\t\t\t\t[6] Eliminar Hoteles", Alerta, false);
        ColorUI::printGradient("\n\t\t\t\t\t[7] salir", rosa, false);
        cin >> opcion;
        switch (opcion)
        {
        case 1: {
            cout << "opcioon para agregar vuelos" << endl;
        } break;
        case 2: {
            cout << "opcioon para agregar Paquetes" << endl;
        } break;
        case 3: {
            cout << "opcioon para agregar Hoteles" << endl;
        } break;
        case 4: {
            cout << "opcioon para Eliminar vuelos" << endl;
        } break;
        case 5: {
            cout << "opcioon para Eliminar Paquetes" << endl;
        } break;
        case 6: {
            cout << "opcioon para Eliminar hoteles" << endl;
        } break;

        case 7: {
            system("cls"); RegisterScreen();
            break;
        }
        default: cout << "opcion no valida."; break;
        }
        

    } while (opcion != 5);
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