#include"mylist.h"
using namespace DSL;

void DSL::insertTest()
{
    list<char> L;
    L.insert(L.end(), 'A');
    L.insert(L.end(), 'B');
    L.insert(L.end(), 'C');
    L.insert(L.end(), 'D');
    L.insert(L.end(), 'E');
    L.push_back('F');
    L.push_front('Z');
    auto it = L.begin();
    assert(*it == 'Z');
    ++it;
    assert(*it = 'A');
    ++it;
    assert(*it = 'B');   
    ++it;
    assert(*it = 'B');
    ++it;
    assert(*it = 'C');
    ++it;
    assert(*it = 'D');
    ++it;
    assert(*it = 'E');
    ++it;
    assert(*it = 'F');

/*  000001BFDB915C20 DNode : A
        000001BFDB915500 DNode :
        000001BFDB9158C0 DNode : B
      000001BFDB9158C0 DNode : B
        000001BFDB915C20 DNode : A
        000001BFDB915020 DNode : C
      000001BFDB915020 DNode : C
        000001BFDB9158C0 DNode : B
        000001BFDB915140 DNode : D
      000001BFDB915140 DNode : D
        000001BFDB915020 DNode : C
        000001BFDB915F20 DNode : E
      000001BFDB915F20 DNode : E
        000001BFDB915140 DNode : D
        000001BFDB915500 DNode :
        000001BFDB915500 DNode          has been free
        000001BFDB915C20 DNode  A       has been free
        000001BFDB9158C0 DNode  B       has been free
        000001BFDB915020 DNode  C       has been free
        000001BFDB915140 DNode  D       has been free
        000001BFDB915F20 DNode  E       has been free
*/
}
void DSL::copyconstructTest()
{
    list<char> L;
    L.push_back('A');
    L.push_back('B');
    L.push_back('C');
    L.push_back('D');
    L.push_back('E');
    list<char>newL = L;
    L.visit();
    std::cout << "\n";
    newL.visit();
    //结果
   /* 0000020D5C2F5380 DNode : A
        0000020D5C2F6100 DNode :
        0000020D5C2F5560 DNode : B
      0000020D5C2F5560 DNode : B
        0000020D5C2F5380 DNode : A
        0000020D5C2F59E0 DNode : C
      0000020D5C2F59E0 DNode : C
        0000020D5C2F5560 DNode : B
        0000020D5C2F5800 DNode : D
      0000020D5C2F5800 DNode : D
        0000020D5C2F59E0 DNode : C
        0000020D5C2F5F80 DNode : E
      0000020D5C2F5F80 DNode : E
        0000020D5C2F5800 DNode : D
        0000020D5C2F6100 DNode :

      0000020D5C2F5B60 DNode : A
        0000020D5C2F5F20 DNode :
        0000020D5C2F5FE0 DNode : B
      0000020D5C2F5FE0 DNode : B
        0000020D5C2F5B60 DNode : A
        0000020D5C2F6040 DNode : C
      0000020D5C2F6040 DNode : C
        0000020D5C2F5FE0 DNode : B
        0000020D5C2F6160 DNode : D
      0000020D5C2F6160 DNode : D
        0000020D5C2F6040 DNode : C
        0000020D5C2F5860 DNode : E
      0000020D5C2F5860 DNode : E
        0000020D5C2F6160 DNode : D
        0000020D5C2F5F20 DNode :
        0000020D5C2F5F20 DNode          has been free
        0000020D5C2F5B60 DNode  A       has been free
        0000020D5C2F5FE0 DNode  B       has been free
        0000020D5C2F6040 DNode  C       has been free
        0000020D5C2F6160 DNode  D       has been free
        0000020D5C2F5860 DNode  E       has been free
        0000020D5C2F6100 DNode          has been free
        0000020D5C2F5380 DNode  A       has been free
        0000020D5C2F5560 DNode  B       has been free
        0000020D5C2F59E0 DNode  C       has been free
        0000020D5C2F5800 DNode  D       has been free
        0000020D5C2F5F80 DNode  E       has been free
        */
}
void DSL::equalTest()
{
    list<char> L;
    L.push_back('A');
    L.push_back('B');
    L.push_back('C');
    L.push_back('D');
    L.push_back('E');
    list<char>newL;
    newL = L;
    newL.visit();
    //结果 :
    /*  000001EBE98142F0 DNode : A
        000001EBE9814B90 DNode :
    000001EBE9814D70 DNode : B
        000001EBE9814D70 DNode : B
        000001EBE98142F0 DNode : A
        000001EBE9814410 DNode : C
        000001EBE9814410 DNode : C
        000001EBE9814D70 DNode : B
        000001EBE98140B0 DNode : D
        000001EBE98140B0 DNode : D
        000001EBE9814410 DNode : C
        000001EBE9814D10 DNode : E
        000001EBE9814D10 DNode : E
        000001EBE98140B0 DNode : D
        000001EBE9814B90 DNode :
    000001EBE9814B90 DNode          has been free
        000001EBE98142F0 DNode  A       has been free
        000001EBE9814D70 DNode  B       has been free
        000001EBE9814410 DNode  C       has been free
        000001EBE98140B0 DNode  D       has been free
        000001EBE9814D10 DNode  E       has been free
        000001EBE9814BF0 DNode          has been free
        000001EBE98143B0 DNode  A       has been free
        000001EBE9814F50 DNode  B       has been free
        000001EBE9814CB0 DNode  C       has been free
        000001EBE9814B30 DNode  D       has been free
        000001EBE98147D0 DNode  E       has been free*/
}
void DSL::nonparameterconstructorTest()
{
    list<char>L;
}
void DSL::initializer_listconstructorTest()
{
    list<char>L = { 'A','B','C','D','E'};
    L.visit();

}
void DSL::deleteTest()
{
    list<char>L = { 'A','B','C','D','E' };
    L.pop_back();
    L.pop_front();
    L.visit();
}
void DSL::reverseTest()
{
    list<char>L = { 'A','B','C','D','E' };
    L.reverse();
    L.pop_back();
    L.pop_front();
    //D C B;
    auto it = L.begin();
    assert(*it == 'D');
    ++it;
    assert(*it == 'C');
    ++it;
    assert(*it == 'B');
    ++it;
}