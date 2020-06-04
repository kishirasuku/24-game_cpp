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
    e.push_back(std::to_string(int(c)));
  }
  return e;
}

std::vector<std::string> exps_results;
std::vector<std::string> stack_results;

void calculate(std::vector<double> c,std::vector<std::string> exps,std::vector<std::string> stacks,int n){
  if(n==1){
    if(std::fabs(c[0]-24) <= 0.0000001){
      exps_results.push_back(exps[0]);
      stack_results.push_back(stacks[0]);
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

      std::string a_stack = stacks[i];
      std::string b_stack = stacks[j];
      stacks[j] = stacks[n-1];

      exps[i] = "(" + a_str + "+" + b_str + ")";
      stacks[i] = a_stack + " " + b_stack + " + ";
      c[i] = a + b;
      calculate(c,exps,stacks,n-1);

      exps[i] = "(" + a_str + "-" + b_str + ")";
      stacks[i] = a_stack + " " + b_stack + " - ";
      c[i] = a - b;
      calculate(c,exps,stacks,n-1);
      exps[i] = "(" + b_str + "-" + a_str + ")";
      stacks[i] = b_stack + " " + a_stack + " - ";
      c[i] = b - a;
      calculate(c,exps,stacks,n-1);

      exps[i] = "(" + a_str + "*" + b_str + ")";
      stacks[i] = a_stack + " " + b_stack + " * ";
      c[i] = a * b;
      calculate(c,exps,stacks,n-1);

      if(b!=0){
	exps[i] = "(" + a_str + "/" + b_str + ")";
	stacks[i] = a_stack + " " + b_stack + " / ";
	c[i] = a / b;
	calculate(c,exps,stacks,n-1);
      }
      if(a!=0){
	exps[i] = "(" + b_str + "/" + a_str + ")";
	stacks[i] = b_stack + " " + a_stack + " / ";
	c[i] = b / a;
	calculate(c,exps,stacks,n-1);
      }

      c[i] = a;
      c[j] = b;
      exps[i] = a_str;
      exps[j] = b_str;
      stacks[i] = a_stack;
      stacks[j] = b_stack;

      j ++;
    }
    i++;
  }
}

int main(){
  std::vector<std::vector<double>> cmb = combination();
  for(auto c:cmb){
    std::vector<std::string> expressions = exp(c);
    std::vector<std::string> stacks = exp(c);
    std::string first_exp;
    for(auto n:c){
      first_exp = first_exp + " " + std::to_string(int(n));
    }
    calculate(c,expressions,stacks,4);
    if(int(exps_results.size()) == 0){
      std::cout << "NO\n";
    }else{
      std::cout << first_exp << " --->   " << stack_results[0] << "    " << exps_results[0] << "\n";
      
    }
    exps_results = {};
    stack_results = {};
  }
  return 0;
}
