#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;
#define L 8//количество ребер
#define N 256//количество подграфов которые можно построить на данном графе
int Start = 2;//точка начала пути
int Finish = 5;//точка конца пути

int Edges[L][3] = { {1,34,43},{2,13,31},{3,42,24},{4,15,51},{5,16,61},{6,56,65},{7,52,25},{8,62,26} };
int main()
{
	setlocale(LC_ALL, "Russian");

	/*int** Edges = (int**)malloc(sizeof(int*)*L);
	for (int i=0;i<L;i++)
	{
		Edges[i] = (int*)malloc(sizeof(int)*3);
	}
		for (int i=0;i<L;i++)
		{
			//cout<<"Данные для ребра с номером "<<i<<endl;
			cout<<"Введите номер ребра--> ";
			cin>>Edges[i][0];
			cout<<"Введите название грани (например грань 1-2 должна быть записана как 12)--> ";
			cin>>Edges[i][1];
			cout<<"Введите название грани наоборот--> ";
			cin>>Edges[i][2];
		}*/

	double Pr = 0, Data[N][L + 2], p = 0;
	int Way[L], End = Finish, current = 0, buff = -1, x = 0, y = 0;
	int** Connection = (int**)malloc(sizeof(int*) * L);
	for (int i = 0; i < L; i++)
	{
		Connection[i] = (int*)malloc(sizeof(int) * L);
	}
	bool deadlock = false, repetition = false, flag = false;
	ofstream out;
	out.open("Results.txt");
	cout << "p" << "\t|\t" << "Pr(p)" << endl;
	cout << "---------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < L + 2; j++)
		{
			Data[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++)//формируем все возможные подграфы
	{
		int z = i;
		for (int j = L - 1; j >= 0; j--)
		{
			if (z > 1)
			{
				Data[i][j] = z % 2;
				z = floor(float(z) / 2);
			}
			else
			{
				Data[i][j] = z;
				break;
			}
		}
	}
	while (p <= 1)
	{
		for (int k = 0; k < N; k++)// проверяем все подгафы
		{
			for (int i = 0; i < L; i++)// Формирование матрицы связей между точками графа
			{
				for (int j = 0; j < L; j++)
				{
					if (i == j)
					{
						Connection[i][j] = 0;
					}
					else
					{
						flag = false;
						for (int x = 0; x < L; x++)
						{
							for (int y = 1; y <= 2; y++)
							{
								if (Edges[x][y] == ((i + 1) * 10 + (j + 1)) && Data[k][Edges[x][0] - 1] == 1)
								{
									Connection[i][j] = 1;
									flag = true;
									break;
								}
							}
							if (flag) break;
						}
						if (!flag) Connection[i][j] = 0;
					}
				}
			}
			for (int i = 0; i < L; i++)
				Way[i] = 0;
			Way[0] = Start;
			End = Finish;
			current = 0;
			deadlock = false;
			repetition = false;
			for (int j = 0; j < L; j++)
			{
				repetition = false;
				if (Connection[Way[current] - 1][End - 1] == 1)
				{
					Data[k][L] = 1;
					break;
				}
				if (Connection[Way[current] - 1][j] == 1)
				{
					for (int q = 0; q < current; q++)
					{
						if (Way[q] == j + 1)
						{
							repetition = true;
							break;
						}
					}
					if (repetition == false)
					{
						buff = j;
						Way[++current] = j + 1;
						j = 0;
						if (Way[current] == End)
						{
							Data[k][L] = 1;
							break;
						}
					}
				}
				if (j == (L - 1))
				{
					j = Way[current - 1] - 1;
					Way[current] = 0;
					if (Way[0] == 0)
					{
						Data[k][L] = 0;
						break;
					}
					current = current - 1;
					Connection[Way[current] - 1][buff] = 0;
				}
			}
			x = 0;
			y = 0;
			for (int i = 0; i < L; i++)
			{
				if (Data[k][i] == 1)
					x = x + 1;
				else
					y = y + 1;
			}
			Data[k][L + 1] = pow(p, x) * pow(1 - p, y);
			if (Data[k][L] == 1)
			{
				Pr += Data[k][L + 1];
			}
		}
		cout << p << "\t|\t" << Pr << endl;
		out << p << "\t\t" << Pr << endl;
		Pr = 0;
		p += 0.1;
	}
	cout << endl;
	out.close();
	system("pause");
}

ervbynhk