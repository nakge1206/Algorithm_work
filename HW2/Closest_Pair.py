import math
import time

def parse_int(s):
    return list(map(int, s.split()))  

def dist(p1, p2):
    result = math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)
    return result

def check_band(S, left, right, d, mid_x):
    sub_list = [p for p in S[left:right + 1] if abs(p[0] - mid_x) < d] 
    sub_list.sort(key=lambda p: p[1])  
    min_dist = d
    closest_pair = None

    for i in range(len(sub_list)):
        for j in range(i + 1, len(sub_list)):
            if sub_list[j][1] - sub_list[i][1] >= min_dist:
                break
            tmp_dist = dist(sub_list[i], sub_list[j])
            if tmp_dist < min_dist:
                min_dist = tmp_dist
                closest_pair = (sub_list[i], sub_list[j])
    
    return min_dist, closest_pair

def closest_pair(S, left, right):
    dots = right - left + 1

    if dots == 2:
        return dist(S[left], S[right]), (S[left], S[right])
    
    elif dots == 3:
        a = dist(S[left], S[left + 1])
        b = dist(S[left + 1], S[right])
        c = dist(S[left], S[right])

        if a <= b and a <= c:
            return a, (S[left], S[left + 1])
        elif b <= a and b <= c:
            return b, (S[left + 1], S[right])
        else:
            return c, (S[left], S[right])
    
    else:
        mid = (left + right) // 2
        mid_x = S[mid][0]  
        a, pair_a = closest_pair(S, left, mid)
        b, pair_b = closest_pair(S, mid + 1, right)
        
        if a < b:
            min_dist = a
            closest_pair_result = pair_a
        else:
            min_dist = b
            closest_pair_result = pair_b
        
        band_dist, band_pair = check_band(S, left, right, min_dist, mid_x)

        if band_dist < min_dist:
            return band_dist, band_pair
        else:
            return min_dist, closest_pair_result

def read_file(filename):
    S = []
    with open(filename, 'r') as file:
        lines = file.readlines()
        for line in lines:
            S.append(parse_int(line.strip()))
    return S

def main():
    filename = "input_closest_pair.txt"  
    S = read_file(filename)  

    start_time = time.time()
    S.sort(key=lambda p: p[0])
    result, pair = closest_pair(S, 0, len(S) - 1)
    end_time = time.time()

    RunningTime = (end_time - start_time) * 1000 
    print(f"최단거리 : {result:.6f}")
    print(f"좌표쌍 : {pair[0]}, {pair[1]}")
    print(f"RunningTime : {RunningTime:.3f} ms")

if __name__ == "__main__":
    main()

