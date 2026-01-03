#include"Graph.h"

bool CreateUDN(AMGraph &G)
{
	printf("请输入顶点数VertexNum与边数ArcNum:\n");
	scanf("%d%d", &G.VertexNum, &G.ArcNum);
	printf("顶点VertexNum为:%d,边数ArcNum为:%d\n", G.VertexNum, G.ArcNum);
	//Init(martrix)
	printf("请输入顶点表信息:\n");
	for (unsigned int i = 0; i < G.VertexNum; i++)scanf("%c", &G.vexs[i]);
	for (unsigned int i = 0; i < G.VertexNum; i++)
		for (unsigned int j = 0; j < G.VertexNum; j++)
			G.arcs[i][j] = MAX_INT_16;
	//arcsList
	for (unsigned int k = 0; k < G.ArcNum; k++)
	{
		printf("请输入任意两个顶点与他们之间的权值:\n");
		unsigned int v1, v2;
		int weight=0;
		scanf("%d%d%d", &v1, &v2, &weight);
		unsigned int i = LocateVex(G, v1);
		unsigned int j = LocateVex(G, v2);
		G.arcs[i][j] = weight;
	}
	for(unsigned int i=0;i<G.VertexNum;i++)
		for (unsigned int j = i + 1; j < G.VertexNum; j++)
		{
			G.arcs[j][i] = G.arcs[i][j];
		}

	Print(G);

	return true;
}



void Print(AMGraph G)
{
	cout << "顶点表:";
	for (int i = 0; i < G.VertexNum; i++)
		printf("%C ", G.vexs[i]);
	cout << endl;
	cout << "边表:" << endl;
	printf("%-10s ","顶点/顶点");
	for (int i = 0; i < G.VertexNum; i++)
		printf("%-10c ", G.vexs[i]);
	cout << endl;
	for (int i = 0; i < G.VertexNum; i++)
	{
		printf("%-10c ", G.vexs[i]);
		for (int j = 0; j < G.VertexNum; j++)
		{
			printf("%-10d ", G.arcs[i][j]);
		}
		cout << endl;
	}
		
}


unsigned int LocateVex(AMGraph G, ElemType u)
{
	int i;
	for (i = 0; i < G.VertexNum; i++)
		if (G.vexs[i] == u)return i;
	return -1;
}

bool CreateUDN(ALGraph &G)
{
	printf("请输入顶点数VertexNum与边数ArcNum:\n");
	scanf("%d%d", &G.VertexNum, &G.ArcNum);
	printf("顶点VertexNum为:%d,边数ArcNum为:%d\n", G.VertexNum, G.ArcNum);
	getchar();//读取'\'
	
	printf("请输入顶点表信息:\n");
	for (int i = 1; i <= G.VertexNum; i++)//输入顶点表
	{
		scanf("%c", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}

	char ch=getchar();//读取'\'
	if (ch != '\n')return false;
	printf("请输入边表信息:\n");
	for (int k = 0; k < G.ArcNum; k++)
	{
		ElemType v1 = 0;
		ElemType v2 = 0;
		scanf("%c%c", &v1, &v2);
		char ch = getchar();
		if (ch != '\n')return false;//读取'\'
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcNode* NewArc = (ArcNode*)malloc(sizeof(ArcNode));
		if (NewArc == NULL)return false;
		NewArc->adjvex = j;
		NewArc->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = NewArc;
		NewArc = (ArcNode*)malloc(sizeof(ArcNode));
		if (NewArc == NULL)return false;
		NewArc->adjvex = i;
		NewArc->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = NewArc;
	}
	return true;
}

unsigned int LocateVex(ALGraph G, ElemType u)
{
	for (unsigned int i = 1; i <=G.VertexNum; i++)
		if (G.vertices[i].data == u)return i;
	return 0;
}


void Print(ALGraph G)
{
	for (int i = 0; i < G.VertexNum; i++)
	{
		printf("%d:顶点%c--->",i, G.vertices[i].data);
		ArcNode* p = G.vertices[i].firstarc;
		while (p)
		{
			printf("%d--->", p->adjvex);
			p = p->nextarc;
		}
		printf("^ \n");
	}

}

void DFS(AMGraph G, ElemType firstvertex)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	for (int i = 0; i < G.VertexNum; i++)IsVisit[i] = false;
	Search(G, firstvertex, IsVisit);
	for (int i = 0; i < G.VertexNum; i++)
		if (IsVisit[i] == false)
			Search(G, G.vexs[i], IsVisit);
}

