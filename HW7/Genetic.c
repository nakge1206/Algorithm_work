#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define CITIES 8 //도시 개수
#define CANDIDATE_NUM 8 //8개의 후보해 선택
#define GENERATION_MAX 1000 //몇새대까지 진행할건지
#define CROSSOVER_RATE 1.0 //교차율
#define MUTATION_RATE 0.01 //돌연변이율

int pos_city[CITIES][2] = {
    {0, 3}, {7, 5}, {6, 0}, {4, 3}, {1, 0}, {5, 3}, {2, 2}, {4, 1}
}; //도시 좌표

char city_name[CITIES] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'
}; //도시 이름

typedef struct { //후보해 구조체
    int path[CITIES]; //경로(다시 처음으로 돌아와야하니까 +1)
    double fitness_value; //적합도
    double pass_distance; //길이
} Generation;

typedef struct {
    Generation population[CANDIDATE_NUM];
    Generation best_individual;
} GA;

double cal_dis(int city1, int city2); //거리계산
double cal_pass(int *path); //pass 길이 계산
void shuffle(int *path, int size); //경로 섞기 위한 셔플
void initial_population(GA *ga); //초기세대 생성
void selection(GA *ga); //선택연산(강의에 있는 룰렛 휠 선택연산사용)
void crossover(GA *ga); //교차연산(사이클 교차연산)
void mutate(GA *ga); //돌연변이연산
void update_population(GA *ga); //세대 업데이트
void cal_ga(GA *ga); //GA시작

int main(){
    srand((unsigned int)time(NULL)); //랜덤 지정

    //세대 생성 후, 연산 시작
    GA ga;
    initial_population(&ga);
    cal_ga(&ga);

    return 0;
}

double cal_dis(int city1, int city2) { //거리계산
    int dx = pos_city[city1][0] - pos_city[city2][0];
    int dy = pos_city[city1][1] - pos_city[city2][1];
    return sqrt(dx * dx + dy * dy);
}

double cal_pass(int *path) { //pass 길이 계산
    double total_distance = 0.0;
    for (int i = 0; i < CITIES - 1; i++) {
        total_distance += cal_dis(path[i], path[i + 1]);
    }
    total_distance += cal_dis(path[CITIES - 1], path[0]);
    return total_distance;
}

void shuffle(int *path, int size) {
    for (int i = size - 1; i > 1; i--) {
        int j = rand() % (i) + 1;
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
    }
}

void initial_population(GA *ga){ //초기세대 생성
    for (int i = 0; i < CANDIDATE_NUM; i++) {
        ga->population[i].path[0] = 0; // A 고정
        for (int j = 1; j < CITIES; j++) {
            ga->population[i].path[j] = j; // 나머지 도시 초기화
        }
        shuffle(ga->population[i].path, CITIES); // 두 번째 도시부터 섞음
        ga->population[i].pass_distance = cal_pass(ga->population[i].path);
        ga->population[i].fitness_value = 1.0 / ga->population[i].pass_distance;
    }
    ga->best_individual = ga->population[0];
}

void selection(GA *ga){//선택연산(강의에 있는 룰렛 휠 선택연산사용)
    double total_fitness = 0.0;
    double probabilities[CANDIDATE_NUM];
    Generation new_population[CANDIDATE_NUM];

    // 전체 적합도 계산
    for (int i = 0; i < CANDIDATE_NUM; i++) {
        total_fitness += ga->population[i].fitness_value;
    }

    // 각 후보해의 누적 확률 계산
    probabilities[0] = ga->population[0].fitness_value / total_fitness;
    for (int i = 1; i < CANDIDATE_NUM; i++) {
        probabilities[i] = probabilities[i - 1] + ga->population[i].fitness_value / total_fitness;
    }

    // 난수를 사용해 후보해 선택
    for (int i = 0; i < CANDIDATE_NUM; i++) {
        double r = (double)rand() / RAND_MAX; // [0, 1] 사이의 난수
        for (int j = 0; j < CANDIDATE_NUM; j++) {
            if (r <= probabilities[j]) {
                new_population[i] = ga->population[j];

                // 디버깅: 선택된 후보해 출력
                // printf("Random value: %.2f -> Candidate %d selected: Path = ", r, j);
                // for (int k = 0; k < CITIES; k++) {
                //     printf("%c ", city_name[ga->population[j].path[k]]);
                // }
                // printf(", Fitness = %.2f\n", ga->population[j].fitness_value);

                break;
            }
        }
    }

    for (int i = 0; i < CANDIDATE_NUM; i++) {
        ga->population[i] = new_population[i];
    }
}

