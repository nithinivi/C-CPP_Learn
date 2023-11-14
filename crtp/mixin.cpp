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
struct EqualityOperators : public CRTP<T>
{
    bool operator==(const EqualityOperators& rhs) const
    {
        const auto rhs_ = this->like_underlying(rhs);
        const auto lhs_ = this->underlying();
        return !(lhs_ < rhs_ || rhs_ < lhs_);
    }

    bool operator!=(const EqualityOperators& rhs) const
    {
        const auto rhs_ = this->like_underlying(rhs);
        const auto lhs_ = this->underlying();
        return !(lhs_ == rhs_);
    }
};

struct Integer : public EqualityOperators<Integer>
{
    int m_value;
    Integer(const int value) : m_value{value} {}

    bool operator<(const Integer& rhs) const { return m_value < rhs.m_value; }
};

Integer getInteger()
{
    static int cur_value = 0;
    return Integer{++cur_value};
};

int main()
{
    auto a = getInteger();
    auto b = getInteger();
    printf("%d \n", b != a);
    printf("%d \n", b == a);
    printf("%d \n", a == a);
    return 1;
}