#include <iostream>
#include <cmath>
#include <iomanip>

class Array
{
public:

    typedef double
        value_type;
    typedef double*
        iterator;
    typedef const double*
        const_iterator;
    typedef double&
        reference;
    typedef const double&
        const_reference;
    typedef std::size_t
        size_type;

    Array(const size_type n);
    Array(const Array& array);
    Array(iterator first, iterator last);

    ~Array()
    {
        delete[]ptr;
    }

    Array& operator=(const Array&);

    iterator begin() { return ptr; }
    const_iterator begin() const { return ptr; }
    iterator end() { return ptr + Count; }
    const_iterator end() const { return ptr + Count; }

    size_type size() const
    {
        return Count;
    }

    void resize(size_type newsize);

    size_type capacity() const
    {
        return sizemem;
    }

    // текущий размер массива
    bool empty() const
    {
        if (Count == 0)
            return true;
        else
            return false;
    }

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    reference front() { return ptr[0]; }
    const_reference front() const { return ptr[0]; }

    reference back()
    {
        return ptr[size() - 1];
    }

    const_reference back() const { return ptr[size() - 1]; }

    void swap(Array& other);

    void assign(const value_type& v);

    void push_back(const value_type& v);

    void pop_back()
    {
        ptr[Count - 1] = 0;
        Count--;
    }

    // очистить массив
    void clear()
    {
        Count = 0;
    }

    void show()
    {
        for (int i = 0; i < Count; i++)
        {
            std::cout.precision(3);
            std::cout << std::fixed << ptr[i] << " ";
        }
        std::cout << '\n';
    }

private:
    // указатель на данные
    value_type* ptr;

    // количество элементов в массиве
    size_type Count;

    // минимальный размер массива
    static const size_type min = 10;

    // выделено элементов в памяти
    size_type sizemem;

};

double summary(const Array& arr)
{
    double sum = 0;

    for (int i = 0; i < arr.size(); i++)
        sum += arr[i];

    return sum;
}

double average(const Array& arr)
{
    double aver = summary(arr) / arr.size();

    return aver;
}

void helper(Array& arr)
{
    int c;

    float f, five, halfsum;

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < 0)
        {
            f = arr[i];

            break;
        }
    }

    for (int i = 0; i < arr.size(); i++)
    {
        if (i == 5)
        {
            five = arr[i];

            break;
        }
    }

    halfsum = (f + five) / 2;

    for (int i = 0; i < arr.size(); i++)
        (arr.begin())[i] = (arr.begin())[i] / halfsum;
}

void Array::push_back(const value_type& v)
{
    if (Count == sizemem)
        resize(sizemem * 2);

    ptr[Count++] = v;
}

void Array::resize(size_type newsize)
{
    value_type* s = new value_type[newsize];

    for (size_type i = 0; i < Count; ++i)
        s[i] = ptr[i];

    delete[] ptr;

    ptr = s;
    sizemem = newsize;
}

Array::Array(iterator first, iterator last)
{
    if (first < last)
    {
        sizemem = (first - last);
        ptr = new value_type[sizemem];

        for (int i = 0; i < sizemem; ++i)
            ptr[i] = *(first + i);

        Count = sizemem;
    }
}

Array::Array(const size_type n)
{
    sizemem = n;
    ptr = new value_type[n];
    Count = 0;
}

double& Array::operator[](size_type index)
{
    if (index < Count)
        return ptr[index];
}

const double& Array::operator[](size_type index) const
{
    if (index < Count)
        return ptr[index];
}

int main()
{
    int size, c = 1;
    double elem, sum = 0, aver = 0;

    std::cin >> size;

    Array arr(size);

    for (int i = 0; i < size; i++)
    {
        std::cin >> elem;

        arr.push_back(elem);
    }

    std::cout << arr.size() << '\n';

    arr.show();

    sum = summary(arr);
    aver = average(arr);

    arr.push_back(sum);
    arr.push_back(aver);

    arr.show();

    helper(arr);

    arr.show();

    while (true)
    {
        std::cin >> c;

        if (c == 0)
        {
            break;
        }

        else
        {
            switch (c)
            {
            case 1:
                std::cin >> elem;

                arr.push_back(elem);

                std::cout << "+:" << arr.size() << '\n';

                arr.show();

                sum = summary(arr);
                aver = average(arr);

                arr.push_back(sum);
                arr.push_back(aver);

                arr.show();

                helper(arr);

                arr.show();

                break;
            case 2:
                arr.pop_back();

                std::cout << "-:" << arr.size() << '\n';

                arr.show();

                sum = summary(arr);
                aver = average(arr);

                arr.push_back(sum);
                arr.push_back(aver);

                arr.show();

                helper(arr);

                arr.show();
                break;
            }
        }
    }
    return 0;
}