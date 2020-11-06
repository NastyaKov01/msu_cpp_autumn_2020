#include "bigint.h"
#include <cassert>

void Creation()
{
    std::cout << "Test 1. Creation" << std::endl;
    BigInt d1("000001234567890123456789012345678"), d2("-657849374500084594592370008454584599");
    BigInt d3(346574588), d4(-82392949829);
    std::cout << "Integer from string '00000001234567890123456789012345678': " << d1 << std::endl;
    std::cout << "Integer from string '-657849374500084594592370008454584599': " << d2 << std::endl;
    std::cout << "Integer from 346574588: " << d3 << std::endl;
    std::cout << "Integer from -82392949829: " << d4 << std::endl;
    BigInt d5(d1);
    BigInt d6;
    d6 = d2;
    std::cout << "Integer created using the copy constructor: " << d5 << std::endl;
    std::cout << "Integer created using the copy operator: " << d6 << std::endl;
    BigInt d7 = std::move(d3);
    BigInt d8;
    d8 = std::move(d4);
    std::cout << "Integer created using the move constructor: " << d7 << std::endl;
    std::cout << "Integer created using the move operator: " << d8 << std::endl;
    std::cout << "Test 1 passed successfully\n" << std::endl;
}

void Comparison()
{
    std::cout << "Test 2. Comparison" << std::endl;
    BigInt d1("86893493403498560459348"), d2("76976876985686968956856"), d3("-58596985695605690");
    BigInt d4("-584594590594588786899"), d5("86893493403498560459348"), d6("-58596985695605690");
    assert(d1 > d2);
    assert(d3 < d2);
    assert(d4 <= d3);
    assert(d1 >= d4);
    assert(d1 == d5);
    assert(d4 != d2);
    assert(d6 == d3);
    std::cout << "Test 2 passed successfully\n" << std::endl;
}

void Arithmetic()
{
    std::cout << "Test 3. Arithmetic operations" << std::endl;
    BigInt d1("3474585859900580"), d2("9340959550348400"), d3("-23563475858757");
    BigInt d4("-192484989459"), d5("10000000000"), d6("9999999999"), d7(47458), d8(123);
    BigInt d9("12334556678990760760");
    assert((d1 + d2) == BigInt("12815545410248980"));
    assert((d2 + d3) == BigInt("9317396074489643"));
    assert((d1 + d4) == BigInt("3474393374911121"));
    assert((d3 + d1) == BigInt("3451022384041823"));
    assert((d3 + d4) == BigInt("-23755960848216"));
    assert((d2 - d1) == BigInt("5866373690447820"));
    assert((d1 - d2) == BigInt("-5866373690447820"));
    assert((d3 - d1) == BigInt("-3498149335759337"));
    assert((d3 - d4) == BigInt("-23370990869298"));
    assert((d4 - d3) == BigInt("23370990869298"));
    assert((d7 - d8) == BigInt(47335));
    assert((d8 - d7) == BigInt(-47335));
    assert((d2 - d7) == BigInt("9340959550300942"));
    assert((d5 - d6) == BigInt(1));
    assert((d6 - d5) == BigInt(-1));
    assert((d2 * d9) == BigInt("115216595009932390629847639048784000"));
    assert((d6 * d4) == BigInt("-1924849894397515010541"));
    assert((d3 * d7) == BigInt("-1118275437304889706"));
    assert((BigInt("3474585859900580") * d8) == BigInt("427374060767771340"));
    assert((BigInt("-12345678901234567") * BigInt("12345678910")) == BigInt("-152415787640603566774881970"));
    assert((BigInt("-282874879894958") * BigInt("-19212399899")) == BigInt("5434705313923528209809242"));
    assert((BigInt("48348348999902384480") * BigInt("-1929394934489")) == BigInt("-93283059651317969771184490330720"));
    std::cout << "Test 3 passed successfully\n" << std::endl;
}

int main()
{
    Creation();
    Comparison();
    Arithmetic();
}
