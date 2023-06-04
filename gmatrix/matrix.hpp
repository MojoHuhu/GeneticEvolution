#ifndef GMATRIX
#define GMATRIX 1

#include "../genetic/genetic.hpp"
#include <iomanip>



#ifndef USE_HALF_GFLOAT
     typedef float gfloat;
#else
    #include "../half/half.hpp"
    using half_float::half;
    typedef half gfloat;
#endif


void  mlp_Matrix( std::vector <gfloat> &ret, std::vector <gfloat> &m1,  unsigned short row1,  unsigned short col1,  std::vector <gfloat> &m2,  unsigned short row2,  unsigned short col2)
{
   
 #ifdef _DEBUG  
    if (col1 != row2){
        std::cout <<"mlp_matrix (col1 != row2) !!\n";
        return; 
        }
#endif

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

 #ifdef _DEBUG  
    if (col1 != row2){
        std::cout <<"mlp_matrix (col1 != row2) !!\n";
        return; 
        }
#endif
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




struct gmatrix
{
    unsigned short row, col;
    std::vector <gfloat> x;
    void resize(unsigned short row1,  unsigned short col1, gfloat init)
    {
        row=row1; 
        col =col1;
        x.resize(row1*col1,init);
    }

   gmatrix operator*(const gmatrix& m2)
   {
     gmatrix ret;
#ifdef _DEBUG  
    if (this->col != m2.row){
        std::cout <<"mlp_matrix (col1 != row2) !!\n";
        return ret; 
        }
#endif

   unsigned short i,j,k;
   const unsigned short row1 = this->row,col1 =this->col,col2 =m2.col;
  
   ret.resize(row1,col2,gfloat(0));

   std::vector <gfloat> &r = ret.x;
   const std::vector <gfloat> &o= this->x;
   const std::vector <gfloat> &t= m2.x;
    for(i = 0; i < row1; i++) {
        for(j = 0; j < col2; j++) {
            for(k = 0; k <col1; k++) {
                r[(i *col2) + j] += o[(i *col2) +k] * t[(k*col2) +j];
            }
        }
    }
     return ret;
   }

 gmatrix transpose()
 {
    gmatrix ret;
    unsigned short i,j,k;
    const unsigned short row1 = this->row,col1 =this->col;
    ret.resize(col1,row1,gfloat(0));
    std::vector <gfloat> &r = ret.x;
    const std::vector <gfloat> &o= this->x;
        for(i = 0; i < row1; i++) {
            for(k = 0; k <col1; k++) {
                    r[(i*col1)+k] = o[(i*row1)+k];
                 }

            }

    return ret;
 }

 
 gmatrix hardmanProuct(const gmatrix& m2)
 {
    //http://neuralnetworksanddeeplearning.com/chap2.html#backpropagation_the_big_picture
    gmatrix ret;
    unsigned short i;
    const unsigned short size= this->x.size();
    ret.resize(this->row,this->col,gfloat(0));
    std::vector <gfloat> &r = ret.x;
    const std::vector <gfloat> &o= this->x;
     const std::vector <gfloat> &t= m2.x;
    
    for(i = 0; i < size; i++)
        r[i] = t[i]*o[i];


    return ret;
 }


  void setRandom(gfloat from =gfloat(-1),gfloat to= gfloat(1))
  {
      unsigned short i;
      const unsigned short size= this->x.size();
       std::random_device dev;
      std::uniform_real_distribution<float> rd(from ,to);
      std::vector <gfloat> &o= this->x;
      for(i = 0; i < size; i++)
            o[i]= rd(dev);

  } 


  void setZero()
  {
 
      unsigned short i;
      const unsigned short size= this->x.size();
      std::vector <gfloat> &o= this->x;
      for(i = 0; i < size; i++)
            o[i]= gfloat(0);

  }

};


void  mlp_Matrix( gmatrix &ret, const gmatrix &m1,  const  gmatrix &m2)
{
   
 #ifdef _DEBUG  
    if (m1.col != m2.row){
        std::cout <<"mlp_matrix (col1 != row2) !!\n";
        return; 
        }
#endif

   unsigned short i,j,k;
   const unsigned short row1 = m1.row,col1 =m1.col,col2 =m2.col;
   
   ret.resize(row1,col2,gfloat(0));

   std::vector <gfloat> &r = ret.x;
   const std::vector <gfloat> &o= m1.x;
   const std::vector <gfloat> &t= m2.x;
    for(i = 0; i < row1; i++) {
        for(j = 0; j < col2; j++) {
            for(k = 0; k <col1; k++) {
                r[(i *col2) + j] += o[(i *col2) +k] * t[(k*col2) +j];
            }
        }
    }
}

void printMatrix(gmatrix  &m)
{
    for(auto i = 0; i < m.row; ++i) {
        for(auto j = 0; j < m.col; ++j) {
            std::cout << std::setw(5) << m.x[(i* m.col )+j] << "; ";
        }
        std::cout << std::endl;
    }
}

#endif