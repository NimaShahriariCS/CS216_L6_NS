// Lab #6 Overloading << >> = == + - / Su26
// Nima Shahriari
// Objective: to  practice operator overloading 

#include <iostream>
#include <string>
#include <limits>
using namespace std;

enum MenuOption { DEMO = 1, QUIT };
enum FractionError { ZERO_NUMERATOR = 1, ZERO_DENOMINATOR, NEGATIVE_VALUE, IMPROPER_MIXED_NUMBER, INVALID_DIVISOR, UNKNOWN_ERROR };

class FractionException
{
private:
    FractionError error = UNKNOWN_ERROR;

public:
    explicit FractionException(FractionError newError);

    string getMessage() const;
};

class Fraction
{
private:
    int numerator = DEFAULT_NUMERATOR;
    int denominator = DEFAULT_DENOMINATOR;
    static int count;
    static const int DEFAULT_NUMERATOR = 1;
    static const int DEFAULT_DENOMINATOR = 1;

public:
    Fraction();
    Fraction(const Fraction& rhs);
    Fraction(int newNumerator);
    Fraction(int newNumerator, int newDenominator);
    Fraction(int newWhole, int newNumerator, int newDenominator);
    ~Fraction();

    void setFraction(int newNumerator);
    void setFraction(int newNumerator, int newDenominator);
    void setFraction(int newWhole, int newNumerator, int newDenominator);

    int getNumerator() const;
    int getDenominator() const;
    string toString() const;
    void print() const;
    static int getCount();

    Fraction& operator=(const Fraction& rhs);
    bool operator==(const Fraction& rhs) const;
    Fraction operator+(const Fraction& rhs) const;
    Fraction operator-(const Fraction& rhs) const;
    Fraction operator-(int rhs) const;
    Fraction operator/(double rhs) const;

    friend Fraction operator+(int lhs, const Fraction& rhs);
    friend ostream& operator<<(ostream& output, const Fraction& rhs);
    friend istream& operator>>(istream& input, Fraction& rhs);
};

void displayMenu();
void clearCin(string errorMessage);
void demonstrateOperators();

int main()
{
    int menuChoice = 0;

    do
    {
        displayMenu();
        cin >> menuChoice;

        switch (menuChoice)
        {
        case DEMO:
            demonstrateOperators();
            break;

        case QUIT:
            cout << "\nProgram ended." << endl;
            break;

        default:
            clearCin("Invalid menu choice. Select from the menu above.");
        }
    } while (menuChoice != QUIT);

    return 0;
}

int Fraction::count = 0;

FractionException::FractionException(FractionError newError)
{
    error = newError;
}

string FractionException::getMessage() const
{
    string message = "Unknown fraction error.";

    switch (error)
    {
    case ZERO_NUMERATOR:
        message = "The numerator cannot be zero. The fraction was not changed.";
        break;

    case ZERO_DENOMINATOR:
        message = "The denominator cannot be zero. The fraction was not changed.";
        break;

    case NEGATIVE_VALUE:
        message = "Whole numbers, numerators, and denominators cannot be negative. The fraction was not changed.";
        break;

    case IMPROPER_MIXED_NUMBER:
        message = "The numerator cannot be greater than the denominator when the whole number is greater than zero. The fraction was not changed.";
        break;

    case INVALID_DIVISOR:
        message = "The divisor must be greater than zero. The fraction was not changed.";
        break;

    default:
        message = "An unknown fraction error occurred. The fraction was not changed.";
    }

    return message;
}

Fraction::Fraction()
{
    ++count;
    setFraction(0, DEFAULT_NUMERATOR, DEFAULT_DENOMINATOR);
}

Fraction::Fraction(const Fraction& rhs)
{
    ++count;
    setFraction(0, rhs.numerator, rhs.denominator);
}

Fraction::Fraction(int newNumerator)
{
    ++count;
    setFraction(0, newNumerator, DEFAULT_DENOMINATOR);
}

Fraction::Fraction(int newNumerator, int newDenominator)
{
    ++count;
    setFraction(0, newNumerator, newDenominator);
}

Fraction::Fraction(int newWhole, int newNumerator, int newDenominator)
{
    ++count;
    setFraction(newWhole, newNumerator, newDenominator);
}

Fraction::~Fraction()
{
    numerator = 0;
    denominator = DEFAULT_DENOMINATOR;
    --count;
}

void Fraction::setFraction(int newNumerator)
{
    setFraction(0, newNumerator, DEFAULT_DENOMINATOR);
}

