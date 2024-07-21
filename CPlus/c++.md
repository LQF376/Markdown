# 1. 数据类型

- 给变量分配合适的内存

## 1.1 基本数据类型

### 整型

| 类型      | 所占字节                                         |
| --------- | ------------------------------------------------ |
| short     | 2 字节                                           |
| int       | 4 字节                                           |
| long      | Windows（4 字节） Linux 32（4字节） 64（8 字节） |
| long long | 8 字节                                           |

typedef 声明

- 为一个已有的类型取一个新的名字

```cpp
typedef type newname;

typedef int feet;
feet distance;		// 合法
```

枚举类型

- 如果一个变量只有几种可能的值，可定义为枚举类型；即将变量的值一一列举出来，变量的值只能在列举出来的值的范围
- 默认情况下，第一个名称的值为0，逐后开始递增
- 内存方面注意**字节对齐**

```cpp
enum 枚举名{
	标识符 [=整数常数],
	标识符 [=整数常数],
	标识符 [=整数常数],
	标识符 [=整数常数]
} 枚举变量；

enum color{ red, green, blue} c;
c = blue;
```

`sizeof`查看变量的大小

```cpp
sizeof <数据类型/变量>

int a;
sizeof(a);
sizeof(int);
```

### 1.2 浮点数

| 类型   | 所占字节 |
| ------ | -------- |
| float  | 4 字节   |
| double | 8 字节   |

```
float a = 3.14f;		// f 代表 float，默认是 double
```

### 1.3 字符型

- 字符型本质是用ASCII码存放的整数类型

| 类型 | 所占字节 |
| ---- | -------- |
| char | 1 字节   |

```
char ch = 'a';		// 单引号注意
```

### 1.4 转义字符

- 显示一些不能显示出来的 ASCII 字符

### 1.5 字符串

C++ 提供了以下两种类型的字符串表示形式：

- C 风格字符串
- C++ 引入的 string 类类型

#### C 风格字符串

C 风格的字符串实际上是使用 **null** 字符 **`\0`** 终止的一维字符数组

```cpp
/* C 语言风格 */
char site[7] = {'R', 'U', 'N', 'O', 'O', 'B', '\0'};
char site[] = "RUNOOB";

char name[] = "xxxxxx";			// C 语言风格
string name = "xxxxxx";			// C++ 语言风格
```

C++ 中有大量的函数用来操作以 null 结尾的字符串:

| 函数                  | 解释                                                         |
| --------------------- | ------------------------------------------------------------ |
| **`strcpy(s1, s2);`** | 复制字符串 s2 到字符串 s1                                    |
| **`strcat(s1, s2);`** | 连接字符串 s2 到字符串 s1 的末尾。连接字符串也可以用 **+** 号【string】 |
| **`strlen(s1);`**     | 返回字符串 s1 的长度                                         |
| **`strcmp(s1, s2);`** | 如果 s1 和 s2 是相同的，则返回 0；<br />如果 s1<s2 则返回值小于 0；如果 s1>s2 则返回值大于 0 |
| **`strchr(s1, ch);`** | 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置     |
| **`strstr(s1, s2);`** | 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置   |

#### String 类

C++ 标准库提供了 **string** 类类型

## 1.2 类型转换

- 将一个数据类型的值转换为另一种数据类型的值

C++提供4种类型转换：静态转换、动态转换、常量转换、重新解释转换

### 静态转换`Static Cast`

- 将一种数据类型的值强制转换为另一种数据类型的值
- 不进行任何运行时的类型检查，可能会导致运行时错误

```
int i = 10;
float f = static_cast<float>(i);	// int ---> float
```

### 动态类型转换`Dynamic Cast`

- 将一个基类指针或引用转换为派生类指针或引用
- 在运行时进行类型转换，如果不能进行转换则返回空指针或引发异常

```c++
class Base{};

class SubClass:public Base{};
Base *ptr_base = new SubClass;
SubClass *ptr_subclass = dynamic_cast<SubClass*>(ptr_base);		// 将基类指针转换为派生类指针
```

###  常量转换`Const Cast`

- 将const类型的对象转换为非const类型的对象
- 只能用于转换掉const属性，不能改变对象的类型

```c++
const int i = 10;
int& r = const_cast<int&>(i);	// const int ---> int
```

重新解释转换`Reinterpret Cast`

- 将一个数据类型的值重新解释为另一个数据类型的值，通常用于在不同数据类型之间进行转换
- 不进行任何类型检查，因此可能会导致未定义行为

```
int i = 10;
float f = reinterpret_cast<float&>(i);	//	 int ---> float
```

# 2. 变量定义/声明

### 变量定义

变量名由字母、数字、下划线组成，必须以字母或下划线开头

```c++
type variable_list;

int i, j, k;		// 未初始化
int d = 2, f = 5;	// 声明时候带初始化
```

不带初始化的定义：带有静态存储持续时间的变量会被隐式初始化为`NULL`（所有字节的值都是0），其他所有变量的初始值是未定义的

### 变量声明

可以在C++程序中多次声明一个变量，但变量只能在某个文件、函数、代码块中被定义一次

向编译器保证变量以给定的类型和名称存在，使之能在不知道变量完整细节的情况下进行进一步编译

#### `extern`外部变量

说明该变量为外部变量，变量的定义来自于其他文件

### 左值和右值

- 左值：指向内存位置的表达式被称为**左值表达式**；左值可以出现在赋值号的左边或右边
- 右值：存储在内存中某些地址的数值；右值不能对其进行赋值的表达式，只能出现在等号的右边

## 变量的作用域

- **局部作用域**：函数内部声明的变量具有局部作用域，只能在函数内部访问。在函数每次被调用时被创建，在函数执行完后被销毁
- **全局作用域**：所有函数和代码块之外声明的变量具有全局作用域，可以被程序中的任何函数访问。全局变量在程序开始时被创建，在程序结束时被销毁
- **块作用域**：代码块内部声明的变量具有块作用域，只能在代码块内部访问。块作用域变量在代码块每次被执行时被创建，在代码块执行完后被销毁
- **类作用域**：在类内部声明的变量具有类作用域，可以被类的所有成员函数访问。类作用域变量的生命周期与类的生命周期相同

当局部变量被定义时，系统不会对其进行初始化；定义全局变量时，系统会自动初始化为下列值

| 数据类型 | 初始化默认值 |
| -------- | ------------ |
| int      | 0            |
| char     | '\0'         |
| float    | 0            |
| double   | 0            |
| pointer  | NULL         |

# 3. 常量

- 固定值，在程序执行期间不会发生改变，定义后不能进行修改

### 整型常量

整型常量可以是十进制、八进制、十六进制，通过前缀来指定基数：

- `0x`或`0X`：十六进制
- `0`：八进制
- 不带前缀默认为十进制

整形常量可以带一个后缀，`U`和`L`的组合，可大写可小写

- `U`：无符号整数 unsigned
- `L`：长整数 long

```cpp
/* 合法整型常量 */
212
216u
0xff2L
078
```

### 浮点常量

由整数部分、小数点、小数部分和指数部分组成；可使用小数形式或者指数形式来表示浮点常量

- 小数表示时，必须包含整数部分、小数部分，或同时包含两者
- 指数表示时，必须包含小数点、指数，或同时包含两者。带符号的指数是用`e`或者`E`引入

```cpp
3.14159       // 合法的 
314159E-5L    // 合法的 
510E          // 非法的：不完整的指数
210f          // 非法的：没有小数或指数
.e55          // 非法的：缺少整数或分数
```

###  bool 布尔常量

- `true`= 1；`false`=0【关键字】

| 类型 | 所占字节 |
| ---- | -------- |
| bool | 1 字节   |

```
bool name = true;
```

### 字符常量

字符常量括在单引号中；可以是一个普通的字符`'x'`、一个转义序列`'\t'`，或者一个通用的字符`'\u02C0'`

- 常量以`L`开头，表示为一个宽字符常量，必须存储在`wchar_t`类型的变量中
- 此外就是一个窄字符常量，存储在`char`类型的简单变量中

转义字符

| 转义序列 | 含义       |
| -------- | ---------- |
| `\\`     | \          |
| `\'`     | '          |
| `\"`     | ''         |
| `\?`     | ?          |
| `\a`     | 警报铃声   |
| `\b`     | 退格键     |
| `\n`     | 换行符     |
| `\r`     | 回车       |
| `\t`     | 水平制表符 |

### 字符串常量

字符串常量是括在双引号`""`中的；可以使用`\`做分隔符，把一个很长的字符串常量进行分行

```cpp
string greet = "hello, \
				runoob";
```

### 常量定义

- 使用`#define`预处理器
- 使用`const`关键字

```cpp
/* 1. #define 预处理器 */
#define identifier value

#define LENGTH 10 

/* 2. const 关键字 */
const type variable = value;

const int LENGTH = 10;
```

# 4. 类型限定符

| 限定符   | 含义                                                         |
| -------- | ------------------------------------------------------------ |
| const    | **const** 定义常量，表示该变量的值不能被修改                 |
| volatile | **volatile** 告诉该变量的值可能会被程序以外的因素改变，如硬件或其他线程；禁止优化 |
| restrict | **restrict** 修饰的指针是唯一一种访问它所指向的对象的方式    |
| mutable  | 表示类中的成员变量可以在 const 成员函数中被修改              |
| static   | 定义静态变量，表示该变量的作用域仅限于当前文件或当前函数内，不会被其他文件或函数访问 |
| register | 定义寄存器变量，表示该变量被频繁使用，可以存储在CPU的寄存器中，以提高程序的运行效率 |

```cpp
/* mutable */
class Example {
public:
    int get_value() const {
        return value_; 		// const 关键字表示该成员函数不会修改对象中的数据成员
    }
    void set_value(int value) const {
        value_ = value; 	// mutable 关键字允许在 const 成员函数中修改成员变量
    }
private:
    mutable int value_;
};
```

---

## C++存储类

**存储类**定义C++ 程序中变量/函数的范围（可见性）和声明周期

- **auto**：默认的存储类说明符，通常省略不写。指定变量具有自动存储期，即它们的生命周期仅限于定义它们的块（block），auto 变量通常在栈上分配【C++11后有了新作用】
- **register**：用于建议编译器将变量存储在CPU寄存器中以提高访问速度。在 C++11 及以后的版本中，register 已经是一个**废弃**的特性，不再具有实际作用
- **static**：用于定义具有静态存储期的变量或函数，生命周期贯穿整个程序的运行期。在函数内部，static变量的值在函数调用之间保持不变。在文件内部或全局作用域，**static变量具有内部链接，只能在定义它们的文件中访问**
- **extern**：用于声明具有外部链接的变量或函数，它们可以在多个文件之间共享。默认情况下，全局变量和函数具有 extern 存储类。在一个文件中使用extern声明另一个文件中定义的全局变量或函数，可以实现跨文件共享
- **mutable (C++11)**：用于修饰类中的成员变量，允许在**const成员函数**中修改这些变量的值。通常用于缓存或计数器等需要在const上下文中修改的数据
- **thread_local (C++11)**：用于定义具有线程局部存储期的变量，每个线程都有自己的独立副本。线程局部变量的生命周期与线程的生命周期相同

---

### `auto`

自c++11以来，`auto`关键字用于两种情况：

- 声明变量时根据初始化表达式自动推断该变量的类型
- 声明函数时函数返回值的占位符

C++98 标准中 `auto` 关键字用于自动变量的声明，但由于使用极少且多余，**被删除**

### `register`

- 用于声明变量，并提示编译器将这些变量存储在寄存器中，提高程序的执行速度，减少了对内存的访问次数。
- 在 C++11 标准中，register 关键字不再是一个存储类说明符，而是一个废弃的特性

```cpp
register int i;
```

### `static`

在程序的生命周期内保持局部变量的存在，而不需要在每次它进入和离开作用域时进行创建和销毁

告知编译器，将变量存储在程序的静态存储区而非栈上

根据用法可分为局部静态变量、全局静态变量、静态函数、类数据成员

- static 修饰局部变量只执行初始化一次，延长了局部变量的生命周期，直到程序执行结束后才释放

- static 修饰全局变量时，使变量的作用域限制在声明它的文件内，不能在其他文件中访问
- static 修饰一个函数，则这个函数的只能在本文件中调用，不能被其他文件调用
- static 用在类数据成员上时，会导致仅有一个该成员的副本被类的所有对象共享

### `extern`

`extern` 修饰符通常用于当有两个或多个文件共享相同的全局变量或函数的时候

`extern` 提供一个全局变量的引用，全局变量对所有的程序文件都是可见的

当您有多个文件且定义了一个可以在其他文件中使用的全局变量或函数时，可以在其他文件中使用 `extern` 来得到已定义的变量或函数的引用

```cpp
#include<iostream>

int count;
extern void write_extern();

int main(){
	count = 5;
	write_extern();
}
```

```cpp
/* 第2个文件 */
#include<iostream>

extern int count;
void write_extern(void){
	std::cout << count << std::endl;
}
```

### `mutable`

### `thread_local`

`thread_local` 声明的变量仅可在它在其上创建的线程上访问

变量在创建线程时创建，并在销毁线程时销毁。 每个线程都有其自己的变量副本

`thread_local` 说明符可以与 `static` 或 `extern`联合使用

`thread_local`只能用于数据声明和定义，不能用于函数声明或定义

```cpp
thread_local int x;  // 命名空间下的全局变量

class X{
    static thread_local std::string s; // 类的static成员变量
};
static thread_local std::string X::s;  // X::s 是需要定义的
 
void foo(){
    thread_local std::vector<int> v;  // 本地变量
}
```

# 运算符

