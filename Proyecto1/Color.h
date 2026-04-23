#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // <--- AGREGAR ESTA LIBRERÍA

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

 // Definicion de funciones:
void PruebaColor();
void Menuprincipal();
void creditos();

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

    // Función principal para imprimir degradados (VERSIÓN OPTIMIZADA CON BUFFER)
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

        // 🔥 OPTIMIZACIÓN: Creamos un buffer para guardar toda la línea antes de imprimir
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

            // Armamos el código de color y la letra, y lo sumamos al buffer
            bufferFinal += "\033[" + mode + ";2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text[i];
        }

        // Reseteo suave y salto de línea al final del buffer
        string resetMode = isBackground ? "49" : "39";
        bufferFinal += "\033[" + resetMode + "m" + (newLine ? "\n" : "");

        // 🔥 OPTIMIZACIÓN: Un solo llamado a la consola en lugar de decenas
        cout << bufferFinal;
    }
    // Función para imprimir 3 bloques de texto multilínea (Raw Strings) uno al lado del otro pura estetica
// Función para imprimir 3 bloques de texto multilínea (VERSIÓN CON AUTO-ALINEACIÓN)
    inline void printMultilinesSideBySide(
        const std::string& s1, const std::vector<std::string>& pal1,
        const std::string& s2, const std::vector<std::string>& pal2,
        const std::string& s3, const std::vector<std::string>& pal3) {

        using namespace std;

        istringstream stream1(s1), stream2(s2), stream3(s3);
        string line1, line2, line3;
        bool has1, has2, has3;

        // Ancho fijo para cada bloque (garantiza que no choquen entre sí)
        const int ANCHO_COL = 33;

        // Mini-función interna para rellenar espacios y limpiar tabs
        auto alinear = [ANCHO_COL](string s) {
            size_t pos;
            while ((pos = s.find("\t")) != string::npos) s.replace(pos, 1, "    ");
            if (s.length() < ANCHO_COL) s.append(ANCHO_COL - s.length(), ' ');
            // Si la línea es muy larga, la cortamos para que no rompa el diseño
            if (s.length() > ANCHO_COL) s = s.substr(0, ANCHO_COL);
            return s;
            };

        do {
            has1 = (bool)getline(stream1, line1);
            has2 = (bool)getline(stream2, line2);
            has3 = (bool)getline(stream3, line3);

            if (has1 || has2 || has3) {
                // Imprimimos cada línea alineada perfectamente a 33 caracteres
                if (has1) printGradient(alinear(line1), pal1, false, false);
                else printGradient(string(ANCHO_COL, ' '), pal1, false, false); // Relleno vacío si el dibujo es más corto

                if (has2) printGradient(alinear(line2), pal2, false, false);
                else printGradient(string(ANCHO_COL, ' '), pal2, false, false);

                if (has3) printGradient(alinear(line3), pal3, false, false);
                else printGradient(string(ANCHO_COL, ' '), pal3, false, false);

                cout << "\n";
            }
        } while (has1 || has2 || has3);
    }
    // Función para pintar toda la pantalla de un color
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
        const std::vector<std::string> femboy = { "#E727F5","#D028DC","#B928C4","#A327AC" };
        const std::vector<std::string> Tux = { "#FF0D0D","#CD1B0F","#9C1E0F","#6F1C0F" };
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
} // Cierre correcto del namespace ColorUI (La llave extra fue eliminada)