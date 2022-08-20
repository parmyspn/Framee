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
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel->s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the luminance will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
   for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      double distance = sqrt((x - centerX)*(x - centerX)+ (y - centerY)*(y - centerY));
      if(distance > 200) {
        pixel->l = 0;
      }
      pixel->l -= pixel->l * distance * 0.025;
    }
  }

  return image;
}


/**
 * Returns a image transformed to UBC colors.
 *
 * The hue of every pixel is set to the a hue value of either yellow or
 * blue, based on if the pixel's hue value is closer to yellow than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The UBCify'd image.
**/
PNG ubcify(PNG image) {
   for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      double hue = pixel ->h;
      if( hue >= 285 ){
        pixel ->h = 40;
      }else if(hue < 285 &&  hue >= 210) {
        pixel ->h = 210;
      }else if(hue >= 125) {
        pixel ->h = 210;
      }else{
        pixel ->h = 40;
      }

    }
  }
  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2 (up to a maximum
* of 1.0).
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


PNG boxBlur(PNG image) {
 

   static double l[1080][1080];
   static double s[1080][1080];
   static double h[1080][1080];
   static double a[1080][1080];
 

   
   //cout << width << endl;
   //cout << height << endl;
   

   for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      l[x][y] = pixel -> l ;
      
      h[x][y] = pixel -> h;
      
      s[x][y] = pixel ->s;
     
      
      a[x][y] = pixel ->a;
     // cout << h[x][y] << endl;
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


PNG sharpen(PNG image) {
 

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
      pixel -> h = (- h[x-1][y]  - h[x][y-1] + 5* h[x][y] - h[x][y+1] - h[x+1][y] ) ;
      pixel ->s = (- s[x-1][y]  - s[x][y-1] + 5* s[x][y] - s[x][y+1] - s[x+1][y] ) ;
      pixel ->l = (- l[x-1][y]  - l[x][y-1] + 5* l[x][y] - l[x][y+1] - l[x+1][y] ) ;
      pixel -> a =  (- a[x-1][y]  - a[x][y-1] + 5* a[x][y] - a[x][y+1] - a[x+1][y] ) ;
    } 
  }
 
  
  return image;
}



PNG ridgeDetect(PNG image) {
 

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
      //pixel ->h = -h[x-1][y-1] -h[x-1][y] - h[x-1][y+1] - h[x][y-1] + 8 * h[x][y] - h[x][y+1] - h[x+1][y-1] - h[x+1][y] - h[x+1][y+1] ;
      pixel ->s = -s[x-1][y-1] - s[x-1][y] - s[x-1][y+1] - s[x][y-1] + 8 * s[x][y] - s[x][y+1] - s[x+1][y-1] - s[x+1][y] - s[x+1][y+1] ;
      pixel->l = -l[x-1][y-1] - l[x-1][y] - l[x-1][y+1] - l[x][y-1] + 8 * l[x][y] - l[x][y+1] - l[x+1][y-1] - l[x+1][y] - l[x+1][y+1];
      
    } 
  }
  return image;
}


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
      
      double hx = (h[x+1][y-1] +2* h[x+1][y] + h[x+1][y+1])/(h[x-1][y-1] +2*h[x-1][y] + h[x-1][y+1])  ;
      double hy = ( h[x-1][y+1] + 2*h[x][y+1] +h[x+1][y+1])/(h[x-1][y-1] +h[x][y-1] +h[x+1][y-1]  );
     // double hy =  h[x-1][y-1] - h[x-1][y+1] +2 * h[x][y-1] -2* h[x][y+1] +h[x+1][y-1]  - h[x+1][y+1] ;
      pixel ->h = sqrt(pow(hx,2)+pow(hy,2));

   
  

      double lx = -l[x-1][y-1] -2*l[x-1][y] - l[x-1][y+1]  + l[x+1][y-1] +2* l[x+1][y] + l[x+1][y+1] ;
      double ly =  l[x-1][y-1] - l[x-1][y+1] +2 * l[x][y-1] -2* l[x][y+1] +l[x+1][y-1]  - l[x+1][y+1] ;
      pixel ->l = sqrt(pow(lx,2)+pow(ly,2));
      
    } 
  }
  return image;
}
