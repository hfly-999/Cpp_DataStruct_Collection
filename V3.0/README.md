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
| 字符串 `String` | `String.h` / `.cpp` | ✅ **可用**：底层是 `DSL::vector<char>`（自己不碰 `new` / `delete`）；`const char*` / `std::string` / `initializer_list` / 拷贝构造、拷贝赋值；`begin` / `end`（各两个 const 版本，返回 `char*`）、`operator[]`（带 `assert` 越界检查）、`size` / `capacity` / `empty`；`BF` / `KMP` 子串匹配 + `Getnext` / `Getnextval`（返回 `vector<size_t>`） |
| 唯一指针 `Unique_ptr` | `Unique_ptr.h` / `.cpp` | 🚧 未完成：缺移动语义、`release` / `reset` |
| 二叉树 `BTree` | `Tree.h` / `.inl` / `.cpp` | ✅ **可用**：`Insert(value, path)` 按 `"l"/"r"` 路径建树；先序 / 中序 / 后序 / 层次遍历**全部非递归**（显式栈 / 队列）；析构用层次遍历删除，深树不爆栈 |
| 线索二叉树 `ThreadTree` | `Tree.h` / `.inl` | ✅ **可用**：共用同一套建树逻辑 + `InThread()` 中序线索化；`getfirstnode` / `getlastnode` / `getnextnode` / `getprenode` 四个导航函数；**`iterator` / `const_iterator` 支持 `++` / `--` 双向遍历，中序不再用栈**；`DeThread()` 去线索化，把树还原成普通二叉树 |
| 哈夫曼树 `HuffmanTree` | `Tree.h` | ❌ **已移除，待重写**：原实现的构造函数在 `hash_list` 尚未扩容时就下标访问、`std::priority_queue<HNode*>` 按地址而非权重排序、空串会解引用空堆、且没有析构函数。类定义已从 `Tree.h` 删除，目前只留下 `HNode`；重写时按「待改进」里那份清单逐条避开 |

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

### `String`：把内存管理整个交给 `vector<char>`

- 整个类只有**一个成员**：`DSL::vector<char> string`。扩容、构造、析构、深拷贝全部复用 `vector`，`String` 自己**不碰 `new` / `delete`**
- 因此拷贝构造只需要 `: string(obj.string)` 一行，析构直接 `= default` —— 深拷贝的正确性由 `vector` 保证，不在 `String` 里重写一遍
- `operator=` 是显式的 `String& operator=(const String&)`，内部交给 `vector<char>::operator=`（它自带自赋值保护）。**必须写 `return *this;`** —— 非 `void` 函数走到末尾而不返回值是未定义行为，`a = b = c` 会拿到一个垃圾引用
- 三类构造：`String("abc")`、`String(std::string)`、`String{'a','b','c'}`（`initializer_list` 直接转交给 `vector` 的同名构造）
- `begin()` / `end()` 直接返回 `vector<char>::begin()` / `end()`（也就是 `char*`），所以范围 `for` 可以直接用
- `operator[]` 里带 `assert(index < size())`，Debug 下越界会立刻断在出错的那一行，而不是跑到别处才崩
- `Getnext()` / `Getnextval()` 返回 `DSL::vector<size_t>` 而不是裸指针 —— `next` 数组的生命周期跟着返回值走，调用方不需要（也无法）`delete[]`
- `BF` 是暴力匹配；`KMP` 用 `Getnext` / `Getnextval` 求出的数组跳转。两者都返回子串在母串中的首位置

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
- **去线索化（`DeThread` → `DeInthread`）**：反向操作 —— 遍历一遍，把 `ltag` / `rtag` 为真的节点复位为 `false`，并把那条线索指针置空。这样同一个节点类型可以在「线索态」和「普通二叉树态」之间来回切换
- 去线索化用 `left()` / `right()`（返回**真孩子**）判断能不能往下走，而不是直接信 `lchild` / `rchild` —— 否则会顺着线索跳到祖先上去，跟 `delete_tree` 犯同一个错
- 去线索化是**显式栈的迭代版**，靠一个 `ispush` 标记区分「这一轮该往下压栈」还是「刚出栈、该处理当前节点」：压栈阶段只往左走，出栈阶段才复位 tag、再把右孩子压回去

