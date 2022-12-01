#pragma once

#include <vector>
#include <string>
#include <boost/optional.hpp>
#include "cxx.h"
#include "carla/Time.h"
#include "carla/Memory.h"
#include "carla/client/Client.h"
#include "carla/client/World.h"
#include "carla/client/Map.h"
#include "carla/client/Actor.h"
#include "carla/client/ActorBlueprint.h"
#include "carla/client/BlueprintLibrary.h"
#include "carla/client/Sensor.h"
#include "carla/client/Vehicle.h"
#include "carla/rpc/AttachmentType.h"
#include "carla/rpc/MapLayer.h"
#include "carla/rpc/OpendriveGenerationParameters.h"
#include "carla/rpc/LabelledPoint.h"
#include "carla/rpc/VehicleControl.h"
#include "carla/rpc/VehiclePhysicsControl.h"
#include "carla/rpc/VehicleDoor.h"
#include "carla/rpc/VehicleWheels.h"
#include "carla/rpc/VehicleLightState.h"
#include "carla/rpc/TrafficLightState.h"
#include "carla/geom/Transform.h"
#include "carla/geom/Location.h"
#include "carla/geom/Rotation.h"
#include "carla/geom/Vector2D.h"
#include "carla/geom/Vector3D.h"
#include "carla/geom/BoundingBox.h"

namespace carla_rust {

    namespace geom {
        using carla::geom::Transform;
        using carla::geom::Location;
        using carla::geom::Rotation;
        using carla::geom::Vector2D;
        using carla::geom::Vector3D;

        // Vector2D
        class FfiVector2D {
        public:
            FfiVector2D(Vector2D &&from)
                : inner_(from)
            {}

            FfiVector2D(float x, float y)
                : inner_(std::move(Vector2D(x, y)))
            {}

            float x() const {
                return inner_.x;
            }

            float y() const {
                return inner_.y;
            }

            const Vector2D& inner() const {
                return inner_;
            }

        private:
            Vector2D inner_;
        };

        // Vector3D
        class FfiVector3D {
        public:
            FfiVector3D(Vector3D &&from)
                : inner_(from)
            {}

            FfiVector3D(float x, float y, float z)
                : inner_(std::move(Vector3D(x, y, z)))
            {}

            float x() const {
                return inner_.x;
            }

            float y() const {
                return inner_.y;
            }

            float z() const {
                return inner_.z;
            }

            const Vector3D& inner() const {
                return inner_;
            }

        private:
            Vector3D inner_;
        };

        // Location
        class FfiLocation {
        public:
            FfiLocation(Location &&from)
                : inner_(from)
            {}

            FfiLocation(float x, float y, float z)
                : FfiLocation(std::move(Location(Vector3D(x, y, z))))
            {}


            float x() const {
                return inner_.x;
            }

            float y() const {
                return inner_.y;
            }

            float z() const {
                return inner_.z;
            }

            const Location &as_location() const {
                return inner_;
            }

            const Vector3D &as_vector_3d() const {
                return static_cast<const Vector3D&>(inner_);
            }

        private:
            Location inner_;
        };

        // Rotation
        class FfiRotation {
        public:
            FfiRotation(Rotation &&from)
                : inner_(from)
            {}

            FfiRotation(float p, float y, float r)
                : FfiRotation(std::move(Rotation(p, y, r)))
            {}


            float pitch() const {
                return inner_.pitch;
            }

            float yaw() const {
                return inner_.yaw;
            }

            float roll() const {
                return inner_.roll;
            }

            const Rotation &inner() const {
                return inner_;
            }

        private:
            Rotation inner_;
        };


        // Transform
        class FfiTransform {
        public:
            FfiTransform(Transform &&transform)
                : inner_(transform)
            {}


            FfiTransform(const FfiLocation &location, const FfiRotation &rotation)
                : inner_(location.as_location(), rotation.inner())
            {
            }

            const Transform& inner() const {
                return inner_;
            }

