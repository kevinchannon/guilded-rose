#include <string>
#include <vector>
#include <compare>

using namespace std;

class Item
{
public:
    string name;
    int sellIn;
    int quality;
    Item(string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}
};

class GildedRose
{
public:
    vector<Item> & items;
    GildedRose(vector<Item> & items);
    
    void updateQuality();
};

constexpr bool operator==(const Item& left, const Item& right) noexcept {
  if (left.name != right.name) {
    return false;
  }

  if (left.quality != right.quality) {
    return false;
  }

  if (left.sellIn != right.sellIn) {
    return false;
  }

  return true;
}

namespace guilded_rose {
  using Items = std::vector<Item>;

  Items update_quality(Items items);
  Item update_quality(Item item);
}