void Search(AMGraph G, ElemType vertex, bool IsVisit[])
{
	visit(vertex);
	int i = LocateVex(G, vertex);
	IsVisit[i] = true;
	for (int j = 0; j < G.VertexNum; j++)
		if (G.arcs[i][j] != 0 && IsVisit[j] == false)
			Search(G, G.vexs[j], IsVisit);
}

void visit(ElemType vertex)
{
	printf("%c ", vertex);
}

bool IsAdjacent(AMGraph G, ElemType x, ElemType y)
{
	unsigned int X = LocateVex(G, x);
	unsigned int Y = LocateVex(G, y);
	if (G.arcs[X][Y] == 0 || G.arcs[X][Y] == MAX_INT_16)
		return false;
	return true;
}


void ALGraphTransToAMGraph(ALGraph src, AMGraph &dst)
{
	dst.ArcNum = src.ArcNum;
	dst.VertexNum = src.VertexNum;
	
	for (int i = 0; i < src.VertexNum; i++)
	{
		dst.vexs[i] = src.vertices[i].data;
		ArcNode* ptr = src.vertices[i].firstarc;
		while (ptr)
		{
			dst.arcs[i][ptr->adjvex] = ptr->info;
			ptr = ptr->nextarc;//指向下一条边
		}
		dst.arcs[i][i] = 0;
	}

}

void BFS(ALGraph G,ElemType firstvertex)
{
	Queue Q;
	Init(Q);
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	for (int i = 0; i < G.VertexNum; i++)IsVisit[i] = false;
	EnQueue(Q, firstvertex);
	ElemType vertex;
	while (!IsEmpty(Q))
	{
		DeQueue(Q,vertex);
		visit(vertex);
		int i = LocateVex(G, vertex);
		IsVisit[i] = true;
		ArcNode* ptr = G.vertices[i].firstarc;
		while (ptr)
		{
			if (IsVisit[ptr->adjvex] == false)
				EnQueue(Q, G.vertices[ptr->adjvex].data);
			ptr = ptr->nextarc;
		}
	}
	for (int i = 0; i < G.VertexNum; i++)
		if (IsVisit[i] == false)
			BFS(G, G.vertices[i].data);
}

void Init(Queue& Q)
{
	Q.front = Q.rear = 0;
}


bool EnQueue(Queue& Q, ElemType e)
{
	if (Q.rear == MAXSIZE)return false;
	Q.data[Q.rear++] = e;
	return true;
}
bool DeQueue(Queue& Q, ElemType& e)
{
	if (Q.front == Q.rear)return false;//队列空
	e = Q.data[Q.front++];
	return true;
}

bool IsEmpty(Queue Q)
{
	if (Q.front == Q.rear)return true;
	return false;
}


void Prim(AMGraph G,char u, AMGraph& MinTree)//最小生成树
{
	MinTree.ArcNum = 0;
	MinTree.VertexNum = G.VertexNum;
	bool* visit = (bool*)malloc(G.VertexNum * sizeof(bool));
	if (visit == NULL)return;
	for (int i = 0; i < G.VertexNum; i++)
		for (int j = 0; j < G.VertexNum; j++)
			MinTree.arcs[i][j] = 0;
	for (int i = 0; i < G.VertexNum; i++)
	{
		MinTree.vexs[i] = G.vexs[i];//复制顶点表
		visit[i] = false;//所有顶点都没访问过
	}
	visit[LocateVex(G, u)] = true;
	for (int i = 0; i < G.VertexNum - 1; i++)//依次加入四个顶点
	{
		int min_weight = MAX_INT_16;
		int min_x=-1,min_y=-1;
		for(int j=0;j<G.VertexNum;j++)
			if(visit[j]==true)//在已经访问的节点当中
				for (int k = 0; k < G.VertexNum; k++)
					if (visit[k]==false
						&&G.arcs[j][k] < min_weight
						&&G.arcs[j][k]!=0
						)//在没有访问的节点当中
					{
						min_weight = G.arcs[j][k];
						min_x = j;
						min_y = k;
					}//在已经加入树当中的节点与没有加入树当中的节点找到权值最小的边
		visit[min_y] = true;//访问权值最小的边邻接的结点
		G.ArcNum++;
		MinTree.arcs[min_x][min_y] = MinTree.arcs[min_y][min_x] = min_weight;//最小树
	}

}