运算符是一种执行特定数学或逻辑操作的符号，主要包括：

## 算数运算符

若变量 A 的值为 10，变量 B 的值为 20

| 运算符 | 描述                             | 实例             |
| ------ | -------------------------------- | ---------------- |
| +      | 把两个操作数相加                 | A + B 将得到 30  |
| -      | 从第一个操作数中减去第二个操作数 | A - B 将得到 -10 |
| *      | 把两个操作数相乘                 | A * B 将得到 200 |
| /      | 分子除以分母                     | B / A 将得到 2   |
| %      | 取模运算符，整除后的余数         | B % A 将得到 0   |
| ++     | 自增运算符，整数值增加 1         | A++ 将得到 11    |
| --     | 自减运算符，整数值减少 1         | A-- 将得到 9     |

## 关系运算符

若变量 A 的值为 10，变量 B 的值为 20

| 运算符 | 描述                                                         | 实例              |
| ------ | ------------------------------------------------------------ | ----------------- |
| ==     | 检查两个操作数的值是否相等，如果相等则条件为真。             | (A == B) 不为真。 |
| !=     | 检查两个操作数的值是否相等，如果不相等则条件为真。           | (A != B) 为真。   |
| >      | 检查左操作数的值是否大于右操作数的值，如果是则条件为真。     | (A > B) 不为真。  |
| <      | 检查左操作数的值是否小于右操作数的值，如果是则条件为真。     | (A < B) 为真。    |
| >=     | 检查左操作数的值是否大于或等于右操作数的值，如果是则条件为真。 | (A >= B) 不为真。 |
| <=     | 检查左操作数的值是否小于或等于右操作数的值，如果是则条件为真。 | (A <= B) 为真。   |

## 逻辑运算符

变量 A 的值为 1，变量 B 的值为 0

| 运算符 | 描述                                                         | 实例                 |
| ------ | ------------------------------------------------------------ | -------------------- |
| `&&`   | 逻辑与运算符。如果两个操作数都 true，则条件为 true           | (A && B) 为 false。  |
| `||`   | 逻辑或运算符。如果两个操作数中有任意一个 true，则条件为 true | (A \|\| B) 为 true。 |
| `!`    | 逻辑非运算符。用来逆转操作数的逻辑状态，如果条件为 true 则逻辑非运算符将使其为 false。 | !(A && B) 为 true。  |

## 位运算符

`A = 0011 1100; B = 0000 1101`

```
A&B = 0000 1100

A|B = 0011 1101

A^B = 0011 0001

~A  = 1100 0010
```

| 运算符 | 描述                                                         | 实例                                                         |
| ------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| &      | 按位与操作，按二进制位进行"与"运算。运算规则：`0&0=0;    0&1=0;     1&0=0;      1&1=1;` | (A & B) 将得到 12，即为 0000 1100                            |
| \|     | 按位或运算符，按二进制位进行"或"运算。运算规则：`0|0=0;    0|1=1;    1|0=1;     1|1=1;` | (A \| B) 将得到 61，即为 0011 1101                           |
| ^      | 异或运算符，按二进制位进行"异或"运算。运算规则：`0^0=0;    0^1=1;    1^0=1;   1^1=0;` | (A ^ B) 将得到 49，即为 0011 0001                            |
| ~      | 取反运算符，按二进制位进行"取反"运算。运算规则：`~1=-2;    ~0=-1;` | (~A ) 将得到 -61，即为 1100 0011，一个有符号二进制数的补码形式。 |
| <<     | 二进制左移运算符。将一个运算对象的各二进制位全部左移若干位（左边的二进制位丢弃，右边补0）。 | A << 2 将得到 240，即为 1111 0000                            |
| >>     | 二进制右移运算符。将一个数的各二进制位全部右移若干位，正数左补0，负数左补1，右边丢弃。 | A >> 2 将得到 15，即为 0000 1111                             |

## 赋值运算符

| 运算符 | 描述                                                         | 实例                            |
| ------ | ------------------------------------------------------------ | ------------------------------- |
| =      | 简单的赋值运算符，把右边操作数的值赋给左边操作数             | C = A + B 将把 A + B 的值赋给 C |
| +=     | 加且赋值运算符，把右边操作数加上左边操作数的结果赋值给左边操作数 | C += A 相当于 C = C + A         |
| -=     | 减且赋值运算符，把左边操作数减去右边操作数的结果赋值给左边操作数 | C -= A 相当于 C = C - A         |
| *=     | 乘且赋值运算符，把右边操作数乘以左边操作数的结果赋值给左边操作数 | C *= A 相当于 C = C * A         |
| /=     | 除且赋值运算符，把左边操作数除以右边操作数的结果赋值给左边操作数 | C /= A 相当于 C = C / A         |
| %=     | 求模且赋值运算符，求两个操作数的模赋值给左边操作数           | C %= A 相当于 C = C % A         |
| <<=    | 左移且赋值运算符                                             | C <<= 2 等同于 C = C << 2       |
| >>=    | 右移且赋值运算符                                             | C >>= 2 等同于 C = C >> 2       |
| &=     | 按位与且赋值运算符                                           | C &= 2 等同于 C = C & 2         |
| ^=     | 按位异或且赋值运算符                                         | C ^= 2 等同于 C = C ^ 2         |
| \|=    | 按位或且赋值运算符                                           | C \|= 2 等同于 C = C \| 2       |

## 杂项运算符

```
Condition ? X:Y;		// 条件运算符。如果 Condition 为真 ? 则值为 X : 否则值为 Y

a, b, c;	// 逗号运算符会顺序执行一系列运算。整个逗号表达式的值是以逗号分隔的列表中的最后一个表达式的值

a->b;	// 成员运算符用于引用类、结构和共用体的成员。
a.b;

int(2.2000);	// 强制转换运算符把一种数据类型转换为另一种数据类型。例如，int(2.2000) 将返回 2

&a;   // 指针运算符 & 返回变量的地址。例如 &a; 将给出变量的实际地址

*a;		// 	指针运算符 * 指向一个变量
```

# 循环语句

## 循环类型

| 循环类型        | 描述                                                         |
| --------------- | ------------------------------------------------------------ |
| while 循环      | 当给定条件为真时，重复语句或语句组。它会在执行循环主体之前测试条件 |
| for 循环        | 多次执行一个语句序列，简化管理循环变量的代码                 |
| do...while 循环 | 除了它是在循环主体结尾测试条件外，其他与 while 语句类似      |
| 嵌套循环        | 您可以在 while、for 或 do..while 循环内使用一个或多个循环    |

## 循环控制语句

| 控制语句      | 描述                                                         |
| ------------- | ------------------------------------------------------------ |
| break 语句    | 终止 **loop** 或 **switch** 语句，程序流将继续执行紧接着 loop 或 switch 的下一条语句。 |
| continue 语句 | 引起循环跳过主体的剩余部分，立即重新开始测试条件。           |
| goto 语句     | 将控制转移到被标记的语句。但是不建议在程序中使用 goto 语句。 |

# 选择语句

- if 语句
- 三目运算符
- switch 语句

```
Exp1 ? Exp2 : Exp3;
```

# 函数

## 函数定义

**函数签名**：函数名+参数列表（注意没有返回值类型！关系重载问题）

```cpp
return_type function_name( parameter list ){
   body of the function
}
```

## 调用函数

当程序调用函数时，程序控制权会转移给被调用的函数。被调用的函数执行已定义的任务，当函数的返回语句被执行时，或到达函数的结束括号时，会把程序控制权交还给主程序。

调用函数时，有三种向函数传递参数的方式

- 传值调用
- 指针调用
- 引用调用

### 传值调用

- 把参数的实际值赋值给函数的形参【拷贝】。修改函数内的形式参数对实际参数没有影响

```cpp
void swap(int x, int y){
	// ...
}

int main(){
	swap(a, b);
}
```

### 指针调用

- 把参数的地址赋值给形参。在函数内，该地址用于访问调用中要用到的实参。这意味着，修改形式参数会影响实际参数。

```cpp
void swap(int *x, int *y){
	// ...
}

int main(){
	int a, b;
	swap(&a, &b);
}
```

### 引用调用

- 参数的引用赋值给形式参数。在函数内，该引用用于访问调用中要用到的实际参数。这意味着，修改形式参数会影响实际参数

```cpp
void swap(int& x, int& y){
	// ....
}

int main(){
	int a, b;
	swap(a, b);
}
```

## 函数的默认参数

形参列表中的形参可以有默认值

1. 如果某个位置参数有默认值，从这个位置往后【从左往右】，必须都有默认值
2. 如果函数声明有默认值，函数实现的时候就不能有默认值【不能同时拥有】

## 函数的占用参数

形参列表里可以有占位参数，用来占位，调用函数时必须填补该位置

占位参数也可以有默认参数

```cpp
void fun(int a, int = 10);		// 只写数据类型进行占位
```

## 函数的重载

相同的函数名，具有不同的函数签名！提高代码的复用性

函数重载满足条件：

- 同一作用域下
- 函数名称相同
- 函数参数类型不同或者个数不同或者顺序不同

注意：返回值的类型不可以作为函数重载的条件

函数重载的注意事项：

1. 引用作为重载条件

   ```cpp
   void func(int &a);
   
   int a = 10;
   func(a);
   func(10);		// 非法
   
   void func(const int &a);
   func(10);		// 合法，查看常量引用
   ```

2. 重载碰到默认参数【函数重载时尽量不用默认参数，应避免二义性的产生】

   ```cpp
   void func(int a, int b = 10);
   void func(int a);
   
   func(10);		// 出现二义性
   ```

## 内联函数

如果一个函数是内联的，那么在编译时，编译器会把该函数的代码副本放置在每个调用该函数的地方

对内联函数的任何修改，都需要重新编译函数的所有客户端，因为编译器需要更新更换一次所有的代码，否则将会继续使用旧的函数

```cpp
inline int Max(int x, int y){
	return (x > y)? x : y;
}
```

## Lambda 表达式

Lambda表达式实际就是提供一个匿名函数的特性，基本语法：

```cpp
[捕获列表](参数列表)mutable(可选) 异常属性 -> 返回类型 {
	// 函数体
}
```

lambda表达式内部函数体在默认情况下是不能够使用函数体外部的变量的，可通过捕获列表起到传递外部数据的作用；捕获方式有值捕获、引用捕获

**值捕获**

值捕获的前提是变量可以拷贝，注意被捕获的变量是在lambda表达式被创建时拷贝，而非调用时才拷贝

```cpp
void lambda_value_capture() {
    int value = 1;
    auto copy_value = [value] {
        return value;			// 创建时就已经拷贝
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 1, 而 value == 100.
}
```

**引用捕获**

引用捕获保存的是引用，值会发生变化

```cpp
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] {
        return value;
    };
    value = 100;
    auto stored_value = copy_value();
    std::cout << "stored_value = " << stored_value << std::endl;
    // 这时, stored_value == 100, value == 100.
    // 因为 copy_value 保存的是引用
}
```

编译器隐式捕获

- `[ ]`空捕获列表
- `[name1, name2, ...]` 捕获一系列变量
- `[&]` 引用捕获，让编译器自动推导捕获列表
- `[=]` 值捕获

### 泛型Lambda【C++14】

C++14开始，Lambda函数的形式参数可以使用`auto`关键字来产生意义上的泛型

```cpp
auto add = [](auto x, auto y){
	return x + y;
}

add(1, 2);
```

# 数字运算 `<cmath>`内置库

| 函数                            | 描述                                                         |
| ------------------------------- | ------------------------------------------------------------ |
| `double cos(double);`           | 函数返回弧度角（double 型）的余弦                            |
| `double sin(double);`           | 函数返回弧度角（double 型）的正弦                            |
| `double tan(double);`           | 函数返回弧度角（double 型）的正切                            |
| `double log(double);`           | 函数返回参数的自然对数                                       |
| `double pow(double, double);`   | 假设第一个参数为 x，第二个参数为 y，则该函数返回 x 的 y 次方 |
| `double hypot(double, double);` | 函数返回两个参数的平方总和的平方根                           |
| `double sqrt(double);`          | 函数返回参数的平方根                                         |
| `int abs(int);`                 | 函数返回整数的绝对值                                         |
| `double fabs(double);`          | 函数返回任意一个浮点数的绝对值                               |
| `double floor(double);`         | 函数返回一个小于或等于传入参数的最大整数                     |

## 随机数

```cpp
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(){
    int i, j;
    
    // 设置种子
    srand((unsigned)time(NULL));
    
    j = rand();
    
    cout << j << endl;
    return 0;
}
```

# 数组

存放相同数据类型元素的集合，由连续的内存位置组成

```cpp
type arrayName [arraySize];

double balance[5] = {10.0, 2.0, 3.0, 5.3, 21.4};
double balance[] = {10.0, 2.0, 3.0};		// 不显示指定数组大小
```

## 多维数组

```
type name[size1][size2][size3]....[sizeN];
```

### 二维数组

![image-20240716235716830](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240716235716830.png)

```cpp
int a[3][4] = {  
 {0, 1, 2, 3} ,   /*  初始化索引号为 0 的行 */
 {4, 5, 6, 7} ,   /*  初始化索引号为 1 的行 */
 {8, 9, 10, 11}   /*  初始化索引号为 2 的行 */
};

int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};	// 等价
```

## 指向数组的指针

数组名是指向数组中第一个元素的常量指针

**Aarray** 是一个指向 `&Aarray[0]` 的指针，即数组 `Aarray` 的第一个元素的地址

```
double *p;
double Aarray[10];

p = Aarray;
```

## 传递数组给函数

C++ 传数组给一个函数，数组类型自动转换为指针类型，因而传的实际是地址

