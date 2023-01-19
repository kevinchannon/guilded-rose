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

  SECTION("single item") {
    SECTION("reduces the quality of a regular item by one") {
      REQUIRE(9 == gr::update_quality(gr::Item{ 10 }).quality);
    }

    SECTION("quality is not reduced if it's already zero") {
      REQUIRE(0 == gr::update_quality(gr::Item{ 0 }).quality);
    }

    SECTION("quality reduces by 2 if sell_in has passed") {
      REQUIRE(8 == gr::update_quality(gr::Item{ 10, -1 }).quality);
    }
  }

  SECTION("multiple items") {
    SECTION("update the quality of multiple items") {
      SECTION("returns the same number of items as the input") {
        REQUIRE(3 == gr::update_quality({ {10}, {9}, {8} }).size());
      }

      SECTION("updates each item") {
        REQUIRE(gr::Items{ {9, -1}, {8, -1}, {7, -1} } == gr::update_quality({ {10}, {9}, {8} }));
      }
    }
  }
}