void Kruskal(AMGraph G, AMGraph& MinTree)
{
	Init(MinTree, G.VertexNum);
	for (int i = 0; i < G.VertexNum; i++)
		MinTree.vexs[i] = G.vexs[i];
	int arcs[3][1024];
	int p_arcs = 0;
	bool* visit = (bool*)malloc(G.VertexNum * sizeof(bool));
	for (int i = 0; i < G.VertexNum; i++)
		visit[i] = false;//visit数组初始化
	for(int i=0;i<G.VertexNum;i++)
		for (int j = i+1; j < G.VertexNum; j++)
		{
			if (G.arcs[i][j] != MAX_INT_16)
			{
				arcs[0][p_arcs] = G.arcs[i][j];
				arcs[1][p_arcs] = i;
				arcs[2][p_arcs] = j;
				p_arcs++;
			}
		}
	for(int i=0;i<p_arcs-1;i++)
		for (int j = i+1; j < p_arcs; j++)
		{
			if (arcs[0][i] > arcs[0][j])//
			{
				int tmp = arcs[0][i];
				arcs[0][i] = arcs[0][j];
				arcs[0][j] = tmp;
				tmp = arcs[1][i];
				arcs[1][i] = arcs[1][j];
				arcs[1][j] = tmp;
				tmp = arcs[2][i];
				arcs[2][i] = arcs[2][j];
				arcs[2][j] = tmp;
			}
		}//从小到大冒泡排序
	MinTree.ArcNum = 0;
	int p = 0;//arcs的工作指针
	while (MinTree.ArcNum != G.VertexNum - 1&&p<p_arcs)
	{
		if (!(visit[arcs[1][p]]&&visit[arcs[2][p]]))
		{
			MinTree.arcs[arcs[1][p]][arcs[2][p]] = G.arcs[arcs[1][p]][arcs[2][p]];
			MinTree.arcs[arcs[2][p]][arcs[1][p]] = G.arcs[arcs[2][p]][arcs[1][p]];
			visit[arcs[1][p]] = true;
			visit[arcs[2][p]] = true;
			MinTree.ArcNum++;
			p++;
		}
		else p++;
	}
}

int Dijkstra(AMGraph G, ElemType src, ElemType dst)
{
	int* dist = (int*)malloc(G.VertexNum * sizeof(int));
	bool* visit = (bool*)malloc(G.VertexNum * sizeof(bool));
	int* parent = (int*)malloc(G.VertexNum * sizeof(int));
	for (int i = 0; i < G.VertexNum; i++)
	{
		dist[i] = MAX_INT_16;
		visit[i] = false;
		parent[i] = i;
	}
	int p = LocateVex(G, src);
	dist[p] = 0;
	for (int i = 0; i < G.VertexNum-1; i++)
	{
		int min_dist = MAX_INT_16;
		int p_min_dist = p;
		for(int j=0;j<G.VertexNum;j++)
			if (visit[j] == false && dist[j] < min_dist)
			{
				min_dist = dist[j];
				p_min_dist = j;
			}
		visit[p_min_dist] = true;
		for (int j = 0; j < G.VertexNum; j++)
			if (G.arcs[p_min_dist][j] != 0
				&& G.arcs[p_min_dist][j] != MAX_INT_16
				&& dist[p_min_dist] + G.arcs[p_min_dist][j] < dist[j]
				)
				{
					dist[j] = dist[p_min_dist] + G.arcs[p_min_dist][j];
					parent[j] = p_min_dist;
				}
	}
	return dist[LocateVex(G, dst)];

}
void Init(AMGraph &G,int V)
{
	G.VertexNum = V;
	G.ArcNum = 0;
	for(int i=0;i<V;i++)
		for (int j = 0;j < V; j++)
		{
			if (i == j)
				G.arcs[i][j] = 0;
			else G.arcs[i][j] = MAX_INT_16;
		}
}
int Floyd(AMGraph G, char src, char dst)
{
	for (int k = 0; k < G.VertexNum; k++)//中转节点
		for(int i=0;i<G.VertexNum;i++)//起始节点
			if(i!=k)
			for (int j = 0; j < G.VertexNum; j++)//目标节点
			{
				if (G.arcs[i][k] + G.arcs[k][j] < G.arcs[i][j])
					G.arcs[i][j] = G.arcs[i][k] + G.arcs[k][j];
			}
	return G.arcs[LocateVex(G, src)][LocateVex(G, dst)];
}

