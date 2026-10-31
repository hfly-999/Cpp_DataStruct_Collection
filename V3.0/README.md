# Cpp_OOP_DataStruct_v2

用 C++ 从零手写的一个数据结构库，命名空间为 `DSL`（DataStructLibrary）。

这是学习 C++ 面向对象与数据结构过程中的实践项目：容器均自行实现，不依赖 STL 容器，目的是把内存管理、拷贝语义、迭代器与经典算法真正写一遍。

> 本目录是 [Cpp_DataStruct_Collection](../README.md) 的 **V3.0** 版本，仓库总览（三个版本的对比与演进）请看根目录的 README。

## 编译环境

- Visual Studio 2022（v143 工具集）
- C++14（项目当前默认语言标准）
- 全部配置已开启 `/utf-8`，源码可以放心用 UTF-8 保存
- 用 VS 打开 `Cpp_OOP_DataStruct_2026_8_14.sln`，选择 `x64` 配置即可编译

## 模块状态

| 模块 | 文件 | 状态 |
| --- | --- | --- |
| 单链表 `list` | `mylist.h` / `.inl` / `.cpp` | ✅ **可用**：双向循环 + 单哨兵；构造 / `initializer_list` 构造 / 拷贝构造 / 拷贝赋值 / 析构；`insert` / `erase` / `push_front` / `push_back` / `pop_front` / `pop_back` / `clear` / `front` / `back` / `size` / `empty` / `reverse`；**`iterator` + `const_iterator` 两套迭代器**；`check()` 不变量自检 |
| 顺序表 `vector` | `myvector.h` / `.cpp` | 🚧 **可用但待打磨**：原始内存分配（`::operator new` + placement new）、默认 / `initializer_list` / 拷贝构造、拷贝赋值（含自赋值保护）；`insert`（任意位置，容量不足自动扩容）/ `erase`（单点 + 区间）/ `pop_back` / `push_back` / `push_front` / `clear` / `operator[]` / `front` / `back` / `size` / `capacity` / `empty` / `begin` / `end`（后四者各两个 const 版本）；`reserve` / `swap` / `operator==` / `resize` 尚缺 |
| 栈适配器 `stack` | `mystack.h` | ✅ **可用**：容器模板参数化，默认底层 `DSL::vector`；`push` / `pop` / `top` / `empty` / `size` |
| 队列适配器 `queue` | `myqueue.h` | ✅ **可用**：容器模板参数化，默认底层 `DSL::list`；`push` / `pop` / `front` / `back` / `empty` / `size` |
| 字符串 `String` | `String.h` / `.cpp` | ✅ 已实现：BF 与 KMP 子串匹配（含 `next` / `nextval` 数组） |
| 唯一指针 `Unique_ptr` | `Unique_ptr.h` / `.cpp` | 🚧 未完成：缺移动语义、`release` / `reset` |
| 二叉树 `BTree` | `Tree.h` / `.inl` / `.cpp` | ✅ **可用**：`Insert(value, path)` 按 `"l"/"r"` 路径建树；先序 / 中序 / 后序 / 层次遍历**全部非递归**（显式栈 / 队列）；析构用层次遍历删除，深树不爆栈 |
| 线索二叉树 `ThreadTree` | `Tree.h` / `.inl` | ✅ **可用**：共用同一套建树逻辑 + `InThread()` 中序线索化；`getfirstnode` / `getlastnode` / `getnextnode` / `getprenode` 四个导航函数；**`iterator` 支持 `++` / `--` 双向遍历，中序不再用栈** |

> 原 `Stack.h` / `Queue.h` / `Stack.inl` / `Queue.inl` 已删除，由 `mystack.h` / `myqueue.h` 取代。

## 实现要点

### `list`：双向循环链表 + 单哨兵

- 只有一个哨兵节点 `Head`，空表时自指：`Head->next == Head->prior == Head`
- `Head->next` 是首元素，`Head->prior` 是尾元素
- 因此「插入」只有一种情况 —— 在某个节点**之前**插入，不需要为首尾写任何特例
- `iterator` 与 `const_iterator` 是两个独立的类，内部都持 `DNode<type>*`，唯一区别是 `operator*` 的返回类型：`type&` 与 `const type&`。同一个节点因此可以用两种权限访问，越权写在编译期就会被挡住
- `check()` 在 Debug 下校验三件事：节点数与 `length` 一致、双向指针互相一致、环闭合

### `vector`：原始内存 + placement new

