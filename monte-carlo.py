import random
import time
import math
from concurrent.futures import ProcessPoolExecutor

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def simplify_score(a, b):
    g = gcd(a, b)
    return (a // g, b // g)

def simulate_game_true_rules(winning_score_n, max_rounds=1_000_000):
    current_score = (1, 1)
    rounds = 0
    while rounds < max_rounds:
        if winning_score_n in current_score:
            if (current_score[0] == winning_score_n and current_score[1] == 1) or \
               (current_score[0] == 1 and current_score[1] == winning_score_n):
                break
        rounds += 1
        if random.random() < 0.5:
            new_score = (current_score[0] + 1, current_score[1])
        else:
            new_score = (current_score[0], current_score[1] + 1)
        current_score = simplify_score(*new_score)
    return rounds

def worker(trials, n):
    return [simulate_game_true_rules(n) for _ in range(trials)]

def monte_carlo_parallel(winning_score_n, num_trials=100000, workers=None):
    start = time.time()
    if workers is None:
        import os
        workers = os.cpu_count() or 4

    # split trials evenly across workers
    chunk = num_trials // workers
    chunks = [chunk] * workers
    chunks[-1] += num_trials % workers  # handle remainder

    with ProcessPoolExecutor(max_workers=workers) as executor:
        results = executor.map(worker, chunks, [winning_score_n] * workers)

    # flatten results
    all_rounds = [r for chunk in results for r in chunk]
    avg = sum(all_rounds) / len(all_rounds)

    # compute standard deviation
    mean = avg
    variance = sum((x - mean) ** 2 for x in all_rounds) / (len(all_rounds) - 1)
    std_dev = math.sqrt(variance)

    # compute 95% confidence interval
    z = 1.96  # 95% CI
    margin_of_error = z * (std_dev / math.sqrt(len(all_rounds)))
    ci_lower = mean - margin_of_error
    ci_upper = mean + margin_of_error

    elapsed = time.time() - start
    print(f"Completed {num_trials} trials in {elapsed:.2f} sec using {workers} workers.")
    print(f"Average game length: {avg:.4f}")
    print(f"95% CI: [{ci_lower:.4f}, {ci_upper:.4f}] (±{margin_of_error:.4f})")
    return avg, (ci_lower, ci_upper)

if __name__ == "__main__":
    # change these values
    WINNING_SCORE_N = 15
    NUM_TRIALS = 100000
    monte_carlo_parallel(WINNING_SCORE_N, NUM_TRIALS, workers=8)
