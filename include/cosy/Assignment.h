// Copyright 2017 Hakan Metin
// Licensed under the GPL, Version 3.0 (the "License");

#ifndef INCLUDE_COSY_ASSIGNMENT_H_
#define INCLUDE_COSY_ASSIGNMENT_H_

#include "cosy/Literal.h"
#include "cosy/Bitset.h"
#include "cosy/Logging.h"

namespace cosy {

class Assignment {
 public:
    Assignment() {}
    explicit Assignment(unsigned int num_variables) {
        resize(num_variables);
    }
    ~Assignment() {}

    void resize(unsigned int num_variables);
    void assignFromTrueLiteral(Literal literal);
    void unassignLiteral(Literal literal);

    bool literalIsTrue(Literal literal) const;
    bool literalIsFalse(Literal literal) const;
    bool literalIsAssigned(Literal literal) const;
    bool variableIsAssigned(BooleanVariable variable) const;

    bool hasSameAssignmentValue(Literal x, Literal y) const;
    bool bothLiteralsAreAssigned(Literal x, Literal y) const;

    Literal getTrueLiteralForAssignedVariable(BooleanVariable var) const;
    Literal getFalseLiteralForAssignedVariable(BooleanVariable var) const;

    unsigned int numberOfVariables() const;

 private:
    Bitset64<LiteralIndex> _assignment;

    DISALLOW_COPY_AND_ASSIGN(Assignment);
};

inline void Assignment::resize(unsigned int num_variables) {
    _assignment.Resize(LiteralIndex(num_variables << 1));
}

inline
void Assignment::assignFromTrueLiteral(Literal literal) {
    DCHECK(!variableIsAssigned(literal.variable()));
    _assignment.Set(literal.index());
}

inline void Assignment::unassignLiteral(Literal literal) {
    DCHECK(variableIsAssigned(literal.variable()));
    _assignment.ClearTwoBits(literal.index());
}

inline bool Assignment::literalIsTrue(Literal literal) const {
    return _assignment.IsSet(literal.index());
}

inline bool Assignment::literalIsFalse(Literal literal) const {
    return _assignment.IsSet(literal.negatedIndex());
}

inline bool Assignment::literalIsAssigned(Literal literal) const {
    return _assignment.AreOneOfTwoBitsSet(literal.index());
}

inline bool Assignment::variableIsAssigned(BooleanVariable var) const {
    return _assignment.AreOneOfTwoBitsSet(LiteralIndex(var.value() << 1));
}

inline bool Assignment::hasSameAssignmentValue(Literal x, Literal y) const {
    return (literalIsAssigned(x) && literalIsAssigned(y)) &&
        !(literalIsTrue(x) ^ literalIsTrue(y));
}

inline bool Assignment::bothLiteralsAreAssigned(Literal x, Literal y) const {
     return literalIsAssigned(x) && literalIsAssigned(y);
}


inline Literal
Assignment::getTrueLiteralForAssignedVariable(BooleanVariable var) const {
    DCHECK(variableIsAssigned(var));
    return Literal(var, _assignment.IsSet(LiteralIndex(var.value() << 1)));
}

inline Literal
Assignment::getFalseLiteralForAssignedVariable(BooleanVariable var) const {
    DCHECK(variableIsAssigned(var));
    return Literal(var, !_assignment.IsSet(LiteralIndex(var.value() << 1)));
}

inline unsigned int Assignment::numberOfVariables() const {
    return _assignment.size().value() / 2;
}

}  // namespace cosy

#endif  // INCLUDE_COSY_ASSIGNMENT_H_
/*
 * Local Variables:
 * mode: c++
 * indent-tabs-mode: nil
 * End:
 */
