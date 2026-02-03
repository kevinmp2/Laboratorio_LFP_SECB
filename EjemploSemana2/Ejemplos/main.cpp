#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

    // constantes
const int MAX_ESTUDIANTE = 100;
const double NOTA_MINIMA_APROBACION = 61.0;

class Estudiante {
        private:
            string m_nombre;
            int m_edad;
            vector<double> m_calificaciones;

        public:
            Estudiante(string nombre, int edad)
                : m_nombre(nombre), m_edad(edad){}

        void agregarCalificacion(double nota){

            if ( nota >= 0 && nota <= 100 ) {
                m_calificaciones.push_back(nota);
            }
        }

        double calcularPromedio() const {

            if(m_calificaciones.empty()) return 0.0;

            double suma = 0;

            for(double nota : m_calificaciones){
                suma = suma + nota;
            }

            return suma/m_calificaciones.size();

        }

        bool estaAprobado() const {

            return calcularPromedio() >= NOTA_MINIMA_APROBACION;

        }


        void mostrarInfo(){
            cout << "Nombre: " << m_nombre << endl;
            cout << "Edad: " << m_edad << endl;
            cout << "Promedio" << calcularPromedio();
            cout << "(" << (estaAprobado()? "Aprobado": "Reprobado") << ")" << endl;
        }

};

int main()
{

    Estudiante* nuevoEstudiante1 =  new Estudiante("Samuel Pereira", 23 );

    Estudiante* nuevoEstudiante2 =  new Estudiante("Mario Marroquin", 23);


    nuevoEstudiante1->agregarCalificacion(80);
    nuevoEstudiante1->agregarCalificacion(90);

    nuevoEstudiante2->agregarCalificacion(80);
    nuevoEstudiante2->agregarCalificacion(80);

    nuevoEstudiante1->calcularPromedio();
    nuevoEstudiante2->calcularPromedio();

    nuevoEstudiante1->mostrarInfo();
    nuevoEstudiante2->mostrarInfo();






}
