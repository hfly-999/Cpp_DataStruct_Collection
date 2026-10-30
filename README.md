# Cpp_DataStruct_Collection

C++ 数据结构项目合集，按编写时间归档，同一个项目从 C 风格一路重写到现代 C++ 容器库。

| 版本 | 时间 | 来源 | 范式 | 文件数 | 一句话特点 |
| --- | --- | --- | --- | --- | --- |
| [V1.0](V1.0) | 2025-08-07 | `Cpp_DataStruct_2025_8_7` | C 风格结构体 + 全局函数 | 20 | 覆盖面最广，408 真题驱动的基础库 |
| [V2.0](V2.0) | 2026-05-22 | `Cpp_OOP_DataStruct` | C++ 类 + 命名空间 + 模板 | 32 | 面向对象重构第一版，有完整 VS 工程 |
| [V3.0](V3.0) | 2026-08-14 | `Cpp_OOP_DataStruct_v2` | 现代 C++（RAII / 迭代器） | 29 | 完成度最高，`list` / `vector` 按标准库思路重写 |

---

## V1.0 — 数据结构基础库（2025-08-07）

### 简介

用 **C 风格（结构体 + 全局函数）** 手写的数据结构练习库，覆盖线性表、链表、栈、队列、串、树、图、查找、排序九大模块，并大量实现 408/王道考研真题。没有使用 STL 容器，`Define.h` 统一了 `ElemType = char`、`KeyType = int` 等类型和常量。

### 模块与能力

| 模块 | 能力 |
| --- | --- |
| 顺序表 `SqList` | 初始化、插入、删除、按值查找、打印；删除 `x`、删除 `s~t`、有序表去重、查找并插入/交换、合并有序表、前后两段互换、三数组交集、两有序数组中位数、未出现的最小正整数 |
| 链表 `LinkList` | 单链表、双链表、循环双链表；BF/KMP 判断子链、对称判断、删除 `x`、删除最小值、就地逆置、删除区间、找公共结点、链表拆分、去重、交集、右移 `k` 位、判环、判断对称 |
| 栈 `Stack` | 顺序栈、链栈；初始化、入栈、出栈、打印、判空、取长度、清空、销毁；另有 `void*` 通用 `Stack` 类 |
| 队列 `Queue` | 顺序队列、带头结点链队列；初始化、入队、出队、打印、取长度、取队头 |
| 串 `String` | KMP 算法（当前整段被注释，见「不足」） |
| 树 `Tree` | 二叉树递归/非递归先中后序、层次遍历、先序建树、复制、计数、叶子数、树高、完全二叉树判断、交换左右子树、相似判断、删除 `x` 子树、祖先、最近公共祖先、连接叶子、WPL、先序转后序、转中缀表达式；线索二叉树；双亲/孩子/孩子兄弟表示；哈夫曼树构建、编码、加密 |
| 图 `Graph` | 邻接矩阵、邻接表、无向网构建、DFS/BFS、Prim、Kruskal、Dijkstra、Floyd、拓扑排序、关键路径（待完成）、邻接表转矩阵、简单路径、DFS 拓扑、拓扑唯一性 |
| 查找 `Search` | 顺序/二分/递归二分查找；二叉排序树插入/删除/查找；AVL 平衡因子更新；红黑树插入/四种旋转/变色/删除（待修正）；n 阶 B 树插入/删除；开放地址哈希、拉链哈希；判断 BST/AVL 等 408 题 |
| 排序 `Sort` | 直接插入、折半插入、希尔、冒泡、快速、堆、归并、桶、计数排序；堆支持无序插入和有序插入 |

### 特点

- **功能最全**：9 大模块、约 100 个函数，三个版本里覆盖面最广
- **考研友好**：大量 408/王道真题，题目注释直接写在函数上方
- **直白易懂**：结构体 + 全局函数，没有模板和继承，适合初学
- **单文件体量大**：`Search.cpp` 约 26KB、`Tree.cpp` 约 17KB、`Graph.cpp` 约 15KB

