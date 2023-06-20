#include <iostream>
#include <stack>
#include <vector>

template <typename T>
class AVLTree {
 public:
  AVLTree() = default;
  ~AVLTree() { delete root_; }

  int Insert(int value);
  void Delete(int value);

 private:
  class Node {
   public:
    Node(T value) : value{value} {}
    Node() = default;
    ~Node() {
      delete right;
      delete left;
    }

    T value{T()};
    int height{1};

    int difference{0};
    Node *left{nullptr};
    Node *right{nullptr};
  };

  int NodeHeight(Node *node);
  void Update(Node *node);
  void SmallLeftRotate(Node *current_node, bool is_complex);
  void SmallRightRotate(Node *current_node, bool is_complex);
  void BigLeftRotate(Node *current_node);
  void BigRightRotate(Node *current_node);
  void BalanceInsert(std::stack<Node *> &node_path);
  void BalanceDelete(std::stack<Node *> &node_path, int child);
  void Delete(Node *node, std::stack<Node *> &node_path, int &last);

  Node *root_;
};

template <typename T>
int AVLTree<T>::Insert(int value) {
  int order = 0;
  if (!root_) {
    root_ = new Node{value};
    return order;
  }

  auto current = root_;
  std::stack<Node *> node_path;

  while (current) {
    node_path.push(current);
    ++current->height;

    if (value < current->value) {
      if (!current->left) {
        order += current->height - 1;
        current->left = new Node{value};
        node_path.push(current->left);
        break;
      } else {
        order += current->height - current->left->height - 1;
      }
      current = current->left;
    } else {
      if (!current->right) {
        current->right = new Node{value};
        node_path(current->right);
        break;
      }
      current = current->right;
    }
  }
  BalanceInsert(node_path);
  return order;
}

template <typename T>
void AVLTree<T>::Delete(int height) {
  Node *current = root_;
  if (!root_) return;
  if (height >= root_->height) {
    return;
  }

  std::stack<Node *> node_path;

  while (true) {
    node_path.push(current);
    if (current->height - NodeValue(current->left) - 1 == height)
      break;
    else if (height < NodeValue(current->right)) {
      --current->height;
      current = current->right;
    } else {
      height -= current->height - NodeValue(current->left);
      --current->number;
      current = current->left;
    }
  }

  int last = node_path.top()->value;
  node_path.pop();

  Delete(current, node_path, last);
  BalanceDelete(node_path, last);
}

template <typename T>
int AVLTree<T>::NodeHeight(Node *node) {
  if (!node) return 0;
  return node->height;
}

template <typename T>
void AVLTree<T>::Update(Node *node) {
  if (node) node->height = 1 + NodeHeight(node->left) + NodeHeight(node->right);
}

template <typename T>
void AVLTree<T>::SmallLeftRotate(Node *current_node, bool is_complex) {
  auto now = current_node->right;
  std::swap(current_node->value, now->value);
  auto left_node = current_node->left;

  current_node->left = now;
  current_node->right = now->right;
  now->right = now->left;
  now->left = left_node;

  update(current_node->left);
  update(current_node);

  if (!is_complex) {
    current_node->difference = -(now->difference + 1);
    now->difference = std::abs(current_node->difference);
  }

  std::swap(now->difference, current_node->difference);
}

template <typename T>
void AVLTree<T>::SmallRightRotate(Node *current_node, bool is_complex) {
  Node *now = current_node->left;
  std::swap(current_node->value, now->value);

  auto right_node = current_node->right;
  current_node->right = now;
  current_node->left = now->left;
  now->left = now->right;
  now->right = right_node;

  update(current_node->right);
  update(current_node);

  if (!is_complex) {
    current_node->difference = std::abs(now->difference - 1);
    now->difference = now->difference - 1;
  }

  std::swap(current_node->difference, now->difference);
}

template <typename T>
void AVLTree<T>::BigLeftRotate(Node *current_node) {
  SmallRightRotate(current_node->right, true);
  SmallLeftRotate(current_node, true);

  switch (current_node->difference) {
    case 0:
      current_node->right->difference = 0;
      current_node->left->difference = 0;
      current_node->difference = 0;
      break;
    case 1:
      current_node->right->difference = -1;
      current_node->left->difference = 0;
      current_node->difference = 0;
      break;
    case -1:
      current_node->right->difference = 0;
      current_node->difference = 0;
      current_node->left->difference = 1;
  }
}

template <typename T>
void AVLTree<T>::BigRightRotate(Node *current_node) {
  SmallLeftRotate(current_node->left, true);
  SmallRightRotate(current_node, true);

  switch (current_node->difference) {
    case 0:
      current_node->right->difference = 0;
      current_node->left->difference = 0;
      current_node->difference = 0;
      break;
    case 1:
      current_node->left->difference = 0;
      current_node->right->difference = -1;
      current_node->difference = 0;
      break;
    case -1:
      current_node->left->difference = 1;
      current_node->difference = 0;
      current_node->right->difference = 0;
  }
}

template <typename T>
void AVLTree<T>::BalanceInsert(std::stack<Node *> &node_path) {
  auto child_node = node_path.top();
  node_path.pop();

  while (!node_path.empty()) {
    auto parent_node = node_path.top();
    node_path.pop();

    if (parent_node->left == child_node)
      ++parent_node->difference;
    else
      --parent_node->difference;

    if (parent_node->difference == 0) break;

    if (parent_node->difference == 2) {
      if (parent_node->left->difference == 0 || parent_node->left->difference)
        SmallRightRotate(parent_node, false);
      else
        BigRightRotate(parent_node);
    }

    if (parent_node->difference == -2) {
      if (parent_node->right->difference == 0 ||
          parent_node->right->difference == -1)
        SmallLeftRotate(parent_node, false);
      else
        BigLeftRotate(parent_node);
    }

    if (parent_node->difference == 0) break;

    child_node = parent_node;
  }
}

template <typename T>
void AVLTree<T>::BalanceDelete(std::stack<Node *> &node_path, int child) {
  while (!node_path.empty()) {
    auto parent_node = node_path.top();
    node_path.pop();

    if (parent_node->value > child)
      --parent_node->difference;
    else
      ++parent_node->difference;

    if (std::abs(parent_node->difference) == 1) break;

    if (parent_node->difference == -2) {
      if (parent_node->right->difference == 1)
        BigLeftRotate(parent_node);
      else
        SmallLeftRotate(parent_node, false);
    }

    if (parent_node->difference == 2) {
      if (parent_node->left->difference == -1)
        BigRightRotate(parent_node);
      else
        SmallRightRotate(parent_node, false);
    }

    if (std::abs(parent_node->difference) == 1) break;

    child = parent_node->value;
  }
}

template <typename T>
void AVLTree<T>::Delete(Node *node, std::stack<Node *> &node_path, int &last) {
  --node->height;

  if (!node->left && !node->right) {
    if (node_path.empty()) {
      root_ = nullptr;
      return;
    }

    if (node_path.top()->right == node)
      node_path.top()->right = nullptr;
    else
      node_path.top()->left = nullptr;

    delete node;
  } else if (node->left && node->right) {
    auto current = node->right;
    node_path.push(node);

    while (current->left) {
      --current->number;

      node_path.push(current);
      current = current->left;
    }

    node->value = current->value;
    last = current->value;

    Delete(node_path, current, last);
  } else {
    Node *current;
    if (node->left)
      current = node->left;
    else
      current = node->right;

    node->value = current->value;
    node->difference = current->difference;
    node->left = current->left;
    current->left = nullptr;
    node->right = current->right;
    current->right = nullptr;

    delete current;
  }
}