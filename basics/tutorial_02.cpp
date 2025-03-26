/**
 * @file tutorial_01.cpp
 * @author Daniel Calderón (https://github.com/dantros)
 * @brief Tutorial C++ code showing how to use some containers and algorithms.
 * @version 1.0
 * @date 2025-03-26
 * @license This code is released under the MIT public licence.
 * 
 */

#include <iostream>
#include <format>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>

/* This is the C++ type protected enum, meaning, it is not an int,
 * you need to cast it when you want that interpretation (using static_cast<>(.)).
 * You can specify the underlying primitive type, but it is optional.
 * If you do, you can also assign values for each type... you can also just
 * specify the first one and the rest will go increasing that integer number.
 */
enum class PowerType : unsigned int
{
    Earth = 0, Water, Air, Fire
};

std::string str(PowerType powerType)
{
    switch (powerType)
    {
        case PowerType::Earth: return "Earth";
        case PowerType::Water: return "Water";
        case PowerType::Air: return "Air";
        case PowerType::Fire: return "Fire";
        default: throw;
    }
}

constexpr float HealthPointEpsilon = 1e-3f;

struct Creature
{
    Creature(const std::string& name, float healthPoints, float attack, PowerType powerType) :
        mName(name),
        mCurrentHealthPoints(healthPoints),
        mMaxHealthPoints(healthPoints),
        mAttack(attack),
        mPowerType(powerType)
    {}

    void attackTo(Creature& other) const
    {
        other.mCurrentHealthPoints -= mAttack;
        if (other.mCurrentHealthPoints <= HealthPointEpsilon)
            other.mCurrentHealthPoints = 0.0f;
    }

    bool isAlive() const
    {
        return mCurrentHealthPoints > HealthPointEpsilon;
    }

    std::string mName;
    float mCurrentHealthPoints;
    float mMaxHealthPoints;
    float mAttack;
    PowerType mPowerType;
};

struct CreatureSorterByAttack
{
    bool operator()(const Creature& lhs, const Creature& rhs)
    {
        return lhs.mAttack < rhs.mAttack;
    }
};

struct CreatureSorterByHealthPointsPercentage
{
    bool operator()(const Creature& lhs, const Creature& rhs) const
    {
        auto healthPointPercentage = [](const Creature& creature)
        {
            return creature.mCurrentHealthPoints / creature.mMaxHealthPoints;
        };
        return healthPointPercentage(lhs) < healthPointPercentage(rhs);
    }
};

struct CreatureTypeComparer
{
    bool operator()(const Creature& lhs, const Creature& rhs) const
    {
        return static_cast<unsigned int>(lhs.mPowerType) < static_cast<unsigned int>(rhs.mPowerType);
    }
};

template <typename Container>
void printCollection(
    const Container& container,
    std::function<std::string(const Creature&)> toStringFunction = [](const Creature&){ return ""; }
)
{
    for (const Creature& creature : container)
        std::cout << creature.mName << toStringFunction(creature) << ", ";
    std::cout << std::endl;
}

int main()
{
    std::vector<Creature> creatures =
    {
        {"charizard", 120, 100, PowerType::Fire},
        {"pikachu", 40, 30, PowerType::Fire},
        {"squirtle", 40, 10, PowerType::Water},
        {"mewtwo", 130, 20, PowerType::Earth},
        {"gyarados", 100, 50, PowerType::Water},
        {"lugia", 90, 90, PowerType::Air},
        {"snorlax", 150, 150, PowerType::Earth},
        {"articuno", 70, 50, PowerType::Air}
    };

    std::cout << "Initial order of the creatures:" << std::endl;
    printCollection(creatures);

    std::cout << std::endl;
    std::cout << "Sorting by attack:" << std::endl;

    CreatureSorterByAttack sorter;
    std::sort(creatures.begin(), creatures.end(), sorter);

    printCollection(creatures,
        [](const Creature& creature)
        {
            return std::format("({})", creature.mAttack);
        });

    std::cout << std::endl;
    std::cout << "Executing some attacks!" << std::endl;

    {
        // grabbing a temporary pointer to the creatures...
        // note that if the std::vector re-allocates, those pointers become invalid.
        // we just rmeove this temporary map structure after we are done with the task (via scope {}).
        std::unordered_map<std::string, Creature*> creaturesByNameMap;

        for (Creature& creature : creatures)
            creaturesByNameMap[creature.mName] = &creature;

        auto attack = [&creaturesByNameMap](const std::string& source, const std::string& target)
        {
            assert(creaturesByNameMap[source]);
            assert(creaturesByNameMap[target]);
    
            Creature& sourceCreature = *creaturesByNameMap[source];
            Creature& targetCreature = *creaturesByNameMap[target];
    
            sourceCreature.attackTo(targetCreature);
    
            std::cout << std::format("{} attacked {} to {}({}/{}).",
                source, sourceCreature.mAttack, target, targetCreature.mCurrentHealthPoints, targetCreature.mMaxHealthPoints) << std::endl;
        };

        attack("pikachu", "charizard");
        attack("charizard", "mewtwo");
        attack("squirtle", "pikachu");
        attack("pikachu", "charizard");
        attack("snorlax", "articuno");
    }

    std::cout << std::endl;
    std::cout << "Sorting by health points percentage:" << std::endl;

    std::sort(creatures.begin(), creatures.end(), CreatureSorterByHealthPointsPercentage{});

    printCollection(creatures,
        [](const Creature& creature)
        {
            return std::format("({}/{})", creature.mCurrentHealthPoints, creature.mMaxHealthPoints);
        });

    std::cout << std::endl;
    std::cout << "Grouping creatures per type..." << std::endl;
    std::unordered_map<PowerType, std::list<Creature>> creaturesByType;

    for (const auto& creature : creatures)
    {
        PowerType powerType = creature.mPowerType;

        if (not creaturesByType.contains(powerType))
            creaturesByType[powerType] = {};

        creaturesByType[powerType].push_back(creature);
    }

    std::cout << "Only Earth creatures: ";
    printCollection(creaturesByType[PowerType::Earth]);

    // we can also code something more generic...
    for (auto& pair : creaturesByType)
    {
        PowerType powerType = pair.first; // key
        std::cout << "- " << str(powerType) << " creatures: ";
        printCollection(creaturesByType[powerType]);
    }

    std::cout << std::endl;
    std::cout << "Looking for a dead creature..." << std::endl;

    auto deadCreatureIt = std::find_if(creatures.cbegin(), creatures.cend(),
        [](const Creature& creature)
        {
            return not creature.isAlive();
        }
    );

    if (deadCreatureIt != creatures.cend())
    {
        const Creature& deadCreature = *deadCreatureIt;
        std::cout << "We found that " << deadCreature.mName << " is dead :(" << std::endl;
    }
    else
    {
        std::cout << "All creatures are alive!" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Selecting only the first creature of each type..." << std::endl;

    std::set<Creature, CreatureTypeComparer> uniqueTypeCreatureSet;

    for (const Creature& creature : creatures)
    {
        auto pair = uniqueTypeCreatureSet.insert(creature);
        std::cout << creature.mName << " " << str(creature.mPowerType) << " -> " << (pair.second ? "yay!" : ":(") << std::endl;
    }

    std::cout << "Selected creatures:" << std::endl;

    printCollection(uniqueTypeCreatureSet);
}