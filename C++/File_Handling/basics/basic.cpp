#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream inputFile("basic.txt");
    if (!inputFile.is_open())
    {
        cout << "Not Opened" << endl;
        return 1;
    }

    cout << "file opened Successfully" << endl;

    int vertexCount = 0;
    int edgeCount = 0;
    int lineNumber = 1;
    string line;

    while (getline(inputFile, line))
    {
        if (lineNumber == 1)
        {
            for (char ch : line)
            {
                if (ch == ',')
                    vertexCount++;
            }
            vertexCount++;
        }
        else if (lineNumber == 2)
        {
            cout << "Edge line: " << line << endl;

            for (int i = 0; i < line.size(); ++i)
            {
                if (line[i] == '{' && i + 1 < line.size() && isdigit(line[i + 1]))
                {
                    string aStr = "", bStr = "";
                    ++i; // move to digit
                    while (i < line.size() && line[i] != ',')
                    {
                        aStr += line[i++];
                    }
                    ++i; // skip comma
                    while (i < line.size() && line[i] != '}')
                    {
                        bStr += line[i++];
                    }

                    int a = stoi(aStr);
                    int b = stoi(bStr);
                    cout << "Extracted edge: {" << a << ", " << b << "}" << endl;
                    edgeCount++;
                }
            }
        }
        lineNumber++;
    }

    cout << "Vertices : " << vertexCount << endl;
    cout << "Edges : " << edgeCount << endl;

    return 0;
}
