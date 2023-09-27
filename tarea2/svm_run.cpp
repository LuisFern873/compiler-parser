#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>


#include "svm_parser.hh"
#include "svm.hh"

#include <iostream>
#include <fstream>
#include <string>
#include "svm.hh"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.svm>" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];
    std::ifstream input_file(filename);

    if (!input_file) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;
    }

    std::cout << "Reading program from file " << filename << std::endl;
    std::stringstream buffer;
    buffer << input_file.rdbuf();

    std::list<Instruction*> instructions;
    Scanner scanner(buffer.str());
    Parser parser(&scanner);
    SVM* svm = parser.parse();

    if (svm == nullptr) {
        std::cerr << "Error: Parsing failed." << std::endl;
        return 1;
    }

    std::cout << "Program:" << std::endl;
    svm->print();
    std::cout << "----------------" << std::endl;

    std::cout << "Running ...." << std::endl;
    svm->execute();
    std::cout << "Finished" << std::endl;

    svm->print_stack();

    return 0;
}
