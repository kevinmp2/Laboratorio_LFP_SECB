// SISTEMA DE CALIFICACIONES

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ESTRUCTURA DE DATO STRUCT
struct Estudiante {
    string nombre;
    int calificacion[3]; // 60, 70, 80
    double promedio;

};

double calcularPromedio(int calificaciones[], int tam) {
    int suma = 0; // 0 + 60 = 60, 60 + 70 = 130, 130 + 80= 210

    for(int i = 0; i < tam; i++) {
        suma += calificaciones[i]; // 1. 60, 2. 70, 3. 80
        // suma = 210
    }

    return (double)suma / tam; // 210/3 = 70;
}

// FUNCION PARA LEET UN ARCHIVO

vector<Estudiante> leerEstudiante(string nombreArchivo){
    vector<Estudiante> estudiantes;
    ifstream archivo(nombreArchivo);

    if(archivo.is_open()) {
        string nombre;
        int cal1, cal2, cal3;

        while( archivo >> nombre >> cal1 >> cal2 >> cal3) {
            Estudiante est;

            est.nombre = nombre; // Miguel
            est.calificacion[0] = cal1; // 90
            est.calificacion[1] = cal2; // 60
            est.calificacion[2] = cal3; // 80
            est.promedio = calcularPromedio(est.calificacion,3);

            estudiantes.push_back(est);

        }
        archivo.close();
    }
    return estudiantes;
}

// FUNCION PARA ESCRIBIR REPORTE

void generarReporte(vector<Estudiante>& estudiante, string nombreArchivo){
    ofstream archivo(nombreArchivo);

    if(archivo.is_open()){
        archivo << "==== Reporte de Calificaciones ===" << endl << endl;

         for(const auto& est : estudiante){
            archivo << "Estudienate" << est.nombre << endl;
            archivo << "Calificaciones: ";

            for(int i = 0; i < 3; i++){
                archivo << est.calificacion[i] << " ";
            }

            archivo << endl << "Promedio " << est.promedio << endl;
            archivo << "--------------" << endl;
         }

         archivo.close();
         cout << "Reporte generado existosamente" << endl;
    }
}


int main()
{

    // Leer archivo
    vector<Estudiante> estudiante = leerEstudiante("estudiantes.txt");

    cout << "Total estudiantes: " << estudiante.size() << endl << endl;

    for(const auto& est: estudiante){
        cout << est.nombre << " - Promedio: " << est.promedio << endl;
    }

    generarReporte(estudiante, "reporteEstudiante.txt");

    return 0;
}
