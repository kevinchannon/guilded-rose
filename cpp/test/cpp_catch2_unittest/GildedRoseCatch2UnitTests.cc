#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"

TEST_CASE("GildedRoseUnitTest", "Foo")
{
    vector<Item> items;
    items.push_back(Item("Foo", 0, 0));
    GildedRose app(items);
    app.updateQuality();
    REQUIRE("Foo" == app.items[0].name);
}

TEST_CASE("update_quality tests") {
  namespace gr = guilded_rose;

  SECTION("reduces the quality of an item by one") {
    REQUIRE(9 == gr::update_quality(gr::Item{10}).quality);
  }
  
}
