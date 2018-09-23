#include "Cabeçalho.h"

vector<vector<int>> MatrizCompatibilidade = { 
{ 1, 0, 1, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1 },
{ 1, 0, 1, 1, 0, 0 },
{ 0, 1, 1, 1, 1, 1 },
{ 0, 1, 0, 1, 1, 0 },
{ 0, 1, 0, 1, 0, 1 } };

vector<int> GuardarSolucao;
vector<double> itensRuins;

void contruirMochilas(vector<Mochila>& mochila1, int mochila, int capacidade)
{
	for (int i = 0; i <= mochila - 1; i++) {
		mochila1[i].id = i;
		mochila1[i].cap = capacidade;
		mochila1[i].capDisp = capacidade;

	}
}

bool sortComLucropeso(const Item & item1, const Item & item2) {
	if (item1.compulsorio != item2.compulsorio)
	{
		return item1.compulsorio > item2.compulsorio;
	}
	return item1.lucropeso > item2.lucropeso;
}

bool sortID(const Item & item1, const Item & item2) {
	return item1.id < item2.id;
}

bool sortLucropeso(const Item & item1, const Item & item2) {
	return item1.lucropeso > item2.lucropeso;
}

bool sortLucropesoInver(const Item & item1, const Item & item2) {
	return item1.lucropeso < item2.lucropeso;
}

bool sortlucroImag(const Item & item1, const Item & item2)
{
	if (item1.compulsorio != item2.compulsorio)
	{
		return item1.compulsorio > item2.compulsorio;
	}
	return item1.lucropesoImag > item2.lucropesoImag;
}

bool sortMochilaDisponibilidade(const Mochila & mochila1, const Mochila & mochila2)
{
	return mochila1.capDisp > mochila2.capDisp;
}

bool ChecaCompatibilidade(int categoriaItem, vector<int> categoriaIn, vector<vector<int>> MatrizCompatibilidade)
{
	categoriaIn[categoriaItem - 1] = 1;

	for (int c = 0; c <= CATEGORIAS - 1; c++)
	{
		if (categoriaIn[c] > MatrizCompatibilidade[categoriaItem - 1][c])
		{
			return false;
		}
	}
	return true;
}

void BestFit(vector<Mochila>& mochila, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade) {

	sort(item.begin(), item.end(), sortComLucropeso);
	for (int i = 0; i <= item.size() - 1; i++)
	{

		for (int j = 0; j <= mochila.size() - 1; j++)
		{

			if (ChecaCompatibilidade(item[i].categ, mochila[j].categ, MatrizCompatibilidade) == true)
			{
				if (item[i].mochila == -1 && item[i].peso <= mochila[j].capDisp && item[i].mochila != -2)
				{

					mochila[j].categ[item[i].categ - 1] = 1;
					item[i].mochila = mochila[j].id;
					mochila[j].capDisp = mochila[j].capDisp - item[i].peso;
					mochila[j].lucro = mochila[j].lucro + item[i].lucro;
					//sort(item.begin(), item.end(), sortComLucropeso);

					break;

				}
			}
		}
	}
	sort(item.begin(), item.end(), sortID);
}

void BestFitcomp(vector<Mochila>& mochila, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade) {

	//sort(item.begin(), item.end(), sortComLucropeso);
	for (int i = 0; i <= item.size() - 1; i++)
	{

		for (int j = 0; j <= mochila.size() - 1; j++)
		{

			if (ChecaCompatibilidade(item[i].categ, mochila[j].categ, MatrizCompatibilidade) == true)
			{
				if (item[i].mochila == -1 && item[i].peso <= mochila[j].capDisp && item[i].compulsorio == 1)
				{

					mochila[j].categ[item[i].categ - 1] = 1;
					item[i].mochila = mochila[j].id;
					mochila[j].capDisp = mochila[j].capDisp - item[i].peso;
					mochila[j].lucro = mochila[j].lucro + item[i].lucro;
					//sort(item.begin(), item.end(), sortComLucropeso);

					break;

				}
			}
		}
	}
	//sort(item.begin(), item.end(), sortID);
}

void reeniciaProblemaCateg(vector<Mochila>& mochila, vector<Item>& item, int capacidade)
{
	//renicia o Mochila
	for (int i = 0; i <= mochila.size() - 1; i++) {
		mochila[i].id = i;
		mochila[i].cap = capacidade;
		mochila[i].capDisp = capacidade;
		mochila[i].categ = { 0,0,0,0,0,0 };
		mochila[i].lucro = 0;
	}
	//renicia o item
	for (int i = 0; i <= item.size() - 1; i++) {
		item[i].mochila = -1;
		item[i].lucroImag = item[i].lucro;
		double x = (double)item[i].lucroImag / (double)item[i].peso;
		item[i].lucropesoImag = x;
	}
}

void zeraMochila(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int idMochila)
{
	mochila1[idMochila].cap = capacidade;
	mochila1[idMochila].capDisp = capacidade;
	mochila1[idMochila].categ = { 0,0,0,0,0,0 };
	mochila1[idMochila].lucro = 0;
	for (int i = 0; i <= item.size() - 1; i++)
	{
		//cout<< item[i].mochila <<"   " << item[idMochila].mochila << "   " << idMochila << endl;

		if (item[i].mochila == idMochila)
			item[i].mochila = -1;
	}
}

void zeraProblema(vector<Mochila>& mochila, vector<Item>& item, int capacidade)
{
	//cout << " 4" << endl;
	for (int i = 0; i <= mochila.size() - 1; i++) {
		mochila[i].id = i;
		mochila[i].cap = capacidade;
		mochila[i].capDisp = capacidade;
		mochila[i].categ = { 0,0,0,0,0,0 };
		mochila[i].lucro = 0;
	}
	//cout << " 5" << endl;
	//printItens(item);
	for (int i = 0; i <= item.size() - 1; i++) {
		item[i].mochila = -1;
	}
	//cout << " 6" << endl;
}

void zeralucro(vector<Mochila>& mochila, vector<Item>& item, int capacidade)
{
	for (int i = 0; i <= mochila.size() - 1; i++) {
		mochila[i].lucro = 0;
	}
}

