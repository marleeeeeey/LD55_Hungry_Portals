#pragma once
#include "utils/coordinates_transformer.h"
#include "utils/objects_factory.h"
#include "utils/resource_manager.h"
#include <entt/entt.hpp>
#include <optional>
#include <queue>
#include <utils/audio_system.h>
#include <utils/box2d_entt_contact_listener.h>
#include <utils/entt_registry_wrapper.h>
#include <utils/game_options.h>

class WeaponControlSystem
{
    EnttRegistryWrapper& registryWrapper;
    entt::registry& registry;
    GameOptions& gameState;
    Box2dEnttContactListener& contactListener;
    AudioSystem& audioSystem;
    ObjectsFactory& objectsFactory;
    float deltaTime;
    std::queue<entt::entity> contactedEntities;
    CoordinatesTransformer coordinatesTransformer;
public:
    WeaponControlSystem(
        EnttRegistryWrapper& registryWrapper, Box2dEnttContactListener& contactListener, AudioSystem& audioSystem,
        ObjectsFactory& objectsFactory);
    void Update(float deltaTime);
private:
    void UpdateTimerExplosionComponents();
    void UpdateContactExplosionComponentTimer();
    void ProcessExplosionEntitiesQueue();
    void OnBazookaContactWithTile(entt::entity bazookaEntity, entt::entity tileEntity);
    void TryToRunExplosionImpactComponent(entt::entity explosionEntity);
private: // Low level functions.
    void ApplyForceToPhysicalBodies(
        std::vector<entt::entity> physicalEntities, const b2Vec2& grenadePhysicsPos, float force);
private: // TODO3: functions to move to shared code like utils.
    std::vector<entt::entity> GetPhysicalBodiesInRaduis(
        const b2Vec2& center, float radius, std::optional<b2BodyType> bodyType);
    std::vector<entt::entity> GetPhysicalBodiesInRaduis(
        const std::vector<entt::entity>& entities, const b2Vec2& center, float physicalRadius,
        std::optional<b2BodyType> bodyType);
    std::vector<entt::entity> AddAndReturnSplittedPhysicalEntetiesToWorld(
        const std::vector<entt::entity>& entities, SDL_Point cellSize);
    std::vector<entt::entity> ExcludePlayersFromList(const std::vector<entt::entity>& entities);
};