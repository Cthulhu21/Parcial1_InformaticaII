#include <Funciones.h>

using namespace std;

int main()
{
    char Codigos[20][7]={}, Nombres[20][40]={}, Teoricas[20]={}, Independientes[20]={}, Creditos[20]={}, Horarios[20][40]={};
    CargarMaterias(Codigos, Nombres, Teoricas, Independientes, Creditos, Horarios);
    CalculoIndependientes(Teoricas, Independientes, Creditos);
    char Horario[7][24]={};
    GestionHorario(Horario, Codigos, Nombres, Creditos, Horarios);
    return 0;
}