void MoveInMochilas(vector<Mochila>& mochila1, vector<Item>& item)
{
	for (int i = 0; i <= item.size() - 1; i++)
	{
		//cout << " 14" << endl;
		int x = item[i].mochila;
		if (x != -1 && x != -2)
		{
			//cout << " 15" << endl;
		for (int j = 0; j <= mochila1.size() - 1; j++)
		{
			//if (x != -1)
			//{
				//cout << item[i].mochila << endl;
				//verifica se o item cabe na mochila e checa compatibilidade
				//cout << item[i].peso << "  <   " << mochila1[j].capDisp << endl;
				if (item[i].peso < mochila1[j].capDisp && ChecaCompatibilidade(item[i].categ, mochila1[j].categ, MatrizCompatibilidade) == true)
				{
					//cout << item[i].peso << "  <   " << mochila1[j].capDisp << endl;
					//verifica se tera uma ocupacao melhor e evitar troca entre mochilas iguais
					if ((mochila1[j].capDisp - item[i].peso) < mochila1[x].capDisp && item[i].mochila != mochila1[j].id)
					{

						//cout << mochila1[j].capDisp - item[i].peso<< "  <   " << mochila1[x].capDisp << endl;
						//coloca e tira a categoria do item na mochila
						mochila1[j].categ[item[i].categ - 1] = 1;
						//verificar se é o unico item dessa categoria na mochila
						///*
						int z = 0;
						for (int k = 0; k <= item.size() - 1; k++)
						{
							if (item[k].categ == item[i].categ  && item[k].mochila == mochila1[x].id)
							{
								//cout << item[i].mochila << "  =  " << mochila1[x].id << endl;
								//cout << item[k].categ << "  =  " << item[i].categ << endl;
								z++;
								//cout <<"z  " << z << endl;
							}

						}
						if (z == 1)
						{
							mochila1[x].categ[item[i].categ - 1] = 0;
						}
						//*/

						//cout << item[i].mochila << "  --   " << mochila1[j].id << "     " << item[i].id << endl;
						//muda o item de mochila
						item[i].mochila = mochila1[j].id;
						//cout << item[i].mochila << "  --   " << mochila1[j].id << endl;

						//colocando na mochila j
						//cout << mochila1[j].capDisp << "  ---   " << mochila1[j].capDisp - item[i].peso << endl;
						mochila1[j].capDisp = mochila1[j].capDisp - item[i].peso;
						//cout << mochila1[j].capDisp<< endl;
						//cout << item[i].mochila<<"  "<<endl;
						//cout << mochila1[j].lucro << "  ---   " << mochila1[j].lucro + item[i].lucro << endl;
						mochila1[j].lucro = mochila1[j].lucro + item[i].lucro;
						//cout << mochila1[j].lucro << endl;


						//tirando da mochila x
						mochila1[x].capDisp = mochila1[x].capDisp + item[i].peso;
						//cout << item[i].mochila << "  " << endl;
						//cout << mochila1[x].lucro << "  ---   " << mochila1[x].lucro - item[i].lucro << endl;
						mochila1[x].lucro = mochila1[x].lucro - item[i].lucro;
						//cout << mochila1[x].lucro << endl;
						break;

					}

				}
			}
		}
	}
}

void GuardarSol(vector<Mochila>& mochila1, vector<Item>& item)
{
	sort(item.begin(), item.end(), sortID);
	GuardarSolucao.clear();
	for (int i = 0; i <= item.size() - 1; i++) {

		GuardarSolucao.push_back(item[i].mochila);
		//cout << GuardarSolucao[i]<< endl;
	}
}

void ReestaurarMelhorSol(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, vector<int> GuardarSolucao)
{
	sort(item.begin(), item.end(), sortID);
	zeraProblema(mochila1, item, capacidade);
	//printMochilasCom(mochila1);
	/*

	for (int i = 0; i <= GuardarSolucao.size() - 1; i++) {

	cout << GuardarSolucao[i] << endl;
	}
	//*/
	///*
	for (int j = 0; j <= mochila1.size() - 1; j++)
	{
		for (int i = 0; i <= GuardarSolucao.size() - 1; i++)
		{

			if (GuardarSolucao[i] == mochila1[j].id)
			{
				//cout << GuardarSolucao[i] << "   " << mochila1[j].id << endl;

				item[i].mochila = mochila1[j].id;

				mochila1[j].categ[item[i].categ - 1] = 1;
				mochila1[j].capDisp = mochila1[j].capDisp - item[i].peso;
				//cout << mochila1[j].capDisp <<  endl;
				mochila1[j].lucro = mochila1[j].lucro + item[i].lucro;

				//break;

			}

			//cout << i << endl;


		}

	}//*/
}

void MoveComp(vector<Mochila>& mochila1, vector<Item>& item, int capacidade)
{
	//sort(item.begin(), item.end(), sortLucropesoInver);
	//int Arruma = 0;
	for (int i = 0; i <= item.size() - 1; i++)
	{
		int x = item[i].mochila;
		if (x == -1 && item[i].compulsorio == 1)
		{
			//cout << x << "  " << item[i].compulsorio << endl;
			//cout << "ERRO comp fora  " << item[i].id << endl;

			//ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
			//zeraProblema(mochila1, item, capacidade);
			zeraProblema(mochila1, item, capacidade);
			//zeralucro(mochila1, item, capacidade);
			//LucroTotal(mochila1) = 0.0;
			/*
			int h = 0;
			for (int j = 0; j <= item.size() - 1; j++)
			{
				if (h == 1)
				{
					break;
				}
				if (item[j].mochila != -1 && item[j].compulsorio == 0)
				{


					if (item[j].peso >= item[i].peso )// && item[j].categ == item[i].categ)
					{

					
							if (ChecaCompatibilidade(item[i].categ, mochila1[item[j].mochila].categ, MatrizCompatibilidade) == true)
							{
								//mochila1[w].categ[item[i].categ - 1] = 1;
								item[i].mochila = item[j].mochila;
								mochila1[item[j].mochila].capDisp = mochila1[item[j].mochila].capDisp - item[i].peso + item[j].peso;
								mochila1[item[j].mochila].lucro = mochila1[item[j].mochila].lucro + item[i].lucro - item[j].lucro;
								item[j].mochila = -1;
								h++;
								Arruma++;
								break;

							
							}
					}
				}
				//*/
			/*
			}
			if (Arruma == 0)
			{
				ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
			}//*/
		}

	}


}

void MoveOutMochilas(vector<Mochila>& mochila1, vector<Item>& item)
{
	sort(item.begin(), item.end(), sortComLucropeso);
	for (int i = 0; i <= item.size() - 1; i++)
	{
		int x = item[i].mochila;
		for (int j = 0; j <= mochila1.size() - 1; j++)
		{
			if (x == -1)
			{
				//cout << item[i].mochila << endl;
				if (item[i].peso <= mochila1[j].capDisp && ChecaCompatibilidade(item[i].categ, mochila1[j].categ, MatrizCompatibilidade) == true)
				{
					//cout << mochila1[j].capDisp - item[i].peso<< "  >   " << mochila1[x].capDisp << endl;
					mochila1[j].categ[item[i].categ - 1] = 1;
					//cout << item[i].mochila << "  --   " << mochila1[j].id << "     " << item[i].id << endl;
					item[i].mochila = mochila1[j].id;
					//cout << item[i].mochila << "  --   " << mochila1[j].id << endl;

					//coloca o item na mochila
					mochila1[j].capDisp = mochila1[j].capDisp - item[i].peso;
					//cout << item[i].mochila << "  " << endl;
					//cout << mochila1[x].lucro << "  ---   " << mochila1[x].lucro - item[i].lucro << endl;
					mochila1[j].lucro = mochila1[j].lucro + item[i].lucro;
					//cout << mochila1[x].lucro << endl;
					break;



				}
			}
		}
	}
}

