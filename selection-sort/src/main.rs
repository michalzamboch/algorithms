
fn main() {
    test(vec![9,5,8,2,6,7,1,5]);
    test(vec![9,8,7,6,5,4,3,2,1,0]);
    test(vec![1,2,3]);
}

fn test(nums: Vec<i32>) {
    let mut array = nums.clone();
    select_sort(&mut array);

    let original_vec_str = vec_to_string(&nums);
    let sorted_vec_str = vec_to_string(&array);

    println!("{} -> {}", original_vec_str, sorted_vec_str);
}

fn vec_to_string(nums: &Vec<i32>) -> String {
    return nums
        .into_iter()
        .map(|c| c.to_string())
        .collect::<Vec<String>>()
        .join(", ");
}

fn select_sort(array: &mut [i32]) {
    for i in 0..(array.len() - 1) {
        
        let mut smallest_index = i;
        for j in i..array.len() {
            if array[j] < array[smallest_index] {
                smallest_index = j;
            }
        }

        let tmp = array[smallest_index];
        array[smallest_index] = array[i];
        array[i] = tmp;

    }
}