bool TopologicalSort(ALGraph G)
{
	//int* indegree = (int*)malloc(G.VertexNum * sizeof(int));
	//for (int i = 0; i < G.VertexNum; i++)
	//	indegree[i] = 0;
	//Stack S;
	//Init(S);
	//for (int i = 0; i < G.VertexNum; i++)
	//{
	//	ArcNode* p = G.vertices[i].firstarc;
	//	while (p)
	//	{
	//		indegree[p->adjvex]++;
	//		p = p->nextarc;
	//	}
	//}
	//for (int i = 0; i < G.VertexNum; i++)
	//{
	//	if (indegree[i] == 0)
	//		Push(S, i);
	//}
	//int count = 0;//用于统计输出的顶点数
	//while (IsEmpty(S) == false)
	//{
	//	int i;
	//	Pop(S,i);
	//	printf("%c ", G.vertices[i].data);
	//	count++;
	//	ArcNode* p = G.vertices[i].firstarc;
	//	while (p)
	//	{
	//		indegree[p->adjvex]--;
	//		if (indegree[p->adjvex] == 0)
	//			Push(S, p->adjvex);
	//		p = p->nextarc;
	//	}
	//}
	//if (count != G.VertexNum)
	//{
	//	cout << "此有向图有环" << endl;
	//	return false;
	//}
	//return true;
	int* ID = (int*)malloc(G.VertexNum * sizeof(int));
	for (int i = 0; i < G.VertexNum; i++)
		ID[i] = 0;
	for (int i = 0; i < G.VertexNum; i++)
	{
		ArcNode* p = G.vertices[i].firstarc;
		while (p)
		{
			ID[p->adjvex]++;
			p = p->nextarc;
		}
	}
	Stack S;
	Init(S);
	for (int i = 0; i < G.VertexNum; i++)
		if (ID[i] == 0)Push(S, i);
	int count = 0;
	while (!IsEmpty(S))
	{
		//visit
		int i;
		Pop(S, i);
		printf("%c ", G.vertices[i].data);
		count++;
		ArcNode* p = G.vertices[i].firstarc;
		while (p)
		{
			ID[p->adjvex]--;
			if (ID[p->adjvex] == 0)
				Push(S, p->adjvex);
			p = p->nextarc;
		}
	}
	if (count == G.VertexNum)return true;
	return false;
}

bool Init(ArcNode** arcnode)
{
	(*arcnode) = (ArcNode*)malloc(sizeof(ArcNode));
	if (*arcnode)
	{
		(*arcnode)->nextarc = NULL;
		return true;
	}
	return false;
}

bool Init(Stack& S)
{
	S.base = S.top = 0;
	return true;
}

bool Push(Stack& S, int e)
{
	if (S.top == MAXSIZE)return false;
	S.data[S.top++] = e;
	return true;
}
bool Pop(Stack& S, int& e)
{
	if (S.base == S.top)return false;
	e = S.data[--S.top];
	return true;
}

bool IsEmpty(Stack S)
{
	if (S.base == S.top)return true;
	return false;
}



void CriticalPath(ALGraph G)
{
	int* ID = (int*)malloc(G.VertexNum * sizeof(int));//记录每个顶点的入度
	int* ve = (int*)malloc(G.VertexNum * sizeof(int));//记录抵达每个顶点的最晚时间
	int* vl = (int*)malloc(G.VertexNum * sizeof(int));//记录抵达每个顶点的最早时间
	int* e = (int*)malloc(G.ArcNum * sizeof(int));//记录每条边的最早开始时间
	int* l = (int*)malloc(G.ArcNum * sizeof(int));//记录每条边的最晚开始时间
	
}