void crossover(GA *ga){ //교차연산(사이클 교차연산)
    for (int i = 0; i < CANDIDATE_NUM / 2; i++) {
        if ((double)rand() / RAND_MAX < CROSSOVER_RATE){
            int parent1_index = i * 2;
            int parent2_index = i * 2 + 1;

            Generation *parent1 = &ga->population[parent1_index];
            Generation *parent2 = &ga->population[parent2_index];

            int cycle[CITIES] = {0}; // 사이클 배열 초기화
            int start = rand() % (CITIES-1) + 1;
            int pos = start;

            // 사이클 생성
            do {
                cycle[pos] = 1;
                int next_val = parent2->path[pos];
                for (int j = 0; j < CITIES; j++) {
                    if (parent1->path[j] == next_val) {
                        pos = j;
                        break;
                    }
                }
            } while (pos != start);

            //후보해 업데이트
            for (int j = 0; j < CITIES; j++) {
                if (cycle[j]) {
                    ga->population[parent1_index].path[j] = parent1->path[j];
                    ga->population[parent2_index].path[j] = parent2->path[j];
                } else {
                    ga->population[parent1_index].path[j] = parent2->path[j];
                    ga->population[parent2_index].path[j] = parent1->path[j];
                }
            }
            ga->population[parent1_index].pass_distance = cal_pass(ga->population[parent1_index].path);
            ga->population[parent1_index].fitness_value = 1.0 / ga->population[parent1_index].pass_distance;

            ga->population[parent2_index].pass_distance = cal_pass(ga->population[parent2_index].path);
            ga->population[parent2_index].fitness_value = 1.0 / ga->population[parent2_index].pass_distance;
        }
    }
}

void mutate(GA *ga){ //돌연변이연산
    for (int i = 0; i < CANDIDATE_NUM; i++) {
        Generation *generation = &ga->population[i];
        for (int j = 1; j < CITIES; j++) { // A는 고정
            if ((double)rand() / RAND_MAX < MUTATION_RATE) {
                int k = rand() % (CITIES - 1) + 1;
                int temp = generation->path[j];
                generation->path[j] = generation->path[k];
                generation->path[k] = temp;
            }
        }
        generation->pass_distance = cal_pass(generation->path);
        generation->fitness_value = 1.0 / generation->pass_distance;
    }
}

void update_population(GA *ga) { // 세대 업데이트
    ga->best_individual = ga->population[0];
    for (int i = 0; i < CANDIDATE_NUM; i++) {
        if (ga->population[i].fitness_value > ga->best_individual.fitness_value) {
            ga->best_individual = ga->population[i];
        }
    }
}

void cal_ga(GA *ga) { // GA 실행
    Generation new_population[CANDIDATE_NUM];
    
    //디버그용
    //
    // printf("Generation 0:\n");
    // for (int i = 0; i < CANDIDATE_NUM; i++) {
    //     printf("  Candidate %d: Distance = %.2f, Path = ", i, ga->population[i].pass_distance);
    //     for (int j = 0; j < CITIES; j++) {
    //         printf("%c ", city_name[ga->population[i].path[j]]);
    //     }
    //     printf("\n");
    // }
    // printf("Best Distance = %.2f\n", ga->best_individual.pass_distance);
    // printf("Best Path: ");
    // for (int i = 0; i < CITIES; i++) {
    //     printf("%c ", city_name[ga->best_individual.path[i]]);
    // }
    // printf("\n");
    //
    // 여기까지

    for (int gen = 0; gen < GENERATION_MAX; gen++) {
        selection(ga); // 선택 연산
        crossover(ga); //후보해에 대해 교차연산 실행(교차율은 내부에서 고려)
        mutate(ga); //각각의 후보해에 대해 돌연변이 연산 실행(돌연변이율은 내부에서 고려)
        update_population(ga); // 세대 업데이트

        // 현재 세대의 모든 후보해 출력(디버그용)
        // printf("Generation %d:\n", gen+1);
        // for (int i = 0; i < CANDIDATE_NUM; i++) {
        //     printf("  Candidate %d: Distance = %.2f, Path = ", i, ga->population[i].pass_distance);
        //     for (int j = 0; j < CITIES; j++) {
        //         printf("%c ", city_name[ga->population[i].path[j]]);
        //     }
        //     printf("\n");
        // }
        // 현재 세대의 최적 경로 출력
        // printf("Best Distance = %.2f\n", ga->best_individual.pass_distance);
        // printf("Best Path: ");
        // for (int i = 0; i < CITIES; i++) {
        //     printf("%c ", city_name[ga->best_individual.path[i]]);
        // }
        // printf("\n");
        //여기까지
    }

    // 최적 경로 출력
    printf("\n%d번째 세대(마지막) 이동순서: ", GENERATION_MAX);
    for (int i = 0; i < CITIES; i++) {
        printf("%c ", city_name[ga->best_individual.path[i]]);
    }
    printf("%c ", city_name[ga->best_individual.path[0]]);
    printf("\n%d번째 세대(마지막) 이동거리: %f\n", GENERATION_MAX, ga->best_individual.pass_distance);
}