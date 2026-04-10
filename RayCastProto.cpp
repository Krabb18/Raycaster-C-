#include <iostream>
#include <vector>
#include <string>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


#define mapWidth 24
#define mapHeight 24


struct GameObject
{
    float x;
    float y;

    olc::Sprite *sprite;
};

class Game : public olc::PixelGameEngine
{
private:
    float playerA = 0.0f;
    float FOV = 3.14159f / 6.0f;
    olc::vf2d playerPos;
    float speed = 5.0f;


   
    int map[mapWidth][mapHeight] =
    {
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    std::map<int,olc::Pixel> colorMap;

    olc::Sprite* wallTexture = new olc::Sprite("textures/rayWall.png");
    olc::Sprite* objectSprite = new olc::Sprite("textures/obj.png");

    std::vector<GameObject> gameObjects;

public:
    Game()
    {
        sAppName = "RayCastPrototype";
    }

    bool OnUserCreate() override
    {
        colorMap[1] = olc::RED;
        colorMap[2] = olc::BLUE;
        colorMap[3] = olc::GREEN;
        colorMap[4] = olc::YELLOW;

        playerPos.x = 4;
        playerPos.y = 4;

        //objectSprite->SetSize(32, 64);

        GameObject gameObj;
        gameObj.x = 10.5f;
        gameObj.y = 10.5f;
        gameObj.sprite = objectSprite;
        gameObjects.push_back(gameObj);

        return true;
    }

    bool OnUserUpdate(float dt) override
    {
        SetPixelMode(olc::Pixel::MASK);
        Clear(olc::BLACK);

        Draw(100, 100, olc::WHITE);

        //Player Movement
        if(GetKey(olc::Key::A).bHeld)
        {
            playerA -= (speed * 0.75f) * dt;
        }
        
        if (GetKey(olc::Key::D).bHeld)
        {
            playerA += (speed * 0.75f) * dt;
        }

        if (GetKey(olc::Key::W).bHeld)
        {
            playerPos.x += sinf(playerA) * speed * dt;
            playerPos.y += cosf(playerA) * speed * dt;
            if (map[(int)playerPos.x][(int)playerPos.y] != 0)
            {
                playerPos.x -= sinf(playerA) * speed * dt;
                playerPos.y -= cosf(playerA) * speed * dt;
            }
        }

        if (GetKey(olc::Key::S).bHeld)
        {
            playerPos.x -= sinf(playerA) * speed * dt;
            playerPos.y -= cosf(playerA) * speed * dt;
            if(map[(int)playerPos.x][(int)playerPos.y] != 0)
            {
                playerPos.x += sinf(playerA) * speed * dt;
                playerPos.y += cosf(playerA) * speed * dt;
            }
        }

        for(int x = 0; x<ScreenWidth(); x++)
        {
            float rayAngle = (playerA - FOV / 2.0f) + ((float)x / (float)ScreenWidth()) * FOV;
            float fEyeX = sinf(rayAngle);
            float fEyeY = cosf(rayAngle);


            int wallType = 0;
            //DDA
            olc::vf2d rayStart = playerPos;
            olc::vf2d rayDir = (olc::vf2d(fEyeX* 10000.0f, fEyeY*10000.0f) - playerPos).norm();

            olc::vf2d rayUnitStepSize = { sqrt(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)), sqrt(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y)) };
            olc::vi2d mapCheck = rayStart;

            olc::vf2d vRayLength1D;
            olc::vi2d step;

            if(rayDir.x < 0)
            {
                step.x = -1;
                vRayLength1D.x = (rayStart.x - float(mapCheck.x)) * rayUnitStepSize.x;
            }
            else
            {
                step.x = 1;
                vRayLength1D.x = (float(mapCheck.x + 1) - rayStart.x) * rayUnitStepSize.x;
            }

            if (rayDir.y < 0)
            {
                step.y = -1;
                vRayLength1D.y = (rayStart.y - float(mapCheck.y)) * rayUnitStepSize.y;
            }
            else if (rayDir.y > 0)
            {
                step.y = 1;
                vRayLength1D.y = (float(mapCheck.y + 1) - rayStart.y) * rayUnitStepSize.y;
            }

            bool tileFound = false;
            float maxDistance = 100.0f;
   
            float distance = 0.0f;
            float sampleX = 0.0f;

            int side = 0;

            while(!tileFound && distance < maxDistance)
            {
                if(vRayLength1D.x < vRayLength1D.y)
                {
                    mapCheck.x += step.x;
                    distance = vRayLength1D.x;
                    vRayLength1D.x += rayUnitStepSize.x;
                    side = 0;
                }
                else
                {

                    mapCheck.y += step.y;
                    distance = vRayLength1D.y;
                    vRayLength1D.y += rayUnitStepSize.y;
                    side = 1;
                }

                if(mapCheck.x >= 0 && mapCheck.x < mapWidth && mapCheck.y >= 0 && mapCheck.y < mapHeight)
                {
                    if(map[mapCheck.x][mapCheck.y] != 0)
                    {
                        wallType = map[mapCheck.x][mapCheck.y];
                        tileFound = true;

                        //Where the wall was hit
                        float fBlockMidX = (float)mapCheck.x + 0.5f;
                        float fBlockMidY = (float)mapCheck.y + 0.5f;

                        float fTestPointX = playerPos.x + fEyeX * distance;
                        float fTestPointY = playerPos.y + fEyeY * distance;

                        float fTestAngle = atan2f((fTestPointY - fBlockMidY), (fTestPointX - fBlockMidX));

                        /*
                        if (lastHit == 1)
                        {
                            
                            sampleX = fTestPointY - (float)mapCheck.y;
                        }
                        else
                        {
                            sampleX = fTestPointX - (float)mapCheck.x;
                            
                        }
                        */

                        ///Calc X UV
                        if (fTestAngle >= -3.14159f * 0.25f && fTestAngle < 3.14159f * 0.25f)
                            sampleX = fTestPointY - (float)mapCheck.y;
                        if (fTestAngle >= 3.14159f * 0.25f && fTestAngle < 3.14159f * 0.75f)
                            sampleX = fTestPointX - (float)mapCheck.x;
                        if (fTestAngle < -3.14159f * 0.25f && fTestAngle >= -3.14159f * 0.75f)
                            sampleX = fTestPointX - (float)mapCheck.x;
                        if (fTestAngle >= 3.14159f * 0.75f || fTestAngle < -3.14159f * 0.75f)
                            sampleX = fTestPointY - (float)mapCheck.y;

                    }
                }
            }

            //From https://www.permadi.com/tutorial/raycast/rayc8.html
            distance = distance * cosf((rayAngle - playerA));

            if(tileFound)
            {
                int nCeiling = (float)(ScreenHeight() / 2.0f) - ScreenHeight() / ((float)distance);
                int nFloor = ScreenHeight() - nCeiling;

                for(int y = 0; y<ScreenHeight(); y++)
                {
                    if (y <= nCeiling)
                    {
                        Draw(x, y, olc::BLUE);
                    }
                    else if(y > nCeiling && y <= nFloor)
                    {
                        //texture
                        float sampleY = ((float)y - (float)nCeiling) / ((float)nFloor - nCeiling);
                        Draw(x, y, wallTexture->GetPixel(sampleX*64.0f, sampleY*64.0f));
                        //Draw(x, y, colorMap[wallType]);
                    }
                    else
                    {
                        Draw(x, y, olc::CYAN);
                    }
                }

            }

            
            

            //Für pixel 0.0-1.0
        }

