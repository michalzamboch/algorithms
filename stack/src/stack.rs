
pub struct Stack<T> {
    array: Vec<T>
}

impl<T> Stack<T> {
    pub fn new() -> Self {
        Self { 
            array: Vec::new()
        }
    }

    pub fn empty(&self) -> bool {
        self.array.is_empty()
    }

    pub fn push(&mut self, value: T) {
        self.array.push(value);
    }
    
    pub fn top(&self) -> Option<&T> {
        self.array.last()
    }

    pub fn pop(&mut self) -> Option<T> {
        self.array.pop()
    }

    pub fn len(&self) -> usize {
        self.array.len()
    }

    pub fn capacity(&self) -> usize {
        self.array.capacity()
    }

    pub fn clear(&mut self) {
        self.array.clear();
    }
}