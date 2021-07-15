#pragma once

class Response
{
public:
    enum CODE {BACK, REDIRECT, RENDER};
private:
    CODE code;
public:
    Response(CODE code) : code(code) {}

    CODE getCode()
    {
        return code;
    }
};

template <class T>
class ObjectResponse : public Response
{
private:
    T *object;

public:
    ObjectResponse(T *object, Response::CODE code) : Response(code), object(object) {}

    T *getObject()
    {
        return object;
    }
};