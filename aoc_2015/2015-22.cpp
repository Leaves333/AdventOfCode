#include <bits\stdc++.h>
using namespace std;

const bool fileIO = true;
void setIO() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int minMana = INT_MAX;

void game(int hp, int mana, int bossHP, int damage, int shield, int poison, int recharge, int spent) {

    //boss turn
    if (poison > 0) {
        poison--;
        bossHP -= 3;
    }

    if (shield > 0) {
        shield--;
        hp -= max(damage - 7, 1);
    }
    else {
        hp -= damage;
    }

    if (recharge > 0) {
        recharge--;
        mana += 101;
    }

    if (bossHP <= 0) { minMana = min(minMana, spent); return; }

    hp -= 1;
    if (mana < 53 || hp <= 0 || spent > minMana) { return; }

    //player turn: try all the attacks
    if (poison > 0) {
        bossHP -= 3;
    }

    if (recharge > 0) {
        mana += 101;
    }

    shield--;
    poison--;
    recharge--;

    if (mana >= 229 && recharge <= 0) {
        game(hp, mana - 229, bossHP, damage, shield, poison, 5, spent + 229);
    }

    if (mana >= 173 && poison <= 0) {
        game(hp, mana - 173, bossHP, damage, shield, 6, recharge, spent + 173);
    }

    if (mana >= 113 && shield <= 0) {
        game(hp, mana - 113, bossHP, damage, 6, poison, recharge, spent + 113);
    }

    if (mana >= 73) {
        game(hp + 2, mana - 73, bossHP - 2, damage, shield, poison, recharge, spent + 73);
    }

    if (mana >= 53) {
        game(hp, mana - 53, bossHP - 4, damage, shield, poison, recharge, spent + 53);
    }

}

int main() {

    if (fileIO) { setIO(); }

    int HP = 51;
    int damage = 9;
    int playerHP = 49;

    game(playerHP, 500 - 53, HP - 4, damage, 0, 0, 0, 53);
    game(playerHP + 2, 500 - 73, HP - 2, damage, 0, 0, 0, 73);
    game(playerHP, 500 - 113, HP, damage, 6, 0, 0, 113);
    game(playerHP, 500 - 173, HP, damage, 0, 6, 0, 173);
    game(playerHP, 500 - 229, HP, damage, 0, 0, 5, 229);

    cout << minMana;

}