void SwapInMochilas(vector<Mochila>& mochila1, vector<Item>& item)
{

	for (int i = 0; i <= item.size() - 1; i++)
	{
		int x = item[i].mochila;
		if (x != -1 && x != -2)
		{
			//cout << x << endl;
			for (int j = 0; j <= item.size() - 1; j++)
			{
				int z = item[j].mochila;
				if (z != -1 && item[j].mochila == item[i].mochila && item[j].id != item[i].id && z != -2)
				{
					//cout << x << " --  " << z << endl;
					for (int h = 0; h <= item.size() - 1; h++)
					{
						int p = item[h].mochila;

						if (p != -1 && item[j].mochila != p && p != -2)
						{
							//cout << x << "   " << z << "   " << p << endl;
							//cout << item[i].mochila << endl;
							if ((mochila1[z].capDisp + item[i].peso + item[j].peso - item[h].peso) >= 0 && mochila1[z].capDisp + item[i].peso + item[j].peso < mochila1[z].capDisp + item[h].peso && (mochila1[p].capDisp - item[i].peso - item[j].peso + item[h].peso) >= 0)
							{

								//checa a compatibilidade de itens
								if (ChecaCompatibilidade(item[h].categ, mochila1[z].categ, MatrizCompatibilidade) == true && ChecaCompatibilidade(item[i].categ, mochila1[p].categ, MatrizCompatibilidade) && ChecaCompatibilidade(item[j].categ, mochila1[p].categ, MatrizCompatibilidade))
								{
									//cout << (mochila1[z].capDisp + item[i].peso + item[j].peso - item[h].peso) << "  >= 0   "<< endl;
									//cout << mochila1[p].capDisp - item[i].peso - item[j].peso + item[h].peso << "  >= 0   " << endl;
									//cout << mochila1[z].capDisp + item[i].peso + item[j].peso << "  <   " << mochila1[z].capDisp + item[h].peso << endl;

									//muda as categorias
									//verificar se é o unico item dessa categoria na mochila zerando a catg
									///*
									int r = 0;
									int e = 0;
									int u = 0;
									for (int k = 0; k <= item.size() - 1; k++)
									{
										if (item[k].categ == item[h].categ  && item[k].mochila == mochila1[z].id)
										{
											//cout << item[i].mochila << "  =  " << mochila1[x].id << endl;
											//cout << item[k].categ << "  =  " << item[i].categ << endl;
											r++;
											//cout <<"z  " << z << endl;
										}
										if (item[k].categ == item[j].categ  && item[k].mochila == mochila1[p].id)
										{
											//cout << item[i].mochila << "  =  " << mochila1[x].id << endl;
											//cout << item[k].categ << "  =  " << item[i].categ << endl;
											e++;
											//cout <<"z  " << z << endl;
										}
										if (item[k].categ == item[i].categ  && item[k].mochila == mochila1[p].id)
										{
											//cout << item[i].mochila << "  =  " << mochila1[x].id << endl;
											//cout << item[k].categ << "  =  " << item[i].categ << endl;
											u++;
											//cout <<"z  " << z << endl;
										}

									}
									if (r == 1)
									{
										mochila1[z].categ[item[h].categ - 1] = 0;
									}
									if (u == 1)
									{
										mochila1[p].categ[item[j].categ - 1] = 0;
									}
									if (e == 1)
									{
										mochila1[p].categ[item[i].categ - 1] = 0;
									}
									//*/


									mochila1[z].categ[item[h].categ - 1] = 1;
									mochila1[p].categ[item[i].categ - 1] = 1;
									mochila1[p].categ[item[j].categ - 1] = 1;



									//muda o id do item
									//cout << i << endl;
									//cout << item[i].mochila << "  --   " << mochila1[p].id << endl;
									//cout << item[j].mochila << "  --   " << mochila1[p].id << endl;
									//cout << item[h].mochila << "  --   " << mochila1[z].id << endl;
									//cout << endl;
									item[h].mochila = mochila1[z].id;
									item[i].mochila = mochila1[p].id;
									item[j].mochila = mochila1[p].id;

									//cout << item[i].mochila << "  --   " << mochila1[p].id << endl;
									//cout << item[j].mochila << "  --   " << mochila1[p].id << endl;
									//cout << item[h].mochila << "  --   " << mochila1[z].id << endl;
									//cout << endl; cout << endl;

									//cout << mochila1[j].capDisp << "  ---   " << mochila1[j].capDisp - item[i].peso << endl;
									//muda peso e lucro da mochila
									mochila1[z].capDisp = mochila1[z].capDisp + item[i].peso + item[j].peso - item[h].peso;
									//cout << mochila1[z].capDisp << "  z " << endl;
									//cout << item[i].mochila<<"  "<<endl;
									//cout << mochila1[j].lucro << "  ---   " << mochila1[j].lucro + item[i].lucro << endl;
									mochila1[z].lucro = mochila1[z].lucro - item[i].lucro - item[j].lucro + item[h].lucro;
									//cout << mochila1[j].lucro << endl;



									mochila1[p].capDisp = mochila1[p].capDisp - item[i].peso - item[j].peso + item[h].peso;
									//cout << item[i].mochila << "  " << endl;
									//cout << mochila1[p].capDisp << " p  " << endl;
									mochila1[p].lucro = mochila1[p].lucro + item[i].lucro + item[j].lucro - item[h].lucro;
									//cout << mochila1[x].lucro << endl;
									break;

								}
							}
						}
					}
				}
			}
		}


	}
}



void LocalSearch(vector<Mochila>& mochila1, vector<Item>& item)
{
	//cout << " 10" << endl;
	for (int i = 0; i <= 3; i++) 
	{
	//SwapInMochilas(mochila1, item);
	//SwapInMochilas(mochila1, item);
	//MoveOutMochilas(mochila1, item);
	//cout << LucroTotal(mochila1)<< endl;

	MoveInMochilas(mochila1, item);
	MoveInMochilas(mochila1, item);
	MoveInMochilas(mochila1, item);
	MoveInMochilas(mochila1, item);
	//MoveInMochilas(mochila1, item);
	//cout << " 13" << endl;
	MoveOutMochilas(mochila1, item);
	//cout << LucroTotal(mochila1) << endl;
	}
	//cout << " 11" << endl;
	/*
	//for (int i = 0; i <= 1; i++)
	//{
	SwapInMochilas(mochila1, item);
	SwapInMochilas(mochila1, item);
	SwapInMochilas(mochila1, item);
	//SwapInMochilas(mochila1, item);
	//cout << " 14" << endl;
	MoveOutMochilas(mochila1, item);
	//}//*/
	//cout << " 12" << endl;

}

void LocalSearch1(vector<Mochila>& mochila1, vector<Item>& item)
{
	//cout << " 10" << endl;
	//for (int i = 0; i <= 1; i++)
	//{
		//SwapInMochilas(mochila1, item);
		//SwapInMochilas(mochila1, item);
		//MoveOutMochilas(mochila1, item);
		//cout << LucroTotal(mochila1)<< endl;

		MoveInMochilas(mochila1, item);
		MoveInMochilas(mochila1, item);
		MoveInMochilas(mochila1, item);
		//MoveInMochilas(mochila1, item);
		//MoveInMochilas(mochila1, item);
		//cout << " 13" << endl;
		MoveOutMochilas(mochila1, item);
		//cout << LucroTotal(mochila1) << endl;
	//}
	//cout << " 11" << endl;
	/*
	//for (int i = 0; i <= 1; i++)
	//{
	SwapInMochilas(mochila1, item);
	SwapInMochilas(mochila1, item);
	SwapInMochilas(mochila1, item);
	//SwapInMochilas(mochila1, item);
	//cout << " 14" << endl;
	MoveOutMochilas(mochila1, item);
	//}//*/
	//cout << " 12" << endl;

}

