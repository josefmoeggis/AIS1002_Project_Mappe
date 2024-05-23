//
// Created by joelo on 14.05.2023.
//
#include "Graph3D.hpp"
#include "threepp/loaders/STLLoader.hpp"
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

STLLoader loader;
Graph3D testGraph(2000, 200, loader.load("resources/LiftArrow.stl"), 0x00FFFF);

TEST_CASE("Graph setup") {
    CHECK(testGraph.getGridSize() == 2000);
    CHECK(testGraph.getDivisions() == 200);
    CHECK(testGraph.getMesh()->material());
    CHECK(testGraph.getMesh()->geometry());
}

TEST_CASE("Updating vector that stores graph values") {
    for(int i = 0; i < 25; i++) {
        testGraph.updateLineVectors(i, 20);
        CHECK(testGraph.getVectors().back().y == i);
    }
    CHECK(testGraph.getVectors().begin()->y != 0);
    CHECK(testGraph.getVectors().size() == 21);
}

TEST_CASE("Get last graph value and scaling it") {
    CHECK(testGraph.lastGraphVal() == 24);
}

TEST_CASE("Create graph line") {
    auto scene = Scene::create();
    testGraph.updateLineVectors(24, 20);
    testGraph.adjustGraphToFit(2000);
    testGraph.makeLine(scene);
    scene->add(testGraph.getLine());
    CHECK(scene->getObjectByName("LastLine"));
    testGraph.adjustGraphToFit(4000);
    testGraph.makeLine(scene);
    scene->add(testGraph.getLine());
    CHECK(testGraph.getLine()->position.y < 1000);
}





