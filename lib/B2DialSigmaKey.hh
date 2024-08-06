//
// Created by Giorgio Pintaudi on 2021/11/28.
//

#ifndef WAGASCIREWEIGHT_B2DIALSIGMAKEY_HPP
#define WAGASCIREWEIGHT_B2DIALSIGMAKEY_HPP

#include <B2Dial.hh>
#include <B2Sigma.hh>

// Useful if a dial and sigma are used as a key in a hash map like std::unordered_map
struct B2DialSigmaKey : public B2Dial {

  B2Sigma SigmaId;

  B2DialSigmaKey(B2Dial dial, B2Sigma sigma);

  bool operator==(const B2DialSigmaKey &other) const;

  friend std::ostream &operator<<(std::ostream &os, const B2DialSigmaKey &obj);
};

std::ostream &operator<<(std::ostream &os, const B2DialSigmaKey &obj);

// hash function using a B2Dial object and B2Sigma variable as key
struct dial_sigma_hash_fn {
  std::size_t operator()(const B2DialSigmaKey &key) const;
};

// function comparing two B2DialSigmaKey objects
struct dial_sigma_key_equal_fn {
  bool operator()(const B2DialSigmaKey &t1, const B2DialSigmaKey &t2) const;
};

#endif // WAGASCIREWEIGHT_B2DIALSIGMAKEY_HPP