void Fraction::setFraction(int newNumerator, int newDenominator)
{
    setFraction(0, newNumerator, newDenominator);
}

void Fraction::setFraction(int newWhole, int newNumerator, int newDenominator)
{
    int possibleNumerator = numerator;
    int possibleDenominator = denominator;

    try
    {
        if (newWhole < 0 || newNumerator < 0 || newDenominator < 0)
            throw FractionException(NEGATIVE_VALUE);

        if (newNumerator == 0)
            throw FractionException(ZERO_NUMERATOR);

        if (newDenominator == 0)
            throw FractionException(ZERO_DENOMINATOR);

        if (newWhole > 0 && newNumerator > newDenominator)
            throw FractionException(IMPROPER_MIXED_NUMBER);

        possibleNumerator = newWhole * newDenominator + newNumerator;
        possibleDenominator = newDenominator;
        numerator = possibleNumerator;
        denominator = possibleDenominator;
    }
    catch (const FractionException& error)
    {
        cout << "\n" << error.getMessage() << endl;
    }
    catch (...)
    {
        FractionException error(UNKNOWN_ERROR);
        cout << "\n" << error.getMessage() << endl;
    }
}

int Fraction::getNumerator() const
{
    return numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

string Fraction::toString() const
{
    int whole = numerator / denominator;
    int remainder = numerator % denominator;
    string fractionString = "n/a";

    if (whole > 0 && remainder > 0)
        fractionString = to_string(whole) + " " + to_string(remainder) + "/" + to_string(denominator);
    else if (whole > 0)
        fractionString = to_string(whole);
    else
        fractionString = to_string(remainder) + "/" + to_string(denominator);

    return fractionString;
}

void Fraction::print() const
{
    cout << toString();
}

int Fraction::getCount()
{
    return count;
}

Fraction& Fraction::operator=(const Fraction& rhs)
{
    if (this != &rhs)
        setFraction(0, rhs.numerator, rhs.denominator);

    return *this;
}

bool Fraction::operator==(const Fraction& rhs) const
{
    bool equalFractions = numerator * rhs.denominator == rhs.numerator * denominator;

    return equalFractions;
}

Fraction Fraction::operator+(const Fraction& rhs) const
{
    int newNumerator = numerator * rhs.denominator + rhs.numerator * denominator;
    int newDenominator = denominator * rhs.denominator;
    Fraction result(newNumerator, newDenominator);

    return result;
}

Fraction Fraction::operator-(const Fraction& rhs) const
{
    int newNumerator = numerator * rhs.denominator - rhs.numerator * denominator;
    int newDenominator = denominator * rhs.denominator;
    Fraction result(newNumerator, newDenominator);

    return result;
}

Fraction Fraction::operator-(int rhs) const
{
    int newNumerator = numerator - rhs * denominator;
    Fraction result(newNumerator, denominator);

    return result;
}

Fraction Fraction::operator/(double rhs) const
{
    const int TENTHS_MULTIPLIER = 10;
    const double ROUNDING_OFFSET = 0.5;
    Fraction result;

    try
    {
        if (rhs <= 0.0)
            throw FractionException(INVALID_DIVISOR);

        int roundedTenths = static_cast<int>(rhs * TENTHS_MULTIPLIER + ROUNDING_OFFSET);
        int newNumerator = numerator * TENTHS_MULTIPLIER;
        int newDenominator = denominator * roundedTenths;
        result.setFraction(newNumerator, newDenominator);
    }
    catch (const FractionException& error)
    {
        cout << "\n" << error.getMessage() << endl;
    }
    catch (...)
    {
        FractionException error(UNKNOWN_ERROR);
        cout << "\n" << error.getMessage() << endl;
    }

    return result;
}

Fraction operator+(int lhs, const Fraction& rhs)
{
    int newNumerator = lhs * rhs.denominator + rhs.numerator;
    Fraction result(newNumerator, rhs.denominator);

    return result;
}

ostream& operator<<(ostream& output, const Fraction& rhs)
{
    output << rhs.toString();

    return output;
}

istream& operator>>(istream& input, Fraction& rhs)
{
    int newNumerator = 0;
    int newDenominator = 0;

    input >> newNumerator >> newDenominator;

    if (input)
        rhs.setFraction(newNumerator, newDenominator);

    return input;
}

void displayMenu()
{
    cout << "\n\nMenu:\n"
            "1. Demonstrate overloaded operators\n"
            "2. Quit\n"
            "Select from the menu above: ";
}

void clearCin(string errorMessage)
{
    if (cin.fail())
        cin.clear();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n" << errorMessage << endl;
}

void demonstrateOperators()
{
    const int FIRST_NUMERATOR = 5;
    const int FIRST_DENOMINATOR = 6;
    const int SECOND_NUMERATOR = 10;
    const int SECOND_DENOMINATOR = 20;
    const int THIRD_NUMERATOR = 3;
    const int THIRD_DENOMINATOR = 7;
    const int FOURTH_NUMERATOR = 5;
    const int FOURTH_DENOMINATOR = 9;
    const int WHOLE_NUMBER = 5;
    const int SUBTRACTED_INTEGER = 1;
    const int IMPROPER_NUMERATOR = 7;
    const int IMPROPER_DENOMINATOR = 3;
    const int EQUAL_NUMERATOR = 1;
    const int EQUAL_DENOMINATOR = 2;
    const double DIVISOR = 5.78;
    Fraction fractionOne(FIRST_NUMERATOR, FIRST_DENOMINATOR);
    Fraction fractionTwo(SECOND_NUMERATOR, SECOND_DENOMINATOR);
    Fraction fractionThree(THIRD_NUMERATOR, THIRD_DENOMINATOR);
    Fraction fractionFour(FOURTH_NUMERATOR, FOURTH_DENOMINATOR);
    Fraction fractionFive(IMPROPER_NUMERATOR, IMPROPER_DENOMINATOR);
    Fraction assignedFraction;
    Fraction equalFraction(EQUAL_NUMERATOR, EQUAL_DENOMINATOR);

    cout << "\n\nOverloaded operator demonstration\n"
            "---------------------------------" << endl;
    cout << "Fraction objects currently in memory: " << Fraction::getCount() << endl;
    cout << "operator << : fractionOne => " << fractionOne << endl;

    assignedFraction = fractionOne;
    cout << "operator =  : assignedFraction = fractionOne => " << assignedFraction << endl;
    cout << "operator == : 10/20 == 1/2 => " << (fractionTwo == equalFraction ? "true" : "false") << endl;
    cout << "operator == : 5/6 == 3/7 => " << (fractionOne == fractionThree ? "true" : "false") << endl;
    cout << "operator +  : fr(5/6) + fr(10/20) => " << fractionOne + fractionTwo << endl;
    cout << "operator +  : 5 + fr(3/7) => " << WHOLE_NUMBER + fractionThree << endl;
    cout << "operator -  : fr(5/6) - fr(3/7) => " << fractionOne - fractionThree << endl;
    Fraction invalidDifference = fractionThree - fractionFour;
    cout << "operator -  : fr(3/7) - fr(5/9) => " << invalidDifference << " (default after rejected negative result)" << endl;
    cout << "operator -  : fr(7/3) - 1 => " << fractionFive - SUBTRACTED_INTEGER << endl;
    cout << "operator /  : fr(3/7) / 5.78 => " << fractionThree / DIVISOR << endl;
    cout << "operator >> is implemented for input in numerator denominator format.\n"
            "It is not called in this demo because the required test values are hard-coded." << endl;
}

/*
Test Run 1
----------
Menu:
1. Demonstrate overloaded operators
2. Quit
Select from the menu above: 1

Overloaded operator demonstration
---------------------------------
Fraction objects currently in memory: 7
operator << : fractionOne => 5/6
operator =  : assignedFraction = fractionOne => 5/6
operator == : 10/20 == 1/2 => true
operator == : 5/6 == 3/7 => false
operator +  : fr(5/6) + fr(10/20) => 1 40/120
operator +  : 5 + fr(3/7) => 5 3/7
operator -  : fr(5/6) - fr(3/7) => 17/42

Whole numbers, numerators, and denominators cannot be negative. The fraction was not changed.
operator -  : fr(3/7) - fr(5/9) => 1 (default after rejected negative result)
operator -  : fr(7/3) - 1 => 1 1/3
operator /  : fr(3/7) / 5.78 => 30/406
operator >> is implemented for input in numerator denominator format.
It is not called in this demo because the required test values are hard-coded.

Menu:
1. Demonstrate overloaded operators
2. Quit
Select from the menu above: abc

Invalid menu choice. Select from the menu above.

Menu:
1. Demonstrate overloaded operators
2. Quit
Select from the menu above: 9

Invalid menu choice. Select from the menu above.

Menu:
1. Demonstrate overloaded operators
2. Quit
Select from the menu above: 2

Program ended.
*/
