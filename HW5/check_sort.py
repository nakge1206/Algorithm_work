def is_sorted_from_file(file_name):
    try:
        # Step 1: 파일에서 숫자 읽기
        with open(file_name, 'r') as file:
            numbers = [int(line.strip()) for line in file if line.strip()]
        
        # Step 2: 정렬 여부 확인
        is_sorted = all(numbers[i] <= numbers[i + 1] for i in range(len(numbers) - 1))
        return is_sorted
    except Exception as e:
        print(f"Error: {e}")
        return False


# 파일 이름 설정
input_file = "heap_output.txt"

# 정렬 여부 확인
sorted_status = is_sorted_from_file(input_file)
print(f"{input_file}의 정렬 상태: {sorted_status}")