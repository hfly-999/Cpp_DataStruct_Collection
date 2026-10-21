# Cpp_OOP_DataStruct_v2

用 C++ 从零手写的一个数据结构库，命名空间为 `DSL`（DataStructLibrary）。

这是学习 C++ 面向对象与数据结构过程中的实践项目：容器均自行实现，不依赖 STL 容器，目的是把内存管理、拷贝语义、迭代器与经典算法真正写一遍。

## 编译环境

- Visual Studio 2022（v143 工具集）
- C++14（项目当前默认语言标准）
- 用 VS 打开 `Cpp_OOP_DataStruct_2026_8_14.sln`，选择 `x64` 配置即可编译

## 模块状态

| 模块 | 文件 | 状态 |
| --- | --- | --- |
| 顺序表 `SeqList` | `SeqList.h` / `.inl` / `.cpp` | 已实现：动态扩容与缩容、深拷贝、拷贝赋值、`operator[]`、迭代器雏形 |
| 单链表 `LinkList` | `LinkList.h` / `.inl` / `.cpp` | **重构中**：哨兵头结点 + 尾指针，拷贝构造与赋值已重写 |
| 字符串 `String` | `String.h` / `.cpp` | 已实现：BF 与 KMP 子串匹配（含 `next` / `nextval` 数组） |
| 唯一指针 `Unique_ptr` | `Unique_ptr.h` / `.cpp` | 未完成：缺移动语义、`release` / `reset` |
| 顺序栈 / 链栈 | `Stack.h` / `.inl` / `.cpp` | 已实现（基于 `SeqList` / `LinkList`），随底层接口重构暂时注释 |
| 链队列 | `Queue.h` / `.inl` / `.cpp` | 已实现（基于 `LinkList`），随底层接口重构暂时注释 |
| 二叉树 | `Tree.h` / `.inl` / `.cpp` | 已实现，先序/中序/后序/层次遍历均为非递归，随底层接口重构暂时注释 |

## 目录约定

- `.h` —— 类声明与接口
- `.inl` —— 模板成员函数的实现，由对应的 `.h` 在末尾包含
- `.cpp` —— 每个功能一个测试函数，注释中写明期望输出

## 开发记录

- `CHANGELOG.txt` —— 按日期记录的功能变更
- `need.txt` —— 待办与设想

## 编码

源码统一使用 **UTF-8 with BOM**，Visual Studio 与 GitHub 均可正确显示中文注释。

## 说明

项目仍在重构中，接口与实现会持续调整。
