#ifndef _GENETIC
#define _GENETIC

#define USE_HALF_GFLOAT 1

// How to use :
/* 
#define num_w 3
float goel = 25;
struct Solution 
{  
    float rank;
    float x[num_w];

    float result() { return  (6*x[0]+ - x[1]+std::pow(x[2],200));  } 
    
    void fitness()
    {
        //wie müssen x[0]...x[n-1] aussehen damit ans 0 wird
        float ans=result() -goel;
        rank = (ans==0) ? 9999999 :std::abs(1/ans);
    }
}; 



int main()
{
    std::vector <Solution>solutions;
    Genetic<Solution>(solutions,num_w);

    return 0;
}
*/


#include <math.h>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>






#ifndef USE_HALF_GFLOAT
     typedef float gfloat;
#else
    #include "../half/half.hpp"
    using half_float::half;
    typedef half gfloat;
#endif


std::random_device dev;


template <class T>
inline void Initial ( std::vector <T> &solu,const int &num_w,const int & NUM)
{
 std::uniform_real_distribution<float> unif(-1,1);
 T tmp;

  for (int i =0; i <NUM;i++){
    for(int h=0;h<num_w;h++)
            tmp.x[h] =unif(dev);
    
    solu.push_back(tmp);
    }
}

template <class T>
inline void Sort_by_Fitness(std::vector <T> &solu)
{


               //#pragma omp parallel for
               for(auto& s:solu){s.fitness();}
                
               /*
                  for(int i = 0;i< solu.size() ;i++)
                          solu[i].fitness();
                */ 

                std::sort(solu.begin(),solu.end(),[](const auto & lhs,const auto & rhs){
                    return  lhs.rank>rhs.rank;
                });

}

template <class T>
inline void Print_Best_10(std::vector <T> &solu,int ep,time_t &begin )
{
                std::cout <<"Epoche :" << ep<<  " : " <<  solu[0].result()  << " T : "<<(double)(clock()- begin) / CLOCKS_PER_SEC  <<"\n";
                std::for_each(solu.begin(),solu.begin()+10,[](const auto &s){
                    std::cout <<"rank :" << s.rank <<"\n";
                });
                

      
}
template <class T>
inline void Copy_Sampel_and_Clean_Solution(std::vector <T> &solu,std::vector<T> &sample,const int  &sample_size )
{

        sample.resize(0); 
            std::copy(solu.begin(),solu.begin() +sample_size,std::back_inserter(sample));
        solu.resize(0);
            
            
}
template <class T>
inline void Mutation( std::vector<T> &sample,const int &num_w,const int  &keep_best,const double &rate )
{
            // mutation
            std::uniform_real_distribution<double> m(1.0 - rate ,1.0+rate);
             //#pragma omp parallel for
                std::for_each(sample.begin()+ keep_best,sample.end(),[&](auto& s){
                    for(int i =0; i<num_w;i++)
                         s.x[i] *=m(dev);
                });

}
template <class T>
inline void Crossover(std::vector <T> &solu,int &num_w,int &NUM,std::vector<T> &sample,const int  &keep_best )
{
         T tmp;
          tmp.rank =0;
            for(int i=0;i< keep_best; i++){
                solu.push_back(sample[i]);
            }

            std::uniform_int_distribution<int> cross(0,sample.size() -1);

           //#pragma omp for
            for(int i=keep_best;i< NUM; i++){
                for(int h=0;h<num_w;h++)
                    tmp.x[h] =sample[cross(dev)].x[h];
                 solu.push_back(tmp);
            }
}


template <class T>
void Genetic (std::vector <T>&solutions, int num_w,int epochen =80,double mutation_rate =0.01, int solu_size = 100000,  int sample_size =1000,int keep_best =4)
{
clock_t begin = clock();
std::vector <T>sample;
Initial<T> (solutions,num_w,solu_size);

 for(int ep =  0; ep < epochen;ep++)
    {
        
        Sort_by_Fitness<T>(solutions);

        Print_Best_10<T>(solutions,ep,begin);

        if(solutions[0].result() ==0){
           std::cout << "Perfect!\n";
           ep = epochen;
           return;
        }

        Copy_Sampel_and_Clean_Solution<T>(solutions,sample,sample_size );
        
        Mutation<T>(sample,num_w,keep_best,mutation_rate);

        Crossover<T>(solutions,num_w,solu_size,sample,keep_best);

    }


}

#endif



