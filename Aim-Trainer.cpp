// Aim-Trainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IMPLEMENT THE FPP AIM
//

#include <iostream>
#include <raylib.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#define UFTHColor CLITERAL(Color) { 20, 30, 40, 20 }
#define ICON {"Icons/bullseye.png"}
#define GUN {"Icons/gun10.png"}
#define RECOIL_DISTANCE 30.F
#define TARGET_VISIBLE_SIZE 10.F
#define TARGET_INVISIBLE_SIZE 0.F

#define FIRE_EFFECT_1_COLOR CLITERAL(Color) { 102, 191, 255, 255 }
#define FIRE_EFFECT_1_SIZE 120
#define FIRE_EFFECT_1_ALPHA 0.075F
#define FIRE_EFFECT_2_COLOR CLITERAL(Color) { 102, 191, 255, 50 }
#define FIRE_EFFECT_2_SIZE 250
#define FIRE_EFFECT_2_ALPHA 0.020F

#define BULLET_DISTANCE 100
#define BULLET_WIDTH 6
#define BULLET_REC CLITERAL(Rectangle) {957, 625, 0, 0}

struct Bullet {
    Vector2 position;
    Vector2 velocity;
    Vector2 target;
    bool isActive;
    bool hasHitTarget;
};

enum Bullet_Visibility
{
    TARGET_INVISIBLE = 0,
    TARGET_VISIBLE = 1
};

const int maxBullets = 100;
Bullet bullets[maxBullets];

bool isMouseOver(Vector2 circlePosition, float radius);
bool isCenter(Vector2 cursorPosition, float radius1, Vector2 targetPosition, float radius2);
float Clamp(float value, float min, float max);

