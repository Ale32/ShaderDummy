#pragma once

#include "glm/glm.hpp"

#include <vector>
#include <functional>


namespace test {

    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnImGuiRender() {}
        virtual void OnRender() {}
        virtual void OnRender(const glm::mat4& view, const glm::mat4& projection)
        {
            // If a child class will not implement this, by default the standard one will be called
            this->OnRender();
        }
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTestPointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "Registering test " << name << std::endl;
            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
        }
        
    private:
        Test*& m_CurrentTest; 
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}
