#include "Cabeçalho.h"

 Dados::Dados(string localArquivo, int& mochila, int& capacidade, vector<Item>& item) {

	ifstream arquivo;
	arquivo.open(localArquivo);
	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo1" << endl;
		system("pause");
		return;
	}


	//Mochilas
	char Mochilas[4];
	arquivo.getline(Mochilas, 4, '\t');
	mochila = stoi(Mochilas);// Convert string para integer 

	//próxima linha
	char cdummy[255];
	arquivo.getline(cdummy, 255);

	//Capacidade 
	char ccapacity[7];
	arquivo.getline(ccapacity, 7, '\t');
	capacidade = stoi(ccapacity);

	//próxima linha
	arquivo.getline(cdummy, 255);

	//Quantidade de itens
	char citems[7];
	arquivo.getline(citems, 7, '\t');
	const int nitems = stoi(citems);

	//próxima linha
	arquivo.getline(cdummy, 255);
	//linha de títulos
	arquivo.getline(cdummy, 255);

	//Defino um vector para receber os dados de cada um dos itens
	item.resize(nitems);

	char auxitem[7] = "";
	int id = 0;
	while (arquivo.good())
	{

		arquivo.getline(auxitem, 7, '\t');
		if (strcmp(auxitem, "EOF") == -1)
		{
			id = stoi(auxitem);
			item[id].id = id;
			arquivo.getline(auxitem, 7, '\t');
			item[id].peso = stoi(auxitem);
			arquivo.getline(auxitem, 7, '\t');
			item[id].categ = stoi(auxitem);
			arquivo.getline(auxitem, 7, '\t');
			item[id].lucro = stoi(auxitem);
			arquivo.getline(auxitem, 7, '\t');
			item[id].compulsorio = stoi(auxitem);
			item[id].lucropeso = (double)item[id].lucro / (double)item[id].peso;
			item[id].lucroImag = item[id].lucro;
			item[id].lucropesoImag = (double)item[id].lucroImag / (double)item[id].peso;
			arquivo.getline(cdummy, 255);
		}
		else
		{
			break;
		}

	}
}
 /*
void MatrizCompatibilidade::Matriz()
 {
	 vector<vector<int>> MatrizCompatibilidade =
	 { 
	 { 1, 0, 1, 0, 0, 0 },
	 { 0, 1, 0, 1, 1, 1 },
	 { 1, 0, 1, 1, 0, 0 },
	 { 0, 1, 1, 1, 1, 1 },
	 { 0, 1, 0, 1, 1, 0 },
	 { 0, 1, 0, 1, 0, 1 } };

	 for (int i = 0; i <= 5; i++) {
		 for (int j = 0; j <= 5; j++) {
			 cout << MatrizCompatibilidade[i][j];
		 }
		 cout << endl;
	 }
 }
 */
 /*
 Mochila::Mochila(vector<Mochila>& Mochila, int mochila, int capacidade)
 {
	 for (int i = 0; i <= mochila - 1; i++) {
		 Mochila[i].id = i;
		 Mochila[i].cap = capacidade;
		 Mochila[i].capDisp = capacidade;
	 }
 }
// */
