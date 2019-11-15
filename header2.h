#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cmath>
#include <sys/stat.h>

template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result) {
  // Build the dictionary.
  int dictSize = 256;
  int bits = 9;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < dictSize; i++)
    dictionary[std::string(1, i)] = i;
 
  std::string w;
  for (std::string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    std::string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary. Assuming the size is 4096!!!
      if (dictionary.size()<pow(2, bits))
         dictionary[wc] = dictSize++;
      else {
        if(bits < 16) {
          bits++;
          dictionary[wc] = dictSize++;
        }
      }
      w = std::string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}

int binaryString2Int(std::string p);

// template <typename Iterator>
std::string decompress(std::string bin) {
  // Build the dictionary.
  int dictSize = 256;
  int bits = 9;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);
  
  std::string item = bin.substr(0, bits);
  std::string w(1, binaryString2Int(item));
  std::string result = w;

  std::string entry;
  for (int i = bits; i < bin.size(); i+= bits) {
    std::string toConvert = bin.substr(i, bits);
    int k = binaryString2Int(toConvert);
    std::cout << toConvert << ": " << k << '\n';
    std::cout << "Dict Size: " << dictSize << "\nMax Size: " << pow(2, bits) - 1 << '\n';
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";
 
    result += entry;
 
    // Add w+entry[0] to the dictionary.
    int max = pow(2, bits) - 1;
    if (dictionary.size()<=max) {
      dictionary[dictSize++] = w + entry[0];
    } else {
      if(bits < 16) {
        bits++;
        dictionary[dictSize++] = w + entry[0];
      }
    }
    w = entry;
  }
  return result;
}

std::string int2BinaryString(int c, int cl) {
      std::string p = ""; //a binary code string with code length = cl
      int code = c;
      while (c>0) {         
		   if (c%2==0)
            p="0"+p;
         else
            p="1"+p;
         c=c>>1;   
      }
      int zeros = cl-p.size();
      if (zeros<0) {
         std::cout << "\nWarning: Overflow. code " << code <<" is too big to be coded by " << cl <<" bits!\n";
         p = p.substr(p.size()-cl);
      }
      else {
         for (int i=0; i<zeros; i++)  //pad 0s to left of the binary code if needed
            p = "0" + p;
      }
      return p;
}

int binaryString2Int(std::string p) {
   int code = 0;
   if (p.size()>0) {
      if (p.at(0)=='1') 
         code = 1;
      p = p.substr(1);
      while (p.size()>0) { 
         code = code << 1; 
		   if (p.at(0)=='1')
            code++;
         p = p.substr(1);
      }
   }
   return code;
}