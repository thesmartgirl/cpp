#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
    Data* data1 = new Data();
    std::cout << "Original pointer: " << data1 << std::endl;
    std::cout << "Serialized pointer: " << Serializer::serialize(data1) << std::endl;
    std::cout << "Deserialized pointer: " << Serializer::deserialize(Serializer::serialize(data1)) << std::endl;
    std::cout << "Note that Deserialized pointer == Original pointer" << std::endl;
    delete data1;
    return 0;
}