# 目录

[13.1](#13.1)

[13.2](#13.2)

[13.3](#13.3)

[13.4](#13.4)

[13.5](#13.5)

[13.6](#13.6)

[13.7](#13.7)

[13.8](#13.8)

[13.9](#13.9)

[13.10](#13.10)

[13.11](#13.11)

[13.12](#13.12)

[13.13](#13.13)

## <span id="13.1">13.1</span>

> 拷贝构造函数是什么？什么时候使用它？

如果一个构造函数的第一个参数是自身类型的引用，且任何其他额外参数都有默认值，则此构造函数是拷贝构造函数。

拷贝构造函数通常在发生拷贝构造的时候使用，而拷贝构造发生的条件如下：

1. 使用“=”定义变量时
2. 将一个对象作为实参传递一个非引用类型的形参
3. 从一个返回类型为非引用类型的函数返回一个对象
4. 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员

## <span id="13.2">13.2</span>

> 解释为什么下面的声明时非法的：
>
> ```c++
> Sales_data::Sales_data(Sales_data rhs);
> ```

拷贝构造函数的第一个参数必须是自身类型的引用。否则参数传递时需要调用拷贝构造函数将发生无限次循环调用。

## <span id="13.3">13.3</span>

> 当我们拷贝一个StrBlob时，会发生什么？拷贝一个StrBlobPtr呢？

```c++
void test()
{
    StrBlob sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 1
    StrBlob sb2(sb1);
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 2

    StrBlobPtr sbp1(sb1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;		// 2
    StrBlobPtr sbp2 (sbp1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;		// 2
}
```

拷贝StrBlob时，其shared_ptr成员的引用计数会增加。拷贝StrBlobPtr, unique_ptr成员的引用计数不变，其引用了shared_ptr的引用计数。

## <span id="13.4">13.4</span>

> 假定Point是一个类型，它有一个public的拷贝构造函数，指出下面程序片段中哪些地方使用了拷贝构造函数。
>
> ```c++
> Point global;
> Point foo_bar(Point arg)	// 传参时使用了拷贝构造函数1
> {
>     Point local = arg, *heap = new Point(global);	// 使用了拷贝构造函数2，3
>     *heap = local;
>     Point pa[4] = {local, *heap};	// 使用了拷贝构造函数4,5
>     return *heap;	// 返回值时使用了拷贝构造函数6
> }
> ```



## <span id="13.5">13.5</span>

> 给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。你的拷贝构造函数应该动态分配一个新的string，并将对象拷贝到ps指向的位置，而不是拷贝ps本身：
>
> ```c++
> class HasPtr
> {
> public:
>     HasPtr(const std::string& s = std::string()) :
>     	ps(new std::string(s)), i(0) {}
>     // 拷贝构造函数
>     HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
> private:
>     std::string *ps;
>     int i;
> };
> ```

## <span id="13.6">13.6</span>

> 拷贝赋值运算符是什么？什么时候使用它？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？

拷贝赋值运算符是重载“=”运算符，即为一个名为operator=的函数，其参数与其所在类的类型相同，返回一个指向其左侧运算对象的引用。

在发生赋值操作时使用。

合成拷贝赋值运算符的工作：将后侧运算对象的每歌非static成员赋予左边运算对象的对应成员。】

当类未定义自己的拷贝赋值运算符时，编译器会自动生成一个合成拷贝赋值运算符。

## <span id="13.7">13.7</span>

> 当我们将一个StrBlob赋值给另一个StrBlob时，会发生什么？赋值StrBlobPtr呢？

```c++
void test()
{
    StrBlob sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 1
    StrBlob sb2 = sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 2

    StrBlobPtr sbp1(sb1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;	// 2
    StrBlobPtr sbp2 = sbp1;
    cout << "reference count of sbp1 is " << sbp1.count() << endl;	// 2
}
// 会发生浅拷贝，所有的指针都指向同一块内存。与拷贝一样，赋值StrBlob时，shared_ptr的引用计数加1，赋值StrBlobPtr时，引用计数不变。
```

## <span id="13.8">13.8</span>

>为13.1.1节练习13.5中的HasPtr类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该讲对象拷贝到ps指向的位置。

```c++
HasPtr& operator=(const HasPtr& hp)
{
    ps = new std::string(*hp.ps);
    i = hp.i;
    return *this;
}
```

## <span id="13.9">13.9</span>

> 析构函数是什么？合成析构函数完成什么工作？什么时候回生成合成析构函数？

析构函数是类的一个成员，名字由波浪线接类名组成，没有返回值也没有参数。

对于某些类，合成析构函数被用来阻止该类型的自动销毁。如果不是这种情况，合成析构函数的函数体就为空。

当一个类没有定义自己的析构函数时，编译器会为它生成一个合成析构函数。

## <span id="13.10">13.10</span>

> 当一个StrBlob对象销毁时会发生什么？一个StrBlobPtr对象销毁时呢？

销毁StrBlob时，分别会执行vector、shared_ptr、string的析构函数，vector析构函数会销毁我们添加到vector中的元素，shared_ptr析构函数会递减StrBlob对象的引用计数。销毁一个StrBlobPtr时，string、weak_ptr的析构函数执行，但是不会更改weak_ptr绑定的shared_ptr的引用计数，所以指向的对象不一定被销毁。

## <span id="13.11">13.11</span>

> 为前面练习中的HasPtr类添加一个析构函数。

```c++
~HasPtr()
{
    delete ps;
}
```

## <span id="13.12">13.12</span>

>在下面的代码片段中会发生几次析构函数调用？
>
>```c++
>bool fun(const Sales_data *trans, Sales_data accum)
>{
>    Sales_data item1(*trans), item2(accum);
>    return item1.isbn() != item2.isbn();
>}
>```

会发生三次析构函数调用，item1和item2分别调用一次析构函数，形参accum也会调用一次析构函数，通过代码验证过。

## <span id="13.13">13.13</span>

> 理解拷贝控制成员和构造函数的一个好方法是定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字：
>

> ```c++
> struct X {
>     X() { std::cout << "X()" << std::endl; }
>     X(const X& x) { std::cout << "X(const X&)" << std::endl; }
> };
> ```
>

> 给X添加拷贝赋值运算符和析构函数，并编写一个程序以不同的方式使用X的对象：将它们作为非引用和引用参数传递；动态分配它们；将它们存放于容器中；诸如此类。观察程序的输出，知道你确认理解了什么时候会使用拷贝控制成员，以及为什么会使用它们。当你观察程序时，记住编译器可以略过对拷贝构造函数的调用。
>

```c++
#include <iostream>
#include <vector>

struct X
{
    X() {std::cout << "X()" << std::endl;}
    X(const X& x) {std::cout << "X(const X&)" << std::endl;}
    X& operator=(const X& x);
    ~X() {std::cout << "~X()" << std::endl;}
};

X& X::operator=(const X& x) {
    std::cout << "operator=(const X&)" << std::endl;
    return *this;
}

void f(X& x1, X* x2)
{
    std::vector<X> xvec;
    xvec.push_back(x1);     // 调用拷贝构造函数，将x1拷贝到vector中
    /*
     * 解引用指针x2生成一个X匿名对象，此时要调用拷贝构造函数，然后将x2的值拷贝到xvec中,
     * 再次调用拷贝构造函数，拷贝结束后临时的匿名对象销毁调用析构函数。
     */
    xvec.push_back(*x2);
    // 销毁xvec，调用容器里面的两个元素的析构函数
    std::cout << "--------destructor in f---------" << std::endl;
}

void dynamicAllowcate()
{
    std::cout << "-------constructor--------" << std::endl;
    X x1;   // 默认构造函数
    X* x2 = new X();    // 默认构造函数构造匿名对象并用指针x2指向它
    X x3;   // 默认构造函数
    x3 = x1;    // 拷贝赋值运算符
    std::cout << "--------copy constructor--------" << std::endl;
    f(x1, x2);
    std::cout << "------destructor 1--------" << std::endl;
    delete x2;  // 销毁x2，x2指向的对象调用析构函数被销毁
    std::cout << "------destructor 2--------" << std::endl; // x1和x3调用析构函数
}

int main()
{
    dynamicAllowcate();
    return 0;
}
```

运行结果：

```c++
-------constructor--------
X()
X()
X()
operator=(const X&)
--------copy constructor--------
X(const X&)
X(const X&)
X(const X&)
~X()
--------destructor in f---------
~X()
~X()
------destructor 1--------
~X()
------destructor 2--------
~X()
~X()
```

