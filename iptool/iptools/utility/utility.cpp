#include "utility.h"
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<math.h>
#define MAXRGB 255
#define MINRGB 0
#define PI 3.14159265
using namespace std;
std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}


void utility::gamp(image &src, image &tgt, int ROI[3][6], int n)
{
	int N = 0, M = 0;
	N = src.getNumberOfRows();
	M = src.getNumberOfColumns();
	tgt.resize(N, M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			tgt.setPixel(i, j, src.getPixel(i, j));
	//int gx[500][500], gy[500][500], g[500][500], theta[500][500];
	for(int k=0;k<n;k++)
		for(int i=ROI[k][0];i<ROI[k][2];i++)
			for (int j = ROI[k][1]; j < ROI[k][3]; j++)
				if(i>0 && i<N-1 && j>0 && j<M-1)
				{
					int x = src.getPixel(i - 1, j + 1) + 2 * src.getPixel(i, j + 1) + src.getPixel(i + 1, j + 1);
					x-= (src.getPixel(i - 1, j - 1) + 2 * src.getPixel(i, j - 1) + src.getPixel(i + 1, j - 1));
					int y = src.getPixel(i + 1, j - 1) + 2 * src.getPixel(i + 1, j) + src.getPixel(i + 1, j + 1);
					y -= (src.getPixel(i - 1, j - 1) + 2 * src.getPixel(i - 1, j) + src.getPixel(i - 1, j + 1));
					int G = sqrt (x * x + y * y);
					tgt.setPixel(i, j, G);
				}

}
void utility::bamp(image &src, image &tgt, int ROI[3][6], int n)
{
	int N = 0, M = 0;
	N = src.getNumberOfRows();
	M = src.getNumberOfColumns();
	tgt.resize(N, M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			tgt.setPixel(i, j, src.getPixel(i, j));
	for (int k = 0; k<n; k++)
		for (int i = ROI[k][0]; i<ROI[k][2]; i++)
			for (int j = ROI[k][1]; j < ROI[k][3]; j++)
				if (i>0 && i<N - 1 && j>0 && j<M - 1)
				{
					int x = src.getPixel(i - 1, j + 1) + 2 * src.getPixel(i, j + 1) + src.getPixel(i + 1, j + 1);
					x -= (src.getPixel(i - 1, j - 1) + 2 * src.getPixel(i, j - 1) + src.getPixel(i + 1, j - 1));
					int y = src.getPixel(i + 1, j - 1) + 2 * src.getPixel(i + 1, j) + src.getPixel(i + 1, j + 1);
					y -= (src.getPixel(i - 1, j - 1) + 2 * src.getPixel(i - 1, j) + src.getPixel(i - 1, j + 1));
					int G = sqrt(x * x + y * y);
					if (G < ROI[k][4])
						tgt.setPixel(i, j, 0);
					else
						tgt.setPixel(i, j, 255);
				}

}
void utility::bang(image &src, image &tgt, int ROI[3][6], int n)
{
	int N = 0, M = 0;
	N = src.getNumberOfRows();
	M = src.getNumberOfColumns();
	tgt.resize(N, M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			tgt.setPixel(i, j, src.getPixel(i, j));
	for (int k = 0; k < n; k++)
		for (int i = ROI[k][0]; i < ROI[k][2]; i++)
			for (int j = ROI[k][1]; j < ROI[k][3]; j++)
				if (i > 0 && i < N - 1 && j>0 && j < M - 1)
				{
					int x = src.getPixel(i - 1, j + 1) + 2 * src.getPixel(i, j + 1) + src.getPixel(i + 1, j + 1);
					x -= (src.getPixel(i - 1, j - 1) + 2 * src.getPixel(i, j - 1) + src.getPixel(i + 1, j - 1));
					int y = src.getPixel(i + 1, j - 1) + 2 * src.getPixel(i + 1, j) + src.getPixel(i + 1, j + 1);
					y -= (src.getPixel(i - 1, j - 1) + 2 * src.getPixel(i - 1, j) + src.getPixel(i - 1, j + 1));
					int G = sqrt(x * x + y * y);
					double ang = 0, theta = 0;
					int thetaint = 0;
					if (y > 0) {
						ang = (double)y / (double)x;
						theta = atan(ang) * 180 / PI;
						thetaint = (int)theta;
					}
					if (thetaint == ROI[k][5])
						tgt.setPixel(i, j, G);
					else
						tgt.setPixel(i, j, 0);

				}

}
void utility::colgamp(image &src, image &tgt, int ROI[3][6], int n)
{
	int N = 0, M = 0;
	N = src.getNumberOfRows();
	M = src.getNumberOfColumns();
	tgt.resize(N, M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			tgt.setPixel(i, j, 1, src.getPixel(i, j, 1));
			tgt.setPixel(i, j, 2, src.getPixel(i, j, 2)); 
			tgt.setPixel(i, j, 3, src.getPixel(i, j, 3));

		}
	for (int k = 0; k<n; k++)
		for (int i = ROI[k][0]; i<ROI[k][2]; i++)
			for (int j = ROI[k][1]; j < ROI[k][3]; j++)
				if (i>0 && i<N - 1 && j>0 && j<M - 1)
				{
					int x1 = src.getPixel(i - 1, j + 1, 1) + 2 * src.getPixel(i, j + 1, 1) + src.getPixel(i + 1, j + 1, 1);
					x1 -= (src.getPixel(i - 1, j - 1, 1) + 2 * src.getPixel(i, j - 1, 1) + src.getPixel(i + 1, j - 1, 1));
					int y1 = src.getPixel(i + 1, j - 1, 1) + 2 * src.getPixel(i + 1, j, 1) + src.getPixel(i + 1, j + 1, 1);
					y1 -= (src.getPixel(i - 1, j - 1, 1) + 2 * src.getPixel(i - 1, j, 1) + src.getPixel(i - 1, j + 1, 1));

					int x2 = src.getPixel(i - 1, j + 1, 2) + 2 * src.getPixel(i, j + 1, 2) + src.getPixel(i + 1, j + 1, 2);
					x2 -= (src.getPixel(i - 1, j - 1, 2) + 2 * src.getPixel(i, j - 1, 2) + src.getPixel(i + 1, j - 1, 2));
					int y2 = src.getPixel(i + 1, j - 1, 2) + 2 * src.getPixel(i + 1, j, 2) + src.getPixel(i + 1, j + 1, 2);
					y2 -= (src.getPixel(i - 1, j - 1, 2) + 2 * src.getPixel(i - 1, j, 2) + src.getPixel(i - 1, j + 1, 2));

					int x3 = src.getPixel(i - 1, j + 1, 3) + 2 * src.getPixel(i, j + 1, 3) + src.getPixel(i + 1, j + 1, 3);
					x3 -= (src.getPixel(i - 1, j - 1, 3) + 2 * src.getPixel(i, j - 1, 3) + src.getPixel(i + 1, j - 1, 3));
					int y3 = src.getPixel(i + 1, j - 1, 3) + 2 * src.getPixel(i + 1, j, 3) + src.getPixel(i + 1, j + 1, 3);
					y3 -= (src.getPixel(i - 1, j - 1, 3) + 2 * src.getPixel(i - 1, j, 3) + src.getPixel(i - 1, j + 1, 3));

					int G1 = sqrt(x1 * x1 + y1 * y1), G2 = sqrt(x2 * x2 + y2 * y2), G3 = sqrt(x3 * x3 + y3 * y3);
					int G = (G1+G2+G3)/3;
					if (G < ROI[k][4])
						G = 0;
					else
						G = 255;
					tgt.setPixel(i, j, 1, G);
					tgt.setPixel(i, j, 2, G);
					tgt.setPixel(i, j, 3, G);
				}

}
void utility::HSIamp(image &src, image &tgt, int ROI[3][6], int n)
{
	int N = 0, M = 0;
	N = src.getNumberOfRows();
	M = src.getNumberOfColumns();
	tgt.resize(N, M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			tgt.setPixel(i, j, 1, src.getPixel(i, j, 1));
			tgt.setPixel(i, j, 2, src.getPixel(i, j, 2));
			tgt.setPixel(i, j, 3, src.getPixel(i, j, 3));
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			int R = src.getPixel(i, j, 1), G = src.getPixel(i, j, 2), B = src.getPixel(i, j, 3);
			int tmp = 0;
			if ((R + G + B) != 0)
				tmp = (R + G + B) / 3;
			src.setPixel(i, j, 3, tmp);
		}
	for (int k = 0; k<n; k++)
		for (int i = ROI[k][0]; i<ROI[k][2]; i++)
			for (int j = ROI[k][1]; j < ROI[k][3]; j++)
				if (i>0 && i<N - 1 && j>0 && j<M - 1)
				{
					int x = src.getPixel(i - 1, j + 1, 3) + 2 * src.getPixel(i, j + 1, 3) + src.getPixel(i + 1, j + 1, 3);
					x -= (src.getPixel(i - 1, j - 1, 3) + 2 * src.getPixel(i, j - 1, 3) + src.getPixel(i + 1, j - 1, 3));
					int y = src.getPixel(i + 1, j - 1, 3) + 2 * src.getPixel(i + 1, j, 3) + src.getPixel(i + 1, j + 1, 3);
					y -= (src.getPixel(i - 1, j - 1, 3) + 2 * src.getPixel(i - 1, j, 3) + src.getPixel(i - 1, j + 1, 3));

					int G = sqrt(x * x + y * y);
					if (G < ROI[k][4])
						G = 0;
					else
						G = 255;
					tgt.setPixel(i, j, 1, G);
					tgt.setPixel(i, j, 2, G);
					tgt.setPixel(i, j, 3, G);
				}
}