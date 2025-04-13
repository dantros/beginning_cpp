/**
 * @file tutorial_04_runtime_game_object_models.cpp
 * @author Daniel Calderón (https://github.com/dantros)
 * @brief Tutorial C++ code showing how to implement different runtime game object models for a game engine.
 *        It also gives you some problems to test and stress your knowledge.
 * @version 1.0
 * @date 2025-03-26
 * @license This code is released under the MIT public licence.
 * 
 * This code builds with: clang++ -std=c++20 -o demo.exe tutorial_04_runtime_game_object_models.cpp
 */

/*
Problem 1:
Our game has 2 characters, Mario and Shantae, both need to focus before executing their flagship actions, jump and dance respectively.

The following code model this behavior using the famous 3 runtime game object models. 
Your task: study this code, questioning every line.
*/

#include <iostream>
#include <cassert>
#include <unordered_map>
#include <memory>

// Monolithic hierarchy, maybe the simplest for a basic game, but also most likely the most cumbersome when dealing with a large gameplay system.
namespace Monolithic
{
    struct GameObjectBase
    {
    private:
        // this is just to trigger the vtable generation by the compiler.
        virtual void f(){};
    };

    struct Focus : public GameObjectBase
    {
        int focusLevel = 0;

        void focus()
        {
            focusLevel++;
        }

        bool perform(int focusRequired)
        {
            assert(focusRequired >= 0);

            if (focusRequired > focusLevel)
                return false;
            
            focusLevel -= focusRequired;
            return true;
        }
    };

    struct Jumper : public Focus
    {
        void jump()
        {
            if (this->perform(/*focus required*/ 3))
                std::cout << "jumping!" << std::endl;
            else
                std::cout << "not focused enough to jump :/" << std::endl;
        }
    };

    struct Dancer : public Focus
    {
        void dance()
        {
            if (this->perform(/*focus required*/ 5))
                std::cout << "dancing like nobody's watching!" << std::endl;
            else
                std::cout << "not focused enough to dance :/" << std::endl;
        }
    };

    void main()
    {
        Jumper mario;
        Dancer shantae;

        /* simulating the game loop */
        for (int i = 0; i < 10; i++)
        {
            mario.focus();
            shantae.focus();

            mario.jump();
            shantae.dance();
        }
    }
}

// here we just use raw pointers for heap memory allocations. We need to be specially careful with their handling. 
namespace BasicComponents
{
    // these are forward declarations, as we have not defined them yet.
    struct FocusComponent;
    struct JumpComponent;
    struct DanceComponent;

    struct GameObject
    {
        FocusComponent* focusComponent;
        JumpComponent* jumpComponent;
        DanceComponent* danceComponent;
    };

    struct FocusComponent
    {
        int focusLevel = 0;

        void focus()
        {
            focusLevel++;
        }

        bool perform(int focusRequired)
        {
            assert(focusRequired >= 0);

            if (focusRequired > focusLevel)
                return false;
            
            focusLevel -= focusRequired;
            return true;
        }
    };

    struct JumpComponent
    {
        // this pointer allow us to interact with the owning game object or sibling components...
        GameObject* owner;

        void jump()
        {
            // good practice: always check pointers before asking them anything.
            assert(owner != nullptr);
            assert(owner->focusComponent != nullptr);

            auto& focusComponent = owner->focusComponent;

            if (focusComponent->perform(/*focus required*/ 3))
                std::cout << "jumping!" << std::endl;
            else
                std::cout << "not focused enough to jump :/" << std::endl;
        }
    };

    struct DanceComponent
    {
        GameObject* owner;

        void dance()
        {
            assert(owner != nullptr);
            assert(owner->focusComponent != nullptr);

            auto& focusComponent = owner->focusComponent;

            if (focusComponent->perform(/*focus required*/ 5))
                std::cout << "dancing like nobody's watching!" << std::endl;
            else
                std::cout << "not focused enough to dance :/" << std::endl;
        }
    };

    void main()
    {
        GameObject mario;
        mario.focusComponent = new FocusComponent();
        mario.jumpComponent = new JumpComponent();
        mario.jumpComponent->owner = &mario;

        GameObject shantae;
        shantae.focusComponent = new FocusComponent();
        shantae.danceComponent = new DanceComponent();
        shantae.danceComponent->owner = &shantae;

        /* simulating the game loop */
        for (int i = 0; i < 10; i++)
        {
            assert(mario.focusComponent != nullptr);
            assert(shantae.focusComponent != nullptr);

            mario.focusComponent->focus();
            shantae.focusComponent->focus();

            assert(mario.jumpComponent != nullptr);
            mario.jumpComponent->jump();

            assert(shantae.danceComponent != nullptr);
            shantae.danceComponent->dance();
        }

        // freeing memory
        delete mario.focusComponent;
        delete mario.jumpComponent;
        delete shantae.focusComponent;
        delete shantae.danceComponent;
    }
}

