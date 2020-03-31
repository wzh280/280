// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include <string>
#include <iostream>

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  //assert(false); // TODO Replace with your implementation!
  img->width = width;
  img->height = height;
  Matrix_init(&(img->red_channel), width, height);
  Matrix_init(&(img->green_channel), width, height);
  Matrix_init(&(img->blue_channel), width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  //assert(false); // TODO Replace with your implementation!
  //std::cout << "in funtion" << std::endl; 
// std::string fsl;
// int j = 0;
//   while(is>>fsl)
//   {std::cout<<"fsl"<<fsl<<" "<<std::endl;
//   j = j+1;
//   std::cout<<"j = "<<j<<std::endl;}

  std::string word;
  int i = 0;
  int row,column;
  int width,height,red,green,blue;
  int *ptr_r,*ptr_g,*ptr_b;
  while(is>>word){
    //std::cout << "is>>word" <<std::endl;
    //std::cout<<i<<std::endl;
    if(i == 1){
      width = stoi(word);
      img->width = width;
    }
    else if(i == 2){
      height = stoi(word);
      img->height = height;
      Matrix_init(&(img->red_channel), width, height);
      Matrix_init(&(img->green_channel), width, height);
      Matrix_init(&(img->blue_channel), width, height);
      //(img->red_channel).height = height;
      //(img->green_channel).height = height;
      //(img->blue_channel).height = height;
    }
    else if(i>2){
      row = (i-4)/(3*img->width);
      column = (i-4)%(3*img->width)/3;
      //std::cout << "row " << row << " column "<<column<<std::endl;

      if((i-4)%3==0){
        red = stoi(word);
        //((img->red_channel).data)[(i-4)/3] = red; 
        ptr_r = Matrix_at(&(img->red_channel), row, column);
        *ptr_r = red;
      }
      else if((i-4)%3==1){
        green = stoi(word);
        //((img->green_channel).data)[(i-4)/3] = green; 
        ptr_g = Matrix_at(&(img->green_channel), row, column);
        *ptr_g = green;
      }
      else if((i-4)%3==2){
        blue = stoi(word);
        //((img->blue_channel).data)[(i-4)/3] = blue; 
        ptr_b = Matrix_at(&(img->blue_channel), row, column);
        *ptr_b = blue;
      }
    }
  i = i+1;
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  //assert(false); // TODO Replace with your implementation!
  os << "P3" << std::endl;
  os << img->width <<" "<< img->height <<std::endl;
  os << "255" << std::endl;
  int row,column;
  const int *ptr_r;
  const int *ptr_g;
  const int *ptr_b;
  for (int i = 0; i< img->height* img->width; i++){
    row = i/(img->width);
    column = i%(img->width);
    ptr_r = Matrix_at(&(img->red_channel), row, column);
    ptr_g = Matrix_at(&(img->green_channel), row, column);
    ptr_b = Matrix_at(&(img->blue_channel), row, column);
    os<< *ptr_r << " " << *ptr_g << " " << *ptr_b << " ";
    //os<<row<<" "<<column<<std::endl;
    if(i%img->width==img->width-1){     
      os << std::endl;
    }
  }


}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  //assert(false); // TODO Replace with your implementation!
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  //assert(false); // TODO Replace with your implementation!
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  //assert(false); // TODO Replace with your implementation!
  const int *ptr_r;
  const int *ptr_g;
  const int *ptr_b;
  ptr_r = Matrix_at(&(img->red_channel), row, column);
  ptr_g = Matrix_at(&(img->green_channel), row, column);
  ptr_b = Matrix_at(&(img->blue_channel), row, column);
  Pixel p;
  p.b = *ptr_b;
  p.g = *ptr_g;
  p.r = *ptr_r;
  return p;

}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  //assert(false); // TODO Replace with your implementation!
  int *ptr_r;
  int *ptr_g;
  int *ptr_b;
  ptr_r = Matrix_at(&(img->red_channel), row, column);
  ptr_g = Matrix_at(&(img->green_channel), row, column);
  ptr_b = Matrix_at(&(img->blue_channel), row, column);
  *ptr_r = color.r;
  *ptr_b = color.b; 
  *ptr_g = color.g;
  //std::cout<< "@d= "<<ptr_r-Matrix_at(&(img->red_channel), 0, 0)<<std::endl;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  //assert(false); // TODO Replace with your implementation!
  Matrix_fill(&(img->red_channel), color.r);
  Matrix_fill(&(img->green_channel), color.g);
  Matrix_fill(&(img->blue_channel), color.b);
}
