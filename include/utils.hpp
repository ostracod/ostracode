
#ifndef UTILS_HEADER_FILE
#define UTILS_HEADER_FILE

#import <vector>

// This function is a little expensive to invoke, so be careful.
template <class T1, class T2>
std::vector<T2 *> castPtrVector(std::vector<T1 *> ptrs) {
    std::vector<T2 *> output;
    for (auto &ptr : ptrs) {
        output.push_back(static_cast<T2 *>(ptr));
    }
    return output;
}

#endif


