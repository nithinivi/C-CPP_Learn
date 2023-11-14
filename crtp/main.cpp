#include <cstdio>

template <typename T>
struct CRTP
{
    T& underlying() { return static_cast<T&>(*this); }
    const T& underlying() const { return static_cast<const T&>(*this); }

    T& like_underlying(CRTP& other) { return static_cast<T&>(other); }

    const T& like_underlying(const CRTP& other) const
    {
        return static_cast<const T&>(other);
    }
};

template <typename T>
struct LogicalFunctions : public CRTP<T>
{
    bool operator==(const LogicalFunctions& rhs) const
    {
        const auto rhs_ = this->like_underlying(rhs);
        const auto lhs_ = this->underlying();
        return !(lhs_ < rhs_ || rhs_ < lhs_);
    }

    bool operator!=(const LogicalFunctions& rhs) const
    {
        const auto rhs_ = this->like_underlying(rhs);
        const auto lhs_ = this->underlying();
        return !(lhs_ == rhs_);
    }
};

struct Drevied : public LogicalFunctions<Drevied>
{
    int m_value;
    Drevied(const int value) : m_value{value} {}

    bool operator<(const Drevied& rhs) const { return m_value < rhs.m_value; }
};

Drevied getValue()
{
    static int cur_value = 0;
    return Drevied{++cur_value};
};

int main()
{
    auto a = getValue();
    auto b = getValue();
    printf("%d \n", b != a);
    printf("%d \n", b == a);
    printf("%d \n", a == a);
    return 1;
}