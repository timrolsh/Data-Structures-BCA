#include <vector>

using std::vector;

template<class T>
struct Link {
    explicit Link(const T &info, Link *next = 0) : info(info), next(next) {
    }

    // This avoids stack overflow
    ~Link() {
        Link *p = next;
        while (p) {
            Link *q = p->next;
            p->next = nullptr;
            delete p;
            p = q;
        }
    }

    T info;
    Link *next;
};

vector<int> loopTail(Link<int> *head);

vector<int> josephus(int n, int k);