//main.cpp
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {
  cout << "hello from main!\n";
  string infilename,columnname,filename,outname;
  infilename = "main_test.in";
  outname = "main_test.out";
  ifstream fin;
  ofstream fout;
  fout.open(outname);


  if(argc == 1){
    cout << "enter a filename" << endl;  //.tsv
    fout << "enter a filename" << endl;
    cin >> filename;
    cout << "enter a column name" << endl;
    fout << "enter a column name" << endl;
    cin >> columnname;
  }
  else if(argc == 3){
    infilename = argv[2];
    fin.open(infilename);
    fin >> filename >> columnname;
    fin.close();
  }
  else{
    outname = argv[3];
  }



  cout << "reading column " << columnname << " from " << filename << endl;
  fout << "reading column " << columnname << " from " << filename << endl;

  vector<double> data;
  data = extract_column(filename, columnname);

  cout << "Summary (value: frequency)" << endl;
  fout << "Summary (value: frequency)" << endl;
  vector<vector<double>> result;
  result = summarize(data);

  for(size_t i = 0; i<result.size(); i++){
    cout << result[i][0] << ": " << result[i][1] <<endl;
    fout << result[i][0] << ": " << result[i][1] <<endl;
  } 

  int countnum;
  double sumnum,meannum,mediannum,modenum,minnum,maxnum,stdevnum,p0,p25,p50,p75,p100;

  countnum = count(data);
  sumnum = sum(data);
  meannum = mean(data);
  mediannum = median(data);
  modenum = mode(data);
  minnum = min(data);
  maxnum = max(data);
  stdevnum = stdev(data);
  p0 = percentile(data,0);
  p25 = percentile(data,25);
  p50 = percentile(data,50);
  p75 = percentile(data,75);
  p100 = percentile(data,100);

  cout << "count = " << countnum << endl;
  cout << "sum = " << sumnum << endl;
  cout << "mean = " << meannum << endl;
  cout << "stdev = " << stdevnum << endl;
  cout << "median = " << mediannum << endl;
  cout << "mode = " << modenum << endl;
  cout << "min = " << minnum << endl;
  cout << "max = " << maxnum << endl;
  cout << "  0th percentile = " << p0 << endl;
  cout << " 25th percentile = " << p25 << endl;
  cout << " 50th percentile = " << p50 << endl;
  cout << " 75th percentile = " << p75 << endl;
  cout << "100th percentile = " << p100 << endl;

  fout << "count = " << countnum << endl;
  fout << "sum = " << sumnum << endl;
  fout << "mean = " << meannum << endl;
  fout << "stdev = " << stdevnum << endl;
  fout << "median = " << mediannum << endl;
  fout << "mode = " << modenum << endl;
  fout << "min = " << minnum << endl;
  fout << "max = " << maxnum << endl;
  fout << "  0th percentile = " << p0 << endl;
  fout << " 25th percentile = " << p25 << endl;
  fout << " 50th percentile = " << p50 << endl;
  fout << " 75th percentile = " << p75 << endl;
  fout << "100th percentile = " << p100 << endl;

fout.close();



}