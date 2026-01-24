#include"Graph.h"

void Init(AMGraph& G)
{
	for (int i = 0; i < MAX_GRAPH_LENGTH; i++)
	{
		G.vetices[i] = '*';//不存在顶点
		
		for(int i=0;i<MAX_GRAPH_LENGTH;i++)
			for (int j = 0; j < MAX_GRAPH_LENGTH; j++)
			{
				G.arcs[i][j] = MAXSIZE;
			}
		for (int j = 0; j < MAX_GRAPH_LENGTH; j++)
		{
			G.arcs[i][i] = 0;//不存在边
		}
	}
	G.ArcsNum = G.VertexNum = 0;
}

void Init(ALGraph& G)
{
	for (int i = 0; i < MAX_GRAPH_LENGTH; i++)
	{
		G.vertices[i].data = '*';
		G.vertices[i].FirstArc = NULL;
	}
	G.ArcsNum = G.VertexNum = 0;
}

void AMDFS(AMGraph G, int start_pos)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	if (IsVisit == NULL)return;
	for (int i = 0; i < G.VertexNum; i++)IsVisit[i] = false;
	DFS(G, start_pos, IsVisit);
	
}
void DFS(AMGraph G, int start_pos, bool* IsVisit)
{
	visit(G.vetices[start_pos]);
	IsVisit[start_pos] = true;
	for (int i = 0; i < G.VertexNum; i++)
		if (
			G.arcs[start_pos][i] != 0 
			&& G.arcs[start_pos][i] != MAXSIZE
			&& IsVisit[i] == false)
		{
			DFS(G, i,IsVisit);
		}
}
void visit(VertexType vertex)
{
	cout << (char)vertex << " ";
}


void ALDFS(ALGraph G, int start_pos)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	if (IsVisit == NULL)return;
	for (int i = 0; i < G.VertexNum; i++)IsVisit[i] = false;
	DFS(G, start_pos, IsVisit);
}

void DFS(ALGraph G, int start_pos, bool* IsVisit)
{
	visit(G.vertices[start_pos].data);
	IsVisit[start_pos] = true;
	ArcNode* p = G.vertices[start_pos].FirstArc;
	while (p)
	{
		if(IsVisit[p->val]==false)
			DFS(G, p->val, IsVisit);
		p = p->next;
	}
}

void Init(ArcNode **node)
{
	(*node) = (ArcNode*)malloc(sizeof(ArcNode));
	(*node)->next = NULL;
	(*node)->val = 0;
}

void AMBFS(AMGraph G, int start_pos)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	if (IsVisit == NULL)return;
	for (int i = 0; i < G.VertexNum; i++)IsVisit[i] = false;
	Queue Q;
	Init(Q);
	BFS(G, start_pos, IsVisit,Q);
}

void BFS(AMGraph G, int start_pos, bool* IsVisit,Queue &Q)
{
	EnQueue(Q, start_pos);
	IsVisit[start_pos] = true;
	while (!IsEmpty(Q))
	{
		int row;
		DeQueue(Q, row);
		visit(G.vetices[row]);

		for (int col = 0; col < G.VertexNum; col++)
			if (
				G.arcs[row][col] != 0
				&& G.arcs[row][col] != MAXSIZE
				&& IsVisit[col] == false
				)
			{
				IsVisit[col] = true;
				EnQueue(Q, col);
			}
	}
}

bool Init(ArcQueue& Q)
{
	Q.data = (ArcNode**)malloc(MAXSIZE*sizeof(ArcNode*));
	Q.front = Q.rear = 0;
	if(Q.data)
	return true;
	return false;
}

bool IsEmpty(ArcQueue Q)
{
	if (Q.front == Q.rear)return true;
	return false;
}

bool IsFull(ArcQueue Q)
{
	if ((Q.rear + 1) % MAXSIZE == Q.front)
		return true;
	return false;
}

bool EnQueue(ArcQueue& Q,ArcNode*node)
{
	if (IsFull(Q))return false;
	Q.data[Q.rear++] = node;
	Q.rear %= MAXSIZE;
	return true;
}

bool DeQueue(ArcQueue& Q, ArcNode** node)
{
	if (IsEmpty(Q))return false;
	*node = Q.data[Q.front++];
	Q.front %= MAXSIZE;
	return true;
}

bool Init(Queue& Q)
{
	Q.data = (int*)malloc(MAXSIZE * sizeof(int));
	Q.front = Q.rear = 0;
	if (Q.data)
		return true;
	return false;
}

bool IsEmpty(Queue Q)
{
	if (Q.front == Q.rear)return true;
	return false;
}

bool IsFull(Queue Q)
{
	if ((Q.rear + 1) % MAXSIZE == Q.front)
		return true;
	return false;
}

bool EnQueue(Queue& Q, int input)
{
	if (IsFull(Q))return false;
	Q.data[Q.rear++] = input;
	Q.rear %= MAXSIZE;
	return true;
}

