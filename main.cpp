#include <raylib.h>
#include <raymath.h>
#include <ctime>
#include <vector>
#include <optional>

using namespace std;

struct {
    int screenWidth = 800;
    int screenHeight = 480;
    int FPS = 60;
    float radius = 3.0f;
    int numParticles = 50;
    float connectionThreshold = 100.0f;
    float gravityStrength = 10000.0f;
    float minVelocity = 50.0f;
    float damping = 0.998f;
    unsigned char trailAlpha = 20;
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

void update_particle(Particle& p, float dt, const optional<Vector2> gravityPosition) {
    // Update: Velocity change by the gravity
    if (gravityPosition.has_value()) {
        Vector2 vdir = Vector2Normalize(Vector2Subtract(gravityPosition.value(), p.position)); // direction of acceleration
	Vector2 accel = Vector2Scale(vdir, config.gravityStrength); // acceleration
        p.velocity = Vector2Add(p.velocity, Vector2Scale(accel, dt)); // velocity change
    }

    // Update: Move particle
    if (Vector2Length(p.velocity)>config.minVelocity) { // slowdown a little bit
        p.velocity = Vector2Scale(p.velocity, config.damping);
    }
    p.position = Vector2Add(p.position, Vector2Scale(p.velocity, dt));
    
    // Boundary check (bouncing)
    if (p.position.x + config.radius >= config.screenWidth || p.position.x - config.radius <= 0) p.velocity.x *= -1.0f;
    if (p.position.y + config.radius >= config.screenHeight || p.position.y - config.radius <= 0) p.velocity.y *= -1.0f;
}

void draw_connection(const Particle& p1, const Particle& p2) {
    float d = Vector2Distance(p1.position, p2.position);
    if (d<=config.connectionThreshold) {
       float opacity = 1.0f - (d/config.connectionThreshold);
       Color connColor = Fade(YELLOW, opacity);
       DrawLineV(p1.position, p2.position, connColor);
    }
}

int main(int argc, char **argv) {
    InitWindow(config.screenWidth, config.screenHeight, "Digital Stardust - Step 5");
    SetTargetFPS(config.FPS);
    const Color clearColor = { 0, 0, 0, config.trailAlpha }; // high-transparency black makes old things dimming

    // Initial state
    SetRandomSeed(time(NULL));
    vector<Particle> particles;
    for (int i=config.numParticles; --i>=0;) {
        particles.push_back(random_particle());
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

	// check: location of gravity source
	optional<Vector2> gravityPos = nullopt;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            gravityPos = GetMousePosition();
        }

	// Update: particles move and bounce
	for (Particle& p : particles) {
            update_particle(p, dt, gravityPos);
	}

        // Draw
        BeginDrawing();
            // clear with a high-transparency black for retaining the traces
            DrawRectangle(0, 0, config.screenWidth, config.screenHeight, clearColor);

	    for (Particle p : particles) {
                DrawCircleV(p.position, config.radius, p.color);
	    }
	    for (int i=0; i<particles.size()-1; i++) {
                for (int j=i+1; j<particles.size(); j++) {
                    draw_connection(particles[i], particles[j]);
		}
	    }
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
