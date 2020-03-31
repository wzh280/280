// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  Matrix_print(mat, cout);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_height_width) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);


  delete mat; // delete the Matrix
}
TEST(test_row_column){
  Matrix *mat = new Matrix;
  Matrix_init(mat,3,5);
  Matrix_fill(mat,42);
  const int *ptr_1 = mat->data+3;
  int actual_row_1 = Matrix_row(mat, ptr_1);
  int actual_column_1 = Matrix_column(mat, ptr_1);
  ASSERT_EQUAL(actual_row_1,1);
  ASSERT_EQUAL(actual_column_1,0);

  const int *ptr_2 = mat->data+14;
  int actual_row_2 = Matrix_row(mat, ptr_2);
  int actual_column_2 = Matrix_column(mat, ptr_2);
  ASSERT_EQUAL(actual_row_2,4);
  ASSERT_EQUAL(actual_column_2,2);
  delete mat;
}

TEST(test_border) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  Matrix_print(mat, cout);
  Matrix_fill_border(mat, 8);
  Matrix_print(mat, cout);
  ASSERT_TRUE(true);



  delete mat; // delete the Matrix
}

TEST(test_max){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, 42);
  Matrix_fill_border(mat, 8);
  ASSERT_EQUAL(Matrix_max(mat),42);
  delete mat;

}

TEST(test_min){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 6);
  Matrix_fill(mat, 42);
  Matrix_fill_border(mat, 8);
  Matrix_print(mat, cout);
  int min = Matrix_min_value_in_row(mat, 1, 0, 3);
  int min_column = Matrix_column_of_min_value_in_row(mat, 1, 0, 3); 
                                      
  ASSERT_EQUAL(min,8);
  ASSERT_EQUAL(min_column,0);

  min = Matrix_min_value_in_row(mat, 1, 1, 3);
  min_column = Matrix_column_of_min_value_in_row(mat, 1, 1, 3); 
                                      
  ASSERT_EQUAL(min,42);
  ASSERT_EQUAL(min_column,1);
 
 
  delete mat;

}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
