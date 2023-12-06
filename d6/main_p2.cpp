#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

uint64_t to_num(std::string &line){
  std::vector<int> rs;
  line = line.substr(line.find(':') + 1);
  int num = 0;
  for(int i = 0; i < line.size(); i++){
    if(std::isdigit(line[i])){
      num = (num * 10)+ (line[i] - '0');
    }else if(num > 0){
      rs.push_back(num);
      num = 0;
    }
  }
  if(num > 0){
      rs.push_back(num);
      num = 0;
  }
  uint64_t ret = 0;
  for(int i = 0; i < rs.size(); i++){
    int x = rs[i]*100;
    ret*=100;
    ret+=x;
  }
  return ret/100;
}

int main(int argc, char **argv){
  if(argc < 2){
     std::cerr<<"usage: "<<argv[0]<<" <filename>\n";
    return -1; 
  }
  std::ifstream file{argv[1]};
  if(!file){
    std::cerr<<"failed to open file "<<argv[1];
    return -1;
  }
  std::string line;
  std::getline(file, line);
  uint64_t time = to_num(line);
  std::getline(file, line);
  uint64_t distance = to_num(line);
  std::vector<uint64_t> results;
  int rs = 0;
  for(uint64_t i = 0; i < time; i++){
    uint64_t race_time = time - i;
    if(race_time * i > distance){
      rs++;
    }
  }
  std::cout<<rs;
  return 0;
}
