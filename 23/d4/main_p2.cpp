#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int64_t> get_map(std::string fl){
  std::vector<int64_t> rs;
  int64_t num = 0;
  for(int i = 0; i < fl.size(); i++){
    if(fl[i] == ' ' || fl[i] == '\n'){
      rs.push_back(num);
      num = 0;
    }else if(std::isdigit(fl[i])){
      num = (num * 10) + fl[i] - '0'; 
    }
  }
  if(num != 0){
    rs.push_back(num);
  }
  return rs;
}

std::vector<int64_t> map_to_range(std::vector<int64_t> source){
  std::vector<int64_t> rs;
  for(int i = 0; i < source.size(); i++){
    for(int j = 0; j < source[i + 1]; j++){
      rs.push_back(source[i] + j);
    }
  }
  return rs;
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
  int rs = 0;
  std::string line;
  std::getline(file, line);
  std::vector<int64_t> source = get_map(line.substr(line.find(':') + 2, line.size()));
  source = map_to_range(source);
  std::vector<int64_t> destination;
  std::getline(file,line);
  std::getline(file,line);
  while(std::getline(file, line)){
    if(line == ""){
      continue;
    }
    if(!std::isdigit(line[0])){
      for(int64_t &val: source){
        if(val != -1){
          destination.push_back(val);
          val = -1;
        }
      }
      source.swap(destination);
      destination.erase(destination.begin(), destination.end());
      continue;
    }
    std::vector<int64_t> map = get_map(line);
    for(int64_t &val: source){
      if(val >= map[1] && val <= map[1] + map[2]){
        destination.push_back(map[0]+ (val - map[1]));
        val = -1;
      }
    }
  }
  for(int64_t &val: source){
    if(val != -1){
      destination.push_back(val);
      val = -1;
    }
  }
  std::cout<<*std::min_element(destination.begin(), destination.end());
  return 0;
}
