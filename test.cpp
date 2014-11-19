#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

int main(){
    srand(time(0));
    priority_queue <int,vector<int>,greater<int> > q;
    for( int i = 0; i != 100000; ++i ) q.push(rand()%10);
    cout << "Min-heap, popped one by one: ";
    while( ! q.empty() ) {
        //cout << q.top() << ' ';  // 0 3 3 3 4 5 5 6 8 9
        q.pop();
    }
    //cout << endl;
    return 0;
}