            FfiLocation location() const {
                Location loc = inner_.location;
                return FfiLocation(std::move(loc));
            }

            FfiRotation rotation() const {
                Rotation rot = inner_.rotation;
                return FfiRotation(std::move(rot));
            }

        private:
            Transform inner_;
        };
    }

    namespace client {
        using carla::SharedPtr;
        using carla::time_duration;
        using carla::geom::Transform;
        using carla::geom::Location;
        using carla::geom::Vector3D;
        using carla::geom::BoundingBox;
        using carla::client::Client;
        using carla::client::World;
        using carla::client::Map;
        using carla::client::Actor;
        using carla::client::Waypoint;
        using carla::client::BlueprintLibrary;
        using carla::client::ActorBlueprint;
        using carla::client::Sensor;
        using carla::client::Landmark;
        using carla::client::WorldSnapshot;
        using carla::client::Vehicle;
        using carla::rpc::AttachmentType;
        using carla::rpc::MapLayer;
        using carla::rpc::OpendriveGenerationParameters;
        using carla::rpc::LabelledPoint;
        using carla::rpc::VehicleControl;
        using carla::rpc::VehiclePhysicsControl;
        using carla::rpc::VehicleDoor;
        using carla::rpc::VehicleWheelLocation;
        using carla::rpc::TrafficLightState;
        using carla::rpc::VehicleLightState;
        // using LightState = carla::rpc::VehicleLightState::LightState;
        using carla::road::Lane;
        using carla::road::RoadId;
        using carla::road::LaneId;
        using carla::road::SignId;
        using carla::traffic_manager::constants::Networking::TM_DEFAULT_PORT;
        using carla_rust::geom::FfiVector2D;
        using carla_rust::geom::FfiVector3D;
        using carla_rust::geom::FfiLocation;
        using carla_rust::geom::FfiRotation;
        using carla_rust::geom::FfiTransform;

        // functions
        ActorBlueprint copy_actor_blueprint(const ActorBlueprint &ref) {
            return ref;
        }

        // class declarations
        class FfiActor;
        class FfiVehicle;

        // Map
        class FfiMap {
        public:
            FfiMap(SharedPtr<Map> &&ref)
                : inner_(ref)
            {}

            FfiMap(FfiMap &&from) = default;

            const std::string &GetName() const {
                return inner_->GetName();
            }

            const std::string &GetOpenDrive() const {
                return inner_->GetOpenDrive();
            }

            const std::vector<Transform> &GetRecommendedSpawnPoints() const {
                return inner_->GetRecommendedSpawnPoints();
            }

            SharedPtr<Waypoint> GetWaypoint(const Location &location,
                                            bool project_to_road = true,
                                            int32_t lane_type = static_cast<uint32_t>(Lane::LaneType::Driving)) const
            {
                return SharedPtr<Waypoint>(inner_->GetWaypoint(location, project_to_road, lane_type));
            }

            SharedPtr<Waypoint> GetWaypointXODR(RoadId road_id,
                                                LaneId lane_id,
                                                float s) const
            {
                return SharedPtr<Waypoint>(inner_->GetWaypointXODR(road_id, lane_id, s));
            }


        private:
            SharedPtr<Map> inner_;
        };

        // Vehicle
        class FfiVehicle {
        public:
            FfiVehicle(SharedPtr<Vehicle> &&base)
                : inner_(base)
            {}


            void SetAutopilot(bool enabled = true, uint16_t tm_port = TM_DEFAULT_PORT) {
                inner_->SetAutopilot(enabled, tm_port);
            }

            void ShowDebugTelemetry(bool enabled = true) {
                inner_->ShowDebugTelemetry(enabled);
            }

            /// Apply @a control to this vehicle.
            void ApplyControl(const VehicleControl &control) {
                inner_->ApplyControl(control);
            }

            void ApplyPhysicsControl(const VehiclePhysicsControl &physics_control) {
                inner_->ApplyPhysicsControl(physics_control);
            }

