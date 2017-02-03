#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H


class Input_Manager
{
public:
    Input_Manager() = default;
    virtual ~Input_Manager() = default;
    virtual void readInput();
};

#endif // INPUT_MANAGER_H
