#pragma once
#include <string>
#include <iostream>
#include <vector>
#ifdef _WIN32
    // Todo lo que esté aquí SOLO se compilará en las PCs de tus amigos (Windows)
#include <windows.h>

    #include <conio.h>

#else
    // Todo lo que esté aquí SOLO se compilará en tu PC (Linux/Mac)

    #include <unistd.h> 
#endif
//#include "ControladorRutas.h"
#include "AsciiArt.h"
#include <sstream> 

/**
 * ============================================================================
 * LIBRERIA DE INTERFAZ DE USUARIO (UI) - EXTENSION VISUAL
 * ============================================================================
 * Nota: Este modulo es opcional y puramente decorativo (Mejora de UX).
 * No interfiere ni modifica la logica de negocio o los algoritmos principales.
 * * Implementacion basada en el uso de Secuencias de Escape ANSI (True Color 24-bit)
 * y la interpolacion lineal (LERP) para el calculo de degradados RGB.
 * * Fuentes y Documentacion Oficial consultada:
 * 1. Microsoft Docs - Console Virtual Terminal Sequences:
 * https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 * * 2. Estandar ANSI / ISO-6429 (Colores de terminal de 24 bits):
 * https://en.wikipedia.org/wiki/ANSI_escape_code#24-bit
 * ============================================================================
 */
class ControladorPrincipal; // Le avisamos que existe esta clase

// Definicion de funciones de ruteo:
void creditos();
void RegisterScreen(ControladorPrincipal* principal);
void LoginScreen(ControladorPrincipal* principal);  
void Admin(ControladorPrincipal* principal);       

// Variables globales de arte (Asegúrate de definirlas en Pantallas.cpp)
extern std::string chocofly, chocoadmin, admin, registro, login;






// Espacio de nombres para encapsular toda la funcionalidad relacionada con la UI de colores
namespace ColorUI {

    struct RGB {
        int r, g, b;
    };

    // Función auxiliar para convertir Hexadecimal a RGB
    inline RGB hexToRGB(const std::string& hex) {
        using namespace std;

        size_t offset = (hex[0] == '#') ? 1 : 0;
        return {
            stoi(hex.substr(offset, 2), nullptr, 16),
            stoi(hex.substr(offset + 2, 2), nullptr, 16),
            stoi(hex.substr(offset + 4, 2), nullptr, 16)
        };
    }

    inline void printGradient(const std::string& text, const std::vector<std::string>& hexColors, bool isBackground = false, bool newLine = true) {
        using namespace std;

        if (hexColors.empty()) {
            cout << text << (newLine ? "\n" : "");
            return;
        }

        int n = text.length();
        int numSections = hexColors.size() - 1;
        float charsPerSection = (float)n / (numSections > 0 ? numSections : 1);
        string mode = isBackground ? "48" : "38";
        string bufferFinal = "";

        for (int i = 0; i < n; ++i) {
            int section = (numSections > 0) ? i / charsPerSection : 0;
            if (section >= numSections && numSections > 0) section = numSections - 1;

            float localFactor = (numSections > 0) ? (i - (section * charsPerSection)) / charsPerSection : 0;

            RGB start = hexToRGB(hexColors[section]);
            RGB end = hexToRGB(hexColors[numSections > 0 ? section + 1 : section]);

            int r = static_cast<int>(start.r + (end.r - start.r) * localFactor);
            int g = static_cast<int>(start.g + (end.g - start.g) * localFactor);
            int b = static_cast<int>(start.b + (end.b - start.b) * localFactor);

            bufferFinal += "\033[" + mode + ";2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text[i];
        }

        string resetMode = isBackground ? "49" : "39";
        bufferFinal += "\033[" + resetMode + "m" + (newLine ? "\n" : "");

        cout << bufferFinal;
    }

    inline void printMultilinesSideBySide(
        const std::string& s1, const std::vector<std::string>& pal1,
        const std::string& s2, const std::vector<std::string>& pal2,
        const std::string& s3, const std::vector<std::string>& pal3) {

        using namespace std;

        istringstream stream1(s1), stream2(s2), stream3(s3);
        string line1, line2, line3;
        bool has1, has2, has3;

        const int ANCHO_COL = 33;

        auto alinear = [ANCHO_COL](string s) {
            size_t pos;
            while ((pos = s.find("\t")) != string::npos) s.replace(pos, 1, "    ");
            if (s.length() < ANCHO_COL) s.append(ANCHO_COL - s.length(), ' ');
            if (s.length() > ANCHO_COL) s = s.substr(0, ANCHO_COL);
            return s;
            };

        do {
            has1 = (bool)getline(stream1, line1);
            has2 = (bool)getline(stream2, line2);
            has3 = (bool)getline(stream3, line3);

            if (has1 || has2 || has3) {
                if (has1) printGradient(alinear(line1), pal1, false, false);
                else printGradient(string(ANCHO_COL, ' '), pal1, false, false); 

                if (has2) printGradient(alinear(line2), pal2, false, false);
                else printGradient(string(ANCHO_COL, ' '), pal2, false, false);

                if (has3) printGradient(alinear(line3), pal3, false, false);
                else printGradient(string(ANCHO_COL, ' '), pal3, false, false);

                cout << "\n";
            }
        } while (has1 || has2 || has3);
    }
    inline void setBackgroundColor(const std::string& hex) {
        using namespace std;
        RGB color = hexToRGB(hex);
        cout << "\033[48;2;" << color.r << ";" << color.g << ";" << color.b << "m";
        cout << "\033[2J\033[H";
    }

    inline void resetConsole() {
        using namespace std;
        cout << "\033[0m\033[2J\033[H";
    }

    /*
    ============================================================================
    PALETAS DE COLORES PREDEFINIDAS
    ============================================================================
    */

    namespace Paletas {
        const std::vector<std::string> TemaPrincipal = { "#4facfe", "#00f2fe" };
        const std::vector<std::string> Alerta = { "#ff416c", "#ff4b2b" };
        const std::vector<std::string> Exito = { "#11998e", "#38ef7d" };
        const std::vector<std::string> gege = { "#00F719", "#15DE1C", "#1EC51E", "#22AD1F" };
        const std::vector<std::string> rosa = { "#E727F5","#D028DC","#B928C4","#A327AC" };
        const std::vector<std::string> Tux = { "#FF0D0D","#CD1B0F","#9C1E0F","#6F1C0F" };
        const std::vector<std::string> Register = { "#00F2FF","#1EC1CB","#24939A" };
		const std::vector<std::string> MoradoD = { "#4E0AF5", "#4411C4", "#3F13AC", "#33137E"};
        const std::vector<std::string> dato = { "#F5A70A","#DC9610","#C48614"};
		const std::vector<std::string> azul = { "#0E71C9", "#1666B5", "#1A5CA1", "#1C518E" };
    }

    namespace Estilo {
        const std::string BOLD = "\033[1m";
        const std::string ITALIC = "\033[3m";
        const std::string UNDERLINE = "\033[4m";
        const std::string BLINK = "\033[5m";
        const std::string REVERSE = "\033[7m";
        const std::string RESET = "\033[0m";
    }

    using namespace Estilo;
    using namespace Paletas;
} 