```cpp
/* 1. 形式参数是一个指针： */
void myFunction(int *param){
	// ...
}

/* 2. 形式参数是一个已定义大小的数组 */
void myFunction(int param[10]){
    // ...
}

/* 3.形式参数是一个未定义大小的数组 */
void myFunction(int param[]){
	// ...
}
```

## 从函数返回数组

C++ 不允许返回一个完整的数组作为函数的参数。但是，您可以通过指定不带索引的数组名来返回一个指向数组的指针

```cpp
int* myFunction(){
   static int myArray[3] = {1, 2, 3};		// 局部变量出了函数域后会销毁
   return myArray;
}
```

使用动态分配【切记不可返回局部变量】

```cpp
int* myFunction(){
   int* myArray = new int[3];
   myArray[0] = 1;
   myArray[1] = 2;
   myArray[2] = 3;
   return myArray;
}

int main(){
   int* result = myFunction();
   // 使用 result
   delete[] result;
   return 0;
}
```

# 指针

指针是一个变量，其值为另一个变量的地址，即内存位置的直接地址；通过解引用`*`方式可找到指针指向的内存

```cpp
type *var-name;
```

指针所占用的内存空间：

- 32位操作系统下：占用 4 字节
- 64位操作系统下：占用 8 字节

## `NULL`空指针/野指针

初始化指针时，若没有确切的地址可以赋值，通常将指针初始化为`NULL`，指向内存编号为0的空间

在大多操作系统上，0~255地址空间为系统占用，程序不允许访问地址为0的内存

```cpp
int *p = NULL;
```

----

传统C++通常将 NULL 和 0 视为同一种东西，这取决于编译器的实现，有的编译器将NULL定义为 ((void *)0)，有些直接定义为0

C++不允许将 void* 隐式转换到其他类型【不同于C语言】

C++11引入 nullptr 关键字来区分空指针和0；nullptr的类型为 nullprt_t，能够隐式的转化为任何指针或成员指针的类型，也能和他们进行相等或者不等的比较

```cpp
int *p = nullptr;
```

----

野指针：指针变量指向非法的内存空间

```cpp
int *p = (int *)0x1100;
cout << *p << endl;		// 没有申请访问这块内存
```

## `const`修饰指针

1. const 修饰指针     常量指针
2. const 修饰常量     指针常量
3. const 即修饰指针又修饰常量

记忆诀窍：`const`靠近哪个哪个不能改变

- 靠近 `*` 就不能解引用
- 靠近 `p` 就地址不能动

### 常量指针

```cpp
const int *p = &a;

*p = 20;	// 错误 指向的值不能更改
p = &b		// 正确 指向可以改
```

- 指针的指向可以修改【地址可以变】
- 指针指向的值不能发生更改【解引用的值不能变】

### 指针常量

````cpp
int * const p = &a;

*p = 20;	// 正确
p = &b		// 错误
````

- 指针的指向不可以修改
- 指针指向的值可以改

### 即修饰指针又修饰常量

```cpp
const int * const p = &a;

*p = 20;	// 错误
p = &b		// 错误
```

- 指针的指向和指针指向的值都不可以改变

## 指针的算术运算

指针算术运算会根据指针的类型和大小来决定移动的距离【与具体的指针类型相关】

- 加法运算：指针p加上一个整数n时，结果是指针p向前移动n个元素的大小
- 减法运算：指针p减去一个整数n时，结果是指针p向后移动n个元素的大小
- 指针与指针之间的减法运算：计算两个指针之间的距离。当从一个指针p减去另一个指针q时，结果是两个指针之间的元素个数
- 指针与整数之间的比较运算：可使用关系运算符（如<、>、<=、>=）对指针和整数进行比较，确保指向内存位置

# 引用

引用是一个别名，是某个已存在变量的另一个名字

- 一旦引用被初始化为一个对象，就不能被指向另一个对象
- 引用必须在创建时被初始化。指针可以在任何时间被初始化

```cpp
int b = 1;
int &a = b;
```

**引用的本质**：在C++内部实现是一个**指针常量**

```cpp
int a = 10;

int &ref = a;		// 相当于 int * const ref = &a;
```

## 引用作为函数的返回值

函数可以放在赋值语句的左边

```cpp
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double& setValues(int i) {  
   double& ref = vals[i];    
   return ref;   // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
}

int main(){
	setValues(1) = 20.23;	// 改变第 2 个元素
	setValues(3) = 70.8;  	// 改变第 4 个元素
}
```

注意：返回一个引用时，被引用的对象不能超出作用域【不可返回局部变量】

## 常量引用

常量引用主要用来修饰形参，防止误操作

在函数形参列表中，加`const`修饰形参，防止形参改变引起实参改变

```cpp
void showValue(const int& v){
	v += 10;		// 常量引用不能修改
	cout << v << endl;
}
```

常量引用的一个特点：

```cpp
int &ref = 10;		// 错误，引用必须需要一个合法的内存空间
const int &ref = 10; // 合理，编译器会进行优化代码
// 等价于
int temp = 10;
const int &ref = temp;
```

# 日期/时间 `<ctime>`

C++ 继承了 C 语言用于日期和时间操作的结构和函数，使用需要包含头文件`<ctime>`

四个与时间相关的结构体：`clock_t`、`time_t`、`size_t` 和 `tm`

```cpp
/* tm 结构体 */
struct tm {
	int tm_sec;   	// 秒，正常范围从 0 到 59，但允许至 61
    int tm_min;   	// 分，范围从 0 到 59
    int tm_hour;  	// 小时，范围从 0 到 23
    int tm_mday;  	// 一月中的第几天，范围从 1 到 31
    int tm_mon;   	// 月，范围从 0 到 11
    int tm_year;  	// 自 1900 年起的年数
    int tm_wday;  	// 一周中的第几天，范围从 0 到 6，从星期日算起
    int tm_yday;  	// 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
    int tm_isdst; 	// 夏令时
};
```

| 函数                                                  | 描述                                                         |
| ----------------------------------------------------- | ------------------------------------------------------------ |
| **`time_t time(time_t *time);`**                      | 返回系统的当前日历时间，自 1970 年 1 月 1 日以来经过的秒数；<br />系统没有时间，则返回 -1 |
| **`char *ctime(const time_t *time);`**                | 返回一个表示当地时间的字符串指针，<br />字符串形式 `day month year hours:minutes:seconds year\n\0` |
| **`struct tm *localtime(const time_t *time);`**       | 返回一个指向表示本地时间的 **tm** 结构的指针                 |
| **`clock_t clock(void);`**                            | 返回程序执行起（一般为程序的开头），处理器时钟所使用的时间<br />如果时间不可用，则返回 -1 |
| **`char * asctime ( const struct tm * time );`**      | 函数返回一个指向字符串的指针，字符串包含了 time 所指向结构中存储的信息，返回形式为：`day month date hours:minutes:seconds year\n\0` |
| **`struct tm *gmtime(const time_t *time);`**          | 函数返回一个指向 time 的指针，time 为 tm 结构，用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示 |
| **`time_t mktime(struct tm *time);`**                 | 函数返回日历时间，相当于 time 所指向结构中存储的时间         |
| **`double difftime ( time_t time2, time_t time1 );`** | 函数返回 time1 和 time2 之间相差的秒数                       |
| **`	size_t strftime();`**                          | 函数可用于格式化日期和时间为指定的格式                       |

```cpp
/*
 * 返回系统的当前日历时间，自 1970 年 1 月 1 日以来经过的秒数
 * 如果 time 参数不为空，返回值也存储在 time 变量中
*/ 
time_t time(time_t *time);		// 原型

time_t seconds;
seconds = time(NULL);
```

```cpp
/* 返回一个表示当地时间的字符串，当地时间是基于参数 timer */
char *ctime(const time_t *timer);	// 原型

time_t curtime;
time(&curtime);
string time = ctime(&curtime);
```

```cpp
/* timer 的值被分解为 tm 结构 */
struct tm *localtime(const time_t *timer);

time_t curtime;
struct tm *tm_time;

time(&curtime);
tm_time = localtime(curtime);
```

```cpp
/* 返回程序执行起（一般为程序的开头），处理器时钟所使用的时间 */
clock_t clock(void);		// 除以 CLOCKS_PER_SEC，为CPU所使用的秒数

clock_t start_t, end_t;
double total_t;

start_t = clock();
// ...
end_t = clock();
total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
```

```cpp
/* 根据tm结构体信息返回一个时间字符串 */
char *asctime(const struct tm *timeptr);

struct tm_t;

t.tm_sec    = 10;  t.tm_min    = 10;  t.tm_hour   = 6;  t.tm_mday   = 25;  
t.tm_mon    = 2;  t.tm_year   = 89;  t.tm_wday   = 6;

asctime(&t);
```

```cpp
/* 使用 timer 的值来填充 tm 结构，并用协调世界时表示 */
struct tm *gmtime(const time_t *timer);		

time_t rawtime;
struct tm *info;

time(&rawtime);
info = gmtime(&rawtime);
```

```cpp
/* 把 timeptr 所指向的结构转换为自 1970 年 1 月 1 日以来持续时间的秒数 */
time_t mktime(struct tm *timeptr)

struct tm info;

info.tm_year = 2021 - 1900;info.tm_mon = 7 - 1;info.tm_mday = 4;
info.tm_hour = 0;info.tm_min = 0;info.tm_sec = 1;info.tm_isdst = -1;

ret = mktime(&info);
```

```cpp
/* 返回 time1 和 time2 之间相差的秒数 */
double difftime(time_t time1, time_t time2);

time_t start_t, end_t;
double diff_t;

time(&start_t);
time(&end_t);

diff_t = difftime(end_t, start_t);
```

```cpp
/* 将tm时间，按格式说明符形式转化为字符串 */
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
str：指向目标数组的指针，用来复制产生的 C 字符串
maxsize：这是被复制到 str 的最大字符数
format：格式说明符
timeptr：时间
```

![image-20240717161310739](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240717161310739.png)

# 基本的输入输出

C++ 的 I/O 发生在流中，流是字节序列

- 输入操作：字节流是从设备（如键盘、磁盘驱动器、网络连接等）流向内存
- 输出操作：字节流是从内存流向设备（如显示屏、打印机、磁盘驱动器、网络连接等）

## I/0 库头文件

- `<iostream>` 该文件定义了 cin、cout、cerr 和 clog 对象，分别对应于标准输入流、标准输出流、非缓冲标准错误流和缓冲标准错误流
- `<iomanip>` 该文件通过所谓的参数化的流操纵器（比如 setw 和 setprecision），来声明对执行标准化 I/O 有用的服务
- `<fstream>`文件为用户控制的文件处理声明服务

## 标准输出流（cout）

`cout` 是 `iostream` 类的一个实例，连接到标准输出设备

```cpp
cout << ... << endl;
```

C++ 编译器根据要输出变量的数据类型，选择合适的流插入运算符来显示值

## 标准输入流（cin）

`cin` 是 `iostream` 类的一个实例，附属到标准输入设备

```cpp
string name;
cin >> name;

cin >> name >> age;		// 流提取运算符 >> 在一个语句中可以多次使用
```

C++ 编译器根据要输入值的数据类型，选择合适的流提取运算符来提取值，并把它存储在给定的变量中

## 标准错误流（cerr）

`cout` 是 `iostream` 类的一个实例，附属到标准输出设备，是非缓冲的！会立即输出

```cpp
cerr << "Error message : " << str << endl;
```

## 标准日志流（clog)

`clog` 是 `iostream` 类的一个实例。附属到标准输出设备，是带缓存的！每个流插入到 clog 都会先存储在缓冲区，直到缓冲填满或者缓冲区刷新时才会输出

```cpp
clog << "Error message : " << str << endl;
```

# 结构体

属于用户自定义的数据类型，允许存储不同的数据类型

```cpp
struct type_name {
member_type1 member_name1;
member_type2 member_name2;
member_type3 member_name3;
} object_names;		// object_names 为变量名，可以不先定义变量名
```

## 创建结构体变量

- C++中在创建结构体变量时，可以省略`struct`，但是C语言不行

```cpp
struct type_name obj;		// 定义变量

struct type_name obj = {memb1, memb2, ...};		// 直接初始化
```

## 结构体数组

```
struct Student stuArr[5] = {
	{"张三", 19, 100},
	{"李四", 29, 99},
	{"王五", 38, 66}
};
```



## 访问结构体成员

```cpp
struct type_name obj;
obj.member_name1;

struct type_name *obj_ptr;			// 指向结构体的指针
obj_ptr->member_name1;
```

## `typedef`关键字定义结构体

`typedef`关键字可为创建的类型取一个“别名”

```cpp
typedef struct Books
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
}Books;

Books Book1, Book2;
```

使用 **typedef** 关键字来定义非结构类型

```cpp
typedef long int *pint32;
 
pint32 x, y, z;		// x, y 和 z 都是指向长整型 long int 的指针
```

# `new`操作符

`new`在堆区开辟数据；`delete`释放对应的内存空间

``` cpp
int *p = new int(10);
delete p;

int *p = new int[10];		// 在堆区开辟一个数组
delete[] p;				// 对应释放需要加 []
```

# 面向对象

## 类和对象

面向对象的三大特征：继承、多态、封装

**封装：**

- 将属性【变量】和行为【函数】作为一个整体
- 将属性和行为加以权限控制

类用于指定对象的形式，是一种用户自定义的数据类型，它是一种封装了数据和函数的组合

- 类中的数据称为成员变量/属性/成员属性
- 类中的函数称为成员函数/行为/成员方法

```cpp
class ClassName{
public:	// 访问权限
	method;		// 行为
	date;		// 属性
};
```

