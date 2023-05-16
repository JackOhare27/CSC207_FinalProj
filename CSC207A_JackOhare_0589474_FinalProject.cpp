/*
    Student: Jack O'Hare
    ID: 0589474
    Email: jmohare@cn.edu
    Professor: Dr.Hong
    Class: CSC207A

*/
#include <iostream>
#include <windows.h>
#include <fstream>
#include <wchar.h>
#include <string>


using namespace std;
class mp3
{
private:
    
    wstring my_str = L"Hello World";
public:

    LPCWSTR getDirectory();
    void goToMenu();
    bool verifyFile(LPCWSTR str);
};

int main()
{

    bool stillRunning = true, isPaused = false, verifying = true;
    int choice;
    mp3 player;

    //Checks to see if file is real, if not try again
    while (verifying)
    {

        LPCWSTR dir = player.getDirectory();
        if (player.verifyFile(dir))
        {
            //Plays sound and stops loop
            verifying = false;
            PlaySound(dir, NULL, SND_ASYNC);

            //Gives settings and options for user in console
            while (stillRunning)
            {
               player.goToMenu();
               cin >> choice;
               switch (choice)
               {
               case 1: //PAUSE OR PLAY
                {
                    if (isPaused)
                    {
                        PlaySound(dir, NULL, SND_ASYNC);
                        isPaused = false;
                    }
                    else
                    {
                        PlaySound(NULL, 0, 0);
                        isPaused = true;
                    }
                    break;
                }


                case 2: //SWITCH SONGS
                {
                    bool verifying = true;
                    PlaySound(NULL, 0, 0);
                    while (verifying)
                    {
                        dir = player.getDirectory();
                        if (player.verifyFile(dir))
                        {
                            PlaySound(dir, NULL, SND_ASYNC);
                            verifying = false;
                        }
                        else
                        {
                            cout << "Please enter a valid directory" << endl;
                        }
                    }
                    break;
                }
                case 3: //ADD TO FAVORITES
                {
                    //if does not exist create file
                    //if (!player.doesFileExists())

                       wstring ws(dir);
                       string playlistDir = string(ws.begin(), ws.end());
                       ofstream outfile;
                       outfile.open("playlist.txt", ios_base::app);
                       outfile << playlistDir<<endl;
                       outfile.close();
                      
                    break;
                }
                case 4: //SHOW ALL FAVORITES
                {
                    string data;
                    
                    fstream infile;
                    infile.open("playlist.txt");
                    while (getline(infile, data))
                    {
                        cout << data << endl;
                    }
                    break;

                }
                case 5: //EXIT
                {
                    return 0;
                    break;

                }
                default:
                {
                    break;
                }
                }
            }

        }
    else
    {
        cout << "File does not exist, please retry again\n";
    }
    }

    return 0;
}

//Gets the directory of the user and transforms it into correct variable format (LPCWSTR)
LPCWSTR mp3::getDirectory()
{
    cout << "Please paste a wav files directory that you would like to play" << endl;
    cout << "Example: C:\\Users\\Jack\\Desktop\\Music\\nationalanthem.wav \n";
    wcin >> my_str;
    LPCWSTR wide_string; //define an array with size of my_str + 1
    wide_string = my_str.c_str();
    return wide_string;

}

//Displays menu to user
void mp3::goToMenu()
{
    cout << "Song and Menu Controls \n";
    cout << "1: Stop \n";
    cout << "2. Change song \n";
    cout << "3. Save to favorites\n";
    cout << "4. List favorited song directories \n";
    cout << "5. Close program \n";
  
}

//Returns true or false if the file is a .wav and existant
bool mp3::verifyFile(LPCWSTR dir)
{
    //give length of submitted directory
    int n = wcslen(dir);

    ifstream ifile;
    ifile.open(dir);
    //Does it end in .wav?
        if (dir[n-1] == 'v' && dir[n - 2] == 'a' && dir[n - 3] == 'w' && dir[n - 4] == '.')
        {
            //Is file real?
            return (ifile ? true : false);
        }
        else
        {
            cout << "Reason: Incorrect file type \n";
            return false;
        }
}

