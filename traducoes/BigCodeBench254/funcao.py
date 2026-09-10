import json
import math


def task_func(decimal_value, precision=2):
    # Calculate the square root of the decimal value
    square_root = round(math.sqrt(decimal_value), 2)
    
    # Encode the result as a JSON string
    json_str = json.dumps(str(square_root))
    
    return json_str