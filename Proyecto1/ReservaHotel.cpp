#include "ReservaHotel.h"
ReservaHotel::ReservaHotel(string codigoUsuario, string nombreUsuario, string nombreHotel, 
	string ciudad, string fechaIngreso,float precioNoche, int noches,int habitacion,int tipoO,int tipoC,int tipoS)
	: Reserva(codigoUsuario, nombreUsuario) {
	ObtenerDia = [](string fecha) {
		size_t pos = fecha.find("-");
		if (pos != string::npos) {
			return stoi(fecha.substr(0, pos));
		}
		return -1;
		};
	ObtenerMes = [](string fecha) {
		size_t pos1 = fecha.find("-");
		size_t pos2 = fecha.find("-", pos1 + 1);
		if (pos1 != string::npos && pos2 != string::npos) {
			return stoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1));
		}
		return -1;
		};
	ObtenerAno = [](string fecha) {
		size_t pos1 = fecha.find("-");
		if (pos1 != string::npos) {
			size_t pos2 = fecha.find("-", pos1 + 1);
			if (pos2 != string::npos) {
				return stoi(fecha.substr(pos2 + 1));
			}
		}
		return -1;
		};

	ObtenerFechaSalida = [](int dia, int mes, int ano,int noches) {
		int diasPorMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
			diasPorMes[2] = 29;
		}

		dia += noches;

		while (dia > diasPorMes[mes]) {
			dia -= diasPorMes[mes]; 
			mes++;                  

			if (mes > 12) {
				mes = 1;
				ano++;

				if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
					diasPorMes[2] = 29;
				}
				else {
					diasPorMes[2] = 28;
				}
			}
		}

		return to_string(dia) + "-" + to_string(mes) + "-" + to_string(ano);
		};
	ObtenerTipoO = [](int tipoO){
		switch (tipoO) {
		case 1:return "INDIVIDUAL"; break;
		case 2:return "SUITE"; break;
		case 3:return "PRESIDENCIAL"; break;
		}
	};
	ObtenerTipoC = [](int tipoC){
		switch (tipoC) {
		case 1:return "INDIVIDUAL"; break;
		case 2:return "MATRIMONIAL"; break;
		case 3:return "QUEEN"; break;
		}
	};
	ObtenerTipoS = [](int tipoS){
		switch (tipoS) {
		case 1:return "BASICOS"; break;
		case 2:return "PREMIUM"; break;
		case 3:return "VIP"; break;
		}
	};
	this->nombreHotel = nombreHotel;
	this->ciudad = ciudad;
	this->fechaIngreso = fechaIngreso;
	this->precioNoche = precioNoche;
	this->noches = noches;
	this->tipoReserva = "HOTEL";
	this->tipoO = tipoO;
	this->tipoC = tipoC;
	this->tipoS = tipoS;
	this->habitacion = habitacion;
	this->fechaSalida = ObtenerFechaSalida(ObtenerDia(fechaIngreso), ObtenerMes(fechaIngreso), ObtenerAno(fechaIngreso),noches);
}
void ReservaHotel::MostrarReserva() {
	
	cout << "Hotel: " << nombreHotel << endl;
	cout << "Ciudad: " << ciudad << endl;
	cout << "Fecha de Ingreso: " << fechaIngreso << endl;
	cout << "Fecha de Salida: " <<  fechaSalida<< endl;
	cout << "Noches: " << noches << endl;
	cout << "Habitacion: " << habitacion << endl;
	cout << "Tipo de habitacion: " << ObtenerTipoO(tipoO) << endl;
	cout << "Tipo de cama/s: " << ObtenerTipoC(tipoC) << endl;
	cout << "Tipo de servicio: " << ObtenerTipoS(tipoS) << endl;
	cout << "Precio Total $" << getPrecioTotal() << endl;
}
string ReservaHotel::aTextoArchivo() {
	return "HOTEL,"+codigoUsuario + "," + nombreUsuario + "," + nombreHotel + ","
		+ ciudad + "," + fechaIngreso+ "," +to_string(precioNoche) + "," + to_string(noches) + "," +
		to_string(habitacion) +","+to_string(tipoO)+"," + to_string(tipoC) +"," +
		to_string(tipoS);
}
string ReservaHotel::getNombreHotel() { return nombreHotel; }
string ReservaHotel::getCiudad() { return ciudad; }
int ReservaHotel::getNoches() { return noches; }
int ReservaHotel::getHabitacion() { return habitacion; }
int ReservaHotel::getTipoO() { return tipoO; }
int ReservaHotel::getTipoC() { return tipoC; }
int ReservaHotel::getTipoS() { return tipoS; }
float ReservaHotel::getPrecioTotal() {
	return precioNoche* noches+(tipoO+tipoC+tipoS)*30; 
}
void ReservaHotel::setNombreHotel(string nombreHotel) { this->nombreHotel = nombreHotel; }
void ReservaHotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void ReservaHotel::setNoches(int noches) { this->noches = noches; }
void ReservaHotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche	; }
void ReservaHotel::setHabitacion(int habitacion) { this->habitacion = habitacion; }
void ReservaHotel::setTipoO(int tipoO) { this->tipoO = tipoO; }
void ReservaHotel::setTipoC(int tipoC) { this->tipoC = tipoC; }
void ReservaHotel::setTipoS(int tipoS) { this->tipoS = tipoS; }