use std::collections::HashMap;

pub trait ITrieNode {
    fn new(c: char, is_final: bool) -> TrieNode;
    fn new_root() -> TrieNode;
    fn check_value(self, c: char) -> bool;
    fn insert_value(&mut self, c: char, is_final: bool);
}

pub struct TrieNode {
    value: Option<char>,
    is_final: bool,
    mapchild_nodes: HashMap<char, TrieNode>
}

impl ITrieNode for TrieNode {
    fn new(c: char, is_final: bool) -> TrieNode {
        todo!()
    }

    fn new_root() -> TrieNode {
        todo!()
    }

    fn check_value(self, c: char) -> bool {
        todo!()
    }

    fn insert_value(&mut self, c: char, is_final: bool) {
        todo!()
    }
}