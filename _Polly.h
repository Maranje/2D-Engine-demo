#pragma once
#include "element.h"

class _Polly :
    public element
{
public:
    _Polly(game* Game);
    
    void updateElement(float deltaTime) override;
    void unload();
    void processInput();

    void setPollySpeed(int Speed) { pollySpeed = Speed; }
    int getPollySpeed() { return pollySpeed; }

    bool getCarry() { return carry; }
    void setCarry(bool Carry) { carry = Carry; }

    bool getImmobile() { return immobile; }
    void setImmobile(bool Immobile) { immobile = Immobile; }

    bool getMove() { return move; }
    void setMove(bool Move) { move = Move; }

    void setSpecialAnim(int SpecialAnim) { specialAnim = SpecialAnim; }

    bool getInteract();

    //assign walking animation
    void setAnimation();

    //get the camera
    class camera* getPollyCam() { return pollyCam; }

    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

    Direction getDirection() { return direction; }

private:
    class sprite* polly;
    class sprite* shadow;
    class camera* pollyCam;
    class collider* pollyCollider;
    class interaction* pollyAction;

    Vector2 position;
    Direction direction;
    std::vector<Direction> directions;
    class input* up;
    class input* down;
    class input* left;
    class input* right;
    class input* action;
    int currentPressed;
    int pollySpeed;
    bool move;
    bool carry;
    bool immobile;
    bool interact;
    int specialAnim;
    int switchInt;
};