#include "./genetic/genetic.hpp"
#include <iomanip>
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