## 访问权限【类访问修饰符】

- `public` 公共权限：成员类内可以访问，类外也可以访问
- `protected` 保护权限：成员类内可以访问，类外不可访问
- `private` 私有权限：成员类内可以访问，类外不可访问

保护和私有在继承中有区别！！！

- 保护权限：儿子可以访问父亲中的保护内容
- 私有权限：儿子不可以访问父亲中私有内容

`struct` 和 `class`区别：

唯一区别就在于访问权限不同

- `struct` 默认为公有权限
- `class` 默认为私有权限

**成员属性私有**

将成员属性都设置成私有后，外部都无法访问

在类中公共部分可以提供对外接口，来 读/写 内部的私有成员属性



## 对象的初始化和清理【构造函数/析构函数】

由编译器自动调用，完成对象的初始化和清理工作，如果我们没有提供构造和析构函数，编译器会自动提供，所提供的构造函数和析构函数都是**空实现**

## 构造函数

主要作用于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用

构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void

构造函数的种类：

- 默认构造函数
- 带参构造函数
- 拷贝构造函数
- 赋值运算符
- 移动构造
- 移动赋值运算符

```cpp
class Person{
public:
	Person();		// 默认构造函数
    Person(int a);	// 带参的构造函数
    Person(const Person& p);	// 拷贝构造函数
};

Person::Person(){
	// ...
}
Person::Person(int a){
    // ...
}
Person::Person(const Person& p){
    // ...
}
```

构造函数的特点：

1. 构造函数，没有返回值，也不用写`void`
2. 函数名称与类名相同
3. 构造函数可以有参数，因此可以发生重载
4. 程序在调用对象时候会自动调用构造，无需手动调用，而且只会调用一次

### 利用构造函数创建对象

```cpp
/* 1. 括号法 */
Person p2(10);	// 有参构造
Person p3(p2);	// 拷贝构造

/* 2. 显示法 */
Person p1;
Person p2 = Person(10);			// 这里出现了匿名对象
Person p3 = Person(p2);			// 匿名对象特点：当前行执行结束后，系统会立即回收掉匿名对象

/* 3. 隐式转换 */
Person p4 = 10;		// 相当于 Person p4 = Person(10);  前提是必须有含一个参数的构造函数
Person p5 = p4;		// 拷贝构造
```

注意：调用默认构造函数时，不要加`()`，`Person p1();`编译器会认为时一个函数的声明，不是在创建对象

### 拷贝构造函数调用的时机

c++ 中拷贝构造调用时机通常有3种：

- 使用一个已经创建完毕的对象来初始化一个新对象
- 值传递的方式给函数参数传值
- 以值方式返回局部对象

```cpp
// 使用一个已经创建完毕的对象来初始化一个新对象
Person p1(10);
Person p2(p1);

// 值传递的方式给函数参数传值
void work(const Person &p){
	// ...
}
Person p1;
work(p1);

// 以值方式返回局部对象
Person back(){
	Person p1;
	return p1;
}
```

### 构造函数调用规则

默认情况下，C++编译器至少给一个类添加3个函数

1. 默认构造函数（无参，函数体为空）
2. 默认析构函数（无参，函数体为空）
3. 默认拷贝构造函数，对属性进行值拷贝

构造函数的调用规则：

1. 如果用户定义有参构造函数，C++不再提供无参构造，但是会提供默认拷贝构造
2. 如果用户定义拷贝构造函数，C++不会再提供其他构造函数

### 初始化列表

代替构造函数的部分功能，提供初始化列表语法，用来**初始化属性**

```cpp
构造函数(): 属性1(值1), 属性2(值2), 属性3(值3)... { }		// 语法
```

重点：**如果属性是引用、`const`之类，则必须用初始化列表的方式进行初始化**

```cpp
class Person{
public:
    Person(int a, int b, int c){			// 传统构造函数做法
        m_A = a;
        m_B = b;
        m_C = c;
    }
    
    int m_A, m_B, m_C;
};

// 初始化列表
class Person{
public:
    Person(int a, int b, int c): m_A(a), m_B(b), m_C(c) {}
    
    int m_A, m_B, m_C;
};
```

## 析构函数

主要作用于对象销毁前系统自动调用，执行一些清理工作

- 析构函数没有返回值，也不写 `void`
- 函数名称与类名相同，在名称前加符号`~`
- 析构函数不可以有参数，因此不可以发生重载
- 程序在对象销毁前会自动调用析构函数，无需手动调用，而且只会调用一次

```cpp
class Person{
public:
	~Person(){		// 析构函数
		// ...
	}
};
```

构造函数中有对属性进行堆空间开辟的，构造函数一定要写对应的`delete`

## 深拷贝和浅拷贝

针对属性有在堆区开辟空间的情况

- 浅拷贝：简单的赋值拷贝操作
- 深拷贝：在堆区重新申请空间，进行拷贝操作

**浅拷贝带来的问题：**堆区的内存重复释放

```cpp
class Person{
public:
    Person(int age, int height){
        m_Age = age;
        m_Height = new int(height);
    }
    ~Person(){
        if(m_Height != NULL){
            delete m_Height;
            m_Height = NULL;
        }
    }
    
    int m_Age;
    int *m_Height;
}

Person p1(18, 160);
Person p2(p1);			// 浅拷贝，会导致同一块内存地址被 delete 两次
```

解决浅拷贝问题的办法就是深拷贝【自己重写拷贝构造函数】

```cpp
Person(const Person p){
	m_Age = p.m_Age;
    // m_Height = p.m_Height;    默认拷贝构造实现的方式，值拷贝
    m_Height = new int(*p.m_Height);
}
```

**要点：**

- 如果在构造函数内在堆区申请了内存空间，在析构函数里一定要释放这一部分空间
- 如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的影响【编译器默认的拷贝构造函数是浅拷贝，值拷贝】

## 类对象作为类成员

类中的成员可以是另一个类的对象，称**对象成员**

```cpp
class A{
};

class B{
public:
	A a;
};
```

重点是创建B类对象时，A与B的构造函数、析构函数的执行顺序：

- 当其他类对象作为本类成员，构造函数的执行顺序是：先构造类对象，再构造自身
- 析构函数的执行顺序与构造相反，先析构自身，再析构类对象

## 静态成员

成员变量或成员函数前加上`static`关键字

### 静态成员变量

- 同一类的所有对象共享同一份数据
- 在编译阶段分配内存【还没跑，全局区】
- 类内声明，类外初始化【必须有一个初始值】

```cpp
class Person{
public:
	static int m_A;
};

int Person::m_A = 100;		// 类外初始化
```

静态成员变量不属于某个对象上，所有对象都共享同一份数据，因此静态成员变量有2种访问方式：

1. 通过对象进行访问

   ```cpp
   Person p;
   p.m_A;
   ```

2. 通过类名进行访问

   ```cpp
   Person::m_A;
   ```

注意：静态成员变量也是有访问权限的，遵循`public`、`protected`、`private`规则

### 静态成员函数

- 所有对象共享同一个函数
- 静态成员函数只能访问静态成员变量，非静态成员不能访问

```cpp
class Person{
public:
	static void func(){
		// ...
	}
};
```

调用静态成员函数方法：

1. 通过对象访问

   ```cpp
   Person p;
   p.func();
   ```

2. 通过类名访问

   ```
   Person::func();
   ```

静态成员函数不可访问非静态成员变量，因为函数是所有对象共有的；同样静态成员函数也遵循访问权限

## C++对象模型

成员变量和成员函数分类存储

- 只有非静态成员变量才是属于类的对象上【静态成员变量、静态成员函数、非静态成员函数不属于类的对象】

```cpp
class Person{
};
```

空对象占用内存空间为 1 字节；C++编译器会给每个空对象也分配一个字节空间，是为了区分空对象占内存的位置

- 每个空对象也应该有一个独一无二的内存地址

```cpp
class Person{
	int m_A;			// 占 4 字节
	static int m_B;		// 静态不占
	void func();		// 成员函数不占对象内存
};
```

上述 `Person` 类只占4字节

每一非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码

这块代码如何区分是哪个对象调用了自己？------> `this`指针

## `this`指针

`this`指针指向当前对象的实例，每一个对象都能通过`this`指针来访问自己的地址

是一个隐藏的指针，可以在类的成员函数中使用

当一个对象的成员函数被调用时，编译器会隐式地传递该对象的地址作为`this`指针

友元函数没有`this`指针，因为友元不是类的成员，**只有成员函数才有`this`指针**

- `this`指针是隐含在每一个非静态成员函数内的一种指针
- `this`指针不需要定义，直接使用即可

```cpp
class MyClass{
public:
	void setValue(int value){	// 属性与形参重名时
		this->value = value;
	}
	
private:
	int value;
};
```

通过使用`this`指针，可以在成员函数中访问当前对象的成员变量，即使它们与函数参数或局部变量同名，可以避免命名冲突

在类的非静态成员函数中返回对象本身，可使用 `return *this`

```cpp
class Person{
public:
	Person& PersonAdd(Person p){
		this->age += p.age;
		return *this
	}
};

p2.PersonAdd(p1).PersonAdd(p1).PersonAdd(p1)		// 链式编程的思想
```

## 空指针访问成员函数

C++中空指针可以调用成员函数，但是注意有没有用到`this`指针

```cpp
class Person{
public:
    void showClassName(){
        cout << "Person" << endl;
    }
    
    void ShowPerson(){
        if(this == NULL)
            return ;
        cout << m_Age << endl;
    }
    int m_Age;
};

Person *p = NULL;
p->showClassName();			// 可以执行
p->showPerson();	// 报错
```

## `const`修饰

### `const`修饰成员属性【成员常量】

`const`修饰成员变量表示成员常量，只能在初始化列表中赋值，可以被`const`和非`const`成员函数调用，但不能修改其值

```cpp
#pragma once
class MyClass{
public:
// 在初始化列表初始化const成员函数
	MyClass():iValue(200){
	// iValue = 300;   error
    }
    
    ~MyClass(void);
private:
	// const 成员变量
	const int iValue;
};
```

注意：一定要以初始化列表的方式进行初始化

### `const`修饰成员函数【常函数】

- 成员函数后加`const`，称这个函数为常函数
- 常函数内不可以修改成员属性
- 成员属性声明时加关键字`mutable`后，在常函数就可以修改

```cpp
class Person{
public:
	void showPerson() const{
		this->m_B = 100;	// 可以修改
		this->m_A = 100;	// 不可修改
	}
    void func(){ }
	
	int m_A;
	mutable int m_B;
}
```

`this`指针的本质是指针常量，指针的指向是不可以改变的；常函数中`this`指针相当于`const Person* const this;`；在成员函数后面加`const`，修饰的是 `this` 指向，让指针指向的值也不可以发生修改

### 常对象

声明对象前加`const`称该对象为常对象

常对象只能调用常函数（不能调用其他成员函数）；同样常对象不可修改成员属性（`mutable`除外）

```cpp
const Person p;
p.m_A = 100;		// 不合法
p.m_B = 100;		// 合法
p.showPerson();		// 合法
p.func();			// 不合法
```

## 友元 `friend`关键字

目的：让一个函数或者类访问另一个类中私有成员

**友元函数不是成员函数！！！！**

" 友元函数 " 的 声明 , 不受类的访问控制限制 , 可以在任何地方定义，如 : 在 private: , protected: , public: , 下声明 友元函数 , 并不影响到 友元函数 的使用

友元函数实现途径：

- 全局函数做友元
- 类做友元
- 成员函数做友元

### 全局函数做友元

```cpp
class Building{
    friend void goodGay(Building &building);	// 声明在类里面
public:
    int m_SettingRoom;
private:
    int m_BedRoom;
};

void goodGay(Building &building){
    cout << building.m_SettingRoom << endl;
    cout << building.m_BedRoom << endl;
}
```

### 类做友元

一个类可以访问另一个类的私有成员

```cpp
class goodGay;		// 前置声明
class Building{
    friend class goodGay;
public:
    Building();
    int m_SettingRoom;
private:
    int m_BedRoom;
};
Building::Building(){
    this->m_SettingRoom = 1;
    this->m_BedRoom = 2;
}

class goodGay{
public:
    goodGay();
    void visit();
private:
    Building *building;
};

goodGay::goodGay(){
    this->building = new Building;
}
void goodGay::visit(){
    cout << building-> m_SettingRoom << endl;
    cout << building-> m_BedRoom << endl;		// 友元作用
}
```

### 成员函数做友元

```cpp
class Building;
class GoodGay{
public:
	void visit();
private:
    Building *building;
};

class Building{
public:
    friend void GoodGay::visit();
    Building();
    int m_SettingRoom;
private:
    int m_BedRoom;
};

void GoodGay::visit(){
    cout << building->m_BedRoom << endl;
}
```

# 重载

C++ 允许在同一作用域中的某个**函数**和**运算符**指定多个定义，分别称为**函数重载**和**运算符重载**

当您调用一个**重载函数**或**重载运算符**时，编译器通过把您所使用的参数类型与定义中的参数类型进行比较，决定选用最合适的定义。选择最合适的重载函数或重载运算符的过程，称为**重载决策**

## 函数重载

在同一个作用域内，可以声明几个功能类似的同名函数，但是这些同名函数的形式参数（指参数的个数、类型或者顺序）必须不同

```cpp
class printData{
public:
      void print(int i) {
        cout << "整数为: " << i << endl;
      }
 
      void print(double  f) {
        cout << "浮点数为: " << f << endl;
      }
 
      void print(char c[]) {
        cout << "字符串为: " << c << endl;
      }
};
 
printData pd;
// 输出整数
pd.print(5);
// 输出浮点数
pd.print(500.263);
// 输出字符串
char c[] = "Hello C++";
pd.print(c);
```

