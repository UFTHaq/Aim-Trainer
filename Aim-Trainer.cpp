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

bool isMouseOver(Vector2 circlePosition, float radius);
bool isCenter(Vector2 cursorPosition, float radius1, Vector2 targetPosition, float radius2);
float Clamp(float value, float min, float max);

int main()
{
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
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
    float targetRadius = 15.F;
    Color color = RED;
    size_t count = 0;

    Vector2 prevMousePos = { x, y };

    x = static_cast<float>(GetScreenWidth() / 2);
    y = static_cast<float>(GetScreenHeight() / 2);
    Vector2 cursorPos{ x, y };
    float cursorRadius = 5.F;
    float recoilDistance = 10.F;
    bool isRecoiling = false;
    bool isAtTarget = false;

    int centerScreenX = GetScreenWidth() / 2;
    int centerScreenY = GetScreenHeight() / 2;

    srand(static_cast<unsigned>(time(0)));

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

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
        
        if (center && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            SetMousePosition((int)cursorPos.x, (int)cursorPos.y);
            targetRadius = 0.F;
            isRecoiling = true;
            isAtTarget = true;
        }
        else if (isAtTarget && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            float xTarget = rand() % (1601 - 100) + 100.F;
            float yTarget = rand() % (801 - 100) + 100.F;
            float xMove = 0;
            if (yTarget > centerScreenY && xTarget > (centerScreenX - 200) && xTarget <= centerScreenX) {
                xMove = xTarget - centerScreenX;
            }
            else if (yTarget > centerScreenX && xTarget < (centerScreenX + 200) && xTarget >= centerScreenX) {
                xMove = xTarget - centerScreenX;
            }
            else {
                xMove = 0;
            }
            xTarget += xMove;
            targetPos.x = xTarget;
            targetPos.y = yTarget;

            std::cout << "INFO: TARGET: [X: " << targetPos.x << ", Y: " << targetPos.y << "]" << std::endl;

            count++;
            isRecoiling = false;
            isAtTarget = false;
            targetRadius = 15.F;
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isRecoiling = true;
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

        DrawTexture(gun, (int)gunPos.x, (int)gunPos.y, GRAY);

        int textX = MeasureText(TextFormat("%d", count), 30);
        DrawText(
            TextFormat("%d", count),
            static_cast<int>(x) - textX/2,
            static_cast<int>(y) + (int)(30)*5.25F + (int)gunPos.y,
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
        targetPos.x = Clamp(targetPos.x, targetRadius, GetScreenWidth() - targetRadius);
        targetPos.y = Clamp(targetPos.y, targetRadius, GetScreenHeight() - targetRadius);

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
