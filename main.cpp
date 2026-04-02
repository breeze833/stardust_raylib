#include <raylib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char **argv) {
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Digital Stardust - Step 1");
    SetTargetFPS(60);

    // Initial state
    Vector2 position = { (float)screenWidth/2, (float)screenHeight/2 };
    srand(time(NULL));
    Vector2 velocity = { ((float)rand()/RAND_MAX-0.5f)*500, ((float)rand()/RAND_MAX-0.5f)*300 };
    float radius = 10.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // 1. Update: Move the ball
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        // 2. Boundary Check (Bouncing)
        if (position.x + radius >= screenWidth || position.x - radius <= 0) velocity.x *= -1.0f;
        if (position.y + radius >= screenHeight || position.y - radius <= 0) velocity.y *= -1.0f;

        // 3. Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(position, radius, WHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
