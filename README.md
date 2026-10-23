# Cpp_OOP_DataStruct_v2

用 C++ 从零手写的一个数据结构库，命名空间为 `DSL`（DataStructLibrary）。

这是学习 C++ 面向对象与数据结构过程中的实践项目：容器均自行实现，不依赖 STL 容器，目的是把内存管理、拷贝语义、迭代器与经典算法真正写一遍。

## 编译环境

- Visual Studio 2022（v143 工具集）
- C++14（项目当前默认语言标准）
- 全部配置已开启 `/utf-8`，源码可以放心用 UTF-8 保存
- 用 VS 打开 `Cpp_OOP_DataStruct_2026_8_14.sln`，选择 `x64` 配置即可编译

## 模块状态

| 模块 | 文件 | 状态 |
| --- | --- | --- |
| 单链表 `list` | `mylist.h` / `.inl` / `.cpp` | ✅ **可用**：双向循环 + 单哨兵；构造 / `initializer_list` 构造 / 拷贝构造 / 拷贝赋值 / 析构；`insert` / `erase` / `push_front` / `push_back` / `pop_front` / `pop_back` / `clear` / `front` / `back` / `size` / `empty` / `reverse`；嵌套迭代器；`check()` 不变量自检 |
| 顺序表 `vector` | `myvector.h` / `.cpp` | 🚧 **可用但待打磨**：原始内存分配（`::operator new` + placement new）、默认 / `initializer_list` / 拷贝构造、拷贝赋值；`insert`（任意位置，容量不足自动扩容）/ `push_back` / `push_front` / `clear` / `operator[]` / `front` / `back` / `size` / `capacity` / `empty` / `begin` / `end`；`erase` / `pop_back` / `reserve` 与 `const` 重载尚缺 |
| 字符串 `String` | `String.h` / `.cpp` | ✅ 已实现：BF 与 KMP 子串匹配（含 `next` / `nextval` 数组） |
| 唯一指针 `Unique_ptr` | `Unique_ptr.h` / `.cpp` | 🚧 未完成：缺移动语义、`release` / `reset` |
| 顺序栈 / 链栈 | `Stack.h` / `.inl` / `.cpp` | ⏸ 已实现，随底层接口重构暂时注释 |
| 链队列 | `Queue.h` / `.inl` / `.cpp` | ⏸ 已实现，随底层接口重构暂时注释 |
| 二叉树 | `Tree.h` / `.inl` / `.cpp` | ⏸ 已实现，先序/中序/后序/层次遍历均为非递归，随底层接口重构暂时注释 |

## 实现要点

### `list`：双向循环链表 + 单哨兵

- 只有一个哨兵节点 `Head`，空表时自指：`Head->next == Head->prior == Head`
- `Head->next` 是首元素，`Head->prior` 是尾元素
- 因此「插入」只有一种情况 —— 在某个节点**之前**插入，不需要为首尾写任何特例
- `check()` 在 Debug 下校验三件事：节点数与 `length` 一致、双向指针互相一致、环闭合

### `vector`：原始内存 + placement new

- 用 `::operator new` **只申请字节，不构造任何对象**
- 元素用 placement new 在指定地址上构造；析构时逐个显式调用 `~type()`
- `[0, size)` 是活对象，`[size, capacity)` 是未构造的原始内存 —— **这是 `size` 与 `capacity` 能分开的根本原因**
- 扩容时按 1.5 倍增长（`calcapacity`，下限为 2）
- 所有插入都走同一个 `insert`：先用 `pos - Data` 算出下标（**必须在扩容之前算** —— 扩容会换掉 `Data`），再按需扩容，然后把 `[pos, size)` 从后往前整体后移一格，最后在 `pos` 处构造新元素

## 待改进

`vector` 目前已知的几处问题，按优先级排列：

- `operator=` 缺自赋值保护，`v = v` 会把自己清空
- `insert(pos, v[k])`：当被插入的值引用的是本容器中**位于插入点之后**的元素时，移位过程会先析构该元素，导致插入错误数据（静默错误，不崩溃）
- `begin` / `end` 的 `const` 版本返回非 `const` 指针，`const` 对象可被修改
- `operator[]` / `front` / `back` 缺 `const` 重载，`front` / `back` 按值返回
- `~vector()` 无需 `virtual`

## 目录约定

- `.h` —— 类声明与接口
- `.inl` —— 模板成员函数的实现，由对应的 `.h` 在末尾包含
- `.cpp` —— 每个功能一个测试函数，注释中写明期望输出

## 下一步

- `vector`：修「待改进」里列出的几项（自赋值保护、`insert` 自引用、`const` 重载等），合计不到 15 行
- `vector`：补 `erase` / `pop_back` / `reserve` / `resize`
- `vector`：学习并接入移动语义（`noexcept` 移动构造、`std::move_if_noexcept`）
- 取消 `Stack` / `Queue` / `Tree` 的注释，改为基于新的 `list` 实现

## 开发记录

- `CHANGELOG.txt` —— 按日期记录的功能变更
- `need.txt` —— 待办与设想

## 编码

源码统一使用 **UTF-8 with BOM**，Visual Studio 与 GitHub 均可正确显示中文注释。

## 说明

项目仍在开发中，接口与实现会持续调整。
