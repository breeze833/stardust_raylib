#include "StardustApp.h"
#include <raymath.h>
#include <ctime>

StardustApp::StardustApp() : clearColor({0,0,0,config.trailAlpha}) {
    mouseGravity = new MouseAttractor();
    autoGravity = new AutoAttractor(config.screenWidth/2, config.screenHeight/2);
}

StardustApp::~StardustApp() {
    delete mouseGravity;
    delete autoGravity;
}

bool StardustApp::init() {
    InitWindow(config.screenWidth, config.screenHeight, "Digital Stardust - Step 7");
    SetTargetFPS(config.FPS);

    // Initial state
    SetRandomSeed(time(NULL));
    for (int i=config.numParticles; --i>=0;) {
        particles.push_back(random_particle());
    }
    return true;
}

void StardustApp::update() {
    float dt = GetFrameTime();

    // check: location of gravity source
    Attractor *attractor = mouseGravity;
    mouseGravity->update();
    double curTime = GetTime();
    if (!mouseGravity->getPosition().has_value()) { // no mouse click
        if (curTime > lastAttract+config.autoGravityInterval) { // no gravity for a long time
            lastAttract = curTime;
            autoGravity->update();
            attractor = autoGravity;
        }
    } else { // mouse clicked
        lastAttract = curTime;
    }

    // Update: particles move and bounce
    for (Particle& p : particles) {
        update_particle(p, dt, attractor->getPosition());
    }
}

void StardustApp::draw() {
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

void StardustApp::run() {
    MouseAttractor mouseGravity; // Gravity source by mouse click
    AutoAttractor autoGravity(config.screenWidth, config.screenHeight); // Gravity source by moving along Lessajous curve
    lastAttract = GetTime(); // track the last attract action
    
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void StardustApp::cleanup() {
    CloseWindow();
}

Particle StardustApp::random_particle() {
    Particle p;
    p.position = {
        GetRandomValue(0, config.screenWidth) * 0.9f,
        GetRandomValue(0, config.screenHeight) * 0.9f
    };
    p.velocity = {
        GetRandomValue(-config.screenWidth / 2, config.screenWidth / 2) * 0.8f,
        GetRandomValue(-config.screenHeight / 2, config.screenHeight / 2) * 0.8f
    };
    unsigned char v = GetRandomValue(128, 224);
    p.color = {v, v, v, (unsigned char)255};
    return p;
}

void StardustApp::update_particle(Particle &p, float dt, const optional<Vector2> gravityPosition) {
    // Update: Velocity change by the gravity
    if (gravityPosition.has_value()) {
        Vector2 vdir = Vector2Normalize(Vector2Subtract(gravityPosition.value(), p.position)); // direction of acceleration
        Vector2 accel = Vector2Scale(vdir, config.gravityStrength); // acceleration
        p.velocity = Vector2Add(p.velocity, Vector2Scale(accel, dt)); // velocity change
    }

    // Update: Move particle
    if (Vector2Length(p.velocity) > config.minVelocity) { // slowdown a little bit
        p.velocity = Vector2Scale(p.velocity, config.damping);
    }
    p.position = Vector2Add(p.position, Vector2Scale(p.velocity, dt));

    // Boundary check (bouncing)
    if (p.position.x + config.radius >= config.screenWidth || p.position.x - config.radius <= 0) {
        p.velocity.x *= -1.0f;
    }
    if (p.position.y + config.radius >= config.screenHeight || p.position.y - config.radius <= 0) {
        p.velocity.y *= -1.0f;
    }
}

void StardustApp::draw_connection(const Particle &p1, const Particle &p2) {
    float d = Vector2Distance(p1.position, p2.position);
    if (d<=config.connectionThreshold) {
       float opacity = 1.0f - (d/config.connectionThreshold);
       Color connColor = Fade(YELLOW, opacity);
       DrawLineV(p1.position, p2.position, connColor);
    }
}
