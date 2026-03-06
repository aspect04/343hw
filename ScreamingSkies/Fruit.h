#ifndef FRUIT_H
#define FRUIT_H

#include <string>

using namespace std;

//  BASE FRUIT CLASS
class Fruit {
public:
    virtual string getName() = 0;
    virtual string getAttackMessage() = 0;
    virtual int getAttackDamage() = 0;
    virtual string takeDamage(int amount) = 0;
    virtual bool isLiving() = 0;
    virtual ~Fruit() = default;
};


//  FRUIT IMPLEMENTATIONS
class Avocado : public Fruit {
    int hp = 60;
public:
    string getName() override { return "Avocado"; }

    string getAttackMessage() override {
        return "The Avocado hurls its massive pit at you like a cannonball!";
    }

    int getAttackDamage() override { return 18; }

    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0)
            return "The Avocado screams 'But I was finally ripe!' and explodes into guacamole!";
        if (hp < 20)
            return "The Avocado wobbles, leaking green ichor. It looks furious.";
        return "The Avocado takes " + to_string(amount) + " damage! (HP: " + to_string(hp) + ")";
    }

    bool isLiving() override { return hp > 0; }
};

class Durian : public Fruit {
    int hp = 100;
public:
    string getName() override { return "Durian"; }

    string getAttackMessage() override {
        return "The Durian launches a barrage of toxic spikes — and the SMELL alone costs you 5 HP!";
    }

    int getAttackDamage() override { return 25; }

    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0)
            return "The Durian collapses, releasing a final odor so foul nearby birds fall from the sky.";
        if (hp < 30)
            return "The Durian shrieks in a frequency only bats can hear. It's terrifying regardless.";
        return "The Durian takes " + to_string(amount) + " damage! (HP: " + to_string(hp) + ")";
    }

    bool isLiving() override { return hp > 0; }
};

class Banana : public Fruit {
    int hp = 30;
public:
    string getName() override { return "Banana"; }

    string getAttackMessage() override {
        return "The Banana drops a peel beneath your feet and cackles maniacally!";
    }

    int getAttackDamage() override { return 10; }

    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0)
            return "The Banana splits dramatically. RIP, you horrifying yellow menace.";
        if (hp < 10)
            return "The Banana is browning fast, growing more unhinged by the second!";
        return "The Banana takes " + to_string(amount) + " damage! (HP: " + to_string(hp) + ")";
    }

    bool isLiving() override { return hp > 0; }
};

class Watermelon : public Fruit {
    int hp = 150;
public:
    string getName() override { return "Watermelon"; }

    string getAttackMessage() override {
        return "The Watermelon BODY SLAMS you with its enormous girth!";
    }

    int getAttackDamage() override { return 30; }

    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0)
            return "The Watermelon shatters into a thousand crimson chunks. The ground is sticky forever now.";
        if (hp < 50)
            return "Cracks spider across the Watermelon's hide. Seeds fly like shrapnel!";
        return "The Watermelon takes " + to_string(amount) + " damage! (HP: " + to_string(hp) + ")";
    }

    bool isLiving() override { return hp > 0; }
};

class Lemon : public Fruit {
    int hp = 40;
public:
    string getName() override { return "Lemon"; }

    string getAttackMessage() override {
        return "The Lemon spits a stream of acid juice directly into your eyes!";
    }

    int getAttackDamage() override { return 15; }

    string takeDamage(int amount) override {
        hp -= amount;
        if (hp <= 0)
            return "The Lemon shrivels with one last sour grimace. When life gives you lemons... you fight them.";
        if (hp < 15)
            return "The Lemon puckers so hard its face caves in. It is somehow MORE aggressive.";
        return "The Lemon takes " + to_string(amount) + " damage! (HP: " + to_string(hp) + ")";
    }

    bool isLiving() override { return hp > 0; }
};
#endif //FRUIT_H
