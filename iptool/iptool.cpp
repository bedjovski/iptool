#include "./iptools/core.h"
#include <string.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <map>
#include<vector>
using namespace std;

#define N 500	//rows
#define M 500	//columns
#define SZ 4000 //number of cells
#define K 20 //radius of firing cells
#define MAXLEN 250000 //N*M
int IMAGES = 0;
string SAVELOC = "../output/test000.ppm";
int n;
long long mat[N][M]; // closest cell to point
bool cell[N][M];
bool colored[N][M];
int grid[N][M];
image src, tgt, tgtp;
void createIMG() {
	src.read("../input/baboon.ppm");
	//char *pch, *next_pch;
	src.resize(N, M);
	//cout << src.getNumberOfRows() << " " << src.getNumberOfColumns();
	for (int i = 0; i < N*M; i++) { //set picture white of size N*M

		int X = i / M, Y = i % M;
		cell[X][Y] = false;
		colored[X][Y] = false;
		src.setPixel(X, Y, 1, 255);
		src.setPixel(X, Y, 2, 255);
		src.setPixel(X, Y, 3, 255);
	}
	return;
}
void createIMG2() {
	src.read("../input/baboon.ppm");
	//char *pch, *next_pch;
	src.resize(N, M);
	//cout << src.getNumberOfRows() << " " << src.getNumberOfColumns();
	for (int i = 0; i < N*M; i++) { //set picture white of size N*M
		int X = i / M, Y = i % M;
		src.setPixel(X, Y, 1, 255);
		src.setPixel(X, Y, 2, 255);
		src.setPixel(X, Y, 3, 255);
	}
	return;
}
void saveIMGsrc() {
	SAVELOC[14] = (char)((IMAGES / 100) + '0');
	SAVELOC[15] = (char)(((IMAGES % 100) /10) + '0');
	SAVELOC[16] = (char)((IMAGES % 10) + '0');
	//cout << SAVELOC << endl;
	src.save(SAVELOC.c_str());
	IMAGES++;
	return ;
}
void saveIMGtar() {
	SAVELOC[14] = (char)((IMAGES / 100) + '0');
	SAVELOC[15] = (char)(((IMAGES % 100) / 10) + '0');
	SAVELOC[16] = (char)((IMAGES % 10) + '0');
	tgt.save(SAVELOC.c_str());
	IMAGES++;
	return;
}
void createCells() {
	srand(time(NULL));
	for (int i = 0; i < SZ; i++)
	{
		int X = rand() % N, Y = rand() % M;
		//cout << X << " " << Y << endl;
		if (cell[X][Y])
			i--;
		cell[X][Y] = true;
		// mark the cell on the image, each cell is a 5x5 pixel square on the image
		//top part of cell
		src.setPixel(max(X - 2, 0), Y, 1, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 1), 1, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 2), 1, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 1), 1, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 2), 1, 0);
		src.setPixel(max(X - 2, 0), Y, 2, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 1), 2, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 2), 2, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 1), 2, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 2), 2, 0);
		src.setPixel(max(X - 2, 0), Y, 3, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 1), 3, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 2), 3, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 1), 3, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 2), 3, 0);
		//cout << "TOP" << endl;
		//bottom
		src.setPixel(min(X + 2, N - 1), Y, 1, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 1), 1, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 2), 1, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 1), 1, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 2), 1, 0);
		src.setPixel(min(X + 2, N - 1), Y, 2, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 1), 2, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 2), 2, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 1), 2, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 2), 2, 0);
		src.setPixel(min(X + 2, N - 1), Y, 3, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 1), 3, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 2), 3, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 1), 3, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 2), 3, 0);
		//cout << "BOT" << endl;
		//left
		src.setPixel(X, max(0, Y - 2), 1, 0);
		src.setPixel(max(X - 1, 0), max(0, Y - 2), 1, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 2), 1, 0);
		src.setPixel(min(X + 1, N - 1), max(0, Y - 2), 1, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 2), 1, 0);
		src.setPixel(X, max(0, Y - 2), 2, 0);
		src.setPixel(max(X - 1, 0), max(0, Y - 2), 2, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 2), 2, 0);
		src.setPixel(min(X + 1, N - 1), max(0, Y - 2), 2, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 2), 2, 0);
		src.setPixel(X, max(0, Y - 2), 3, 0);
		src.setPixel(max(X - 1, 0), max(0, Y - 2), 3, 0);
		src.setPixel(max(X - 2, 0), max(0, Y - 2), 3, 0);
		src.setPixel(min(X + 1, N - 1), max(0, Y - 2), 3, 0);
		src.setPixel(min(X + 2, N - 1), max(0, Y - 2), 3, 0);
		//cout << "LEFT" << endl;
		//right
		src.setPixel(X, min(M - 1, Y + 2), 1, 0);
		src.setPixel(max(X - 1, 0), min(M - 1, Y + 2), 1, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 2), 1, 0);
		src.setPixel(min(X + 1, N - 1), min(M - 1, Y + 2), 1, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 2), 1, 0);
		src.setPixel(X, min(M - 1, Y + 2), 2, 0);
		src.setPixel(max(X - 1, 0), min(M - 1, Y + 2), 2, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 2), 2, 0);
		src.setPixel(min(X + 1, N - 1), min(M - 1, Y + 2), 2, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 2), 2, 0);
		src.setPixel(X, min(M - 1, Y + 2), 3, 0);
		src.setPixel(max(X - 1, 0), min(M - 1, Y + 2), 3, 0);
		src.setPixel(max(X - 2, 0), min(M - 1, Y + 2), 1, 0);
		src.setPixel(min(X + 1, N - 1), min(M - 1, Y + 2), 3, 0);
		src.setPixel(min(X + 2, N - 1), min(M - 1, Y + 2), 3, 0);
		//cout << "RIGHT" << endl;
	}
	return;
}
void nearestPoint()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			int steps = 0;
			while (1) {
				int left = j - steps, right = j + steps, down = i + steps, up = i - steps;
				if (left >= 0) {
					if (cell[left][j]) {
						mat[i][j] = left * M + j;
						break;
					}
				}
				if (left >= 0) { //left
					if (cell[i][left]) {
						mat[i][j] = i * M + left;
						break;
					}
				}
				if (right >= 0) {  //right
					if (cell[i][right]) {
						mat[i][j] = i * M + right;
						break;
					}
				}
				if (up >= 0) { // up
					if (cell[up][j]) {
						mat[i][j] = up * M + j;
						break;
					}
				}
				if (down < N) { //down
					if (cell[down][j]) {
						mat[i][j] = down * M + j;
						break;
					}
				}
				if (left >= 0) {
					if (cell[left][j]) {
						mat[i][j] = left * M + j;
						break;
					}
				}
				if (left >= 0) {
					if (cell[left][j]) {
						mat[i][j] = left * M + j;
						break;
					}
				}
				if (left >= 0) {
					if (cell[left][j]) {
						mat[i][j] = left * M + j;
						break;
					}
				}
				steps++;
			}
		}
	return;
}


