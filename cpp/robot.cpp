#include <iostream>
class Solution {
public:
    int dx[4]{0, 0, -1, 1};
    int dy[4]{1, -1, 0, 0};

    int turnLeft(int d){
        if (d==0) return 2;
        if (d==2) return 1;
        if (d==1) return 3;
        return 0;
    }

    int turnRight(int d){
        if (d==0) return 3;
        if (d==3) return 1;
        if (d==1) return 2;
        return 0;
    }

    bool isRobotBounded(std::string instructions){
        int x, y, direct;
        x = y = direct = 0;
        instructions += instructions + instructions + instructions;
        for (auto c : instructions) {
            if (c=='L')
                direct = turnLeft(direct);
            else if (c=='R')
                direct = turnRight(direct);
            else {
                x += dx[direct];
                y += dy[direct];
            }
        }
        if (x == 0 && y == 0) return true;
        return false;
    }
};

int main() {
    Solution s;
    std::cout << s.isRobotBounded("GG");
}
