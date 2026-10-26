# V2.0 — 面向对象数据结构第一版

> 编写时间：2026-05-22　|　语言：C++14　|　规模：32 个文件（源码 + Visual Studio 工程）
>
> 工程文件：`Cpp_DataStruct_2026_5_22.sln`

## 简介

这是把 V1.0 的 C 风格代码用 **C++ 面向对象** 重写的第一版：引入 `namespace DSL`（DataStructLibrary）、`class`、模板泛型、继承与虚函数，开始把「数据」和「操作」封装到一起。

和 V1.0 最大的区别：

- 从 `struct` + 全局函数 → `class` + 成员函数
- 从固定 `ElemType` → `template<typename type>` 泛型
- 从各模块互不相干 → 统一的 `DSL` 命名空间和类继承层次
- 模板实现放到 `.inl`，由对应 `.h` 末尾包含

## 模块与文件

| 模块 | 文件 | 内容 |
| --- | --- | --- |
| 泛型单链表 | `LinkList.h` + `GenericLinkList.inl` | `GenericLNode<type>`：构造、头插、尾插、创建结点 |
| 泛型双链表 | 同上 | `GenericDNode<type>` 继承单链表，增加 `prior` 指针和重写的插入/创建结点 |
| 泛型栈 | `Stack.h` + `Stack.inl` | `GenericStack<type>`：`Push` / `Pop` / `IsEmpty` / `IsFull` / `GetTop`，动态扩容 |
| 泛型队列 | `Queue.h` + `Queue.inl` | `GenericQueue<type>`：`EnQueue` / `DeQueue` / `IsFull` / `IsEmpty` / `GetLength`，动态扩容 |
| 泛型顺序表 | `Sort.h` + `GenericSqList.inl` | `GenericSqList<type>`：插入、交换、判满/判空、取长度 |
| 泛型堆 | `Sort.h` + `GenericHeap.inl` | `GenericHeap<type>`：自定义比较器，支持大顶堆/小顶堆，`Push` / `Pop` |
| 二叉树 | `BTree.h/.cpp` | `BNode`：递归/非递归先中后序、层次遍历、高度、叶子判断、访问、创建结点 |
| 线索二叉树 | `BTree.h` | `ThreadNode`：在 `BNode` 基础上增加 `ltag` / `rtag` |
| 哈夫曼树 | `BTree.h/.cpp` | `HNode`：统计字符频次、构建哈夫曼树、中序遍历、编码/加密 |
| 二叉排序树 | `Search.h/.cpp` | `BSTNode` / `BSTree`：插入、查找、创建结点 |
| 平衡二叉树 | `Search.h/.cpp` | `BBTNode` / `AVL`：重写插入、计算平衡因子（`CountBF`） |
| 红黑树 | `Search.h/.cpp` | `RBTNode` / `RBTree`：创建结点（算法部分未完成） |
| 图 | `Graph.h` + `AMGraph.inl` | `AMGraph<type>` 模板有向图：加顶点、连边、DFS/BFS、Dijkstra、Floyd、拓扑排序、出入度 |
| 无向图 | `Graph.h` + `NoDirectAMGraph.inl` | `NoDirectAMGraph<type>` 继承有向图，`connect` 同时连双向边 |
| 字符串 | `String.h/.cpp` | `Strlen`、BF、KMP |
| 公共定义 | `Define.h` | 默认容量常量、`ElemType = int`、`VertexType = char`、`DSL` 命名空间 |
| 入口 | `main.cpp` | 哈夫曼树演示：对 `"I LOVE YOU,MY BEAUTY"` 建树并中序遍历 |

## 设计特点

1. **统一命名空间**：所有类型和函数都在 `namespace DSL` 下，避免和标准库冲突。
2. **类继承层次**：`BNode` → `BSTNode` → `BBTNode` → `RBTNode`，用虚函数 `CreateNode` / `Insert` / `visit` 实现多态。
3. **模板泛型**：链表、栈、队列、顺序表、堆、图都做成了模板类，元素类型由使用者指定。
4. **声明与实现分离**：模板实现放在 `.inl`，由对应 `.h` 末尾 `#include`，兼顾可读性与编译。
5. **动态扩容**：栈、队列、顺序表、堆都按需申请/扩容，不再固定 `MAXSIZE`。
6. **完整工程**：附带 Visual Studio 2022（v143）工程，可直接编译运行。

## 编译

用 Visual Studio 2022 打开 `Cpp_DataStruct_2026_5_22.sln`，选择 `x64` 配置编译即可。

也可以用 g++：

```bash
g++ -std=c++14 *.cpp -o datastruct
```

## 已知未完成部分

原项目 README 中明确标注了这些不足：

- 没有解决**深拷贝 / 浅拷贝**问题（涉及指针成员的类默认拷贝会出问题）
- 模板类的 `type` 不能是 `std::string` 等复杂类型
- **AVL 和红黑树**部分算法还未完成
- **ALGraph**（邻接表）部分还未完成
- 图的**最小生成树**（Kruskal / Prim）还未实现

此外：

- 部分源文件注释是 GBK 编码，在 UTF-8 环境下可能显示乱码
- 网络上的 `Graph.cpp` 只有几十字节，图的实现主要在 `AMGraph.inl` 模板里

## 与 V1.0 的对比

| 维度 | V1.0 | V2.0 |
| --- | --- | --- |
| 编程范式 | C 风格结构体 + 全局函数 | C++ 类 + 命名空间 + 模板 |
| 数据类型 | 固定 `ElemType` | `template<typename type>` |
| 内存管理 | 手动 `malloc/free` | 构造/析构 + 动态扩容 |
| 代码组织 | 每个模块一对 `.h/.cpp` | 类继承 + `.inl` 模板实现 |
| 功能覆盖 | 9 大模块、约 100 个函数 | 容器类 + 树/图类，覆盖略窄 |
| 工程化 | 无工程文件 | 完整 VS 工程 |
