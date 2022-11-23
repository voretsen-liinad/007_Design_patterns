#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class Command {
public:
    virtual void Execute() = 0;
};

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    template <typename T>
    class DeleteObjectCommand : public Command {
    public:
        DeleteObjectCommand(T* _pObj, std::vector<T*>& _vecObj) : pObj(_pObj), vecObj(_vecObj) {}
        void Execute() override {
            auto it = vecObj.begin();
            for (; it != vecObj.end(); it++)
            {
                if (*it == pObj)
                {
                    vecObj.erase(it);
                    break;
                }
            }
        }
    private:
        T* pObj;
        std::vector<T*>& vecObj;
    };

    class DropBombCommand : public Command {
    public:
        DropBombCommand(Plane* _pPlane, std::vector<DynamicObject*>& _vecDynObj)
            : pPlane(_pPlane), vecDynObj(_vecDynObj) {}
        void Execute() override {
                double x = pPlane->GetX() + 4;
                double y = pPlane->GetY() + 2;

                //Bomb* pBomb = new Bomb;
                BombDecorator* pBomb = new BombDecorator;
                pBomb->SetDirection(0.3, 1);
                pBomb->SetSpeed(2);
                pBomb->SetPos(x, y);
                pBomb->SetWidth(SMALL_CRATER_SIZE);

                vecDynObj.push_back(pBomb);
        }
    private:
        Plane* pPlane;
        std::vector<DynamicObject*>& vecDynObj;
    };

    void CommandExecuter(Command* pCommand) {
        pCommand->Execute();
        delete pCommand;
    }

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(BombDecorator* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    std::vector<BombDecorator*> FindAllBombsDecorator() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};