void purp(int X, int Y) {
	//255,0, 255
		for (int i = X - 7; i <= X + 7; i++) {
			for (int j = Y - 7; j <= Y + 7; j++) {
				if (i >= 0 && i < N && j >= 0 && j < M)
				{
					tgt.setPixel(i, j, 1, 255);
					tgt.setPixel(i, j, 2, 0);
					tgt.setPixel(i, j, 3, 255);
				}
			}
	}
	return;
}
void clearPurp(int X, int Y)
{
	for(int i=X-20;i<=X+20; i++)
		for(int j = Y-20;j<=Y+20;j++)
			if (i >= 0 && i < N && j >= 0 && j < M)
			{
				int r = tgt.getPixel(i, j, 1), g = tgt.getPixel(i, j, 2), b = tgt.getPixel(i, j, 3);
				int r1 = src.getPixel(i, j, 1), g1 = src.getPixel(i, j, 2), b1 = src.getPixel(i, j, 3);
				if (r != 255 && g != 0 && b != 255)
					continue;
				tgt.setPixel(i, j, 1, r1);
				tgt.setPixel(i, j, 2, g1);
				tgt.setPixel(i, j, 3, b1);
			}
	return;
}
void red(int X, int Y) { // 255 0 0
	for (int i = X - K; i <= X + K; i++)
		for (int j = Y - K; j <= Y + K; j++)
			if (i >= 0 && i < N && j >= 0 && j < M)
				if(cell[i][j])
					for(int I=i-2;I<=i+2;I++)
						for (int J = j - 2; J <= j + 2; J++)
							if (I >= 0 && I < N && J >= 0 && J < M)
							{
								tgt.setPixel(I, J, 1, 255);
								tgt.setPixel(I, J, 2, 0);
								tgt.setPixel(I, J, 3, 0);
								colored[I][J] = true;
							}
	return;
}
void gray(int X, int Y) { // 105 105 105
	for (int i = X - K; i <= X + K; i++)
		for (int j = Y - K; j <= Y + K; j++)
			if (i >= 0 && i < N && j >= 0 && j < M)
				if (cell[i][j] && colored[i][j])
					for (int I = i - 2; I <= i + 2; I++)
						for (int J = j - 2; J <= j + 2; J++)
							if (I >= 0 && I < N && J >= 0 && J < M)
							{
								tgt.setPixel(I, J, 1, 105);
								tgt.setPixel(I, J, 2, 105);
								tgt.setPixel(I, J, 3, 105);
							}
	return;
}
void fire(int i, int j) {
	red(mat[i][j] / M, mat[i][j] % M);
	return;
}
void estinguish(int i, int j)
{
	gray(mat[i][j] / M, mat[i][j] % M);
	return;
}
void move(int X, int Y, int FX, int FY)
{
	int dx, dy;
	while (1)
	{
		dx = 0;
		dy = 0;
		if (X > FX)
			dx = -1;
		if (X < FX)
			dx = 1;
		if (Y > FY)
			dy = -1;
		if (Y < FY)
			dy = 1;
		fire(X, Y);
		estinguish(X, Y);
		if (dx == 0 && dy == 0)
			return;
		X+=dx;
		Y+=dy;
	}
	return;
}
void markit1(int cnt, int sz) {
	int cntdbg = 0,rt=1;

	for (int k = sz / 2; k < N; k += sz) {
		int loc = sz;
		while (loc < M)
		{
			grid[k][loc] = rt;
			for (int X = -(sz / 2); X <= sz / 2; X++)
				for (int Y = -(sz / 2); Y <= sz / 2; Y++)
					if(k+X>=0 && k+X<N && loc+Y>=0 && loc+Y<M)
						if(X*X+Y*Y<(sz/2)*(sz/2))
							grid[k + X][loc + Y] = grid[k][loc];
			loc += sz;
			rt++;
			if (rt > cnt) {
				loc += sz / 2;
				rt = 1;
			}
		}
	}
		

	/*
	for (int j = sz / 2; j < M;) {
			for (int i = 1; i*rt*sz < M; i++)
				for (int X = -(sz / 2); X <= sz / 2; X++)
					for (int Y = -(sz / 2); Y <= sz / 2; Y++)
						if (j + X >= 0 && j + X < N && i*k*sz + Y >= 0 && i*k*sz + Y < M)
							grid[j + X][i*rt*sz + Y] = k - 1;
	}*/
	/*for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			if (grid[i][j] == 1)
			{
				tgt.setPixel(i, j, 1, 0);
				tgt.setPixel(i, j, 2, 0);
				tgt.setPixel(i, j, 3, 255);
			}
			if (grid[i][j] == 2)
			{
				tgt.setPixel(i, j, 1, 255);
				tgt.setPixel(i, j, 2, 0);
				tgt.setPixel(i, j, 3, 0);
			}
			if (grid[i][j] == 3)
			{
				tgt.setPixel(i, j, 1, 0);
				tgt.setPixel(i, j, 2, 255);
				tgt.setPixel(i, j, 3, 0);
			}
		}*/
	//cout << cntdbg << endl;

	return;
}