            void OpenDoor(const VehicleDoor door_idx) {
                inner_->OpenDoor(door_idx);
            }

            void CloseDoor(const VehicleDoor door_idx) {
                inner_->CloseDoor(door_idx);
            }

            void SetLightState(const VehicleLightState::LightState &light_state) {
                inner_->SetLightState(light_state);
            }

            void SetWheelSteerDirection(VehicleWheelLocation wheel_location, float angle_in_deg) {
                inner_->SetWheelSteerDirection(wheel_location, angle_in_deg);
            }

            float GetWheelSteerAngle(VehicleWheelLocation wheel_location) {
                return inner_->GetWheelSteerAngle(wheel_location);
            }

            VehicleControl GetControl() const {
                return inner_->GetControl();
            }

            VehiclePhysicsControl GetPhysicsControl() const {
                return inner_->GetPhysicsControl();
            }

            VehicleLightState::LightState GetLightState() const {
                return inner_->GetLightState();
            }

            float GetSpeedLimit() const {
                return inner_->GetSpeedLimit();
            }

            TrafficLightState GetTrafficLightState() const {
                return inner_->GetTrafficLightState();
            }

            bool IsAtTrafficLight() {
                return inner_->IsAtTrafficLight();
            }

            // SharedPtr<TrafficLight> GetTrafficLight() const {}

            void EnableCarSim(std::string simfile_path) {
                inner_->EnableCarSim(simfile_path);
            }

            void UseCarSimRoad(bool enabled) {
                inner_->UseCarSimRoad(enabled);
            }

            void EnableChronoPhysics(uint64_t MaxSubsteps,
                                     float MaxSubstepDeltaTime,
                                     std::string VehicleJSON = "",
                                     std::string PowertrainJSON = "",
                                     std::string TireJSON = "",
                                     std::string BaseJSONPath = "") {
                inner_->EnableChronoPhysics(MaxSubsteps,
                                           MaxSubstepDeltaTime,
                                           VehicleJSON,
                                           PowertrainJSON,
                                           TireJSON,
                                           BaseJSONPath);
            }

            std::unique_ptr<FfiActor> to_actor() const {
                SharedPtr<Actor> ptr = boost::static_pointer_cast<Actor>(inner_);
                return std::make_unique<FfiActor>(std::move(ptr));
            }

        private:
            SharedPtr<Vehicle> inner_;
        };


        // Actor
        class FfiActor {
        public:
            FfiActor(SharedPtr<Actor> &&ref)
                : inner_(ref)
            {
            }

            const SharedPtr<Actor>& inner() const {
                return inner_;
            }

            FfiLocation GetLocation() const {
                auto location = inner_->GetLocation();
                return FfiLocation(std::move(location));
            }

            FfiTransform GetTransform() const {
                auto transform = inner_->GetTransform();
                return FfiTransform(std::move(transform));
            }

            FfiVector3D GetVelocity() const {
                auto vel = inner_->GetVelocity();
                return FfiVector3D(std::move(vel));
            }

            FfiVector3D GetAngularVelocity() const {
                auto av = inner_->GetAngularVelocity();
                return FfiVector3D(std::move(av));
            }

            FfiVector3D GetAcceleration() const {
                auto acc = inner_->GetAcceleration();
                return FfiVector3D(std::move(acc));
            }

            std::unique_ptr<FfiVehicle> to_vehicle() const {
                SharedPtr<Vehicle> ptr = boost::dynamic_pointer_cast<Vehicle>(inner_);
                if (ptr == nullptr) {
                    return nullptr;
                } else {
                    return std::make_unique<FfiVehicle>(std::move(ptr));
                }
            }

        private:
            SharedPtr<Actor> inner_;
        };

        class FfiBlueprintLibrary {
        public:
            FfiBlueprintLibrary(SharedPtr<BlueprintLibrary> &&ref)
                : inner_(ref)
            {
            }