- 用 `::operator new` **只申请字节，不构造任何对象**
- 元素用 placement new 在指定地址上构造；析构时逐个显式调用 `~type()`
- `[0, size)` 是活对象，`[size, capacity)` 是未构造的原始内存 —— **这是 `size` 与 `capacity` 能分开的根本原因**
- 扩容时按 1.5 倍增长（`calcapacity`，下限为 2）
- 所有插入都走同一个 `insert`：先用 `pos - Data` 算出下标（**必须在扩容之前算** —— 扩容会换掉 `Data`），再按需扩容，然后只做三件事：
  1. 在 `Data[size]` 处**构造**一次 —— 这是整个 `insert` 唯一的一次构造（`size` 处是未构造的原始内存）
  2. 中间元素逐个**拷贝赋值**后移
  3. 新值**拷贝赋值**进目标槽位
- 因此 `insert` 期间**不会析构容器内任何已有元素**：目标位置是「被覆盖」，不是「删掉再重建」。（唯一的析构来自函数内的局部拷贝，用来防止 `insert(pos, v[k])` 读到被移位覆盖的数据）
- `erase` 与 `insert` 方向相反：**先把后续元素逐个拷贝赋值前移，最后单独析构尾部那个多出来的元素**

### `stack` / `queue`：容器适配器

- 两者都**不实现存储**，只持有一个容器（组合，不是继承）
- 容器作为模板参数，默认值分别是 `DSL::vector` 与 `DSL::list`：
  ```cpp
  template<typename Type, typename Container = vector<Type>> class stack;
  template<typename Type, typename Container = list<Type>>   class queue;
  ```
- 它们对底层只要求少数几个操作：栈需要 `push_back` / `pop_back` / `size`，队列需要 `push_back` / `pop_front` / `size`
- 因为用组合而不是继承，底层容器的 `insert` / `begin` / `operator[]` **不会**泄漏到适配器的接口上 —— 栈就只能从顶上看

### `Tree`：节点只存数据，操作全非递归

- `BNode` 只保留 `val` / `lchild` / `rchild`，**不承担任何树的行为** —— 早期版本里节点的递归析构、递归拷贝构造、递归赋值都写在节点上，既难维护，又把树的行为分散到了两个类里
- `friend class BTree<T>;` —— 显式声明「只有 `BTree` 能碰节点的私有字段」，其余代码一律无权访问。**注意不能再在它前面加一行 `template<typename T>`**：那样会变成「所有 `BTree<X>` 都是所有 `BNode<Y>` 的友元」，并触发 `C3772` 友元模板声明无效
- 四种遍历**全部非递归**：先序 / 中序 / 后序用显式 `DSL::stack`，层次遍历用 `DSL::queue`
- 删除整棵树也用层次遍历（借助 `DSL::queue`），因此再深的树也不会爆栈
- 拷贝构造 / 拷贝赋值在 `BTree` 上**显式删除**，避免两棵树共享同一批节点后二次释放
- `Insert(value, path)` 用一个 `"l"/"r"` 路径串描述插入位置，便于按指定形状建树

### `ThreadTree`：线索化把「栈」从遍历里拿掉

- 线索化（`InThread`）就是在一棵**已经建好**的树上跑一遍中序遍历，额外维护一个 `pre` 指针：
  - 访问 `p` 时，若 `pre->rchild` 为空 → 让 `pre->rchild` 指向 `p`，`pre->rtag = true`
  - 若 `p->lchild` 为空 → 让 `p->lchild` 指向 `pre`，`p->ltag = true`
- 线索化完成后，中序遍历**不再需要栈**：叶子节点的空指针已经变成了「前驱 / 后继」，顺着线索走即可 —— 这是空间上的收益（省掉 O(h) 的栈）
- 四个导航函数构成迭代器的骨架：
  - `getfirstnode` —— 一路向左到底，得到中序第一个节点
  - `getlastnode` —— 一路向右到底，得到中序最后一个节点
  - `getnextnode` —— `rtag` 为真则直接走后继线索；否则是「右子树的最左节点」
  - `getprenode` —— `ltag` 为真则直接走前驱线索；否则是「左子树的最右节点」
- `iterator` 的 `++` / `--` 各自复用一个导航函数，`end()` 用 `nullptr` 表示「越界」，所以 `it != end()` 能自然终止
- **同一个 `ThreadNode` 有两套指针语义**：`ltag == false` 时 `lchild` 是孩子，`ltag == true` 时它是前驱。因此删除必须走 `delete_thread_tree`（先查 tag），**不能**复用普通的 `delete_tree` —— 否则会把祖先当孩子 `delete`，直接 use-after-free