void LocalSearch2(vector<Mochila>& mochila1, vector<Item>& item)
{
	//cout << " 10" << endl;
	//for (int i = 0; i <= 1; i++)
	//{
	//SwapInMochilas(mochila1, item);
	//SwapInMochilas(mochila1, item);
	//MoveOutMochilas(mochila1, item);
	//cout << LucroTotal(mochila1)<< endl;

	MoveInMochilas(mochila1, item);
	//MoveInMochilas(mochila1, item);
	//MoveInMochilas(mochila1, item);
	//MoveInMochilas(mochila1, item);
	//MoveInMochilas(mochila1, item);
	//cout << " 13" << endl;
	MoveOutMochilas(mochila1, item);
	//cout << LucroTotal(mochila1) << endl;
	//}
	//cout << " 11" << endl;
	/*
	//for (int i = 0; i <= 1; i++)
	//{
	SwapInMochilas(mochila1, item);
	SwapInMochilas(mochila1, item);
	SwapInMochilas(mochila1, item);
	//SwapInMochilas(mochila1, item);
	//cout << " 14" << endl;
	MoveOutMochilas(mochila1, item);
	//}//*/
	//cout << " 12" << endl;

}

void Shaking1(vector<Mochila>& mochila1, vector<Item>& item)
{
	int x = rand() % 6 + 1;
	//cout << x << endl;
	for (int i = 0; i <= item.size() - 1; i++)
	{
		int l = item[i].mochila;
		//cout << item[i].mochila << endl;
		if (item[i].categ == x && item[i].mochila != -1 && item[i].categ != 1)
		{
			//cout << x << "  " << item[i].categ << endl;
			mochila1[l].categ[item[i].categ - 1] = 0;
			// cout << item[i].mochila << "  --   " << mochila1[j].id << "     " << item[i].id << endl;
			item[i].mochila = -1;
			//cout << item[i].mochila << "  --   " << mochila1[j].id << endl;

			//coloca o item na mochila
			mochila1[l].capDisp = mochila1[l].capDisp + item[i].peso;
			//cout << mochila1[l].capDisp << "  " << endl;
			//cout << mochila1[x].lucro << "  ---   " << mochila1[x].lucro - item[i].lucro << endl;
			mochila1[l].lucro = mochila1[l].lucro - item[i].lucro;

		}

	}
}

void Shaking2(vector<Mochila>& mochila1, vector<Item>& item)
{
	int x = rand() % 6 + 1;
	int r = rand() % 6 + 1;
	//cout << x << endl;
	//cout << r << endl;
	for (int i = 0; i <= item.size() - 1; i++)
	{
		int l = item[i].mochila;
		//cout << item[i].mochila << endl;
		if (item[i].categ == x && item[i].mochila != -1 && item[i].categ != 1)
		{
			//cout << x << "  " << item[i].categ << endl;
			mochila1[l].categ[item[i].categ - 1] = 0;
			// cout << item[i].mochila << "  --   " << mochila1[j].id << "     " << item[i].id << endl;
			item[i].mochila = -1;
			//cout << item[i].mochila << "  --   " << mochila1[j].id << endl;

			//coloca o item na mochila
			mochila1[l].capDisp = mochila1[l].capDisp + item[i].peso;
			//cout << mochila1[l].capDisp << "  " << endl;
			//cout << mochila1[x].lucro << "  ---   " << mochila1[x].lucro - item[i].lucro << endl;
			mochila1[l].lucro = mochila1[l].lucro - item[i].lucro;

		}
		if (item[i].categ == r && item[i].mochila != -1 && item[i].categ != 1)
		{
			//cout << x << "  " << item[i].categ << endl;
			mochila1[l].categ[item[i].categ - 1] = 0;
			// cout << item[i].mochila << "  --   " << mochila1[j].id << "     " << item[i].id << endl;
			item[i].mochila = -1;
			//cout << item[i].mochila << "  --   " << mochila1[j].id << endl;

			//coloca o item na mochila
			mochila1[l].capDisp = mochila1[l].capDisp + item[i].peso;
			//cout << mochila1[l].capDisp << "  " << endl;
			//cout << mochila1[x].lucro << "  ---   " << mochila1[x].lucro - item[i].lucro << endl;
			mochila1[l].lucro = mochila1[l].lucro - item[i].lucro;

		}
	}
}

