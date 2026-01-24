#pragma once
#include"Define.h"



typedef struct AMGraph
{
	int arcs[MAX_GRAPH_LENGTH][MAX_GRAPH_LENGTH];//边表
	VertexType vetices[MAX_GRAPH_LENGTH];//顶点表
	int ArcsNum;//边数
	int VertexNum;//顶点数
};

typedef struct ArcNode//边节点
{
	int val;//当前边所邻接的另一顶点在顶点表当中的下表
	ArcNode* next;//下一条边
}ArcNode;

typedef struct Vertex
{
	VertexType data;
	ArcNode* FirstArc;//第一条边
}Vertex,Vertices[MAX_GRAPH_LENGTH];//顶点表


typedef struct ALGraph//邻接表
{
	Vertices vertices;//顶点表
	int ArcsNum, VertexNum;//边数，顶点数
};

typedef struct Queue
{
	int* data;
	int front, rear;
};

typedef struct ArcQueue
{
	ArcNode** data;
	int front,rear;
};



//-------------------Graph.h----------------------//

void Init		(AMGraph& G);

void Init		(ALGraph& G);

//邻接矩阵的深度优先搜索算法
void AMDFS		(AMGraph G,int start_pos);

void DFS		(AMGraph G, int start_pos,bool *IsVisit);

//邻接表的广度优先搜索算法
void ALDFS		(ALGraph G, int start_pos);

void DFS		(ALGraph G, int start_pos, bool* IsVisit);
	
//邻接矩阵的深度优先搜索算法
void AMBFS		(AMGraph G, int start_pos);
void BFS		(AMGraph G, int start_pos, bool* IsVisit, Queue& Q);
//邻接表的深度优先搜索算法
void ALBFS		(ALGraph G, int start_pos);
void BFS		(ALGraph G, int start_pos, bool* IsVisit, Queue& Q);
//-------------------Graph.h----------------------//
//Queue普通队列
bool Init		(Queue& Q);

bool IsEmpty	(Queue Q);

bool IsFull		(Queue Q);

bool EnQueue	(Queue& Q,int input);

bool DeQueue	(Queue& Q, int &output);
//-------------------Graph.h----------------------//
//ArcQueue-----边队列
bool Init		(ArcQueue& Q);

bool IsEmpty	(ArcQueue Q);

bool IsFull		(ArcQueue Q);

bool EnQueue	(ArcQueue &Q,ArcNode* node);

bool DeQueue	(ArcQueue &Q, ArcNode** node);

//-------------------Graph.h----------------------//

void visit		(VertexType vertex);

void Init		(ArcNode** node);

//-------------------Graph.h----------------------//
void Prim		(AMGraph G, AMGraph &minCreateTree);

int  Dijkstra	(AMGraph G,int src,int dst);

int Floyd		(AMGraph G,int src,int dst);

void Print		(AMGraph G);





