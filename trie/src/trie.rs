
use std::collections::HashMap;

/*
pub trait ITrieNode {
    fn new(c: char, is_final: bool) -> TrieNode;
    fn new_root() -> TrieNode;
    fn check_value(self, c: char) -> bool;
    fn insert_value(&mut self, c: char, is_final: bool);
}
*/

pub struct TrieNode {
    value: Option<char>,
    is_final: bool,
    child_nodes: HashMap<char, TrieNode>
}

impl TrieNode {
    fn new(c: char, is_final: bool) -> TrieNode {
        TrieNode {
            value: Some(c),
            is_final: is_final,
            child_nodes: HashMap::new()
        }
    }

    fn new_root() -> TrieNode {
        TrieNode {
            value: None,
            is_final: false,
            child_nodes: HashMap::new()
        }
    }

    fn check_value(self, c: char) -> bool {
        self.value == Some(c)
    }

    fn insert_value(&mut self, c: char, is_final: bool) {
        self.child_nodes.insert(c, TrieNode::new(c, is_final));
    }
}