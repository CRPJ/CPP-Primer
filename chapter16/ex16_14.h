//
// Created by wangheng on 2020/6/10.
//

#ifndef CPP_PRIMER_EX16_14_H
#define CPP_PRIMER_EX16_14_H

#include <string>
#include <iostream>

template<unsigned H, unsigned W>
class Screen{
    // 从头打印到cursor所在的位置
    friend std::ostream& operator<<(std::ostream& os, const Screen<H, W> &c) {
        unsigned lines = c.cursor / c.width;
        int i;
        for (i = 0; i < lines; ++i) {
            os << c.contents.substr(i * c.width, c.width) << std::endl;
        }
        os << c.contents.substr(i*c.width, c.cursor - i * c.width) << std::endl;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, const Screen &c) {
        char a;
        is >> a;
        c.contents = std::string(H * W, a);
        return is;
    }

public:
    typedef std::string::size_type pos;

    Screen() = default; // 因为有一个自定义的构造函数，所以默认构造函数必须显示声明，否则不会合成

    explicit Screen(char c) : contents(H*W, c) {}
    char get() const {
        return contents[cursor];
    }
    void set(char c) {
        contents[cursor] = c;
    }

    Screen& move(pos r, pos c);

private:
    pos cursor = 0;
    pos height = H, width = W;
    std::string contents;
};

template<unsigned H, unsigned W>
inline Screen<H, W>& Screen<H, W>::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

#endif //CPP_PRIMER_EX16_14_H