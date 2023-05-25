#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstdlib> 
#include <cmath> 

using namespace std;

class QuadraticEquation
{
private:
    double a, b, c;

public:
    QuadraticEquation(double _a = 0, double _b = 0, double _c = 0) : a(_a), b(_b), c(_c) {}

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }

    void solve(double& x1, double& x2) const
    {
        double D = b * b - 4 * a * c;
        if (D < 0)
        {
            x1 = x2 = 0;
        }
        else if (D == 0)
        {
            x1 = x2 = -b / (2 * a);
        }
        else
        {
            x1 = (-b + sqrt(D)) / (2 * a);
            x2 = (-b - sqrt(D)) / (2 * a);
        }
    }
};

class Student
{
protected:
    string name;

public:
    Student(const string& _name) : name(_name) {}

    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const = 0;

    string getName() const { return name; }
};

class GoodStudent : public Student
{
public:
    GoodStudent(const string& _name) : Student(_name) {}

    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const override
    {
        eq.solve(x1, x2);
        return true;
    }
};

class AverageStudent : public Student
{
public:
    AverageStudent(const string& _name) : Student(_name) {}

    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const override
    {
        if (rand() % 2 == 0)
        {
            eq.solve(x1, x2);
            return true;
        }
        else
        {
            return false;
        }
    }
};

class PoorStudent : public Student
{
public:
    PoorStudent(const string& _name) : Student(_name) {}

    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const override
    {
        x1 = x2 = 0;
        return false;
    }
};

class Professor
{
public:
    void countEquations(queue<QuadraticEquation>& equations, int& goodCount, int& averageCount, int& poorCount) const
    {
        GoodStudent gs("Ivan");
        AverageStudent as("Masha");
        PoorStudent ps("Oleg");

        goodCount = 0;
        averageCount = 0;
        poorCount = 0;

        while (!equations.empty())
        {
            double x1 = 0, x2 = 0;
            if (gs.solveEquation(equations.front(), x1, x2))
            {
                goodCount++;
            }
            if (as.solveEquation(equations.front(), x1, x2))
            {
                averageCount++;
            }
            if (ps.solveEquation(equations.front(), x1, x2))
            {
                poorCount++;
            }
            equations.pop();
        }
    }
};

void readEquationsFromFile(queue<QuadraticEquation>& equations, const string& fileName)
{
    ifstream ifs(fileName);
    if (!ifs)
    {
        cerr << "Error opening file: " << fileName << endl;
        exit(1);
    }
    double a, b, c;
    while (ifs >> a >> b >> c)
    {
        equations.push(QuadraticEquation(a, b, c));
    }
    ifs.close();
}

void printResults(int goodCount, int averageCount, int poorCount)
{
    cout << "Student  Number of solved problems" << endl;
    cout << "Ivan        " << goodCount << endl;
    cout << "Masha       " << averageCount << endl;
    cout << "Oleg        " << poorCount << endl;
}

int main()
{
    queue<QuadraticEquation> equations;
    readEquationsFromFile(equations, "input.txt");

    Professor professor;
    int goodCount = 0, averageCount = 0, poorCount = 0;
    professor.countEquations(equations, goodCount, averageCount, poorCount);

    printResults(goodCount, averageCount, poorCount);

    return 0;
}