bool DeQueue(Queue& Q, int& output)
{
	if (IsEmpty(Q))return false;
	output = Q.data[Q.front++];
	Q.front %= MAXSIZE;
	return true;
}

void ALBFS(ALGraph G, int start_pos)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	if (IsVisit == NULL)return;
	for (int i = 0; i < G.VertexNum; i++)IsVisit[i] = false;
	Queue Q;
	Init(Q);
	BFS(G, start_pos, IsVisit, Q);
}

void BFS(ALGraph G, int start_pos, bool* IsVisit, Queue& Q)
{
	EnQueue(Q, start_pos);
	IsVisit[start_pos] = true;
	while (!IsEmpty(Q))
	{
		int output;
		DeQueue(Q, output);
		visit(G.vertices[output].data);
		ArcNode* p = G.vertices[output].FirstArc;
		while (p)
		{
			if (IsVisit[p->val] == false)
			{
				IsVisit[p->val] = true;
				EnQueue(Q, p->val);
			}
			p = p->next;
		}
	}
}

void Prim(AMGraph G, AMGraph &minCreateTree)
{
	minCreateTree.ArcsNum = G.VertexNum-1;//找n-1条边
	minCreateTree.VertexNum = G.VertexNum;//复制顶点数
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	for (int i = 0; i < G.VertexNum; i++)
	{
		minCreateTree.vetices[i] = G.vetices[i];//复制顶点表
		IsVisit[i] = false;
	}
	IsVisit[0] = true;//从第一个顶点开始找
	for (int i = 0; i < G.VertexNum - 1; i++)//要找顶点数-1次
	{
		int dst = -1;//新边的终点
		int MinArc = MAXSIZE;//边的权值
		int src= -1;//新边的起点
		for (int j = 0; j < G.VertexNum; j++)
			if (IsVisit[j] == true)
				for (int k = 0; k < G.VertexNum; k++)
					if (
						IsVisit[k] == false
						&& G.arcs[j][k] != 0
						&& G.arcs[j][k] != MAXSIZE
						)
					{
						if (MinArc > G.arcs[j][k])
						{
							MinArc = G.arcs[j][k];
							dst = k;
							src = j;
						}
					}
		IsVisit[dst] = true;//把顶点加入最小树
		minCreateTree.arcs[src][dst] = MinArc;
	}
}

void Print(AMGraph G)
{
	for (int i = 0; i < G.VertexNum; i++)
	{
		for (int j = 0; j < G.VertexNum; j++)
		{
			cout << G.arcs[i][j] << "   ";
		}
		cout << endl;
	}
		
}

int Dijkstra(AMGraph G, int src, int dst)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));//记录每个顶点是否访问过
	int* Dist = (int*)malloc(G.VertexNum * sizeof(int));//原点到每个顶点的最短距离
	int* parent = (int*)malloc(G.VertexNum * sizeof(int));//从原点到该顶点的前驱顶点位置
	for (int i = 0; i < G.VertexNum; i++)
	{
		IsVisit[i] = false;
		Dist[i] = MAXSIZE;
		parent[i] = i;
	}//初始化各数组
	//访问源顶点
	IsVisit[src] = true;
	Dist[src] = 0;
	for (int i = 0; i < G.VertexNum; i++)
		if (G.arcs[src][i] != 0 && G.arcs[src][i] != MAXSIZE)
		{
			Dist[i] = G.arcs[src][i];
			parent[i] = src;
		}//把源顶点加入已经访问的顶点
		


	for (int i = 0; i < G.VertexNum - 1; i++)
	{
		int min_dist_point = -1;
		int min_dist = MAXSIZE;//到原点的最小距离
		for (int j = 0; j < G.VertexNum; j++)
		{
			if (IsVisit[j] == false&&Dist[j]<min_dist)//找到距离原点最短，并且没有访问过的节点min_dist_point
			{
				min_dist = Dist[j];
				min_dist_point = j;
			}
		}//找到与原点最近，并且没有访问过的顶点
		IsVisit[min_dist_point] = true;//访问该节点
		for (int j = 0; j < G.VertexNum; j++)
		{
			if (Dist[min_dist_point] + G.arcs[min_dist_point][j] < Dist[j])
			{
				Dist[j] = Dist[min_dist_point] + G.arcs[min_dist_point][j];
				parent[j] = min_dist_point;
			}
		}
	}
	return Dist[dst];
}

int Floyd(AMGraph G, int src, int dst)
{
	for (int i = 0; i < G.VertexNum; i++)
		for (int j = 0; j < G.VertexNum; j++)
			for (int k = 0; k < G.VertexNum; k++)
				if (G.arcs[i][j] + G.arcs[i][k] < G.arcs[j][k])
					G.arcs[j][k]=G.arcs[i][j] + G.arcs[i][k] ;
	return G.arcs[src][dst];

}