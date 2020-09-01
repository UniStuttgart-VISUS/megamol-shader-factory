#pragma once

namespace megamol::shaderfactory {

template <typename T> void safe_delete_array(T* ptr) {
    if (ptr != nullptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

template <typename T> void safe_delete(T* ptr) {
    if (ptr != nullptr) {
        delete ptr;
        ptr = nullptr;
    }
}

} // end namespace megamol::shaderfactory
