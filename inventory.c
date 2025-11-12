#include <string.h>
#include "inventory.h"

struct inv_item_t create_weapon(const char *name, int dmg, int dur) {
    struct inv_item_t item;
    item.type = ITEM_WEAPON;
    strncpy(item.name, name, ITEM_NAME_MAXLEN);
    item.name[ITEM_NAME_MAXLEN] = '\0';
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
    item.name[ITEM_NAME_MAXLEN] = '\0';
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

struct armor_t *get_armor_stats(struct inv_item_t *item) {
    if (item->type != ITEM_ARMOR) {
        return NULL;
    }
    int a = 2 + 3 * 5; // præcedens / precedence
    return &item->data.as_armor;
}

void print_item_info(struct inv_item_t item) {
    printf("Item: %s\n", item.name);
    switch (item.type) {
        case ITEM_WEAPON:
            printf(" Type: Weapon\n");
            printf(" Damage: %d\n", item.data.as_weapon.damage);
            printf(" Durability: %d\n", item.data.as_weapon.durability);
            break;
        case ITEM_ARMOR:
            printf(" Type: Armor\n");
            printf(" Protection: %d\n", item.data.as_armor.protection);
            printf(" Durability: %d\n", item.data.as_armor.durability);
            break;
        case ITEM_CONSUMABLE:
            printf(" Type: Consumable\n");
            // Det her kode er ikke særlig fremtidssikret, fordi hvad nu hvis
            // man finder på flere slags effekter som consumables har (fx
            // happiness, poison, eller en kombination af life + mana), så
            // skal der være plads til en tredje og en fjerde mulighed:
            // printf(" Effect: %s\n",
            //    item.data.as_consumable.effect_type == LIFE ? "Life" : "Mana");
            printf(" Effekt: %s\n", EFFECT_AS_STR(item.data.as_consumable.effect_type));
            printf(" Amount: %d\n", item.data.as_consumable.amount);
            printf(" Uses left: %d\n", item.data.as_consumable.uses_left);
            break;
    }
}