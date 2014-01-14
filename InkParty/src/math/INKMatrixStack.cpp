/* ***********************************************************************
	INKMatrixStack.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "math/INKMatrixStack.h"

#include <gtc/matrix_transform.hpp>

INKMatrixStack::INKMatrixStack(){
        m_Stack.push(glm::mat4(1.f));
}

INKMatrixStack::~INKMatrixStack(){
        
}

void INKMatrixStack::push(){
        m_Stack.push(m_Stack.top());
}

void INKMatrixStack::pop(){
        m_Stack.pop();
}

void INKMatrixStack::mult(const glm::mat4& m){
        m_Stack.top() = m_Stack.top()*m;
}

const glm::mat4 INKMatrixStack::top() const{
        return m_Stack.top();
}

void INKMatrixStack::set(const glm::mat4& m){
        m_Stack.top() = m;
}

void INKMatrixStack::scale(const glm::vec3& s){
        m_Stack.top() = glm::scale(m_Stack.top(), s);
}

void INKMatrixStack::translate(const glm::vec3& t){
        m_Stack.top() = glm::translate(m_Stack.top(), t);
}

void INKMatrixStack::rotate(float degrees, const glm::vec3& r){
        m_Stack.top() = glm::rotate(m_Stack.top(), degrees, r);
}