### 不足

- `String.cpp` 的 KMP 整体被注释，串模块不可用
- 图的 `CriticalPath` 标注待完成
- 红黑树 `Delete` 标注「还没实现自平衡机制（待修正）」
- `main.cpp` 是空入口，没有统一测试
- 依赖 `Windows.h`，且没有工程文件

---

## V2.0 — 面向对象数据结构第一版（2026-05-22）

### 简介

把 V1.0 用 **C++ 面向对象** 重写的第一版：引入 `namespace DSL`（DataStructLibrary）、`class`、模板泛型、继承与虚函数，把「数据」和「操作」封装到一起。附带 Visual Studio 2022 工程（`Cpp_DataStruct_2026_5_22.sln`）。

### 模块与能力

| 模块 | 能力 |
| --- | --- |
| 泛型单/双链表 | `GenericLNode<type>` / `GenericDNode<type>`：构造、头插、尾插、创建结点，双链表增加 `prior` |
| 泛型栈 | `GenericStack<type>`：`Push` / `Pop` / `IsEmpty` / `IsFull` / `GetTop`，动态扩容 |
| 泛型队列 | `GenericQueue<type>`：`EnQueue` / `DeQueue` / `IsFull` / `IsEmpty` / `GetLength`，动态扩容 |
| 泛型顺序表 / 堆 | `GenericSqList<type>`：插入、交换、判满/判空、取长度；`GenericHeap<type>`：自定义比较器、大/小顶堆、`Push` / `Pop` |
| 二叉树 | `BNode`：递归/非递归先中后序、层次遍历、高度、叶子判断、访问、创建结点 |
| 线索二叉树 | `ThreadNode`：`ltag` / `rtag` |
| 哈夫曼树 | `HNode`：统计字符频次、构建哈夫曼树、中序遍历、编码/加密 |
| 二叉排序树 | `BSTNode` / `BSTree`：插入、查找、创建结点 |
| 平衡二叉树 | `BBTNode` / `AVL`：重写插入、计算平衡因子 |
| 红黑树 | `RBTNode` / `RBTree`：创建结点（算法未完成） |
| 图 | `AMGraph<type>` 模板有向图：加顶点、连边、DFS/BFS、Dijkstra、Floyd、拓扑排序、出入度；`NoDirectAMGraph<type>` 无向图 |
| 字符串 | `Strlen`、BF、KMP |

### 特点

- **统一命名空间**：所有类型和函数都在 `DSL` 下
- **类继承层次**：`BNode` → `BSTNode` → `BBTNode` → `RBTNode`，虚函数 `CreateNode` / `Insert` / `visit` 实现多态
- **模板泛型**：容器元素类型由使用者指定，不再固定 `ElemType`
- **声明与实现分离**：模板实现放在 `.inl`，由 `.h` 末尾包含
- **动态扩容**：栈、队列、顺序表、堆都按需申请/扩容
- **工程完整**：VS 2022（v143）工程可直接编译

### 不足

原项目 README 已标注：

- 未解决**深拷贝 / 浅拷贝**问题
- 模板类的 `type` 不能是 `std::string` 等复杂类型
- **AVL / 红黑树**部分算法未完成
- **ALGraph**（邻接表）部分未完成
- 图的**最小生成树**（Kruskal / Prim）未实现

另外部分注释是 GBK 编码，在 UTF-8 环境下可能乱码。

---

## V3.0 — 面向对象数据结构库 DSL（2026-08-14）

### 简介

三个版本里完成度最高的一版。不再追求「每种结构都写一遍」，而是把 `list`、`vector` 这类容器做扎实：原始内存分配、placement new、迭代器、异常安全边界、不变量自检，都按标准库的思路重新实现；并在容器之上补了 `stack` / `queue` 两个容器适配器。工程文件 `Cpp_OOP_DataStruct_2026_8_14.sln`。

### 模块状态

