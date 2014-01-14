/* ***********************************************************************
	INKMatrixStack.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_MATRIX_STACK_H__
#define __INK_MATRIX_STACK_H__

#include <stack>
#include <glm.hpp>

class INKMatrixStack{
public:
    INKMatrixStack();
    ~INKMatrixStack();
    void push();
    void pop();
    void mult(const glm::mat4& m);
    const glm::mat4 top() const;
    void set(const glm::mat4& m);
    void scale(const glm::vec3& s);
    void translate(const glm::vec3& t);
    void rotate(float degrees, const glm::vec3& r);
        
private:
    std::stack<glm::mat4> m_Stack;
};

#endif //__INK_MATRIX_STACK_H__