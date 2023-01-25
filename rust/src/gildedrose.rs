use std::fmt::{self, Display};
pub struct Item {
    pub name: String,
    pub sell_in: i32,
    pub quality: i32,
}

impl Item {
    pub fn new(name: impl Into<String>, sell_in: i32, quality: i32) -> Item {
        Item {
            name: name.into(),
            sell_in,
            quality,
        }
    }
}

impl Display for Item {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}, {}, {}", self.name, self.sell_in, self.quality)
    }
}

pub struct GildedRose {
    pub items: Vec<Item>,
}

impl GildedRose {
    pub fn new(items: Vec<Item>) -> GildedRose {
        GildedRose { items }
    }

    pub fn update_quality(&mut self) {
        for item in &mut self.items {
            if item.name != "Aged Brie" && item.name != "Backstage passes to a TAFKAL80ETC concert"
            {
                if item.quality > 0 {
                    if item.name != "Sulfuras, Hand of Ragnaros" {
                        item.quality = item.quality - 1;
                    }
                }
            } else {
                if item.quality < 50 {
                    item.quality = item.quality + 1;

                    if item.name == "Backstage passes to a TAFKAL80ETC concert" {
                        if item.sell_in < 11 {
                            if item.quality < 50 {
                                item.quality = item.quality + 1;
                            }
                        }

                        if item.sell_in < 6 {
                            if item.quality < 50 {
                                item.quality = item.quality + 1;
                            }
                        }
                    }
                }
            }

            if item.name != "Sulfuras, Hand of Ragnaros" {
                item.sell_in = item.sell_in - 1;
            }

            if item.sell_in < 0 {
                if item.name != "Aged Brie" {
                    if item.name != "Backstage passes to a TAFKAL80ETC concert" {
                        if item.quality > 0 {
                            if item.name != "Sulfuras, Hand of Ragnaros" {
                                item.quality = item.quality - 1;
                            }
                        }
                    } else {
                        item.quality = item.quality - item.quality;
                    }
                } else {
                    if item.quality < 50 {
                        item.quality = item.quality + 1;
                    }
                }
            }
        }
    }
}

fn push_quality_into_range(quality: i32) -> i32 {
    quality.min(50).max(0)
}

fn calculate_new_quality(item: &Item) -> i32 {
    if item.name == "Aged Brie" {
        item.quality + 1
    } else {
        if item.sell_in > 0 { item.quality - 1 } else { item.quality - 2 }
    }
}

fn update_item_quality(item: &Item) -> Item {
    Item::new(
        item.name.clone(),
        item.sell_in - 1,
        push_quality_into_range(calculate_new_quality(&item))
    )
}

pub fn update_quality(items: Vec<Item>) -> Vec<Item> {
    return items.iter().map(|x| { update_item_quality(&x)}).collect();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn update_quality_reduces_quality_of_all_regular_item_by_one(){
        let items = update_quality(vec![Item::new("foo", 10, 10), Item::new("bar", 10, 10)]);

        assert_eq!(9, items[0].quality);
        assert_eq!(9, items[1].quality);
    }

    #[test]
    fn update_item_quality_reduces_quality_of_regular_item_by_one(){
        let item = Item::new("foo", 10, 10);
        assert_eq!(9, update_item_quality(&item).quality);
    }

    #[test]
    fn update_item_quality_does_not_reduce_quality_below_zero() {
        let item = Item::new("foo", 10, 0);
        assert_eq!(0, update_item_quality(&item).quality);
    }

    #[test]
    fn update_item_quality_reduces_sell_in_by_one() {
        let item = Item::new("foo", 10, 0);
        assert_eq!(9, update_item_quality(&item).sell_in);
    }

    #[test]
    fn update_item_quality_reduces_quality_of_regular_items_twice_as_fast_after_expiry() {
        let initial_quality = 10;
        let mut item = Item::new("foo", 1, initial_quality);

        item = update_item_quality(&item);
        let first_quality = item.quality;

        let normal_quality_reduction = initial_quality - first_quality;assert_eq!(1, normal_quality_reduction);

        assert_eq!(2 * normal_quality_reduction, first_quality - update_item_quality(&item).quality);
    }

    #[test]
    fn aged_brie_increases_in_quality() {
        let item = Item::new("Aged Brie", 10, 10);
        assert_eq!(11, update_item_quality(&item).quality);
    }

    #[test]
    fn update_item_quality_doesnt_increase_quality_above_50() {
        let item = Item::new("Aged Brie", 10, 50);
        assert_eq!(50, update_item_quality(&item).quality);
    }

    #[test]
    pub fn foo() {
        let items = vec![Item::new("foo", 0, 0)];
        let mut rose = GildedRose::new(items);
        rose.update_quality();

        assert_eq!("foo", rose.items[0].name);
    }
}