### `HuffmanTree`：设计记录（类已移除，下面是重写时要保留的思路）

- `HNode` 只存 `we`（权重）/ `val`（字符）/ `lchild` / `rchild`，不留任何建树或编码逻辑
- 建树流程：先扫一遍字符串统计每个字符的频次，把**频次非零**的字符各造一个叶子节点丢进堆，然后循环「弹出两个、造一个父节点、压回去」，直到堆里只剩一个节点，它就是 `root`
- 叶子节点存原字符，合并出来的内部节点字符位置填 `'\0'` —— 编码时靠「往左走记 0、往右走记 1」区分，不依赖节点自己记编码
- `HNode` 的拷贝构造与拷贝赋值都 `= delete`：树节点一旦被拷贝，父子指针就会指回原树，等于制造两个「根」

## 待改进

按模块列出尚未做完的部分。

### `vector`

- 缺 `reserve` / `swap` / `operator==` / `resize` / `data()`
- `reverse(size_t n)` 会**析构全部 `Size` 个元素**再换内存，语义上等于「清空 + 重设容量」，末尾已把 `Size` 归零；但它不保留任何元素，与标准库的 `reserve`（保留元素、只改容量）完全不同，名字却只差两个字母，调用时极易看错
- 容量缩小时不检查 `n >= Size`（`Size` 已归零，所以当前不会破坏 `Capacity >= Size`，但语义上仍是一次「清空」）
- `~vector()` 已去掉 `virtual`（不再需要多态删除）
- `check()` 未声明为 `const`
- 要求 `type` 可默认构造（`insert` 中的 `new (Data + size) type()`）；接入移动语义后可放宽

### `list`

- 迭代器缺 `operator->`，`it->member` 无法使用
- 迭代器缺 5 个类型别名（`value_type` 等），暂时无法与 `std::find` / `std::distance` 等标准算法配合
- `~list()` 无需 `virtual`

### `stack` / `queue`

- `stack::top()` 用 `*(c.end() - 1)` 实现，**隐含要求底层容器支持随机访问** —— 换成 `list` 会编不过，这一点应在注释里写明
- `queue::back()` 同样用 `*(--c.end())`，也要求随机访问

### `String`

- 仍缺「长度 + 字符」构造（`String(size_t n, char c)`）
- 没有 `c_str()` / `data()`，无法直接交给 C 接口
- `KMP` 每次调用都重新求一遍 `nextval`；短串无所谓，长文本反复匹配时应把 `nextval` 缓存到对象里

### `Tree` / `ThreadTree`

- `insert` 的回滚路径已重写：**先摘父链接 → 再 `delete_tree` → 最后 `return false`**。当新建的树就是根（没有父节点）时，把 `root` 置空 —— 此前这种情况会让 `root` 悬空，析构时对已释放的根再删一次。**改动后尚未在 ASan / CRT 下正式复验**
- **`InThread()` 只能调用一次**：重复线索化时 `lchild` 已指向前驱，遍历会跳到别的子树上去。目前没有 `threaded` 标志做保护
- `DeInthread` 已从递归改为**显式栈的迭代版**，深树不再爆栈；但它靠 `ispush` 标记驱动，控制流是「压栈阶段只往左、出栈阶段处理当前节点再压右孩子」，比 `delete_tree` 的层次遍历更难一眼看懂
- 四个测试函数（`btree_insert_test_1/2/3`、`thread_tree_insert_test`）是**非模板自由函数，直接定义在 `Tree.h` 里**：一旦被两个以上翻译单元包含，链接期会重复定义。应加 `inline`，或声明留在 `.h`、定义移到 `.cpp`
- `delete_tree` 与 `delete_thread_tree` 几乎是同一份代码，只差两个 tag 判断。如果让 `ThreadNode::left()` / `right()` 在 `ltag` / `rtag` 为真时返回 `nullptr`，再另配 `raw_left()` / `raw_right()` 供线索化使用，两份可以合并成一份
- `iterator` 的 `operator*` 已随 `operator==` / `operator!=` 一起补上 `const`；`const_iterator` 的四处错误（`operator++(int)` / `operator--(int)` 的局部变量与返回值写成 `iterator`、比较运算符形参写成 `const iterator&`）也已修正，现在可以正常实例化
- `BTree::operator=` 的返回类型写成了 `BTree`，应为 `BTree&`（`ThreadTree` 那处是对的）
- `Insert(value, path)` 用 `"l"/"r"` 字符串描述路径，更像「按图纸建树」而不是「按值有序插入」；若要当 BST 用，需要再补一个按序插入的重载
- `BNode::visit()` 内部直接写 `std::cout`，隐含要求元素类型可流输出（装一个没有 `operator<<` 的 `struct` 会编不过）
- `Tree.h` 顶部 `#include` 了 `mystack.h` / `myqueue.h`，即与「栈 / 队列用哪种容器实现」这件事耦合；更彻底的做法是把容器提成模板参数

