//
// Created by yarik on 05.04.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_COMPOSITE_FLOAT_H
#define CMAKE_INSTALL_CMAKE_COMPOSITE_FLOAT_H

#include <cmath>

class CompositeFloat{
public:
    CompositeFloat();
    explicit CompositeFloat(double l);
    CompositeFloat(long long int w, double f);

    explicit operator double() const;
    CompositeFloat operator+(CompositeFloat const& other) const;
    CompositeFloat operator+=(CompositeFloat const& other);
    CompositeFloat operator-(CompositeFloat const& other) const;
    CompositeFloat operator-=(CompositeFloat const& other);
    CompositeFloat operator*(CompositeFloat const& other) const;
    CompositeFloat operator*=(CompositeFloat const& other);

    [[nodiscard]] long long int getWholePart() const;
    [[nodiscard]] double getFraction() const;
    [[nodiscard]] double getAsSingleNumber() const;

private:
    void normalize();

    long long int wholePart;
    double fraction;
};

CompositeFloat::CompositeFloat() {
    wholePart = 0;
    fraction = 0;
}

CompositeFloat::CompositeFloat(double l) {
    wholePart = 0;
    fraction = l;
    normalize();
}

long long int CompositeFloat::getWholePart() const {
    return wholePart;
}

double CompositeFloat::getFraction() const {
    return fraction;
}

void CompositeFloat::normalize() {
    long long int diff = floor(fraction);
    wholePart += diff;
    fraction -= static_cast<double>(diff);
}

CompositeFloat::operator double() const {
    return getAsSingleNumber();
}

[[maybe_unused]] double CompositeFloat::getAsSingleNumber() const {
    return static_cast<double>(wholePart) + fraction;
}

CompositeFloat CompositeFloat::operator+(CompositeFloat const &other) const{
    long long int w1 = wholePart, w2 = other.wholePart, w3;
    double f1 = fraction, f2 = other.fraction, f3;
    w3 = w1 + w2;
    f3 = f1 + f2;

    long long int diff = floor(f3);
    w3 += diff;
    f3 -= static_cast<double>(diff);

    return {w3,f3};
}

CompositeFloat CompositeFloat::operator+=(const CompositeFloat &other) {
    *this = *this + other;
    return *this;
}

CompositeFloat CompositeFloat::operator-(CompositeFloat const &other) const{
    long long int w1 = wholePart, w2 = other.wholePart, w3;
    double f1 = fraction, f2 = other.fraction, f3;
    w3 = w1 - w2;
    f3 = f1 - f2;

    long long int diff = floor(f3);
    w3 += diff;
    f3 -= static_cast<double>(diff);

    return {w3,f3};
}

CompositeFloat CompositeFloat::operator-=(const CompositeFloat &other) {
    *this = *this - other;
    return *this;
}

CompositeFloat CompositeFloat::operator*(CompositeFloat const &other) const{
    long long int w1 = wholePart, w2 = other.wholePart, w3;
    double f1 = fraction, f2 = other.fraction, f3;
    auto w1f2 = static_cast<double>(w1) * f2, w2f1 = static_cast<double>(w2) * f1;
    w3 = w1 * w2 +
         static_cast<long long int>(floor(w1f2)) +
         static_cast<long long int>(floor(w2f1));

    f3 = f1 * f2 +
         (w1f2 - floor(w1f2)) +
         (w2f1 - floor(w2f1));

    long long int diff = floor(f3);
    w3 += diff;
    f3 -= static_cast<double>(diff);

    return {w3,f3};
}
CompositeFloat CompositeFloat::operator*=(const CompositeFloat &other) {
    *this = *this * other;
    return *this;
}
CompositeFloat::CompositeFloat(long long int w, double f) {
    wholePart = w;
    fraction = f;
}



#endif //CMAKE_INSTALL_CMAKE_COMPOSITE_FLOAT_H
