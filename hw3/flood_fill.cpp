#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Point{
    int x, y, time;
}point;

void print_room(char** room, int n, int m){
    cout << "\n";
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < m+1; j++)
            cout << room[i][j];
        cout << endl;
    }
    cout << "\n";
}

int main(){
    int n, m;
    cin >> n >> m;
    char** room = new char*[n+2];

    int fill = 0; // record how many floor is lava or obstacles

    point bed, door;
    queue<point> lava;

    for (int i = 0; i < (n+2); i++){
        room[i] = new char[m+2];
        for (int j = 0; j < (m+2); j++){
            if (i == 0 || i == n+1 || j == 0 || j == m+1){   // make boundary
                room[i][j] = 'O';
                continue;
            }
            else{
                cin >> room[i][j];
                if (room[i][j] != 'C')
                    fill++;
            }
            point tmp;
            tmp.x = i; tmp.y = j;

            switch (room[i][j]){
                case 'L':
                    room[i][j] = '0';
                    tmp.time = 1;
                    lava.push(tmp);
                    break;
                case 'D':
                    door = tmp;
                    break;
                case 'B':
                    bed = tmp;
                    break;
                default:
                    break;
            }
        }
    }

    // flood fill
    int time = 2;
    point next;
    while (!lava.empty() && n*m > fill){
        bool flag = false;

        while (n*m > fill){
            point curr = lava.front();
            lava.pop();

            // Check all adjacent points 下上右左
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};

            for (int i = 0; i < 4; i++){
                int nx = curr.x + dx[i];
                int ny = curr.y + dy[i];

                // Check is valid
                if (room[nx][ny] == 'C'){
                    room[nx][ny] = curr.time + 48;
                    lava.push({nx, ny, time});
                    fill++;
                    
                    if (!flag)
                        next = {nx, ny};
                    flag = true;
                }
            }

            if (next.x == lava.front().x && next.y == lava.front().y){
                time++;
                break;
            }
        }
        print_room(room, n, m);
    }
    return 0;
}