// Same components based approach than before, but implementing it with a unique pointer
namespace BasicComponentsSmartPtr
{
    // these are forward declarations, as we have not defined them yet.
    struct FocusComponent;
    struct JumpComponent;
    struct DanceComponent;

    struct GameObject
    {
        std::unique_ptr<FocusComponent> focusComponent;
        std::unique_ptr<JumpComponent> jumpComponent;
        std::unique_ptr<DanceComponent> danceComponent;
    };

    struct FocusComponent
    {
        int focusLevel = 0;

        void focus()
        {
            focusLevel++;
        }

        bool perform(int focusRequired)
        {
            assert(focusRequired >= 0);

            if (focusRequired > focusLevel)
                return false;
            
            focusLevel -= focusRequired;
            return true;
        }
    };

    struct JumpComponent
    {
        // same as the case with raw pointers, this is to interact with the owning game object or other sibling components.
        // this does not require to be a smart pointer, as the component is not responsible for managing the memory of its owner.
        GameObject* owner;
        int focusRequiredToJump = 3;

        void jump()
        {
            // good practice: always check pointers before asking them anything.
            assert(owner != nullptr);
            assert(owner->focusComponent != nullptr);

            auto& focusComponent = owner->focusComponent;

            if (focusComponent->perform(focusRequiredToJump))
                std::cout << "jumping!" << std::endl;
            else
                std::cout << "not focused enough to jump :/" << std::endl;
        }
    };

    struct DanceComponent
    {
        GameObject* owner;
        int focusRequiredToDance = 5;

        void dance()
        {
            assert(owner != nullptr);
            assert(owner->focusComponent != nullptr);

            auto& focusComponent = owner->focusComponent;

            if (focusComponent->perform(focusRequiredToDance))
                std::cout << "dancing like nobody's watching!" << std::endl;
            else
                std::cout << "not focused enough to dance :/" << std::endl;
        }
    };

    void main()
    {
        GameObject mario;
        mario.focusComponent = std::make_unique<FocusComponent>();
        mario.jumpComponent = std::make_unique<JumpComponent>();
        mario.jumpComponent->owner = &mario; // this does not require to be a smart poiner

        GameObject shantae;
        shantae.focusComponent = std::make_unique<FocusComponent>();
        shantae.danceComponent = std::make_unique<DanceComponent>();
        shantae.danceComponent->owner = &shantae;

        /* simulating the game loop */
        for (int i = 0; i < 10; i++)
        {
            assert(mario.focusComponent != nullptr);
            assert(shantae.focusComponent != nullptr);

            mario.focusComponent->focus();
            shantae.focusComponent->focus();

            assert(mario.jumpComponent != nullptr);
            mario.jumpComponent->jump();

            assert(shantae.danceComponent != nullptr);
            shantae.danceComponent->dance();

            // we could also implement an update function for each game object, where all of its components and object logic is updated
            // the important part. Logic is handled at game object and component levels.
        }

        // memory handled via unique pointers will be freed once they go out of scope...
    }
}

// The Entity Component System approach takes advantage of the cache locality, and its logic is run at systems level.
// This approach is most likely faster when there are many game objects running exactly the same logic.
namespace EntityComponentSystem
{
    // note: only attributes in game objects and component definitions..., no member functions.
    // functionality should be implemented in systems.
    struct GameObject
    {
        int id;
    };

    struct FocusComponent
    {
        int gameObjectId;
        int focusLevel;
    };

    // note that we need to know which focus component is associated to the owning game object.
    struct JumpComponent
    {
        int gameObjectId;
        int focusRequiredToJump;
        /* for convenience, this will be the index at the focus components vector container
         * to handle the case where component can be removed and added during runtime, will require a more complex strategy. */
        int focusComponentId; 
        
    };

    // same here for focusComponentId
    struct DanceComponent
    {
        int gameObjectId;
        int focusRequiredToDance;
        int focusComponentId;
    };

    struct FocusSystem
    {
        void focus(FocusComponent& focusComponent)
        {
            focusComponent.focusLevel++;
        }

