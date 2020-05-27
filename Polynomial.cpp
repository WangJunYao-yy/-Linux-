#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<vector>
#include"Polynomial.h"

using namespace std;

void Polynomial::input(){
    this->factor.clear();
    int n;
    cin>>n;
    int tmp_factor;
    for(int i=0;i<n;i++){
        cin>>tmp_factor;
        this->factor.push_back(tmp_factor);
    }
    cin>>this->name;
}
    

void Polynomial::output(){//output one specific polynomial
    int r = this->factor.size();
    for(int i = 0; i < this->factor.size(); i++){
        if(fabs(this->factor[i])<=1e-10){
            continue;
        }
        else if(fabs(this->factor[i]-1)<=1e-10){
            if(i==0){
                if(r-i-1==1){
                    cout<<"x";
                }
                else if(r-i-1==0){
                    cout<<"1";
                }
                else{
                    cout<<"x^"<<r-i-1;
                }
            }
            else{
                if(r-i-1==1){
                    cout<<"+x";
                }
                if(r-i-1==0){
                    cout<<"+1";
                }
                else{
                    cout<<"+x^"<<r-i-1;
                }
            }
        }
        else if(fabs(this->factor[i]+1)<=1e-10){
            if(r-i-1==1){
                cout<<"-x";
            }
            else if(r-i-1==0){
                cout<<"-1";
            }
            else{
                cout<<"-x^"<<r-i-1;
            }
        }
        else{
            if(i==0){
                printf("%g",this->factor[i]);
                if(r-i-1==1){
                    cout<<"x";
                }
                else if(r-i-1==0){
                }
                else{
                    cout<<"x^"<<r-i-1;
                }
            }
            else if(this->factor[i]<0){
                printf("%g",this->factor[i]);
                if(r-i-1==1){
                    cout<<"x";
                }
                else if(r-i-1==0){
                }
                else{
                    cout<<"x^"<<r-i-1;
                }
            }
            else {
                cout<<"+";
                printf("%g",this->factor[i]);
                if(r-i-1==1){
                    cout<<"x";
                }
                else if(r-i-1==0){
                }
                else{
                    cout<<"x^"<<r-i-1;
                }
            }

        }
    }


}

Polynomial Polynomial::plus(Polynomial operand1, Polynomial operand2){
    Polynomial new_poly;
    int m = operand1.factor.size();
    int n = operand2.factor.size();
    for(int i = 0; i < m && i < n; i++){
        double adder = operand1.factor[m-1-i]+operand2.factor[n-1-i];
        new_poly.factor.insert(new_poly.factor.begin(),adder);
    }
    if(m<n){
        for(int i=0; i<n-m; i++){
            new_poly.factor.insert(new_poly.factor.begin(),operand2.factor[n-m-i-1]);
        }
    }
    if(m>n){
        for(int i = 0; i <m-n;i++){
            new_poly.factor.insert(new_poly.factor.begin(),operand1.factor[m-n-i-1]);
        }
    }
    return new_poly;
}

Polynomial Polynomial::devirate(Polynomial operand){
    Polynomial new_poly;
    int r = operand.factor.size();
    for(int i=0;i<r-1;i++){
        double new_fac=operand.factor[i]*(r-1-i);
        new_poly.factor.push_back(new_fac);
    }

    return new_poly;
}

Polynomial Polynomial::multiplicate(Polynomial operand1, Polynomial operand2){
    int m = operand1.factor.size();
    int n = operand2.factor.size();
    int new_r=m+n-1;
    Polynomial new_poly;
    for(int i = 0; i <new_r; i++){
        double tmp=0;
        new_poly.factor.push_back(tmp);
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            new_poly.factor[i+j]+=(operand1.factor[i]*operand2.factor[j]);
        }
    }
    

    return new_poly;
}

double Polynomial::value(double x){
    double value=0;
    int r = this->factor.size();
    for(int i = 0; i < r; i++){
        double tmp=1;
        for(int j = 0; j<r-i-1;j++){
            tmp*=x;
        }
        tmp*=this->factor[i];
        value+=tmp;
    }
    return value;

}
double Polynomial::integral(double upper_limit, double lower_limit){
    Polynomial new_poly;
    int r = this->factor.size();
    double ans;
    for(int i = 0; i < r; i++){
        double tmp;
        tmp = this->factor[i]/(r-i);
        new_poly.factor.push_back(tmp);
    }
    new_poly.factor.push_back(0);
    ans=new_poly.value(upper_limit)-new_poly.value(lower_limit);

    return ans;
}
