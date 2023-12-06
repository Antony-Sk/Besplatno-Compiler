#include <stdio.h>
#include <stdbool.h>
long Plus_Integer_Integer_(long other, long this) {
    return this + other;
}

long Minus_Integer_Integer_(long other, long this) {
    return this - other;
}

long Mult_Integer_Integer_(long other, long this) {
    return this * other;
}

long Div_Integer_Integer_(long other, long this) {
    return this / other;
}

bool Less_Integer_Integer_(long other, long this) {
    return this < other;
}

bool LessEqual_Integer_Integer_(long other, long this) {
    return this <= other;
}
bool Equal_Integer_Integer_(long other, long this) {
    return this == other;
}

int Integer_() {
    return 0;
}

int Integer_Integer_(int i) {
    return i;
}


int toInteger_Real_(double i) {
    return i;
}
int toInteger_Boolean_(bool i) {
    return i;
}
bool Or_Boolean_Boolean_(bool a, bool b) {
    return a || b;
}
bool And_Boolean_Boolean_(bool a, bool b) {
    return a && b;
}
bool Xor_Boolean_Boolean_(bool a, bool b) {
    return a ^ b;
}
bool Not_Boolean_(bool a) {
    return !a;
}


long Print_Integer_(long i) {
    printf("%ld ", i);
    return i;
}
long Print_Ptr_(void* i) {
    printf("%p ", i);
    return 1;
}

