#include<iostream>
#include<vector>
#include<string>
#include<cmath>

std::vector<std::vector<double>> combination(){
  std::vector<std::vector<double>> cmb;
  for(double i=1;i<=6;i++){
    for(double j=i+1;j<=7;j++){
      for(double k=j+1;k<=8;k++){
	for(double l=k+1;l<=9;l++){
	  std::vector<double> elm;
	  elm.push_back(i);
	  elm.push_back(j);
	  elm.push_back(k);
	  elm.push_back(l);
	  cmb.push_back(elm);
	}
      }
    }
  }
  return cmb;
}

std::vector<std::string> exp(std::vector<double> cmb){
  std::vector<std::string> e;
  for(auto c:cmb){
    e.push_back(std::to_string(c));
  }
  return e;
}

std::vector<std::string> exps_results;

void calculate(std::vector<double> c,std::vector<std::string> exps,int n){
  if(n==1){
    if(std::fabs(c[0]-24) <= 0.0000001){
      exps_results.push_back(exps[0]);
    }
  }
  int i = 0;
  int j = i+1;
  
  while(i < n){
    while(j < n){
      double a = c[i];
      double b = c[j];
      c[j] = c[n-1];

      std::string a_str = exps[i];
      std::string b_str = exps[j];
      exps[j] = exps[n-1];

      exps[i] = "(" + a_str + "+" + b_str + ")";
      c[i] = a + b;
      calculate(c,exps,n-1);

      exps[i] = "(" + a_str + "-" + b_str + ")";
      c[i] = a - b;
      calculate(c,exps,n-1);
      exps[i] = "(" + b_str + "-" + a_str + ")";
      c[i] = b - a;
      calculate(c,exps,n-1);

      exps[i] = "(" + a_str + "*" + b_str + ")";
      c[i] = a * b;
      calculate(c,exps,n-1);

      if(b!=0){
	exps[i] = "(" + a_str + "/" + b_str + ")";
	c[i] = a / b;
	calculate(c,exps,n-1);
      }
      if(a!=0){
	exps[i] = "(" + b_str + "/" + a_str + ")";
	c[i] = b / a;
	calculate(c,exps,n-1);
      }

      c[i] = a;
      c[j] = b;
      exps[i] = a_str;
      exps[j] = b_str;

      j ++;
    }
    i++;
  }
}

int main(){
  std::vector<std::vector<double>> cmb = combination();
  for(auto c:cmb){
    std::vector<std::string> expressions = exp(c);
    calculate(c,expressions,4);
    if(int(exps_results.size()) == 0){
      std::cout << "NO\n";
    }else{
      std::cout << exps_results[0] << "\n";
      
    }
    exps_results = {};
  }
  return 0;
}
