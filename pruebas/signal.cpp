#include <iostream>
#include <csignal>
#include <unistd.h>


using namespace std;

void signalHandler( int signum ) {
    cout << "\nInterrupt signal (" << signum << ") received.\n";

    // cleanup and close up stuff here  
    // terminate program  

    exit(signum);  
}

void loop (){
    while(1) {
        cout << "Going to sleep...." << endl;
        usleep(1000000);
    }
}
int main () {
    // register signal SIGINT and signal handler  
    signal(SIGINT, signalHandler);  
    loop();
    return 0;
}