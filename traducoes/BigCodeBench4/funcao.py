from collections import Counter
import itertools

def task_func(d):
    count_dict = Counter(itertools.chain.from_iterable(d.values()))
    return dict(count_dict)