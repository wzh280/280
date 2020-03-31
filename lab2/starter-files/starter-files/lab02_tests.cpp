#include "lab02.h"
#include "unit_test_framework.h"

//we define a test case with the TEST(<test_name>) macro.
//<test_name> can be may valid C++ function name.
TEST(test_slideright){
    int arr[5] = {0,1,3,3,4};
    int expected_arr[] = {4,0,1,3,3};
    slideRight(arr,5);
    ASSERT_SEQUENCE_EQUAL(expected_arr, arr);
}
TEST(test_flip){
    int arr[5] = {1,2,3,4,5};
    int expected_arr[] = {5,4,3,2,1};
    flip(arr,5);

    // int arr[4] = {1,2,3,4};
    // int expected_arr[] = {4,3,2,1};
    // flip(arr,4);
    ASSERT_SEQUENCE_EQUAL(expected_arr, arr);
}

TEST(numbers_are_equal) {
    ASSERT_EQUAL(42,42);
}

TEST_MAIN()