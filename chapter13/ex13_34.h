//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_34_H
#define CPP_PRIMER_EX13_34_H

#include <string>
#include <set>

class Folder;
class Message {
    friend class Folder;
    friend void swap(Message&, Message&);

public:
    // folder被隐式初始化为空集合
    explicit Message(const std::string &str = "") : contents(str) {}
    // 拷贝控制成员，用来管理指向本Message的指针
    Message(const Message&);    // 拷贝构造函数
    Message& operator=(const Message&);     // 拷贝赋值运算符
    Message(Message&&);     // 移动构造函数
    Message& operator=(Message&&);  // 移动赋值运算符
    ~Message();
    // 从给定的Folder集合中添加/删除本Message
    void save(Folder&);
    void remove(Folder&);
    void addFolder(Folder*);
    void remFolder(Folder*);

private:
    std::string contents;   // 实际文本消息
    std::set<Folder*> folders;  // 包含文本Message的Folder
    // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
    // 将本Message添加到指向参数的Folder中
    void add_to_Folders(const Message&);
    // 从folders中的每个Folder中删除本Message
    void remove_from_Folders();
};

#endif //CPP_PRIMER_EX13_34_H
