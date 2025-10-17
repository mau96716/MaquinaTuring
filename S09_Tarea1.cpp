#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Direccion { IZQ, DER };

struct Transicion {
	string estadoActual;
	char simboloLectura;
	string estadoSiguiente;
	char simboloEscritura;
	Direccion dirMov;
};

class MaquinaTuring {
	string estadoActual;
	int cabezal;
	vector<char> cinta;
	vector<Transicion> transiciones;
	
public:
	MaquinaTuring(string estadoInicial, vector<Transicion> tr, string entrada)
		: estadoActual(estadoInicial), transiciones(tr), cabezal(1)
	{
		cinta = vector<char>(entrada.begin(), entrada.end());
		cinta.insert(cinta.begin(), '_');
		cinta.push_back('_');
	}
	
	void ejecutar() {
		while (true) {
			bool trE = false;
			
			for (const auto& t : transiciones) {
				if (t.estadoActual == estadoActual && t.simboloLectura == cinta[cabezal]) {
					cinta[cabezal] = t.simboloEscritura;
					estadoActual = t.estadoSiguiente;
					cabezal += (t.dirMov == DER) ? 1 : -1;
					trE = true;
					break;
				}
			}
			
			if (!trE || estadoActual == "q6") break;
		}
		
		cout << "Estado final: " << estadoActual << endl;
		cout << "Cinta final: ";
		for (char c : cinta) cout << c;
		cout << endl;
	}
};

int main(int argc, char** argv) {
	vector<Transicion> transiciones = {
		
	{"q0", '1', "q0", '1', DER},
	{"q0", '0', "q0", '0', DER},
	{"q0", '_', "q1", '_', IZQ},
	{"q1", '0', "q1", '0', IZQ},
	{"q1", '1', "q1", '1', IZQ},
	{"q1", '_', "q2", '?', DER},
	{"q2", '1', "q3", '?', DER},
	{"q2", '0', "q4", '?', DER},
	{"q2", '?', "q5", '?', DER},
	{"q2", '_', "q1", '_', IZQ},
	{"q3", '1', "q3", '1', DER},
	{"q3", '0', "q3", '0', DER},
	{"q3", '_', "q1", '1', IZQ},
	{"q4", '1', "q4", '1', DER},
	{"q4", '0', "q4", '0', DER},
	{"q4", '_', "q1", '0', IZQ},
	{"q5", '?', "q1", '?', IZQ},
	{"q1", '0', "q6_Ac", '1', DER},
	{"q1", '1', "q1", '0', IZQ}, 
	{"q1", '?', "q6_Ac", '1', DER}, 
	};
	
	string entrada;
	cout << "Ingrese palabra: ";
	cin >> entrada;
	
	MaquinaTuring mt("q0", transiciones, entrada);
	mt.ejecutar();
	
	return 0;
}
