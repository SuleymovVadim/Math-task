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
    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const 
    { 
        eq.solve(x1, x2);
        return true; 
    }
};

class AverageStudent : public Student 
{
public:
    AverageStudent(const string& _name) : Student(_name) {} 
    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const 
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
    virtual bool solveEquation(const QuadraticEquation& eq, double& x1, double& x2) const 
    { 
        x1 = x2 = 0; 
        return false;
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

int main() 
{
    queue<QuadraticEquation> equations;
    readEquationsFromFile(equations, "input.txt");

    
    const GoodStudent gs("Ivan");
    const AverageStudent as("Masha"); 
    const PoorStudent ps("Oleg"); 

    int goodCount = 0, averageCount = 0, poorCount = 0;

    
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

    cout << "Student  Number of solved problems" << endl;
    cout << gs.getName() << "        " << goodCount << endl;
    cout << as.getName() << "       " << averageCount << endl; 
    cout << ps.getName() << "        " << poorCount << endl; 

    return 0;
}