        bool perform(FocusComponent& focusComponent, int focusRequired)
        {
            assert(focusRequired >= 0);

            if (focusRequired > focusComponent.focusLevel)
                return false;
            
            focusComponent.focusLevel -= focusRequired;
            return true;
        }

        // this system operates over all components at once
        void update(std::vector<FocusComponent>& focusComponents)
        {
            // this is just a for, but it could be something different, such as a sweep line for efficient collision detection.
            for (FocusComponent& focusComponent : focusComponents)
                focus(focusComponent);
        }
    };

    struct JumpSystem
    {
        void jump(FocusComponent& focusComponent, FocusSystem& focusSystem, JumpComponent& jumpComponent)
        {
            if (focusSystem.perform(focusComponent, jumpComponent.focusRequiredToJump))
                std::cout << "jumping!" << std::endl;
            else
                std::cout << "not focused enough to jump :/" << std::endl;
        }

        // do note the complexity in stablishing the dependency relationship between different components.
        void update(std::vector<FocusComponent>& focusComponents, FocusSystem& focusSystem, std::vector<JumpComponent>& jumpComponents)
        {
            for (JumpComponent& jumpComponent : jumpComponents)
            {
                FocusComponent& relatedFocusComponent = focusComponents.at(jumpComponent.focusComponentId);

                if (focusSystem.perform(relatedFocusComponent, jumpComponent.focusRequiredToJump))
                    std::cout << "jumping!" << std::endl;
                else
                    std::cout << "not focused enough to jump :/" << std::endl;
            }
        }
    };

    struct DanceSystem
    {
        void dance(FocusComponent& focusComponent, FocusSystem& focusSystem, DanceComponent& danceComponent)
        {
            if (focusSystem.perform(focusComponent, danceComponent.focusRequiredToDance))
                std::cout << "dancing like nobody's watching!" << std::endl;
            else
                std::cout << "not focused enough to dance :/" << std::endl;
        }

        void update(std::vector<FocusComponent>& focusComponents, FocusSystem& focusSystem, std::vector<DanceComponent>& danceComponents)
        {
            for (DanceComponent& danceComponent : danceComponents)
            {
                FocusComponent& relatedFocusComponent = focusComponents.at(danceComponent.focusComponentId);

                if (focusSystem.perform(relatedFocusComponent, danceComponent.focusRequiredToDance))
                    std::cout << "dancing like nobody's watching!" << std::endl;
                else
                    std::cout << "not focused enough to dance :/" << std::endl;
            }
        }
    };

    void main()
    {
        GameObject mario{0};
        GameObject shantae{1};

        std::vector<FocusComponent> focusComponents;
        std::vector<JumpComponent> jumpComponents;
        std::vector<DanceComponent> danceComponents;

        // setting up all components in our ECS
        focusComponents.push_back({mario.id, 0});   // focusComponentId = 0
        focusComponents.push_back({shantae.id, 0}); // focusComponentId = 1

        jumpComponents.push_back({mario.id, 3, 0});
        danceComponents.push_back({shantae.id, 5, 1});

        // setting up our systems
        // note: these systems could have state variables in the general case...
        FocusSystem focusSystem;
        JumpSystem jumpSystem;
        DanceSystem danceSystem;

        /* simulating the game loop */
        for (int i = 0; i < 10; i++)
        {
            // the update happens at system level
            focusSystem.update(focusComponents);
            jumpSystem.update(focusComponents, focusSystem, jumpComponents);
            danceSystem.update(focusComponents, focusSystem, danceComponents);
        }
    }
}

// Here we execute all previous implementations. Results should be the same.
int main()
{
    std::cout << "Monolithic Hierarchy ..." << std::endl;
    Monolithic::main();
    std::cout << std::endl;

    std::cout << "Basic Components via raw pointers ..." << std::endl;
    BasicComponents::main();
    std::cout << std::endl;

    std::cout << "Basic Components via unique pointers ..." << std::endl;
    BasicComponentsSmartPtr::main();
    std::cout << std::endl;

    std::cout << "Entity Component System ..." << std::endl;
    EntityComponentSystem::main();
    std::cout << std::endl;
}

/*
Problem 2:
How do you implement a new player character, one that could dance and jump. Describe your solution for each of the architectures.

Problem 3:
About the generic components and the ECS approaches... How can we handle a game object that depends on a specific component of another game object.
Let us say, how can we implement that Mario can jump only when Shantae is dancing?, or viceversa, that Shantae can dance only when Mario is dancing?.
*/