#include <raylib.h>
#include <ctime>
#include <vector>

using namespace std;

struct {
    int screenWidth = 800;
    int screenHeight = 480;
    int FPS = 60;
    float radius = 5.0f;
    int numParticles = 50;
} config;

typedef struct _Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
} Particle;

Particle random_particle() {
    Particle p;
    p.position = {
        GetRandomValue(0, config.screenWidth)*0.9f,
        GetRandomValue(0, config.screenHeight)*0.9f
    };
    p.velocity = {
        GetRandomValue(-config.screenWidth/2, config.screenWidth/2)*0.8f,
        GetRandomValue(-config.screenHeight/2, config.screenHeight/2)*0.8f,
    };
    unsigned char v = GetRandomValue(128, 224);
    p.color = { v, v, v, (unsigned char)255 }; 
    return p;
}

void update_particle(Particle& p, float dt) {
    // Update: Move particle
    p.position.x += p.velocity.x * dt;
    p.position.y += p.velocity.y * dt;
    
    // Boundary check (bouncing)
    if (p.position.x + config.radius >= config.screenWidth || p.position.x - config.radius <= 0) p.velocity.x *= -1.0f;
    if (p.position.y + config.radius >= config.screenHeight || p.position.y - config.radius <= 0) p.velocity.y *= -1.0f;
}

int main(int argc, char **argv) {
    InitWindow(config.screenWidth, config.screenHeight, "Digital Stardust - Step 2");
    SetTargetFPS(config.FPS);

    // Initial state
    SetRandomSeed(time(NULL));
    vector<Particle> particles;
    for (int i=config.numParticles; --i>=0;) {
        particles.push_back(random_particle());
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

	// Update: particles move and bounce
	for (Particle& p : particles) {
            update_particle(p, dt);
	}

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
	    for (Particle p : particles) {
                DrawCircleV(p.position, config.radius, p.color);
	    }
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
