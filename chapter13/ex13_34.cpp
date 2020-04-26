//
// Created by wangheng on 2020/4/25.
//

#include "ex13_34.h"
#include "ex13_36.h"

Message::Message(const Message &rhs) : contents(rhs.contents), folders(rhs.folders) {
    add_to_Folders(rhs);    // 将本消息添加到指向rhs的Folder中
}

Message& Message::operator=(const Message &rhs) {
    // 通过先删除指针再插入他们来处理自赋值情况
    this->remove_from_Folders();    // 更新已有Folder
    contents = rhs.contents;        // 从rhs拷贝消息
    folders = rhs.folders;          // 从rhs拷贝Folder指针
    this->add_to_Folders(rhs);      // 将本Message添加到那些Folder中
    return *this;
}

Message::Message(Message &&m) : contents(std::move(m.contents)) {
    m.remove_from_Folders();
    folders = std::move(m.folders);
    add_to_Folders(*this);
}

Message& Message::operator=(Message &&rhs) {
    if (this != &rhs) {
        rhs.remove_from_Folders();
        contents = std::move(rhs.contents);
        folders = std::move(rhs.folders);
        add_to_Folders(*this);
    }
    return *this;
}

Message::~Message() {
    remove_from_Folders();
}

void Message::save(Folder &f) {
    folders.insert(&f);     // 将给定Folder添加到我们的Folder列表中
    f.addMsg(this);         // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f) {
    folders.erase(&f);      // 将给定的Folder从我们的Folder列表中删除
    f.remMsg(this);         // 将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders)   // 对每个包含m的folder
        f->addMsg(this);        // 向该Folder添加一个指向本Message的指针
}

void Message::remove_from_Folders() {
    for (auto f : this->folders)   // 对folders中每个指针
        f->remMsg(this);    // 从该Folder中删除Message
}

void swap(Message& lhs, Message& rhs) {
    using std::swap;
    // 将每个消息的指针从它（原来）所在的Folder中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    // 交换contents和Folder指针set
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    // 将每个Message的指针添加到它的（新）Folder中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void Message::addFolder(Folder *f) {
    folders.insert(f);
}

void Message::remFolder(Folder *f) {
    folders.erase(f);
}