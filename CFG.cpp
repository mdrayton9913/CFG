// CFG.cpp : This file contains the 'main' function. Program execution begins and ends there.


//Group: Maximillan Drayton, Jay Chen

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include <cctype>
using std::ifstream;
using namespace std;
int main()
{
    vector<string> lines; //Vector used to store lines of file
    string file_name;
    cout << "Please enter name of file: " << endl;
    cin >> file_name;
    fstream user_file;
    ofstream write_file;
    write_file.open("Simplified CFG.txt");
    user_file.open(file_name);
    if (!user_file)
    {
        cerr << "Error: file cannot be opened" << endl;
        exit(1);
    }
    else
    {
        cout << "File Opened\n";
    }

    string input;
    while (!user_file.eof())
    {
        getline(user_file, input);
        lines.push_back(input);
    }
    int occurences = 0; //Variable used to check if a variable appears or not
    for (int i = 6; i < lines[0].size(); i++) //Loop that searches through the first line of code for every variable and makes sure the variable is actually used and if not, removes all lines that mention that variable
    {
        for (int j = 5; j < lines.size(); j++)
        {
            if (lines[0][i] == lines[j][0] && isupper(lines[0][i]) && lines[0][i] != ' ' && lines[0][i] != ',')
            {
                occurences++;
            }
        }
        //cout << lines[0][i] << " : " << occurences << endl; debugging
        if (occurences == 0 && isupper(lines[0][i]) && lines[0][i] != ' ' && lines[0][i] != ',')
        {
            for (int a = 4; a < lines.size(); a++)
            {
                for (int b = 4; b < lines[a].size(); b++)
                {
                    if (lines[a][b] == lines[0][i])
                    {
                        lines.erase(lines.begin() + a);
                    }
                }
            }

        }
        occurences = 0;
    }
    occurences = 0; //To make sure occurences is at 0
    for (int i = 5; i < lines.size(); i++) //Used to see if a variable is never mentioned in another variable thus making it unreachable
    {
        char target = lines[i][0];
        for (int j = 4; j < lines.size(); j++)
        {
            for (int k = 3; k < lines[j].size(); k++)
            {
                if (lines[j][k] == target)
                {
                    occurences++;
                }
            }
        }
        if (occurences == 0)
        {
            lines.erase(lines.begin() + i);
            i = 5;
        }
        else if (lines[i].back() == target)
        {
            lines.erase(lines.begin() + i);
            i = 5;
            for (int i = 6; i < lines[0].size(); i++) //Loop that searches through the first line of code for every variable and makes sure the variable is actually used and if not, removes all lines that mention that variable
            {
                for (int j = 5; j < lines.size(); j++)
                {
                    if (lines[0][i] == lines[j][0] && isupper(lines[0][i]) && lines[0][i] != ' ' && lines[0][i] != ',')
                    {
                        occurences++;
                    }
                }
                //cout << lines[0][i] << " : " << occurences << endl; debugging
                if (occurences == 0 && isupper(lines[0][i]) && lines[0][i] != ' ' && lines[0][i] != ',')
                {
                    for (int a = 4; a < lines.size(); a++)
                    {
                        for (int b = 4; b < lines[a].size(); b++)
                        {
                            if (lines[a][b] == lines[0][i])
                            {
                                lines.erase(lines.begin() + a);
                            }
                        }
                    }

                }
                occurences = 0;
            }
        }
        else
        {
            occurences = 0;
        }
    }
    //for (int i = 0; i < lines.size(); i++) //Used for debugging
    //{
        //cout << lines[i] << endl;
   // }
    //cout << lines.size() << endl;; Used for debugging
    for (int i = 4; i < lines.size(); i++) //Loops through all lines containing variables and their paths
    {
        //cout << lines[i] << endl; //debugging
        if (islower(lines[i].back())) //if the back letter is lowercase, line should be good since it means it terminates
        {
            //cout << lines[i].back() << endl;  Debugging
        }
        else
        {
            char new_target = lines[i].back(); //if the line is uppercase, we have to check to see if it leads into a termination from another line (Ex: A:aC, C:a), thus we mark C from A: as a target while we check other lines
            //cout << "else " << new_target << endl; Debugging
            for (int j = i + 1; j < lines.size(); j++) //loop used to go to next line and check until we get the target variable
            {
                //cout << j << endl; debugging
                if (lines[j][0] == new_target && j == lines.size() - 1 && isupper(lines[j].back())) //if j is at the last line in the vector and it equals the target and it still does not terminate,
                    //it's safe to remove that line and any lines containing that variable
                {
                    for (int a = 4; a < lines.size(); a++)
                    {
                        //cout << "Lines: " << lines.size() << endl; debugging
                        //cout << "a: " << a << endl; debugging
                        for (int b = 0; b < lines[a].size(); b++)
                        {
                            if (lines[a][b] == new_target)
                            {
                                lines.erase(lines.begin() + a);
                                a = 4;
                            }
                        }
                    }
                }
                else if (lines[j][0] != new_target && j == lines.size() - 1 && isupper(lines[j].back())) //if j is at the last line in the vector and it equals the target and it still does not terminate,
                     //it's safe to remove that line and any lines containing that variable
                {
                    lines.erase(lines.begin() + j);
                }
                else if (lines[j][0] == new_target) //if we reach the target and it's not the last line
                {
                    if (islower(lines[j].back())) //if we get to a lowercase letter at the end of the target line, that means it terminates thus we can break out of this loop
                    {
                        //cout << lines[j].back() << endl; debugging
                        break;
                    }
                    else //after finding a target line it still does not terminatem it means we have a chain of connected variables and need to check even further using a new target
                    {
                        //cout << lines[i][lines[j].size() - 1] << endl;
                        new_target = lines[j].back();
                        //cout << "Hello" << endl;
                        bool unproductive = true; //variable used to check if a line is unproductive or not
                        //cout << "Hello" << endl; debugging
                       while (unproductive == true) //while it is unproductive, we continue using the loop
                        {
                            for (int k = j; k < lines.size(); k++) //k marks the line the target was on and checks from there
                            {
                                if (lines[k][0] == new_target && islower(lines[k].back())) //we reached the end of the chain and found it terminates meaning we can leave the loop since it is not unproductive
                                {
                                    unproductive = false;
                                }
                                else if (k == lines.size() - 1 && unproductive == true) //if we reached the last line of the vector and it is still unproductive, that line must be unproductive thus
                                    //it can be removed and any lines with that variable can be removed
                                {
                                    for (int a = 4; a < lines.size(); a++)
                                    {
                                        for (int b = 4; b < lines[a].size(); b++)
                                        {
                                            if (lines[a][b] == new_target)
                                            {
                                                lines.erase(lines.begin() + a);
                                                a = 4; //reset a to make sure lines were properly parsed
                                            }
                                        }
                                    }

                                }
                                else if (lines[k][0] == new_target && isupper(lines[k].back() && new_target == lines[k].back())) //if the line marked by k is equal to the target, the last character does not terminate
                                    //and it is equal to the target (ex: B: aB) then it is removed for reduncacy
                                {
                                    lines.erase(lines.begin() + k);
                                    k = j; //reset k to make sure the lines have been properly parsed
                                }
                                else if (lines[k][0] != new_target && isupper(lines[k].back())) //if the target is not found and the last letter does not terminate, change target to current line's non-terminate character
                                {
                                    //cout << lines[k].back() << endl; debugging
                                    //cout << k << endl; debugging
                                    unproductive = true;
                                    new_target = lines[k].back();
                                    //cout << lines[k].back() << endl; debugging
                                   // cout << new_target; debugging
                                   
                                }
                            }
                        }

                    } 
                }
                else //do nothing for any other cases
                {

                } 
            }
        } 
    }
    vector<char> first_line; //vector used to store T: line
    vector<char> second_line; //vector used to store S: line
    first_line.push_back(lines[4][0]); //adding starting character to first line
    bool copy = true; //used to check if a variable will be stored twice
    for (int i = 4; i < lines.size(); i++) //loop that checks each variable and determines uniqueness to see if it will be added to first line vector or not
    {
        for (int j = 0; j < first_line.size(); j++)
        {
            if (first_line[j] == lines[i][0])
            {
                copy = true;
            }
            else
            {
                copy = false;
            }
        }
        if (copy == false)
        {
            first_line.push_back(lines[i][0]);
        }
    }
    for (int i = 3; i < lines[1].size(); i++) //adds in characters from second line 
    {
        if (lines[1][i] != ' ' && lines[1][i] != ',')
        {
            second_line.push_back(lines[1][i]);
        } 
    }
    write_file << "V: "; //starting line
    for (int i = 0; i < first_line.size(); i++) //builds V: using first line vector
    {
        write_file << first_line[i] << ", ";
    }
    for (int i = 0; i < second_line.size() - 1; i++) //builds rest of V: using second line vector until the last character
    {
        write_file << second_line[i] << ", ";
    }
    write_file << second_line.back() << endl; //prints out last character in second line vector
    for (int i = 1; i < lines.size(); i++) //prints out final output
    {
 
        write_file << lines[i] << endl;
    }
    user_file.close();
    write_file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
