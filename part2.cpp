#include "header2.h"

std::ofstream logger;

void printHelp() {
    std::cout << "Help for lzw command:\n";
    std::cout << "\nUsage: lzw [option] [filename]\n";
    std::cout << "Available Options:\n";
    std::cout << "e or E: - expand a lzw file and print out the expanded message\n\n";
    std::cout << "c or C: - compress a file and export out to a file called [filename].lzw\n\n";
    std::cout << "h or H: - print this help message\n\n";
}

void processCompression(char* filename) {
    int bits = 9;
    std::ifstream readIn;
    readIn.open(filename, std::ios::binary);
    if(!readIn) {
        std::cout << "Invalid File name or file could not be opened. Please specify a different one and try again.\n";
        return;
    }
    std::streampos begin, end;
    begin = readIn.tellg();
    readIn.seekg(0, std::ios::end);
    end = readIn.tellg();
    std::streampos size = end - begin;
    char* memblock = new char[size];
    readIn.seekg(0, std::ios::beg);
    readIn.read(memblock, size);
    readIn.close();
    std::vector<int> compressed;
    compress(memblock, std::back_inserter(compressed));
    std::string bcode = "";
    for(std::vector<int>::iterator it = compressed.begin() ; it != compressed.end(); ++it) {
        if(*it >= pow(2, bits)) ++bits;
        bcode += int2BinaryString(*it, bits);
    }
    logger << "String to Write " << bcode << '\n';
    std::ofstream writeOut;
    writeOut.open(std::string(filename) + ".lzw", std::ios::binary);
    std::string zeroes = "00000000";
    if(bcode.size() %8 != 0) bcode += zeroes.substr(0, 8-bcode.size()%8);
    int b;
    for(int i = 0; i < bcode.size(); i += 8) {
        b = 1;
        for(int j = 0; j < 8; ++j) {
            b = b<<1;
            if(bcode.at(i + j) == '1') b += 1;
        }
        char c = (char) (b & 255);
        writeOut.write(&c, 1);
    }
    writeOut.close();
}

void processExpansion(char* filename) {
    if(std::string(filename).substr(std::string(filename).length() - 4) != ".lzw") {
        std::cout << "Cannot expand non lzw file. Please run again with lzw file.\n";
        return;
    }

    std::ifstream readIn;
    readIn.open(filename, std::ios::binary);
    if(!readIn) {
        std::cout << "Unable to open file. Please try again with a different one,\n";
        return;
    }

    struct stat filestatus;
    stat(filename, &filestatus);
    long fsize = filestatus.st_size;

    char c2[fsize];
    readIn.read(c2, fsize);
    std::string zeroes = "00000000";
    std::string s = "";
    long count = 0;
    while (count < fsize)
    {
        unsigned char uc = (unsigned char) c2[count];
        std::string p = "";
        for(int j = 0; j < 8 && uc > 0; ++j) {
            if(uc%2==0)
                p="0"+p;
            else
                p="1"+p;
            uc=uc>>1;
        }
        p = zeroes.substr(0, 8-p.size()) + p;
        s += p;
        count++;
    }
    readIn.close();
    // std::cout << "Saved String: " << s << "\n";
    std::vector<int> blocks;
    std::string decomopressed = decompress(s);
    std::cout << "Decompressed String: " << decomopressed << '\n';
}

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cout << "Invalid number of arguments. Please run lzw h to see a list of avaliable options\n";
        return 0;
    }
    logger.open("log.txt", std::ios::out);
    std::ofstream logger;
    switch(argv[1][0]) {
        case 'h': case 'H':
            printHelp();
            break;
        case 'c': case 'C':
            processCompression(argv[2]);
            break;
        case 'e': case 'E':
            processExpansion(argv[2]);
            break;
        default:
            std::cout << "Invalid option. Plese run lzw h for a list of available options\n";
    }
    return 0;
}
