#include "./genetic/genetic.hpp"
#include <memory.h>
#include <iomanip>

std::vector <gfloat> input; 
std::vector <gfloat> output; 


void  mlp_Matrix( std::vector <gfloat> &ret, std::vector <gfloat> &m1,  unsigned short row1,  unsigned short col1,  std::vector <gfloat> &m2,  unsigned short row2,  unsigned short col2)
{
   
    if (col1 != row2){
        std::cout <<"mlp_matrix (col1 != row2) !!\n";
        return; 
        }

     ret.resize(row1*col2,gfloat(0));
    
  unsigned short i,j,k;

    for(i = 0; i < row1; i++) {
        for(j = 0; j < col2; j++) {
            for(k = 0; k < col1; k++) {
                ret[(i *col2) + j] += m1[(i *col2) +k] * m2[(k*col2) +j];
            }
        }
    }
}

inline 
void  mlp_Matrix( std::vector <gfloat> &ret, std::vector <gfloat> &m1,  unsigned short row1,  unsigned short col1,  gfloat *m2,  unsigned short row2,  unsigned short col2)
{
   
    if (col1 != row2){
        std::cout <<"mlp_matrix (col1 != row2) !!\n";
        return; 
        }

     ret.resize(row1*col2,gfloat(0));
    
  unsigned short i,j,k;

    for(i = 0; i < row1; i++) {
        for(j = 0; j < col2; j++) {
            for(k = 0; k < col1; k++) {
                ret[(i *col2) + j] += m1[(i *col2) +k] * m2[(k*col2) +j];
            }
        }
    }

   
}


void printMatrix(std::vector <gfloat> &m, int row, int col)
{
    for(auto i = 0; i < row; ++i) {
        for(auto j = 0; j < col; ++j) {
            std::cout << std::setw(5) << m[(i* col )+j] << "; ";
        }
        std::cout << std::endl;
    }
}



#define inp_size 6
#define out_size 2

#define num_w (inp_size * out_size )

float goel = 25;
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