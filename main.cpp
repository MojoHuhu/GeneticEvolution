
#define USE_HALF_GFLOAT 1
#define _DEBUG 

#include "matrix.hpp"
#include <memory.h>


std::vector <gfloat> input; 
std::vector <gfloat> output; 


#define inp_size 6
#define out_size 2

#define num_w (inp_size * out_size )


struct Solution 
{  
    float rank;
    gfloat x[num_w];

    gfloat result() 
    { 
        std::vector <gfloat> ret;  
        mlp_Matrix(ret,input,1,6, x,inp_size,out_size );
        return  (abs(ret[0]-output[0]) + abs(ret[1]-output[1])); 
       
    } 
    
    void fitness()
    {
        gfloat ans=result() ;
        rank = (ans==0) ? 9999999 :abs(1/ans);
    }
}; 



int main()
{
    for(int i  =0;i< 6; i++)
       input.push_back(gfloat(i)) ;

   for(int i  =0;i< 2; i++)
       output.push_back(gfloat(i)) ;

   
  

    std::vector <Solution>solutions;
    Genetic<Solution>(solutions,num_w,10,0.001,10000,10,2);
  

    std::cout << "\nCompair : \n";
    printMatrix(output,1,2);
    std::vector <gfloat> ret;  
    mlp_Matrix(ret,input,1,6, solutions[0].x,inp_size,out_size );
    std::cout << "     =\n";
    printMatrix(ret,1,2);
    std::cout << "     \n";
  
  
    std::cout << "  gmatrix how to   \n";
    gmatrix r,t,m1,m2;
    m1.resize(1,6,gfloat(2)); m2.resize(6,2,gfloat(1));
    r=m1*m2;
     
    printMatrix(r);
    std::cout << "  transpose   \n";
    t =r.transpose();
    printMatrix(t);

    return 0;
}