## 待改进

按模块列出尚未做完的部分。

### `vector`

- 缺 `reserve` / `swap` / `operator==` / `resize` / `data()`
- `~vector()` 无需 `virtual`
- `check()` 未声明为 `const`
- 要求 `type` 可默认构造（`insert` 中的 `new (Data + size) type()`）；接入移动语义后可放宽

### `list`

- 迭代器缺 `operator->`，`it->member` 无法使用
- 迭代器缺 5 个类型别名（`value_type` 等），暂时无法与 `std::find` / `std::distance` 等标准算法配合
- `~list()` 无需 `virtual`

### `stack` / `queue`

- 两个头文件都缺 `#pragma once`，重复包含会重定义
- `size()` 未声明为 `const`（`empty()` 是 `const`，不一致）
- `stack::push` 按值传参，应为 `const Type&`
- `stack::top()` 用 `*(c.end() - 1)` 实现，**隐含要求底层容器支持随机访问** —— 换成 `list` 会编不过，这一点应在注释里写明

### `Tree` / `ThreadTree`

- **`insert` 的回滚路径有 use-after-free（待修）**：`op` 里出现非 `l`/`r` 字符会走回滚分支，`delete_tree(create_tree)` 删掉了 `p` 所在的子树，但函数末尾仍会执行 `p->val = value` —— ASan 报 `heap-use-after-free`（WRITE）。修法是在回滚分支末尾直接 `return false;`
- **`InThread()` 只能调用一次**：重复线索化时 `lchild` 已指向前驱，遍历会跳到别的子树上去。目前没有 `threaded` 标志做保护
- `delete_tree` 与 `delete_thread_tree` 几乎是同一份代码，只差两个 tag 判断。如果让 `ThreadNode::left()` / `right()` 在 `ltag` / `rtag` 为真时返回 `nullptr`，再另配 `raw_left()` / `raw_right()` 供线索化使用，两份可以合并成一份
- `iterator::operator*` 返回 `T&`，const 迭代器也能改值；缺 `const_iterator`，`operator==` / `operator!=` 也未声明 `const`
- `BTree::operator=` 的返回类型写成了 `BTree`，应为 `BTree&`（`ThreadTree` 那处是对的）
- `insert` 里的 `bool dir_l` 赋值了三处、从未被读取（死变量）
- `Insert(value, path)` 用 `"l"/"r"` 字符串描述路径，更像「按图纸建树」而不是「按值有序插入」；若要当 BST 用，需要再补一个按序插入的重载
- `BNode::visit()` 内部直接写 `std::cout`，隐含要求元素类型可流输出（装一个没有 `operator<<` 的 `struct` 会编不过）
- `Tree.h` 顶部 `#include` 了 `mystack.h` / `myqueue.h`，即与「栈 / 队列用哪种容器实现」这件事耦合；更彻底的做法是把容器提成模板参数

## 目录约定

- `.h` —— 类声明与接口
- `.inl` —— 模板成员函数的实现，由对应的 `.h` 在末尾包含
- `.cpp` —— 每个功能一个测试函数，注释中写明期望输出

## 下一步

- `Tree`：修 `insert` 回滚路径的 use-after-free；给 `InThread()` 加 `threaded` 标志，防止重复线索化
- `Tree`：合并 `delete_tree` / `delete_thread_tree`；`iterator` 补 `const_iterator` 与 `const` 成员函数
- `Tree`：`Insert` 增加「按值有序插入」的重载；`visit()` 改为接受输出器，去掉对 `std::cout` 的硬依赖
- `vector`：补 `reserve` / `swap` / `operator==` / `resize`，并把 `reallocate` 抽成带参数的 `reallocate_to`
- `stack` / `queue`：补 `#pragma once`，`size()` 加 `const`，`push` 改 `const&`
- `list`：补 `operator->` 与 5 个迭代器类型别名
- 学习并接入移动语义（`noexcept` 移动构造、`std::move_if_noexcept`）

## 开发记录

- `CHANGELOG.txt` —— 按日期记录的功能变更
- `need.txt` —— 待办与设想

## 编码

源码统一使用 **UTF-8 with BOM**，Visual Studio 与 GitHub 均可正确显示中文注释。

## 说明

项目仍在开发中，接口与实现会持续调整。
