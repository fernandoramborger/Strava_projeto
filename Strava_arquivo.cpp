#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <locale.h>

using namespace std;

long double calculaDistancia (long double lat1, long double long1, long double lat2, long double long2)
{
	long double aux, dist, pi = 3.1415926536, raio = 6371;
	aux = pi / 180;
	dist = raio * acos(cos((90 - lat2) * aux) * cos((90 - lat1) * aux) + sin((90 - lat1) * aux) * sin((90 - lat2) * aux) * cos((long1 - long2) * aux));
	return dist;
}

void tempo (int tempoI, int tempoF, int &Ht, int &Mt, int &St)
{
	int tt;
	tt = tempoF - tempoI;
	Ht = tt / 3600;
	Mt = (tt % 3600) / 60;
	St = (tt % 60) % 60;

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

int main()
{
	setlocale(LC_ALL, "Portuguese");
	ifstream teste;
	ofstream saida;

	long double altMax, altMin, distancia, distanciaTotal = 0, velocidadeMedia, velocidadeParcial, velocidadeTotal = 0, velocidadeMaxima = -1, ganhoAlt = 0, perdaAlt = 0;
	int tempoI, tempoF, tempoTotal, Ht, Mt, St;
	int decisao;
	char escolhearquivo[50];
	strava dados[2];

	cout << "+-------------------------------------------+" << endl;
	cout << "| Bem-vindo ao Strava!                      |" << endl;
	cout << "|                                           |" << endl;
	cout << "| Escolha uma das opções:                   |" << endl;
	cout << "| 1- Entrar com os dados.                   |" << endl;
	cout << "| 2- Abrir o arquivo teste.                 |" << endl;
	cout << "| 0- Sair.                                  |" << endl;
	cout << "+-------------------------------------------+" << endl;

	cout << "Insira o comando: ";
	cin >> decisao;
	cout << endl;

	while(decisao != 1 && decisao != 2 && decisao != 0)
	{
		cout << "Digite 1 para entrar com os dados ou 2 para abrir o aquivo teste: " << endl;
		cin >> decisao;
	}

	if (decisao == 0)
	{
		return 0;
	}


	if (decisao == 1)
	{
		cout << "Digite a latitude e longitude: " << endl;
		cin >> dados[0].lat >> dados[0].lon;
		while (dados[0].lat != 0 && dados[0].lon != 0)
		{
			cout << "Digite a elevação: " << endl;
			cin >> dados[0].eleva;
			altMax = dados[0].eleva;
			altMin = dados[0].eleva;
			cout << "Digite a hora, minutos e segundos: " << endl;
			cin >> dados[0].hora >> dados[0].min >> dados[0].seg;
			tempoI = tempoSegundos(dados[0].hora, dados[0].min, dados[0].seg);
			dados[0].tempo = tempoI;
			cout << "Digite a latitude e longitude: " << endl;
			cin >> dados[1].lat >> dados[1].lon;
			while(dados[1].lat != 0 && dados[1].lon != 0)
			{
				cout << "Digite a elevação: " << endl;
				cin >> dados[1].eleva;
				cout << "Digite a hora, minutos e segundos: " << endl;
				cin >> dados[1].hora >> dados[1].min >> dados[1].seg;
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
				cout << "Digite a latitude e longitude: " << endl;
				cin >> dados[1].lat >> dados[1].lon;
			}
			dados[0].lat = dados[1].lat;
			dados[0].lon = dados[1].lon;
			cout << endl;
		}
	}

	if (decisao == 2)
	{
		cout << "Digite o nome do arquivo que deseja abrir (não esqueça do .txt): ";
		cin >> escolhearquivo;
		cout << endl;
		teste.open(escolhearquivo, ifstream :: in);
		if (teste.is_open())
		{
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
		}
		else 
		{
			while (teste.is_open() == false)
			{
				cout << "Não foi possível abrir o arquivo, tente novamente: " << endl;
				cout << "Nome do arquivo: ";
				cin >> escolhearquivo;
				cout << endl;
				teste.open(escolhearquivo, ifstream :: in);
				if (teste.is_open())
				{
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
				}
			}
		}
	}


	cout << fixed << setprecision(2);

	cout << "Distância total: " << distanciaTotal << " km" << endl;
	tempoF = tempoSegundos(dados[1].hora, dados[1].min, dados[1].seg);
	tempoTotal = tempoF - tempoI;
	tempo(tempoI, tempoF, Ht, Mt, St);
	cout << "Tempo total decorrido: " << Ht << ":" << Mt << ":" << St << endl;
	velocidadeMedia = (distanciaTotal / tempoTotal) * 3600;
	cout << "Velocidade máxima: " << fixed << setprecision(2) << velocidadeMaxima * 3600 << " km/h" << endl;
	cout << "Velocidade média: " << velocidadeMedia << " km/h" << endl;
	cout << "Ganho de elevação: ";
	cout << ganhoAlt << " m" << endl;
	cout << "Perda de elevação: ";
	cout << perdaAlt << " m" << endl;
	cout << "Maior altitude: ";
	cout << altMax << " m" << endl;
	cout << "Menor altitude: ";
	cout << altMin << " m" << endl;

	saida.open("resultado.txt" , ofstream :: out);
	saida << "Distância total: " << distanciaTotal << " km" << endl;
	tempo(tempoI, tempoF, Ht, Mt, St);
	saida << "Tempo total decorrido: " << Ht << ":" << Mt << ":" << St << endl;
	saida << "Velocidade maxima: " << fixed << setprecision(2) << velocidadeMaxima * 3600 << " km/h" << endl;
	saida << "Ganho de elevação: ";
	saida << ganhoAlt << " m" << endl;
	saida << "Perda de elevação: ";
	saida << perdaAlt << " m" << endl;
	saida << "Maior altitude: ";
	saida << altMax << " m" << endl;
	saida << "Menor altitude: ";
	saida << altMin << " m" << endl;

	return 0;
}
