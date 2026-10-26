#include"Graph.h"
namespace DSL
{
//--------------------------------------------------------------------------//
/*
*		DataStruct-GenericAMGraph泛型图)
*	
*														Created by HFLY
*
*															---time:2026.5
*
*/
//--------------------------------------------------------------------------//

	template<typename type>
	AMGraph<type>::AMGraph()
	{
		//定点数和边数为0
		this->VertexNum = 0;
		this->ArcsNum = 0;
		//申请边数组的内存
		Arcs = new int[DEFAULT_VERTEX_SIZE * DEFAULT_VERTEX_SIZE];
		//申请顶点数组的内存
		Vertice = new type[DEFAULT_VERTEX_SIZE];
		//如果申请失败直接返回即可
		if (Arcs == nullptr || Vertice == nullptr)return;
		//把数组内容初始化
		for (unsigned int i = 0; i < DEFAULT_VERTEX_SIZE; i++)
		{
			Vertice[i] = 0;
			for (unsigned int j = 0; j < DEFAULT_VERTEX_SIZE; j++)
			{
				if (i == j)
					*(
						Arcs +
						DEFAULT_VERTEX_SIZE *
						i +
						j) = 0;
				else *(Arcs + DEFAULT_VERTEX_SIZE * i + j) = DEFAULT_MAX_SHORT;
			}
		}
	}


	template<typename type>
	AMGraph<type>::~AMGraph()
	{
		delete Arcs;//释放边数组空间
		delete Vertice;//释放顶点数组空间
	}


	template<typename type>
	bool AMGraph<type>::AddVertex(type e)
	{
		if (VertexNum == DEFAULT_VERTEX_SIZE - 1)return false;
		Vertice[VertexNum++] = e;
		return true;
	}


	template<typename type>
	bool AMGraph<type>::connect(type src, type dst, int weight)
	{
		unsigned int srcpos = GetVertexPosition(src);
		unsigned int dstpos = GetVertexPosition(dst);

		if (
			srcpos > DEFAULT_VERTEX_SIZE
			||
			dstpos > DEFAULT_VERTEX_SIZE
			)return false;//起始点或终点非法
		*(Arcs + DEFAULT_VERTEX_SIZE * srcpos + dstpos) = weight;//设置权值
		return true;
	}


	template<typename type>
	unsigned int AMGraph<type>::GetVertexPosition(type V)
	{
		for (unsigned int i = 0; i < VertexNum; i++)
			if (Vertice[i] == V)return i;
		return DEFAULT_MAX_SHORT;//没有该顶点
	}


	template<typename type>
	void AMGraph<type>::DFS(unsigned int start)
	{
		if (start >= VertexNum)return;//深搜位置非法
		bool* IsVisit = (bool*)malloc(VertexNum * sizeof(bool));//申请内存
		for (unsigned int i = 0; i < VertexNum; i++)
			IsVisit[i] = false;
		DepthFirstSearch(start, IsVisit);
		free(IsVisit);//释放内存
	}


	template<typename type>
	void AMGraph<type>::DepthFirstSearch(unsigned int start, bool* IsVisit)
	{
		if (start >= VertexNum)return;//深搜位置非法
		visit(start);
		IsVisit[start] = true;
		for (unsigned int i = 0; i < this->VertexNum; i++)
			if (
				IsVisit[i] == false &&
				*(Arcs + DEFAULT_VERTEX_SIZE * start + i) != 0 &&
				*(Arcs + DEFAULT_VERTEX_SIZE * start + i) != DEFAULT_MAX_SHORT
				)
				DepthFirstSearch(i, IsVisit);

	}


	template<typename type>
	void AMGraph<type>::BFS(unsigned int start)
	{
		if (start >= VertexNum)return;//广搜非法
		bool* IsVisit = (bool*)malloc(VertexNum * sizeof(bool));
		for (unsigned int i = 0; i < VertexNum; i++)
			IsVisit[i] = false;
		BreathFirstSearch(start, IsVisit);
		for (unsigned int i = 0; i < VertexNum; i++)
			if (IsVisit[i] == false)BreathFirstSearch(i, IsVisit);
	}


	template<typename type>
	void AMGraph<type>::BreathFirstSearch(unsigned int start, bool* IsVisit)
	{
		GenericQueue<type> Q;
		Q.EnQueue(Vertice[start]);
		IsVisit[start] = true;
		type p;
		while (Q.IsEmpty() == false)
		{
			Q.DeQueue(p);
			unsigned int Vpos = GetVertexPosition(p);
			visit(Vpos);
			for (unsigned int i = 0; i < this->VertexNum; i++)
				if (
					IsVisit[i] == false &&
					*(Arcs + DEFAULT_VERTEX_SIZE * Vpos + i) != 0 &&
					*(Arcs + DEFAULT_VERTEX_SIZE * Vpos + i) != DEFAULT_MAX_SHORT
					)
				{
					Q.EnQueue(Vertice[i]);
					IsVisit[i] = true;
				}
		}

	}


