mod trie;
use trie::*;

fn main() {
    let mut trie_test = TrieStruct::create();

    trie_test.insert("Test".to_string());
    trie_test.insert("Tea".to_string());
    trie_test.insert("Background".to_string());
    trie_test.insert("Back".to_string());
    trie_test.insert("Brown".to_string());

    println!(
        "Is Testing in the trie? {}",
        trie_test.find("Testing".to_string())
    );
    println!(
        "Is Brown in the trie? {}",
        trie_test.find("Brown".to_string())
    );
}
