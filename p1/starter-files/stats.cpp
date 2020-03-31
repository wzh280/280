// stats.cpp

#include "stats.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
//  assert(false);
  sort(v.begin(),v.end());
  vector<vector<double>> summarize_v; 
  for(size_t i=0; i<v.size(); i++){
    if(i == 0){
      summarize_v.push_back({v[0],1}); 
    }
    else{
      for(size_t j=0; j<summarize_v.size(); j++){
        if(v[i]==summarize_v[j][0]){
          summarize_v[j][1] = summarize_v[j][1] + 1;
          break;
        }
        
        if((j == summarize_v.size()-1)&&(v[i]!=summarize_v[j][0])){
          summarize_v.push_back({v[i],1});
          break;
        }
      }
    }    
  }
  return summarize_v;
}

int count(vector<double> v) {
//  assert(false);
  return static_cast<int>(v.size());
}

double sum(vector<double> v) {
 // assert(false);
  double sum = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sum = sum + v[i];
  }
  return sum;
}

double mean(vector<double> v) {
//  assert(false);
  return sum(v) /count(v);

}

double median(vector<double> v) {
//  assert(false);
  double *p = &v[0]; 
  double a;
  double b;
  sort(v.begin(),v.end());
  if((v.size())%2 == 0){
    a = *(p-1+(v.size())/2);
    b = *(p+(v.size())/2);
    return (a+b)/2;
  }
  else{
    a = *(p+(v.size()-1)/2);
    return a;
  }
}

double mode(vector<double> v) {
  vector<vector<double>> result;
  sort(v.begin(),v.end());
  result = summarize(v);
  int max = 0;
  int index = 0;
  for(size_t i = 0; i < result.size(); i++){
    if(max<result[i][1]){
      max = result[i][1];
      index = i;
    }
  }
  return result[index][0];
}

double min(vector<double> v) {
//  assert(false);
  return *min_element(v.begin(),v.end());
}

double max(vector<double> v) {
//  assert(false);
  return *max_element(v.begin(),v.end());
}

double stdev(vector<double> v) {
//  assert(false);
  double m = mean(v);
  double dsum = 0;
  for(size_t i = 0; i<v.size(); i++){
    dsum = dsum + (v[i]-m)*(v[i]-m);
  }
  return sqrt((dsum)/(v.size()-1));
}

double percentile(vector<double> v, double p) {
//  assert(false);

double n;
n = p/100*(5-1)+1;
sort(v.begin(),v.end());
double d;
double k;
d = modf(n , &k);
double out;
out = v[k-1] + d*(v[k]-v[k-1]);
return out;
}
