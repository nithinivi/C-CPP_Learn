#include <cstdio>

template <typename T>
class Amount
{
   public:
    double getValue() const { return static_cast<T const&>(*this).getValue(); }
};

class Constant42 : public Amount<Constant42>
{
   public:
    double getValue() const { return 42; }
};

class Variable : public Amount<Variable>
{
   public:
    explicit Variable(int value) : value_(value) {}
    double getValue() const { return value_; }

   private:
    int value_;
};

template <typename T>
void print(Amount<T> const& amount)
{
    printf("%lf \n", amount.getValue());
}

int main()
{
    Constant42 c42;
    print(c42);
    Variable v(43);
    print(v);
}