# ifstream – Input file stream (for reading)
# ofstream – Output file stream (for writing)
# fstream – File stream (for both reading and writing)

Method - 1 :
ifstream inFile("input.txt");                           // Open for reading
ofstream outFile("output.txt");                         // Open for writing
fstream file("file.txt", std::ios::in | std::ios::out); // Both read & write

Method - 2 :
ifstream inFile;
inFile.open("input.txt");

Use file.is_open() to check if the file opened successfully.


# Reading from a File
1. Reading Text Files Line by Line :

    string line;
    while (getline(inFile, line)) {      // this method doesn't ignores the spacing between data
        cout << line << endl;            // if we use datatype of line is string then only it works.
    }

2. Reading Word by Word : 

    string word;
    while (inFile >> word) {            // this method ignores the spacing between data
        cout << word << endl;
    }

3. Reading Numbers :

    int num;
    while (inFile >> num) {          // It only reads number whether string or char is written in txt file.
        cout << "Number: " << num << endl;
    }


4. Reading Mixed Data : 

    string name;
    int age;
    while (inFile >> name >> age) {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    format of data : 
    John 25
    Alice 30

    # Writing to a file

    1. Writing Strings/Numbers :

    outFile << "Hello, world!" << endl;
    outFile << 123 << " " << 45.6 << endl;

5. Reading/Writing (Comma-Separated) :

    string name;
    int age, salary;
    char comma;

    while (inFile >> name >> comma >> age >> comma >> salary) {
        cout << name << " " << age << " " << salary << endl;
    }

A more robust way is to use getline() and then parse using stringstream:

    #include <sstream>

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int age, salary;
        string ageStr, salaryStr;

        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, salaryStr, ',');

        age = stoi(ageStr);
        salary = stoi(salaryStr);

        cout << name << " " << age << " " << salary << endl;
    }


6. Copying from One File to Another : 

    ifstream source("input.txt");
    ofstream dest("output.txt");

    string line;
    while (getline(source, line)) {
        dest << line << endl;
    }


7. Closing Files : 
    inFile.close();
    outFile.close();