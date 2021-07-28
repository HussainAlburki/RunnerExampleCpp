#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

class ScoreInfo {
    protected:
        int distance; // distance in kilometers
        int runningTime; // running time in minutes
    public:
        ScoreInfo() {}

        ScoreInfo(int distance, int runningTime): distance(distance),runningTime(runningTime) {}
        int getDistance() { return distance; }
        int getRunningTime() { return runningTime; }

        //overloading the function to print score information
        friend ostream & operator << (ostream &out, ScoreInfo &scoreInfo) {
            out <<"Distance (km): "<< scoreInfo.distance << " Running Time (minutes): "<< scoreInfo.runningTime << endl;   //outputting the information stored
            return out;        //returning out to cout 
       }
};

class Runner {
    private:
        string name;
        LinkedList<ScoreInfo> previousRuns; // A list of previous runs (ScoreInfo objects)
        float bestAvgRunningTime = 0; // Best Average Running Time for 1km for all time (float seconds).
    public:
        Runner() {}

        Runner(string name) {
            this->name = name;
        }

        string getName() { return name; }

        LinkedList<ScoreInfo> getPreviousRuns() { return previousRuns; }

        float getBestAvgRunningTime() { return bestAvgRunningTime; }
        
// inserting previous Run inforamtion into Linked list , calculating the average time and checking and updating the Best average each time
        void addPreviousRun(ScoreInfo &run) {
            previousRuns.insertLast(run);
            float avgRunningTime =1/((float)run.getDistance()/(float)run.getRunningTime()) ;

            if (avgRunningTime > bestAvgRunningTime) {
                bestAvgRunningTime = avgRunningTime;
            }
        }
};

int main() {
    int runnersNum; // Number of runners
	cout << "How many Runner information will you enter (Max 10): "; //asking the user to get the information 
    cin >> runnersNum;

    Runner runners[runnersNum];//creating an array of Runner class of size the number of players entered . 

    string runnerName;  // name of the current runner
    int previousRunsNum;    // Number of previous runs
    int distance;   // distance in km
    int runningTime;    // running time in minutes

    // Read information from input
    for(int i = 0; i < runnersNum; i++) {   // for each runner
        cout << "Name of the Runner " << i+1 << ": ";
        cin >> runnerName;

        Runner runner = Runner(runnerName); // Information of current runner
        cout << "How many previous run does " << runnerName << " have: ";
        cin >> previousRunsNum;

        cout << "Enter " << runnerName << "'s scores" << endl;
        for(int j = 0; j < previousRunsNum; j++ ) {
            cout << "Run " << j+1 << ": " << endl;
            cout << "Distance(km): ";
            cin >> distance;
            cout << "Running Time (minutes): ";
            cin >> runningTime;

            ScoreInfo run = ScoreInfo(distance, runningTime); //making an aobject of ScoreInfo and set the values by the constructor function
            runner.addPreviousRun(run); 
        }

        runners[i] = runner;
    }

    // Print information
    for(int i = 0; i < runnersNum; i++) {
        cout << runners[i].getName() << "'s Runs:" << endl;
        cout << runners[i].getPreviousRuns();
    }

    for(int i = 0; i < runnersNum; i++) {
        cout << runners[i].getName() << "'s best average running time for 1 km: " << runners[i].getBestAvgRunningTime() << endl;
    }
}