            FfiBlueprintLibrary filter(const std::string &pattern) const {
                auto lib = inner_->Filter(pattern);
                return FfiBlueprintLibrary(std::move(lib));
            }

            const ActorBlueprint* find(const std::string &key) const {
                return inner_->Find(key);
            }

            const ActorBlueprint* at(size_t pos) const {
                if (pos >= size()) {
                    return nullptr;
                }
                return &inner_->at(pos);
            }


            bool is_empty() const {
                return inner_->empty();
            }

            size_t size() const {
                return inner_->size();
            }

        private:
            SharedPtr<BlueprintLibrary> inner_;
        };


        class FfiWorld {
        public:
            FfiWorld(World &&base)
                : inner_(base)
            {
            }


            uint64_t GetId() const {
                return inner_.GetId();
            }

            FfiMap GetMap() const {
                auto inner = inner_.GetMap();
                FfiMap map(std::move(inner));
                return map;
            }

            FfiActor GetSpectator() const {
                auto inner = inner_.GetSpectator();
                FfiActor actor(std::move(inner));
                return actor;
            }

            FfiBlueprintLibrary GetBlueprintLibrary() const {
                auto lib = inner_.GetBlueprintLibrary();
                return FfiBlueprintLibrary(std::move(lib));
            }

            std::unique_ptr<FfiActor> TrySpawnActor(const ActorBlueprint &blueprint,
                                               const FfiTransform &transform,
                                               FfiActor *parent = nullptr,
                                               AttachmentType attachment_type = AttachmentType::Rigid) noexcept
            {
                Actor *parent_arg = nullptr;
                if (parent != nullptr) {
                    const SharedPtr<Actor> &ptr = parent->inner();
                    parent_arg = ptr.get();
                }

                auto transform_arg = transform.inner();

                auto actor = inner_.TrySpawnActor(blueprint, transform_arg, parent_arg, attachment_type);
                if (actor == nullptr) {
                    return nullptr;
                } else {
                    return std::make_unique<FfiActor>(std::move(actor));
                }
            }


            WorldSnapshot WaitForTick(size_t millis) const {
                return inner_.WaitForTick(time_duration::milliseconds(millis));
            }

            uint64_t Tick(size_t millis) {
                return inner_.Tick(time_duration::milliseconds(millis));
            }

            void SetPedestriansCrossFactor(float percentage) {
                inner_.SetPedestriansCrossFactor(percentage);
            }

            void SetPedestriansSeed(unsigned int seed) {
                inner_.SetPedestriansSeed(seed);
            }

            FfiActor GetTrafficSign(const Landmark& landmark) const {
                auto actor = inner_.GetTrafficSign(landmark);
                return FfiActor(std::move(actor));
            }

            FfiActor GetTrafficLight(const Landmark& landmark) const {
                auto actor = inner_.GetTrafficLight(landmark);
                return FfiActor(std::move(actor));
            }

            FfiActor GetTrafficLightFromOpenDRIVE(const SignId& sign_id) const {
                auto actor = GetTrafficLightFromOpenDRIVE(sign_id);
                return FfiActor(std::move(actor));
            }

            void ResetAllTrafficLights() {
                inner_.ResetAllTrafficLights();
            }

            // SharedPtr<LightManager> GetLightManager() const;

            // detail::EpisodeProxy GetEpisode() const {
            //     return _episode;
            // };


            void FreezeAllTrafficLights(bool frozen) {
                inner_.FreezeAllTrafficLights(frozen);
            }

            std::vector<BoundingBox> GetLevelBBs(uint8_t queried_tag) const {
                return inner_.GetLevelBBs(queried_tag);
            }

            // boost::optional<LabelledPoint> ProjectPoint(Location location,
            //                                             Vector3D direction,
            //                                             float search_distance = 10000.f) const
            // {
            //     return inner_.ProjectPoint(location, direction, search_distance);
            // }

