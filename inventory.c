#include <string.h>
#include "inventory.h"

struct inv_item_t create_weapon(const char *name, int dmg, int dur) {
    struct inv_item_t item;
    item.type = ITEM_WEAPON;
    strcpy(item.name, name);
    item.data.as_weapon.damage = dmg;
    item.data.as_weapon.durability = dur;
    return item;
}

struct inv_item_t create_armor(const char *name, int ac, int dur) {
    // Heap-allokeret item (malloc() returnerer en pointer)
    // struct inv_item_t *item = malloc(sizeof(struct inv_item_t));
    struct inv_item_t item;

    // Hvis den var heap-allokeret, skulle man skrive en af følgende:
    // (*item).type = ITEM_ARMOR;
    // item->type = ITEM_ARMOR;
    item.type = ITEM_ARMOR;

    // For at undgå at programmet crasher ved for lange navne, bruger vi
    // strncpy() i stedet for strcpy(), fordi den stopper ved for lange navne.
    // strcpy(item.name, name);
    strncpy(item.name, name, ITEM_NAME_MAXLEN);
    item.data.as_armor.protection = ac;
    item.data.as_armor.durability = dur;

    // Når jeg returnerer item, bliver der kopieret 62 bytes fra denne funktion
    // til funktionen der kalder. Det er en ret stor mængde af bytes!
    return item;
}

struct inv_item_t create_life_potion(int amount, int uses_left) {
    struct inv_item_t item;

    item.type = ITEM_CONSUMABLE;
    strcpy(item.name, "Life Potion");
    item.data.as_consumable.effect_type = LIFE;
    item.data.as_consumable.amount = amount;
    item.data.as_consumable.uses_left = uses_left;

    return item;
}