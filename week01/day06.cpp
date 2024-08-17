//
// Created by 李勃鋆 on 24-8-17.
//
#include "../week01.h"
class Points{
private:
    int _ix;
    int _iy;
public:
    Points():_ix(0),_iy(0){}
    Points(int ix,int iy=0):_ix(ix),_iy(iy){}
    void toString(){
        std::cout<<_ix<<","<<_iy<<std::endl;
    }
};

void test_06_01(){
    
}
