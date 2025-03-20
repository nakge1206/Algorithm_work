jobs = {
    "t1": [7, 8],
    "t2": [3, 7],
    "t3": [1, 5],
    "t4": [5, 9],
    "t5": [0, 2],
    "t6": [6, 8],
    "t7": [1, 6]
}

sorted_jobs = sorted(jobs.items(), key=lambda job: (job[1][0], -job[1][1]))

machines = []

def schedule_jobs(jobs):
    for job, (start, end) in sorted_jobs:
        assigned = False
        for machine in machines:
            if all(slot == "" for slot in machine[start:end]):
                for i in range(start, end):
                    machine[i] = job
                assigned = True
                break
        if not assigned:
            new_machine = ["" for _ in range(10)]
            for i in range(start, end):
                new_machine[i] = job
            machines.append(new_machine)

schedule_jobs(jobs)

print("Time     ", end=" ")
for i in range(10):
    print(f"{i:^5}", end=" ")
print()

for idx, machine in enumerate(reversed(machines), start=1):
    print(f"Machine {len(machines) - idx + 1}", end=" ")
    for job in machine:
        print(f"{job:^5}", end=" ")
    print()

