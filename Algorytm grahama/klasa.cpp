//#include "stdafx.h"
#include "klasa.h"

graham::graham()
{
	duze = 0;
	male = 0;
}
graham::~graham()
{
	delete [] duze;
	delete [] male;
}
void graham::wczytaj()
{
	//ifstream plik("in.txt");
	//if (!plik) cout << "Brak pliku w katalogu z programem. Sproboj ponownie\n";
	int x;
	while (cin >> x) dane.push_back(x);

	//plik.close();

}
void graham::konwersja()
{
	string c;
	int b,b1;
	int g;
	if (n == NULL)
	{
		n = dane[0];
		//cout << n << endl;
	}
	if (n1 == NULL)
	{
		g = (n * 2)+1;
		n1 = dane[g];
		//cout << n1 << endl;
	}

	duze = new punktD[n];
	male = new punktM[n1];

	int c1 = 0 , c2 = 0, v = 0, v1 = 0;

	for (int i = 1; i < dane.size(); i++)
	{
		if (i <= (2 * n))
		{
			if (i % 2 == 0) //jesli parzyste to y
			{
				duze[c1].y = dane[i];
				c1++;
			}
			else //jesli nieparzyste to x
			{
				duze[c2].x = dane[i];
				c2++;
			}
		}
		if (i > (2 * n)+1)
		{
			if (i % 2 == 0) //jesli parzyste to x
			{
				male[v].x = dane[i];
				v++;
			}
			else //jesli nieparzyste to y
			{
				male[v1].y = dane[i];
				v1++;
			}
		}
	}

}

void graham::uporzadkuj()
{
	int min = 0;
	min = duze[0].y;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	for (int i = 1; i < n; i++)
	{
		if (min > duze[i].y)
		{
			min = duze[i].y;
			indeks = i;
		}
		if (min == duze[i].y)
		{
			if (duze[indeks].x > duze[i].x)
			{
				indeks = i;
			}
		}
	}
	x2 = duze[indeks].x;
	y2 = duze[indeks].y;
	for (int j = 0; j < n; j++)
	{
		x1 = duze[j].x;
		y1 = duze[j].y;
		duze[j].x = x1 - x2;
		duze[j].y = y1 - y2;
		//cout << duze[j].x << " " << duze[j].y << endl;
	}
	for (int b = 0; b < n1; b++)
	{
		x1 = male[b].x;
		y1 = male[b].y;
		male[b].x = x1 - x2;
		male[b].y = y1 - y2;
		
	}
}

void graham::sortuj()
{
	double d = 0; 
	int x1 = 0, y1 = 0;
	int tmp = 0, tmp1 = 0;
	double tmp2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == indeks)
		{
			duze[i].k = 0;
		}
		else
		{
			x1 = duze[i].x;
			y1 = duze[i].y;
			d = abs(x1) + abs(y1);
			duze[i].k = alfa(d, x1, y1);
		}
	}

	for (int h = 0; h < n; h++)
	{
		for (int l = 0; l < n - 1; l++)
		{
			if (duze[l].k > duze[l + 1].k)
			{
				swap(duze[l].x, duze[l + 1].x);
				swap(duze[l].y, duze[l + 1].y);
				swap(duze[l].k, duze[l + 1].k);
			}
		}
	}

	/*for (int g = 0; g < n; g++)
	{
		cout << duze[g].x << " " << duze[g].y << " " << duze[g].k << endl;
	}*/
}

double graham::alfa(double d , int x, int y)
{
	double alfa = 0.0;
	
	if (x >= 0 && y >= 0)
	{
		alfa = y / d;
	}
	if (x < 0 && y >= 0)
	{
		alfa = 2 - (y / d);
	}
	if (x < 0 && y < 0)
	{
		alfa = 2 + (abs(y) / d);
	}
	if (x >= 0 && y < 0)
	{
		alfa = 4 - (abs(y) / d);
	}

	return alfa;
}

void graham::b_otoczka()
{
	
	int det1 = 0;
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	X.push(duze[0].x);
	Y.push(duze[0].y);

	X.push(duze[1].x);
	Y.push(duze[1].y);

	x1 = X.top();
	y1 = Y.top();

	X.push(duze[2].x);
	Y.push(duze[2].y);

	x2 = X.top();
	y2 = Y.top();
	
	for (int i = 3; i < n; i++)
	{
		//cout << "det(a,b,c) " << "a: x: " << x1 << " y: " << y1 << " b: x: " << x2 << " y: " << y2 << " c: x:" << duze[i].x << " y: " << duze[i].y << endl;
		det1 = (x1 * y2) + (x2 * duze[i].y) + (duze[i].x * y1) - (duze[i].x * y2) - (x1 * duze[i].y) - (x2 * y1);
		//cout << "wyznacznik: " << det1 << endl;
		if (det1 > 0)
		{
			x1 = x2;
			y1 = y2;
			
			X.push(duze[i].x);
			Y.push(duze[i].y);

			x2 = X.top();
			y2 = Y.top();
			//cout << "Punkty gdy det > 0: x: " << x1 << " y: " << y1 << " x: " << x2 << " y: " << y2 << endl;
			
		}
		if (det1 < 0)
		{
			X.pop();
			Y.pop();
			
			x2 = X.top();
			y2 = Y.top();

			X.pop();
			Y.pop();

			x1 = X.top();
			y1 = Y.top();

			X.push(x2);
			Y.push(y2);
			//cout << "Punkty gdy det < 0: x: " << x1 << " y: " << y1 << " x: " << x2 << " y: " << y2 << endl;
			if(i != 3) i--;

		}
	}
	//cout << endl;
	/*do
	{
		cout << X.top() << " " << Y.top()<<endl;
		X.pop();
		Y.pop();
	} while (!X.empty());
	*/
	
}

void graham::wys()
{
	int det1 = 0;
	int licznik = 0;
	
	int rx = X.size()+1;
	int ry = Y.size()+1;
	
	int * x = new int[rx];
	int * y = new int[ry];
	
	for (int z = 0; z < rx; z++)
	{
		if (z == rx - 1)
		{
			x[z] = x[0];
			y[z] = y[0];
		}
		else
		{
			x[z] = X.top();
			y[z] = Y.top();

			X.pop();
			Y.pop();
		}

	}

	for (int i = 0; i < n1; i++)
	{
		for (int j = 1; j < rx; j++)
		{
			//cout << "det(a,b,c) " << "a: x: " << x[j - 1] << " y: " << y[j - 1] << " b: x: " << x[j] << " y: " << y[j] << " c: x:" << male[i].x << " y: " << male[i].y << endl;
			det1 = (x[j - 1] * y[j]) + (x[j] * male[i].y) + (male[i].x * y[j - 1]) - (male[i].x * y[j]) - (x[j - 1] * male[i].y) - (x[j] * y[j - 1]);
			
			//cout <<"wyznacznik: "<< det1 << endl;
			if (det1 > 0)
			{
				male[i].zawarty = 0;
				break;
			}
			if (det1 < 0)
			{
				male[i].zawarty = 1;
				
			}
			if (det1 == 0)
			{
				male[i].zawarty = 1;
			}
		}
	}
	for (int h = 0; h < n1; h++)
	{
		if (male[h].zawarty == 1) licznik++;
	}
		delete[] x;
		delete[] y;
		cout <<"ilosc punktow w otoczce: "<< licznik << endl;
		
}

