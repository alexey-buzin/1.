
#include <iostream>

template <typename T, int minc = 0> class Vector
{
  public:
    int cup = minc;
    int size;
    T *v = 0;
    Vector(int size = 0)
        : cup(minc > size ? minc : size), size(size), v(new T[cup])
    {
    }

    void push_back(T &&a)
    {
        if (cup == size) {
            T *nv = new T[cup * 2];
            for (int i = 0; i < cup; ++i) {
                nv[i] = v[i];
            }
            delete[] v;
            v = nv;
            cup *= 2;
        }
        v[size] = a;
        size++;
    }

    T pop_back()
    {
        if (cup < 2 * size) {
            size--;
            return v[size];
        } else {
            int nc = cup / 2 > minc ? cup / 2 : minc;
            T *nv = new T[nc];
            for (int i = 0; i < nc; ++i) {
                nv[i] = v[i];
            }
            delete[] v;
            v = nv;
            cup = nc;

            if (size > 0) {
                size--;
                return v[size];
            }
            throw "vector is empty";
        }
    }

    ~Vector() { delete[] v; }
};

int main()
{
    Vector<int, 2> vec;
    vec.push_back(1);
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.push_back(2);
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.pop_back();
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.push_back(3);
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.push_back(4);
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.pop_back();
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.push_back(5);
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.pop_back();
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    vec.pop_back();
    std::cout << vec.size << " " << vec.cup << " " << vec.v[vec.size - 1]
              << std::endl;

    return 0;
}