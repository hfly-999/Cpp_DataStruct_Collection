# Cpp_DataStruct_Collection

C++ 数据结构项目合集，按编写时间归档。

## 版本

| 版本 | 时间 | 来源 | 内容 |
| --- | --- | --- | --- |
| V1.0 | 2025-08-07 | Cpp_DataStruct_2025_8_7 | 数据结构基础库：顺序表、链表、栈、队列、字符串、树、图、查找、排序 |
| V2.0 | 2026-05-22 | Cpp_OOP_DataStruct | 面向对象数据结构第一版：泛型链表/栈/队列、二叉树与哈夫曼树、二叉排序树/AVL/红黑树、泛型顺序表与堆、字符串 BF/KMP、泛型图 |
| V3.0 | 2026-08-14 | Cpp_OOP_DataStruct_v2 | `DSL` 命名空间数据结构库：list / vector / String / Unique_ptr、双迭代器、非递归遍历 |

## 各版本说明

### V1.0（2025-08-07）

- 20 个源文件
- 模块：`SqList`、`LinkList`、`Stack`、`Queue`、`String`、`Tree`、`Graph`、`Search`、`Sort`
- 以 C 风格 + C++ 实现的基础数据结构库，`main.cpp` 为简单入口

### V2.0（2026-05-22）

- 32 个文件（源码 + Visual Studio 工程）
- 模块：泛型单链表/双链表、泛型栈（`DeQueue`）、泛型队列（`EnQueue` / `DeQueue`）、二叉树与哈夫曼树、二叉排序树/二叉搜索树/AVL/红黑树、泛型顺序表与泛型堆、字符串 BF/KMP 匹配、泛型图
- 原作者 README 标注的未完成部分：深浅拷贝问题、模板类型不支持 `std::string` 等复杂类型、AVL/RBT 部分算法、`ALGraph` 部分、图的最小生成树（Kruskal / Prim）
- 仅收录源码与工程文件，未包含原仓库的 `.vs` 缓存和编译产物

### V3.0（2026-08-14）

- 29 个文件
- `DSL`（DataStructLibrary）命名空间的 OOP 数据结构库：`list` / `vector` / `String` / `Unique_ptr`、`iterator` + `const_iterator`、非递归遍历
- 模块状态详见 `V3.0/README.md`

## 目录结构

```
Cpp_DataStruct_Collection/
├── README.md
├── V1.0/
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
├── V2.0/
│   ├── *.h / *.cpp / *.inl
│   ├── Cpp_DataStruct_2026_5_22.sln
│   ├── Cpp_DataStruct_2026_5_22.vcxproj
│   └── README.md
└── V3.0/
    ├── mylist.h / .inl / .cpp
    ├── myvector.h / .cpp
    ├── String.h / .cpp / .inl
    ├── Unique_ptr.h / .cpp
    ├── Stack.h / .inl / .cpp
    ├── Queue.h / .inl / .cpp
    ├── Tree.h / .inl / .cpp
    ├── Cpp_OOP_DataStruct_2026_8_14.sln
    └── README.md
```

## 编译

- **V2.0**：用 Visual Studio 打开 `V2.0/Cpp_DataStruct_2026_5_22.sln` 编译
- **V3.0**：用 Visual Studio 2022 打开 `V3.0/Cpp_OOP_DataStruct_2026_8_14.sln`，选择 x64 配置编译
- **V1.0**：原项目只提交了源码、没有工程文件，可自行新建控制台项目或按源码组织编译

## 来源

- V1.0 来自 `Cpp_DataStruct_2025_8_7`
- V2.0 来自 `Cpp_OOP_DataStruct`
- V3.0 来自 `Cpp_OOP_DataStruct_v2`

V1.0 和 V3.0 通过 `git subtree` 合并，保留各自提交历史；V2.0 的原仓库含 380MB 构建缓存，因此只导入了源码与工程文件。
