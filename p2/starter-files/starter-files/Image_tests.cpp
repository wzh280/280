// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  // const Pixel p1 = {1, 2, 3};
  // const Pixel p2 = {4, 5, 6};
  // const Pixel p3 = {7, 8, 9};
  // const Pixel p4 = {10, 11, 12};
  // Image_set_pixel(img, 1, 0, p3);
  // Image_set_pixel(img, 1, 1, p4);
  // Image_set_pixel(img, 0, 0, p1);
  // Image_set_pixel(img, 0, 1, p2);

  cout <<"pixel00 " << Image_get_pixel(img, 0, 0).r <<" "<<
  Image_get_pixel(img, 0, 0).g <<" "<<
  Image_get_pixel(img, 0, 0).b <<" "<<endl;

  cout <<"pixel01 " << Image_get_pixel(img, 0, 1).r <<" "<<
  Image_get_pixel(img, 0, 1).g <<" "<<
  Image_get_pixel(img, 0, 1).b <<" "<<endl;

  cout <<"pixel10 " << Image_get_pixel(img, 1, 0).r <<" "<<
  Image_get_pixel(img, 1, 0).g <<" "<<
  Image_get_pixel(img, 1, 0).b <<" "<<endl;

  cout <<"pixel11 " << Image_get_pixel(img, 1, 1).r <<" "<<
  Image_get_pixel(img, 1, 1).g <<" "<<
  Image_get_pixel(img, 1, 1).b <<" "<<endl;

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  ASSERT_EQUAL(Image_height(img), 2);
  ASSERT_EQUAL(Image_width(img), 2);

  delete img; // delete the Image
}


TEST(test_fill){
  Image *img = new Image;
  Image_init(img, 2, 2);
  const Pixel green = {0, 255, 0};
  Image_fill(img, green);
  ostringstream s,correct;
  Image_print(img, s);
  correct << "P3\n2 2\n255\n";
  correct << "0 255 0 0 255 0 \n";
  correct << "0 255 0 0 255 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  

}

TEST(test_init_is){
  Image *img = new Image;
  istringstream is;
  ifstream fin;
  ofstream fout;
  fout.open("test_dog.txt");
  string filename = "dog_4x5.correct.ppm";
  string s;
  fin.open(filename);
  
  Image_init(img, fin);
  //////////////////method2////////////////////////////
  //int i = 0;
  //string whole;
  // while(fin>>s){
  //   i = i+1;
  //   whole = whole + " "+s;
  //   //cout << s;
  // };
  // //cout <<"i = " <<i<<endl;

  // istringstream ss(whole);
  // // string fsl;
  // // while(ss>>fsl)
  // // {cout<<"fsl"<<fsl<<endl;}

  // Image_init(img, ss);
  //////////////////////////////////////////////
  
  cout << "height" << Image_height(img);
  ASSERT_EQUAL(Image_height(img), 5);
  ostringstream output,correct;
  Image_print(img, output);
  fout<<output.str();
  fout.close();
  fin.close();
  delete img;
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
