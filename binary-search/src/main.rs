
fn main() {
    test(vec![9,5,8,2,6,7,1,5], 1);
    test(vec![9,8,7,6,5,4,3,2,1,0], 123);
    test(vec![1,2,3,4,5], 0);
    test(vec![1,2,3,4,5], 1);
    test(vec![1,2,3,4,5], 2);
    test(vec![1,2,3,4,5], 3);
    test(vec![1,2,3,4,5], 4);
    test(vec![1,2,3,4,5], 5);
    test(vec![1,2,3,4,5], 6);
    test(vec![1,2,3,4,5], 7);
    test(vec![1,2,3,4,5], 8);
    test(vec![1,2,3,4,5], 9);
    test(vec![1,2,3,4,5], 10);
}

fn test(nums: Vec<i32>, target: i32) {
    let mut array = nums.clone();
    array.sort();

    let sorted_vec_str = vec_to_string(&array);
    let result = bin_search(&array, target);

    println!("{} -> {}: {}", sorted_vec_str, target, result);
}

fn vec_to_string(nums: &Vec<i32>) -> String {
    return nums
        .into_iter()
        .map(|c| c.to_string())
        .collect::<Vec<String>>()
        .join(", ");
}

fn bin_search<T: Ord>(nums: &Vec<T>, target: T) -> bool {
    return bin_search_internal(nums, target, 0, nums.len() as i32 - 1);
}

fn bin_search_internal<T: Ord>(nums: &Vec<T>, target: T, first: i32, last: i32) -> bool {
    if first <= last {
        let middle: i32 = ((first + last) / 2) as i32;
        
        if nums[middle as usize] == target {
            return true;
        }
        else if nums[middle as usize] < target {
            return bin_search_internal(nums, target, middle + 1, last);
        }
        else  {
            return bin_search_internal(nums, target, first, middle - 1);
        }
    }
    
    return false;
}