int main()
{
	
	char str[MAXLEN];
	
	int controller = 0;
	cout << "For CANN entetr 1, For grid cell enter 2: ";
	cin >> controller;
	if (controller == 1) {
		// create image
		createIMG();
		tgt.copyImage(src);
		//create cells
		createCells();
		//nearest cell to point using bfs
		nearestPoint();
		saveIMGsrc();
		int X = -4, Y = -4, Xprev = -4, Yprev = -4;
		while (1) { // enter coords x,y, if entered -1 exit, -2 for clear, -3 for save result
			if (X >= 0) {
				Xprev = X;
				Yprev = Y;
			}
			cin >> X;
			if (X == -1)
			{
				break;
			}
			if (X == -2)
			{
				Xprev = -4;
				tgt.copyImage(src);
				for (int i = 0; i < N; i++)
					for (int j = 0; j < M; j++)
						colored[i][j] = false;
				continue;
			}
			cin >> Y;
			if (Xprev == -4)
			{
				fire(X, Y);
				purp(X, Y);
				saveIMGtar();
			}
			if (Xprev >= 0) {
				clearPurp(Xprev, Yprev);
				purp(X, Y);
				cout << Xprev << " " << Yprev << " " << X << " " << Y << endl;
				move(Xprev, Yprev, X, Y);
				fire(X, Y);
				saveIMGtar();

			}

		}
	}
	else {
		// create image
		createIMG2();
		tgt.copyImage(src);
		tgtp.copyImage(src);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) 
				grid[i][j] = 0;
		markit1(3,30);
		srand(time(NULL));
		int i = 250, j = 250;
		for (int k = 0; k < 10000000; k++)
		{
			if (i >= 0 && i < N && j >= 0 && j < M) {
				tgtp.setPixel(i, j, 1, 0);
				tgtp.setPixel(i, j, 2, 0);
				tgtp.setPixel(i, j, 3, 0);
				if (grid[i][j] == 1)
				{
					tgt.setPixel(i, j, 1, 0);
					tgt.setPixel(i, j, 2, 0);
					tgt.setPixel(i, j, 3, 255);
				}
				if (grid[i][j] == 2)
				{
					tgt.setPixel(i, j, 1, 255);
					tgt.setPixel(i, j, 2, 0);
					tgt.setPixel(i, j, 3, 0);
				}
				if (grid[i][j] == 3)
				{
					tgt.setPixel(i, j, 1, 0);
					tgt.setPixel(i, j, 2, 255);
					tgt.setPixel(i, j, 3, 0);
				}
			}
			int z = rand() % 4;
			if (z == 0)
				i--;
			if (z == 1)
				i++;
			if (z == 2)
				j--;
			if (z == 3)
				j++;
		}
		saveIMGtar();
		tgt.copyImage(tgtp);
		saveIMGtar();
	}
	
	//src.save(outfile);
	system("pause");
	return 0;
}