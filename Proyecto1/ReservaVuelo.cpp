#include "ReservaVuelo.h"
ReservaVuelo::ReservaVuelo(string codigoUsuario, string nombreUsuario, string origen, string destino, string escalas,string fecha, float distancia, int equipaje, int equipajecabina,int clase,int asiento)
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
void ReservaVuelo::MostrarReserva() {
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Escalas: " << escalas << endl;
	cout << "Fecha: " << fecha << endl;
	cout << "Distancia: " << distancia << endl;
	cout << "Equipaje en bodega: " << equipaje << endl;
	cout << "Equipaje de cabina: " << equipajecabina << " [1 MALETA INCLUIDA SIN COSTO]"<<endl;
	cout << "Asiento: " << asiento << endl;
	cout << "Clase: " << obtenerClase(clase)<<endl;
	cout << "Precio Total: $" << getPrecioTotal() << endl;
}
string ReservaVuelo::aTextoArchivo() {
	return "VUELO," + getCodigoUsuario() + "," + getNombre() + "," + origen + "," + destino + "," + escalas + "," + fecha+"," + to_string(getPrecioTotal())
		+ "," + to_string(distancia) + "," + to_string(equipaje) + "," + to_string(equipajecabina)+","+to_string(clase)+","+to_string(asiento);
}
float ReservaVuelo::getPrecioTotal() {
	float costoEquipaje = (equipaje-1) * 10.0f; 
	float costoEquipajeCabina = (equipajecabina-1) * 20.0f; 
	return (distancia*0.8)*clase + costoEquipaje*10 + costoEquipajeCabina*40;
}
string ReservaVuelo::getNombre() { return nombre; }
string ReservaVuelo::getOrigen() { return origen; }
string ReservaVuelo::getDestino() { return destino; }
string ReservaVuelo::getEscalas() { return escalas; }
string ReservaVuelo::getFecha() { return fecha; }
int ReservaVuelo::getAsiento() { return asiento; }
int ReservaVuelo::getClase() { return clase; }
float ReservaVuelo::getDistancia() { return distancia; }
int ReservaVuelo::getEquipaje() { return equipaje; }
int ReservaVuelo::getEquipajeCabina() { return equipajecabina; }
void ReservaVuelo::setEquipaje(int equipaje) { this->equipaje = equipaje; }
void ReservaVuelo::setEquipajeCabina(int equipajecabina) { this->equipajecabina = equipajecabina; }
void ReservaVuelo::setOrigen(string origen) { this->origen = origen; }
void ReservaVuelo::setDestino(string destino) { this->destino = destino; }
void ReservaVuelo::setEscalas(string escalas) { this->escalas = escalas; }
void ReservaVuelo::setDistancia(float distancia) { this->distancia = distancia; }
void ReservaVuelo::setNombre(string nombre) { this->nombre = nombre; }