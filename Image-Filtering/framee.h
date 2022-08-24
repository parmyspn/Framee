#ifndef LAB_INTRO_H
#define LAB_INTRO_H

#include "cs221util/PNG.h"
using namespace cs221util;

PNG grayscale(PNG image);  
PNG watermark(PNG firstImage, PNG secondImage);
PNG boxBlur(PNG image);
PNG sharpen(PNG image);
PNG ridgeDetect(PNG image);
PNG edgeDetect(PNG image);
PNG adjustBrightness(PNG image, double factor);
PNG adjustVibrance(PNG image, double factor) ;
PNG adjustWarmth(PNG image, double factor);
PNG adjustBrightnessVibranceWarmth(PNG image, double brithnessFactor, double vibranceFactor , double warmthFactor);

#endif
