#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

long double calculaDistancia (long double lat1, long double long1, long double lat2, long double long2){
    long double aux, dist, pi = 3.1415926536, raio = 6371;
    aux = pi / 180;
    dist = raio * acos(cos((90 - lat2) * aux) * cos((90 - lat1) * aux) + sin((90 - lat1) * aux) * sin((90 - lat2) * aux) * cos((long1 - long2) * aux));
    return dist;
}

void tempo (int tempoI, int tempoF)
{
    int tt;
    int Ht, Mt, St;
    tt = tempoF - tempoI;
    Ht = tt / 3600; 
    Mt = (tt % 3600) / 60; 
    St = (tt % 60) % 60; 
    cout << "Tempo total decorrido: " << Ht << ":" << Mt << ":" << St << endl;
}

int tempoSegundos(int hora, int min, int seg)
{
	int totalSegundos = hora * 3600 + min * 60 + seg;
	return totalSegundos;
}

long double velocidade(int tempo1, int tempo2, long double distancia)
{
	long double velocidadeParcial = distancia / (tempo2 - tempo1);
	return velocidadeParcial;
}

struct strava
{
    double lat;
    double lon;
    double altitude;
    int hora, min, seg, tempo;
    double eleva;
};

int main(){
	ifstream teste;
	ofstream saida;
	
	long double altMax, altMin, distancia, distanciaTotal = 0, velocidadeMedia, velocidadeParcial, velocidadeTotal = 0, velocidadeMaxima = -1, ganhoAlt = 0, perdaAlt = 0;
	int tempoI, tempoF, tempoTotal;
    strava dados[2];
    
    teste.open("in.txt", ifstream :: in);
    
    teste >> dados[0].lat >> dados[0].lon;
    while (dados[0].lat != 0 && dados[0].lon != 0)
    {
        teste >> dados[0].eleva;
        altMax = dados[0].eleva;
        altMin = dados[0].eleva;
        teste >> dados[0].hora >> dados[0].min >> dados[0].seg;
        tempoI = tempoSegundos(dados[0].hora, dados[0].min, dados[0].seg);
        dados[0].tempo = tempoI;
        teste >> dados[1].lat >> dados[1].lon;
        while(dados[1].lat != 0 && dados[1].lon != 0)
		{
			teste >> dados[1].eleva;
			teste >> dados[1].hora >> dados[1].min >> dados[1].seg;
			dados[1].tempo = tempoSegundos(dados[1].hora, dados[1].min, dados[1].seg);
			distancia = calculaDistancia (dados[0].lat, dados[0].lon, dados[1].lat, dados[1].lon);
			distanciaTotal += distancia;
			velocidadeParcial = velocidade(dados[0].tempo, dados[1].tempo, distancia);
			velocidadeTotal += velocidadeParcial;
			if(velocidadeParcial > velocidadeMaxima)
			{
				velocidadeMaxima = velocidadeParcial;
			}
			if(dados[1].eleva > altMax)
			{
				altMax = dados[1].eleva;
			}
			else if (dados[1].eleva < altMin)
			{
				altMin = dados[1].eleva;
			}
			if(dados[0].eleva > dados[1].eleva)
			{
				perdaAlt += (dados[1].eleva - dados[0].eleva);
			}
			else
			{
				ganhoAlt += (dados[1].eleva - dados[0].eleva);
			}
			dados[0].lat = dados[1].lat;
			dados[0].lon = dados[1].lon;
			dados[0].eleva = dados[1].eleva;
			dados[0].tempo = dados[1].tempo;
			teste >> dados[1].lat >> dados[1].lon;
		}
		dados[0].lat = dados[1].lat;
		dados[0].lon = dados[1].lon;
    }
    
    cout << fixed << setprecision(2);
    
    cout << "Distancia total: " << distanciaTotal << " km" << endl;
    tempoF = tempoSegundos(dados[1].hora, dados[1].min, dados[1].seg);
    tempoTotal = tempoF - tempoI;
	tempo(tempoI, tempoF);
	velocidadeMedia = (distanciaTotal / tempoTotal) * 3600;
    cout << "Velocidade maxima: " << fixed << setprecision(2) << velocidadeMaxima * 3600 << " km/h" << endl;
    cout << "Velocidade media: " << velocidadeMedia << " km/h" << endl;
    cout << "Ganho de elevacao: ";
    cout << ganhoAlt << " m" << endl;
    cout << "Perda de elevacao: ";
    cout << perdaAlt << " m" << endl;
    cout << "Maior altitude: ";
    cout << altMax << " m" << endl;
    cout << "Menor altitude: ";
    cout << altMin << " m" << endl;
    
    saida.open("resultado.txt" , ofstream :: out);
    saida << "Distancia total: " << distanciaTotal << " km" << endl;
    saida << tempo(tempoI, tempoF);
    saida << "Velocidade maxima: " << fixed << setprecision(2) << velocidadeMaxima * 3600 << " km/h" << endl;
    saida << "Ganho de elevacao: ";
    saida << ganhoAlt << " m" << endl;
    saida << "Perda de elevacao: ";
    saida << perdaAlt << " m" << endl;
    saida << "Maior altitude: ";
    saida << altMax << " m" << endl;
    saida << "Menor altitude: ";
    saida << altMin << " m" << endl;
    
    
    return 0;
}