## 运算符重载

对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型

重载的运算符是带有特殊名称的函数，函数名是由关键字`operator`和其后面要重载的运算符符号构成的

**运算符重载函数定义为成员函数**

```cpp
class Person{
public:
	Person operator+(Person &p){
		Person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}
	
	int m_A;
	int m_B;
};

Person p3 = p1.operator+(p2);
// 简化为
Person p3 = p1 +p2;
```

**运算重载函数定义为全局函数**

```cpp
Person operator+(Person &p1, Person &p2){
	Person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}

Person p3 = operator+(p1, p2);
Person p3 = p1 + p2;
```

可重载的运算符列表：

| 运算符         | 含义                                                         |
| -------------- | ------------------------------------------------------------ |
| 双目算术运算符 | + (加)，-(减)，*(乘)，/(除)，% (取模)                        |
| 关系运算符     | ==(等于)，!= (不等于)，< (小于)，> (大于)，<=(小于等于)，>=(大于等于) |
| 逻辑运算符     | \|\|(逻辑或)，&&(逻辑与)，!(逻辑非)                          |
| 单目运算符     | + (正)，-(负)，*(指针)，&(取地址)                            |
| 自增自减运算符 | ++(自增)，--(自减)                                           |
| 位运算符       | \| (按位或)，& (按位与)，~(按位取反)，^(按位异或),，<< (左移)，>>(右移) |
| 赋值运算符     | =, +=, -=, *=, /= , % = , &=, \|=, ^=, <<=, >>=              |
| 空间申请与释放 | new, delete, new[ ] , delete[]                               |
| 其他运算符     | **()**(函数调用)，**->**(成员访问)，**,**(逗号)，**[]**(下标) |

### 左移运算符重载

作用：输出自定义的数据类型

```cpp
class Person{
public:
	void operator<<(ostream &cout){
		cout << this->m_A << endl;
	}
};

// 相当于
Person p;
p.operator<<(cout);
p << cout;			// 不符合一般书写规范
```

一般不会用成员函数来重载`<<`符号

一般用全局函数来重载`<<`，并配合友元函数实现输出自定义类型

```cpp
class Person{
public:
	friend ostream& operator<<(ostream &cout, Person &p);
};

ostream& operator<<(ostream &cout, Person &p){
	cout << p.m_A << p.m_B;
	return cout;		// 可用于链式输出和 << endl;
}
```

### 自增运算符重载

- 前置++运算符
- 后置++运算符

```cpp
class MyInteger{
public:
	MyInteger& operator++(){		// 前置++
		m_Num++;
		return *this;		// 先++，然后返回自身引用
	}
	
	MyInteger operator++(int){
		MyInteger temp = *this;		// 调用拷贝构造，进行了赋值（一个新的对象）
		m_Num++;
		return temp;		// 后置++返回值
	}
};
```

### 赋值运算符`=`重载

C++编译器至少给一个类提供4个函数（自动添加）

1. 默认构造函数（无参，函数体为空）
2. 默认析构函数（无参，函数体为空）
3. 默认拷贝构造函数（对属性进行值拷贝）
4. 赋值运算符`operator=`，对属性进行值拷贝

如果类中有属性指向堆区，做赋值操作时会出现深浅拷贝问题

```cpp
class Person{
public:
	Person(int age){
		m_Age = new int(age);
	}
	~Person(){
		if(m_Age != NULL){
			delete m_Age;
			m_Age = NULL;
		}
	}
	// 重载实现深拷贝
	Person& operator=(Person& p){
		if(m_Age != NULL){
			delete m_Age;
			m_Age = NULL;
		}
		m_Age = new int(*p.m_Age);
		return *this;
	}
	// 系统默认提供 浅拷贝
	void operator=(Person &p){
		m_Age = p.m_Age;
	}
private:
	int m_Age;
};
```

### 关系运算符重载

重载关系运算符，可以让2个自定义类型对象进行对比

```cpp
class Person{
public:
	Person(string name, int age){
		this->m_Name = name;
        this->m_Age = age;
	}
	bool operator==(Person &p){
		if(this->m_Name == p.m_Name && this->m_Age == p.m_Age)
			return true;
		else
			return false;
	}
private:
    string m_Name;
    int age;
};

Person p1("Tom", 18);
Person p2("Tom", 18);
p1 == p2;
```

### 函数调用运算符重载【仿函数】

函数调用运算符`()`也可以重载

重载后使用的方式非常像函数的调用，因此称为仿函数

仿函数没有固定的写法，非常领过

```cpp
class MyPrint{
public:
	void operator()(string text){
		cout << text << endl;
	}
};
MyPrint myprint;
myprint("Hello World!/n");
```

# 继承

继承允许我们依据另一个类来定义一个类；当创建一个类时，您不需要重新编写新的数据成员和成员函数，只需指定新建的类继承了一个已有的类的成员即可。这个已有的类称为**基类**，新建的类称为**派生类**。

```cpp
// 基类
class Animal {
    // eat() 函数
    // sleep() 函数
};

//派生类
class Dog : public Animal {
    // bark() 函数
};
```

继承方式：公有继承`public`、保护继承`protected`、私有继承`private`

派生类可以访问基类中所有的非私有成员。因此基类成员如果不想被派生类的成员函数访问，则应在基类中声明为 `private`

我们几乎不使用 **`protected`** 或 **`private`** 继承，通常使用 **`public`** 继承，继承规则如下：

- **公有继承（public）**：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问
- **保护继承（protected）**： 当一个类派生自保护基类时，基类的**公有**和**保护成员**将成为派生类的**保护**成员
- **私有继承（private）：**当一个类派生自私有基类时，基类的**公有**和**保护**成员将成为派生类的**私有**成员。

| 继承方式  | 基类的public成员  | 基类的protected成员 | 基类的private成员 | 继承引起的访问控制关系变化概括         |
| --------- | ----------------- | ------------------- | ----------------- | -------------------------------------- |
| public    | 仍为public成员    | 仍为protected成员   | 不可见            | 基类的非私有成员在子类的访问属性不变   |
| protected | 变为protected成员 | 变为protected成员   | 不可见            | 基类的非私有成员都为子类的保护成员     |
| private   | 变为private成员   | 变为private成员     | 不可见            | 基类中的非私有成员都称为子类的私有成员 |

## 继承中的对象模型【子类继承了父类哪些成员】

一个派生类继承了所有的基类方法，但以下除外：

- 基类的构造函数、析构函数和拷贝构造函数
- 基类的重载运算符
- 基类的友元函数

父类中所有非静态成员属性都会被子类继承下去

父类中的私有属性是被编译器隐藏了，因此访问不到，但确实被继承下去了

```cpp
class Base{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son:public Base{
public:
	int m_D;
};

cout << sizeof(Son) << endl; 		// 16
```

## 继承中的构造函数和析构函数顺序

子类继承分类后，当创建子类对象，也会调用父类的构造函数

```cpp
class Base{
public:
	Base(){
		cout << "..." << endl;
	}
	~Base(){
		cout << "..." << endl;
	}
};
class Son:public Base{
public:
	Son(){
		cout << "..." << endl;
	}
	~Son(){
		cout << "..." << endl;
	}
};
```

继承中的构造和析构的顺序如下：

- 构造：先构造父类，再构造子类
- 析构：先析构子类，再析构父类【执行顺序与构造相反】

## 继承同名成员处理方式

继承中出现同名成员，子类会隐藏父类的同名成员，若需要访问需要加作用域

- 访问子类同名成员，直接访问即可
- 访问父类同名成员，需要加作用域

```cpp
class Base{
public:
	Base(){
		m_A = 100;
	}
	int m_A;
};

class Son:public Base{
public:
	Son(){
		m_A = 200;
	}
	int m_A;
};

Son s;
cout << s.m_A << endl;			// 访问子类成员
cout << s.Base::m_A << endl;	// 访问父类成员
```

总结：

1. 子类对象可以直接访问到子类中同名成员
2. 子类对象加作用域可以访问到父类同名成员
3. 当子类和父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数

## 继承中同名静态成员处理方式

静态成员出现同名处理方式和非静态成员出现同名一致

- 访问子类同名成员，直接访问即可
- 访问父类同名成员，需加作用域

```cpp
/* 1. 通过对象访问（同非静态成员） */
Son s;
cout << s.m_A << endl;
cout << s.Base::m_A << endl;

/* 2. 通过类名访问 */
cout << Som::m_A << endl;
cout << Base::m_A << endl;
// 第一个::代表通过类名方式访问，第二个::代表访问父类作用域下
cout << Son::Base::m_A << endl;
```

1. 子类出现同父类同名静态成员函数，也会隐藏父类中所有同名成员函数
2. 如果想访问父类中被隐藏同名成员，需加作用域

## 多继承语法

```cpp
class 子类:public 父类1, protected 父类2{
	// ...
};
```

多继承可能会引起父类中有同名成员出现，需加作用域区分

**C++实际开发过程中不建议用多继承**

```cpp
class Base1{
	int m_A;
};
class Base2{
	int m_A;
};
class Son:public Base1, public Base2{
	// ....    Son 中有两份继承下来的 m_A
};
Son s;
s.m_A;	// 引发二义性，需加作用域
s.Base1::m_A;
```

## 菱形继承

2个派生类同时继承同一个基类，又有某个类同时继承这2个派生类，这种继承被称为**菱形继承**

![image-20240719212709689](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240719212709689.png)

当菱形继承2个父类拥有相同的数据，需要加作用域来区分

实际中，我们只需要一份数据就可以了，菱形继承导致数据有2份，浪费资源

利用虚继承解决菱形继承问题：

- 继承之前加上关键字`virtual`变虚继承

```cpp
class Animal{
public:
	int m_Age;
};

class Sheep:virtual public Animal{
};

class Tuo: virtual public Animal{
};

class SheepTuo: public Sheep, public Tuo{
};

SheepTuo st;
cout << st.Sheep::m_Age << endl;
cout << st.Tuo::m_Age << endl;		// 与上面是同一个 m_Age
```

总结：

- 菱形继承带来的问题是子类继承两份相同的数据，导致资源浪费以及毫无意义
- 虚继承可以解决菱形继承问题

**底层实现：**

依靠虚基类指针`vbptr`指向虚基类表`vbtable`，表中依靠偏移量来找到真正的数据

# 多态

多态分为两类：

- 静态多态：函数重载和运算符重载属于静态多态【复用函数名】
- 动态多态：派生类和虚函数实现运行时多态

静态多态和动态多态的区别：

- 静态多态的函数地址早绑定：编译阶段确定
- 动态多态的函数地址晚绑定：运行阶段确定

```cpp
class Animal{
public:
	virtual void speak(){
		cout << "I am Animal" << endl;
	} 
};

class Cat:public Animal{
public:
	void speak(){
		cout << "I am Cat" << endl; 
	}
};

void doSpeak(Animal &animal){
	animal.speak();
}

Cat cat;
doSpeak(cat);		// 输出 “I am Cat” 多态
```

动态多态实现条件：

1. 有继承关系

2. 子类重写父类的虚函数

   重写时 函数返回值类型、函数名、参数列表 完全相同；重写时 `virtual`可写可不写

3. 父类的指针或者引用指向子类时，才能启用

动态多态的使用：

- 父类的指针或引用执行子类对象

**底层实现原理：**【重点！！！！】

```cpp
sizeof(Animal) = 1;				// 无虚函数的版本
sizeof(virtual Animal) = 4;		// 有虚函数的版本
```

`Animal`（内部含虚函数版本）类内结构：内部有一个**虚函数指针`vfptr`**，虚函数指针指向**虚函数表`vftable`**，虚函数表中记录虚函数的入口地址，**当子类重写父类的虚函数时，子类中的虚函数表内部会替换成子类的虚函数地址，当父类的指针或者引用指向子类对象时就会发生多态**

```cpp
/* 多态实现 2 个数计算器功能 */
class AbstractCalculator{
public:
	virtual int getResult(){
		return 0;
	}
	int m_Num1;
	int m_Num2;
};

class AddCalculator: public AbstractCalculator{
	int getResult(){
		return m_Num1 + m_Num2;
	}
};

class SubCalculator: public AbstractCalculator{
	int getResult(){
		return m_Num1 - m_Num2;
	}
};

AbstractCalculator *abc = new AddCalculator;
abc->m_Num1 = 10;
abc->m_Num2 = 10;
abc->getResult();
```

多态的好处：

1. 组织结构清晰
2. 代码可复性强
3. 后期/前期拓展和维护性高

## 纯虚函数和抽象类

**在多态中，通常父类中函数的实现是毫无意义的【只提供接口规范】，主要都是调用子类重写内容来实现功能**

因此，可以将父类中的虚函数改为**纯虚函数**

```cpp
virtual 返回值类型 函数名(参数列表) = 0;
```

当类中有了纯虚函数，这个类被称为**抽象类**

抽象类的特点：

- 无法实例化对象
- 子类必须重写抽象类中的纯虚函数，否则也属于抽象类

## 虚析构和纯虚析构

多态使用时，**如果子类中有属性开辟到堆区**，那么父类指针在释放时无法调用到子类的析构函数，释放堆区

解决方法：将父类中的析构函数改为**虚析构**或者**纯虚析构**

如果是纯虚析构，该类属于抽象类，无法实例化对象

注意：**纯虚析构函数必须要实现定义**，如果纯虚析构函数没有实现定义，‌链接器在链接阶段会检测到这个问题，‌导致程序无法成功编译和运行

