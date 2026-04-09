#include <iostream>
#include "Array.hpp"

int main()
{
    //constructor with no parameter
    Array<int> arr1;
    std::cout << "array was created with size = " << arr1.size() << std::endl;

    //constructor with size n
    Array<char> arr2(2);
    std::cout << "array was created with size = " << arr2.size() << std::endl;
    std::cout << "arr[0] = " << arr2[0] << std::endl;
    std::cout << "arr[1] = " << arr2[1] << std::endl;
    
    //opertaor [] overload
    arr2[0] = 'a';
    arr2[1] = 'z';
    std::cout << "arr[0] = " << arr2[0] << std::endl;
    std::cout << "arr[1] = " << arr2[1] << std::endl;

    //copy constructor
    Array<char> arr3(arr2);
    std::cout << "arr2[0] = " << arr2[0] << std::endl;
    std::cout << "arr2[1] = " << arr2[1] << std::endl;
    std::cout << "arr3[0] = " << arr3[0] << std::endl;
    std::cout << "arr3[1] = " << arr3[1] << std::endl;
    arr3[0] = 'b';
    arr3[1] = 'c';    
    std::cout << "arr2[0] = " << arr2[0] << std::endl;
    std::cout << "arr2[1] = " << arr2[1] << std::endl;
    std::cout << "arr3[0] = " << arr3[0] << std::endl;
    std::cout << "arr3[1] = " << arr3[1] << std::endl;

    // //assignment constructor
    std::cout << "Assignment Constructor tests\n";
    Array<int> arr4(2), arr5(2);
    arr4 = arr5;
    std::cout << "arr4[0] = " << arr4[0] << std::endl;
    std::cout << "arr4[1] = " << arr4[1] << std::endl;
    std::cout << "arr5[0] = " << arr5[0] << std::endl;
    std::cout << "arr5[1] = " << arr5[1] << std::endl;
    arr4[0] = -7;
    arr4[1] = 99;
    std::cout << "arr4[0] = " << arr4[0] << std::endl;
    std::cout << "arr4[1] = " << arr4[1] << std::endl;
    std::cout << "arr5[0] = " << arr5[0] << std::endl;
    std::cout << "arr5[1] = " << arr5[1] << std::endl;

    // out of bound
    std::cout << "out of bound tests\n";
    try{
        std::cout << "arr4[10] = " << arr1[10] << std::endl;
    }
    catch (std::out_of_range &e)
    {
        std::cout << "catched an error: " << e.what() << std::endl;
    }

    return 0;
}