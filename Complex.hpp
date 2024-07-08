//oriyai0701@gmail.com
#include <iostream>
#include <string>

/**
 * @brief A class representing complex numbers and supporting basic operations.
 */
class Complex {
public:
    double real;       ///< The real part of the complex number.
    double imaginary;  ///< The imaginary part of the complex number.

    /**
     * @brief Construct a new Complex object.
     *
     * @param real The real part of the complex number.
     * @param imaginary The imaginary part of the complex number.
     */
    Complex(double real, double imaginary) : real(real), imaginary(imaginary) {}

    /**
     * @brief Get the real part of the complex number.
     *
     * @return double The real part of the complex number.
     */
    double getReal() const {
        return real;
    }

    /**
     * @brief Get the imaginary part of the complex number.
     *
     * @return double The imaginary part of the complex number.
     */
    double getImaginary() const {
        return imaginary;
    }

    /**
     * @brief Convert the complex number to a string representation.
     *
     * @return std::string The string representation of the complex number.
     */
    std::string toString() const {
        return std::to_string(real) + " + " + std::to_string(imaginary) + "i";
    }

    /**
     * @brief Output stream operator for printing the complex number.
     *
     * @param os The output stream.
     * @param c The complex number to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.toString();
        return os;
    }

    /**
     * @brief Equality operator to compare two complex numbers.
     *
     * @param other The other complex number to compare with.
     * @return true If the two complex numbers are equal.
     * @return false If the two complex numbers are not equal.
     */
    bool operator==(const Complex& other) const {
        return real == other.real && imaginary == other.imaginary;
    }

    /**
     * @brief Inequality operator to compare two complex numbers.
     *
     * @param other The other complex number to compare with.
     * @return true If the two complex numbers are not equal.
     * @return false If the two complex numbers are equal.
     */
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    /**
     * @brief Less-than operator to compare the magnitude of two complex numbers.
     *
     * @param other The other complex number to compare with.
     * @return true If this complex number has a smaller magnitude than the other.
     * @return false If this complex number does not have a smaller magnitude than the other.
     */
    bool operator<(const Complex& other) const {
        double norm = real * real + imaginary * imaginary;
        double otherNorm = other.real * other.real + other.imaginary * other.imaginary;
        return norm < otherNorm;
    }

    /**
     * @brief Greater-than operator to compare the magnitude of two complex numbers.
     *
     * @param other The other complex number to compare with.
     * @return true If this complex number has a greater magnitude than the other.
     * @return false If this complex number does not have a greater magnitude than the other.
     */
    bool operator>(const Complex& other) const {
        return other < *this;
    }

    /**
     * @brief Less-than-or-equal-to operator to compare the magnitude of two complex numbers.
     *
     * @param other The other complex number to compare with.
     * @return true If this complex number has a smaller or equal magnitude than the other.
     * @return false If this complex number does not have a smaller or equal magnitude than the other.
     */
    bool operator<=(const Complex& other) const {
        return !(*this > other);
    }

    /**
     * @brief Greater-than-or-equal-to operator to compare the magnitude of two complex numbers.
     *
     * @param other The other complex number to compare with.
     * @return true If this complex number has a greater or equal magnitude than the other.
     * @return false If this complex number does not have a greater or equal magnitude than the other.
     */
    bool operator>=(const Complex& other) const {
        return !(*this < other);
    }

};
