
#include"Tree.h"
#include"Graph.h"


int main()
{
    AMGraph G;
    Init(G);
    G.vetices[0] = 'A';
    G.vetices[1] = 'B';
    G.vetices[2] = 'C';
    G.vetices[3] = 'D';
    G.vetices[4] = 'E';
    G.VertexNum = 5;
    //A
    G.arcs[0][1] = 10;//AB
    G.arcs[0][2] = 20;//AC
    G.arcs[0][3] = MAXSIZE;
    G.arcs[0][4] = MAXSIZE;
    //B
    G.arcs[1][0] = 10;//BA
    G.arcs[1][2] = 25;//BC
    G.arcs[1][3] = MAXSIZE;
    G.arcs[1][4] = 75;//BE
    //C
    G.arcs[2][0] = 20;//CA
    G.arcs[2][1] = 25;//CB
    G.arcs[2][3] = 5;//CD
    G.arcs[2][4] = MAXSIZE;
    //D
    G.arcs[3][0] = MAXSIZE;
    G.arcs[3][1] = MAXSIZE;
    G.arcs[3][2] = 5;//DC
    G.arcs[3][4] = 35;//DE
    //E
    G.arcs[4][0] = MAXSIZE;
    G.arcs[4][1] = 75;//EB
    G.arcs[4][2] = MAXSIZE;
    G.arcs[4][3] = 35;//ED
    G.ArcsNum = 6;
    AMGraph minCreateTree;
    Init(minCreateTree);
    Prim(G, minCreateTree);
    Print(minCreateTree);
    
    cout << Dijkstra(G,0,4)<<endl;
    cout << Floyd(G, 0, 4) << endl;
    return 0;
}