	template<typename type>
	int AMGraph<type>::Dijkstra(type src, type dst)
	{
		unsigned int srcpos = GetVertexPosition(src);//获取起始点下标
		unsigned int dstpos = GetVertexPosition(dst);//获取终点下标
		int* Distance = (int*)malloc(VertexNum * sizeof(int));
		bool* IsVisit = (bool*)malloc(VertexNum * sizeof(bool));
		type* Path = (type*)malloc(VertexNum * sizeof(type));
		if (Distance == nullptr || IsVisit == nullptr || Path == nullptr)
			return DEFAULT_MAX_SHORT;
		for (unsigned int i = 0; i < VertexNum; i++)
		{

			Distance[i] = DEFAULT_MAX_SHORT;
			IsVisit[i] = false;
			Path[i] = Vertice[i];
		}

		Distance[srcpos] = 0;

		for (unsigned int i = 0; i < VertexNum; i++)//访问n个节点
		{
			unsigned int min_dist_pos = srcpos;
			unsigned int min_dist = DEFAULT_MAX_SHORT;
			for (unsigned int j = 0; j < VertexNum; j++)
			{
				if (IsVisit[j] == false && min_dist > Distance[j])
				{
					min_dist = Distance[j];
					min_dist_pos = j;
				}
			}//找到未被访问的，并且dist值最小的节点
			IsVisit[min_dist_pos] = true;//访问该节点

			for (unsigned int j = 0; j < VertexNum; j++)
			{
				if (
					Distance[min_dist_pos] +//起始点到访问点的距离
					*(Arcs + DEFAULT_VERTEX_SIZE * min_dist_pos + j)//访问点到某一点的距离
					< Distance[j]//起始点到某一点的距离
					) {
					Distance[j]
						=
						Distance[min_dist_pos]
						+
						*(Arcs + DEFAULT_VERTEX_SIZE * min_dist_pos + j);
					Path[j] = Vertice[min_dist_pos];//记录路径
				}
			}
		}
		GenericStack<type> S;
		unsigned int p = GetVertexPosition(dst);
		while (dst != src)
		{
			S.Push(dst);//
			dst = Path[p];
			p = GetVertexPosition(dst);

		}
		S.Push(dst);
		printf("路径：");
		while (S.IsEmpty() == false)
		{
			VertexType V;
			S.Pop(V);

			if (S.IsEmpty())
				printf("%c\n", V);
			else printf("%c->", V);
		}

		return Distance[dstpos];
	}


	template<typename type>
	void AMGraph<type>::visit(unsigned int pos)
	{
		if (pos >= VertexNum)return;
		printf("%c", Vertice[pos]);

	}


	template<typename type>
	unsigned int AMGraph<type>::GetVertexOutDegree(type V)
	{
		unsigned int pos = GetVertexPosition(V);
		unsigned int ret = 0;
		for (unsigned int i = 0; i < VertexNum; i++)
			if (
				*(Arcs + DEFAULT_VERTEX_SIZE * pos + i) != 0
				&&
				*(Arcs + DEFAULT_VERTEX_SIZE * pos + i) != DEFAULT_MAX_SHORT
				) {
				ret++;
			}
		return ret;
	}


	template<typename type>
	unsigned int AMGraph<type>::GetVertexInDegree(type V)
	{
		unsigned int pos = GetVertexPosition(V);
		unsigned int ret = 0;
		for (unsigned int i = 0; i < VertexNum; i++)
			if (
				*(Arcs + DEFAULT_VERTEX_SIZE * i + pos) != 0
				&&
				*(Arcs + DEFAULT_VERTEX_SIZE * i + pos) != DEFAULT_MAX_SHORT
				) {
				ret++;
			}
		return ret;
	}


	template<typename type>
	int AMGraph<type>::Floyd()
	{
		return 0;
	}


	template<typename type>
	void AMGraph<type>::TopoSort()
	{
		bool* IsVisit = (bool*)malloc(VertexNum * sizeof(bool));//是否加入过队列
		unsigned int* InDegree = (unsigned int*)malloc(VertexNum * sizeof(int));//入度
		if (IsVisit == NULL || InDegree == NULL)return;//申请失败
		for (unsigned int i = 0; i < VertexNum; i++)
		{
			IsVisit[i] = false;
			InDegree[i] = GetVertexInDegree(Vertice[i]);
		}//初始化入度数组和访问数组
		GenericQueue<unsigned int>  Q;//队列
		for (unsigned int i = 0; i < VertexNum; i++)
			if (InDegree[i] == 0)
			{
				Q.EnQueue(i);
				IsVisit[i] = true;
			}
		unsigned int pos;
		while (Q.IsEmpty() == false)
		{
			Q.DeQueue(pos);
			visit(pos);

			for (unsigned int i = 0; i < VertexNum; i++)
				if (*(Arcs + DEFAULT_VERTEX_SIZE * pos + i) != 0
					&&
					*(Arcs + DEFAULT_VERTEX_SIZE * pos + i) != DEFAULT_MAX_SHORT
					&&
					IsVisit[i] == false//如果i没有加入过队列并且Arcs[pos][i]有边
					) {
					InDegree[i]--;
				}
			for (unsigned int i = 0; i < VertexNum; i++)
				if (IsVisit[i] == false
					&&
					InDegree[i] == 0)
				{
					Q.EnQueue(i);
					IsVisit[i] = true;
				}
		}
	}
}
