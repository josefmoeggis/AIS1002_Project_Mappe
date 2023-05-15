//
// Created by joelo on 01.05.2023.


#include "../include/SceneSetup.hpp"

std::shared_ptr<DirectionalLight> setLight() {
    auto light = DirectionalLight::create(0xffffff);
    light->position.set(100, 10, 100);
    return light;
}

std::shared_ptr<Sky> setSky(std::shared_ptr<DirectionalLight> light) {
    auto mySky = Sky::create();
    mySky->scale.setScalar(10000);
    mySky->material()->as<ShaderMaterial>()->uniforms->at("turbidity").value<float>() = 10;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("rayleigh").value<float>() = 1;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("mieCoefficient").value<float>() = 0.005;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("mieDirectionalG").value<float>() = 0.8;
    mySky->material()->as<ShaderMaterial>()->uniforms->at("sunPosition").value<Vector3>().copy(light->position);
    return mySky;
}

std::shared_ptr<Mesh> getAirflowArrow(STLLoader loader) {
    auto geometry = loader.load("resources/AirflowArrow.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::lightsteelblue;
    auto arrow = Mesh::create(geometry, material);
    arrow->position.z = -900;
    arrow->position.y = -50;
    arrow->rotateY(math::PI);
    arrow->rotateX(math::PI);
    arrow->rotateZ(math::PI / 2);
    arrow->scale.setScalar(0.5);
    return arrow;
}

std::shared_ptr<AirObject> setupAircraft1(STLLoader loader) {
    auto fuselage = loader.load("resources/B737_800.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::beige;
    auto boeing = AirObject::create(fuselage, material, 40000, 470);
    boeing->setAngleParameters(1.6, 14, 20, 1.3);
    boeing->createMesh();
    boeing->scaleModel(1000);
    boeing->centerModel(1000);
    boeing->getMesh()->rotateY(math::PI);
    boeing->getMesh()->position.y += -100;
    boeing->getMesh()->name = "Boeing";
    return boeing;
}

std::shared_ptr<AirObject> setupAircraft2(STLLoader loader) {
    auto fuselage = loader.load("resources/A320neo.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::silver;
    auto airbus = AirObject::create(fuselage, material, 4000, 470, 0.76, 0.26);
    airbus->setAngleParameters(1.6, 14, 20, 1.3);
    airbus->createMesh();
    airbus->scaleModel(1000);
    airbus->centerModel(1000);
    airbus->getMesh()->name = "Airbus";
    return airbus;
}

std::shared_ptr<AirObject> setupAircraft3(STLLoader loader) {
    auto fuselage = loader.load("resources/Cessna_172.stl");
    auto material = MeshPhongMaterial::create();
    material->flatShading = true;
    material->color = Color::lightskyblue;
    auto cessna = AirObject::create(fuselage, material, 800,
                                    16.17,0.33, 0.035, 0);
    cessna->setAngleParameters(1.5, 12, 18, 1.3);
    cessna->createMesh();
    cessna->scaleModel(700);
    cessna->centerModel(1000);
    cessna->getMesh()->position.z += 500;
    cessna->getMesh()->rotateY(math::PI);
    cessna->getMesh()->name = "Cessna";
    return cessna;
}


void loopAircraft(std::shared_ptr<Group> movementShell,std::shared_ptr<AirObject> aircraftModel1,
                  std::shared_ptr<AirObject> aircraftModel2, std::shared_ptr<AirObject> aircraftModel3, PID pid, float dt) {
    if(!movementShell->getObjectByName(aircraftModel1->getMesh()->name)) {
        if(movementShell->getObjectByName(aircraftModel2->getMesh()->name)) {
//            movementShell->position.z += (10 * pid.regulate(-6000, movementShell->position.z, dt) * dt);
//            if(movementShell->position.z < -4000) {
                movementShell->remove(movementShell->getObjectByName(aircraftModel2->getMesh()->name));
//                movementShell->position.z = 0;
//                movementShell->add(aircraftModel1->getMesh());
//            }
        }
        else if(movementShell->getObjectByName(aircraftModel3->getMesh()->name)) {
//            movementShell->position.z += 10 * pid.regulate(-6000, movementShell->position.z, dt) * dt;
//            if(movementShell->position.z < -4000) {
                movementShell->remove(movementShell->getObjectByName(aircraftModel3->getMesh()->name));
//                movementShell->position.z = 0;
//                movementShell->add(aircraftModel1->getMesh());
//            }
        }
    }
    movementShell->add(aircraftModel1->getMesh());

}


