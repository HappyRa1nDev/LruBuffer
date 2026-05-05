#pragma once
#include <unordered_map>
#include <set>
#include <utility>
#include <stdexcept>

class LruBuffer {
private:
    size_t maxSize = 1;
    size_t Tm = 0;
    std::unordered_map<int, int> Data;
    std::unordered_map<int, int> LastUse;
    std::set<std::pair<int, int>> Queue;

public:
    LruBuffer(int max_size) : maxSize(max_size) {}

    void erase(int key) {
        if (!Data.count(key)) {
            throw std::runtime_error("fail erase");
        }
        Queue.erase({LastUse[key], key});
        LastUse.erase(key);
        Data.erase(key);
    }

    void set(int key, int val) {
        if (Data.count(key)) {
            erase(key);
        }
        if (Data.size() == maxSize) {
            auto [_, kk] = *Queue.begin();
            erase(kk);
        }
        Data[key] = val;
        LastUse[key] = Tm++;
        Queue.insert({LastUse[key], key});
    }

    int get(int key) {
        if (!Data.count(key)) {
            throw std::runtime_error("bad key");
        }

        Queue.erase({LastUse[key], key});
        LastUse[key] = Tm++;
        Queue.insert({LastUse[key], key});

        return Data[key];
    }

    bool check(int key) {
        return Data.count(key);
    }
};
