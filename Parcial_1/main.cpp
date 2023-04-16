#include <Funciones.h>

using namespace std;

int main()
{
    char Codigos[20][7]={}, Nombres[20][40]={}, Teoricas[20]={}, Independientes[20]={}, Creditos[20]={};
    CargarMaterias(Codigos, Nombres, Teoricas, Independientes, Creditos);
    CalculoIndependientes(Teoricas, Independientes, Creditos);
    return 0;
}
