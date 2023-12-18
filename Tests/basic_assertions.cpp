#include <criterion/criterion.h>

TestSuite(basic_assertions, .disabled = false);

Test(basic_assertions, ok)
{
    cr_expect(true);
}
