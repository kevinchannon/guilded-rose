#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Catch.hpp"
#include "GildedRose.h"

#include <iostream>
#include <ranges>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const Item& item) {
  os << "{" << item.name << ", " << item.sellIn << ", " << item.quality << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const guilded_rose::Items& items) {
  os << "[ ";

  if (not items.empty()) {
    for (const auto& item : items | std::views::take(items.size() - 1)) {
      os << item << ", ";
    }

    os << items.back() << " ";
  }

  os << "]";

  return os;
}

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
      REQUIRE(9 == gr::update_quality(Item{ "foo", 10, 10 }).quality);
    }

    SECTION("quality is not reduced if it's already zero") {
      REQUIRE(0 == gr::update_quality(Item{ "foo", 10, 0 }).quality);
    }

    SECTION("quality reduces by 2 if sell_in has passed") {
      REQUIRE(8 == gr::update_quality(Item{ "foo", -1, 10 }).quality);
    }

    SECTION("Aged Brie increases in quality") {
      REQUIRE(11 == gr::update_quality(Item{ "Aged Brie", 0, 10 }).quality);
    }
  }

  SECTION("multiple items") {
    SECTION("update the quality of multiple items") {
      SECTION("returns the same number of items as the input") {
        REQUIRE(3 == gr::update_quality({ {"foo", 0, 10}, {"foo", 0, 9}, {"foo", 0, 9} }).size());
      }

      SECTION("updates each item") {
        REQUIRE(gr::Items{ {"foo", -1, 9}, {"foo", -1, 8}, {"foo", -1, 7} } == gr::update_quality({ {"foo", 0, 10}, {"foo", 0, 9}, {"foo", 0, 8} }));
      }
    }
  }
}
