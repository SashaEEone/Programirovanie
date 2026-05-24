#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "lab7.c"

static void add_test(void **state) { 
    assert_int_equal(add(100,150), 250);
}
static void noadd_test(void **state) { 
    assert_int_equal(add(100,150), 200);
}
static void subtract_test(void **state) { 
    assert_int_equal(subtract(15,5), 10);
}
static void nosubtract_test(void **state) { 
    assert_int_not_equal(subtract(15,5), 5);
}
static void multiply_test(void **state) { 
    assert_int_equal(multiply(3,3), 9);
}
static void nomultiply_test(void **state) { 
    assert_int_equal(multiply(3,3), 6);
}
static void divide_test(void **state) { 
    assert_int_equal(divide(16,4), 4);
}
static void nodivide_test(void **state) { 
    assert_int_not_equal(divide(16,4), 5);
}

int main(void) { 
    const struct CMUnitTest tests[] = { 
        cmocka_unit_test(add_test),
        cmocka_unit_test(noadd_test),
        cmocka_unit_test(subtract_test),
        cmocka_unit_test(nosubtract_test),
        cmocka_unit_test(multiply_test),
        cmocka_unit_test(nomultiply_test),
        cmocka_unit_test(divide_test),
        cmocka_unit_test(nodivide_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);  
}
