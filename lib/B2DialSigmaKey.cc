//
// Created by Giorgio Pintaudi on 2021/11/28.
//

#include <B2DialSigmaKey.hh>
#include <B2Sigma.hh>

B2DialSigmaKey::B2DialSigmaKey(B2Dial dial, B2Sigma sigma) : B2Dial(std::move(dial)), SigmaId(sigma) {}

bool B2DialSigmaKey::operator==(const B2DialSigmaKey &other) const {
  return B2Dial::operator==(other) && SigmaId == other.SigmaId;
}

std::ostream &operator<<(std::ostream &os, const B2DialSigmaKey &obj) {
  os << (B2Dial&) obj << ", SigmaId " << SigmaToString(obj.SigmaId);
  return os;
}

std::size_t dial_sigma_hash_fn::operator()(const B2DialSigmaKey &key) const {
  const dial_hash_fn dial_hash;
  std::size_t h1 = dial_hash(key);
  std::size_t h2 = std::hash<B2Sigma>()(key.SigmaId);
  return h1 ^ h2;
}

bool dial_sigma_key_equal_fn::operator()(const B2DialSigmaKey &t1, const B2DialSigmaKey &t2) const {
  return t1 == t2;
}