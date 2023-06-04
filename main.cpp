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

    float result() 
    { 
        std::vector <gfloat> ret;  
        mlp_Matrix(ret,input,1,6, x,inp_size,out_size );
        return  ( std::abs(ret[0]-output[0]) + std::abs(ret[1]-output[1]) ); 
    } 
    
    void fitness()
    {
        float ans=result() ;
        rank = (ans==0) ? 9999999 :std::abs(1/ans);
    }
}; 



int main()
{
    for(int i  =0;i< 6; i++)
       input.push_back(gfloat(i)) ;

   for(int i  =0;i< 2; i++)
       output.push_back(gfloat(i)) ;

   

   

    std::vector <Solution>solutions;
    Genetic<Solution>(solutions,num_w,20,0.001,2000,500,4);
  

    std::cout << "\nCompair : \n";
    printMatrix(output,1,2);
    std::vector <gfloat> ret;  
    mlp_Matrix(ret,input,1,6, solutions[0].x,inp_size,out_size );
    std::cout << "     =\n";
    printMatrix(ret,1,2);
    std::cout << "     \n";
    return 0;
}