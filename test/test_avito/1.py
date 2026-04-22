

def find_max_pattern(list_of_nums):
    if not list_of_nums:
        return 0
    
    max_pattern=1
    current_pattern=1
    current_num=list_of_nums[0] 
    for i in list_of_nums[1:]:
        if i==current_num:
            current_pattern+=1
        else:
            max_pattern=max(max_pattern, current_pattern)
            current_num=i
            current_pattern=1
    max_pattern=max(max_pattern, current_pattern)
    return max_pattern

print(find_max_pattern([1, 2, 2, 3, 3, 3, 4]))