int main()
{
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(1920, 1080, "Aim Trainer");
    SetWindowIcon(LoadImage(ICON));

    SetTargetFPS(60);
    HideCursor();

    Texture2D gun = LoadTexture(GUN);
    float gunX = 0;
    float gunY = 0;
    Vector2 gunPos{ gunX, gunY };

    float x = static_cast<float>(GetScreenWidth() / 2);
    float y = static_cast<float>(GetScreenHeight() / 2);

    Vector2 targetPos{ x, y };
    float targetRadius = TARGET_VISIBLE_SIZE;
    Color color = RED;
    size_t count = 0;

    Vector2 prevMousePos = { x, y };

    x = static_cast<float>(GetScreenWidth() / 2);
    y = static_cast<float>(GetScreenHeight() / 2);
    Vector2 cursorPos{ x, y };
    float cursorRadius = 5.F;
    
    bool isRecoiling = false;
    bool isAtTarget = false;

    int centerScreenX = GetScreenWidth() / 2;
    int centerScreenY = GetScreenHeight() / 2;

    srand(static_cast<unsigned>(time(0)));

    size_t reload = 22;
    size_t bullets = reload;
    size_t isTargetVisible = 1;

    Rectangle bulletRec = BULLET_REC;
    enum State
    {
        GROWING = 0,
        MAX_SIZE,
        SHRINKING,
        DONE
    };

    State BulletState = DONE;
    float FireEffect_1 = FIRE_EFFECT_1_ALPHA;
    float FireEffect_2 = FIRE_EFFECT_2_ALPHA;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        float recoilDistance = RECOIL_DISTANCE;

        switch (BulletState)
        {
        case GROWING:
            bulletRec.width = BULLET_WIDTH;
            bulletRec.height += BULLET_DISTANCE;
            bulletRec.y -= BULLET_DISTANCE;
            FireEffect_1 = FIRE_EFFECT_1_ALPHA;
            FireEffect_2 = FIRE_EFFECT_2_ALPHA;

            if (bulletRec.height >= BULLET_DISTANCE)
            {
                BulletState = MAX_SIZE;
            }
            break;

        case MAX_SIZE:
            BulletState = SHRINKING;
            break;

        case SHRINKING:
            //bulletRec.y += BULLET_DISTANCE;
            bulletRec.height -= BULLET_DISTANCE;

            if (bulletRec.height <= 0)
            {
                BulletState = DONE;
            }
            break;

        case DONE:
            bulletRec.width = 0;
            bulletRec.height = 0;
            bulletRec.x = BULLET_REC.x;
            bulletRec.y = BULLET_REC.y;
            FireEffect_1 = 0.F;
            FireEffect_2 = 0.F;
            break;
        }

        switch (isTargetVisible)
        {
        case TARGET_VISIBLE:
            targetRadius = TARGET_VISIBLE_SIZE;
            break;
        case TARGET_INVISIBLE:
            targetRadius = TARGET_INVISIBLE_SIZE;
            break;
        default:
            break;
        }

        if (isRecoiling) {
            float recoil = recoilDistance * deltaTime * 100.F;
            cursorPos.y -= recoil;
            gunPos.y -= recoil;

            if (cursorPos.y <= centerScreenY - recoilDistance) {
                cursorPos.y = centerScreenY - recoilDistance;
                gunPos.y = 0 - recoilDistance;
                isRecoiling = false;
            }

        }
        else {
            float derecoil = recoilDistance * deltaTime * 4.F;
            cursorPos.y += derecoil;
            gunPos.y += derecoil;

            if (cursorPos.y >= centerScreenY) {
                cursorPos.y = (float)centerScreenY;
                gunPos.y = 0;
            }
        }


        bool center = isCenter(cursorPos, cursorRadius, targetPos, targetRadius);
        
        if (center && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && bullets) {
            SetMousePosition((int)cursorPos.x, (int)cursorPos.y);
            isTargetVisible = TARGET_INVISIBLE;
            isRecoiling = true;
            isAtTarget = true;
            count++;
            bullets--;
            BulletState = GROWING;
        }
        else if (isAtTarget && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && bullets >= 0) {
            float xTarget = rand() % (1601 - 800) + 800.F;
            float yTarget = rand() % (801 - 600) + 600.F;
            float xMove = 0;
            if (yTarget > centerScreenY && xTarget > (centerScreenX - 200) && xTarget <= centerScreenX) {
                //xMove = xTarget - centerScreenX;
                //xMove = xMove + 200 + (xMove * (3 / 5));
                xTarget = 760;
            }
            else if (yTarget > centerScreenX && xTarget < (centerScreenX + 200) && xTarget >= centerScreenX) {
                //xMove = xTarget - centerScreenX;
                //xMove = xMove - 200 + (xMove * (3 / 5));
                xTarget = 1160;
            }
            else {
                //xMove = 0;
            }
            //xTarget += xMove;
            targetPos.x = xTarget;
            targetPos.y = yTarget;

            std::cout << "INFO: TARGET: [X: " << targetPos.x << ", Y: " << targetPos.y << "]" << std::endl;

            isRecoiling = false;
            isAtTarget = false;
            isTargetVisible = TARGET_VISIBLE;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && bullets) {
            isRecoiling = true;
            bullets--;
            BulletState = GROWING;
        }
        else if (IsKeyPressed(KEY_R) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            bullets = reload;
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isRecoiling = false;
        }
        else {
            color = VIOLET;
        }


        // Draw Target
        DrawCircle(
            (int)targetPos.x, 
            (int)targetPos.y, 
            targetRadius, 
            color
        );

        // Draw Cursor
        DrawCircle(
            (int)cursorPos.x,
            (int)cursorPos.y,
            cursorRadius,
            GOLD
        );

        // Draw Bullet
        DrawRectangleRounded(
            bulletRec, 
            0.2F, 
            10, 
            SKYBLUE
        );

        // Draw Fire Effect I
        DrawCircle(
            (int)cursorPos.x,
            (int)BULLET_REC.y - 50,
            FIRE_EFFECT_1_SIZE,
            Fade(FIRE_EFFECT_1_COLOR, FireEffect_1)
        );

        // Draw Fire Effect II
        DrawCircle(
            (int)cursorPos.x,
            (int)BULLET_REC.y - 50,
            FIRE_EFFECT_2_SIZE,
            Fade(FIRE_EFFECT_2_COLOR, FireEffect_2)
        );

        DrawRectangle(960, 540, 200, 10, GOLD);

        // Draw GUN
        DrawTexture(gun, (int)gunPos.x, (int)gunPos.y, GRAY);

        // Draw SCORE
        int textX = MeasureText(TextFormat("%d", count), 30);
        DrawText(
            TextFormat("%d", count),
            static_cast<int>(x) - textX / 2,
            static_cast<int>(y) + (int)(30) * 5.25F + (int)gunPos.y,
            30,
            RAYWHITE
        );

        // Draw Magazine
        int bulletTextX = MeasureText(TextFormat("%d/%d", bullets, reload), 30);
        DrawText(
            TextFormat("%d/%d", bullets, reload),
            static_cast<int>(x) - bulletTextX / 2,
            static_cast<int>(y) + (int)(30) * 7.5F + (int)gunPos.y,
            30,
            RAYWHITE
        );


        Vector2 currentMousePos = GetMousePosition();
        float deltaX = currentMousePos.x - prevMousePos.x;
        float deltaY = currentMousePos.y - prevMousePos.y;

        // Update target position by subtracting the mouse movement
        targetPos.x -= deltaX;
        targetPos.y -= deltaY;

        // Clamp target position to stay within window boundaries
        targetPos.x = Clamp(targetPos.x, 100, GetScreenWidth() - (100 * 2));
        targetPos.y = Clamp(targetPos.y, 100, GetScreenHeight() - (100 * 2));

        prevMousePos = currentMousePos;

        BeginDrawing();
        ClearBackground(UFTHColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

bool isMouseOver(Vector2 circlePosition, float radius) {
    return CheckCollisionPointCircle(GetMousePosition(), circlePosition, radius);
}

bool isCenter(Vector2 cursorPosition, float radiusCursor, Vector2 targetPosition, float radiusTarget) {
    return CheckCollisionCircles(cursorPosition, radiusCursor, targetPosition, radiusTarget);
}

float Clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    else {
        return value;
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
