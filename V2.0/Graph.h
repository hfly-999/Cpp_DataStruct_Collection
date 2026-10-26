#pragma once

#include"Define.h"
#include"Stack.h"
#include"Queue.h"

namespace DSL
{
	template<typename type>
	class AMGraph//有向图
	{
	public:


		AMGraph();
		
		
		~AMGraph();
	
		
		bool AddVertex(type e);

		//链接从src到dst的边，并且设置权值
		bool connect(
			type		src,
			type		dst,
			int			weight			);
		
		
		//深度优先搜索
		//输入起始顶点位置，从0开始
		void DFS(unsigned int start);
		void DepthFirstSearch(
			unsigned int	start,
			bool*			IsVisit		);


		//广度优先搜索
		void BFS(unsigned int start);
		void BreathFirstSearch(
			unsigned int	start,
			bool*			IsVisit		);
		
		
		//Dijkstra寻路
		int Dijkstra(
			type src,
			type dst					);

		//Floyd寻路
		int Floyd();
		
		
		//最小生成树
		//virtual AMGraph Prim();


		//virtual AMGraph Kruskal();


		//访问第i个顶点，i从0开始
		void visit(unsigned int pos);
		
		
		//根据顶点值获得其在顶点数组当中的下标
		unsigned int GetVertexPosition(type V);
		
		
		//获得顶点V出度
		unsigned int GetVertexOutDegree(type V);
		
		
		//获得顶点V的入度
		unsigned int GetVertexInDegree(type V);

		
		//拓扑排序
		void TopoSort();

		//成员变量
	private:
		int				* Arcs;
		type			* Vertice;
		unsigned int	VertexNum;
		unsigned int	ArcsNum;

	};


	template<typename type>//模版类的声明，type为顶点类型
	class NoDirectAMGraph :public AMGraph<type>//模版类无向图，
	{
	public:


		//无向图的链接
		bool connect(
					type	src,
					type	dst,
					int		weight
		)
											{
												return
													AMGraph<type>::connect(src, dst, weight)
												&&
													AMGraph<type>::connect(dst, src, weight);
											}


		//加入顶点
		bool AddVertex(type e)				{ return AMGraph<type>::AddVertex(e); }
		

		//深度优先搜索
		void DFS(unsigned int start)		{ AMGraph<type>::DFS(start); }
		void DepthFirstSearch(
			unsigned int	start,
			bool*			IsVisit) 
											{ AMGraph<type>::DepthFirstSearch(start, IsVisit); }
		
		
		//广度优先搜索
		void BFS(unsigned int start)		{ AMGraph<type>::BFS(start); }
		void BreathFirstSearch(
				unsigned int	start,
				bool*			IsVisit)	{ AMGraph<type>::BreathFirstSearch(start, IsVisit); }
		
		
		//寻路
		int Dijkstra(type src, type dst)	{ return AMGraph<type>::Dijkstra(src, dst); }
	
		//最小生成树
		

		//访问第i个顶点，i从0开始
		void visit(unsigned int pos)		{ AMGraph<type>::visit(pos); }
		
		
		//根据顶点值获得其在顶点数组当中的下标
		unsigned int GetVertexPosition(type V) 
											{ return AMGraph<type>::GetVertexPosition(V); }
		
		
		//获得顶点V出度
		unsigned int GetVertexOutDegree(type V)
											{ return AMGraph<type>::GetVertexOutDegree(V); }
		
		
		//获得顶点V的入度
		unsigned int GetVertexInDegree(type V)
											{ return AMGraph<type>::GetVertexInDegree(V); }

		
		//拓扑排序
		void TopoSort()						{ AMGraph<type>::TopuSort(); }
		
	};
}

#include"AMGraph.inl"
#include"NoDirectAMGraph.inl"
//-------------------------------------------------------------------------------//
