#include"LinkList.h"
using namespace DSL;
void DSL::insertTest()
{
	list<char> L;
	L.insert(0, 'A');
	L.insert(0, 'B');
	L.insert(0, 'C');
	L.insert(0, 'D');
	L.insert(0, 'E');
    L.push_back('F');
    L.push_back('G');
    L.visit();
    //结果:
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