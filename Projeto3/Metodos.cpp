#include "Cabeçalho.h"

//**************************************************************************
bool sortIDM(const Item & item1, const Item & item2) {
	return item1.id < item2.id;
}

void printItens(vector<Item>& item)
{
	sort(item.begin(), item.end(), sortIDM);
	cout << "ID Mochila Categoria   Profit  Peso Compulsorio Densidade" << endl;
	for (int i = 0; i <= item.size() - 1; i++) {
		cout << item[i].id << "     " << item[i].mochila << "      " << item[i].categ << "         " <<
			item[i].lucro << "   " << item[i].peso << "      " << item[i].compulsorio << "      " << item[i].lucropeso << endl;
	}

}

void printItensMochila(vector<Item>& item)
{
	cout << "Mochila" << endl;
	for (int i = 0; i <= item.size() - 1; i++) {
		cout << item[i].mochila<< endl;
	}

}


void printItensDens(vector<Item>& item)
{
	cout << "ID   Lucro   Densidade" << endl;
	for (int i = 0; i <= item.size() - 1; i++) {
		cout << item[i].id << "    " << item[i].lucro << "    " << item[i].lucropeso << endl;
	}
}

void printlucroImag(vector<Item>& item)
{
	for (int i = 0; i <= item.size() - 1; i++)
	{
		cout << item[i].lucroImag << "   " << item[i].lucropesoImag << endl;
	}

}

void printMochilas(vector<Mochila>& mochila)
{
	cout << "ID   Capacidade   capDisp" << endl;
	for (int i = 0; i <= mochila.size() - 1; i++) {
		cout << mochila[i].id << "       " << mochila[i].cap << "       " << mochila[i].capDisp << endl;
	}
}

void printMochilasCom(vector<Mochila>& mochila)
{
	double LucroTotal = 0;
	int PesoTotal = 0;
	cout << "ID   Lucro   CapDisp  Porcentagem   Categ" << endl;
	for (int i = 0; i <= mochila.size() - 1; i++) {
		LucroTotal = LucroTotal + mochila[i].lucro;
		PesoTotal = PesoTotal - mochila[i].capDisp + mochila[i].cap;
		cout << mochila[i].id << "      " << mochila[i].lucro << "       " << mochila[i].capDisp << "    " << -((double)mochila[i].capDisp/(double)mochila[i].cap*100)+100 << "    ";
		for (int c = 0; c <= CATEGORIAS - 1; c++) {
			cout << " " << mochila[i].categ[c];
		}
		cout << endl;
	}
	
	cout << "Lucro Total: " << LucroTotal << endl;
	cout << "Peso Total: " << PesoTotal << endl;
}

void printvetorInt(vector<int>& vector)
{
	for (int i = 0; i <= vector.size() - 1; i++) {
		cout << vector[i] << endl;
	}
}

void printvetorDoubl(vector<double>& vector)
{
	for (int i = 0; i <= vector.size() - 1; i++) {
		cout << vector[i] << endl;
	}
}

//**************************************************************************


double LucroTotal(vector<Mochila>& mochila)
{
	double LucroTotal = 0;
	for (int i = 0; i <= mochila.size() - 1; i++)
		LucroTotal = LucroTotal + mochila[i].lucro;

	return LucroTotal + 0.0;
}

//*************************************************************************
/*
void Mochila::printItens(ofstream& saida, vector<Item>& item)
{


	
	saida << "ID Mochila Categoria   Profit  Peso Compulsorio Densidade" << endl;
	for (int i = 0; i <= item.size() - 1; i++) {
		saida << item[i].id << "     " << item[i].mochila << "      " << item[i].categ << "         " <<
			item[i].lucro << "   " << item[i].peso << "      " << item[i].compulsorio << "      " << item[i].lucropeso << endl;
	}
}*/