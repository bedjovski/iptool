#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void gamp(image &src, image &tgt, int ROI[3][6], int n); // gradient amplitude
		static void bamp(image &src, image &tgt, int ROI[3][6], int n); // binary derived from gradient amplitude by threshholding
		static void bang(image &src, image &tgt, int ROI[3][6], int n); // binary derived from angle from gradient amplitude by threshholding
		static void colgamp(image &src, image &tgt, int ROI[3][6], int n); // gradient amplitude for colorful pics
		static void HSIamp(image &src, image &tgt, int ROI[3][6], int n); // binary derived from gradient amplitude on I

};


#endif