            // boost::optional<rpc::LabelledPoint> GroundProjection(
            //                                                      geom::Location location, float search_distance = 10000.0) const;

            // std::vector<rpc::LabelledPoint> CastRay(
            //                                         geom::Location start_location, geom::Location end_location) const;

            // std::vector<SharedPtr<Actor>> GetTrafficLightsFromWaypoint(
            //                                                            const Waypoint& waypoint, double distance) const;

            // std::vector<SharedPtr<Actor>> GetTrafficLightsInJunction(
            //                                                          const road::JuncId junc_id) const;



            // void ApplyColorTextureToObject(
            //                                const std::string &actor_name,
            //                                const rpc::MaterialParameter& parameter,
            //                                const rpc::TextureColor& Texture);

            // void ApplyColorTextureToObjects(
            //                                 const std::vector<std::string> &objects_names,
            //                                 const rpc::MaterialParameter& parameter,
            //                                 const rpc::TextureColor& Texture);

            // void ApplyFloatColorTextureToObject(
            //                                     const std::string &actor_name,
            //                                     const rpc::MaterialParameter& parameter,
            //                                     const rpc::TextureFloatColor& Texture);

            // void ApplyFloatColorTextureToObjects(
            //                                      const std::vector<std::string> &objects_names,
            //                                      const rpc::MaterialParameter& parameter,
            //                                      const rpc::TextureFloatColor& Texture);

            // void ApplyTexturesToObject(
            //                            const std::string &actor_name,
            //                            const rpc::TextureColor& diffuse_texture,
            //                            const rpc::TextureFloatColor& emissive_texture,
            //                            const rpc::TextureFloatColor& normal_texture,
            //                            const rpc::TextureFloatColor& ao_roughness_metallic_emissive_texture);

            // void ApplyTexturesToObjects(
            //                             const std::vector<std::string> &objects_names,
            //                             const rpc::TextureColor& diffuse_texture,
            //                             const rpc::TextureFloatColor& emissive_texture,
            //                             const rpc::TextureFloatColor& normal_texture,
            //                             const rpc::TextureFloatColor& ao_roughness_metallic_emissive_texture);

            std::vector<std::string> GetNamesOfAllObjects() const {
                return inner_.GetNamesOfAllObjects();
            }


        private:
            World inner_;
        };

        class FfiClient {
        public:
            explicit FfiClient(const std::string &host,
                               uint16_t port,
                               size_t worker_threads = 0u)
                : inner_(host, port, worker_threads)
            {}

            FfiClient(const Client &&base)
                : inner_(base)
            {}

            size_t GetTimeout() {
                return inner_.GetTimeout().milliseconds();
            }

            void SetTimeout(size_t millis) {
                inner_.SetTimeout(time_duration::milliseconds(millis));
            }


            std::string GetClientVersion() const {
                return inner_.GetClientVersion();
            }

            std::string GetServerVersion() const {
                return inner_.GetServerVersion();
            }


            std::vector<std::string> GetAvailableMaps() const {
                return inner_.GetAvailableMaps();
            }

            FfiWorld ReloadWorld(bool reset_settings = true) const {
                auto world = inner_.ReloadWorld(reset_settings);
                return FfiWorld(std::move(world));
            }

            FfiWorld LoadWorld(std::string map_name,
                               bool reset_settings = true) const
            {
                auto map_layers = MapLayer::All;
                auto world = inner_.LoadWorld(map_name, reset_settings, map_layers);
                return FfiWorld(std::move(world));
            }

            FfiWorld GenerateOpenDriveWorld(std::string opendrive,
                                            const OpendriveGenerationParameters & params,
                                            bool reset_settings = true) const
            {
                auto world = inner_.GenerateOpenDriveWorld(opendrive, params, reset_settings);
                return FfiWorld(std::move(world));
            }

            FfiWorld GetWorld() const {
                auto world = inner_.GetWorld();
                return FfiWorld(std::move(world));
            }

        private:
            Client inner_;
        };
    }
}
