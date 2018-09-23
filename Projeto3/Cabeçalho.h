#pragma once

#include <iomanip>
#include <tchar.h>
#include <iostream>
#include <fstream> // arquivo texto
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <math.h>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <random>
#include "gurobi_c++.h"
#define CATEGORIAS 6

using namespace std;

//Classe Item
class Item {
public:
	int id;
	int peso;
	int categ;
	double lucro;
	double lucroImag;
	int compulsorio;
	double lucropeso;
	double lucropesoImag;
	int mochila = -1;

	
};




//Classe Mochila
class Mochila {
public:
	int id;
	int cap;
	vector<int> categ = { 0,0,0,0,0,0 };
	int capDisp;
	double lucro;
	//void printItens(ofstream& saida, vector<Item>& item);
	//Mochila();
	//~Mochila();
};

class Dados
{
public:
	Dados(string localArquivo, int& mochila, int& capacidade, vector<Item>& item);

};

//***********************************
//print
void printItens(vector<Item>& item);

void printItensMochila(vector<Item>& item);

void printItensDens(vector<Item>& item);

void printlucroImag(vector<Item>& item);

void printMochilas(vector<Mochila>& mochila);

void printMochilasCom(vector<Mochila>& mochila);

void printvetorInt(vector<int>& vector);

void printvetorDoubl(vector<double>& vector);


//***********************************

double LucroTotal(vector<Mochila>& mochila);

int PesoTotal(vector<Mochila>& mochila);