```cpp
class Animal{
public:
	Animal(){
		cout << "..." << endl;
	}
	// virtual ~Animal() = 0;		// 纯虚析构
	virtual ~Animal(){
		cout << "..." << endl;
	}
};
// Animal::~Animal(){		// 纯虚析构也必须实现其定义，具体实现（父类是否有在堆区开辟空间）
// }

class Cat: public Animal{
public:
	Cat(String name){
		m_Name = new string(name);			// 子类在堆区开辟了空间
	}
	~Cat(){
		delete m_Name;
	}
	string* m_Name;
};

Animal *animal = new Cat("Tom");
delete animal;
```

总结；

- 虚析构或纯虚析构就是用来解决通过父类指针释放子类对象
- 如果子类中没有堆区数据，可以不写虚析构和纯虚析构，**纯虚函数也必须写定义**
- 拥有纯虚析构函数的类也属于抽象类

```cpp
clasas Cpu{		// 基类提供抽象接口
public:
	virtual void calculate() = 0;
};

class VideoCard{
public:
	virtual void display() = 0;
};

class Memory{
public:
	virtual void storage() = 0;
};

class IntelCpu: public Cpu{
public:
	void calculate(){
		cout << "..." << endl;		// 具体实现
	}
};

class HuaWeiVideoCard: public VideoCard{
public:
	void display(){
		cout << "..." << endl;
	}
};

class SangsumMemory: public Memory{
public:
	void storage(){
		cout << "..." << endl;
	}
};

class Computer{
public:
	Computer(Cpu *cpu, VideoCard *vc, Memory *mem){
		m_Cpu = cpu;
		m_Vc = vc;
		m_Mem = mem;
	}
	void work(){
		m_Cpu->calculate();
		m_Vc->display();
		m_Mem->storage();
	}
	~Computer(){
		if(m_Cpu != NULL){
			delete m_Cpu;
			m_Cpu = NULL;
		}
		if(m_Vc != NULL){
			delete m_Vc;
			m_Vc = NULL;
		}
		if(m_Mem != NULL){
			delete m_Mem;
			m_Mem = NULL;
		}
	}
	
private:
	Cpu *m_Cpu;
	VideoCard *m_Vc;
	Memory *m_Mem;
}
```

# 文件和流

程序运行时产生的数据都属于临时数据，程序一旦运行结束都会被释放

通过文件可以将数据持久化

C++对文件操作需要包含头文件`<fstream>`

文件类型分成两种：

- 文本文件：文件以文字的 ASCII 码形式存储在计算机中
- 二进制文件：文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂它们

操作文件的三大类：【必须包含头文件`<iostream>`和`fstream`】

| 数据类型 | 描述                                                         |
| -------- | ------------------------------------------------------------ |
| ofstream | 该数据类型表示输出文件流，用于创建文件并向文件写入信息       |
| ifstream | 该数据类型表示输入文件流，用于从文件读取信息                 |
| fstream  | 该数据类型通常表示文件流，且同时具有 `ofstream` 和 `ifstream` 两种功能，这意味着它可以创建文件，向文件写入信息，从文件读取信息。 |

## 打开文件

在从文件读取信息或者向文件写入信息之前，必须先打开文件

- `ofstream` 和 `fstream` 对象都可以用来打开文件进行**写操作**
- 只需要打开文件进行**读操作**，则使用 `ifstream` 对象

```cpp
// open() 函数是 fstream、ifstream 和 ofstream 对象的一个成员
void open(const char *filename, ios::openmode mode);
```

`filename`：指定要打开的文件的名称和位置

`mode` ：定义文件被打开的模式

| 模式标志    | 描述                                                         |
| ----------- | ------------------------------------------------------------ |
| ios::app    | 追加模式。所有写入都追加到文件末尾                           |
| ios::ate    | 文件打开后定位到文件末尾                                     |
| ios::in     | 打开文件用于读取                                             |
| ios::out    | 打开文件用于写入                                             |
| ios::trunc  | 如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为 0 |
| ios::binary | 二进制方式                                                   |

注：文件打开方式可以配合使用，利用`|`操作符，二进制写文件`ios::binary | ios::out`

```cpp
ofstream outfile;
outfile.open("file.dat", ios::out | ios::trunc);
```

## 关闭文件

当 C++ 程序终止时，它会自动关闭刷新所有流，释放所有分配的内存，并关闭所有打开的文件，但应养成良好习惯，在程序终止前手动关闭

```cpp
// close() 函数是 fstream、ifstream 和 ofstream 对象的一个成员
void close();
```

## 写入文件

使用流插入运算符 `<< ` 向文件写入信息，使用的是 `ofstream` 或 `fstream` 对象

## 读取文件

使用流提取运算符 `>> ` 从文件读取信息，使用的是 `ifstream` 或 `fstream` 对象

```cpp
#include <fstream>
#include <iostream>
using namespace std;
 
int main ()
{
	char data[100];
 
 	// 以写模式打开文件
 	ofstream outfile;
 	outfile.open("afile.dat");
 	cin.getline(data, 100);
 	
 	// 向文件写入用户输入的
 	outfile << data << endl;
 	
 	// 关闭打开的文件
 	outfile.close();
 	
 	// 以读模式打开文件
 	ifstream infile; 
 	infile.open("afile.dat"); 
 	
 	infile >> data; 
 
 	// 在屏幕上写入数据
 	cout << data << endl;
   
   // 再次从文件读取数据，并显示它
   infile >> data; 
   cout << data << endl; 
 
   // 关闭打开的文件
   infile.close();
 
   return 0;
}
```

常用读文件的方式

```cpp
/* 1. */
char buf[1024] = {0};
while( ifs >> buf){
	cout << buf << endl;
}

/* 2. */
char buf[1024] = {0};
while(ifs.getline(buf, sizeof(buf))){
	cout << buf << endl;
}

/* 3. */
string buf;
while(getline(ifs, buf)){
	cout << buf << endl;
}

/* 4. 一个字符一个字符的读（不推荐） */
char c;
while((c = ifs.get()) ! EOF){
	cout << c << endl;
}
```

## 二进制文件

以二进制方式对文件进行读写操作

### 写文件

二进制方式写文件主要利用流对象调用成员函数`write`

```cpp
ofstream& write(const char *buffer, int len);
```

`buffer`：指向内存中一段存储空间

`len`：读写的字节数

```cpp
ofstream ofs("person.txt", ios::out | ios::binary);

Person p("张三", 18);
ofs.write((const char*)&p, sizeof(Person));

ofs.close();
```

### 读文件

二进制方式读文件主要利用流对象调用成员函数`read`

```cpp
istream& read(char *buffer, int len);
```

`buffer`：指向内存中一段存储空间

`len`：读写字节数

```cpp
ifstream ifs;
ifs.open("person.txt", ios::in | ios::binary);
if(!ifs.is_open()){
	cout << "打开失败/n" << endl;
}
ifs.read((char*)&p, sizeof(Person));
cout << p.m_Name << p.m_Age << endl;
ifs.close();
```

## 文件位置指针

`istream` 和 `ostream` 都提供了用于重新定位文件位置指针的成员函数

- `istream` 的 **`seekg`**
- `ostream` 的 **`seekp`**

`seekg` 和 `seekp` 的参数通常是一个长整型。第二个参数可以用于指定查找方向

| 查找方向     | 描述                       |
| ------------ | -------------------------- |
| **ios::beg** | 默认的，从流的开头开始定位 |
| **ios::cur** | 从流的当前位置开始定位     |
| **ios::end** | 从流的末尾开始定位         |

```cpp
// 定位到 fileObject 的第 n 个字节（假设是 ios::beg）
fileObject.seekg( n );
 
// 把文件的读指针从 fileObject 当前位置向后移 n 个字节
fileObject.seekg( n, ios::cur );
 
// 把文件的读指针从 fileObject 末尾往回移 n 个字节
fileObject.seekg( n, ios::end );
 
// 定位到 fileObject 的末尾
fileObject.seekg( 0, ios::end );
```

# 异常处理

异常是程序在执行期间产生的问题，C++ 异常是指在程序运行时发生的特殊情况，比如尝试除以零的操作

异常提供了一种转移程序控制权的方式。C++ 异常处理涉及到三个关键字：**try、catch、throw**

- **`throw`**： 当问题出现时，程序会抛出一个异常。这是通过使用 throw 关键字来完成的
- **`catch`**： 在您想要处理问题的地方，通过异常处理程序捕获异常。catch 关键字用于捕获异常
- **`try`**：try 块中的代码标识将被激活的特定异常。它后面通常跟着一个或多个 catch 块

**`try` 块中放置可能抛出异常的代码**，try 块中的代码被称为**保护代码**

```cpp
try{
   // 保护代码
}catch( ExceptionName e1 ){
   // catch 块
}catch( ExceptionName e2 ){
   // catch 块
}catch( ExceptionName eN ){
   // catch 块
}
```

## 抛出异常

您可以使用 `throw` 语句在代码块中的任何地方抛出异常。throw 语句的操作数可以是任意的表达式，表达式的结果的类型决定了抛出的异常的类型

## 捕获异常

**`catch`** 块跟在 **`try`** 块后面，用于捕获异常。您可以指定想要捕捉的异常类型

如果您想让 catch 块能够处理 try 块抛出的任何类型的异常，则必须在异常声明的括号内使用省略号 `...`

```cpp
try{
   // 保护代码
}catch(...){
  // 能处理任何异常的代码
}
```

---

```cpp
/* demo */
double division(int a, int b){
	if( b == 0 ){
		throw "Division by zero condition!";
	}
	return (a/b);
}
 
int main (){
	int x = 50;
	int y = 0;
	double z = 0;
	
	try {
		z = division(x, y);
		cout << z << endl;
	}catch (const char* msg) {
		cerr << msg << endl;
	}
	
	return 0;
}
```

## C++ 标准的异常

C++ 提供了一系列标准的异常，定义在 **`<exception>`** 中，我们可以在程序中使用这些标准的异常

