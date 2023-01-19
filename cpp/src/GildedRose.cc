#include "GildedRose.h"

#include <algorithm>

GildedRose::GildedRose(vector<Item> & items) : items(items)
{}
    
void GildedRose::updateQuality() 
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].name != "Aged Brie" && items[i].name != "Backstage passes to a TAFKAL80ETC concert")
        {
            if (items[i].quality > 0)
            {
                if (items[i].name != "Sulfuras, Hand of Ragnaros")
                {
                    items[i].quality = items[i].quality - 1;
                }
            }
        }
        else
        {
            if (items[i].quality < 50)
            {
                items[i].quality = items[i].quality + 1;

                if (items[i].name == "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (items[i].sellIn < 11)
                    {
                        if (items[i].quality < 50)
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }

                    if (items[i].sellIn < 6)
                    {
                        if (items[i].quality < 50)
                        {
                            items[i].quality = items[i].quality + 1;
                        }
                    }
                }
            }
        }

        if (items[i].name != "Sulfuras, Hand of Ragnaros")
        {
            items[i].sellIn = items[i].sellIn - 1;
        }

        if (items[i].sellIn < 0)
        {
            if (items[i].name != "Aged Brie")
            {
                if (items[i].name != "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (items[i].quality > 0)
                    {
                        if (items[i].name != "Sulfuras, Hand of Ragnaros")
                        {
                            items[i].quality = items[i].quality - 1;
                        }
                    }
                }
                else
                {
                    items[i].quality = items[i].quality - items[i].quality;
                }
            }
            else
            {
                if (items[i].quality < 50)
                {
                    items[i].quality = items[i].quality + 1;
                }
            }
        }
    }
}

namespace guilded_rose {

  Items update_quality(Items items)
  {
    std::ranges::transform(items, items.begin(), [](auto&& item) {return update_quality(std::move(item)); });
    return items;
  }

  Item update_quality(Item item)
  {
    item.quality -= item.sell_in < 0 ? 2 : 1;
    if (item.quality < 0) {
      item.quality = 0;
    }

    return item;
  }

}
