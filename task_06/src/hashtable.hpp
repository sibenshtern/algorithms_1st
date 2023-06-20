#include <algorithm>
#include <list>
#include <vector>

// Hash function for generic types
template <typename Key>
struct HashFunction {
  std::size_t operator()(const Key& key) const { return std::hash<Key>{}(key); }
};

template <typename Key, typename Value>
struct Entry {
  Key key;
  Value value;

  Entry(const Key& k, const Value& v) : key(k), value(v) {}
};

template <typename Key, typename Value, typename Hash = HashFunction<Key>>
class HashTable {
 public:
  HashTable(std::size_t size = kDefaultSize) : buckets_(size) {}

  void Insert(const Key& key, const Value& value);

  void InsertOrUpdate(const Key& key, const Value& value);

  void Remove(const Key& key);

  const Value Find(const Key& key) const;

  std::size_t Size() const;

 private:
  static constexpr std::size_t kDefaultSize = 16;

  std::vector<std::list<Entry<Key, Value>>> buckets_;

  std::size_t GetBucketIndex(const Key& key) const {
    Hash hashFunction;
    return hashFunction(key) % buckets_.size();
  }
};

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::InsertOrUpdate(const Key& key,
                                                 const Value& value) {
  std::size_t bucketIndex = GetBucketIndex(key);
  auto& bucket = buckets_[bucketIndex];

  auto it = std::find_if(
      bucket.begin(), bucket.end(),
      [&key](const Entry<Key, Value>& entry) { return entry.key == key; });

  if (it != bucket.end()) {
    it->value = value;
  } else {
    bucket.push_back(Entry<Key, Value>(key, value));
  }
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::Remove(const Key& key) {
  std::size_t bucketIndex = GetBucketIndex(key);
  auto& bucket = buckets_[bucketIndex];

  auto it = std::find_if(
      bucket.begin(), bucket.end(),
      [&key](const Entry<Key, Value>& entry) { return entry.key == key; });

  if (it != bucket.end()) {
    bucket.erase(it);
  }
}

template <typename Key, typename Value, typename Hash>
const Value HashTable<Key, Value, Hash>::Find(const Key& key) const {
  std::size_t bucketIndex = GetBucketIndex(key);
  const auto& bucket = buckets_[bucketIndex];

  auto it = std::find_if(
      bucket.begin(), bucket.end(),
      [&key](const Entry<Key, Value>& entry) { return entry.key == key; });

  if (it != bucket.end()) {
    return it->value;
  }

  return Value();
}

template <typename Key, typename Value, typename Hash>
std::size_t HashTable<Key, Value, Hash>::Size() const {
  std::size_t size = 0;
  for (const auto& bucket : buckets_) {
    size += bucket.size();
  }
  return size;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::Insert(const Key& key, const Value& value) {
  std::size_t bucketIndex = GetBucketIndex(key);
  auto& bucket = buckets_[bucketIndex];

  auto it = std::find_if(
      bucket.begin(), bucket.end(),
      [&key](const Entry<Key, Value>& entry) { return entry.key == key; });

  if (it == bucket.end()) {
    bucket.push_back(Entry<Key, Value>(key, value));
  } else {
    throw std::runtime_error(
        "If you want to update value, use InsertOrUpdate method.");
  }
}