use std::collections::VecDeque;

pub struct BinaryTree<T> {
    pub value: T,
    pub left: Option<Box<BinaryTree<T>>>,
    pub right: Option<Box<BinaryTree<T>>>,
}

// creating a root node
impl<T> BinaryTree<T> {
    pub fn new(value: T) -> Self {
        BinaryTree {
            value,
            left: None,
            right: None,
        }
    }

    // inserted value into left node of tree
    pub fn left(mut self, node: BinaryTree<T>) -> Self {
        self.left = Some(Box::new(node));
        self
    }

    // inserted value into right node of tree
    pub fn right(mut self, node: BinaryTree<T>) -> Self {
        self.right = Some(Box::new(node));
        self
    }

    pub fn insert(&mut self, new_value: T) {
        let mut queue: VecDeque<&mut BinaryTree<T>> = VecDeque::new();
        queue.push_front(self);
    
        loop {
            let BinaryTree {
                ref mut left,
                ref mut right,
                ..
            } = queue.pop_back().unwrap();
    
            match left {
                Some(node) => {
                    queue.push_front(node);
                }
                None => {
                    *left = Some(Box::new(BinaryTree::new(new_value)));
                    return;
                }
            }
    
            match right {
                Some(node) => {
                    queue.push_front(node);
                }
                None => {
                    *right = Some(Box::new(BinaryTree::new(new_value)));
                    return;
                }
            }
        }
    }
}

#[test]
pub fn test_case01() {
    let mut tree = BinaryTree::new(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    assert_eq!(
        tree,
        BinaryTree::new(1)
            .left(
                BinaryTree::new(2)
                    .left(BinaryTree::new(4))
                    .right(BinaryTree::new(5))
            )
            .right(BinaryTree::new(3))
    );

    tree.insert(6);

    assert_eq!(
        tree,
        BinaryTree::new(1)
            .left(
                BinaryTree::new(2)
                    .left(BinaryTree::new(4))
                    .right(BinaryTree::new(5))
            )
            .right(BinaryTree::new(3).left(BinaryTree::new(6)))
    )
}