void FindEasyPathFromvitovj(ALGraph G, int i, int j)
{
	bool* IsVisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	Stack S;
	for (int k = 0; k < G.VertexNum; k++)
		IsVisit[k] = false;
	Init(S);
	Push(S, i);
	IsVisit[i] = true;
	ArcNode* p = G.vertices[i].firstarc;
	while (p)
	{
		if (IsVisit[p->adjvex] == false)
			DFS(G,p->adjvex,j,IsVisit,S);
		p = p->nextarc;
	}
}
void DFS(ALGraph G, int i, int j, bool IsVisit[], Stack& S)
{
	Push(S, i);
	if (i == j)
	{
		for (int k = S.base; k < S.top; k++)
			printf("%c ", G.vertices[S.data[k]].data);
		printf("\n");
		
	}
	else
	{
		IsVisit[i] = true;
	}
	ArcNode* p = G.vertices[i].firstarc;
	while (p)
	{
		if (IsVisit[p->adjvex] == false)
			DFS(G, p->adjvex, j, IsVisit, S);
		p = p->nextarc;
	}
	Pop(S, i);
}
int FirstNeighbor(AMGraph G, int v)
{
	for (int i = 0; i < G.VertexNum; i++)
		if (G.arcs[v][i] != 0 && G.arcs[v][i] != MAX_INT_16)return v;
	return -1;
}
int FirstNeighbor(ALGraph G, int v)
{
	if(G.vertices[v].firstarc)
	return G.vertices[v].firstarc->adjvex;
	return -1;
}
int NextNeighbor(AMGraph G, int v, int w)
{
	for(int i=w;i<G.VertexNum;i++)
		if (G.arcs[v][i] != 0 && G.arcs[v][i] != MAX_INT_16)return v;
	return -1;
}

int NextNeighbor(ALGraph G, int v, int w)
{
	ArcNode* p = G.vertices[v].firstarc;
	while (p&&p->adjvex != w)
	{
		p = p->nextarc;
	}
	if (p)
		return p->nextarc->adjvex;
	return -1;
}

bool DFSTopologicalSort(ALGraph G)
{
	int* ID = (int*)malloc(G.VertexNum * sizeof(int));
	bool* isvisit = (bool*)malloc(G.VertexNum * sizeof(bool));
	for (int i = 0; i < G.VertexNum; i++)
		ID[i] = 0;
	for (int i = 0; i < G.VertexNum; i++)
	{
		ArcNode* p = G.vertices[i].firstarc;
		while (p)
		{
			ID[p->adjvex]++;
			p = p->nextarc;
		}
	}
	Stack S;
	Init(S);
	for (int i = 0; i < G.VertexNum; i++)
	{
		if(ID[i]==0)
		Push(S, i);
	}
	while (!IsEmpty(S))
	{
		int i;
		Pop(S, i);
		DFS(G, i, ID);
	}
	for (int i = 0; i < G.VertexNum; i++)
	{
		if (ID[i] != 0)return false;//有环
	}
	return true;
}

void DFS(ALGraph G, int i, int ID[])
{
	//visit
	printf("%c ", G.vertices[i].data);
	ArcNode* p = G.vertices[i].firstarc;
	while (p)
	{
		ID[p->adjvex]--;
		if (ID[p->adjvex] == 0)
			DFS(G, p->adjvex, ID);
		p = p->nextarc;
	}
}

bool Uniquely(AMGraph G)
{
	int* ID = (int*)malloc(G.VertexNum * sizeof(int));
	for (int i = 0; i < G.VertexNum; i++)
		ID[i] = 0;
	for (int i = 0; i < G.VertexNum; i++)
		for (int j = 0; j < G.VertexNum; j++)
			if (G.arcs[i][j] != 0 && G.arcs[i][j] != MAX_INT_16)
				ID[j]++;
	Stack S;
	Init(S);
	for (int i = 0; i < G.VertexNum; i++)
		if (ID[i] == 0)Push(S, i);
	while (!IsEmpty(S))
	{
		if (S.top - S.base > 1)return false;
		int i = 0;
		Pop(S, i);
		for (int j = 0; j < G.VertexNum; j++)
			if (G.arcs[i][j] != 0 && G.arcs[i][j] != MAX_INT_16)
			{
				ID[j]--;
				if (ID[j] == 0)
					Push(S, j);
			}
	}
	return true;

}