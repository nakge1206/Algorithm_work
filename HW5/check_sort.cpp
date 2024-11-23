#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file1("insertion_output.txt");
    std::ifstream file2("radix_msd_output.txt");

    // 파일을 열 수 있는지 확인
    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return 1;  // 파일 열기 실패 시 종료
    }

    std::string line1, line2;
    bool areFilesSame = true;
    int lineNumber = 0;

    // 두 파일을 한 줄씩 읽어서 비교
    while (true) {
        lineNumber++;
        
        // 각각의 파일에서 한 줄을 읽는다.
        bool file1End = !std::getline(file1, line1);
        bool file2End = !std::getline(file2, line2);

        // 두 파일이 동시에 끝에 도달하면 종료
        if (file1End && file2End) {
            break;
        }

        // 두 파일 중 하나만 끝에 도달하면 다르다는 의미
        if (file1End || file2End || line1 != line2) {
            areFilesSame = false;
            std::cout << "파일이 " << lineNumber << "번째 줄에서 다릅니다." << std::endl;
            break;
        }
    }

    if (areFilesSame) {
        std::cout << "두 파일은 동일합니다." << std::endl;
    }

    file1.close();
    file2.close();

    return 0;
}

