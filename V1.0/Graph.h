#pragma once
#include"Define.h"

/*---------------------------------Graph.h--------------------------------*/
//邻接矩阵
typedef struct
{
	ElemType	vexs[MAXSIZE];//图的顶点表
	int			arcs[MAXSIZE][MAXSIZE];//图的边表
	int			VertexNum;//图的顶点数
	int			ArcNum;//图的边数
}AMGraph;//Adjacency Martrix Graph//邻接矩阵

#pragma region 邻接矩阵的使用场景
//用于稠密图即V>ElogE时
//空间复杂度O(n^2)
#pragma endregion
 





/*---------------------------------Graph.h--------------------------------*/
//邻接表

typedef struct ArcNode
{
	int			adjvex;//当前边邻接的顶点在数组当中的下标
	int			info;//当前边的权值
	ArcNode		*nextarc;//指向下一条边的指针
};//边结点

typedef struct VNode//顶点结点
{
	ElemType	data;//当前顶点的值
	ArcNode		* firstarc;//指向其第一条边的指针
}VNode, AdjList[MAXSIZE];

typedef struct//邻接表
{
	AdjList vertices;//图的顶点表
	int		VertexNum;//图顶点数
	int		ArcNum;//图的边数
}ALGraph;
#pragma region 链式邻接表的特点及使用场景
//方便找任意顶点的邻接点
//需要N个头指针与2E个边结点
//对于无向图来说非常方便计算节点的度
//对于有向图来说难以计算节点的度
//常用于稀疏图
//空间复杂度O(n+e)
#pragma endregion


/*---------------------------------Graph.h--------------------------------*/
typedef struct
{
	ElemType	data[MAXSIZE];
	int			front,
				rear;
}Queue;
typedef struct
{
	int data[MAXSIZE];
	int base,
		top;
}Stack;
/*---------------------------------Graph.h--------------------------------*/
typedef struct
{
	int data[2][MAXSIZE];
	int base,
		top;
}EdgeStack;
/*---------------------------------Graph.h--------------------------------*/
//简单算法
//构建无向网
bool CreateUDN			(AMGraph &G);
//打印无向图的顶点表vexs,边表arcs[][]
void Print				(AMGraph G);
//查找值为u的第一个顶点在图的顶点表当中的下标
unsigned int LocateVex	(AMGraph G, ElemType u);
//采用邻接表构建无向网
bool CreateUDN			(ALGraph &G);
//查找值为u的顶点在图的顶点表当中的下标
unsigned int LocateVex	(ALGraph G, ElemType u);
//
void Print				(ALGraph G);
//
bool Init				(ArcNode** arcnode);
//得到顶点v的第一个邻接顶点的下标
int FirstNeighbor		(AMGraph G, int v);
int FirstNeighbor		(ALGraph G, int v);
//得到边<v,w>的下一条边的顶点下标
int NextNeighbor		(AMGraph G, int v,int w);
int NextNeighbor		(ALGraph G, int v, int w);
void Init				(AMGraph &G,int V);
/*---------------------------------Graph.h--------------------------------*/
//深度优先搜索
void DFS				(AMGraph G,ElemType firstvertex);
//搜索的具体实现
void Search				(AMGraph G, ElemType vertex, bool IsVisit[]);

//访问操作
void visit				(ElemType vertex);
/*---------------------------------Graph.h--------------------------------*/
//广度优先搜索
void BFS				(ALGraph G, ElemType firstvertex);
//初始化队列
void Init				(Queue& Q);
//入队
bool EnQueue			(Queue &Q, ElemType e);
//出队
bool DeQueue			(Queue &Q, ElemType& e);
//判断队是否为空
bool IsEmpty			(Queue Q);
/*---------------------------------Graph.h--------------------------------*/
//最小生成树
//Prim
void Prim				(AMGraph G,char u,AMGraph& MinTree);
//Kruskal
void Kruskal			(AMGraph G,AMGraph& MinTree);

/*---------------------------------Graph.h--------------------------------*/
//最短路径
//int Dijkstra(AMGraph G,char src,char dst);
int Dijkstra			(AMGraph G, ElemType src, ElemType dst);
int Floyd				(AMGraph G, char src, char dst);
/*---------------------------------Graph.h--------------------------------*/
//拓扑排序
bool TopologicalSort	(ALGraph G);
bool Init				(Stack& S);
bool Push				(Stack& S, int e);
bool Pop				(Stack& S, int& e);
bool IsEmpty			(Stack S);
/*---------------------------------Graph.h--------------------------------*/
//关键路径(待完成)
void CriticalPath		(ALGraph G);
/*---------------------------------Graph.h--------------------------------*/
//判断图G是否存在边<x,y>
bool IsAdjacent			(AMGraph G, ElemType x, ElemType y);
/*---------------------------------Graph.h--------------------------------*/
//408
void ALGraphTransToAMGraph(ALGraph src,AMGraph &dst);
//找vi->vj的简单路径
void FindEasyPathFromvitovj(ALGraph G, int i, int j);
void DFS				(ALGraph G, int i, int j, bool IsVisit[], Stack& S);
//使用DFS进行拓扑排序
bool DFSTopologicalSort	(ALGraph G);
void DFS				(ALGraph G, int i, int ID[]);
//判断图的拓扑排序是否唯一
bool Uniquely			(AMGraph G);
























































































