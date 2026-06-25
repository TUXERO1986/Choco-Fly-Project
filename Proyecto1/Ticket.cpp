#include "Ticket.h"
Ticket::Ticket(string codigoUsuario, string nombreUsuario, string origen, string destino, string escalas,string fecha, float distancia, int equipaje, int equipajecabina,int clase,int asiento)
    : Reserva(codigoUsuario, nombreUsuario)
{
	this->nombre = nombreUsuario;
	this->origen = origen;
	this->destino = destino;
	this->escalas = escalas;
	this->distancia = distancia	;
	this->equipaje = equipaje;
	this->equipajecabina = equipajecabina;
	this->tipoReserva = "VUELO";
	this->clase = clase;
	this->asiento = asiento;
	this->fecha = fecha;
	obtenerClase = [](int clase) {
		switch (clase) {
		case 1:return "ECONOMICA"; break;
		case 2:return "PREMIUM"; break;
		case 3:return "EJECUTIVA"; break;
		case 4:return "PRIMERA CLASE"; break;
		}
	};
}
#include "Color.h"

void Ticket::MostrarReserva() {
    ColorUI::printGradient("================ VOUCHER DE VUELO ================", ColorUI::Paletas::TemaPrincipal, false);
    ColorUI::printGradient(" Origen: " + origen + "   -->   Destino: " + destino, ColorUI::Paletas::Exito, false);
    ColorUI::printGradient(" Fecha: " + fecha + "   | Escalas: " + escalas, ColorUI::Paletas::azul, false);
    ColorUI::printGradient(" Equipaje Bodega: " + to_string(equipaje) + " | Cabina: " + to_string(equipajecabina), ColorUI::Paletas::Register, false);
    ColorUI::printGradient(" Asiento: [" + to_string(asiento) + "] | Clase: " + obtenerClase(clase), ColorUI::Paletas::MoradoD, false);
    ColorUI::printGradient("--------------------------------------------------", ColorUI::Paletas::TemaPrincipal, false);
    
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", getPrecioTotal());
    ColorUI::printGradient(" Precio Total: $" + string(buffer), ColorUI::Paletas::gege, false);
    ColorUI::printGradient("==================================================\n", ColorUI::Paletas::TemaPrincipal, false);
}
string Ticket::aTextoArchivo() {
	return "VUELO," + getCodigoUsuario() + "," + getNombre() + "," + origen + "," + destino + "," + escalas + "," + fecha+"," + to_string(getPrecioTotal())
		+ "," + to_string(distancia) + "," + to_string(equipaje) + "," + to_string(equipajecabina)+","+to_string(clase)+","+to_string(asiento);
}
float Ticket::getPrecioTotal() {
	float costoEquipaje = (equipaje-1) * 10.0f; 
	float costoEquipajeCabina = (equipajecabina-1) * 20.0f; 
	return (distancia*0.8)*clase + costoEquipaje*10 + costoEquipajeCabina*40;
}
string Ticket::getNombre() { return nombre; }
string Ticket::getOrigen() { return origen; }
string Ticket::getDestino() { return destino; }
string Ticket::getEscalas() { return escalas; }
string Ticket::getFecha() { return fecha; }
int Ticket::getAsiento() { return asiento; }
int Ticket::getClase() { return clase; }
float Ticket::getDistancia() { return distancia; }
int Ticket::getEquipaje() { return equipaje; }
int Ticket::getEquipajeCabina() { return equipajecabina; }
void Ticket::setEquipaje(int equipaje) { this->equipaje = equipaje; }
void Ticket::setEquipajeCabina(int equipajecabina) { this->equipajecabina = equipajecabina; }
void Ticket::setOrigen(string origen) { this->origen = origen; }
void Ticket::setDestino(string destino) { this->destino = destino; }
void Ticket::setEscalas(string escalas) { this->escalas = escalas; }
void Ticket::setDistancia(float distancia) { this->distancia = distancia; }
void Ticket::setNombre(string nombre) { this->nombre = nombre; }