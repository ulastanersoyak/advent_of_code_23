#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <algorithm>
#include <math.h>

int get_intersection_count(std::vector<int> arr1, std::vector<int> arr2){ 
  std::vector<int> intersection;
  std::unordered_set<int> set(arr1.begin(), arr1.end());
  for(const auto &num : arr2){
    if(set.count(num) > 0){
      intersection.push_back(num);
    }
  }
  return intersection.size();
}
std::vector<int> convert_to_vector(std::string nums){
  std::vector<int> rs;
  for(int i = 0; i < nums.size(); i++){
    int num = 0;
    while(std::isdigit(nums[i])){
      num = (num * 10) + nums[i] - '0';
      i++;
    }
    if(num > 0){
      rs.push_back(num);
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
  int card_idx = 0;
  std::array<int, 204> cards;
  std::fill(cards.begin(), cards.end(), 1);
  while(std::getline(file, line)){
    std::string card = line.substr(line.find(':') + 1, line.size());
    std::vector<int> winning_nums = convert_to_vector(card.substr(0, card.find('|')));
    std::vector<int> player_nums = convert_to_vector(card.substr(card.find('|') + 1, card.size()));
    int intersect_count = get_intersection_count(winning_nums, player_nums);
    for(int i = 1; i  <= intersect_count; i++){
      cards[card_idx + i] += cards[card_idx];
    }
    card_idx+=1;
  }
  for(auto &x: cards){
    rs+=x;
  }
  std::cout<<rs;
  return 0;
}
