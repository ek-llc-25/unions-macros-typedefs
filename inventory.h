#ifndef UNIONSJOV_INVENTORY_H
#define UNIONSJOV_INVENTORY_H

#include <stdio.h>
#include <string.h>

struct weapon_t {
    int damage;
    int durability;
};

struct armor_t {
    int protection;
    int durability;
};

enum effect_type {
    LIFE,
    MANA,
};

struct consumable_t {
    enum effect_type effect_type;
    int amount;
    int uses_left;
};

enum item_type_t {
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_CONSUMABLE,
};

#define ITEM_NAME_MAXLEN 50

// Det her er en tagged union:
// Hvorfor skal der stå 'struct' på følgende linje, og ikke 'union'?
// Fordi en tagged union er en struct der gemmer på et tag ('type' nedenfor) og en union ('data' nedenfor)
struct inv_item_t {
    enum item_type_t type;
    char name[ITEM_NAME_MAXLEN + 1];
    union {
        struct weapon_t as_weapon;
        struct armor_t as_armor;
        struct consumable_t as_consumable;
    } data;
};

struct inv_item_t create_weapon(const char *name, int dmg, int dur);
struct inv_item_t create_armor(const char *name, int ac, int dur);
struct inv_item_t create_life_potion(int amount, int uses_left);
struct armor_t *get_armor_stats(struct inv_item_t *item);
void print_item_info(struct inv_item_t item);

#endif //UNIONSJOV_INVENTORY_H