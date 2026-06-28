#include "ReservaPaquete.h"
ReservaPaquete::ReservaPaquete(string codUser, string nomUser, ReservaVuelo* vueloida, ReservaVuelo* vueloretorno, ReservaHotel* hotel)
    : Reserva(codUser, nomUser)
{
    this->vueloReservado = vueloida;
    this->vueloRetorno = vueloretorno;
    this->hotelReservado = hotel;
    this->tipoReserva = "PAQUETE";
}

ReservaPaquete::~ReservaPaquete() {
    delete vueloReservado;
    delete vueloRetorno;
    delete hotelReservado;
}

void ReservaPaquete::MostrarReserva() {
    cout << "======================================" << endl;
    cout << "        PAQUETE TURISTICO             " << endl;
    cout << "Pasajero: " << nombreUsuario << endl;
    cout << "======================================" << endl;

    if (vueloReservado != nullptr) vueloReservado->MostrarReserva();
    cout << "--------------------------------------" << endl;
    if (hotelReservado != nullptr) hotelReservado->MostrarReserva();
    cout << "--------------------------------------" << endl;
    if (vueloRetorno != nullptr) vueloRetorno->MostrarReserva();
    float total = vueloReservado->getPrecioTotal() + hotelReservado->getPrecioTotal()+vueloRetorno->getPrecioTotal();
    cout << "======================================" << endl;
    cout << "PRECIO TOTAL DEL PAQUETE: $" << total << endl;
    cout << "======================================" << endl;
}
string ReservaPaquete::aTextoArchivo() {
    return "PAQUETE," + codigoUsuario + "," + nombreUsuario + "|" + vueloReservado->aTextoArchivo() +"|"+vueloRetorno->aTextoArchivo() + "|" + hotelReservado->aTextoArchivo();
}
ReservaVuelo* ReservaPaquete::getVueloReservado() { return vueloReservado; }
ReservaHotel* ReservaPaquete::getHotelReservado() { return hotelReservado; }
ReservaVuelo* ReservaPaquete::getVueloRetorno() { return vueloRetorno; }
void ReservaPaquete::setVueloReservado(ReservaVuelo* vuelo) { this->vueloReservado = vuelo; }
void ReservaPaquete::setHotelReservado(ReservaHotel* hotel) { this->hotelReservado = hotel; }
void ReservaPaquete::setVueloRetorno(ReservaVuelo* vuelo) { this->vueloRetorno = vuelo; }
float ReservaPaquete::getPrecioTotal() {
    return vueloReservado->getPrecioTotal() + hotelReservado->getPrecioTotal();
}