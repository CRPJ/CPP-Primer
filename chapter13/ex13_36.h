//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_36_H
#define CPP_PRIMER_EX13_36_H

#include <set>
#include "ex13_34.h"

class Folder {
public:
    Folder() {}
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    void addMsg(Message*);
    void remMsg(Message*);

private:
    std::set<Message*> messages;
};

void Folder::addMsg(Message *m) {
    messages.insert(m);
}

void Folder::remMsg(Message *m) {
    messages.erase(m);
}

Folder::Folder(const Folder &f) : messages(f.messages) {
    for (auto m : messages)
        m->addFolder(this);
}

Folder& Folder::operator=(const Folder &f) {
    for (auto m : messages)
        m->remFolder(this);
    messages = f.messages;
    for (auto m : messages)
        m->addFolder(this);
    return *this;
}

#endif //CPP_PRIMER_EX13_36_H
