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

namespace guilded_rose {
  struct Item {
    int quality;

    constexpr auto operator<=>(const Item&) const noexcept = default;
   };

  using Items = std::vector<Item>;

  Items update_quality(Items items);
  Item update_quality(Item item);
}
