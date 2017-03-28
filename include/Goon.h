#ifndef GOON_H
#define GOON_H

class Goon final
{
public:
    Goon() = default;
    virtual ~Goon() = default;

    Goon& operator=(const bool& other) {
        mGoon = other;
        return *this;
    }

    static void stop() {
        mGoon = false;
    }

    explicit operator bool() const {
        return mGoon;
    }

    bool operator!() const {
        return !mGoon;
    }

private:
    static bool mGoon;
};

#endif // GOON_H