        //Object Drawing

        for (int i = 0; i < gameObjects.size(); i++)
        {
            float vecX = gameObjects[i].x - playerPos.x;
            float vecY = gameObjects[i].y - playerPos.y;

            float distanceToPlayer = sqrtf(vecX * vecX + vecY * vecY);

            float fEyeXA = sinf(playerA);
            float fEyeYA = cosf(playerA);


            float objectAngle = atan2f(fEyeYA, fEyeXA) - atan2f(vecY, vecX);
            // to determine if the lamp is in the players field of view

            if (objectAngle < -3.14159f)
                objectAngle += 2.0f * 3.14159f;
            if (objectAngle > 3.14159f)
                objectAngle -= 2.0f * 3.14159f;

            bool inPlayerFOV = fabs(objectAngle) < FOV / 2.0f;
            if (inPlayerFOV && distanceToPlayer < 10.0f && distanceToPlayer > 2.5f)
            {
                //In Player FOV
                float fObjectCeiling = (float)(ScreenHeight() / 2.0) - ScreenHeight() / ((float)distanceToPlayer);
                float fObjectFloor = ScreenHeight() - fObjectCeiling;
                float fObjectHeight = fObjectFloor - fObjectCeiling;

                float fObjectAspectRatio = (float)gameObjects[i].sprite->height / (float)gameObjects[i].sprite->width;
                float fObjectWidth = fObjectHeight / fObjectAspectRatio;

                float fMiddleOfObject = (0.5f * (objectAngle / (FOV / 2.0f)) + 0.5f) * (float)ScreenWidth();

                for (int lx = 0; lx < fObjectWidth; lx++)
                {
                    for (int ly = 0; ly < fObjectHeight; ly++)
                    {
                        int nObjectColumn = (int)(fMiddleOfObject + lx - (fObjectWidth / 2.0f));


                        if (nObjectColumn >= 0 && nObjectColumn < ScreenWidth())
                        {
                            float fSampleX = lx / fObjectWidth;
                            float fSampleY = ly / fObjectHeight;
                            Draw(nObjectColumn, fObjectCeiling + ly, gameObjects[i].sprite->Sample(fSampleX, fSampleY));
                        }


                    }
                }

            }

        }

        return true;
    }

    bool OnUserDestroy() override
    {
        delete wallTexture;
        delete objectSprite;
        return true;
    }
};

int main()
{
    Game game;
    if (game.Construct(256, 240, 4, 4))
        game.Start();
}