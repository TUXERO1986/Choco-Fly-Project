#include "ReservaPaquete.h"
ReservaPaquete::ReservaPaquete(string codUser, string nomUser, ReservaVuelo* vueloida, ReservaVuelo* vueloretorno, ReservaHotel* hotel,int id)
    : Reserva(codUser, nomUser,id)
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

#include "Color.h"

void ReservaPaquete::MostrarDatos() {
    ColorUI::printGradient("\n==================================================", ColorUI::Paletas::TemaPrincipal, false);
    ColorUI::printGradient("                PAQUETE TURISTICO                 ", ColorUI::Paletas::TemaPrincipal, false);
    ColorUI::printGradient(" Pasajero: " + nombreUsuario, ColorUI::Paletas::Exito, false);
    ColorUI::printGradient("==================================================\n", ColorUI::Paletas::TemaPrincipal, false);

    if (vueloReservado != nullptr) vueloReservado->MostrarDatos();
    if (hotelReservado != nullptr) hotelReservado->MostrarDatos();
    if (vueloRetorno != nullptr) vueloRetorno->MostrarDatos();
    
    float total = 0;
    if (vueloReservado != nullptr) total += vueloReservado->getPrecioTotal();
    if (hotelReservado != nullptr) total += hotelReservado->getPrecioTotal();
    if (vueloRetorno != nullptr) total += vueloRetorno->getPrecioTotal();

    ColorUI::printGradient("==================================================", ColorUI::Paletas::TemaPrincipal, false);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", total);
    ColorUI::printGradient(" PRECIO TOTAL DEL PAQUETE: $" + string(buffer), ColorUI::Paletas::gege, false);
    ColorUI::printGradient("==================================================\n", ColorUI::Paletas::TemaPrincipal, false);
}
string ReservaPaquete::aTextoArchivo() {
    return "PAQUETE," + codigoUsuario + "," + nombreUsuario + "|" + vueloReservado->aTextoArchivo() +"|"+vueloRetorno->aTextoArchivo() + "|" + hotelReservado->aTextoArchivo()+"|"+to_string(id);
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