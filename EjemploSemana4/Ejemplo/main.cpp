#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

// ============================================================
//  ESTRUCTURAS DE DATOS
// ============================================================

struct Curso {
    int codigo;
    string nombre;
    int creditos;
    int semestre;
    string carrera;
};

struct Nota {
    int carnet;
    int codigoCurso;
    double nota;
    string ciclo;
    int anio;
};

// ============================================================
//  FUNCION SPLIT
// ============================================================

vector<string> split(const string& linea, char delimitador) {
    vector<string> tokens;
    string token;
    istringstream stream(linea);
    while (getline(stream, token, delimitador)) {
        while (!token.empty() && (token.front() == ' ' || token.front() == '\r'))
            token.erase(token.begin());
        while (!token.empty() && (token.back() == ' ' || token.back() == '\r'))
            token.pop_back();
        tokens.push_back(token);
    }
    return tokens;
}

// ============================================================
//  LECTURA DE ARCHIVOS
// ============================================================

bool cargarCursos(const string& archivo, vector<Curso>& cursos) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir: " << archivo << endl;
        return false;
    }
    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        vector<string> partes = split(linea, ',');
        if (partes.size() < 5) continue;
        Curso c;
        c.codigo   = stoi(partes[0]);
        c.nombre   = partes[1];
        c.creditos = stoi(partes[2]);
        c.semestre = stoi(partes[3]);
        c.carrera  = partes[4];
        cursos.push_back(c);
    }
    file.close();
    cout << "Cursos cargados: " << cursos.size() << endl;
    return true;
}

bool cargarNotas(const string& archivo, vector<Nota>& notas) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir: " << archivo << endl;
        return false;
    }
    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        vector<string> partes = split(linea, ',');
        if (partes.size() < 5) continue;
        Nota n;
        n.carnet      = stoi(partes[0]);
        n.codigoCurso = stoi(partes[1]);
        n.nota        = stod(partes[2]);
        n.ciclo       = partes[3];
        n.anio        = stoi(partes[4]);
        notas.push_back(n);
    }
    file.close();
    cout << "Notas cargadas: " << notas.size() << endl;
    return true;
}

// ============================================================
//  CALCULO: SOLO PROMEDIO
// ============================================================

double calcularPromedio(const vector<double>& valores) {
    double suma = 0;
    for (double v : valores) suma += v;
    return suma / valores.size();
}

// ============================================================
//  GENERACION DE REPORTE HTML
// ============================================================

void generarReporte1(const vector<Curso>& cursos, const vector<Nota>& notas) {
    // Agrupar notas por codigo de curso
    map<int, vector<double>> notasPorCurso;
    for (const Nota& n : notas) {
        notasPorCurso[n.codigoCurso].push_back(n.nota);
    }

    ofstream html("reporte1_estadisticas_curso.html");
    if (!html.is_open()) {
        cout << "No se pudo crear el archivo HTML." << endl;
        return;
    }

    html << R"(<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Reporte 1 - Estadisticas Generales por Curso</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            font-family: 'Segoe UI', Arial, sans-serif;
            background: #f0f2f5;
            color: #333;
        }
        header {
            background: linear-gradient(135deg, #1a237e, #283593);
            color: white;
            padding: 30px 40px;
            text-align: center;
        }
        header h1 { font-size: 28px; margin-bottom: 6px; }
        header p  { font-size: 14px; opacity: 0.85; }
        .container { max-width: 900px; margin: 30px auto; padding: 0 20px; }
        table {
            width: 100%;
            border-collapse: collapse;
            background: white;
            border-radius: 10px;
            overflow: hidden;
            box-shadow: 0 4px 16px rgba(0,0,0,0.08);
        }
        thead tr { background: #1a237e; color: white; }
        thead th {
            padding: 14px 16px;
            text-align: center;
            font-size: 13px;
            letter-spacing: 0.5px;
        }
        tbody tr:nth-child(even) { background: #f5f7ff; }
        tbody tr:hover { background: #e8eaf6; transition: 0.2s; }
        tbody td {
            padding: 12px 16px;
            text-align: center;
            font-size: 13px;
            border-bottom: 1px solid #e0e0e0;
        }
        tbody td:first-child { text-align: left; font-weight: 600; }
        footer {
            text-align: center;
            padding: 20px;
            font-size: 12px;
            color: #888;
            margin-top: 30px;
        }
    </style>
</head>
<body>
<header>
    <h1> Reporte 1: Estadisticas Generales por Curso</h1>
</header>
<div class="container">
    <table>
        <thead>
            <tr>
                <th>Curso</th>
                <th>Código</th>
                <th>Carrera</th>
                <th>Estudiantes</th>
                <th>Promedio</th>
            </tr>
        </thead>
        <tbody>
)";

    for (const Curso& c : cursos) {
        auto it = notasPorCurso.find(c.codigo);

        html << "            <tr>\n";
        html << "                <td>" << c.nombre  << "</td>\n";
        html << "                <td>" << c.codigo  << "</td>\n";
        html << "                <td>" << c.carrera << "</td>\n";

        if (it == notasPorCurso.end() || it->second.empty()) {
            html << "                <td>0</td>\n";
            html << "                <td style='color:#999;font-style:italic;'>Sin registros</td>\n";
        } else {
            double promedio = calcularPromedio(it->second);
            html << fixed << setprecision(2);
            html << "                <td>" << it->second.size() << "</td>\n";
            html << "                <td>" << promedio          << "</td>\n";
        }

        html << "            </tr>\n";
    }

    html << R"(        </tbody>
    </table>
</div>
</body>
</html>
)";

    html.close();
    cout << "\nReporte generado: reporte1_estadisticas_curso.html\n" << endl;
}

// ============================================================
//  MAIN
// ============================================================

int main() {
    vector<Curso> cursos;
    vector<Nota>  notas;

    bool curCargados = false;
    bool notCargados = false;

    int opcion;

    do {
        cout << "\n==========================================" << endl;
        cout << "   SISTEMA DE ANALISIS ACADEMICO"          << endl;
        cout << "==========================================" << endl;
        cout << "1. Cargar archivo de cursos"               << endl;
        cout << "2. Cargar archivo de notas"                << endl;
        cout << "3. Generar Reporte 1: Estadisticas por Curso" << endl;
        cout << "4. Salir"                                  << endl;
        cout << "------------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin  >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string archivo;
                cout << "Ruta del archivo (ej: cursos.lfp): ";
                getline(cin, archivo);
                cursos.clear();
                curCargados = cargarCursos(archivo, cursos);
                break;
            }
            case 2: {
                string archivo;
                cout << "Ruta del archivo (ej: notas.lfp): ";
                getline(cin, archivo);
                notas.clear();
                notCargados = cargarNotas(archivo, notas);
                break;
            }
            case 3: {
                if (!curCargados || !notCargados) {
                    cout << "Debes cargar cursos.lfp y notas.lfp primero." << endl;
                } else {
                    generarReporte1(cursos, notas);
                }
                break;
            }
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
        }

    } while (opcion != 4);

    return 0;
}
