#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<int> to_num(std::string &line){
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
  std::string line;
  std::getline(file, line);
  std::vector<int> time = to_num(line);
  std::getline(file, line);
  std::vector<int> distance = to_num(line);
  std::vector<uint64_t> results;
  for(int i = 0; i< time.size(); i++){
    int score_breaks = 0;
    for(int j = 0; j< time[i]; j++){
      int mov_time = time[i] - j;
      if(mov_time * j > distance[i]){
        score_breaks++;
      }
    }
    results.push_back(score_breaks);
  }
  int rs = 1;
  for(int i = 0; i < results.size(); i++){
    rs*=results[i];
  }
  std::cout<<rs;
  return 0;
}
