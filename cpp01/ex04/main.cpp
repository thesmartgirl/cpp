#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(std::string content, std::string s1, std::string s2) {
    size_t pos = 0;
    while ((pos = content.find(s1, pos)) != std::string::npos) {
        content.erase(pos, s1.length());
        content.insert(pos, s2);
        pos += s2.length();
    }
    return content;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <file_name> <s1> <s2>\n";
        return 1;
    }

    std::string file_name = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    std::ifstream input_file(file_name.c_str());
    if(!input_file.is_open()) {
        std::cerr << "Error: Could not open file " << file_name << "\n";
        return 1;
    }
    
    std::string content;
    std::string line;

    while (std::getline(input_file, line)) {
        content += line;
        if (!input_file.eof())
            content += "\n";
    }
    input_file.close();

    std::string replaced = replaceAll(content, s1, s2);
    
    std::ofstream output_file("Makefile.replace");
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open output file\n";
        return 1;
    }
    output_file << replaced;
    output_file.close();
        
    
    return 0;
}