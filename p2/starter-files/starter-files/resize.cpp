#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.h"
#include "processing.h"
#include "Matrix_test_helpers.h"
#include "Image_test_helpers.h"

#include <iostream> /////wzh added
#include <sstream>
using namespace std;

int main(int argc, char **argv){
    if(argc<5){
        cout << "Usage example: " << argv[0] << " [dog|crabster|horses].ppm" <<
         "[dog|crabster|horses]_4*4.ppm"<< " 4" << " 4"<< endl;
        return 1;
    }
    else{
        string infilename, outfilename;
        int expected_w,expected_h;
        infilename = argv[1];
        outfilename = argv[2];
        expected_w = stoi(argv[3]);
        expected_h = stoi(argv[4]);

        Image *img = new Image;
        ifstream fin;
        ofstream fout;
        fin.open(infilename.c_str());
        
        if (!fin.is_open()){
            cout << "Unable to open " << infilename << endl;
            return 1;
        }

        Image_init(img, fin);
        int old_height = Image_height(img);
        int old_width = Image_width(img);
        fin.close();
        if(old_height<expected_h){
            cout << "height unexpected" << endl;
            cout << "height should be no larger than " << old_height <<"."<<endl;
            return 1;
        }

        if(old_width<expected_w){
            cout << "width unexpected" << endl;
            cout << "width should be no larger than " << old_width <<"."<<endl;
            return 1;
        }
 

        seam_carve(img, expected_w, expected_h);
        fout.open(outfilename.c_str());
        cout << Image_width(img) << endl;
        cout << Image_height(img) << endl;
        Image_print(img, fout);
        fout.close();
        delete img;
        cout << "resizing done!"<<endl;
    }


}