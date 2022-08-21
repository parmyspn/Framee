#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "framee.h"


using namespace cs221util;

/**
 * Returns an image that has been transformed to grayscale.
 *
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel->s = 0;
    }
  }

  return image;
}




/**
* Returns an immge that has been watermarked by another image.
*
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  for (unsigned x = 0; x < secondImage.width(); x++) {
    for (unsigned y = 0; y < secondImage.height(); y++) {
      HSLAPixel *secondPixel = secondImage.getPixel(x, y);
      if(secondPixel -> l == 1) {
        HSLAPixel *firstPixel = firstImage.getPixel(x, y);
        if( firstPixel -> l <= 0.8) {
          firstPixel -> l += 0.2;
        }else {
          firstPixel -> l = 1;
        }
      }
      
    }
  }

  return firstImage;
}

/**
* Returns an image that has been blured.
*
*
* @param image  The image
*
* @return The blurred image.
*/

PNG boxBlur(PNG image) {
 
   static double l[1080][1080];
   static double s[1080][1080];
   static double h[1080][1080];
   static double a[1080][1080];


   for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      l[x][y] = pixel -> l ;
      h[x][y] = pixel -> h;
      s[x][y] = pixel ->s;
      a[x][y] = pixel ->a;

    } 
  }

  
  for (unsigned x = 1; x < image.width()-1; x++) {
    for (unsigned y = 1; y < image.height()-1; y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      
      pixel -> h = (h[x-1][y-1] + h[x-1][y] + h[x-1][y+1] + h[x][y-1] + h[x][y] + h[x][y+1] + h[x+1][y-1] + h[x+1][y] + h[x+1][y+1])/9 ;
      pixel ->s =  (s[x-1][y-1] + s[x-1][y] + s[x-1][y+1] + s[x][y-1] + s[x][y] + s[x][y+1] + s[x+1][y-1] + s[x+1][y] + s[x+1][y+1])/9;
      pixel ->l = (l[x-1][y-1] + l[x-1][y] + l[x-1][y+1] + l[x][y-1] + l[x][y] + l[x][y+1] + l[x+1][y-1] + l[x+1][y] + l[x+1][y+1])/9;
      pixel -> a =   (a[x-1][y-1] + a[x-1][y] + a[x-1][y+1] + a[x][y-1] + a[x][y] + a[x][y+1] + a[x+1][y-1] + a[x+1][y] + a[x+1][y+1])/9 ;
    } 
  }
 
  return image;
}


/**
* Returns an image that has been sharpen.
*
*
* @param image  The image
*
* @return The sharpened image.
*/

PNG sharpen(PNG image) {

  static double l[1080][1080];

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
       HSLAPixel *pixel = image.getPixel(x, y);
       l[x][y] = pixel -> l ;   
      } 
     }
  for (unsigned x = 1; x < image.width()-1; x++) {
    for (unsigned y = 1; y < image.height()-1; y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel ->l = (- l[x-1][y]  - l[x][y-1] + 5* l[x][y] - l[x][y+1] - l[x+1][y] ) ;
    } 
  }
 
  return image;
}



/**
* Returns an image that has been ridge detected.
*
*
* @param image  The image
*
* @return The ridge detected image.
*/

PNG ridgeDetect(PNG image) {
 
   static double l[1080][1080];

   for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      l[x][y] = pixel -> l ;
    } 
  }
  
  for (unsigned x = 1; x < image.width()-1; x++) {
    for (unsigned y = 1; y < image.height()-1; y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel->l = -l[x-1][y-1] - l[x-1][y] - l[x-1][y+1] - l[x][y-1] + 8 * l[x][y] - l[x][y+1] - l[x+1][y-1] - l[x+1][y] - l[x+1][y+1];
    } 
  }
  return image;
}

/**
* Returns an image that has been edge detected.
*
*
* @param image  The image
*
* @return The edge detected image.
*/

PNG edgeDetect(PNG image) {
   
   static double l[1080][1080];
   static double h[1080][1080];
   
   for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      l[x][y] = pixel -> l ;
      h[x][y] = pixel -> h;
      pixel ->s = 0;
    } 
  }
  
  for (unsigned x = 1; x < image.width()-1; x++) {
    for (unsigned y = 1; y < image.height()-1; y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      
      double hx = (h[x+1][y-1] +2* h[x+1][y] + h[x+1][y+1])/(h[x-1][y-1] +2*h[x-1][y] + h[x-1][y+1]);
      double hy = ( h[x-1][y+1] + 2*h[x][y+1] +h[x+1][y+1])/(h[x-1][y-1] +h[x][y-1] +h[x+1][y-1]  );
      pixel ->h = sqrt(pow(hx,2)+pow(hy,2));

      double lx = -l[x-1][y-1] -2*l[x-1][y] - l[x-1][y+1]  + l[x+1][y-1] +2* l[x+1][y] + l[x+1][y+1] ;
      double ly =  l[x-1][y-1] - l[x-1][y+1] +2 * l[x][y-1] -2* l[x][y+1] +l[x+1][y-1]  - l[x+1][y+1] ;
      pixel ->l = sqrt(pow(lx,2)+pow(ly,2));
      
    } 
  }
  return image;
}

/**
* Returns an image that its brightness has been adjusted
*
*
* @param image  The image
* @param image  The factor of adjustment
*
* @return The adjusted image.
*/

PNG adjustBrightness(PNG image, double factor) {
  if(!factor) return image;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel ->l = max(0.0,min(1.0, pixel ->l+ pixel ->l *(factor/100.0)));
    
      
    } 
  }
  return image;
}


/**
* Returns an image that its vibrance has been adjusted
*
*
* @param image  The image
* @param image  The factor of adjustment
*
* @return The adjusted image.
*/


PNG adjustVibrance(PNG image, double factor) {
  if(!factor) return image;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      if(pixel->s <0.85){
        pixel ->s = max(0.0,min(1.0, pixel ->s+ pixel ->s *(factor/100.0)));
      }
      
    } 
  }
  return image;
}


/**
* Returns an image that its warmth has been adjusted
*
*
* @param image  The image
* @param image  The factor of adjustment
*
* @return The adjusted image.
*/
PNG adjustWarmth(PNG image, double factor) {
  if(!factor) return image;
  if(factor>0){
    double value = factor/180;
    for (unsigned x = 0; x < image.width(); x++) {
      for (unsigned y = 0; y < image.height(); y++) {
        HSLAPixel *pixel = image.getPixel(x, y);
        double hue = pixel ->h;
        if (hue > 0 && hue < 120 ){
          pixel ->h -= pixel ->h *value;
        }
        if (hue >300 && hue < 360 ){
         pixel ->h += pixel ->h *value;
      }
    } 
  }
  }else{
    double value = factor/120.0/4.0;
    for (unsigned x = 0; x < image.width(); x++) {
      for (unsigned y = 0; y < image.height(); y++) {
        HSLAPixel *pixel = image.getPixel(x, y);
        double hue = pixel ->h;
        if (hue > 120 && hue < 180 ){
          pixel ->h += pixel ->h *value;
        }
        if (hue >180 && hue < 285 ){
          pixel ->h -= pixel ->h *value;
        }
     } 
   }
  }
  
  return image;
}
