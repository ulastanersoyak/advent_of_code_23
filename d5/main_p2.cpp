#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

std::vector<int64_t> map_to_range(const std::vector<int64_t> &map){
	std::vector<int64_t> rs;
	for(int i = 0; i <map.size(); i+=2){
		rs.push_back(map[i]);
		rs.push_back(map[i] + map[i + 1]);
	}
	return rs;
}

std::vector<int64_t> get_map(const std::string &fl){
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
  std::vector<int64_t> seeds = get_map(line.substr(line.find(':') + 2, line.size()));
	std::vector<int64_t> source = map_to_range(seeds);
	std::vector<int64_t> destination;
  std::getline(file,line);
  std::getline(file,line);
  while(std::getline(file, line)){
    if(line == ""){
      continue;
    }
    if(!std::isdigit(line[0])){
      for(int i = 0; i < source.size(); i+=2){
        destination.push_back(source[i]);
        destination.push_back(source[i + 1]);
      }
      source.swap(destination);
      destination.erase(destination.begin(), destination.end());
      continue;
    }
    std::vector<int64_t> line_map = get_map(line); 
    std::array<int64_t, 4> line_range;
    line_range[0] = line_map[0];
    line_range[1] = line_map[0] + line_map[2];
    line_range[2] = line_map[1];
    line_range[3] = line_map[1] + line_map[2];
    for(int i = 0; i < source.size(); i+=2){
      if(source[i] < line_range[2] && source[i + 1] > line_range[3]){
        source.push_back(line_range[3]);
        source.push_back(line_range[4]);
        source.push_back(line_range[4] + 1);
        source.push_back(source[i + 1]);
        source[i + 1] = line_range[2] - 1;
      }
      if(source[i + 1] > line_range[3] && source[i] < line_range[3]){
        source.push_back(source[i]);
        source.push_back(line_range[3]);
        source[i] = line_range[3] + 1;
      }
      if(source[i] < line_range[2] && source[i + 1] > line_range[2]){
        source.push_back(line_range[2]);
        source.push_back(source[i + 1]);
        source[i + 1] = line_range[2] - 1;
      }
    }
    for(int i = 0; i < source.size(); i+=2){
      if(source[i] >= line_range[2] && source[i + 1] <= line_range[3]){
        destination.push_back(source[i] + (line_map[1] - line_map[0]));
        destination.push_back(source[i+ 1] + (line_map[1] - line_map[0]));
        source.erase(source.begin() + i);
        source.erase(source.begin() + i);
      }    
    }
    // std::cout<<'\n';
    // for(int i = 0; i < destination.size();i++){
    //   std::cout<<destination[i]<<' ';
    // }
    // std::cout<<'\n';
  }
  std::cout<<*std::min(source.begin(),source.end());
  return 0;
}
