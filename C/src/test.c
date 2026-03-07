struct A {};

typedef struct B {} C;

typedef struct D {} D;

int main()
{
    // A a; // does not compile
    struct A a;
    struct B b;
    // struct C c; // does not compile
    C c;
    struct D d1;
    D d2;
    return 0;
}
