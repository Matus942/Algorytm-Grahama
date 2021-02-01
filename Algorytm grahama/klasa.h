#pragma once
#ifndef KLASA_H
#define KLASA_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stack>



using namespace std;

struct punktD
{
	int x;
	int y;
	double k;
};

struct punktM
{
	int x;
	int y;
	int zawarty;
};


class graham
{
private:
	int n = NULL;
	int n1 = NULL;
	int indeks = 0;

	vector<int>dane;
	stack<int>X;
	stack<int>Y;
	punktD * duze;
	punktM * male;
public:
	graham();
	~graham();
	void wczytaj();
	void konwersja();
	void uporzadkuj();
	void sortuj();
	double alfa(double, int, int);
	void b_otoczka();
	void wys();
};


#endif // !KLASA_H