### `HuffmanTree`（类已移除，以下是有过的缺陷，重写时逐条避开）

- **`hash_list[*it]++` 越界**：`hash_list` 是默认构造的 `vector<size_t>`，`size == 0`、`capacity == 0`、`Data == nullptr`；构造里没有先扩容就下标访问，`operator[]` 的 `assert(index < Size)` 在 Debug 下会立刻断在这里，Release 下是往空指针上写
- **比较器比较的是指针地址**：`std::priority_queue<HNode*>` 用默认的 `less<HNode*>`，它按**地址大小**排序，而不是按 `weight()` —— 弹出的两个并不是权值最小的两个，建出来的不是哈夫曼树
- **空串会解引用空堆**：若入参字符串为空，没有任何节点入堆，`while (heap.size() != 1)` 依然成立，紧接着 `heap.top()` 作用在空容器上
- `*it` 的类型是 `char`：若 `char` 为有符号、读到高位字节（≥ 0x80，中文 UTF-8 必现），转成 `size_t` 下标会得到极大值
- `translate_list`（译码表）声明了但从未写入；`HuffmanTree` 没有析构函数，`new` 出来的 `HNode` 与 `root` 都不会释放
- 内部依赖 `std::priority_queue`（新增了 `#include<queue>`），与本项目「不依赖 STL 容器」的前提不一致；要贯彻这一前提，需要自己写一个堆，或复用已有的 `vector` 手写 `push_heap` / `pop_heap`
- 类删除后 `HNode` 仍留在 `Tree.h` 里，`friend class HuffmanTree;` 现在指向一个**不存在的类**（合法，只是引入了一个未定义的 `DSL::HuffmanTree`）；重写时这两处要么一起补上、要么一起删掉

## 目录约定

- `.h` —— 类声明与接口
- `.inl` —— 模板成员函数的实现，由对应的 `.h` 在末尾包含
- `.cpp` —— 每个功能一个测试函数，注释中写明期望输出

## 下一步

- `Tree`：回滚路径改动后在 ASan / CRT 下复验；给 `InThread()` 加 `threaded` 标志，防止重复线索化
- `Tree`：合并 `delete_tree` / `delete_thread_tree`；给 `InThread()` 加 `threaded` 标志，防止重复线索化；把 `DeInthread` 的 `ispush` 标记式控制流改写成更直白的「先一路压左、出栈时处理、再转右」
- `Tree`：测试函数加 `inline` 或移到 `.cpp`；`BTree::operator=` 的返回类型改回 `BTree&`
- `Tree`：`Insert` 增加「按值有序插入」的重载；`visit()` 改为接受输出器，去掉对 `std::cout` 的硬依赖
- `HuffmanTree`：按「待改进」清单从零重写 —— `hash_list` 先扩容再下标访问；堆的比较器改成按 `weight()`；空串先判空；补析构函数释放节点；写出编码表与译码；把 `std::priority_queue` 换成自己的堆
- `vector`：补 `reserve` / `swap` / `operator==` / `resize`，并把 `reallocate` 抽成带参数的 `reallocate_to`
- `list`：补 `operator->` 与 5 个迭代器类型别名
- 学习并接入移动语义（`noexcept` 移动构造、`std::move_if_noexcept`）

## 开发记录

- `CHANGELOG.txt` —— 按日期记录的功能变更
- `need.txt` —— 待办与设想

## 编码

源码统一使用 **UTF-8 with BOM**，Visual Studio 与 GitHub 均可正确显示中文注释。

## 说明

项目仍在开发中，接口与实现会持续调整。
