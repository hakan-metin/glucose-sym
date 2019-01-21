// Copyright 2017 Hakan Metin - LIP6

#include "cosy/SymmetryFinder.h"
#include "cosy/BlissSymmetryFinder.h"

namespace cosy {

// static
SymmetryFinder*
SymmetryFinder::create(const CNFModel& model,
                       SymmetryFinder::Automorphism tool) {
    switch (tool) {
    case BLISS: return new BlissSymmetryFinder(model);
    default: return nullptr;
    }
}

}  // namespace cosy