void Shaking3(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{
	for (int i = 0; i < mochila / 4; i++)
	{
		int idMochila = rand() % mochila;
		//cout << idMochila << endl;
		zeraMochila(mochila1, item, capacidade, idMochila);
	}
}

void Shaking4(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{
	for (int i = 0; i < mochila / 2; i++)
	{
		int idMochila = rand() % mochila;
		//cout << idMochila << endl;
		zeraMochila(mochila1, item, capacidade, idMochila);
	}
}

void Shaking5(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{
	for (int i = 0; i < mochila / 1.333; i++)
	{
		int idMochila = rand() % mochila;
		//cout << idMochila << endl;
		zeraMochila(mochila1, item, capacidade, idMochila);
	}
}


void tiraItens(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{
	

	
	double MelhorLucro = LucroTotal(mochila1);
	double destira = 0.5;
	double destira1 = 0;
	
	///*
	for (int i = 0; i <= 15; i++)
	{
		//cout << " 7" << endl;
		for (int i = 0; i < item.size() - 1; i++)
		{
			if (item[i].lucropeso < destira && item[i].compulsorio != 1)
			{
				item[i].mochila = -2;
			}

		}
		//cout << " 8" << endl;

		

		BestFit(mochila1, item, MatrizCompatibilidade);
		//cout << " 9" << endl;
		LocalSearch1(mochila1, item);
		//cout << " 10" << endl;
		//cout <<  LucroTotal(mochila1) << endl<< destira << endl;
		
		//cout << " 1" << endl;
		MoveComp(mochila1, item, capacidade);

		if (LucroTotal(mochila1) > MelhorLucro)
		{
			//cout << " 2" << endl;
			GuardarSol(mochila1, item);
			//cout << " melhor solucao " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			destira1 = destira;
		}

		destira = destira + 0.1;
		//cout << " 3" << endl;

		
		zeraProblema(mochila1, item, capacidade);


			
	}//*/

	 ///*
	 //apagar itens ruins
	for (int i = 0; i < item.size() - 1; i++)
	{
		if (item[i].lucropeso < destira1 && item[i].compulsorio != 1)
		{
			item[i].mochila = -2;
		}

	}
	/*
	int y = 0;

	for (int j = 0; j < 30; j++) {
		y = 0;
		for (int i = 0; i < item.size() - 1; i++)
		{

			if (item[i].mochila == -2)
			{
				item.erase(item.begin() + y);
				//y++;
				//i++;
			}
			y++;

		}
	}//*/
	
	/*
	for (int i = 0; i < 100; i++)
	{
		ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
		//int TipoShak = rand() % 2 + 2;
		int TipoShak = 3;
		//cout << TipoShak;
		if (TipoShak == 1) {
			Shaking1(mochila1, item);
		}
		if (TipoShak == 2) {
			Shaking2(mochila1, item);
		}
		if (TipoShak == 3) {
			Shaking3(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 4) {
			Shaking4(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 5) {
			Shaking5(mochila1, item, capacidade, mochila);
		}
		BestFit(mochila1, item, MatrizCompatibilidade);

		if (LucroTotal(mochila1) > MelhorLucro * 0.998)
		{
			//cout << "  " << LucroTotal(mochila1) << " >  " << MelhorLucro * 0.998 << endl;
			LocalSearch(mochila1, item);
		}


		MoveComp(mochila1, item, capacidade);
		if (LucroTotal(mochila1) > MelhorLucro)
		{
			GuardarSol(mochila1, item);
			//cout << "  " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			
		}

		
	}//*/




}

void vns1(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{



	double MelhorLucro = LucroTotal(mochila1);
	double destira = 0.5;
	double destira1 = 0;

	///*
	for (int i = 0; i <= 2; i++)
	{
		//cout << " 7" << endl;
		for (int i = 0; i < item.size() - 1; i++)
		{
			if (item[i].lucropeso < destira && item[i].compulsorio != 1)
			{
				item[i].mochila = -2;
			}

		}
		//cout << " 8" << endl;



		BestFit(mochila1, item, MatrizCompatibilidade);
		//cout << " 9" << endl;
		LocalSearch1(mochila1, item);
		//cout << " 10" << endl;
		//cout <<  LucroTotal(mochila1) << endl<< destira << endl;

		//cout << " 1" << endl;
		MoveComp(mochila1, item, capacidade);

		if (LucroTotal(mochila1) > MelhorLucro)
		{
			//cout << " 2" << endl;
			GuardarSol(mochila1, item);
			//cout << " melhor solucao " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			destira1 = destira;
		}

		destira = destira + 0.5;
		//cout << " 3" << endl;


		zeraProblema(mochila1, item, capacidade);



	}//*/
	ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
	 ///*
	 //apagar itens ruins
	for (int i = 0; i < item.size() - 1; i++)
	{
		if (item[i].lucropeso < destira1 && item[i].compulsorio != 1)
		{
			item[i].mochila = -2;
		}

	}
	///*
	int y = 0;

	for (int j = 0; j < 20; j++) {
	y = 0;
	for (int i = 0; i < item.size() - 1; i++)
	{

	if (item[i].mochila == -2)
	{
	item.erase(item.begin() + y);
	//y++;
	//i++;
	}
	y++;

	}
	}//*/

	GuardarSol(mochila1, item);




	///*
	
	int contador = 0;
	///*
	for (int i = 0; i < 30; i++)
	{
		ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
		int TipoShak = rand() % 3 + 2;
		//int TipoShak = 3;
		//cout << TipoShak;
		if (TipoShak == 1) {
			Shaking1(mochila1, item);
		}
		if (TipoShak == 2) {
			Shaking2(mochila1, item);
		}
		if (TipoShak == 3) {
			Shaking3(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 4) {
			Shaking4(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 5) {
			Shaking5(mochila1, item, capacidade, mochila);
		}

		//BestFit(mochila1, item, MatrizCompatibilidade);
		BestFitcomp(mochila1, item, MatrizCompatibilidade);
		MoveComp(mochila1, item, capacidade);

		//if (LucroTotal(mochila1) > MelhorLucro * 0.95)
		//{
		//cout << "  " << LucroTotal(mochila1) << " >  " << MelhorLucro * 0.85 << endl;
		LocalSearch1(mochila1, item);
		//}



		if (LucroTotal(mochila1) > MelhorLucro)
		{
			GuardarSol(mochila1, item);
			//cout << "  " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			contador = 0;

		}
		else
		{
			contador++;
			//cout << "  " << contador << "  " << MelhorLucro << "  " << LucroTotal(mochila1) << endl;
			if (contador == 15)
				break;
		}//*/

	}


}


void vns2(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{



	double MelhorLucro = LucroTotal(mochila1);
	double destira = 1;
	double destira1 = 0;

	///*
	for (int i = 0; i <= 4; i++)
	{
		//cout << " 7" << endl;
		for (int i = 0; i < item.size() - 1; i++)
		{
			if (item[i].lucropeso < destira && item[i].compulsorio != 1)
			{
				item[i].mochila = -2;
			}

		}
		//cout << " 8" << endl;



		BestFit(mochila1, item, MatrizCompatibilidade);
		//cout << " 9" << endl;
		LocalSearch1(mochila1, item);
		//cout << " 10" << endl;
		cout <<  LucroTotal(mochila1) << endl<< destira << endl;

		//cout << " 1" << endl;
		MoveComp(mochila1, item, capacidade);

		if (LucroTotal(mochila1) > MelhorLucro)
		{
			//cout << " 2" << endl;
			GuardarSol(mochila1, item);
			//cout << " melhor solucao " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			destira1 = destira;
		}

		destira = destira + 0.2;
		//cout << " 3" << endl;


		zeraProblema(mochila1, item, capacidade);



	}//*/
	ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
	///*
	//apagar itens ruins
	for (int i = 0; i < item.size() - 1; i++)
	{
		if (item[i].lucropeso < destira1 && item[i].compulsorio != 1)
		{
			item[i].mochila = -2;
		}

	}
	///*
	int y = 0;

	for (int j = 0; j < 20; j++) {
		y = 0;
		for (int i = 0; i < item.size() - 1; i++)
		{

			if (item[i].mochila == -2)
			{
				item.erase(item.begin() + y);
				//y++;
				//i++;
			}
			y++;

		}
	}//*/

	GuardarSol(mochila1, item);




	int contador = 0;
	///*
	for (int i = 0; i < 1000; i++)
	{
		ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
		int TipoShak = rand() % 3 + 2;
		//int TipoShak = 3;
		//cout << TipoShak;
		if (TipoShak == 1) {
			Shaking1(mochila1, item);
		}
		if (TipoShak == 2) {
			Shaking2(mochila1, item);
		}
		if (TipoShak == 3) {
			Shaking3(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 4) {
			Shaking4(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 5) {
			Shaking5(mochila1, item, capacidade, mochila);
		}

		BestFit(mochila1, item, MatrizCompatibilidade);
		//BestFitcomp(mochila1, item, MatrizCompatibilidade);
		MoveComp(mochila1, item, capacidade);

		if (LucroTotal(mochila1) > MelhorLucro * 0.995)
		{
			cout << "  " << LucroTotal(mochila1) << " >  " << MelhorLucro * 0.995 << endl;
			LocalSearch2(mochila1, item);
		}



		if (LucroTotal(mochila1) > MelhorLucro)
		{
			GuardarSol(mochila1, item);
			cout << "  " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			contador = 0;

		}
		else
		{
			contador++;
			//cout << "  " << contador << "  " << MelhorLucro << "  " << LucroTotal(mochila1) << endl;
			if (contador == 500)
				break;
		}


	}//*/

	cout << "Next" << endl;


}


void VNS(vector<Mochila>& mochila1, vector<Item>& item, int capacidade, int mochila)
{
	//iniciando o VNS
	

	//printItens(item);
	//printMochilasCom(mochila1);
	//double MelhorLucro = LucroTotal(mochila1);
	double MelhorLucro = LucroTotal(mochila1);
	int contador = 0;
	///*
	for (int i = 0; i < 1000; i++)
	{
		ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
		int TipoShak = rand() % 4 + 2;
		//int TipoShak = 3;
		cout << TipoShak;
		if (TipoShak == 1) {
			Shaking1(mochila1, item);
		}
		if (TipoShak == 2) {
			Shaking2(mochila1, item);
		}
		if (TipoShak == 3) {
			Shaking3(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 4) {
			Shaking4(mochila1, item, capacidade, mochila);
		}
		if (TipoShak == 5) {
			Shaking5(mochila1, item, capacidade, mochila);
		}

		BestFit(mochila1, item, MatrizCompatibilidade);
		//BestFitcomp(mochila1, item, MatrizCompatibilidade);
		MoveComp(mochila1, item, capacidade);

		//if (LucroTotal(mochila1) > MelhorLucro * 0.95)
		//{
		//cout << "  " << LucroTotal(mochila1) << " >  " << MelhorLucro * 0.95 << endl;
		LocalSearch1(mochila1, item);
		//}



		if (LucroTotal(mochila1) > MelhorLucro)
		{
			GuardarSol(mochila1, item);
			cout << "  " << LucroTotal(mochila1) << "  " << MelhorLucro << endl;
			MelhorLucro = LucroTotal(mochila1);
			contador = 0;

		}
		else
		{
			contador++;
			//cout << "  " << contador << "  " << MelhorLucro << "  " << LucroTotal(mochila1) << endl;
			if (contador == 200)
				break;
		}


	}//*/

	cout << "Next" << endl;
}

void BestFitBest(vector<Mochila>& mochila1, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade)
{
	BestFit(mochila1, item, MatrizCompatibilidade);
	LocalSearch(mochila1, item);
}


/*
void Otimizar(vector<Mochila>& mochila, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade) {

	//Declaração do ambiente
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);


	//Declaração das Variáveis 
	vector<vector<GRBVar>> x(item.size(), vector<GRBVar>(mochila.size()));
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			x[i][j] = model.addVar(0.0, 1.0, 0, GRB_BINARY, "x(" + to_string(i) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	vector<vector<GRBVar>> y(MatrizCompatibilidade.size(), vector<GRBVar>(mochila.size()));
	for (int c = 0; c < MatrizCompatibilidade.size(); c++) {
		for (int j = 0; j < mochila.size(); j++) {
			y[c][j] = model.addVar(0.0, 1.0, 0, GRB_BINARY, "y(" + to_string(c) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	//Declaração da Função Objetivo
	GRBLinExpr sum_profit = 0;
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			sum_profit = sum_profit + x[i][j] * item[i].lucro;
		}
	}
	model.setObjective(sum_profit, GRB_MAXIMIZE);
	model.update();

	//Declaração das Restrições

	//Restrição de Compulsoriedade e Unicidade
	for (int i = 0; i < item.size(); i++) {
		GRBLinExpr aux = 0;
		if (item[i].compulsorio == 1) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux == 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
		if (item[i].compulsorio == 0) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux <= 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
	}
	model.update();

	//Restrição de capacidade de cada mochilas
	for (int j = 0; j < mochila.size(); j++) {
		GRBLinExpr aux = 0;
		for (int i = 0; i < item.size(); i++) {
			aux = aux + x[i][j] * item[i].peso;
		}
		model.addConstr(aux <= mochila[j].cap, "Restricao_Capacidade_Mochila_" + to_string(j));
	}
	model.update();

	//Restrição de Ligação para as variáveis de categoria
	for (int j = 0; j < mochila.size(); j++) {
		for (int c = 0; c < CATEGORIAS; c++) {
			GRBLinExpr aux = 0;
			for (int i = 0; i < item.size(); i++) {
				if (item[i].categ == c + 1) {
					aux = aux + x[i][j];
				}
			}
			aux = aux - 20 * y[c][j];
			model.addConstr(aux <= 0, "Restricao_Ligação_Categoria_" + to_string(c) + "_Mochila_" + to_string(j));
		}
	}
	model.update();

	//Restrição de Categoria
	GRBLinExpr aux = 0;
	for (int j = 0; j < mochila.size(); j++) {
		for (int c1 = 0; c1 < CATEGORIAS; c1++) {
			for (int c2 = 0; c2 < CATEGORIAS; c2++) {
				if (MatrizCompatibilidade[c1][c2] == 0) {
					aux = y[c1][j] + y[c2][j];
					model.addConstr(aux <= 1, "Restricao_Categorias_" + to_string(c1) + "-" + to_string(c2) + "_Mochila_" + to_string(j));
				}
			}
		}
	}
	model.update();

	model.write("teste.lp");


	model.getEnv().set(GRB_DoubleParam_TimeLimit, 60);
	model.getEnv().set(GRB_DoubleParam_MIPGap, 0.01);
	model.optimize();

	cout << endl;
	cout << "ObjBound ObjVal" << endl;
	cout << model.get(GRB_DoubleAttr_ObjBound) << " ";
	cout << model.get(GRB_DoubleAttr_ObjVal) << endl;
	cout << endl;
	///*
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			cout << "X_" << i << "-" << j << " = " << x[i][j].get(GRB_DoubleAttr_X) << endl;
		}
	}

	for (int c = 0; c < CATEGORIAS; c++) {
		for (int j = 0; j < mochila.size(); j++) {
			cout << "y_" << c << "-" << j << " = " << y[c][j].get(GRB_DoubleAttr_X) << endl;
		}
	}

}

void Otimizar2(vector<Mochila>& mochila, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade) {
	//Declaração do ambiente
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);


	//Declaração das Variáveis 
	vector<vector<GRBVar>> x(item.size(), vector<GRBVar>(mochila.size()));
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			x[i][j] = model.addVar(0.0, 1.0, 0, GRB_CONTINUOUS, "x(" + to_string(i) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	vector<vector<GRBVar>> y(MatrizCompatibilidade.size(), vector<GRBVar>(mochila.size()));
	for (int c = 0; c < MatrizCompatibilidade.size(); c++) {
		for (int j = 0; j < mochila.size(); j++) {
			y[c][j] = model.addVar(0.0, 1.0, 0, GRB_CONTINUOUS, "y(" + to_string(c) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	//Declaração da Função Objetivo
	GRBLinExpr sum_profit = 0;
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			sum_profit = sum_profit + x[i][j] * item[i].lucro;
		}
	}
	model.setObjective(sum_profit, GRB_MAXIMIZE);
	model.update();

	//Declaração das Restrições

	//Restrição de Compulsoriedade e Unicidade
	for (int i = 0; i < item.size(); i++) {
		GRBLinExpr aux = 0;
		if (item[i].compulsorio == 1) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux == 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
		if (item[i].compulsorio == 0) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux <= 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
	}
	model.update();

	//Restrição de capacidade de cada mochilas
	for (int j = 0; j < mochila.size(); j++) {
		GRBLinExpr aux = 0;
		for (int i = 0; i < item.size(); i++) {
			aux = aux + x[i][j] * item[i].peso;
		}
		model.addConstr(aux <= mochila[j].cap, "Restricao_Capacidade_Mochila_" + to_string(j));
	}
	model.update();

	//Restrição de Ligação para as variáveis de categoria
	for (int j = 0; j < mochila.size(); j++) {
		for (int c = 0; c < CATEGORIAS; c++) {
			GRBLinExpr aux = 0;
			for (int i = 0; i < item.size(); i++) {
				if (item[i].categ == c + 1) {
					aux = aux + x[i][j];
				}
			}
			aux = aux - 20 * y[c][j];
			model.addConstr(aux <= 0, "Restricao_Ligação_Categoria_" + to_string(c) + "_Mochila_" + to_string(j));
		}
	}
	model.update();

	//Restrição de Categoria
	GRBLinExpr aux = 0;
	for (int j = 0; j < mochila.size(); j++) {
		for (int c1 = 0; c1 < CATEGORIAS; c1++) {
			for (int c2 = 0; c2 < CATEGORIAS; c2++) {
				if (MatrizCompatibilidade[c1][c2] == 0) {
					aux = y[c1][j] + y[c2][j];
					model.addConstr(aux <= 1, "Restricao_Categorias_" + to_string(c1) + "-" + to_string(c2) + "_Mochila_" + to_string(j));
				}
			}
		}
	}
	model.update();

	model.write("teste.lp");


	model.getEnv().set(GRB_DoubleParam_TimeLimit, 60);
	model.getEnv().set(GRB_DoubleParam_MIPGap, 0.01);
	model.optimize();

	//cout << endl;
	//cout << "ObjBound ObjVal" << endl;
	//cout << model.get(GRB_DoubleAttr_ObjBound) << " ";
	//cout << model.get(GRB_DoubleAttr_ObjVal) << endl;
	//cout << endl;
	///*
	for (int i = 0; i < item.size(); i++) {
		double sum = 0;
		for (int j = 0; j < mochila.size(); j++) {
			//cout << "X_" << i << "-" << j << " = " << x[i][j].get(GRB_DoubleAttr_X) << endl;
			double y = x[i][j].get(GRB_DoubleAttr_X);
			sum = sum + y;
			
		}
		//cout << sum << endl;
		if (sum == 0)
		{
			itensRuins.push_back(0);
		}
		if (sum != 0)
		{
			itensRuins.push_back(1);
		}

	}
	/*
	for (int c = 0; c < CATEGORIAS; c++) {
		for (int j = 0; j < mochila.size(); j++) {
			cout << "y_" << c << "-" << j << " = " << y[c][j].get(GRB_DoubleAttr_X) << endl;
		}
	}


}

void Otimizar3(vector<Mochila>& mochila, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade) {
	//Declaração do ambiente
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);


	//Declaração das Variáveis 
	vector<vector<GRBVar>> x(item.size(), vector<GRBVar>(mochila.size()));
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			x[i][j] = model.addVar(0.0, 1.0, 0, GRB_BINARY, "x(" + to_string(i) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	vector<vector<GRBVar>> y(MatrizCompatibilidade.size(), vector<GRBVar>(mochila.size()));
	for (int c = 0; c < MatrizCompatibilidade.size(); c++) {
		for (int j = 0; j < mochila.size(); j++) {
			y[c][j] = model.addVar(0.0, 1.0, 0, GRB_BINARY, "y(" + to_string(c) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	//Declaração da Função Objetivo
	GRBLinExpr sum_profit = 0;
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			sum_profit = sum_profit + x[i][j] * item[i].lucro;
		}
	}
	model.setObjective(sum_profit, GRB_MAXIMIZE);
	model.update();

	//Declaração das Restrições

	//Restrição de Compulsoriedade e Unicidade
	for (int i = 0; i < item.size(); i++) {
		GRBLinExpr aux = 0;
		if (item[i].compulsorio == 1) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux == 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
		if (item[i].compulsorio == 0) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux <= 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
	}
	model.update();

	//Restrição de capacidade de cada mochilas
	for (int j = 0; j < mochila.size(); j++) {
		GRBLinExpr aux = 0;
		for (int i = 0; i < item.size(); i++) {
			aux = aux + x[i][j] * item[i].peso;
		}
		model.addConstr(aux <= mochila[j].cap, "Restricao_Capacidade_Mochila_" + to_string(j));
	}
	model.update();

	//Restrição de Ligação para as variáveis de categoria
	for (int j = 0; j < mochila.size(); j++) {
		for (int c = 0; c < CATEGORIAS; c++) {
			GRBLinExpr aux = 0;
			for (int i = 0; i < item.size(); i++) {
				if (item[i].categ == c + 1) {
					aux = aux + x[i][j];
				}
			}
			aux = aux - 20 * y[c][j];
			model.addConstr(aux <= 0, "Restricao_Ligação_Categoria_" + to_string(c) + "_Mochila_" + to_string(j));
		}
	}
	model.update();

	//Restrição de Categoria
	GRBLinExpr aux = 0;
	for (int j = 0; j < mochila.size(); j++) {
		for (int c1 = 0; c1 < CATEGORIAS; c1++) {
			for (int c2 = 0; c2 < CATEGORIAS; c2++) {
				if (MatrizCompatibilidade[c1][c2] == 0) {
					aux = y[c1][j] + y[c2][j];
					model.addConstr(aux <= 1, "Restricao_Categorias_" + to_string(c1) + "-" + to_string(c2) + "_Mochila_" + to_string(j));
				}
			}
		}
	}
	model.update();

	model.write("teste.lp");


	model.getEnv().set(GRB_DoubleParam_TimeLimit, 5);
	//model.getEnv().set(GRB_DoubleParam_MIPGap, 0.01);
	model.optimize();

	//cout << endl;
	//cout << "ObjBound ObjVal" << endl;
	//cout << model.get(GRB_DoubleAttr_ObjBound) << " ";
	//cout << model.get(GRB_DoubleAttr_ObjVal) << endl;
	//cout << endl;
	///*
	for (int i = 0; i < item.size(); i++) {
		double sum = 0;
		for (int j = 0; j < mochila.size(); j++) {
			//cout << "X_" << i << "-" << j << " = " << x[i][j].get(GRB_DoubleAttr_X) << endl;
			double y = x[i][j].get(GRB_DoubleAttr_X);
			sum = sum + y;

		}
		//cout << sum << endl;
		if (sum == 0)
		{
			itensRuins.push_back(0);
		}
		if (sum != 0)
		{
			itensRuins.push_back(1);
		}

	}
	/*
	for (int c = 0; c < CATEGORIAS; c++) {
	for (int j = 0; j < mochila.size(); j++) {
	cout << "y_" << c << "-" << j << " = " << y[c][j].get(GRB_DoubleAttr_X) << endl;
	}
	}


}

void Otimizar4(vector<Mochila>& mochila, vector<Item>& item, vector<vector<int>> MatrizCompatibilidade) {
	//Declaração do ambiente
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);


	//Declaração das Variáveis 
	vector<vector<GRBVar>> x(item.size(), vector<GRBVar>(mochila.size()));
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			x[i][j] = model.addVar(0.0, 1.0, 0, GRB_CONTINUOUS, "x(" + to_string(i) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	vector<vector<GRBVar>> y(MatrizCompatibilidade.size(), vector<GRBVar>(mochila.size()));
	for (int c = 0; c < MatrizCompatibilidade.size(); c++) {
		for (int j = 0; j < mochila.size(); j++) {
			y[c][j] = model.addVar(0.0, 1.0, 0, GRB_CONTINUOUS, "y(" + to_string(c) + ")_(" + to_string(j) + ")");
		}
	}
	model.update();

	//Declaração da Função Objetivo
	GRBLinExpr sum_profit = 0;
	for (int i = 0; i < item.size(); i++) {
		for (int j = 0; j < mochila.size(); j++) {
			sum_profit = sum_profit + x[i][j] * item[i].lucro;
		}
	}
	model.setObjective(sum_profit, GRB_MAXIMIZE);
	model.update();

	//Declaração das Restrições

	//Restrição de Compulsoriedade e Unicidade
	for (int i = 0; i < item.size(); i++) {
		GRBLinExpr aux = 0;
		if (item[i].compulsorio == 1) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux == 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
		if (item[i].compulsorio == 0) {
			for (int j = 0; j < mochila.size(); j++) {
				aux = aux + x[i][j];
			}
			model.addConstr(aux <= 1, "Restricao_Compulsoriedade_Item_" + to_string(i));
		}
	}
	model.update();

	//Restrição de capacidade de cada mochilas
	for (int j = 0; j < mochila.size(); j++) {
		GRBLinExpr aux = 0;
		for (int i = 0; i < item.size(); i++) {
			aux = aux + x[i][j] * item[i].peso;
		}
		model.addConstr(aux <= mochila[j].cap*1.2, "Restricao_Capacidade_Mochila_" + to_string(j));
	}
	model.update();

	//Restrição de Ligação para as variáveis de categoria
	for (int j = 0; j < mochila.size(); j++) {
		for (int c = 0; c < CATEGORIAS; c++) {
			GRBLinExpr aux = 0;
			for (int i = 0; i < item.size(); i++) {
				if (item[i].categ == c + 1) {
					aux = aux + x[i][j];
				}
			}
			aux = aux - 20 * y[c][j];
			model.addConstr(aux <= 0, "Restricao_Ligação_Categoria_" + to_string(c) + "_Mochila_" + to_string(j));
		}
	}
	model.update();

	//Restrição de Categoria
	GRBLinExpr aux = 0;
	for (int j = 0; j < mochila.size(); j++) {
		for (int c1 = 0; c1 < CATEGORIAS; c1++) {
			for (int c2 = 0; c2 < CATEGORIAS; c2++) {
				if (MatrizCompatibilidade[c1][c2] == 0) {
					aux = y[c1][j] + y[c2][j];
					model.addConstr(aux <= 1, "Restricao_Categorias_" + to_string(c1) + "-" + to_string(c2) + "_Mochila_" + to_string(j));
				}
			}
		}
	}
	model.update();

	model.write("teste.lp");


	model.getEnv().set(GRB_DoubleParam_TimeLimit, 60);
	model.getEnv().set(GRB_DoubleParam_MIPGap, 0.01);
	model.optimize();

	//cout << endl;
	//cout << "ObjBound ObjVal" << endl;
	//cout << model.get(GRB_DoubleAttr_ObjBound) << " ";
	//cout << model.get(GRB_DoubleAttr_ObjVal) << endl;
	//cout << endl;
	///*
	for (int i = 0; i < item.size(); i++) {
		double sum = 0;
		for (int j = 0; j < mochila.size(); j++) {
			//cout << "X_" << i << "-" << j << " = " << x[i][j].get(GRB_DoubleAttr_X) << endl;
			double y = x[i][j].get(GRB_DoubleAttr_X);
			sum = sum + y;

		}
		//cout << sum << endl;
		if (sum == 0)
		{
			itensRuins.push_back(0);
		}
		if (sum != 0)
		{
			itensRuins.push_back(1);
		}

	}
	/*
	for (int c = 0; c < CATEGORIAS; c++) {
	for (int j = 0; j < mochila.size(); j++) {
	cout << "y_" << c << "-" << j << " = " << y[c][j].get(GRB_DoubleAttr_X) << endl;
	}
	}


}*/


void tirarItensRuinsSemOtim(vector<Item>& item)
{
	
	//printvetorDoubl(itensRuins);

	//printItens(item);
	///*
	for (int i = 0; i < item.size() - 1; i++)
	{
		if (item[i].lucropeso < 1.7 && item[i].compulsorio != 1)
		{
			item[i].mochila = -2;
		}

	}
	//printItens(item);
	//system("pause");
	///*
	int y = 0;

	for (int j = 0; j < 30; j++) {
		y = 0;
		for (int i = 0; i < item.size() - 1; i++)
		{

			if (item[i].mochila == -2)
			{
				item.erase(item.begin() + y);
				//y++;
				//i++;
			}
			y++;
		}
	}
	//printItens(item);//*/
	//system("pause");

}


void limpaTudo(vector<Mochila>& mochila1, vector<Item>& item)
{
	mochila1.clear();
	item.clear();
	GuardarSolucao.clear();
	itensRuins.clear();
}



int main()
{
	srand(0);
	clock_t t_ini, t_fin;
	t_ini = clock();
	t_fin = 0;
	double segundos = 0;
	double segun2 = 0;

	ofstream resultado("C:/Users/Felipe.DESKTOP-SD9EH44/Desktop/Mestrado/Aulas/Aula/Heuristica/resultados2.txt");

	string localArquivo;
	int mochila;
	int capacidade;
	vector<Item> item;//vetor de itens
	
	//uma instancia
	/*
	localArquivo = "C:\\Users\\Felipe.DESKTOP-SD9EH44\\Desktop\\Programas\\Aula\\Heuristica\\Instancias MKPc\\Instancias\\402_75_4_40_NR_49.txt";
	

	Dados(localArquivo, mochila, capacidade, item);
	vector<Mochila> mochila1(mochila);
	contruirMochilas(mochila1, mochila, capacidade);
	printMochilasCom(mochila1);
	//Otimizar4(mochila1, item, MatrizCompatibilidade);
	//tirarItensRuins(item);
	//tirarItensRuinsSemOtim(item);

	//BestFitBest(mochila1, item, MatrizCompatibilidade);
	//BestFit(mochila1, item, MatrizCompatibilidade);
	//LocalSearch(mochila1, item);
	GuardarSol(mochila1, item);

	//VNS4(mochila1, item, capacidade, mochila);

	ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);
	
	
	cout << "Lucro " << LucroTotal(mochila1) << "." << endl;
	
	///*
	if(resultado.is_open()) {
		
		resultado << "Lucro " << (int)LucroTotal(mochila1) << "." << endl;
		resultado << localArquivo << endl;
	}
	//printItens(item);
	//printMochilasCom(mochila1);
	//
	
	txtResultGeral(mochila1, item, t_ini, t_fin, segundos);
	//txtResultLucro(mochila1, item, t_ini, t_fin, segundos);*/

	//Varias instancias
	///*
	string lgstr;

	ifstream local;
	local.open("C:/Users/Felipe.DESKTOP-SD9EH44/Desktop/Mestrado/Aulas/Aula/Heuristica/Instancias MKPc/200.txt");
	if (!local.is_open()) {
		cout << "Erro ao abrir o arquivo2" << endl;
		

	}
	while (local.good())
	{
		
		
		lgstr.clear();
		getline(local, lgstr);
		localArquivo = lgstr;

		Dados(localArquivo, mochila, capacidade, item);
		vector<Mochila> mochila1(mochila);
		
		contruirMochilas(mochila1, mochila, capacidade);

		
		//tirarItensRuinsSemOtim(item);
		//Otimizar4(mochila1, item, MatrizCompatibilidade);
		
		BestFit(mochila1, item, MatrizCompatibilidade);

		LocalSearch(mochila1, item);

		GuardarSol(mochila1, item);

		//tiraItens(mochila1, item, capacidade, mochila);
		VNS(mochila1, item, capacidade, mochila);
		//vns1(mochila1, item, capacidade, mochila);
		//vns2(mochila1, item, capacidade, mochila);

		ReestaurarMelhorSol(mochila1, item, capacidade, GuardarSolucao);

		if (resultado.is_open()) {
			t_fin = clock();
			
			segundos = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
			resultado << LucroTotal(mochila1) << "     " << segundos - segun2 << endl;
			//resultado << "Lucro " << LucroTotal(mochila1) << "." << endl;
			//resultado << localArquivo << endl;
			segun2 = segundos;

		}

		printItens(item);
		printMochilasCom(mochila1);


		//txtResultGeral(mochila1, item, t_ini, t_fin, segundos);
		//txtResultLucro(mochila1, item, t_ini, t_fin, segundos);
		limpaTudo(mochila1, item);

		
	}
	

	
	if (resultado.is_open()) {
		t_fin = clock();
		segundos = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
		// resultado << "Tempo de processamento: " << segundos << " segundos." << endl;
		resultado << segundos << endl;
		resultado.close();
	}
	else {
		return -1;
	}//*/

	system("pause");
	return 0;
}


