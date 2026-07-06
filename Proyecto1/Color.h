#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
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
class ControladorPrincipal;


void creditos();
void RegisterScreen(ControladorPrincipal* principal);
void LoginScreen(ControladorPrincipal* principal);  
void Admin(ControladorPrincipal* principal);       


extern std::string chocofly, admin, registro, login;




namespace ColorUI {

    struct RGB {
        int r, g, b;
    };

    
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

    inline void printSpriteAndCard(
        const std::string& sprite, const std::vector<std::string>& palSprite,
        const std::string& card, const std::vector<std::string>& palCard) {

        using namespace std;

        istringstream stream1(sprite), stream2(card);
        string line1, line2;
        bool has1, has2;

        auto padRight = [](string s, int width) {
            if (s.length() < width) s.append(width - s.length(), ' ');
            return s;
        };
        
        int widthSprite = 20; 
        int widthCard = 0;
        {
            istringstream s2(card);
            string l;
            while(getline(s2, l)) if(l.length() > widthCard) widthCard = l.length();
        }

        do {
            has1 = (bool)getline(stream1, line1);
            has2 = (bool)getline(stream2, line2);

            if (has1 || has2) {
                if (has1) printGradient(padRight(line1, widthSprite), palSprite, false, false);
                else printGradient(string(widthSprite, ' '), palSprite, false, false); 
                
                cout << "  ";

                if (has2) printGradient(padRight(line2, widthCard), palCard, false, false);
                else printGradient(string(widthCard, ' '), palCard, false, false);

                cout << "\n";
            }
        } while (has1 || has2);
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

    namespace Alertas {
        inline void MostrarCaja(const std::string& icono, const std::string& titulo, const std::string& mensaje, const std::vector<std::string>& paleta, const std::string& sangria = "") {
            std::string texto = " " + icono + " " + titulo + ": " + mensaje + " ";
            int width = texto.length() + 2;
            std::string border = "+" + std::string(width, '-') + "+";
            
            ColorUI::printGradient(sangria + border, paleta, false, true);
            ColorUI::printGradient(sangria + "| " + texto + " |", paleta, false, true);
            ColorUI::printGradient(sangria + border, paleta, false, true);
        }

        inline void MostrarExito(const std::string& mensaje, const std::string& sangria = "") {
            MostrarCaja("[V]", "EXITO", mensaje, Paletas::Exito, sangria);
        }

        inline void MostrarError(const std::string& mensaje, const std::string& sangria = "") {
            MostrarCaja("[X]", "ERROR", mensaje, Paletas::Alerta, sangria);
        }

        inline void MostrarInfo(const std::string& mensaje, const std::string& sangria = "") {
            MostrarCaja("[i]", "INFO", mensaje, Paletas::azul, sangria);
        }
    }

    namespace Animaciones {
        inline void mostrarSpinner(const std::string& texto, int duracion_ms = 1500, const std::string& sangria = "\t\t\t") {
            std::vector<std::string> frames = {"|", "/", "-", "\\"};
            int ms_per_frame = 100;
            int frames_count = duracion_ms / ms_per_frame;
            
            std::cout << "\n";
            for (int i = 0; i < frames_count; ++i) {
                std::string frame = "\r" + sangria + "[ " + frames[i % 4] + " ] " + texto + "...";
                std::cout << frame << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(ms_per_frame));
            }
            std::cout << "\r" << sangria << "                                                                                \r"; 
        }
    }

    using namespace Estilo;
    using namespace Paletas;
    using namespace Alertas;
    using namespace Animaciones;
} 