#pragma once
#include <GUI/Scene/Scene2D.h>
#include <GUI/Scene/SceneDepth.h>
#include <GUI/Scene/Scene3D.h>
#include <GUI/Menu/Menu.h>
#include <GUI/Loader/Loader.h>
#include <GUI/Blueprint/Blueprint.h>
#include <GUI/Selection/Selection.h>
#include <GUI/Timeline/Timeline.h>

class GUI{
    private:
        Menu menu;
        Loader loader;
        Scene3D scene3D;
        Scene2D scene2D;
        SceneDepth sceneDepth;
        Blueprint blueprint;
        Selection selection;
        Timeline timeline;
    
    public:
        void Setup();
        void Show();
        void Update();
        void Shutdown();
};