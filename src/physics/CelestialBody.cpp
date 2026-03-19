#include "physics/CelestialBody.h"
#include "core/Constants.h"
#include "raymath.h"

// Helper: builds the sphere model used for both constructors
static Model BuildSphereModel(float radius) {
    // GenMeshSphere(radius, rings, slices)
    // More rings/slices = smoother sphere, but heavier.
    // 32x32 is a good balance for a planet.
    Mesh mesh = GenMeshSphere(radius, 32, 32);
    return LoadModelFromMesh(mesh);
}

CelestialBody::CelestialBody(std::string name, float mass, float radius, Color color, Vector3 position, Vector3 velocity){
    m_name = name;
    m_mass = mass;
    m_radius = radius;
    m_color = color;
    m_position = position;
    m_velocity = velocity;

    m_acceleration = {0.0f, 0.0f, 0.0f};
    m_forceAccumulator = {0.0f, 0.0f, 0.0f};

    
}

CelestialBody::CelestialBody(float radius, Vector3 position){
    m_name = "random body";
    m_mass = radius*SimPhysics::UNIT_MASS;
    m_radius = radius;
    m_color = RED;
    m_position = position;
    m_velocity = Vector3{0.0f, 0.0f, 0.0f};
    m_acceleration = {0.0f, 0.0f, 0.0f};
    m_forceAccumulator = {0.0f, 0.0f, 0.0f};

    
}

CelestialBody::~CelestialBody() {
    // Unload frees GPU memory for the mesh + texture
    UnloadModel(m_model);
}

void CelestialBody::Initialize() {
    // Bu fonksiyon InitWindow'dan SONRA çağrılacak
    Mesh mesh = GenMeshSphere(m_radius, 32, 32);
    m_model = LoadModelFromMesh(mesh);
}

void CelestialBody::LoadBodyTexture(const char* texturePath) {
    Texture2D tex = LoadTexture(texturePath);
    
    // Eğer texture yüklenmediyse id=0 olur
    if (tex.id == 0) {
        TraceLog(LOG_ERROR, "TEXTURE: Yuklenemedi -> %s", texturePath);
        return;
    }
    
    TraceLog(LOG_INFO, "TEXTURE: Yuklendi! id=%d, %dx%d -> %s", 
             tex.id, tex.width, tex.height, texturePath);
    
    SetTextureFilter(tex, TEXTURE_FILTER_BILINEAR);
    SetMaterialTexture(&m_model.materials[0], MATERIAL_MAP_DIFFUSE, tex);
    m_hasTexture = true;
}

void CelestialBody::Update(float deltaTime){
    if (m_mass > 0) {
        m_acceleration.x = m_forceAccumulator.x / m_mass;
        m_acceleration.y = m_forceAccumulator.y / m_mass;
        m_acceleration.z = m_forceAccumulator.z / m_mass;
    }

    // 2. Update Velocity: v = v + (a * dt)
    Vector3 deltaV = Vector3Scale(m_acceleration, deltaTime);
    m_velocity = Vector3Add(m_velocity, deltaV);

    // 3. Update Position: p = p + (v * dt)
    Vector3 deltaP = Vector3Scale(m_velocity, deltaTime);
    m_position = Vector3Add(m_position, deltaP);

    if (m_position.x > m_limit || m_position.x < -m_limit)
    {
        m_velocity.x *= -0.9f;
    }
    if (m_position.y > m_limit || m_position.y < -m_limit)
    {
        m_velocity.y *= -0.9f;
    }
    if (m_position.z > m_limit || m_position.z < -m_limit)
    {
        m_velocity.z *= -0.9f;
    }

    // 4. Reset Forces
    // We must clear the force accumulator every frame, otherwise forces build up forever!
    m_forceAccumulator = { 0.0f, 0.0f, 0.0f };
}

// --- Draw (The Render Engine) ---
void CelestialBody::Draw() {
    m_model.transform = MatrixTranslate(m_position.x, m_position.y, m_position.z);
    
    if (m_hasTexture) {
        DrawModel(m_model, {0,0,0}, 1.0f, WHITE);
    } else {
        DrawModel(m_model, {0,0,0}, 1.0f, m_color);
    }
    
    DrawSphereWires(m_position, m_radius + 0.05f, 16, 16, Fade(m_color, 0.3f));

    DrawWires(m_color);
}

void CelestialBody::DrawWires(Color color){
    DrawSphereWires(m_position, m_radius + 0.1f, 32, 32, Fade(color, 0.6f));
}

// --- Physics Helpers ---
void CelestialBody::ApplyForce(Vector3 force) {
    m_forceAccumulator = Vector3Add(m_forceAccumulator, force);
}