![image-20240720110516827](https://raw.githubusercontent.com/LQF376/image/main/img/image-20240720110516827.png)

| 异常                   | 描述                                                         |
| ---------------------- | ------------------------------------------------------------ |
| **std::exception**     | 该异常是所有标准 C++ 异常的父类。                            |
| std::bad_alloc         | 该异常可以通过 **new** 抛出。                                |
| std::bad_cast          | 该异常可以通过 **dynamic_cast** 抛出。                       |
| std::bad_typeid        | 该异常可以通过 **typeid** 抛出。                             |
| std::bad_exception     | 这在处理 C++ 程序中无法预期的异常时非常有用。                |
| **std::logic_error**   | 理论上可以通过读取代码来检测到的异常。                       |
| std::domain_error      | 当使用了一个无效的数学域时，会抛出该异常。                   |
| std::invalid_argument  | 当使用了无效的参数时，会抛出该异常。                         |
| std::length_error      | 当创建了太长的 std::string 时，会抛出该异常。                |
| std::out_of_range      | 该异常可以通过方法抛出，例如 `std::vector` 和 `std::bitset<>::operator[]()`。 |
| **std::runtime_error** | 理论上不可以通过读取代码来检测到的异常。                     |
| std::overflow_error    | 当发生数学上溢时，会抛出该异常。                             |
| std::range_error       | 当尝试存储超出范围的值时，会抛出该异常。                     |
| std::underflow_error   | 当发生数学下溢时，会抛出该异常。                             |

## 自定义异常

通过继承和重载 exception 类来定义新的异常

```cpp
#include <iostream>
#include <exception>
 
class MyException : public exception{
	const char * what () const throw (){
		return "C++ Exception";
	}
};
 
int main(){
	try{
		throw MyException();
	}
	catch(MyException& e){
		std::cout << "MyException caught" << std::endl;
		std::cout << e.what() << std::endl;
	}
	catch(std::exception& e){
   		//其他的错误
    }
}
```

# 动态内存

C++ 程序中的内存分为两个部分：

- **栈：**在函数内部声明的所有变量都将占用栈内存
- **堆：**这是程序中未使用的内存，在程序运行时可用于动态分配内存

`new`：为给定类型的变量在运行时分配堆内的内存，这会返回所分配的空间地址

`delete`：不再需要动态分配的内存空间，删除之前由 new 运算符分配的内存

## `new`运算符

new 运算符来为任意的数据类型动态分配内存的通用语法

```
new data-type;
```

如果自由存储区已被用完，可能无法成功分配内存。所以建议检查 new 运算符是否返回 NULL 指针

```cpp
double *pvalue = NULL;
if(!(pvalue = new double)){
	cout << "Error: out of memory." << endl;
	exit(1);
}
```

**`malloc()`** 函数在 C 语言中就出现了，在 C++ 中仍然存在，但建议尽量不要使用 `malloc()` 函数，因为`new`不只是分配了内存，还创建了对象【会主动调用对象的构造函数】

## `delete`运算符

某个已经动态分配内存的变量不再需要使用时，您可以使用 delete 操作符释放它所占用的内存

```cpp
delete pvalue;        // 释放 pvalue 所指向的内存
```

## 数组的动态内存分配

```cpp
// 动态分配,数组长度为 m
int *array=new int [m];
 
//释放内存
delete [] array;
```

二维数组

```cpp
int **array;
// 假定数组第一维长度为 m， 第二维长度为 n
// 动态分配空间
array = new int *[m];
for( int i=0; i<m; i++ ){
    array[i] = new int [n];
}

//释放
for( int i=0; i<m; i++ ){
    delete [] array[i];
}
delete [] array;
```

## 对象的动态内存分配

```cpp
#include <iostream>
using namespace std;
 
class Box{
public:
    Box(){ 
        cout << "调用构造函数！" <<endl; 
    }
    ~Box(){ 
        cout << "调用析构函数！" <<endl; 
    }
};
 
int main( ){
    Box* myBoxArray = new Box[4];
    
    delete [] myBoxArray; // 删除数组
    return 0;
}
```

# 命名空间

命名空间即定义了上下文，可作为附加信息来区分不同库中相同名称的函数、类、变量等。本质上，就是定义了一个范围。

## 定义命名空间

```cpp
namespace namespace_name {
    // 代码声明
}
```

调用带有命名空间的函数或变量，需要在前面加上命名空间的名称

```cpp
name::code;  // code 可以是变量或函数
```

```cpp
#include <iostream>
using namespace std;
 
// 第一个命名空间
namespace first_space{
    void func(){
        cout << "Inside first_space" << endl;
    }
}
// 第二个命名空间
namespace second_space{
    void func(){
        cout << "Inside second_space" << endl;
    }
}
int main (){
    // 调用第一个命名空间中的函数
    first_space::func();
   
    // 调用第二个命名空间中的函数
    second_space::func(); 
 
    return 0;
}
```

## `using`指令

使用 **`using namespace`** 指令，这样在使用命名空间时就可以不用在前面加上命名空间的名称，编译器会将后续的代码将使用指定的命名空间中的名称

```cpp
#include <iostream>
using namespace std;
 
// 第一个命名空间
namespace first_space{
    void func(){
        cout << "Inside first_space" << endl;
    }
}
// 第二个命名空间
namespace second_space{
    void func(){
        cout << "Inside second_space" << endl;
    }
}
using namespace first_space;
int main (){
    // 调用第一个命名空间中的函数
    func();

    return 0;
}
```

**using** 指令也可以用来指定命名空间中的特定项目

**using** 指令引入的名称遵循正常的范围规则。名称从使用 **using** 指令开始是可见的，直到该范围结束。此时，在范围以外定义的同名实体是隐藏的

```cpp
sing std::cout;		// 随后在使用 cout 时就可以不用加上命名空间名称作为前缀，但其他标准库需要
```

## 不连续的命名空间

一个命名空间的各个组成部分可以分散在多个文件中

如果命名空间中的某个组成部分需要请求定义在另一个文件中的名称，则仍然需要声明该名称

## 嵌套的命名空间

命名空间可以嵌套，您可以在一个命名空间中定义另一个命名空间

```cpp
namespace namespace_name1 {
	// 代码声明
    namespace namespace_name2 {
        // 代码声明
    }
}
```

通过使用 **::** 运算符来访问嵌套的命名空间中的成员

```cpp
// 访问 namespace_name2 中的成员
using namespace namespace_name1::namespace_name2;
 
// 访问 namespace_name1 中的成员
using namespace namespace_name1;
```

#  模板

模板是泛型编程的基础，泛型编程即以一种独立于任何特定类型的方式编写代码

模板即通用的模具，大大提高代码的复用性

特点：

- 模板不可以直接使用，他只是一个框架
- 模板的通用并不是万能的

C++提供两种模板机制：**函数模板**和**类模板**

## 函数模板

建立一个通用函数，其函数返回值类型和形参类型可以不具体指定，用一个虚拟的类型来代表

语法：

```cpp
template<typename type>
ret-type func-name(parameter list){
	// ...
}
```

`template`：声明创建模板

`typename`：表示其后面的符号是一种数据类型，可以用 `class` 代替

`type`：通用的数据类型，通常为大写字母

```cpp
template<typename T>
void mySwap(T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}
// 使用模板：2种方式使用函数模板
int a = 1;
int b = 2;
mySwap(a, b);			// 1.自动类型推导
mySwap<int>(a, b);		// 2. 显式指定类型(建议)
```

函数模板注意事项：

- 自动类型推导，必须推导出一致的数据类型`T`才可使用
- 模板必须要确定`T`的数据类型，才可使用

```cpp
template<typename T>
void mySwap(T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}
int a = 10;
char b = 'c';
mySwap(a, b);	// 类型不一致，无法推出 T
```

### 普通函数与模板函数

**普通函数与函数模板的区别：**

- 普通函数调用时可以发生自动类型转换（隐式类型转换）
- 函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换
- 如果利用显式指定类型的方式，可以发生隐式类型转换

```cpp
template<typename T>
T myAdd(T& a, T& b){
	return a + b;
}

int a = 10;  char c = 'a';
myAdd<int>(a, c);		// 可以实现
```

普通函数和函数模板的调用规则：

- 如果函数模板和普通模板都可以实现，优先调用普通函数
- 可以通过空模板参数列表来强制调用函数模板
- 函数模板也可以发生重载
- 如果函数模板可以产生更好的匹配，优先调用函数模板

```cpp
void myPrint(int a, int b);

template<class T>
void myPrint(T &a, T &b);

myPrint<>(a, b);	// 空模板参数列表，强制调用函数模板
```

### 函数模板的局限性

在传入参数为数组或者类对象时会出现问题

```cpp
template<typename T>
bool myCompare(Person &p1, Person &p2){
	// ...
}

class Person{
public:
	Person(string name, int age){
		this->m_Name = name;
		this->m_Age = age;
	}
	string m_Name;
	int m_Age;
};

// 1. 使用具体化Person的版本实现代码，具体化优先调用
template<> bool myCompare(Person &p1, Person &p2){
	if(p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age)
		return ture;
	else
		return false;
}

// 2. 重载运算符的方法也可以实现2个类对象的判等
```

## 类模板

建立一个通用类，类中的成员数据类型可以不具体指定，用一个虚拟的类型来代表

```cpp
template<class T>
class Stack{
public:
	void push(T const&);	// 入栈
	void pop();		// 出栈
	T top() const;	// 返回栈顶元素
	bool empty() const{
		return elems.empty();
	}
private:
	vector<T> elems;	// 元素
};

template<class T>
void Stack::push(T const& elem){
	elems.push_back(elem);
}

template<class T>
void pop(){
	if(elems.empty())
		throw out_of_range("Stack<>::pop(): empty stack");
	elems.pop_back();
}

template<class T>
T Stack::top() const{
	if(elems.empty())
		throw out_of_range("Stack<>::top(): empty stack");
	return elems.back();
}

Stack<int> intStack;	// 创建对象
```

类模板和函数模板的区别：

- 类模板没有自动类型推导的使用方式
- 类模板在模板参数列表中可以默认参数

```cpp
template<class NameType, class AgeType = int>
class Person{};

Person p("Tom", 16);	// 报错，没有自动类型推导
Person<string> p("Jack", 22);	// 默认参数
```

### 类模板中成员函数的创建时机

类模板中成员函数和普通类中成员函数创建时机是有区别的：

- 普通类中的成员函数一开始就可以创建
- 类模板中的成员函数在调用时才创建

### 类模板对象做函数参数

类模板实例化出的对象，向函数传参的方式（3种）：

1. 指定传入的类型 --- 直接显式对象的数据类型
2. 参数模板化 --- 将对象中的参数变成模板进行传递
3. 整个类模板化 --- 将这个对象类型模板化进行传递

```cpp
// 1. 指定传入的类型【使用广泛】
void printPerson(Person<string, int> &p){
	// ...	
}

// 2. 参数模板化
template<typename T1, typename T2>
void printPerson2(Person<T1, T2> &p){
	// ...
}

// 3. 整个类模板化
template<typename T>
void printPerson(T &p){
	// ...
}
```

### 类模板与继承

当类模板遇到继承时，要注意：

- 当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中`T`的类型【模板实例化】
- 如果不指定，编译器无法给子类分配内存
- 如果想灵活指定出父类中`T`的类型，子类也需要变成类模板

```cpp
// 1. 指出父类模板中的参数类型
template<class T>
class Base{
public:
	T t;
};
class Son: public Base<int>{ };

// 2. 子类也做类模板处理
template<class T1, class T2>
class Son2: public Base<T2>{
public:
	T1 obj;
};

Son2<int, char> s2;
```

### 类模板成员函数类外实现

类模板中成员函数类外实现时，需要加上模板参数列表

```cpp
template<class T1, class T2>
class Person{
public:
	Person(T1 name, T2 age);
	void showPerson();
	T1 m_Name;
	T2 m_Age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age){
	this->m_Name = name;
	this->m_Age = name;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson(){
	cout << "..." << endl;
}
```

### 类模板份文件编写

类模板中的成员函数创建时机是调用阶段，导致分文件编写时链接不到

解决方法：

1. 直接包含`.cpp`源文件`#include<.cpp>`
2. 将声明和实现写到同一个文件中，并更改后缀名为`.hpp`，`.hpp`是约定的名称，不是强制

### 类模板和友元

类模板配合友元函数的类内类外实现

- 全局函数类内实现【直接在类内声明友元即可】
- 全局函数类外实现【需要提前让编译器知道全局函数存在】

```cpp
template<class T1, class T2>
class Person{
	// 1，友元直接在类内实现
	friend void prientPerson(Person<T1, T2> p){
		cout << p.m_Name << p.m_Age << endl;
	}
	// 2. 友元在类内声明，类外实现
	friend void printPerson(Person<T1, T2> p);
public:
	Person(){}
private:
	T1 m_Name;
	T2 m_Age;
};

// 2. 类外实现，相当于模板函数
template<class T1, class T2>
void printPerson(Person<T1, T2> p){
    cout << p.m_Name << p.m_Age << endl;
}
```

# 预处理器

## `#define`预处理

\#define 预处理指令用于创建符号常量，称为**宏**

```cpp
#define macro-name replacement-text 
```

在该文件中后续出现的所有宏都将会在程序编译之前被替换为 replacement-text，需要注意替换后结合性的问题

## 参数宏

```cpp
#define MIN(a, b) (a>b ? a : b)

int i = 10;
int j = 100;
cout << MIN(i, j) << endl;
```

## 条件编译

根据条件选择性地对部分程序源码进行编译

```cpp
// 只在调试时进行编译
#ifdef DEBUG
	cerr <<"Variable x = " << x << endl;
#endif
```

## `#`和`##`运算符

`#`运算符会把 replacement-text 令牌转换为引号引起来的字符串

```cpp
#define MKSTR( x ) #x

cout << MKSTR(HELLO C++) << endl;		// 输出 HELLO C++
```

`##`运算符用于连接两个令牌

```cpp
#define concat(a, b) a ## b

int xy = 100;
   
cout << concat(x, y);		// 相当于 xy
```

## C++ 中的预定义宏

| 宏         | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| `__LINE__` | 这会在程序编译时包含当前行号                                 |
| `__FILE__` | 这会在程序编译时包含当前文件名                               |
| `__DATE__` | 这会包含一个形式为 month/day/year 的字符串，它表示把源文件转换为目标代码的日期 |
| `__TIME__` | 这会包含一个形式为 hour:minute:second 的字符串，它表示程序被编译的时间 |

# 信号处理

信号由操作系统传给进程的中断，会提早终止一个程序

有些信号不能被程序捕获，但是下表所列信号可以在程序中捕获，并可以基于信号采取适当的动作

这些信号定义在头文件`<csignal>`中

| 信号    | 描述                                       |
| ------- | ------------------------------------------ |
| SIGABRT | 程序的异常终止，如调用 **abort**           |
| SIGFPE  | 错误的算术运算，比如除以零或导致溢出的操作 |
| SIGILL  | 检测非法指令                               |
| SIGINT  | 程序终止(interrupt)信号                    |
| SIGSEGV | 非法访问内存                               |
| SIGTERM | 发送到程序的终止请求                       |

## `signal`函数

C++使用 signal 函数来捕获突发事件

```cpp
void (*signal(int sig, void (*func)(int)))(int);  // 原型
```

```cpp
signal(registered signal, signal handler)
```

函数接收两个参数：

- 第一个参数是要设置的信号的标识符
- 第二个参数是指向信号处理函数的指针

返回值是一个指向先前信号处理函数的指针，如果之前没有设置信号处理函数，则返回值为 SIG_DFL

```cpp
#include <iostream>
#include <csignal>
#include <unistd.h>
 
using namespace std;
 
void signalHandler( int signum ){
    cout << "Interrupt signal (" << signum << ") received.\n";
 
    // 清理并关闭
    // 终止程序  
    exit(signum);  
 }
 
int main (){
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);  
 
    while(1){
       cout << "Going to sleep...." << endl;
       sleep(1);
    }
    return 0;
}
```

## `raise`函数

使用`raise`函数生成信号，该函数带有一个整数编号作为参数

```cpp
int raise (signal sig);
```

```cpp
#include <iostream>
#include <csignal>
#include <unistd.h>
 
using namespace std;
 
void signalHandler( int signum ){
    cout << "Interrupt signal (" << signum << ") received.\n";
    // 清理并关闭
    // 终止程序 
    exit(signum);  
}
 
int main (){
    int i = 0;
    // 注册信号 SIGINT 和信号处理程序
    signal(SIGINT, signalHandler);  
 
    while(++i){
        cout << "Going to sleep...." << endl;
        if( i == 3 ){
            raise( SIGINT);
        }
        sleep(1);
    }
 
    return 0;
}
```

# 多线程

多任务处理允许让电脑同时运行两个或两个以上的程序，一般来说，多任务处理分为两种类型：**基于进程**和**基于线程**

- 基于进程的多任务处理是程序的并发执行
- 基于线程的多任务处理是同一程序的片段的并发执行

多线程程序包含可以同时运行的两个或多个部分

程序中的每个部分称为一个线程，每个线程定义了一个单独的执行路径

使用 Linux 操作系统，使用 POSIX 编写多线程 C++ 程序

## 创建线程

创建一个 POSIX 线程

```cpp
#include<pthread.h>
pthread_create(thread, attr, start_routine, arg);
```

`thread`：指向线程标识符的指针

`attr`：一个不透明的属性对象，可以被用来设置线程属性。您可以指定线程属性对象，也可以使用默认值 NULL

`start_routine`：线程运行函数起始地址，一旦线程被创建就会执行

`arg`：运行函数的参数。它必须通过把引用作为指针强制转换为 void 类型进行传递。如果没有传递参数，则使用 NULL

返回值：创建线程成功时，函数返回 0，若返回值不为 0 则说明创建线程失败

## 终止线程

终止一个 POSIX 线程

```cpp
#include <pthread.h>
pthread_exit(status) 
```

**pthread_exit** 用于显式地退出一个线程

如果 `main()` 是在它所创建的线程之前结束，并通过 `pthread_exit()` 退出，那么其他线程将继续执行。否则，它们将在 `main()` 结束时自动被终止

### 向线程传递参数

```cpp
#include <iostream>
#include <cstdlib>
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS     5
 
struct thread_data{
    int  thread_id;
    char *message;
};
 
void *PrintHello(void *threadarg){
    struct thread_data *my_data;
    
    my_data = (struct thread_data *) threadarg;
 
    cout << "Thread ID : " << my_data->thread_id ;
    cout << " Message : " << my_data->message << endl;
 
    pthread_exit(NULL);
}
 
int main (){
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;
    int i;
 
    for( i=0; i < NUM_THREADS; i++ ){
        cout <<"main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].message = (char*)"This is message";
        rc = pthread_create(&threads[i], NULL,
                          PrintHello, (void *)&td[i]);
        if (rc){
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
```

## 连接和分离线程

```cpp
pthread_join(threadid, status); 
pthread_detach(threadid);
```

## `std::thread`及其成员函数【`<thread>`库】

C++ 11 之后添加了新的标准线程库 **`std::thread`**，在语言层面实现了多线程，程序可移植性大大提高

**`std::thread`** 在 `<thread>` 头文件中声明

```bash
# 设置编译器使用 c++11 编译
g++ -std=c++11 test.cpp
```

### `std::thread`构造函数

**默认构造函数**，创建一个空的 std::thread 执行对象

```cpp
thread() noexcept;
```

**初始化构造函数**

创建一个 `std::thread` 对象，该 `std::thread` 对象可被 `joinable`，新产生的线程会调用 `fn` 函数，该函数的参数由 `args` 给出

`Fn`：可调用对象：函数指针/函数对象/Lambda表达式

```cpp
template<class Fn, Class...Args>
explict thread(Fn&& fn, Args&&... args);
```

**拷贝构造函数**（禁用），意味着 `std::thread` 对象不可拷贝构造

```cpp
thread(const thread&) = delete;
```

**移动构造函数**，调用成功之后 `x` 不代表任何 `std::thread` 执行对象

```cpp
thread(thread&& x) noexcept;
```

注意：可被 `joinable` 的 `thread` 对象必须在他们销毁之前被主线程 `join` 或者将其设置为 `detached`.

---

```cpp
// 演示多线程的CPP程序
// 使用三个不同的可调用对象
#include <iostream>
#include <thread>
using namespace std;
  
// 一个虚拟函数
void foo(int Z){
    for (int i = 0; i < Z; i++) {
        cout << "线程使用函数指针作为可调用参数\n";
    }
}
  
// 可调用对象
class thread_obj {
public:
    void operator()(int x)
    {
        for (int i = 0; i < x; i++)
            cout << "线程使用函数对象作为可调用参数\n";
    }
};
  
int main(){
    cout << "线程 1 、2 、3 "
         "独立运行" << endl;
  
    // 函数指针
    thread th1(foo, 3);
  
    // 函数对象
    thread th2(thread_obj(), 3);
  
    // 定义 Lambda 表达式
    auto f = [](int x) {
        for (int i = 0; i < x; i++)
            cout << "线程使用 lambda 表达式作为可调用参数\n";
    };
  
    // 线程通过使用 lambda 表达式作为可调用的参数
    thread th3(f, 3);
  
    // 等待线程完成
    // 等待线程 t1 完成
    th1.join();
  
    // 等待线程 t2 完成
    th2.join();
  
    // 等待线程 t3 完成
    th3.join();
  
    return 0;
}
```

### `std::thread`赋值操作

Move 赋值操作：如果当前对象不可 `joinable`，需要传递一个右值引用(`rhs`)给 `move` 赋值操作；如果当前对象可被 `joinable`，则会调用 `terminate`() 报错。

```cpp
thread& operator=(thread&& rhs) noexcept;
```

拷贝赋值操作（禁用），`std::thread` 对象不可拷贝赋值

```cpp
thread& operator=(const thread&) = delete;
```

### `get_id()`

获取线程 ID，返回一个类型为 `std::thread::id` 的对象

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void foo(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(){
    std::thread t1(foo);
    std::thread::id t1_id = t1.get_id();
    
    std::thread t2(foo);
    std::thread::id t2_id = t2.get_id();

    std::cout << "t1's id: " << t1_id << '\n';
    std::cout << "t2's id: " << t2_id << '\n';

    t1.join();
    t2.join();
}
```

### `join()`

回收线程，调用该函数会阻塞当前线程，直到由 *this 所标识的线程执行完毕 join 才返回

为什么需要用 join？

主线程创建两个线程后，三个线程各自走各自的互不干扰，当主线程走完时，这两个线程可能还没走完，即线程仍然存在，又由于线程的对象是在主线程创建的，主线程走完，线程对象便销毁，但子线程还存在这就导致崩溃，所以要加join让主线程先等子线程走完再结束

### `joinable()`

`joinable` 方法主要判断是否可以使用 `join` 方法或者 `detach` 方法，可以返回 `true`，不可以返回 `false`

一个线程最多只能调用一次 `join` 或者 `detach`

```cpp
#include <iostream>
#include <thread>

void func(){
	// ...
}

int main(){
	std::thread th1(func);
	
	if(th1.joinable())
		th1.join();
	else
		cout << "thread is disjoinable!" << endl;
}
```

### `detach()`

`detach`有脱离分离的意思，线程调用该方法可以使得主线程和子线程失去上下级关系，二者平行。子线程运行完毕会自动退出，主线程也无须等待子线程运行完毕

当主线程和子线程并没有产生交集时，可以使子线程进行脱离，运行完毕自动回收

- 举个例子：例如用户登录软件或者Web页面，当账户验证通过时主线程需要继续响应用户的登录请求，而用户的登录日志的保存或者一些其他的日志需要子线程去保存，此时主线程和子线程没有任何交集，总不可能主线程等待子线程存完日志再响应用户吧？因此类似这种情况可以让子线程自动脱离，运行完毕自动结束
- 类似于驻留后台的守护线程：脱离的子线程由C++运行时库接管，当子线程运行完毕时由运行时库负责清理该线程的相关资源

调用  `detach()` 之后

- `joinable() == false`
- `get_id() == std::thread::id()`

```cpp
#include <iostream>
#include <thread>

void thread_func1(){
    std::cout << "thread create!" << std::endl;
}
int main(){
    std::thread mythread1(thread_func1);
    mythread1.detach();
    std::cout << "main thread executed finish!" << std::endl;
    return 0;
}
```

### `swap()`

`swap()`交换两个线程对象所代表的底层句柄(underlying handles)

```cpp
#include <iostream>
#include <thread>
#include <chrono>

void foo(){
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar(){
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(){
	std::thread t1(foo);
	std::thread t2(bar);

	std::cout << "thread 1 id: " << t1.get_id() << std::endl;
	std::cout << "thread 2 id: " << t2.get_id() << std::endl;

	std::swap(t1, t2);

	std::cout << "after std::swap(t1, t2):" << std::endl;
	std::cout << "thread 1 id: " << t1.get_id() << std::endl;
	std::cout << "thread 2 id: " << t2.get_id() << std::endl;

	t1.swap(t2);

	std::cout << "after t1.swap(t2):" << std::endl;
	std::cout << "thread 1 id: " << t1.get_id() << std::endl;
	std::cout << "thread 2 id: " << t2.get_id() << std::endl;

	t1.join();
	t2.join();
}
```

### `native_handle`

返回 native handle（由于 std::thread 的实现和操作系统相关，因此该函数返回与 std::thread 具体实现相关的线程句柄）

### `hardware_concurrency[static]`

**`hardware_concurrency [static]`**: 检测硬件并发特性，返回当前平台的线程实现所支持的线程并发数目，但返回值仅仅只作为系统提示

```cpp
unsigned int n = std::thread::hardware_concurrency();
cout << n << endl;
```

## `std::this_thread`命名空间中相关辅助函数介绍

### `get_id()`

获取线程ID

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex g_display_mutex;

void foo(){
	std::thread::id t_id = std::this_thread::get_id();

	g_display_mutex.lock();
	std::cout << "thread id is " << t_id << endl;
	g_display_mutex.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(1));
}


int main(){
	std::thread t1(foo);
	std::thread t2(foo);

	t1.join();
	t2.join();
}
```

### `yield()`

当前线程放弃执行，操作系统调度另一线程继续执行

```cpp
#include <iostream>
#include <chrono>
#include <thread>

// 使当前线程暂停 us 时间
void little_sleep(std::chrono::microseconds us){
	auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    little_sleep(std::chrono::microseconds(100));

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
        << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
        << " microseconds\n";
}
```

### `sleep_until()`

线程休眠至某个指定的时刻（time point），该线程才被重新唤醒

```cpp
template< class Clock, class Duration>
void sleep_until( const std::chrono::time_point<Clock,Duration>& sleep_time );
```

### `sleep_for()`

线程休眠某个指定的时间片（time span），该线程才被重新唤醒，不过由于线程调度等原因，实际休眠时间可能比 `sleep_duration`所表示的时间片更长

```cpp
std::chrono::milliseconds dura(2000);
std::this_thread::sleep_for(dura);
```

# `<chrono>`库

C++11 引入了 `<chrono>` 库，这是一个用于处理时间和日期的库。它提供了一套丰富的工具来测量时间间隔、执行时间点的计算以及处理日期和时间。`<chrono>` 库是 C++ 标准库中处理时间相关操作的核心部分

## 基本概念

**时间点（Time Points）**

时间点表示一个特定的时间点，通常与某个特定的时钟相关联

**持续时间（Durations）**

持续时间表示两个时间点之间的时间间隔



# STL 标准模板库

标准模板库STL：

- 建立一种可重复使用的东西
- 建立数据结构和算法的一套标准

STL的六大组件：容器、算法、迭代器、仿函数、适配器、空间配置器

- 容器：提供了各种数据结构，包括向量（vector）、链表（list）、队列（queue）、栈（stack）、集合（set）、映射（map）等。这些容器具有不同的特性和用途，可以根据实际需求选择合适的容器
- 算法：STL 提供了大量的算法，用于对容器中的元素进行各种操作，包括排序、搜索、复制、移动、变换等。这些算法在使用时不需要关心容器的具体类型，只需要指定要操作的范围即可
- 迭代器：迭代器用于遍历容器中的元素，允许以统一的方式访问容器中的元素，而不用关心容器的内部实现细节。STL 提供了多种类型的迭代器，包括随机访问迭代器、双向迭代器、前向迭代器和输入输出迭代器等
- 仿函数【函数对象】：函数对象是可以像函数一样调用的对象，可以用于算法中的各种操作。STL 提供了多种函数对象，包括一元函数对象、二元函数对象、谓词等，可以满足不同的需求
- 适配器：适配器用于将一种容器或迭代器适配成另一种容器或迭代器，以满足特定的需求。STL 提供了多种适配器，包括栈适配器（stack adapter）、队列适配器（queue adapter）和优先队列适配器（priority queue adapter）等
- 空间配置器：负责空间的配置和管理

## 容器

STL 中的容器可以分为三类：

1. 序列容器：强调值的排序，序列容器中的每个元素均有固定的位置
   - `vector`：动态数组，支持快速随机访问
   - `deque`：双端队列，支持快速插入和删除
   - `list`：链表，支持快速插入和删除，但不支持随机访问
2. 关联容器：存储键值对，每个元素都有一个键（key）和一个值（value），并且通过键来组织元素
   - `set`：集合，不允许重复元素
   - `multiset`：多重集合，允许多个元素具有相同的键
   - `map`：映射，每个键映射到一个值
   - `multimap`：多重映射，允许多个键映射到相同的值
3. 无序容器（C++11引入）：哈希表，支持快速的查找、插入和删除
   - `unordered_set`：无序集合
   - `unordered_multiset`：无序多重集合
   - `unordered_map`：无序映射
   - `unordered_multimap`：无序多重映射

## 算法

算法可分为两类：质变算法和非质变算法

- 质变算法：指运算过程中会更改区间内的元素的内容
- 非质变算法：运算过程中不会更改区间内的元素内容

## 迭代器

迭代器是容器和算法之间的粘合剂

提供一种方法，使之能够依序寻访某个容器所包含的各个元素，而又无需暴露改容器的内部表示方式

每个容器都有自己专属的迭代器

算法要通过迭代器访问容器里面各个元素

| 迭代器种类     | 访问权限                           | 支持操作                                 |
| -------------- | ---------------------------------- | ---------------------------------------- |
| 输入迭代器     | 对数据只读访问                     | 只读，支持++，==，!=                     |
| 输出迭代器     | 对数据只写访问                     | 只写，支持++                             |
| 前向迭代器     | 读写操作，并能向前推进             | 读写，++，==，!=                         |
| 双向迭代器     | 读写操作，向前向后操作             | 读写，支持++，--                         |
| 随机访问迭代器 | 读写操作，可以跳跃方式访问任意数据 | 读写，支持++、--、[n]、- n、<、<=、>、>= |

## `vector`