| 模块 | 文件 | 状态 |
| --- | --- | --- |
| 单链表 `list` | `mylist.h` / `.inl` / `.cpp` | ✅ **可用**：双向循环 + 单哨兵；构造 / `initializer_list` 构造 / 拷贝构造 / 拷贝赋值 / 析构；`insert` / `erase` / `push_front` / `push_back` / `pop_front` / `pop_back` / `clear` / `front` / `back` / `size` / `empty` / `reverse`；**`iterator` + `const_iterator` 两套迭代器**；`check()` 不变量自检 |
| 顺序表 `vector` | `myvector.h` / `.cpp` | 🚧 **可用但待打磨**：原始内存分配 + placement new、默认 / `initializer_list` / 拷贝构造、拷贝赋值（含自赋值保护）；`insert`（任意位置、自动扩容）/ `erase` / `pop_back` / `push_back` / `push_front` / `clear` / `operator[]` / `front` / `back` / `size` / `capacity` / `empty` / `begin` / `end`；`reserve` / `swap` / `operator==` / `resize` 尚缺 |
| 栈适配器 `stack` | `mystack.h` | ✅ **可用**：容器模板参数化，默认底层 `DSL::vector`；`push` / `pop` / `top` / `empty` / `size` |
| 队列适配器 `queue` | `myqueue.h` | ✅ **可用**：容器模板参数化，默认底层 `DSL::list`；`push` / `pop` / `front` / `back` / `empty` / `size` |
| 字符串 `String` | `String.h` / `.cpp` | ✅ 已实现：BF 与 KMP 子串匹配（含 `next` / `nextval` 数组） |
| 唯一指针 `Unique_ptr` | `Unique_ptr.h` / `.cpp` | 🚧 未完成：缺移动语义、`release` / `reset` |
| 二叉树 `Tree` | `Tree.h` / `.inl` / `.cpp` | 🚧 **重新设计中**：`BNode` / `BTree` 类结构已定，成员函数尚未实现，且当前有 5 处实现问题会导致实例化失败（见「不足」） |

### 实现要点

- **`list` 双向循环链表 + 单哨兵**：空表时 `Head` 自指，插入只有「在某个节点之前插入」一种情况，不需要为首尾写特例；`iterator` 与 `const_iterator` 是两个独立类，唯一区别是 `operator*` 返回 `type&` 还是 `const type&`；`check()` 在 Debug 下校验节点数、双向指针一致性和环闭合
- **`vector` 原始内存 + placement new**：`::operator new` 只申请字节不构造对象，`[0, size)` 是活对象、`[size, capacity)` 是未构造内存；扩容按 1.5 倍增长；`insert` 先算下标再扩容，只构造一次、其余拷贝赋值，不会析构容器内已有元素
- **`stack` / `queue` 容器适配器**：两者都不实现存储，只持有一个容器（**组合而非继承**）；容器作为模板参数，默认值分别是 `DSL::vector` 与 `DSL::list`，因此底层容器的 `insert` / `begin` / `operator[]` 不会泄漏到适配器接口上
- **`Tree` 节点只存数据**：`BNode` 只保留 `val` / `lchild` / `rchild`，原先写在节点上的递归析构、递归拷贝构造、递归赋值全部移除；`friend class BTree<T>` 显式声明「只有树能碰节点私有字段」；整棵树的删除改用**层次遍历**（借助 `DSL::queue`），避免深树递归爆栈

### 特点

- **最接近标准库**：原始内存管理、placement new、显式析构、迭代器
- **两套迭代器**：`iterator` / `const_iterator`，越权写编译期拦截
- **不变量自检**：`check()` 保证链表结构正确
- **容器适配器**：`stack` / `queue` 以模板参数复用底层容器，换底层不动上层
- **完整的 VS 工程**：VS 2022 + C++14 + `/utf-8`
- **有开发记录**：`CHANGELOG.txt` 按日期记录变更，`need.txt` 记录待办

### 不足

