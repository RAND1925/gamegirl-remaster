//
// Created by rand1925 on 2021/2/16.
//

#ifndef GAMEGIRL_SINGLETON_H
#define GAMEGIRL_SINGLETON_H

template <typename T>
class Singleton {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }
};


#endif //GAMEGIRL_SINGLETON_H
