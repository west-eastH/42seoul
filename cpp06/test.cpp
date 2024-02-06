// dynamic_cast_8.cpp
// compile with: /GR /EHsc
#include <stdio.h>
#include <iostream>

struct A {
    virtual void test() {
        printf("in A\n");
   }
};

struct B : A {
    virtual void test() {
        printf("in B\n");
    }

    void test2() {
        printf("test2 in B\n");
    }
};

struct C : B {
    virtual void test() {
        printf("in C\n");
    }

    void test2() {
        printf("test2 in C\n");
    }
};

void Globaltest(A& a) {
    try {
        C &c = dynamic_cast<C&>(a);
        printf("in GlobalTest\n");
    }
    catch(std::bad_cast) {
        printf("Can't cast to C\n");
    }
}

int main() {
    A *pa = new C;
    A *pa2 = new B;

	printf("=========================================================\n");
    pa->test();

	printf("=========================================================\n");
    B * pb = dynamic_cast<B *>(pa);
    if (pb)
        pb->test2();

	printf("=========================================================\n");
    C * pc = dynamic_cast<C *>(pa2);
    if (pc)
        pc->test2();

	printf("=========================================================\n");
    C ConStack;
    Globaltest(ConStack);

	printf("=========================================================\n");
   // fails because B knows nothing about C
    B BonStack;
    Globaltest(BonStack);
	printf("=========================================================\n");
}