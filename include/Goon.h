#ifndef GOON_H
#define GOON_H

class Goon final
{
public:
    Goon() = default;
    virtual ~Goon() = default;

    bool operator()() {
        return mGoon;
    }

    Goon& operator=(const bool& other) {
        mGoon = other;
        return *this;
    }

    static void stop() {
        mGoon = false;
    }

private:
    static bool mGoon;
};

#endif // GOON_H