- `vector` 缺 `reserve` / `swap` / `operator==` / `resize` / `data()`，且要求元素可默认构造
- `list` 迭代器缺 `operator->` 和 5 个类型别名，暂时不能配合标准算法
- `stack` / `queue` 缺 `#pragma once`，`size()` 未加 `const`，`stack::push` 按值传参
- `Tree` 目前一旦实例化即编译失败：`friend` 缺模板参数、`tree` 未初始化、只删拷贝构造未删拷贝赋值、默认构造丢失、队列元素类型写成了对象
- `Unique_ptr` 未完成移动语义

---

## 版本演进

```
V1.0 (2025-08)
  C 风格：结构体 + 全局函数，固定 ElemType，覆盖 9 大模块和 408 真题
        │
        ▼
V2.0 (2026-05)
  C++ 面向对象：namespace DSL、class、模板泛型、继承、VS 工程
        │
        ▼
V3.0 (2026-08)
  现代 C++：原始内存 + placement new、双迭代器、不变量自检、RAII
```

从「把每个数据结构都写一遍」到「把容器写扎实」，三个版本反映了从语法练习到工程实现的演进。

## 目录结构

```
Cpp_DataStruct_Collection/
├── README.md
├── V1.0/                     # 2025-08-07，20 个文件
│   ├── README.md
│   ├── Define.h
│   ├── SqList.h / SqList.cpp
│   ├── LinkList.h / LinkList.cpp
│   ├── Stack.h / Stack.cpp
│   ├── Queue.h / Queue.cpp
│   ├── String.h / String.cpp
│   ├── Tree.h / Tree.cpp
│   ├── Graph.h / Graph.cpp
│   ├── Search.h / Search.cpp
│   ├── Sort.h / Sort.cpp
│   └── main.cpp
├── V2.0/                     # 2026-05-22，32 个文件
│   ├── README.md
│   ├── Define.h
│   ├── LinkList.h + GenericLinkList.inl
│   ├── Stack.h + Stack.inl
│   ├── Queue.h + Queue.inl
│   ├── Sort.h + GenericSqList.inl + GenericHeap.inl
│   ├── BTree.h / BTree.cpp
│   ├── Search.h / Search.cpp
│   ├── Graph.h + AMGraph.inl + NoDirectAMGraph.inl + Graph.cpp
│   ├── String.h / String.cpp
│   ├── main.cpp
│   └── Cpp_DataStruct_2026_5_22.sln / .vcxproj / .filters / .user
└── V3.0/                     # 2026-08-14，29 个文件
    ├── README.md
    ├── Define.h / Include.h
    ├── mylist.h / .inl / .cpp
    ├── myvector.h / .cpp
    ├── String.h / .inl / .cpp
    ├── Unique_ptr.h / .cpp
    ├── Stack.h / .inl / .cpp
    ├── Queue.h / .inl / .cpp
    ├── Tree.h / .inl / .cpp
    ├── AAAmain.cpp
    ├── CHANGELOG.txt / need.txt
    └── Cpp_OOP_DataStruct_2026_8_14.sln / .vcxproj / .filters
```

## 编译

- **V1.0**：没有工程文件，可新建空控制台项目把 `.cpp` 全部加入，或 `g++ -std=c++14 *.cpp -o datastruct`
- **V2.0**：VS 2022 打开 `V2.0/Cpp_DataStruct_2026_5_22.sln`，选 `x64` 编译；或 `g++ -std=c++14 *.cpp -o datastruct`
- **V3.0**：VS 2022 打开 `V3.0/Cpp_OOP_DataStruct_2026_8_14.sln`，选 `x64` 编译

## 说明

- V1.0 和 V3.0 通过 `git subtree` 合并，保留各自提交历史；V2.0 的原仓库含 380MB 构建缓存，因此只导入了源码与工程文件
- 编码：V1.0 主要是 GBK；V2.0 部分注释为 GBK，可能乱码；V3.0 统一 UTF-8 with BOM
- 三个版本是同一项目的迭代关系，不是三个独立项目
